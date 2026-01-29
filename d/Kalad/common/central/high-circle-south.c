/* 
 * /d/Kalad/common/central/high-circle-south.c
 * Purpose    : Road connection between high and circlestreet
 * Located    : /d/Kalad/common/central/
 * Created By : Korat 1995
 * Modified By: 
 *   Fysix, 2-3-1998, fixed npc clone bug.
 */ 

/* High street, north of plaza. */

inherit "/d/Kalad/room_std";  
#include "/d/Kalad/defs.h"  

object ob1;

/* made by Korat */ 

reset_room()
{
   if(!objectp(ob1))
      {
      ob1 = clone_object("/d/Kalad/common/central/npc/patrol_watchman");
      ob1->move_living("xxx",TO);
   }
}

void
create_room()
{
   ::create_room();
   hear_bell = 3;
   set_short("High Street");
   set_long("You are walking along the High Street, trying to avoid all the "+
      "small water pulps scattered around on the bricked road. You notice "+
      "that this crossroad also leads to the Circle street that circle the "+
      "grand plaza with its huge statue. Northwards you can see that "+
      "statue rising high among several buildings.\n"+
      "     To your south you can see the city walls and some kind of "+
      "a mechanism of sorts. ");
   
   set_time_desc("You notice some pigeons that fly out from a "+
      "building to the northwest.\n","\n");
   
   add_exit(CENTRAL(high/s4), "south", 0);
   add_exit(CENTRAL(plaza/sq_south), "north", 0);
   add_exit(CENTRAL(circle/s9), "west", 0, 1);
   add_exit(CENTRAL(circle/s8), "east", 0, 2);
   
   add_item(({"pulps","pulp"}), 
      "Just small, wet pulps. Better try to avoid stepping into them!\n");
   add_item("statue", 
      "A large state indeed. It has to be since you can "+
      "see it from this distance.\n");
   add_item("plaza",
      "The plaza lies north of you as an island surrounded with buildings, "+
      "just like all plaza's do.\n");
   add_item("walls","Its the city's walls against the cliffside.\n");
   add_item("mechanism","Its too far to see what it is.\n");

   reset_room();
}

patrol_text(string str)
{
   if (!str) return;
   if(objectp(ob1)) ob1->new_event(str);
}
