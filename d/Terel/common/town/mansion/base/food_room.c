/*  Vader    9/27/92
 *
 *  This is the food storage room in the basement in the mansion in Calathin.
 *
 *  Here will be guards, an entrance to a 'jail', and a dumbwaiter which will
 *  connect other floors of the mansion with the rest of the mansion.
 *
 *  A quest will involve this room.  When a player enters, one of the guards
 *  become worried, and exit t room via the dumbwaiter, and relocate to
 *  a random room within the mansion.  It will be up to the player to fi
 *  find this guard, kill him, get the key, and complete the quest.
 */
inherit "/std/room.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"

#define TO         this_object()
#define TP         this_player()
#define DUMBWAITER (MANSION + "base/dumb")
#define EGUARD     (MANSION + "mon/evil_guard")

int level;
object guard1, guard2;

public void
reset_room()
{
   if (!guard1) {
       guard1 = clone_object(EGUARD);
       guard1->move_living("M", TO);
   }

   if (!guard2) {
       guard2 = clone_object(EGUARD);
       guard2->move_living("M", TO);
   }
}

public void
create_room()
{
   set_short("Food storage room");
   set_long("The shelves in this room once held jarred food that the owners " +
            "were preserving.  Now, they only hold dust.  There is a small " +
            "window here where light filters in.  The exit is to your south, " +
            "and there is a dumbwaiter here.\n");

   add_item(({"shelves", "shelf"}), "These dusty shelves are empty.\n");

   add_item(({"window", "small window"}), "It is a small window, set near " +
              "the ceiling of the room.  It is too small to climb through.\n");
   add_item(({"dumbwaiter"}), "It is just big enough for a person to sit in.\n");

   add_prop(ROOM_I_INSIDE, 0);
   level = 0;
   
   add_exit(DUMBWAITER, "dumbwaiter", "@@check_dumb");
   add_exit(BASE + "dungeon", "west", "@@guarded");
   add_exit(BASE + "hall1", "south", 0);
   
   DUMBWAITER->teleledningsanka();

   reset_room();
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

public int
guarded()
{
   if (guard1 && present(guard1) && CAN_SEE(guard1, TP))
   {
       TP->catch_msg(QCTNAME(guard1) + " stops you from going west.\n");
       tell_room(TO, QCTNAME(guard1) + " stops " + QTNAME(TP) +
                 " from going west.\n", ({TP, guard1}));
       return 1;
   }
   if (guard2 && present(guard2) && CAN_SEE(guard2, TP))
   {
       TP->catch_msg(QCTNAME(guard2) + " stops you from going west.\n");
       tell_room(TO, QCTNAME(guard2) + " stops " + QTNAME(TP) +
                 " from going west.\n", ({TP, guard2}));
       return 1;
   }
   return 0;
}

