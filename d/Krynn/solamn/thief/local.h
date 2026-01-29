/* The local.h file for the caves beneath the Vingaard Mountains */

#include "/d/Krynn/common/defs.h"

/*Whoami?*/
#define WIZARD_IN_CHARGE  "Aridor"

/*Directories*/
#define PARENT  "/d/Krynn/solamn/"
#define TDIR    PARENT + "thief/"
#define OBJ     TDIR + "obj/"
#define LIV     TDIR + "living/"
#define GUILDR  TDIR + "guild/"
#define TOBJ    GUILDR + "obj/"
#define CAVERN  TDIR + "cavern/"
#define DEWAR   TDIR + "theiwar/"
#define THEIWAR TDIR + "theiwar/"
#define LOG     GUILDR + "log/"
#define POBJ    PARENT + "palan/obj/"

/*General Base room*/
#define ROOM_BASE TDIR + "room_base";

/*Theiwar Base*/
#define THEIWAR_BASE LIV + "theiwar_base";

/*Thief area*/
#define TURNA   CAVERN + "turning_a"
#define TURNB   CAVERN + "turning_b"
#define TURNC   CAVERN + "turning_c"
#define DOOR_ROOM_BASE  CAVERN + "door_room_base";

/*Theiwar area*/
#define THEIWARTABLE  "/d/Krynn/common/rndtables/tbltheiwar"
#define LIGHTDARKROOM THEIWAR + "lightdarkroom"
#define MININGROOM    THEIWAR + "mining_room"
#define MECHANISM     (THEIWAR + "mechanism")
#define DOORROOM      (THEIWAR + "r11")
#define GUARDROOM     (THEIWAR + "r13")
#define CAST_IRON     "/d/Genesis/start/hobbit/v/cast_iron"

/* a PROP- used in the thief entrance quest */
#define THIEF_I_CAN_ENTER      "_thief_i_can_enter"
/* a PROP- used in the dwarfgate quest */
#define PLAYER_I_DWARFGATE     "_player_i_dwarfgate"
/* a save-file used in the dwarfgate quest */
#define NUMBER_SOLVED          OBJ + "num_solved_dwfgt"
#define NUM_BLOCK_LOCATIONS    3
#define PRODUCE                ({ OBJ + "dudgeon", OBJ + "axe" })

/* connections to the world */
#define WATERFALL      PARENT + "splains/room/waterfall"
#define WATERROOM      PARENT + "splains/room/in_water"
#define IN_CAVE        PARENT + "vin_mount/cave/cave3"
#define PALANWALL      PARENT + "palanthas/shipping/wall"
#define ON_THE_PLAINS  PARENT + "splains/room/mount1"
