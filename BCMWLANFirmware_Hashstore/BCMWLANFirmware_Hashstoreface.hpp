//
//  BCMWLANFirmware_HashstoreInterface.hpp
//  BCMWLANFirmware_Hashstore
//
//  Created by qcwap on 2020/9/7.
//  Copyright © 2020 钟先耀. All rights reserved.
//

#ifndef BCMWLANFirmware_HashstoreInterface_hpp
#define BCMWLANFirmware_HashstoreInterface_hpp

#include "Airport/Apple80211.h"
#include <IOKit/IOLib.h>
#include <libkern/OSKextLib.h>
#include <sys/kernel_types.h>
#include <HAL/ItlHalService.hpp>

class BCMWLANFirmware_HashstoreInterface : public IO80211Interface {
    OSDeclareDefaultStructors(BCMWLANFirmware_HashstoreInterface)
    
public:
    virtual UInt32   inputPacket(
                                 mbuf_t          packet,
                                 UInt32          length  = 0,
                                 IOOptionBits    options = 0,
                                 void *          param   = 0 ) override;

    bool init(IO80211Controller *controller, ItlHalService *halService);

private:
    ItlHalService *fHalService;
};

#endif /* BCMWLANFirmware_HashstoreInterface_hpp */
