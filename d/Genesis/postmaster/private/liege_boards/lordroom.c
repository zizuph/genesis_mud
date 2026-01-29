inherit "/std/room";

#include <std.h>
#include <stdproperties.h>

void load_board();

void
create_room()
{
    set_short("The House of Lords\n");
    set_long("You are in the great House of Lords. There is nothing but " +
	     "a big board in this room. Maybe it was created this way to " +
	     "keep the discussions nice and tidy...\n");

    load_board();
}

void
enter_inv(object ob,object from)
{
    ::enter_inv(ob,from);

    if (!objectp(ob) ||
	!living(ob) ||
	(SECURITY->query_wiz_rank(geteuid(ob)) >= WIZ_LORD))
    {
        return;
    }

    ob->catch_msg("\nOnly Lords, Ladies, and Arches are welcome here !\n\n");

    seteuid(getuid());

    if (objectp(from) &&
	from->query_prop(ROOM_I_IS))
        ob->move(from);
    else
        ob->move(ob->query_def_start());

    return;
}

void
load_board()
{
    object bboard;
    string name;

    if (present("board",this_object()))
        return;

    seteuid(getuid());
    bboard = clone_object("/d/Genesis/postmaster/private/liege_boards/lboard");

    name = "/d/Genesis/postmaster/private/liege_boards/lboard";
    if (file_size(name) != -2)
        mkdir(name);

    bboard->set_board_name(name);
    bboard->set_num_notes(50);
    bboard->set_silent(1);	
    bboard->set_show_lvl(1);
    bboard->set_remove_rank(WIZ_LORD);
    bboard->set_remove_str("Sorry, but you cant do that !");
    bboard->move(this_object(), 1);
}

