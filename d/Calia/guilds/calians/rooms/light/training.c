/*      This is a room in the crystal palace.

    coder(s):   Glykron & Maniac

    history:    12/12/95     vandalism possibility added     Maniac
                 22/9/95     Kroug raid code installed       Maniac
                 8.12.94    minor changes                   Maniac
                31. 8.93    modified                        Glykron

    purpose:    to guard stairs
    exits:	s to guild, e to stairs, n to silver room, w to late room

    npcs:	Calians in Training
    objects:    none

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/

#pragma save_binary

inherit "/std/room";
inherit "/d/Calia/std/kroug_palace_room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include "/d/Calia/std/vandalism.c"

#define NUM 2
object *calian = allocate(NUM);

void
make_monster(int i)
{
    object this;

    this = THIS;
    calian[i] = clone_object(MONSTER("calian_in_training"));
    calian[i]->move(THIS);
    tell_room(THIS, QCTNAME(calian[i]) + " arrives.\n");
}

void
reset_room()
{
    int i;

    for (i = 0; i < NUM; i++)
	if (!calian[i])
	    make_monster(i);
}

void
create_room()
{
    set_short("The training room");
    set_long(
	"This is a small trapezoidal-shaped room whose north and south walls " +
	"slope away from you to the west. On the floor are a number of " + 
        "training mats, and a stuffed straw model of a warrior stands " +
        "in the middle of the room.\n");

    add_item(({"straw model", "model", "stuffed straw model", "warrior"}),
             "A stuffed straw model of a warrior, used for youth training " +
             "purposes (to practise hitting accurately with polearms). It " +
             "is in fine condition.\n"); 

    add_item_possible_vandalism("stuffed straw model", 
             "A stuffed straw model of a warrior, used for youth training " +
             "purposes (to practise hitting accurately with polearms).",
             ({"smear", "shatter"}), 20);

    add_item(({"mats", "training mats"}), "Training mats are placed on the " +
             "floor to prevent damage from falls when training.\n");

    add_item(({"wall", "walls"}), "");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_NO_CLEANUP, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_exit(ROOM("light_stairs"), "east", 0);
    add_exit(ROOM("light_late"), "west", 0);
    add_exit(ROOM("light_silver"), "north", 0);
    add_exit(ROOM("light_trainroom"), "south", 0);
    reset_room();
}


void
init()
{
    ::init();
    init_vandalism();
}


public int
clean_up()
{
    int i;

    for(i = 0; i < NUM; i++)
        if(calian[i])
            return 1;

    remove_object();
}

