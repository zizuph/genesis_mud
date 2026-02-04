/*  This is the Torture room, for the basement of the Mansion in the town
    of Calathin.  The player will be able to ring a bell.  If he or she is
    stupid enough to do this, he will immeadiatly be tortured, and lose
    a certain percentage of his maximum hit points (yes, CAN be killed,
    if he is already hurt damaged enough when he rings the bell)
*/

inherit "/std/room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Terel/common/terel_defs.h"

public int no_victim();

static object victim = 0;

public void
create_room()
{
   set_short("large workroom");
   set_long(
    "This is a rather large workroom, where the master of this house often " +
    "played around with various inventions and potions and such.  Scattered " +
    "around, you can see various devices.  In the middle of the " +
    "room, you can see the rack.  To the north side, there is a nail " +
    "coffin.  It looks like some of this equipment has been used " +
    "recently.  There is a small bell, hanging from the ceiling.\n");

   add_item(({"bell", "small bell"}), "It is a small bell, made of brass.  " +
     "There is a small sign attached to it that reads 'Ring for service'.\n");
     
   add_item(({"rack"}), "A large table, made of boards that separate " +
     "when you turn a large wheel at the side of the table.  There " +
     "are shackles here to hold the victim down while his body is " +
     "being expanded.\n");
     
   add_item(({"dark-hooded man", "man", "torturer"}), "@@exa_torturer");

   add_item(({"coffin", "nail coffin", "iron maiden"}), "Filled with " +
     "nails this iron " +
     "maiden, he or she who rests in here will feel many sharp pains.\n");

   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);

   add_exit(BASE + "hall3", "south", "@@leave_check");
}

public string
exa_torturer()
{
   if (victim && environment(victim) == this_object()) {
      return "The dark-hooded man is the professional torturer.\n"; 
   } else {
      return "He is not here. Why not ring the bell?\n";
   }
}

public void
init()
{
   ::init();
   add_action("do_torture", "ring");
}

public int
do_torture(string str)
{
   notify_fail("Ring what? Bell?\n");
   if (str != "bell") return 0;
   
   if (victim && this_player() == victim) {
       write("You cannot reach the bell.\n");
       return 1;
   }
   
   write("You ring the bell.\n");
   say(QCTNAME(this_player()) + " rings the bell.\n");
   
   if (victim) {
       tell_room(this_object(), "The dark-hooded man says: " +
                 "I'm busy right now.\n");
       return 1;
   }

   tell_room(this_object(), "A dark-hooded human arrives.\n");
   
   victim = this_player();
   
   set_alarm(2.0, -1.0, "strap_wait");

   return 1;
}

public void
strap_wait()
{
   if (no_victim()) return;
   
   victim->catch_msg("The dark-hooded human grabs you " +
                     "and straps you to a table.\n");
   tell_room(this_object(), 
        "The dark-hooded human grabs " + QNAME(victim) +
        " and straps " + victim->query_objective()  +
        " to a table.\n", victim);
   
   set_alarm(2.0, -1.0, "try_wait");
}

public void
try_wait()
{
   if (no_victim()) return;
   
   victim->catch_msg("You try to get away, but cannot.\n");
   tell_room(this_object(), QCTNAME(victim) +
             " tries to get away, but cannot.\n", victim);
   
   set_alarm(2.0, -1.0, "lever_wait");
}

public void
lever_wait()
{
   if (no_victim()) return;
   
   victim->catch_msg("The dark-hooded human pulls a lever, " +
                     "and you feel INTENSE pain.\n");
   tell_room(this_object(), "The dark-hooded human pulls a lever and " +
        QTNAME(victim) + " screams as if " + victim->query_pronoun() +
        " feels INTENSE pain.\n", victim);
   
   victim->command("$moan painfully");

   victim->reduce_hit_point(victim->query_max_hp()/2);
   if (victim->query_hp() <= 0) {
       victim->do_die(this_object());
       tell_room(this_object(), "The dark-hooded man " +
                 "shivers with satisfaction.\n");
   }
   set_alarm(2.0, -1.0, "release_wait");
}

public void
release_wait()
{
   if (no_victim()) return;
   
   victim->catch_msg("The dark-hooded human releases " +
                     "you from the table.\n");
   tell_room(this_object(), "The dark-hooded human releases " +
             QTNAME(victim) + " from the table.\n", victim);
   victim = 0;
   set_alarm(1.0, -1.0, "no_victim");
}

public int
leave_check()
{
   if (victim && environment(victim) == this_object()) {
     if (this_player() == victim) {
         write("The dark-hooded human will not allow that.\n");
         return 1;
     } else {
         this_player()->catch_msg("You feel good about leaving " +
             "this area. " + QCTNAME(victim) + " would appreciate " +
             "it even more.\n");
         return 0;
     }
   } else {
     write("You feel good about leaving this area.\n");
     return 0;
   }
}

public int
no_victim()
{
    if (!victim || environment(victim) != this_object())
        victim = 0;
        
    if (victim) return 0;
    
    tell_room(this_object(), "The dark-hooded man leaves south.\n");
    return 1;
}
