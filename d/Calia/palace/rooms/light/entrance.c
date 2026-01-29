/* 
   Entrance room in the Calian palace.
   This room inherits kroug_palace_room to handle kroug raids  

   History:
            6/4/96     tidied up kroug handling         Maniac
          12/12/95      vandalism possibility added       Maniac
          22/9/95       kroug_palace_room inherited       Maniac
           8.12.94      minor changes                     Maniac
*/

#pragma save_binary

inherit "/d/Calia/std/kroug_palace_room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include "/d/Calia/std/vandalism.c"

#define NUM 3
object *calian = allocate(NUM);

void
make_monster(int i)
{
    calian[i] = clone_object(MONSTER("very_young_calian"));
    calian[i]->move(THIS);
    tell_room(THIS, QCNAME(calian[i]) + " arrives.\n");
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
    set_short("Palace entrance");
    set_long(
	"This is a large trapezoidal-shaped room whose east and west walls " +
	"slope away from you to the south.  " +
	"A brilliant light fills the room.  " +
	"\n");

    add_item(({"wall", "walls"}), "The east and west walls have the " +
             "thickness one would expect in a fortified building.\n");

    add_item("east wall", 
                     "The east wall has the thickness one would  " +
                     "expect in a fortified building. It " +
                     "is in good repair.\n");

    add_item("west wall", 
                     "The west wall has the thickness one would  " +
                     "expect in a fortified building. It " +
                     "is in good repair.\n");

    add_item_possible_vandalism("west wall", 
                          "The west wall has the thickness " +
                          "one would expect in a fortified building.",
                                ({"scratch", "smear"}), 50);

    add_item_possible_vandalism("east wall", 
                          "The east wall has the thickness " +
                          "one would expect in a fortified building.",
                                ({"scratch", "smear"}), 50);
    
    clone_object(DOOR("crystalline"))->move(THIS);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_LIGHT, 1);
    add_exit(ROOM("light_hall"), "north", 0);
    add_exit(ROOM("light_shop"), "east", 0);
    add_exit(ROOM("light_bank"), "west", 0);
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

    for (i = 0; i < NUM; i++)
        if (calian[i])
            return 1;

    remove_object();
}
