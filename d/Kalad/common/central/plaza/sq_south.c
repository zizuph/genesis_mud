/*
ROOM: South corner of Town Square
BY:   Sebster
DATE: Aug 27, 1994
*/

inherit "/d/Kalad/room_std";

#include "/d/Kalad/defs.h"
object dog;

void
create_room()
{
   ::create_room();
   hear_bell = 3;
   
   set_short("The south corner of Town Square");
   set_long(
      "This is the south corner of Town Square. To the north you "+
      "see the massive city monument, and to the south you see two "+
      "buildings. A post office lies to the southwest, with a pigeon "+
      "house, and to the southeast you see the office of the "+
      "famous Sage, Hernan. The High Street "+
      "goes south towards the city walls in the distance. Once in a "+
      "while, "
   );
   
   set_time_desc(
      "a hopeful adventurer strolls into the Sage, Hernans office.\n",
      "a disappointed adventurer lurks out from the Sage, Hernan's office.\n");
   
   add_exit(CENTRAL(plaza/sq_mon), "north", 0);
   add_exit(CENTRAL(plaza/sq_st_se), "east");
   add_exit(CENTRAL(plaza/post_office),"southwest",0,-1,-1);
   add_exit(CENTRAL(plaza/sq_sage),"southeast",0,-1,-1);
   add_exit(CENTRAL(plaza/sq_st_sw), "west", 0, 2);
   add_exit(CENTRAL(plaza/sq_east), "northeast", 0);
   add_exit(CENTRAL(plaza/sq_west), "northwest", 0);
   add_exit(CENTRAL(high-circle-south), "south", 0);
   
   add_item(({"post office","postoffice"}),
      "A small wooden house. You notice some pigeons "+
      "flying up from the back of the house.\n"
   );
   
   add_item(({"pigeon","pigeons"}),
      "These must be carrying letters and messages. You can probably "+
      "buy one for yourself inside that house.\n"
   );
   add_item(({"sage","sages office","office"}),
      "This is the house of the wildly famous Hernan; a Sage that "+
      "has the reputation of knowing everything, but also of being "+
      "in dire need of help to do the High Lord's bidding. Hernan "+
      "is employed by the High Lord to take care of most administrative "+
      "jobs that needs to be done. Therebye, the sage was given an "+
      "office on the plaza itself!\n");
   add_item(({"house","houses"}),
      "You see two buildings here. A post office to the southwest and an "+
      "office to the southeast.\n"
   );
   add_item(({"city walls","walls"}),
      "The city walls are too far south to reveal any details. Go down "+
      "the High Street to get a closer look.\n");
   set_alarm(1.0,0.0,"reset_room");
}

reset_room()
{
   if(!objectp(dog))
      {
      dog = clone_object("/d/Kalad/common/central/npc/dog");
      dog -> move_living("M",TO);
      tell_room(E(TO),"A ragged dog comes lurking out from the shadows.\n");
   }
}
