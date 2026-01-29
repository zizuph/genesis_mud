/*
 * 20110829 Lunatari
 *
 * Removed leading 0 from K_HOLE1 (also in crypt/local.h)
 */
#define PARENT	"/d/Krynn/solace/"
#define DOR_DIR    "/d/Krynn/dorak/"
#define TDIR	PARENT + "graves/"
#define CRYPT     TDIR + "crypt/"
#define BOOK	TDIR + "book/"
#define LOG	TDIR + "log/"
#define MONSTER	TDIR + "mnstrs/"
#define OBJ	TDIR + "obj/"

#define C_SOLACE	PARENT + "new_village/east_road4"

#define GRAVE_STD	"/d/Krynn/solace/graves/grave_std"
#define OUTSIDE_BASE    "/d/Krynn/solace/std/outside_base"
#define INSIDE_BASE     "/d/Krynn/solace/std/inside_base"

#define K_HOLE1         232773270
#define GRAVE_LOG	"/d/Krynn/common/log/graves/"
#define NUM_OF_GRAVES	20
#define CONTROLLER	TDIR + "controller"

#define ADD_GRAVES	add_item(({"grave", "graves"}), "@@graves");
#define ADD_GRAVEYARD      add_item("graveyard", graveyard);
#define READ_GRAVE	add_cmd_item(({"on", "grave"}), "read", "@@grave_look");

/* The wiz/ files havn't been changed. */
