#include "defs.h";

inherit LAKESHORE_ROOM;

int music;

void
create_telberin_room()
{
    set_short("By the lakeshore");
    set_em_long("You are in front of a large glass domed building. " +
		"@@query_music@@" + "Snow capped peaks far in the " +
		"distance compliment the clear blue waters " +
		"of lake beautifully. There seems to be some " +
		"kind of a gathering to the northwest.\n");
    add_item(({"lake", "waters", "water"}),
	     "The lake water is crystal pure.\n");
    add_item(({"path", "cobblestone", "cobblestone path"}),
	     "The cobblestone path is nearly spotless. " +
	     "The Telberin elves must really pride themselves " +
	     "in cleanliness.\n");
    add_item(({"peak", "peaks"}),
	     "The majestic white peaks seem to rise out of the water " +
	     "on the far end of the lake.\n");
    add_exit("beach10", "west");
    add_exit("beach08", "east");
    add_exit("opera_house", "south");
    add_exit("tel10_01", "north");
}

string
query_music()
{
    if (music)
      {
	return "The sound of beautiful music flows through here from the " +
	  "building to the south.\n";
      }
    else
      {
	return "It seems kind of silent here.\n";
      }
}


