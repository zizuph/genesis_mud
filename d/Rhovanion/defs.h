/* 
 * This is the standard definitions file for Rhovanion
 */

#ifndef DO_I_TELL_RUMOURS
#define DO_I_TELL_RUMOURS  "_do_i_tell_rumours"
#endif 

#ifndef RHOVANION_COMMON_DEFINITIONS
#define RHOVANION_COMMON_DEFINITIONS

#define BS(x)        (x)
#define NF(x)        notify_fail(x)
#define TP           this_player()
#define TO           this_object()
#define PO	     previous_object()
#define ENV          environment
#define CAP(x)       capitalize(x)
#define LOW(x)       lower_case(x)
#define ONE_OF_LIST(x) x[random(sizeof(x))]
#define HE(who)      who->query_pronoun()
#define HIS(who)     who->query_possessive()
#define HIM(who)     who->query_objective()

#define ANDUIN_DIR  "/d/Rhovanion/common/anduin/"
#define MISTY_DIR    "/d/Rhovanion/common/misty/"
#define MIRK_DIR    "/d/Rhovanion/common/mirkwood/"
#define ERE_DIR      "/d/Rhovanion/common/erebor/"
#define ESG_DIR      "/d/Rhovanion/common/esgaroth/"
#define RHUN_DIR     "/d/Rhovanion/common/rhun/"
#define NPC_DIR      "/d/Rhovanion/common/npcs/"
#define OBJ_DIR      "/d/Rhovanion/common/objects/"
#define ARMOUR_DIR   "/d/Rhovanion/common/armours/"
#define WEAPON_DIR   "/d/Rhovanion/common/weapons/"
#define HERB_DIR     "/d/Rhovanion/common/herbs/"
#define CAMP_DIR     RHUN_DIR + "camp/"

/*
 * This sorts lines of file in alphabetic order
 */
#define SORT_FILE(file) ((int)"/d/Rhovanion/lib/sort_file.c"->sort_file(file))

#endif
