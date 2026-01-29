// kirk priory (office/storage)
inherit "/d/Khalakhor/std/room";
#include "defs.h"
#include <macros.h>
object   prior;
 
public void reset_room()
{
   if (prior) return;
   seteuid(getuid());
   prior=clone_object(SEAN_RHIAN+"npc/briareus");
   prior->equip_me();
   prior->move(TO);
   tell_room(TO,QCNAME(prior)+" enters from the courtyard.\n");
}
 
public void create_khalakhor_room()
{
   set_short("kirk Priory");
   set_long(
      "This is the priory of the village kirk, which serves as both "+
      "an office and a sacristy or storage room. There is a small "+
      "desk and chair in front of a hearth along the west wall, "+
      "while along the remaining walls stand shelves and cabinets "+
      "holding books, vestments, equipment and supplies.\n");
 
   add_item(({"kirk","priory","room","sacristy"}),
      "The priory is constructed like all the other buildings of "+
      "the village, a one-level wood plank building painted in "+
      "pastel blue. The walls are framed and crossed by large "+
      "beams of dark color.\n");
   add_item(({"desk","chair"}),
      "It is a inornate but highly polished desk and chair, standing "+
      "near the hearth for warmth.\n");
   add_item("hearth",
      "It is a small clay brick hearth used to heat the priory and "+
      "possibly for cooking, though you see no utensils.\n");
   add_item(({"shelves","shelf","books","scrolls"}),
      "There are a few wooden shelves of polished wood standing "+
      "along the walls. They are filled with dozens of books "+
      "and scrolls, though you see none with titles you can "+
      "read.\n");
   add_item(({"cabinets","cabinet","vestments","equipment","supplies"}),
      "The cabinets are made of polished wood with locked glass "+
      "doors. They hold various vestments and equipment used "+
      "by the manachs who live here.\n");
   add_exit("courtk","east");
   reset_room();
}
