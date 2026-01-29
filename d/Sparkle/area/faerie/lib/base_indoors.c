/*
 * Base file for indoor rooms in Faerie
 * By Finwe, August 2004
 */

#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit "/std/room";
//inherit S_LIB_CLOCK;
inherit COMMON_BASE;

void create_indoor_room() {}
 
int room_num;
   
public void
create_room()
{

    set_short("an indoor room in Green Oaks");
    set_long("Inside a building in Green Oaks.\n");

    add_item(({"walls", "wall"}),
        "The walls are smooth and made from white blocks of stone. " +
        "Exquisite carvings have been engraved into the walls. They seem " +
        "alive and almost sing with life.\n");
    add_item(({"floor", "ground"}),
        "The floor made from white blocks of stone. They are smooth " +
        "and plain, except for the carvings of springtime grass " +
        "engraved into the floor.\n");
    add_item(({"carvings", "exquisite carvings"}),
        "They depict landscapes and other quiet scenes to elves. They " +
        "are so perfectly carved, the landscapes seem to draw " +
        "you in, mesmerizing you with their beauty.\n");
    add_item(({"white stones", "white blocks of stone", "blocks of stone"}),
        "The blocks of stone are square and fitted perfectly together. " +
        "Only hair-line cracks are visible where the stones meet. The " +
        "stones are smooth and decorated only with exquisite carvings.\n");
    add_item(({"landscapes", "quiet scenes", "scenes"}),
        "There are many scenes depicted, and some you recognize. There are " +
        "scenes like of quiet forests and joyous celebrations. These " +
        "scenes are so perfectly carved, they seem alive.\n");
    add_item(({"forests", "quiet forests"}),
        "These are still images of forests that elves visit. They are " +
        "realistc and breathtaking.\n");
    add_item(({"celebrations", "joyous celebration"}),
        "These are scenes from one of many elven celebration. The " +
        "elves look joyful in their merrymaking.\n");
    add_item(({"room", "area"}),
        "This is a spacious room. It is made from white blocks of " +
        "stone that  have been polished smooth and almost seem to " +
        "be alive.\n");

    
    create_indoor_room();
    reset_room();
 
    add_prop(ROOM_I_INSIDE, 1); // This is an indoor room
    add_prop(ROOM_I_NO_ALLOW_STEED, 1); // sorry, no horses in here.
 
}
 
/******************************************************************************
 * Main routines for describing areas
 ******************************************************************************/
/*
 * Function name : set_add_dome
 * Description   : adds descr of the inside of the domes
 */
void set_add_dome()
{
    add_item(({"ceiling", }),
        "The ceiling made from white stone and is square. Set in the " +
        "center of the ceiling is a white dome.\n");
    add_item(({"dome"}),
        "It is perfectly round and made from smooth white stones. It " +
        "rises above you. The inside of the dome is " +
        "decorated with engravings that resemble the sky. The lower " +
        "end of the dome resembles tree tops. The upper end of the " +
        "dome resembles the sky with only a few clouds drifting across it.\n");
    add_item(({"sky"}),
        "The sky is plain inside the dome, but is decorated with a " +
        "few puffy clouds.\n");
    add_item(({"clouds"}),
        "The clouds inside the dome are puffy looking. They are engraved " +
        "onto the dome, and seem to move slowly around the inside of " +
        "the dome.\n");
    add_item(({"treetops"}),
        "The treetops are carved onto the lower end of the dome. They " +
        "look full and seem to move in the breeze.\n");
}

/*
 * Function name : set_add_ceiling_flat
 * Description   : adds descr of a flat ceiling. Allows strings to be added to 
 *                 personalize ceiling, ie stairs, etc.
 */

void set_add_ceiling_flat(string str)
{
    add_item(({"ceiling"}),
        "The ceiling is made from white stone and is flat. " + str + "\n");
   
}

/*
 * Function name : set_add_stairs_up
 * Description   : adds descr of stairs on lower floor
 */
void set_add_stairs_up()
{
    add_item(({"staircase", "stairs", "stairway"}),
           "They follow the wall and lead upstairs through a hole in " +
           "the ceiling.\n");          
}

/*
 * Function name : set_add_stairs_dn
 * Description   : adds descr of stairs on upper floor
 */
void set_add_stairs_dn()
{
    add_item(({"stairs", "staircase", "stairway"}),
        "The staircase is set in the back of the room. They descend " +
        "through a hole in the floor to the level below.\n");
}

/*
 * Function name : set_add_counter
 * Description   : adds descr of stairs on upper floor
 */
void set_add_counter()
{
    add_item(({"counter", "wooden counter"}),
        "The counter is wide and made from a large piece of wood. It " +
        "has been stained and polished to a dark luster.\n");
}

