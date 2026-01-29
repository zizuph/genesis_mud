inherit "/std/room.c";

#include "/d/Rhovanion/defs.h"
#include <macros.h>
#include <stdproperties.h>

#define MAX_NO_SERV 3

/* 
* Prototypes
*/
void do_add_exits();
void do_remove_exits();

/* 
* Global variables
*/
public int p_centerstone, called;

public void
reset_room()
{
   if (p_centerstone) do_remove_exits();
   p_centerstone = 0;
   called = MAX_NO_SERV;
}

void
create_room()
{
   set_short("passageway");
   set_long("You are in one of the many stretches of tunnel this place " +
      "seems to be riddled with.  The floors and ceiling are constructed " +
      "of large, stone blocks and the floor here is geometrically arranged " +
      "with large, curved stone blocks like in the walls, but arranged in " +
      "a circle around an oddly shaped center stone.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({ "block", "blocks" }), "These are large, dark blocks of " +
      "stone approximately one by two feet in dimension.  They all " +
      "appear to be nearly identical so you figure they must have been " +
      "worked on by a master stoneworker.\n");
   add_item(({ "center stone", "stone" }), "This stone is smooth, more " +
      "polished then the rest a bit, and expertly set into the floor " +
      "perfectly level obviously by a truly skillfull master craftsman.  " +
      "There is some odd dust around the edges of the stone.\n");
   add_item("dust", "As you examine it closer, you see it is not really " +
      "dust, but tiny little chips of stone that form from rubbing stone " +
      "against stone. Perhaps you should examine the center stone more " +
      "closely.\n");
   add_item("center stone closely", "You take a good, hard look at the center stone again and realize it is raised slightly higher than the other stones around it.  It might have been set into the floor more recently or tampered ith in some way.  Strange...\n");
   add_exit("/d/Rhovanion/mute/dungeon1/tun3","east");
   add_exit("/d/Rhovanion/mute/dungeon1/tun5.c","west");
   add_cmd_item("stone", "lift", "@@lift_centerstone");
   add_cmd_item("shaft", "enter", "@@enter_shaft");
   p_centerstone = 0;
   called = MAX_NO_SERV;
}

void
do_add_exits()
{
   seteuid(getuid());
   TO->add_exit("/d/Rhovanion/mute/dungeon1/spilair1.c", "shaft", 0);
   TO->add_my_desc("The center stone has been moved aside and a dark " +
      "shaft leading down can be seen where it once was.\n");
}

void
do_remove_exits()
{
   seteuid(getuid());
   TO->remove_exit("shaft");
   TO->remove_my_desc();
}

int
lift_centerstone()
   {
   if (p_centerstone) 
      {
      say(QCTNAME(TP) + " lifts the center stone with an undignified grunt " +
         "and sets it back into place...\n" +
         "The center stone sinks slowly back into the hole with a low " +
         "grating noise.\n");
      write("You lift the heavy stone and set it back into place...\n" +
         "The center stone sinks slowly back into the hole with a low grating " +
         "noise.\n");
      do_remove_exits();
      p_centerstone = 0;
      return 1;
   }
   say(QCTNAME(TP) + " lifts the center stone with a grating sound and sets " +
      "it off to the side.\n" +
      "Here the center stone once was is now a dark shaft.\n");
   write("You lift the heavy stone and set it aside...\n" +
      "Where the center stone once was is now a dark shaft.\n");
   do_add_exits();
   p_centerstone = 1;
   return 1;
}

enter_shaft()
{
   TP->move_living("into the shaft", "/d/Rhovanion/mute/dungeon1/spilair1.c");
   return 1;
}
