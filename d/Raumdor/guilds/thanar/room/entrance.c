/**********************************************************************
 * - entrance.c                                                     - *
 * - The entrance room to the Temple of Thanar                      - *
 * - Created by Damaris@Genesis 3/2004                              - *
 **********************************************************************/

#pragma strict_types

#include "/d/Raumdor/defs.h"
#include "../guild.h"

#define NAGAROTH_EXIT "/d/Raumdor/cities/nagaroth/room/gar0603"

inherit GUILD_ROOM;

public int
block_exit()
{
    write("You may not go this way, at this time.\n");
    return 1;
}

public int
members_only()
{
    if ((TP->query_race() == "human" &&
         member_array(TP->query_race_name(), VALID_SUBRACES) >= 0) ||
         this_player()->query_wiz_level())
    {
	/* Is an acceptable race, pass through as normal */

	return 0;
    }

    write("A magical force prevents you from entering.\n");
    return 1;
}

object book;
void
create_guild_room()
{

    set_short("Oval Temple Entrance");
    set_long("    This is a grand oval entrance hall to the grand temple "+
      "of Thanar. The hall is quite large and filled with "+
      "unbelievable wealth and finery. There are unique oil "+
      "paintings that fill the oval walls and in the center of "+
      "the room is a large foreboding statue. A golden plaque "+
      "has been placed at the foot of the statue.\n");
    add_item(({"room", "area", "entrance", "hall", "oval hall"}), query_long);
    add_item(({"painting", "paintings"}),
      "There are beautiful paintings that line the oval walls here. "+
      "There are a total of six paintings and you should be able "+
      "to look a bit closer at each one.\n");
    add_item(({"first painting", "painting one"}),
      "The painting is quite exquisite and it tells a story of "+
      "ages old. The simple brush strokes along the canvas bring "+
      "out the scene in this painting to display such truth of "+
      "history. The scene depicted is of a small male human child "+
      "being tortured by demihumans.\n");
    add_item(({"second painting", "painting two"}),
      "The painting is quite exquisite and it tells a story of "+
      "ages old. The simple brush strokes along the canvas bring "+
      "out the scene in this painting to display such truth of "+
      "history. The scene depicted is of a young male human "+
      "standing at large well while being shunned by demihumans.\n");
    add_item(({"third painting", "painting three"}),
      "The painting is quite exquisite and it tells a story of "+
      "ages old. The simple brush strokes along the canvas bring "+
      "out the scene in this painting to display such truth "+
      "of history. The scene depicted is of a young male human "+
      "standing in a city square being tortured by demihumans.\n");
    add_item(({"fourth painting", "painting four"}),
      "The painting is quite exquisite and it tells a story "+
      "of ages old. The simple brush strokes along the canvas "+
      "bring out the scene in this painting to display such "+
      "truth of history. The scene depicted is of a young male "+
      "human standing in a city square with a mass of black "+
      "snakes surrounding him protecting him from demihumans.\n");
    add_item(({"fifth painting", "painting five"}),
      "The painting is quite exquisite and it tells a story of "+
      "ages old. The simple brush strokes along the canvas "+
      "bring out the scene in this painting to display such "+
      "truth of history. The scene depicted is of a young male "+
      "human kneeling before an apparition of the great god Thanar.\n");
    add_item(({"sixth painting", "painting six"}),
      "The painting is quite exquisite and it tells a story of "+
      "ages old. The simple brush strokes along the canvas bring "+
      "out the scene in this painting to display such truth of "+
      "history. The scene depicted is of the great god Thanar "+
      "lifting up humanity while scattered below are demihumans "+
      "who now serve humans.\n");
    add_item(({"statue"}),
      "The statue is made from obsidian and it is the figure "+
      "of a noble human carrying a scroll in his hand and a "+
      "snake in the other. At the foot of the statue is a golden "+
      "plaque, which you may read.\n");
    add_item(({"scroll"}),
      "The scroll is part of the statue and is unreadable.\n");
    add_item(({"plaque","gold plaque", "golden plaque"}),
      "Welcome to the Temple of Thanar.\n\n"+
      "We are pleased that you have found your way here.\n"+
      "If you are human you may enter our grand temple\n"+
      "and learn more about the Great Thanar and our cause.\n\n"+
      "Chosen Minister of Thanar\n");
    add_cmd_item("plaque", "read","Welcome to the Temple of Thanar.\n\n"+
      "We are pleased that you have found your way here.\n"+
      "If you are human you may enter our grand temple\n"+
      "and learn more about the Great Thanar and our cause.\n\n"+
      "Chosen Minister of Thanar\n");
    clone_object(GUILD_DIR + "book")->move(this_object());
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);

    add_exit("join", "north", members_only);
    // add_exit(NAGAROTH_EXIT, "south", members_only);
    add_exit("/d/Kalad/common/guilds/new_thanar/rooms/upper_mid5", "portal");

}
