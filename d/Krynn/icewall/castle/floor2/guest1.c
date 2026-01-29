/* Created by Macker 11/2/94 */
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"

inherit ICEINROOM;

object bozak, baaz, kapak;

void
reset_icewall_room()
{
   if(!bozak)
      {
      bozak = clone_object(SPLAINS_L + "bozak.c");
      bozak->set_color("white");
      bozak->move(TO);
   }
   if(!kapak)
      {
      kapak = clone_object(SPLAINS_L + "kapak.c");
      kapak->set_color("white");
      kapak->move(TO);
   }
   if(!baaz)
      {
      baaz = clone_object(SPLAINS_L + "baaz.c");
      baaz->set_color("white");
      baaz->move(TO);
   }
   return;
}

void create_icewall_room() {
   set_short("Guest Room");
   set_long("This room is clean and nicely furnished. " +
      "It appears to be a guest room, " +
      "@@my_long@@" + "\n");
   add_item("bed", "The bed is unmade and lacks the fine layer of " +
      "dust which seems to cover everything else in " +
      "this place.\n");
   add_exit(ICE_CAST2_R+"hall6_2","east");
   
   reset_icewall_room();
}

string
my_long()
{
   if((bozak)||(kapak)||(baaz))
      return(" and it looks like the current guests " +
      "are draconians!");
   else
      return(" but you see no guests. There is a bed " +
      "here, though, which looks like it may have " +
      "been slept in recently.\n");
}

