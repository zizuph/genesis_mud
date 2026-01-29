// file name:    /d/Avenir/common/dark/albus_base.c
// creator(s):   Casca, 11/24/99
// revisions: 
// purpose:          
// note:         This file is to be inherited in all albus rooms.  
//               The more frequent add_items should be placed here.
// bug(s):           
// to-do:            

#pragma strict_types

/* Inherit the standard room object */
inherit "/d/Avenir/inherit/room";

/* Inherit the room_tell functions */
inherit "/d/Avenir/inherit/room_tell";

/* Include the local area defines, etc */
#include "/d/Avenir/include/defs.h"            /* Short-hand macros */
#include "/d/Avenir/include/paths.h"           /* Avenirian path defines */
#include "/d/Avenir/include/macros.h"          /* ADD_SKIN, IN_IN, etc */
#include "/sys/macros.h"                       /* macros like VBFC and QNAME */
#include "/sys/stdproperties.h"                /* self-explanatory */


/* Prototypes */
/* These are the add_items and add_cmd_items for 
 * (see below)
 */
void add_air();
void add_floor();
void add_ceiling();
void add_ceiling2();
void add_cavern();
void add_room();
void add_walls();
void add_walls2();
void add_carved_room();
void add_cavern_room();
void add_fire();
void add_tents();
void add_bedding();


/*
 * Function name: create_albus_room
 * Description:   This function should be called to create albus rooms.
 */
void create_albus_room()
{
}

/*
 * Function name: reset_albus_room
 * Description:   This function should be called to reset albus rooms.
 */
void reset_albus_room()
{
    reset_domain_room();
}

/*
 * Function name: create_domain_room
 * Description:   This function creates a SMIS-enabled room.
 */
public void
create_domain_room()
{
    set_area("darkl2p");
    set_tell_time (250);

    /* Tells made to player when a room is occupied */

    add_tell("You hear the low muttering of voices.\n");
    add_tell("An unreconizable sound echoes through the cavern.\n");
    add_tell("You become aware of a barely audible scratching noise.\n");
    add_tell("There is something oppressive about this place, you feel "+
            "as though the walls are closing in on you.\n");

    /* If an add_item will be in every room, add it here */
        add_air();
        add_floor();

    
    /* It is dark in this area (see ~Avenir/include/macros.h
     * for this define and the one following) */
    IN_IN;
    IN;

    add_prop(ROOM_I_LIGHT, -3);
    add_prop(ROOM_I_HIDE, 0);

    create_albus_room();
    reset_albus_room();
}

/* These are the add_items and add_cmd_items for the tunnels.
 * (Those used more than once in the area).
 */

void
add_carved_room()
{
    add_ceiling2();
    add_walls2();
    add_room();
}

void
add_cavern_room()
{
    add_ceiling();
    add_walls();
    add_cavern();
    add_fire();
    add_tents();
    add_bedding();
}

void
add_air()
{
     /* Default in every room */
    add_cmd_item("air", "smell", "The air is thick with the smell of "+
        "unwashed bodies and cooking food.\n");
}

void
add_floor()
{
    /* Default in every room */
    add_item(({"floor","ground"}),
        "The rough and uneven floor is covered with a fine dark dirt "+
        "that is littered with many overlapping footprints.\n");
}


void 
add_ceiling()
{
    add_item(({"ceiling","roof","above"}),
        "The rough ceiling hangs far over your head, cloaked in shadow.\n");
}

void 
add_ceiling2()
{
    add_item(({"ceiling","roof","above"}),
        "The crudely carved rock hanging over your head is blackened "+
        "from years of smoke.\n");
}

void 
add_cavern()
{
    add_item(({"cavern","room"}),
        "This is a large natural cavern formed long ago by the mechanisms "+
        "of the planet.\n");
}

void 
add_room()
{
    add_item(({"cavern","room"}),
        "This is a small crudely carved room, chiseled from the dark "+
        "stone walls of the cavern.\n");
}

void 
add_walls()
{
    add_item(({"walls","wall"}),
        "The wall here is rough and naturally formed, marred only "+
        "by the rooms that have been carved deep into it.\n");
}

void 
add_walls2()
{
    add_item(({"walls","wall"}),
        "The walls are still rough and scarred from the tools "+
        "used during the excavation of this place.\n");
}

void
add_fire()
{
    add_item(({"fire","fires","campfire","campfires"}),"You see several "+
        "at various places in the cavern. Some have hunks of meat or "+
        "crude pots over them.\n");
    add_tell("The fire pops and sizzles as fat from the roasting meat "+
        "falls into the flames.\n");
    add_tell("The fire crackles and pops, throwing a beautiful cascade of "+
        "sparks arcing through the air.\n");
}

void
add_tents()
{
    add_item(({"tent","tents"}),"Several small tents that are simple open-ended "+
        "sections of cloth supported by pieces of wood.  They provide some "+
        "privacy for their occupants.\n");
    add_tell("The fabric of the tent sways slightly with the ebb and flow "+
        "of a breeze.\n");
}

void
add_bedding()
{
    add_item(({"bedding","bed"}),"These are piles of furs that have "+
        "been bundled together. "+
        "They provide a slightly more comfortable bed than the ground.\n");
}
      
/* Start the room tells as soon as someone enters the room */
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
        start_room_tells();
}

/*
 * Function name: 
 * Description:   
 * Arguments:     
 * Returns:       
 */
