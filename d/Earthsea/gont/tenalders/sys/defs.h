/**********************************************************
 *   include domain paths
 ***************************************************************/
#include "/d/Earthsea/sys/paths.h"
/***********************************************************
 *    MACROS
 ****************************************************************/

#include "/d/Earthsea/sys/bits.h"
#define BS(str, int)   break_string(str, int)
#define TP     this_player()
#define TO     this_object()
#define E(x)     environment(x)

/***********************************************
 *  Local defs
 *********************************************/
#define TERRAIN_HEADER "/d/Earthsea/sys/terrain_types.h"
#define EARTHSEA_PROPS "/d/Earthsea/sys/properties.h"
#define HERB_DIR "/d/Earthsea/herbs/herb_store_files/"
#define HERB_OBJ "/d/Earthsea/herbs/obj/"
#define HERB_SEARCH "/d/Earthsea/herbs/specials/hs.c"
#define HERB_FILES "/d/Earthsea/herbs/herb_files/"
#define HERB_SETS "/d/Earthsea/herbs/herb_sets/"
#define FOREST_HERB_SET "/d/Earthsea/herbs/herb_sets/forest_herbs.h"
#define GARDEN_HERB_FILE "/d/Earthsea/herbs/herb_sets/garden_herbs.h"
#define MEADOW_HERB_SET "/d/Earthsea/herbs/herb_sets/meadow_herbs.h"


#define TA_DIR     "/d/Earthsea/gont/tenalders/"
#define LIVING TA_DIR+"npc/"
#define TA_SPECIALS    TA_DIR+"specials/"
#define TA_OBJ      TA_DIR+"obj/"
#define TA_ITEMS   TA_OBJ+"items/"
#define TA_WEAPONS TA_DIR+"wep/"
#define TA_ARMOURS TA_DIR+"arm/"
#define DOORS       TA_OBJ+"doors/"
#define VILLAGE       TA_DIR+"village/"
#define HIGH_FALL TA_DIR+"high_fall/"
#define ROOF VILLAGE+"witch_roof.c"
#define STORE VILLAGE+"store.c"
#define SOUTH_PATH TA_DIR+"south_path/"
#define CAMP1 SOUTH_PATH + "camp_1/"
#define CAMP2 SOUTH_PATH+ "camp2/"
#define CAVES   HIGH_FALL+"caves/"
#define GONT "/d/Earthsea/gont/"
#define BEACH GONT + "beach/"


/****************************************************
 *  VARIOUS PROPS
 *****************************************************/
#define GAVE_CREAM "_gave_cream"
/********************************************************
  *  INHERITED OBJECTS
 ****************************************************/
#define ROOM_TELL "/d/Earthsea/lib/room_tell.c"
#define INTRO "/d/Earthsea/lib/intro.c"
#define REMEMBER "/d/Earthsea/lib/remember.c"
#define FEMALE_KARG "/d/Earthsea/gont/tenalders/npc/karg_f.c"
#define BASIC_KARG "/d/Earthsea/gont/tenalders/npc/basic_karg.c"
#define BASIC_GUARD "/d/Earthsea/gont/tenalders/npc/basic_guard.c"
#define BASE_HERB_ROOM "/d/Earthsea/gont/tenalders/std/base_herb_room.c"
#define BASE_FOR_ROOM  "/d/Earthsea/gont/tenalders/std/\
base_forest_room.c"
#define CLIMB "/d/Earthsea/gont/tenalders/high_fall/climb.c"
#define AMBUSH "/d/Earthsea/gont/tenalders/south_path/ambush.c"
#define QUEST_HANDLER_HEADER "/d/Earthsea/quest_handler/\
quest_handler.h"
#define GLOOMY "/d/Earthsea/gont/tenalders/south_path/\
base_south_path"
#define FARM "/d/Earthsea/gont/tenalders/south_path/\
base_south_path_w.c"
#define AUTO_TEAM "/d/Earthsea/gont/tenalders/npc/auto_teaming.c"
#define CONTROL "/d/Earthsea/gont/tenalders/std/control_room.c"

/***********************************************************
  *  SPECIAL ROOMS
  ***************************************************************/
#define CLIFF1 HIGH_FALL+"cliff1.c"
#define CLIFF2 HIGH_FALL+"cliff2.c"
#define CLIFF3 HIGH_FALL+"cliff3.c"
#define CLIFF4 HIGH_FALL+"cliff4.c"
#define CLIFF5 HIGH_FALL+"cliff5.c"
#define TOP HIGH_FALL+"cliff_top.c"
#define LEDGE HIGH_FALL+"ne7.c"
#define WITCH_GARDEN VILLAGE+"witch_garden_3.c"

/***************************************************
  *  NPCS, ARMOURS, WEAPONS, AND OTHER OBJECTS
/********************************************************/
#define BRASS_KEY 123654
#define CRYSTAL_KEY 1000004
#define DIAMOND_KEY 2000004
#define MITHRIL_KEY 3000004
#define CLOVER4 HERB_FILES + "clover4.c"
#define BASKET TA_ITEMS + "basket"
#define SPARROWHAWK LIVING+"goatherd.c"
#define SMITH LIVING+"smith.c"
#define WITCH LIVING+"herb_witch.c"
#define SNAKE LIVING+"garden_snake.c"
#define RABBIT LIVING+"rabbit.c"
#define BLIND_MAN LIVING+"blind_man.c"
#define WORM LIVING+"wooley_worm.c"
#define GRIZZLY_BEAR LIVING + "grizzly.c"
#define GOPHER LIVING+"gopher.c"
#define BIRD LIVING+"baby_bird.c"
#define GOAT LIVING + "goat.c"
#define EUNUCH LIVING + "eunuch"
#define KARGESS_UNARMED LIVING + "kargess_unarmed"
#define KARGESS_AXE LIVING + "kargess_axe"
#define CAT LIVING + "cat"
#define KARG1 LIVING + "karg1.c"
#define KARG2 LIVING + "karg2.c"
#define KARG3 LIVING + "karg3.c"
#define KARG4 LIVING + "karg4.c"
#define KARG5 LIVING + "karg5.c"
#define KARG6 LIVING + "karg6.c"
#define KARGS ({ KARG1, KARG2, KARG3, KARG4, KARG5 })
#define CAPTAIN LIVING + "karg_captain.c"
#define STOREKEEPER LIVING + "storekeeper"
#define BEE LIVING + "ta_bee.c"


#define GOAT_SPELL "noth hierth malk man hiolk han merth han"

/*   ASSORTED QUEST PROPS
 ******************************************/
#define GOT_I_GOAT_SPELL "_got_i_goat_spell"
#define GETTING_I_THE_WAX "_getting_i_the_wax"
#define WORM_GIVEN "_worm_given_"
#define GOT_KITTY_QUEST "_player_i_got_kitty_quest_"
#define GOT_GOAT_QUEST "_player_i_got_goat_quest_"
#define GOT_LUCKY_QUEST "_player_i_got_lucky_quest_"
#define GOT_PARCHMENT_QUEST "_player_i_got_parchment_quest_"
#define PLAYER_I_FOUND_PARCHMENT "_player_i_found_parchment_"
#define PLAYER_I_GOT_SHELL_QUEST "_player_i_got_shell_quest_"
#define PLAYER_I_ATTACKED_GOAT "_player_i_attacked_goat"
// *bad* player, who attacked the quest goat!


#define EA_SCROLL TA_ITEMS+ "ea_scroll.c"
#define HONEYCOMB TA_ITEMS + "honeycomb.c"
#define HAMMER TA_WEAPONS+"hammer.c"
#define SMITH_OVERALLS TA_ARMOURS+"smith_overalls.c"
#define BOOTS TA_ARMOURS+"boots.c"
#define BUST TA_ARMOURS+"bust.c"
#define AUNTIE_DRESS TA_ARMOURS+"dress.c"
#define TATTERED_ROBE TA_ARMOURS+"robe.c"
#define GAUNTLETS TA_ARMOURS+"gauntlets.c"
#define DRAGON_HELM TA_ARMOURS+"dragon_helm.c"
#define CLOAK TA_ARMOURS+"velvet_cloak.c"
#define BLACK_CLOAK TA_ARMOURS+"black_cloak.c"
#define GREEN_CLOAK TA_ARMOURS+"emerald_cloak.c"
#define AXE TA_WEAPONS+"crescent_axe.c"
#define LANCE TA_WEAPONS + "lance.c"
#define BRONZE_PLATE TA_ARMOURS + "bronze_plate.c"
#define BRONZE_HELM TA_ARMOURS + "bronze_plate_helm.c"
#define HALBERD TA_WEAPONS+"unholy_halberd.c"
#define EMERALD_RING TA_ARMOURS+"emerald_ring.c"
#define GOLD_PLATE TA_ARMOURS + "gold_plate.c"
#define SASH TA_ARMOURS + "sash.c"
#define RUBY_RING TA_ARMOURS+"ruby_ring.c"
#define BLACK_RING TA_ARMOURS + "black_ring.c"
#define SPIKE_BOOTS TA_ARMOURS + "spike_boots.c"
#define CIRCLET TA_ARMOURS+"circlet.c"
#define RINGMAIL TA_ARMOURS+"ringmail.c"
#define LEATHER TA_ARMOURS + "leather_armour.c"
#define L_HELM TA_ARMOURS + "leather_helm.c"
#define BANDS TA_ARMOURS + "arm_bands.c"
#define LOINCLOTH TA_ARMOURS+"loincloth.c"
#define COLLAR TA_ARMOURS+"collar.c"
#define BLIND_STICK TA_WEAPONS+"blind_stick.c"
#define SCIMITAR TA_WEAPONS + "scimitar"
#define BRONZE_AXE TA_WEAPONS + "bronze_axe"
#define SPEAR TA_WEAPONS + "spear"
#define CLUB TA_WEAPONS + "club"
#define HORSESHOE TA_ITEMS+"horseshoe.c"
#define GOOD_APPLE TA_ITEMS + "good_apple.c"
#define JON_APPLE TA_ITEMS + "jon_apple.c"
#define BAD_APPLE TA_ITEMS + "bad_apple.c"
#define GREEN_WORM TA_ITEMS+"worm.c"
#define CREAM TA_ITEMS + "cream"
