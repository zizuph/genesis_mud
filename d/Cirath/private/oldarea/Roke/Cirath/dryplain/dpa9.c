inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

void create_room()
{
	set_short("Dark room");
	set_long(break_string("You are in a dump and dark room with no abvious exits. "+
	"You wonder: why on earth did I press that button, now I have to quit. "+
	"Or shall you try to solve this? Well problems are created to be solved "+
	"Maybe you can find your way out if you use your imagination, if you have any. "+
	"At least you feel quite sure there are no mosters around. "+
        "Maybe you shall try to be religous if you haven't been that before.                  "+
	"There are no obvious exits. \n",70));
	set_noshow_obvious(1);
	add_prop(ROOM_I_LIGHT, -1);
	add_prop(ROOM_I_INSIDE, 1);
}
init()
{
    ::init();
    add_action("pray","pray");
}

int
pray(string str)
{
    mixed words;

    if (!strlen(str)) return 0;
    if (str != "to god")
	if (member_array("pray",explode(str," ")) == -1)
	    return 0;
	else
	{
	    notify_fail("Pray to whom?\n");
	    return 0;
	}
    write("You start to pray to God\n \n \n");
    TP->move_living("in a divine flash north",DRYPLAIN+"dpac1",1);
    tell_room(QCTNAME(TP)+ " mumbles a prayer and disappears.\n");
    return 1;
}