#pragma save_binary

/*
**This room is used for the vouching of new members in the Tricksters.
**The vouching system was taken from the Heralds
**of the Valar found in /d/Shire/heralds/board.c
*/


inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "trickster.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <std.h>

int
glance(string str)
{
    if ((!str) && (str != "big book") && (str != "book"))
    {
	TP->catch_msg("Glance at what?\n");
	return 1;
    }

    if (!(IS_MEMBER(TP)))
    {
	TP->catch_msg("Hey!!!  Your not a Trickster!!  How'd you get in " +
	  "here anways?\n");
	return 1;
    }

    seteuid(getuid());
    if (TP->query_wiz_level())
	TP->more(MEMBER_TRACKER->query_members(1));
    else
	TP->more(MEMBER_TRACKER->query_members(0));
    return 1;
}

void
create_room()
{
    set_short("A crude hallway");
    set_long("A crude hallway has been dug here.  It's much drier and " +
      "more livable than some of the other rooms around here.  You notice " +
      "a sign pointing east in the middle of the room as well there are " +
      "rows of torches which line this hallway providing some warmth. " +
      "In the corner of the room there is a small wooden desk and " +
      "a big book which lies upon it. " +
      "This hallway breaks off to the east and continues to the south.\n");

    add_cmd_item("sign", "read", "Alchemist shop:  Enter at your own risk!\n");

    add_item(({"book", "big book"}),
      "This book is bound in dafed leather, within it is a "+
      "listing of all the members within the Tricksters.  "+
      "You may wish to take a glance at the book to see "+
      "the names of your fellow Tricksters.\n");
    add_item(({"desk","wooden desk", "small desk", "small wooden desk"}),
      "The desk is made of some rotting wood, obivously someone scavanged " +
      "this from a junk pile somewhere.  You wonder how much longer " +
      "the desk will hold up, under the wieght of the big book, which " +
      "sits upon it.\n");
    add_item("sign", "Ummm maybe you should try reading it?\n");
    add_item(({"torches","torch","light","lights"}),
      "These torches burn brightly in the room providing light.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(TRICK_DIR + "alchemy_shop","east","@@shop_open@@",1);
    add_exit(TRICK_DIR + "back_way","south",0,1);
    add_exit(TRICK_DIR + "train","northwest",0,1);

}

void
init()
{
    ::init();
    add_action("glance","glance");
}

int
shop_open()
{
    int   closed;

    closed = 0;  /* Set to 1 if you wish to close the alchemy_shop */
    if(closed)
    {
	write("I'm sorry but the Alchemist Shop is currently closed. "+
	  "Perhaps try here later?\n");
	return 1;
    }
    return 0;
}
