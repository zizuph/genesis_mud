inherit "/std/room.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"

#define TP          this_player()
#define DUMBWAITER  (MANSION + "base/dumb")

int level;

public void
create_room()
{
    set_short("Kitchen");
   set_long(
     "You have entered the kitchen of this large mansion.  It is " +
     "filled with all of the implements to feed the family members, " +
     "servants, and guests of the house.  Against one wall, you see " +
     "a line of fireplaces, used to cook in.  There is a large cutting " +
     "table placed in the middle of the room, and several hundred " +
     "pots, pans, and utensils are scattered across the room.  " +
     "There is also a dumbwaiter here.  A trail of blood leads from " +
     "the dumbwaiter to a cutting table.\n");

   add_item(({"cutting table", "table"}),
     "This large table is covered in blood, as if fresh meat " +
     "was prepared for cooking recently.\n");

   add_item(({"fireplaces", "fireplace"}),
     "One of them seems to be cooking something in a large iron " +
     "cauldron.\n");

   add_item(({"cauldron", "iron cauldron", "large iron cauldron"}),
     "It bubbles and it boils.  Occasionally, bits and " +
     "pieces of vegetables float to the top, and sink back down " +
     "again.  Suddenly, an eye floats to the top.  These people are " +
     "cooking people!   How sickening!\n");
   add_item(({"dumbwaiter"}),
     "This dumbwaiter looks as if it can hold one and only one " +
     "person.  There is a set of ropes here, so if the dumbwaiter is " +
     "not at this floor, just pull the rope.\n");

   add_prop(ROOM_I_INSIDE, 1);
   level = 1;
   
   add_exit(DUMBWAITER, "dumbwaiter", "@@check_dumb");
   add_exit(MANSION + "wing_e5", "south", 0);
   add_exit(MANSION + "rooms/dining", "west", 0);
   DUMBWAITER->teleledningsanka();
}

public void
init()
{
    ::init();
    add_action("get_dumb", "pull");
}

public int
get_dumb(string str)
{
    notify_fail("Pull what?\n");
    if (str != "rope") return 0;
   
    write("You pull the rope.\n");
    say(QCTNAME(TP) + " pulls the rope.\n");

    DUMBWAITER->move_me_from_outside(level);

    return 1;
}

public int
check_dumb()
{
   return DUMBWAITER->can_i_enter(level);
}
