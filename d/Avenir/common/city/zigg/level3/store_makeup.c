// Ziggurat Makeup Storeroom (ZIG_RL3 + "store_makeup.c")
// creator(s):   Zielia 2006
// last update:
// purpose:
// note:
// bug(s):
// to-do:
#pragma strict_types

#include "zigg.h"
inherit "/d/Avenir/inherit/storage";

#define NUM_POMADE	2

private void
make_pomades(void)
{
    string *tints;
    object ob = (ZIG_OBJ + "pomade")->get_this_object();

    tints = ob->query_tints();

    foreach(string tint : tints)
    {
	int num = NUM_POMADE;

	while(num--)
	{
	    ob = clone_object(ZIG_OBJ + "pomade");
	    ob->set_tint(tint);
	    ob->move(TO);
	}
    }
}

/*
 * Restore pomade supply.
 */
public void
leave_inv(object ob, object to)
{
    ::enter_inv(ob, to);

    if (ob->id("pomade"))
    {
	string tint = ob->query_tint();

	ob = clone_object(ZIG_OBJ + "pomade");
	ob->set_tint(tint);
	ob->move(TO);
    }
}

public void
create_room(void)
{
    set_shop_room(ZIG_RL3 + "makeup");

    set_short("The makeup shop's store room");
    set_long("This is the store room for the makeup shop.\n");

    add_exit("makeup", "out");

    add_prop(ROOM_I_INSIDE, 1);

    set_alarm(0.2, 0.0, &make_pomades());

    set_default_stock(
      ({
	ZIG_OBJ + "mascara", 4,
	ZIG_OBJ + "brush", 4,
	ZIG_OBJ + "soap", 5,
	ZIG_OBJ + "glotion", 5,
	//       ZIG_OBJ + "pomade", 18,
      }) );

    max_items = 50;
    set_max_identical(3);

    enable_reset(200);
    reset_store();
}

