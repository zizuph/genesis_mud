inherit "/std/room";
inherit "/lib/store_support";

#include "/d/Emerald/defs.h"

int flag;

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
/*
    if (from && ob->id("torch")) {
      set_alarm(1.0, 0.0, &remove_torch(ob));
    }
    else
*/
	store_update(ob);
}

void
remove_torch(object ob)
{
    if (!ob || !present(ob))
	return;
    flag = 1;
    ob->remove_object();
    flag = 0;
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    if (to && !flag && ob->id("torch"))
	if (ob->short() == "small torch")
	    clone_object(VILLAGE_DIR + "obj/smalltorch")->move(this_object());
}

void
create_room()
{
    set_short("Shop storeroom");
    set_long("You are in a rather large storeroom.  To the "+
	     "west you can make out the innards of a shop.\n");

    add_exit(VILLAGE_DIR + "shop", "west", 0);
    add_prop(ROOM_I_INSIDE, 1);

    set_max_values(30, 3);

    clone_object(VILLAGE_DIR + "/obj/smalltorch")->move(this_object());
    clone_object(VILLAGE_DIR + "/obj/smalltorch")->move(this_object());
    clone_object(VILLAGE_DIR + "/obj/smalltorch")->move(this_object());
}
