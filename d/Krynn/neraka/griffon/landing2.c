/* Original by Percy
* New easier to handle Version of the dragon, by Aridor. */
/* Converted to GRIFFON by Macker (for icewall quest) */
/* random stuff in random room mod's by Stevenson */

#include "/d/Krynn/common/defs.h"
#include "local.h"
#include "/d/Krynn/common/random_meet.h"
#include <ss_types.h>
#include <macros.h>

inherit TANTALLON_OUTSIDE;

object griffon, ob;

void reset_tantallon_room()
{

}

void create_tantallon_room()
{
   set_short("Griffon's Nest");
   set_long("This is a flat spot on a small hill near the mountains. On the ground you see " +
      "claw marks and strange feathers.\n");

   add_exit(TDIR + "city3", "south", "@@slip");

   add_item("rock","There are a few rocks on the ground.\n");
   add_item(({"nest", "bird nest", "feathers", "feather", "griffon nest"}), "@@nest");
   add_item(({"marks", "claw marks"}), "There are large claw marks in the rock.\n");
   add_item("path", "It leads to a house. Why don't you follow it?\n");
   add_item("house", "It is hard to make it out clearly from this distance. Why don't you go take a closer look?.\n");
   add_cmd_item(({"feather","feathers"}), ({"get","take","pick"}),
      "You cannot do that because the feathers are frozen to the ground.\n");
   add_item("ground","It is very frozen.\n");

   (DRAGON_ROOM)->load_me();
   add_prop(ROOM_I_NO_CLEANUP, 1);
   add_prop(OBJ_S_WIZINFO, BS(
         "Don't update this room or the dragon unnecessary since it can mess " +
         "things up.", 70));

   reset_tantallon_room();
}

int
slip()
{
   write("You carefully go down the hill, being carefull not to "
      + "slip on the ice.\n");
   return(0);
}


void init()
{
   ::init();
   ADA("whistle");
}



/* Handles summoning the griffon */
   int whistle(string str)
{
   NF("Whistle for who?\n");
   if (str == "for griffon")
      {
      write("You whistle with all your force. ");
      say(QCTNAME(TP) + " whistles a shrill sound.\n");
      seteuid(getuid(TO));
      if ((DRAGON_ROOM)->call_dragon(4))
         write("You feel that the griffon has heard you. He ought to be here soon.\n");
      else
         write(BS("You wait a while and decide the griffon is not coming. He is probably just busy at the moment, but griffons move quickly. Why don't you just try again in a bit?", 70));
      return 1;
   }
   return 0;
}



/* add_item descriptions. */
string nest()
{
   if(griffon)
      write("You have trouble looking at anything other than the griffon, because it is staring directly at you.\n");
   else
      write(BS("Judging from the size of the nest and feathers, you decide this place is probably home to a rather large griffon.", 70));
   return "";
}

