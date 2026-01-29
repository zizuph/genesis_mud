#ifndef _darkenwd_local_h_
#define _darkenwd_local_h_

#include "/d/Krynn/common/defs.h"

/* Standard defines */
#define PARENT             "/d/Krynn/"
#define DARKENWD           PARENT + "darkenwd/"
#define STD                DARKENWD + "std/"
#define TDIR               DARKENWD + "road/"
#define WEAPON             TDIR + "weapon/"
#define ARMOUR             TDIR + "armour/"
#define NPC                TDIR + "npc/"
#define OBJ                TDIR + "obj/"
#define LOG                TDIR + "log/"

/* defines to make it easier for me */
#define AI                 add_item

/* connections to the outside world */
#define SOL_ROAD           PARENT + "solace/road/"
#define HAV_ROAD           PARENT + "haven/road/"
 
/* Base room defines */
#define ROADOUT            STD + "roadout_base"
#define INCAVE             STD + "in_room"

/* places to visit */
#define DEFAULT            0
#define SHORE              1
#define PATH               2
#define ROAD               3
#define FOREST             4
#define TRAIL              5

/* the wizard(s) responsible for this area */
#define RESPONSIBLE        ({"teth"})

#endif _darkenwd_local_h_


