// kirk abbey (temp start loc here)
inherit "/d/Khalakhor/std/room";
#include "defs.h"
#include <macros.h>
 
public void create_khalakhor_room()
{
   set_short("village kirk abbey");
   set_long(
      "This is the abbey of the village kirk where the manachs eat, "+
      "sleep and just generally live. There is a large hearth along "+
      "the eastern wall in front of which stands a long table with "+
      "six chairs around it. There are four small beds placed along "+
      "the southern end of the room, while a large more comfortable "+
      "bed with a small stand next to it is placed along the northern "+
      "wall. There is a large cabinet next to the hearth, while a "+
      "tall wardrobe stands next to the entrance.\n");
 
   add_item(({"table","chairs"}),
      "It is a rather long wooden table which comfortably sits six "+
      "for a meal. Ten simple but comfortable wooden chairs are "+
      "pushed neatly beneath it.\n");
   add_item("beds",
      "There are four small wood frame beds with straw mattresses "+
      "covered with wool blankets sitting along the south wall. "+
      "They don't seem like they'd be fit for a clan chief, but "+
      "they look sufficient.\n");
   add_item(({"large bed","north bed","bed"}),
      "The bed along the north wall is large with a soft down-filled "+
      "mattress and several wool blankets. Its frame is made of "+
      "polished wood with four high posts. It must be for someone "+
      "important or perhaps a visitor.\n");
   add_item("stand",
      "It is a small stand of polished wood next to the large bed to the "+
      "north. There is a card with some writing on it.\n");
   add_item("card",
      "It is a small paper card with elegant writing on it placed "+
      "on the stand next to the bed to the north. Perhaps you can "+
      "read it.\n");
   add_cmd_item("card","read",
      "+------------------------------+\n"+
      "| Guests are welcomed to spend |\n"+
      "|      the night with us.      |\n"+
      "|                              |\n"+
      "|  See the prior for details.  |\n"+
      "|           ........           |\n"+
      "|           ........           |\n"+
      "+------------------------------+\n"+
      "You see there is fine print which you can read on it.\n");
   add_cmd_item(({"fine print","instructions"}), "read",
      "To stay the night, ask the prior 'to stay the night'. There will "+
      "be a donation of 6 silver required. Then return here and do "+
      "'start here'. The next time you login, you will start here "+
      "instead of your normal home. This is one time only, as you must "+
      "see the prior again each time you wish to stay.\n");
   add_item("cabinet",
      "It is a large wooden cabinet standing next to the hearth. "+
      "It contains dishes and various other items for daily living.\n");
   add_item("wardrobe",
      "The tall wardrobe next to the entrance is made of dark polished "+
      "wood and probably holds the daily clothing of the manachs who "+
      "live here.\n");
   add_item(({"kirk","priory","room","abbey"}),
      "The small abbey is constructed like all the other buildings of "+
      "the village, a one-level wood plank building painted in "+
      "pastel blue. The walls are framed and crossed by large "+
      "beams of dark color.\n");
   add_item("hearth",
      "It is a large clay brick hearth used to heat the abbey and "+
      "for cooking. There are utensils hanging from its mantle.\n");
   add_item(({"pots","pans","utensils","mantle"}),
      "It is just a wooden beam over the mouth of the hearth, "+
      "from which hang pots, pans and other cooking utensils.\n");
   add_cmd_item("here","start","@@start_here");
 
   add_exit("courtk","west");
   reset_room();
}
 
string start_here()
{
   if (TP->query_prop(ROOM_RENTED))
      if (TP->set_temp_start_location(ROOM+"kabbey"))
         return "When you rise from slumber next, it shall be here.\n";
      else
         {
         TP->add_prop(ROOM_RENTED,2); // 2=refundable
         return "There seems to be a problem...please ask the prior "+
                "for a refund.\n";
         }
   else
      return "You must ask the prior to stay the night first.\n";
}
