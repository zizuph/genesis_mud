/* 
Citadel, private chambre.
Made by Korat 
Feb 14. 1995 
*/

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

void
create_room()
{
   ::create_room();
   add_prop(ROOM_I_INSIDE,1);
   add_prop(ROOM_M_NO_TELEPORT, 1);
   hear_bell = 2;
   set_short("Citadel, private chamber");
   set_long("You see a single, small desk here in this room "+
      "and next to it a large bed covered with feather pillows. "+
      "The walls are decorated with a few "+
      "paintings that matches the brownish paneling on the walls. "+
      "Either the decorator or the person living here has a taste for "+
      "simplicity, because the room is rather empty.\n");
   
   add_item(({"painting","paintings"}),"They portray a few scenarios "+
      "of people, nature and a battle-scene here and there.\n");
   add_item("table","The desk is of polished redwood, giving it a burgunder "+
      "colour that matches the panelings on the walls. On it you see a "+
      "leatherbound book.\n");
   add_item("book","When you look at it closer, you notice that this closed "+
      "book has several runes engraved on it. You feel that it would be unwise "+
      "to touch it...but where that feeling comes from is beyond you.\n");
   add_item(({"panel","paneling"}),"The paneling must be of oak, and has "+
      "been lighly torched to give the wood a darker brownish touch in its "+
      "colour. Together with the desk it manages to dampen the lights from "+
      "the candles, giving a relaxed atmosphere in the room.\n");
   add_item("bed","It is a large bed that looks pretty comfy.\n");
   add_item(({"pillow","pillows"}),"Ohhh, they look soft!\n");
   add_exit(CENTRAL(citadel/cit20),"northeast",0,-1,-1);
}

init()
{
   ::init();
   add_action("touch","touch");
}

touch(string str)
{
   notify_fail("Touch what?\n");
   if (!str || str != "book") return 0;
   TP->catch_msg("You touch the leatherbound book with your fingertips.\n");
   say(QCTNAME(TP)+" touches the leatherboud book with the "+
      "fingertips.\n");
   TP->catch_msg("A stream of energy pours into you! You feel "+
      "your lifeforce being slowly drained.\n");
   say(QCTNAME(TP)+" visibly pales and withdraws the hand fast!\n");
   TP->catch_msg("You withdraw you hand fast!\n");
   TP->set_hp(TP->query_hp()-300);
   if (TP->query_hp()<=0) TP->do_die(TO);
   return 1;
}
