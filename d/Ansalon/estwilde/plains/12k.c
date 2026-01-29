#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

inherit PLAINS_OUT;

#define HARD_TO_CLIMB 20

void
reset_estwilde_room()
{
    return;
}

int
climb_inside()
{
    if(this_player()->query_skill(SS_CLIMB) < HARD_TO_CLIMB)
    {
	write("You don't think you are skilled enough to try " +
	  "and climb inside the chasm.\n");
	say(QCTNAME(this_player()) + 
          " attempts to climb inside the chasm but fails.\n");
	return 1;
    }

    write("You climb inside the chasm by way of the chimney, "+
         "entering an opening in the sheer stone wall far below.\n");
    say(QCTNAME(TP)+ 
       " disappears from sight within a chimney in the chasm wall.\n");

    TP->move_living("M",IRON + "brewery_tunnel",1,0);
    tell_room(IRON + "brewery_tunnel",QCNAME(TP) + 
      " arrives climbing inside " +
      "from the chasm outside.\n", TP);
    return 1;
}

create_estwilde_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_exit(ROOM + "bridge1","northwest",0);
    add_exit(ROOM + "12l","east",0);
    add_exit(ROOM + "11l","northeast",0);
    add_item_chasm();

    add_item(({"chasm","chasm fissures","fissures"}),
      "From the lip of the chasm, a number of fissures "+
      "have formed in the sheer rock wall. One of them "+
      "appears as a chimney, perhaps scalable by the bold.\n");

    add_item(({"chimney"}),"The chimney offers the means to climb inside "+
      "the chasm; providing access to an opening in the sheer stone wall.\n");

    add_item(({"bridge","wooden bridge"}),
      "To the northwest an ancient-looking wooden bridge " +
      "hangs down between the two sides of the chasm. It creaks " +
      "ominously as it sways with the wind that blows through " +
      "the chasm.\n");

    add_cmd_item(({"in","inside"}),"climb","@@climb_inside");

    reset_estwilde_room();
}

string
short_descr()
{
    return tod_descr1() + " before a bridge over a great chasm";
}

string
long_descr()
{
    return plain_desc()+
    "To your northwest a great chasm opens up before you. " +
    "An ancient-looking wooden bridge starts here, " +
    "crossing over the chasm. Far below, fissures line the "+
    "chasm wall.\n";
}
