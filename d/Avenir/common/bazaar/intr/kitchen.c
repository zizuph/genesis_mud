 // Kitchen        (/d/Avenir/common/bazaar/intr/kitchen.c)
 //                Now attached to the /d/Avenir/common/port/pub.c
 // creator(s):    Glinda, may 95
 // last update:   Lilith, June 2004
 //                Getting ready to add parts of the village
 //                and don't want to have start areas in the 
 //                bazaar anymore, since the village is where
 //                people live.
 // purpose:       The kitchen of the pub/inn.
 // note:
 // bug(s):
 // to-do:


inherit "/std/room.c";

#include "/d/Avenir/common/bazaar/bazaar.h"
#include <cmdparse.h>

object cook;


int vegetables, eels;

void
create_room()
{
    set_short("The kitchen of the Stormy Haven");
    set_long("For a kitchen at a port, this one looks pretty standard. "+
        "Along the west wall a heavy wooden working bench stands, while "+
        "the stove is placed at the north wall. On the floor under the "+
        "bench are a few buckets.\n");
	
	IN;       // Avenir is an undergound domain.
	IN_IN;    // Interior room, no flux msgs, steeds etc.

   AI(({"bench"}),"A heavily scarred wooden bench.\n");
   AI(({"wall","walls","east wall","west wall","north wall","south wall"}),
        "The walls are dark and sooty.\n");
   AI(({"floor"}),
        "The floor is smooth and kept swept fairly clean.\n");
   AI(({"stove","pots","pans"}),
        "A few pots and pans are set on the stove. Something smells good.\n");
   AI(({"bucket","buckets"}),"@@bucket_desc");
   add_cmd_item(({"eel","fish"}),({"get","take","pick"}),
        ({"get","take","pick"}));
    AI(({"eel","fish"}),
        "One of the buckets contain a living eel, and another " +
        "some live fish.\n");
   add_exit(BAZAAR + "intr/inn", "south", 0, 1);
   reset();

}

string
bucket_desc()
{
   string str;
   if(vegetables)
      str="There is one with vegetables, and one with some live fish, " +
          "and even one that contains a living eel.\n";
   else
      str="There is one with some live fish, and one which contain " +
          "a living eel. The rest of them are empty.\n";
   return str;
}

cmditem_action(string str)
{
   object veggie, eel;
   int i;
      if(!str)
      return 0;
   sscanf(str,"%s\n",str);
   if(parse_command(str,(({})),"'fish'"))
   {
      write("You try to get the fish from the bucket, but it " +
            "slips away from your grip.\n");
      say(QCTNAME(TP) + " rumbles about in the buckets.\n");
      return 1;
   }

   if(parse_command(str,(({})),
       "[the] / [an] 'eel' / 'eels' [from] [the] [bucket]"))
   {
      if(!eels)
         return 0;
     
      if (eels > 0)
      {
         eels--;
         eel=clone_object(NPC + "eel");
         write("You manage to get a good hold on a slippery eel and "+
             "lift it out of the bucket.\n");
         say(QCTNAME(TP) + " gets something from a bucket.\n");
         eel->move(TP);
         return 1;
      }
      eels=0;
      write("You try to get the eel from the bucket, but it " +
            "slips away from your grip.\n");
      say(QCTNAME(TP) + " splashes about in a bucket.\n");
      return 1;
   }

   if(parse_command(str,(({})),
       "[the] / [a] 'vegetable' / 'vegetables' [from] [the] [bucket]"))
   {
      if(!vegetables)
         return 0;
     
      if (vegetables > 0)
      {
         vegetables--;
         veggie=clone_object(FOOD + "vegetable");
         veggie->move(TP);
         write("You get some vegetables from one of the buckets.\n");
         say(QCTNAME(TP) + " gets something from a bucket.\n");
         return 1;
      }

      remove_cmd_item("vegetables");
      remove_item("vegetables");
      write("You sift through the bucket but there isn't anything "+
          "worth taking.\n");
      vegetables=0;
      return 1;
   }
   NF("Get what?\n");
   return 0;
}


void
reset_room()
{
   vegetables= random(7) +4;
   eels = random(5) + 3;

   remove_cmd_item("vegetables");
   add_cmd_item(({"vegetables"}),({"get","take","pick"}), ({"get","take","pick"}));

   remove_item("vegetables");
   AI(({"vegetables"}),
        "One of the buckets contain some vegetables.\n");
   if(!cook)
   {
      cook=clone_object(BAZAAR +"NPCS/cook");
      cook->arm_me();
      cook->move(TO);
   }
}
