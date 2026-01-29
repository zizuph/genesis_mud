/* Hall in the Crystalline palace of the Calians.

   History:
          6/4/96     tidied up kroug handling         Maniac
         12/12/95     vandalism possibility added       Maniac
         22/9/95      Kroug raid code installed         Maniac
          8.12.94     minor changes                     Maniac
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
    calian[i] = clone_object(MONSTER("young_calian"));
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
    set_short("Hall");
    set_long(
	"This is a small trapezoidal-shaped room whose east and west walls " +
	"slope away from you to the south.  " +
	"This room is filled by a brilliant light. " +
	"Paintings adorn the east wall.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_NO_CLEANUP, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_exit(ROOM("light_entrance"), "south", 0);
    add_exit(ROOM("light_stairs"), "north", 0);
    add_exit(ROOM("light_trainroom"), "west", 0);
    add_exit(ROOM("light_post"), "east", 0);

    add_item( ({ "wall", "east wall", "paintings" }),
             "There are many paintings hung on the east wall. One of them " +
             "appears to depict Caliana.\n");
 
    add_item(({"painting", "painting of caliana", "caliana painting"}),
         "A painting of Caliana is hung on the east wall. The athletic " +
         "heroine is depicted in full battle dress, a great helm nearly " +
         "hiding her austere elven features.\n");

    add_item_possible_vandalism("painting of caliana", "A painting of " +
           "Caliana is hung on the east wall.", ({"smear", "tear"}), 85);

    add_item("walls", "");
    add_item(({"room"}), "");
    reset_room();
}

void
init()
{
    ::init();
    init_vandalism();
}

