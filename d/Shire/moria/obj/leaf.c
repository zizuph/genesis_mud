#include "defs.h"
#include <stdproperties.h>

inherit "/std/object";

int charges;

create_object()
{
    set_short("golden whorled leaf");
    set_pshort("golden whorled leaves");
    set_name("leaf");
    set_pname("leaves");
    add_adj(({"golden", "whorled"}));
    set_long("You are looking at a golden whorled leaf, sparkling "+
	     "in the light! This is a leaf from the sacred forest "+
	     "of Lorien, where the Elven Lady Galadriel lives.\n");
    add_prop(MAGIC_AM_MAGIC,
	     ({ 30, "abjuration", 40, "spells" }));
    add_prop(MAGIC_AM_ID_INFO,
	     ({ "It seems to contain magical powers.\n", 1,
		"It is enchanted to cast spells.\n", 23,
		"The spell is of abjuration.\n", 42,
		"In fact, it is a dispelling spell!!\n", 50,
		"You have to swirl the golden leaf encircling an object "+
		    "to cast the inbedded spell.\n", 75 }));
    add_prop(OBJ_I_WEIGHT, 2);
    add_prop(OBJ_I_VALUE, 200);
    charges = 5 + random(3);
}

init()
{
    ::init();
    add_action("do_swirl", "swirl");
    add_action("do_swirl", "wreathe");
    add_action("do_swirl", "encircle");
}

int
do_swirl(string arg)
{
    string verb;
    object with, obj;

    verb = query_verb();
    
    if (!parse_command(arg, ETP, "[the] %o 'around' / 'aloft' / 'encircling' / 'crowning' [the] %o",
		       with, obj))
	return notify_fail(CAP(verb) + " <what> crowning <what>?\n");

    if (with != TO)
	return 0;
    
    if (charges <= 0)
	return notify_fail("The golden leaf seems not to work.\n");

    if (ENV(with) != TP)
	return notify_fail("You must hold it to use it.\n");

    write("You start to swirl the golden leaf of Lorien crowning the " +
	  obj->short() + "!\n");
    say(QCTNAME(TP) + " starts to swirl " + HIS_HER(TP) + " golden leaf " +
	"of Lorien crowning the " + QSHORT(obj) + ".\n", TP);
    
    charges --;
    obj->dispel_magic(30+random(70));
    if (charges == 0)
	call_out("crumble", 2, TP);
    return 1;
}

crumble(object tp)
{
    tell_room(ENV(tp),
	      "The golden leaf of Lorien crumbles into dust.\n");
    call_out("remove_object", 0);
}


