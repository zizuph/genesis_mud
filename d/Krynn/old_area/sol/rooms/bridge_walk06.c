/*
* The village Solace
*
* By Rastlin
*/
#include "local.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>

inherit SOLOUTROOM;

object gDoor;

RESETROOM

create_solace_room()
{
   seteuid(getuid());
   
   set_place(BRIDGEWALK);
   
   set_long_desc("@@my_desc@@");
   
   add_exit(TDIR + "bridge_walk05", "northeast");
   add_exit(TDIR + "platform1", "southeast");
   add_exit(TDIR + "platform5", "northwest");
   
   add_item("park", "The park below you contains gazebos, benches, " +
      "and picnic tables. You'd need to go down among the bases of the " +
      "Vallenwoods to inspect the items more closely.\n");
   
   gDoor = clone_object(OBJ + "d_bridge_walk06");
   gDoor->move(TO);
   
   reset_solace_room();
}

public string
my_desc()
{
   string str, people;
   
   str = "Located in this mighty vallenwood tree is a small house " +
   "with a ";
   
   if (gDoor->query_open())
      str += "open";
   else
      str += "closed";
   
   str += " green door. The owner has a perfect view " +
   "of the beautiful park down below you. The limbs of " +
   "the mighty trees intertwine above you, providing a " +
   "protective canopy from the harsh outside world. Down below " +
   "you, you can see the Solace park";
   
   if (people = get_living(({TDIR + "park2"})))
   str += ", presently visited by " + people;
   
   str += ".";
   
   return str;
}





