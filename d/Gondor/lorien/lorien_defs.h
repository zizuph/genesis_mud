/*
 * /d/Gondor/lorien/defs.h
 * 
 * Lorien definitions
 *
 * Created by Mona 2020
 */

#ifndef __LORIEN_DEFINES__
#define __LORIEN_DEFINES__

#include "/d/Gondor/defs.h"

#define LORIEN_DIR              "/d/Gondor/lorien/"
#define LORIEN_DIR_NPC          (LORIEN_DIR + "npc/")
#define LORIEN_DIR_OBJ          (LORIEN_DIR + "obj/")
#define LORIEN_DIR_STD          (LORIEN_DIR + "std/")
#define LORIEN_STD_DIR          (LORIEN_DIR + "std/")

#define DIMRILL_DIR             (LORIEN_DIR + "dimrill/")
#define DIMRILL_DIR_NPC         (DIMRILL_DIR + "npc/")
#define DIMRILL_DIR_OBJ         (DIMRILL_DIR + "npc/")
#define DIMRILL_DIR_RM          (DIMRILL_DIR + "rooms/")

#define MERE_DIR                (DIMRILL_DIR + "mirrormere/")
#define MERE_DIR_RM             (MERE_DIR + "rooms/")

#define PLAINS_DIR              "/d/Gondor/lorien/plains/"
#define E_ROAD_DIR              "/d/Gondor/lorien/eastroad/"
#define M_ROAD_DIR              "/d/Gondor/lorien/mallornroad/"
#define W_ROAD_DIR              "/d/Gondor/lorien/westroad/"

#define SILVERLODE_DIR          (LORIEN_DIR + "silverlode/")


// IMPORTANT change below in dimrill_base.c to add our own tree shadow
#define AN_OBJ_DIR               "/d/Gondor/anorien/cairandros/obj"

#define LATE_NIGHT              0..3    /*12am-3am*/
#define EARLY_MORNING           4..7    /*4am-7am*/
#define MORNING                 8..10   /*8am-10am*/
#define NOON                    11..13  /*11am-1pm*/
#define AFTERNOON               14..17  /*2pm-5pm*/
#define EVENING                 18..21  /*6pm-9pm*/
#define EARLY_NIGHT             22..24  /*10pm-12am*/

//#define NIPHREDIL               HERB_DIR + "niphredil"
//#define ELANOR                  HERB_DIR + "elanor"
#define LOTHORE                 HERB_DIR + "lothore"
#define REDWEED                 HERB_DIR + "redweed"
#define ATHELAS                 HERB_DIR + "athelas"
#define HOLLY                   HERB_DIR + "holly"
#define TUO                     HERB_DIR + "tuo"
#define ALFIRIN                 HERB_DIR + "alfirin"
#define FOXGLOVE                HERB_DIR + "foxglove"
#define ANNA                    HERB_DIR + "anna"
#define YAVE                    HERB_DIR + "yave.c"
#define ASTALDO                 HERB_DIR + "astaldo",
#define ATTANAR                 HERB_DIR + "attanar"
#define BASIL                   HERB_DIR + "basil"
#define BLACKBERRY              HERB_DIR + "blackberry"
#define BLUEBERRY               HERB_DIR + "blueberry"
#define BLUNG                   HERB_DIR + "blung"
#define BRASPBERRY              HERB_DIR + "braspberry"
#define CARAWAY                 HERB_DIR + "caraway"
#define CARROT                  HERB_DIR + "carrot"
#define GARLIC                  HERB_DIR + "garlic"
#define GONION                  HERB_DIR + "gonion"
#define GINGER                  HERB_DIR + "ginger"
#define HANDASSE                HERB_DIR + "handasse"
#define MINT                    HERB_DIR + "mint"
#define LISSUIN                 HERB_DIR + "lissuin"
#define MYRTLE                  HERB_DIR + "myrtle"
#define SEREGON                 HERB_DIR + "seregon"
#define SURANIE                 HERB_DIR + "suranie"
#define PINOLME                 HERB_DIR + "pinolme"
#define TYELKA                  HERB_DIR + "tyelka"
#define UNGOLESTEL              HERB_DIR + "ungolestel"
#define VORONWIE                HERB_DIR + "voronwie"

#endif