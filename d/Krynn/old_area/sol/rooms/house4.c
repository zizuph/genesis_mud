/*
* A normal house in Solace
*
* By Rastlin
* Descrips and add_items by Teth
*/

#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit  SOLINROOM;

object gDoor;

public void
create_solace_room()
{
   seteuid(getuid());
   
   set_short("A house full of antiques");
   set_long("@@my_desc@@");
   
   add_item("bed", "Although you'd expect most of the beds in this " +
      "village to be humble or practical, this one is an exception. It " +
      "is a work of art. The elegantly sculpted headboard and tailboard " +
      "are perfectly matched with the laced bedsheets and pillow " +
      "covers.\n");
   
   add_item(({"headboard", "tailboard"}), "Both the headboard and " +
      "tailboard are made of some light-coloured fine grained wood, " +
      "perhaps birch from some far off forest. They feature swirling " +
      "scrolls and carved flowers.\n");
   
   add_item(({"bedsheets", "sheets", "bedsheet"}), "One touch of " +
      "the bedsheets is enough to make you exclaim in wonder, as you " +
      "realize such a weave has not been seen to commoner's eyes since " +
      "the Cataclysm.\n");
   
   add_item(({"pillow covers", "pillow cover"}), "These enclose the " +
      "pillows, but are special in and of themselves, as they are " +
      "embroidered in a fine lace.\n");
   
   add_item(({"pillow", "pillows"}), "Nestled comfortably in the " +
      "pillow cases, these sluggish headrests look like they will do " +
      "no harm.\n");
   
   add_item("dresser", "Constructed of a dark walnut, this treasure " +
      "is certainly worth a small fortune. Perhaps the drawers hide " +
      "something of a similar value?\n");
   
   add_item(({"drawer", "drawers"}), "Gently shuffling your way " +
      "through the drawers, you disturb tidy piles of clothes that look " +
      "outrageous by today's fashion standards. You find nothing of note, " +
      "however.\n");
   
   add_item("kitchen", "It is difficult to spot any antique items in " +
      "the kitchen, as not much has changed in hundreds of years in " +
      "terms of cooking utensils. Boiling water is still done in a pot. " +
      "The stove looks fairly old, though.\n");
   
   add_item(({"stove", "wood stove"}), "A sturdy stove, it looks a " +
      "lot like a squat bulldog. It seems to do its job quite well, " +
      "despite its age. A small engraved metal plate is riveted to it.\n");
   
   add_item(({"metal plate", "plate"}), "The metal plate reads, " +
      "'Forged in the mountains near Thorba.di., in t.. y..r of 1...'. " +
      "Sadly, parts of the plate are scratched or scraped off.\n");
   
   add_item("rack", "This cloak rack stands on a cross-like base, " +
      "the distal portions of the base ending in carved griffin claws " +
      "that enclose a crystal or glass ball. The trunk of the rack " +
      "stands straight and true, perhaps made of ash or pine. The hooks " +
      "that hold cloaks are made of an untarnished brass, but are simple " +
      "in design.\n");
   
   add_item(({"rug", "ornamental rug"}), "Finely woven, this faded " +
      "carpet could perhaps be one of the final works of some long " +
      "forgotten civilization.\n");
   
   gDoor = clone_object(OBJ + "d_house4");
   gDoor->move(TO);
}

public string
my_desc()
{
   string str;
   
   str = "You are standing in what appears to be a normal house at " +
   "first glance. However, poking around a bit more reveals that " +
   "almost every item in the room is an antique. The one exception to " +
   "this is the ";
   
   if (gDoor->query_open())
      str += "open";
   else
      str += "closed";
   
   str += " brown door that is set in the south wall. Standing in the " +
   "center of the room, you note that the bed and dresser are to the " +
   "north end of the house, while the kitchen and wood stove occupy " +
   "the east. In the west portion of the house stands a rack for " +
   "hanging cloaks. Beneath your feet is an ornamental rug.\n";
   
   return str;
}

