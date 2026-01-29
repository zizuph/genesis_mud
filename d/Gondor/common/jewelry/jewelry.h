#ifndef _JEWELRY_DEFINES_
#define _JEWELRY_DEFINES_
/* All defines must go below this line. */

#define JEWELRY_DIR             ("/d/Gondor/common/jewelry/")
#define JEWELRY_ID              "_saving_jewelry_id_"
#define ORDER_OBJ_ID            "_order_obj_id_"
#define ORDER_SUBLOC_GROUP      "_order_subloc_group_"
#define ORDER_SUBLOC            "_order_subloc_"
#define MAX_NUM                 5
#define CONSTRUCT_TIME          120.0

/* Regalia ranks */
#define KGC_RANK 2
#define KC_RANK 1
#define MEMBER_RANK 0

/* Regalia costs */
#define KGC_COST                432000
#define KC_COST                 259200
#define MEMBER_COST             86400
#define FOUND_COST              864000

#define PLAYER_I_GM_FREEBIE     "_player_i_gm_freebie"

/* Head Gear prices in coppers */
#define SIMPLE_BRONZE_PRICE     25920
#define SIMPLE_SILVER_PRICE     60480
#define KNIGHTLY_SILVER_PRICE   129600
#define KNIGHTLY_ELECTRUM_PRICE 172800
#define BARONIAL_ELECTRUM_PRICE 432000
#define BARONIAL_GOLD_PRICE     691200
#define DUCAL_GOLD_PRICE        1036800
#define DUCAL_PLAT_PRICE        1296000
#define PRINCELY_GOLD_PRICE     1468800
#define PRINCELY_PLAT_PRICE     1641600
#define PRINCELY_MITHRIL_PRICE  1728000
#define ROYAL_GOLD_PRICE        2073600
#define ROYAL_PLAT_PRICE        2592000
#define ROYAL_MITHRIL_PRICE     3456000

/* Other prices */
#define COLLAR_SILVER_PRICE     216000
#define COLLAR_ELECTRUM_PRICE   259200
#define COLLAR_GOLD_PRICE       302400
#define EQS_RING_PRICE          43200
#define MEDAL_PRICE             86400

/* The following are combined with their metal price for the total. */
#define RING_PRICE              17280
#define BRACELET_PRICE          3456
#define ANKLET_PRICE            6912
#define NECKLACE_PRICE          13824
#define TORC_PRICE              27648

/* Metal prices */
#define BRONZE_PRICE            864
#define SILVER_PRICE            1728
#define ELECTRUM_PRICE          3456
#define GOLD_PRICE              6912
#define PLATINUM_PRICE          13824
#define MITHRIL_PRICE           27648

#define ENGRAVING_PRICE         8640

#define METAL_PRICE             ({ BRONZE_PRICE, SILVER_PRICE, \
                                   ELECTRUM_PRICE, GOLD_PRICE, \
                                   PLATINUM_PRICE, MITHRIL_PRICE })

#define METALS                  ({ "bronze", "silver", "electrum", "gold", \
                                   "platinum", "mithril" })

/* All defines must go above this line. */
#endif _JEWELRY_DEFINES_
