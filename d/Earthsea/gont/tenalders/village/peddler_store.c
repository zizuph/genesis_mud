#pragma save_binary
#pragma strict_types

inherit "/std/room";
inherit "/lib/store_support";

public void
create_room()
{
    set_short("The shop's store room");
    set_long("This is the store room for the shop.\n");
    reset_room();
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}
