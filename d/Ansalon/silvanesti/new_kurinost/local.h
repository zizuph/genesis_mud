/*
 * local.h
 *
 * Local defines for the new Kurinost camp
 *
 * Copyright (C): Kellon, November 2010
 *
*/
// F I L E   D E F I N I T I O N S
#define RSDIR           "/d/Ansalon/silvanesti/new_kurinost/"
#define RSROOMS         RSDIR + "rooms/"
#define RSOBJS          RSDIR + "objs/"
#define RSTXT           RSDIR + "text/"
#define RSLIVING        RSDIR + "living/"
#define RSWEAPON        RSDIR + "weapon/"
#define RSARMOUR        RSDIR + "armour/"

#define DRACONIANBASE   "/d/Krynn/solamn/splains/living/"
#define BAAZ    "/d/Krynn/common/monster/baaz_base"
#define BOZAK   "/d/Krynn/common/monster/bozak_base"
#define KAPAK   "/d/Krynn/common/monster/kapak_base"
#define SIVAK   "/d/Krynn/common/monster/sivak_base"
#define AURAK   "/d/Krynn/common/monster/aurak_base"

#define SHOREBASE       RSROOMS + "shore_base"
#define CLIMBBASE       RSROOMS + "climb_base"
#define CAMPBASE        RSROOMS + "camp_base"
#define INSIDEBASE      RSROOMS + "inside_base"
#define BEACHBASE       RSROOMS + "beach_base"
#define FORESTBASE      RSROOMS + "forest_base"

// M A P   D E F I N I T I O N S
#define KURINOSTMAP     add_prop(ROOM_S_MAP_FILE, "new_kurinost_map.txt");

// O T H E R   D E F I N I T I O N S
// ROCKY SHORE
#define LEDGEFOUND      "_kurinost_cliffs_ledge_found_"
#define LEDGESEEN       "_kurinost_cliffs_ledge_seen_"
#define LEDGENOTIFY     "_kurinost_cliffs_notify_player_"
#define LEDGEHINT       "_kurinost_cliffs_hint_given_"
#define RSCAVEFOUND     "_kurinost_cave_found_"
#define RSAMBUSHCAVE    RSROOMS + "rs_ambushcave"

#define PEARNAME        "_kurinost_prickly_pear"
#define CAPERNAME       "_kurinost_small_caper"
#define EGGNAME         "_kurinost_gull_egg"
#define NESTNAME        "_kurinost_gullnest"

#define GULLNAME        "_kurinost_seagull"
#define GULLCOLOURS     ({ "white", "grey", "greyish", "lavender" })
#define GULLADJS        ({ "grey-winged", "black-tipped", "black-headed", "white-winged" })

// DRACONIAN CAMP
#define PLFOUNDSHED     "_kurinost_camp_pl_did_find_shed_"
#define PLFOUNDWINDOW   "_kurinost_camp_pl_did_find_window_"

#define DC_KEYNAME      "_rusty_key_to_door_in_small_shed_"
#define DC_SATCHEL      "_kurinost_camp_secret_satchel_"
#define DC_DOCUMENT     "_kurinost_camp_secret_document_"
#define DC_DRIFTWOOD    "_kurinost_camp_beach_driftwood_"
#define DC_BONENAME     "_kurinost_camp_meat_bone_"
#define PARCHMENT_FILE  RSTXT + "parchment.txt"

#define HOBGNAME        "_kurinost_hobgoblin"
#define HOBGSTR         ({ "strong", "powerful", "muscular" })
#define HOBGADJS        ({ "scarred", "dark-skinned", "pale-faced", "black-skinned", "ugly", "angry", "dangerous" })


