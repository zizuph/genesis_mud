inherit "/std/room";
inherit "/lib/guild_library";

void create_room()
{
    set_short("Library");
    set_long("This is a guild library. Read the plaque for instructions.\n");

    set_library_save_path("/doc/examples/guild_library/simple/books");
    set_library_allow_new_books(1);

    create_library();

    add_item(({"plaque", "instructions", }), library_help);
    add_cmd_item(({"plaque", "instructions", }), "read", library_help);
}

void init()
{
    ::init();
    init_library();
}

void leave_inv(object ob, object to)
{
    library_leave_inv(ob, to);
    ::leave_inv(ob, to);
}