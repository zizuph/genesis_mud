inherit "/std/room";
inherit "/d/Gondor/std/library/library";

public void
create_room()
{
    set_short("gwyneth's library");
    set_long("It's Gwyneth's library.\n");

    set_lib_id("gwyneth_lib_id");
    set_lib_path("/d/Gondor/std/library/tmp");
    set_default_topics((["General" : 0, "Maps" : 0]));
    set_lib_type(2);
    set_search_delay(1.0);
    set_max_librarian_num(1);
    setup_library();
}

public void
init()
{
    ::init();
    init_library();
}

public void
leave_inv(object player, object dest)
{
    library_leave_inv(player, dest);
    ::leave_inv(player, dest);

}

