#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;

int key_here;
create_icewall_room()
{

   object door;

   set_short("Doorway To Master Bedroom");
   set_long(
      "You stand at the north end of the hallway. To the west the "
      + "hallway continues, and to the east is a set of doors "
      + "leading to what you assume is the master bedroom. Just in "
      + "front of the doors you notice a rug. Going south will "
      + "return you to the stairs. "
      + "\n");

   add_item("rug","@@rug_lump");
   add_item("lump","@@lump");

   add_exit(ICE_CAST2_R + "master.c", "east");
   add_exit(ICE_CAST2_R + "hall5_2.c", "west");
   add_exit(ICE_CAST2_R + "hall2_2.c", "south");

   door = clone_object(ICE_CAST_O + "masddoor.c");
   door->move(TO);
   door->set_key(MASKEY);

   reset_icewall_room();
}

reset_icewall_room() {key_here = 1;}

init() {
   ADA("search");
   ADD("get_key", "get");
   ADD("get_key", "take");
   ADD("get_key", "move");
   ADD("get_key", "lift");
   ::init();
}

string rug_lump() {
   string rug = "It is blue, green, and red.  The threads are "
   + "exposed, and you see dirt caked into it. ";
   if (key_here) rug = rug + "You notice a small lump in the "
      + "center of the rug. ";
   return rug + "\n";
}

string lump() {
   if (key_here) return "It doesn't look normal.\n";
   return "What lump?\n";
}

search(string str) {
   if ((str == "rug" || str == "lump") && key_here) {
      key_here=0;
      seteuid(getuid());
      clone_object(ICE_CAST_O + "masterkey")->move(TP);
      write("You search the rug and find a key.\n");
      say(QCTNAME(TP) + " finds a key.\n");
      return 1;
   }
   return 0;
}

get_key(string str)
{
	NF(query_verb() + " what?\n");
	if(!(key_here))
		return 0;
	if(!((str == "rug")||(str == "key from rug")||(str == ""+
		"key from under rug")||(str == "key from under rug" +
		"")||(str == "key from the rug")||(str == "key from " +
		"under the rug")))
		return 0;
	else
	{
		TP->catch_msg("You lift the rug up and discover a key " +
		"hidden under it.\nYou quickly pick up the key and " +
		"replace the rug.\n");
		tell_room(TO, QCTNAME(TP) + " bends down and gets a key " +
		"from under the rug.\n", ({TP}));
		key_here = 0;
		clone_object(ICE_CAST_O + "masterkey")->move(TP);
		return 1;
	}
}

