/*     Created by:     Sir Toby, 97-06-24
 *     Location:       North end of sewers. The lizards lair 
 *     Modified:       Toby, 97-07-03
 */

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/sewers/lizards_lair/path.h"

object guard1, guard2, guard3, guard4;


void
reset_room()
{

   if (!guard1)
      {
      guard1 = clone_object("/d/Kalad/common/sewers/npc/g_lizard_guard.c");
      guard1 -> arm_me();
      guard1 -> move_living("M",TO);      
      }

   if (!guard2)
      {
      guard2 = clone_object("/d/Kalad/common/sewers/npc/g_lizard_guard.c");
      guard2 -> arm_me();
      guard2 -> move_living("M",TO);      
      }

   if (!guard3)
      {
      guard3 = clone_object("/d/Kalad/common/sewers/npc/g_lizard_guard.c");
      guard3 -> arm_me();
      guard3 -> move_living("M",TO);      
      }

   if (!guard4)
      {
      guard4 = clone_object("/d/Kalad/common/sewers/npc/g_lizard_guard.c");
      guard4 -> arm_me();
      guard4 -> move_living("M",TO);
      guard1 -> team_join(guard2);
      guard1 -> team_join(guard3);
      guard1 -> team_join(guard4);      

      tell_room(TO,"Four guards arrive looking for their " +
		   "next victim.\n");
      }
}

      


void
create_room()
{
::create_room();

    set_short("Inside a tunnel");
    set_long("You are step into a large room dimly lit by torches " +
            "resting in holders cut out of the walls. The walls " +
            "are made of stone but as you look up you notice that " +
            "they turn to mud and the ceiling is totaly cut out of " +
            "mud. The air is chilly and moist. " + "@@dwarf_check");

    add_item( ({"wall","walls","mud wall","mud walls"}),
            "The walls are cut directly out of the rock and mud.\n");
    add_item("ceiling","The ceiling is cut directly out of the mud and " +
            "supported by wooden beams.\n");
    add_item( ({"beam","beams","wooden beam","wooden beams"}),
            "The beams are made out of fresh wood and supports the " +
            "ceiling safely.\n");
    add_item("ground","The ground is made of stone and it looks like " +
                     "it has not been cleaned for a long time.\n");
    add_item( ({"tunnel","tunnels"}),"You would have to enter the " +
            "tunnels to find out more of them.\n");
    add_item( ({"holder","holders"}), "They are drilled directly " +
            "into the rockwall.\n");
    add_item( ({"torch","torches"}),"It is small standard torches.\n");

    add_cmd_item("air",({"smell","sniff"}),
                "The air smells of dirt and sweat.\n");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,-2);

    add_exit(PATH + "ll4.c","north",0,1);
    add_exit(PATH + "ll5.c","south",0,1);
    add_exit(PATH + "ll6.c","east",0,1);
    add_exit(PATH + "ll2.c","west",0,3);
    set_noshow_obvious(1);

reset_room();
}


string
dwarf_check()
{
    if(TP->query_race() == "dwarf")
        return"The ground not sloping in this room and you see exits " +
             "to the north and south. Looking east and west you see " +
             "a tunnel stretching.\n";

    return"You see exits to the north and south. A tunnel opens up " +
         "to the east and west.\n";
}
