/***************************************************************************
 *                                                                         *
 *          ###########   ###########   ##########    ##########           *
 *         ############  ############  ############  ############          *
 *         ##            ##            ##   ##   ##  ##        ##          *
 *         ##            ##            ##   ##   ##  ##        ##          *
 *         ###########   ####  ######  ##   ##   ##  ##    ######          *
 *          ###########  ####  #       ##   ##   ##  ##    #    #          *
 *                   ##  ##    ######  ##   ##   ##  ##    #    #          *
 *                   ##  ##    #       ##   ##   ##  ##    #    #          *
 *         ############  ##### ######  ##   ##   ##  ##### ######          *
 *         ###########    ###########  ##   ##   ##   ##########           *
 *                                                                         *
 *            S E C U R E   M O B I L E   N E T W O R K I N G              *
 *                                                                         *
 * This file is part of NexMon.                                            *
 *                                                                         *
 * Copyright (c) 2016 NexMon Team                                          *
 *                                                                         *
 * NexMon is free software: you can redistribute it and/or modify          *
 * it under the terms of the GNU General Public License as published by    *
 * the Free Software Foundation, either version 3 of the License, or       *
 * (at your option) any later version.                                     *
 *                                                                         *
 * NexMon is distributed in the hope that it will be useful,               *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 * GNU General Public License for more details.                            *
 *                                                                         *
 * You should have received a copy of the GNU General Public License       *
 * along with NexMon. If not, see <http://www.gnu.org/licenses/>.          *
 *                                                                         *
 **************************************************************************/

#pragma NEXMON targetregion "patch"

#include <firmware_version.h>   // definition of firmware version macros
#include <debug.h>              // contains macros to access the debug hardware
#include <wrapper.h>            // wrapper definitions for functions that already exist in the firmware
#include <structs.h>            // structures that are used by the code in the firmware
#include <helper.h>             // useful helper functions
#include <patcher.h>            // macros used to craete patches such as BLPatch, BPatch, ...
#include <rates.h>              // rates used to build the ratespec for frame injection
#include <nexioctls.h>          // ioctls added in the nexmon patch
#include <version.h>            // version information

#define IP_PROTOCOL_ICMP    0x1
#define ICMP_TYPE_REQUEST   0x8
#define ICMP_TYPE_REPLY     0x0
#define ARP_REQ_SINK        0x4 /* Input packet should be discarded */

static int i = 0;

int
wl_arp_recv_proc_hook(struct wlc_info **arpi, struct sk_buff *p)
{
    struct ethernet_ip_icmp_ping_header *frame = (struct ethernet_ip_icmp_ping_header *) p->data;
    struct wlc_info *wlc = *arpi;

    if (frame->ip.protocol == IP_PROTOCOL_ICMP && frame->icmp.type == ICMP_TYPE_REQUEST) {
        //printf("%s: %d\n", __FUNCTION__, i++);

        struct sk_buff *p_reply = (struct sk_buff *) pkt_buf_dup_skb(wlc->osh, p);
        frame = (struct ethernet_ip_icmp_ping_header *) p_reply->data;

        // switch dst and src mac addresses
        uint8 mac[6];
        memcpy(mac, frame->ethernet.dst, 6);
        memcpy(frame->ethernet.dst, frame->ethernet.src, 6);
        memcpy(frame->ethernet.src, mac, 6);

        // switch dst and src ip addresses
        uint32 ip;
        ip = frame->ip.dst_ip.integer;
        frame->ip.dst_ip.integer = frame->ip.src_ip.integer;
        frame->ip.src_ip.integer = ip;

        // change icmp type from request to reply
        frame->icmp.type = ICMP_TYPE_REPLY;

        // fix icmp checksum
        uint32 checksum = ntohs(frame->icmp.checksum);
        checksum += 0x800;
        checksum = ((checksum & 0xffff0000) >> 16) + (checksum & 0xffff);
        frame->icmp.checksum = htons(checksum);

        wlc_sendpkt(wlc, p_reply, *(int *) (((int) arpi) + 0x168));

        return ARP_REQ_SINK;
    }

    return wl_arp_recv_proc(arpi, p);
}


__attribute__((at(0x1893F0, "", CHIP_VER_BCM4339, FW_VER_6_37_32_RC23_34_43_r639704)))
BLPatch(wl_arp_recv_proc_hook, wl_arp_recv_proc_hook);