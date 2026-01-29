// file name: dlord.c
// creator(s): Farlong
// last update: 25 June 94 by Tepisch
//              Ilyian (8 March, 1995)
// purpose:
// note: removed the possibility of entering the fountain until
//       something can be done with it.
// bug(s):
// to-do:

inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>

#include "park.h"

private static object guardian;

public void
create_room(void)
{
    set_short("By a fountain");
    set_long(
      "A strange quiet hangs here like the hand of death. The room"
      +" is empty, save for the large and intricate fountain which"
      +" dominates its center. Sculpted from marble,"
      +" it consists of a broad, heavy base, surrounded by a"
      +" shallow pool. Atop the base is a menacing figure wielding a"
      +" trident. Jets of water"
      +" spray up behind the figure and fall into the pool below.\n");

    add_exit(PK+"slope","up",0);

    add_prop(ROOM_I_LIGHT,0);
    IN_IN

    add_item(({"plants","plant","life"}),"This room is totally"
      +" devoid of the vines, brush, and other growth that chokes"
      +" the rest of the island.\n");
    add_item(({"fountain","base","pool"}),"The "
      +"entire fountain seems to be carved from a single slab "
      +"of pale white marble. It is somewhat dirty from the "
      +"dust that settles and get wet. A large statue rises "
      +"up from the center of the fountain.\n");
    add_item(({"trident","figure"}),"The figure is one of a titanic "
      +"elf carved of ebony. It has its head thrown back to the "
      +"sky and holds a gigantic trident over its head, seemingly "
      +"howling in victory.\n");
    add_item(({"jets","water","spray"}),"The jets of frothy water"
      +" circulate through the fountain over and over"
      +" again.\n");

    reset_room();
}

public void
reset_room(void)
{
    if (!guardian)
    {
	guardian = clone_object(PK + "mon/guardian");
	guardian->equip_me();
	guardian->move_living("M", this_object());
    }
}

public int
fountain(string str)
{
    if ((str == "fountain") || (str == "pool"))
    {
	if (present("W_am_guard"))
	{
	    write("The Guardian stops you from"
	      +" entering the fountain.\n");
	    say(QCTNAME(this_player())+ " tries to enter"
	      +" the fountain, but is stopped"
	      +" by the twisted creature.\n");
	}
	else
	{
	    tell_room(PK + "fountain",
		QCTNAME(this_player()) +" steps into the fountain.\n");
	    write("You step into shallow"+
		" pool at the base of the fountain.\n");
	    say(QCTNAME(this_player())+ " steps into"+
		" the pool of water at the base of the fountain.\n");
	    this_player()->move_living("M", PK + "fountain");
	}
	return 1;
    }

    return notify_fail("Enter what?\n");
}

public void
init(void)
{
    ::init();
    add_action( fountain, "enter" );
}
