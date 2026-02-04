/*  Coded by Vader on 9/28/92
 *
 *  This is a dumbwaiter.  It will be possible to take the player up
 *  or down using 'rope up' or 'rope down'.  There will be as
 *  many possible destinations as there are floors in the mansion.  Entry
 *  will be guarded, so that no more than one person can enter the dumbwaiter
 *  at a time, and they cannot enter unless the dumbwaiter is on their floor.
 *
 */
inherit "/std/room.c";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Terel/common/terel_defs.h"

/* DEFINE A FEW CONSTANTS */

#define TP          this_player()
#define ETP         environment(TP)
#define FLOORS      ({MANSION + "base/food_room",\
                      MANSION + "rooms/kitchen"})
#define START_FLOOR 0

int floor_num=START_FLOOR;
object occupant=0;

public void
create_room()
{
    set_short("inside a dumbwaiter");
   set_long( "This small dumbwaiter is just big enough for you to fit.  No one " +
            "else could fit in at the same time.  Its walls are made of wood, " +
            "which are stained by a few drops of blood.  There is also " +
            "a rope here.  To operate the dumbwaiter, just use " +
            "'rope up' or 'rope down'.\n");

   add_item(({"rope"}), "This rope is old, but solid.\n");
   add_exit("@@query_floor_name", "out", 0);
}

public void
init()
{
   ::init();
   add_action("do_pull", "rope");
}

public int
do_pull(string str)
{
   if (!str) return 0;
   
   if (str == "up")
   {
      if (floor_num < sizeof(FLOORS)-1)
      {
         floor_num++;
         write("You pull yourself and the dumbwaiter up one level.\n");
         return 1;
      }
      else
      {
         write("You cannot go any higher.\n");
         return 1;
      }
   }
   if (str == "down")
   {
      if (floor_num > 0)
      {
         floor_num--;
         write("You pull you and the dumbwaiter down one level.\n");
           return 1;
      }
      else
      {
         write("You cannot go any lower.\n");
         return 1;
      }
   }
   notify_fail("Rope how?\n");
   return 0;
}

public string
query_floor_name()
{
   return FLOORS[floor_num];
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    if (occupant && ob == occupant) occupant = 0;
}

public void
move_me_from_outside(int level)
{
   if (floor_num == level) {
       if (occupant)
           TP->catch_msg("The dumbwaiter is already on this floor, but " +
                         "is occupied by " + QTNAME(occupant) + ".\n");
       else
           write("The dumbwaiter is already here!\n");
       return;
   }
   if (occupant) {
       write("The dumbwaiter is currently occupied by someone.\n");
       return;
   }
   tell_room(ETP, "The dumbwaiter arrives to this floor.\n");
   floor_num = level;
}

public int
can_i_enter(int level)
{
   if (floor_num != level) {
       write("The dumbwaiter is not at this floor.\n");
       return 1;
   }
   if (occupant) {
       TP->catch_msg("The dumbwaiter is currently occupied by " +
                     QTNAME(occupant) + ".\n");
       return 1;
   }
   occupant = TP;
   return 0;
}
