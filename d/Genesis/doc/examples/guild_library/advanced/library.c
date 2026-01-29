inherit "/std/room";
inherit "/lib/guild_library";

void create_room()
{
    set_short("Library");
    set_long("This is a guild library. Read the plaque for instructions.\n");

    set_library_save_path("/doc/examples/guild_library/advanced/books");
    set_library_allow_new_books(1);

    set_library_book_type("scroll");
    set_library_book_object("/doc/examples/guild_library/advanced/library_scroll");

    add_library_access_level("normal", "Everyone");
    add_library_access_level("restricted", "Card owners");
    add_library_access_level("owner", "Owners");
    
    set_library_librarian_level("owner");

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

int query_librarian(object player)
{
    if(player->query_wiz_level() || present("_library_owner_card", player))
        return 1;

    return 0;
}

string *query_player_access(object player)
{
    if (present("_library_owner_card", player) || player->query_wiz_level()) {
        return ({ "normal", "restricted", "owner" });
    }

    if (present("_library_card", player)) {
        return ({ "normal", "restricted" });
    }

    return ({ "normal" });
}