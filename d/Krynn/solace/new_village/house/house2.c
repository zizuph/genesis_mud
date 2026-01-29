/*
* A normal house in Solace
*
* By Rastlin
* Room descrip changed by Teth
*/

#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit  SOLINROOM;

object gDoor;

public void
create_solace_room()
{
   seteuid(getuid());
   
   set_short("A filthy house in Solace");
   set_long("@@my_desc@@");
   
   add_item(({"heaps", "heap", "clothes", "dirty clothes"}), "These " +
      "clothes look like they have been resting here for weeks. You " +
      "must be quite brave, looking at underwear that is ten times " +
      "dirtier than yours have ever been.\n");
   
   add_item(({"dishes", "dirty dishes"}), "They are quite dirty " +
      "indeed. If you were a mycologist, you'd have quite the heyday " +
      "identifying all the fungi and moulds. As it is, they don't look " +
      "too interesting. And they smell bad.\n");
   
   add_item("dresser", "This dresser has various drawers open, some " +
      "with items of apparel, some without.\n");
   
   add_item(({"drawers", "drawer"}), "Found in these drawers, oddly " +
      "enough, are clothes just as dirty as the ones that make the floor " +
      "their home.\n");
   
   add_item("bed", "The bed has to be the most disgusting item in the " +
      "entire house. Bedbugs, lice, and mites of all kinds call this bed " +
      "'paradise'. It would be a bad idea to sleep in this bed, and " +
      "it would be a worse idea to examine the sheets, for fear of " +
      "diseases sometimes carried by these creepy-crawlies.\n");
   
   add_item(({"sheet", "sheets"}), "Not one to listen to your better " +
      "instincts, you investigate the sheets. All you find is more " +
      "arthropods.\n");
   
   add_item(({"bedbugs", "lice", "mites", "arthropods"}), "You " +
      "suspect that this bed competes with tropical rainforests in " +
      "terms of sheer diversity of buggies.\n");
   
   add_item("kitchen", "This kitchen has not been cleaned in years. " +
      "You wonder if some of the grease and grime was around when the " +
      "Cataclysm struck.\n");
   
   add_item(({"wood stove", "stove"}), "This stove has seen better " +
      "days. While studying it, you hear a sound from somewhere in the " +
      "pipe. Looks like a raccoon or a magpie has found a new home.\n");
   
   add_item("rug", "This tattered piece of fabric may have at one " +
      "time been a family heirloom. Now, it is home to a medley of " +
      "stains, one large one in particular.\n");
   
   add_item(({"stain", "stains", "huge stain"}), "Smack dab in the " +
      "middle of the rug is a hideous stain, the largest of all the " +
      "ones present. Using fine deductive techniques, you surmise that " +
      "it consists of a combination of beer and Otik's Spiced " +
      "Potatoes, from the Inn of the Last Home.\n");
   
   gDoor = clone_object(OBJ + "d_house2");
   gDoor->move(TO);
}

public string
my_desc()
{
   string str;
   
   str = "This house you are standing is best described with one " +
   "word - filthy. The only route of escape from this mess is by " +
   "leaving through the door set in the west wall, which is currently ";
   
   if (gDoor->query_open())
      str += "open";
   else
      str += "closed";
   
   str += ". Scattered throughout the room are heaps of clothes and " +
   "dirty dishes. A half-opened dresser and an unmade bed occupy the " +
   "north end of the room, while a run-down wood stove and dirty " +
   "kitchen face them from the opposite side of the room. On the " +
   "tattered rug in the middle of the room is a huge stain.\n";
   
   return str;
   
}

