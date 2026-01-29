/*
* A normal house in Solace
*
* By Rastlin
* room descrip changed by Teth
*/

#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit  SOLINROOM;

object gDoor, gLadder;

reset_solace_room()
{
   if (!gLadder)
      {
      gLadder = clone_object(OBJ + "ladder");
      gLadder->move(TO);
   } 
   else 
      if (!present("ladder", TO))
      gLadder->owner_arrives();
}

public void
create_solace_room()
{
   seteuid(getuid());
   
   set_short("Inside a tidy well-kept house in Solace");
   set_long("@@my_desc@@");
   
   add_item("rug", "@@my_rug@@");
   
   add_item("wood", "Since the citizens of Solace would never use the " +
      "timber of their beloved Vallenwoods, you suspect this wood is an " +
      "import, perhaps silver maple from the forests near Lemish.\n");
   
   add_item(({"case", "display case"}), "This wooden display case is " +
      "spartan in design. It seems the intents of the well-locked case are " +
      "to show off the delicate figurines inside it and to draw no " +
      "attention to itself.\n");
   
   add_item(({"figurine", "wooden figurine"}), "No one figurine " +
      "captures your attention, instead you find your eyes flit from " +
      "one to another.\n");
   
   add_item(({"figurines", "wooden figurines"}), "The hand-carved " +
      "wooden figurines are delicate and fine-featured - the work of a " +
      "true master wood carver. Animals both known and fantastic come " +
      "to life in the soft basswood artform. Each statuette is " +
      "initialled at the base.\n");
   
   add_item(({"initial", "initials"}), "Straining your eyes to make " +
      "out the details in the poor light, you manage to see the " +
      "letters 'F.F.' shallowly engraved in each figurine.\n");
   
   add_item("kitchen", "A typical kitchen, not much draws your " +
      "interest, except for the stove.\n");
   
   add_item(({"wood stove", "stove"}), "The wood stove is enamelled " +
      "black. One large pipe leads from the back end of the stove to " +
      "the east wall of the dwelling, where it exits outside through " +
      "a hole cut in the wall. You wonder if people who live in trees " +
      "should use wood stoves.\n");
   
   add_item("dresser", "This dresser contains the clothes of the " +
      "house's owners, you guess. It has several drawers.\n");
   
   add_item("drawers", "Snooping through the drawers, you find " +
      "nothing that suits your style or your waist size.\n");
   
   add_item("bed", "The bed looks extremely comfortable. It looks " +
      "like it was recently made, as no wrinkles are present in " +
      "the top blanket. The pillows appear to have served their owner " +
      "well over the years.\n");
   
   add_item("blanket", "This well-knit blanket looks warm. " +
      "Embroidered into the blanket is a picture of what appears " +
      "to be a unicorn. The owner is a believer in a fairy tales, " +
      "it seems.\n");
   
   add_item(({"pillow", "pillows"}), "Each pillow is fluffed up, " +
      "which seems to be a routine they've been subjected to for " +
      "years.\n");
   
   gDoor = clone_object(OBJ + "d_house1");
   gDoor->move(TO);
   
   reset_solace_room();
}

public string
my_desc()
{
   string str;
   
   str = "You have entered the house of one of the local citizens. " +
   "This dwelling is both well-furnished and tidy, obviously the home " +
   "of someone who has little to worry about material needs. The " +
   "solid wooden door, set in the west wall, is ";
   
   if (gDoor->query_open())
      str += "open";
   else
      str += "closed";
   
   str +=". Its wood captures your attention. A display case lies " +
   "against the north wall. The kitchen, complete with wood stove, " +
   "is opposite the door. The bed and a dresser occupy the southern " +
   "portions of the room, while a rug hugs the floor.\n";
   
   return str;
}

public string
my_rug()
{
   string str;
   
   str = "This rug is in extremely fine condition. However";
   
   if (gLadder && P(gLadder,TO))
      str += ", for some reason, a useful-looking ladder rests on it.\n";
   else
      str += ", you notice that a fine lattice of pebbles dirties it. " +
   "The lattice almost seems to be in the pattern of a ladder. Odd.\n";
   
   return str;
}




