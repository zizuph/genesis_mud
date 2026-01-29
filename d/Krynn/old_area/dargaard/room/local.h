#ifndef _DARGAARD_LOCAL_H
#define _DARGAARD_LOCAL_H

/* Include the common definitions of Krynn. */
#include "/d/Krynn/common/defs.h"

/* Defined paths */
#define DARGAARD       "/d/Krynn/dargaard/"
#define NPC            DARGAARD + "npc/"
#define ARMOUR         DARGAARD + "armour/"
#define OBJ            DARGAARD + "obj/"
#define WEAPON         DARGAARD + "weapon/"
#define STD            DARGAARD + "std/"
#define ROOM           DARGAARD + "room/"

/* Some other paths that should be used */
#define OUTROOM        STD + "outdoor_base"
#define INROOM         STD + "indoor_base"

/* The Wizard responsible for this area */
#define RESPONSIBLE ({"vidur"})

#define LONG(x)        set_long(BSN(x))

#endif _DARGAARD_LOCAL_H

