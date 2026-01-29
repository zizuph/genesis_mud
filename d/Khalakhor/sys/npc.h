/*
 *   Khalakhor NPC Defines for Common NPCs
 *
 *   This file must be included whenever a common npc is to be added
 *   to a room. This includes the common dwarf, goblin, human and elf
 *   to make cloning of these critters easier.
 *
 *   Generally, you would use this in tandem with the paths.h file in
 *   /d/Khalakhor/sys/.
 */

#include "/d/Khalakhor/sys/paths.h"

#ifndef _KHALAKHOR_NPC_DEFS_
#define _KHALAKHOR_NPC_DEFS_

// Common dwarf npc defines
#define DWCITIZEN        0
#define DWTRADES         1
#define DWMINER          2
#define DWGUARD          3
#define DWWARRIOR        4
#define DWELITE          5
#define DWSUPREME        6

// Common elf npc defines
// Will need more when the time comes
#define ELFCITIZEN       0
#define ELFTRADES        1
#define ELFWARRIOR       2

// Common goblin npc defines
#define GOBSLAVE         0
#define GOBWORKER        1
#define GOBPATROL        2
#define GOBGUARD         3
#define GOBWARRIOR       4
#define GOBELITE         5
#define GOBSUPREME       6

// Common human npc defines
#define HUMCITIZEN       0
#define HUMTRADES        1
#define HUMPATROL        2
#define HUMGUARD         3
#define HUMWARRIOR       4
#define HUMELITE         5
#define HUMSUPREME       6

// Common talamhdubh npc defines
// None under warrior class & high numbers to make them similar.
#define TALWARRIOR       7
#define TALELITE         8
#define TALSUPREME       9

// Arrays storing weapons and armours. See a cloned npc for an example.
// See /d/Shire/orcmaker/orcmaker.h and orcmaker.c to see how this works.

#define HUMPATROL_WEP ({ "dirk" })

// For npc specific properties eg KILLER props,
// define in /d/Khalakhor/sys/properties.h

#endif
