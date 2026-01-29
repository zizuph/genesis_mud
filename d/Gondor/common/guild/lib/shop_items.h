#ifndef SHOP_ITEMS
#define SHOP_ITEMS 1
#define HERBJAR       "/d/Gondor/common/guild/obj/herbjar"
#define HERBPOUCH     "/d/Gondor/common/guild/obj/herbpouch"
#define HERBGLOVES    "/d/Gondor/common/arm/herb_gloves"
#define HERBCORD      "/d/Gondor/common/obj/herb_cord"
#define MORTAR        "/d/Gondor/common/potions/mortar"
#define VIAL          "/d/Gondor/common/potions/vial"
#define SATCHEL       "/d/Gondor/common/potions/satchel"
#define BACKPACK      "/d/Gondor/common/guild/obj/backpack"
#define OIL_LAMP      "/d/Gondor/common/obj/oil_lamp"
#define OIL_FLASK     "/d/Gondor/common/obj/oilflask"
#define TORCH         "/d/Gondor/common/obj/torch"
#define WHETSTONE     "/d/Gondor/common/guild/obj/whetstone"
#define BROWN_CLOAK   "/d/Gondor/common/guild/obj/brown_cloak"
#define GREY_CLOAK    "/d/Gondor/common/guild/north/obj/grey_cloak"
#define GREEN_CLOAK   "/d/Gondor/common/guild/obj/green_cloak"
#define CAMO_CLOAK    "/d/Gondor/common/guild/obj/ith_cloak"
#define GAUNTLETS     "/d/Gondor/common/guild/obj/ith_gauntlets"
#define BOOTS         "/d/Gondor/common/guild/obj/leather_boots"
#define TRAVEL_CLOAK  "/d/Gondor/common/guild/obj/travel_cloak"
#define	KNIFE	      "/d/Gondor/common/wep/woodknife"
#define TRAVEL_HAT    "/d/Gondor/common/guild/obj/r_hat"
#define BOWSTRING     "/std/bowstring"
#define WRAP          "/d/Shire/common/herbs/obj/wrap"

#endif

#define GONDOR_EQUIP  ({ HERBJAR, HERBPOUCH, HERBGLOVES, HERBCORD, \
                         MORTAR, SATCHEL, VIAL, \
                         BACKPACK, OIL_LAMP, OIL_FLASK, TORCH, \
                         WHETSTONE, BROWN_CLOAK, \
                         KNIFE, TRAVEL_HAT,  \
                      })
#define ITH_EQUIP     ({ HERBJAR, HERBPOUCH, SATCHEL, MORTAR, VIAL, \
                         BACKPACK, OIL_LAMP, OIL_FLASK, TORCH, \
                         WHETSTONE, GREEN_CLOAK, CAMO_CLOAK, GAUNTLETS, \
                         KNIFE, TRAVEL_HAT, BOWSTRING, \
                      })
#define NORTH_EQUIP   ({ HERBJAR, HERBPOUCH, MORTAR, SATCHEL, VIAL, \
                         BACKPACK, OIL_LAMP, OIL_FLASK, TORCH, \
                         WHETSTONE, GREY_CLOAK, GREEN_CLOAK, BOOTS, \
                         KNIFE, TRAVEL_HAT, \
                      })
