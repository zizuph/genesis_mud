#include "rangers.h"
#include "files.h"

#ifndef SHOP_DEFS
#define SHOP_DEFS

#ifndef SHOP_ITEMS
#define SHOP_ITEMS 1
#define BACKPACK        (RANGERS_OBJ + "backpack")
#define BACKPACKN       (RANGERS_OBJ + "backpackn")
#define BOOTS           (RANGERS_OBJ + "leather_boots")
#define BOW             (RANGERS_OBJ + "shortbow")
#define BOWSTRING       (RANGERS_OBJ + "bowstring")
#define BROWN_CLOAK     (RANGERS_OBJ + "brown_cloak")
#define COMMON_CLOAK    (RANGERS_OBJ + "common_cloak")
#define GAUNTLETS       (RANGERS_OBJ + "ith_gauntlets")
#define GREEN_CLOAK     (RANGERS_OBJ + "green_cloak")
#define GREY_CLOAK      (RANGERS_OBJ + "grey_cloak")
#define HERBCORD        "/d/Gondor/common/obj/herb_cord"
#define HERBGLOVES      "/d/Gondor/common/arm/herb_gloves"
#define HERBJAR         (RANGERS_OBJ + "herbjar")
#define HERBPOUCH       ("/d/Gondor/common/obj/herbpouch")
#define HOLSTER_ROI     (RANGERS_OBJ + "roi_holster")
#define HOLSTER_RON     (RANGERS_OBJ + "ron_holster")
#define KNIFE           "/d/Gondor/common/wep/woodknife"
#define MORTAR          "/d/Gondor/common/potions/mortar"
#define MOTTLED         (RANGERS_OBJ + "mottled_cloak")
#define OIL_FLASK       "/d/Shire/common/obj/oilflask"
#define OIL_LAMP        "/d/Gondor/common/obj/oil_lamp"
#define SATCHEL         "/d/Gondor/common/potions/satchel"
#define SCABBARD        (RANGERS_OBJ + "scabbard")
#define SCABBARD_ROI    (RANGERS_OBJ + "roi_scabbard")
#define SCABBARD_RON    (RANGERS_OBJ + "ron_scabbard")
#define SPOTTED_CLOAK   (RANGERS_OBJ + "ith_cloak")
#define TORCH           "/d/Gondor/common/obj/torch"
#define TRAVEL_CLOAK    (RANGERS_OBJ + "travel_cloak")
#define TRAVEL_HAT      (RANGERS_OBJ + "r_hat")
#define VIAL            POTION_VIAL_OBJECT
//#define WHETSTONE     RANGERS_OBJ + "whetstone"
#endif

#define GONDOR_EQUIP  ({ HERBJAR, HERBPOUCH, HERBGLOVES, HERBCORD, \
                         MORTAR, SATCHEL, VIAL, SCABBARD, \
                         BACKPACK, OIL_LAMP, OIL_FLASK, TORCH, \
                         BROWN_CLOAK, COMMON_CLOAK, KNIFE, TRAVEL_HAT, \
                      })
#define ITH_EQUIP     ({ HERBJAR, HERBPOUCH, SATCHEL, MORTAR, VIAL, \
                         BACKPACK, OIL_LAMP, OIL_FLASK, TORCH, \
                         GREEN_CLOAK, SPOTTED_CLOAK, COMMON_CLOAK, GAUNTLETS, \
                         KNIFE, TRAVEL_HAT, BOWSTRING, HERBGLOVES, \
                         MOTTLED, SCABBARD_ROI, HOLSTER_ROI \
                      })
#define NORTH_EQUIP   ({ HERBJAR, HERBPOUCH, MORTAR, SATCHEL, VIAL, \
                         BACKPACKN, OIL_LAMP, OIL_FLASK, TORCH, \
                         GREY_CLOAK, GREEN_CLOAK, COMMON_CLOAK, BOOTS, \
                         KNIFE, TRAVEL_HAT, BOWSTRING, HERBGLOVES, \
                         MOTTLED, SCABBARD_RON, HOLSTER_RON \
                      })
#endif SHOP_DEFS
