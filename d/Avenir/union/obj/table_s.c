// file name:	/d/Avenir/union/obj/table_s.c
// creator(s): 	Cirion
// last update:	Lilith ??? ??, Unknown
// 	Lucius Nov 08, Added 'serve' command and support + cleanups.
// purpose:	Table for the salon / lounge.
#pragma strict_types
#include "../defs.h"

inherit "/std/container";

#include <files.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <stdproperties.h>


private object
clone_heap(string id, int num, string file)
{
    int size;
    object obj = present(id);

    if (!objectp(obj))
    {
	obj = clone_object(file);
	obj->move(TO, 1);
    }

    if (obj->num_heap() < num)
	obj->set_heap_size(num);

    return obj;
}

public void
reset_container(void)
{
    object obj = present("_crucible_component");
    int num = random(4) + 3, size = obj->num_heap();

    clone_heap("_crucible_component", num, OBJ + "glass_of_water");
    clone_heap("hkahve", num, BAZAAR + "museum/obj/coffee");
    clone_heap("ikahve", num, CITY + "obj/food/iced_coffee");
    clone_heap("morsel", 12, OBJ + "morsel");

    if (!present("knife"))
	clone_object(OBJ + "knife")->move(TO, 1);

    if (!present("cheese"))
	clone_object(OBJ + "c_round")->move(TO, 1);
}

public void
create_container(void)
{
    if (!IS_CLONE)
	return;

    reset_euid();

    set_name("table");
    add_name("salon:table", 1);
    set_adj(({"low","round"}));
    set_short("marble-topped table");
    set_long("This table was made by adding a slab of marble atop "+
      "a wide basalt column. It is the perfect surface from which "+
      "to \"serve\" others or even yourself. ");

    add_prop(CONT_I_MAX_WEIGHT, 50000);
    add_prop(CONT_I_MAX_VOLUME, 50000);
    add_prop(CONT_I_WEIGHT, 500);
    add_prop(CONT_I_VOLUME, 500);
    add_prop(OBJ_I_VALUE, 500);
    add_prop(CONT_I_ATTACH, 1);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET, "It cannot be moved.\n");

    // Don't want it to show up in room desc.
    set_no_show_composite(1);
}

public int
food_drink(object item)
{
    if (IS_FOOD_OBJECT(item))
	return 1;

    if (IS_DRINK_OBJECT(item))
	return 1;

    return 0;
}

public int
do_serve(string str)
{
    if (!strlen(str))
	return NF("Serve what?\n");

    object *iarr, *larr, *oarr = all_inventory();

    if (!sizeof(oarr))
	return NF("There is nothing on the table to serve!\n");

    if (!parse_command(str, oarr, "%i 'to' [the] %s", iarr, str))
	return NF("Serve what to whom?\n");

    iarr = NORMAL_ACCESS(iarr, "food_drink", this_object());

    if (!sizeof(iarr))
    {
	write("What are you trying to serve?\n");
	return 1;
    }

    oarr = FILTER_OTHER_LIVE(all_inventory(environment()));

    if (!strlen(str) || !sizeof(oarr) ||
	!parse_command(str, oarr, "%l", larr) ||
	!sizeof(larr = NORMAL_ACCESS(larr, 0, 0)))
    {
	write("Whom are you trying to serve?\n");
	return 1;
    }

    if (sizeof(larr) != 1)
    {
	write("You may only serve one individual at a time.\n");
	return 1;
    }

    oarr = filter(iarr, &->move(larr[0]));

    if (sizeof(iarr -= oarr))
    {
	if (sizeof(iarr) > 1 || iarr[0]->num_heap() > 1)
	    str = "them";
	else
	    str = "it";

	write("You pick up "+ COMPOSITE_DEAD(iarr) +" from the "+
	    short() +" and serve "+ str +" to "+
	    larr[0]->query_the_name(TP) +".\n");
	larr[0]->catch_msg(QCTNAME(TP) +" picks up "+ QCOMPDEAD +
	    " from the "+ short() +" and serves "+ str +" to you.\n");
	say(QCTNAME(TP) +" picks up "+ QCOMPDEAD +" from the "+
	    short() +" and serves "+ str +" to "+ QTNAME(larr[0]) +
	    ".\n", ({ this_player(), larr[0] }));
    }

    if (sizeof(oarr))
    {
	write("You were unable to serve "+ COMPOSITE_DEAD(oarr) +
	    " to "+ larr[0]->query_the_name(TP) +".\n");
    }

    return 1;
}

public void
init(void)
{
    ::init();
    add_action(do_serve, "serve");
}
