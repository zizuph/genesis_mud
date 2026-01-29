#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>

inherit ASHLAR_OUT;

object dwarf = 0;

void
reset_ashlar_room()
{
	if (!dwarf)
    {
    	dwarf = clone_object(ANPC + "dwarf");
        if (dwarf)
        {
        	if(!dwarf->move_living("M",TO,1))
                tell_room(TO,"A wrinkled dwarf wanders in.\n",dwarf);
        }
    }
    return;
}

create_ashlar_room()
{
    set_short("moor, by a stone circle");
   
    set_long("@@long_descr");

    add_item(({"moor","ground"}),
        "The ground is soft and your feet sink down with every step.\n");

    add_item(({"stone","stones","stone circle","circle","monoliths"}),
        "The huge monoliths are smooth, but there are some remnants " +
        "of an ancient inscription on them. Weather and wind has " +
        "eradicated any hope of deciphering them however.\n");
        
    reset_ashlar_room();
}

string
long_descr()
{
    return tod_descr1() + tod_descr2() + 
        "You stand on a moor, where a large stone circle has been " +
        "erected. The huge monoliths are worn smooth by weather and " +
        "wind, yet there is still some traces of inscriptions on them. " +
        season_descr() + "\n";
}

/*
 * A little emote that lets people dance in the stone circle 
 */
int
do_dance(string str)
{
	NF("What?\n");
    if (!str || ((str != "in circle") && (str != "in stone circle")))
        return 0;

    write("As you dance around in the stone circle, you feel some " +
        "ancient power stirring in you.\n");
    tell_room(TO,QCTNAME(TP) + " dances a merry dance in the stone circle.\n",
        TP);

    return 1;
}

void
init()
{
	::init();
	ADD(do_dance,"dance");
}


