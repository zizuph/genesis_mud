inherit "/std/room";

#include <macros.h>
#include <filter_funs.h>
#include <composite.h>
#include "chapel.h"
#include <stdproperties.h>

/* Variables */
int repeater_alarm;
int count = 0;

void
create_room()
{
   set_short("Wedding gazebo");
   set_long("   You are in an outside chapel, a big bright room. "+
      "It is built of thin wooden slats, latticed on two sides. "+
      "At the front of the room, the wall is solidly enclosed. Against "+
      "this wall you see a large stone podium. The soothing sounds of " +
      "nature surround you in this gazebo, creating an air of calmness all " +
      "around you. Sunlight streams in through the lattice, "+
      "illuminating the room beautifully.\n\n");
   
   add_item(({ "stone podium", "podium" }),
      "This podium is constructed from a very large stone. It has "+
      "been chiseled and cut into it's current shape. The stone "+
      "has been polished until it gleams like cut glass.\n");

   add_item(({"lattice","lattices"}),"The white wooden slats "+
      "form a grid pattern as they climb up the walls. In and "+
      "around the slats you can see greenery growing.\n"+
      "@@view_garden@@\n");
   add_item("floor","The floor of the gazebo is a highly "+
      "polished stone, with a small rug near the front of the room up "+
      "around the podium.\n");
   add_item("rug","This is a round piece of carpet for the bride and groom to stand on.\n");
   add_item(({"rafter","rafters"}),"The rafters above your head are the supports for the roof of the gazebo. Far above you there is a small nest.\n");
   add_item("nest","High up on the rafters you see a small bird nest.\n");
   add_item("bird","This is a common bluebird.\n");
   
   add_prop(ROOM_I_INSIDE, 1);
   add_exit("outside_chapel", "out");
   
}

void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
   if (!count)
      {
      repeater_alarm=set_alarm(15.0,15.0+itof(random(30)),"make_noise");
   }
   count++;
}

void
leave_inv(object ob, object to)
{
   ::leave_inv(ob, to);
   count--;
   if (!count) remove_alarm(repeater_alarm);
}

int
is_chapel()
{
   return 1;
}


/*
* MAKE_NOISE
* Coded by Xarguul for Melita
* to add more noises, add to the # in the random field
* and insert a new string in the switch statement.
*/
void
make_noise()
{
   int seed = random(5);
   string str;
   
   switch (seed)
   {
      case 0 : str = "The sound of wind gently brushing against the "+
      "flowers in the garden fills the gazebo.\n";
      break;
      case 1 : str = "A gentle breeze blows through the gazebo, "+
      "bringing with it the sweet scent of flowers "+
      "from the garden.\n";
      break;
      case 2 : str = "The sounds of birds chirping echos through the "+
      "area.\n";
      break;
      case 3 : str = "A bird flutters through the gazebo and lands "+
      "in the rafters above, perching on its nest.\n";
      break;
      case 4 : str = "The sound of children laughing and playing in "+
      "the garden drifts through the gazebo.\n";
      break;
   } /* END SWITCH */
   
   tell_room(this_object(),str);
   
} /* END MAKE_NOISE */

string
view_garden()
{
   object *people;
   
   if (!LOAD_ERR("/d/Emerald/melita/chapel/outside_chapel"))
      people = 
   FILTER_LIVE(all_inventory(find_object("/d/Emerald/melita/chapel/outside_chapel")));
   
   if (!sizeof(people))
      return "The garden appears empty.\n";
   else
      return "Out in the garden, you can see "+COMPOSITE_LIVE(people)+".";
}

