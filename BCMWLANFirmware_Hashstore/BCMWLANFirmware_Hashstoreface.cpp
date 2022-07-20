//
//  BCMWLANFirmware_HashstoreInterface.cpp
//  BCMWLANFirmware_Hashstore
//
//  Created by qcwap on 2020/9/7.
//  Copyright © 2020 钟先耀. All rights reserved.
//

#include "BCMWLANFirmware_HashstoreInterface.hpp"

#define super IO80211Interface
OSDefineMetaClassAndStructors(BCMWLANFirmware_HashstoreInterface, IO80211Interface);

const char* hexdump(uint8_t *buf, size_t len)
{
    ssize_t str_len = len * 3 + 1;
    char *str = (char*)IOMalloc(str_len);
    if (!str)
        return nullptr;
    for (size_t i = 0; i < len; i++)
    snprintf(str + 3 * i, (len - i) * 3, "%02x ", buf[i]);
    str[MAX(str_len - 2, 0)] = 0;
    return str;
}

bool BCMWLANFirmware_HashstoreInterface::
init(IO80211Controller *controller, ItlHalService *halService)
{
    if (!super::init(controller)) {
        return false;
    }
    this->fHalService = halService;
    return true;
}

UInt32 BCMWLANFirmware_HashstoreInterface::
inputPacket(mbuf_t packet, UInt32 length, IOOptionBits options, void *param)
{
    ether_header_t *eh;
    size_t len = mbuf_len(packet);
    
    eh = (ether_header_t *)mbuf_data(packet);
    if (len >= sizeof(ether_header_t) && eh->ether_type == htons(ETHERTYPE_PAE)) { // EAPOL packet
        const char* dump = hexdump((uint8_t*)mbuf_data(packet), len);
        IOLog("itlwm: input EAPOL packet, len: %zu, data: %s\n", len, dump ? dump : "Failed to allocate memory");
        if (dump)
            IOFree((void*)dump, 3 * len + 1);
        return IO80211Interface::inputPacket(packet, (UInt32)len, 0, param);
    }
    return IOEthernetInterface::inputPacket(packet, length, options, param);
}
