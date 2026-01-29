#pragma save_binary

inherit "/std/room";
inherit "/lib/store_support";

void create_room()
{
       set_short("Store room");
	set_long("Store room.\n");
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}