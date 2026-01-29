// Ziggurat Fetish Storeroom (ZIG_RL3 + "store_fetish.c")
// creator(s):   Zielia 2006
// last update:
// purpose:
// note:
// bug(s):
// to-do:
#pragma strict_types

#include "zigg.h"
inherit "/d/Avenir/inherit/storage";

#define NUM_CORSET	3

private static object *corsets = allocate(NUM_CORSET);

public void
hook_reset_store(void)
{
    /* Corsets need special handling. */
    for(int i = 0; i < NUM_CORSET; i++)
    {
	object ob;

	if (objectp(corsets[i]))
	{
	    if (present(corsets[i]))
		continue;
	}

	ob = clone_object(ZIG_OBJ + "corset");
	ob->make_random();
	ob->make_desc();
	ob->move(TO);

	corsets[i] = ob;
    }
}

public void
create_room(void)
{
    set_shop_room(ZIG_RL3 + "fetish");

    set_short("The fetish shop's store room");
    set_long("This is the store room for the fetish shop.\n");

    add_exit("fetish", "out");

    add_prop(ROOM_I_INSIDE, 1);

    set_default_stock(
      ({
	ZIG_OBJ + "cage", 1,
	ZIG_OBJ + "whip", 4,
	ZIG_OBJ + "rods", 4,
	ZIG_OBJ + "paddle", 4,
	ZIG_OBJ + "feather", 5,
	ZIG_OBJ + "blindfold", 4,
	ZIG_OBJ + "th_boots", 4,
	ZIG_OBJ + "zig_harness", 4,
	ZIG_OBJ + "lskirt", 3,
      }) );

    set_max_items(50);
    set_max_identical(5);

    enable_reset(200);
    reset_room();
}

