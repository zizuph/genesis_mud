inherit "/std/room";
inherit "/d/Genesis/lib/post";

#include <stdproperties.h>
#include <std.h>
#include <macros.h>

void
create_room()
{
    set_short("Confinement area");
    set_long("A plain, white room with padded walls.  All you " +
        "can do here is send and receive mail.\n");

    add_item(({ "walls", "padded walls" }),
        "The walls are padded to prevent those confined here from " +
        "causing themselves bodily harm.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_TELEPORT, 1);
}

int
confine(string str)
{
    object player;
    string name = this_interactive()->query_real_name();

    if (this_player() != this_interactive())
    {
        return 0;
    }

    if ((SECURITY->query_wiz_rank(name) < WIZ_ARCH) &&
        (member_array(name, SECURITY->query_team_list("aop")) < 0))
    {
        notify_fail("You do not have permission to use this command.\n");
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Confine whom?\n");
        return 0;
    }

    if (!(player = find_player(str)))
    {
        if (!SECURITY->exist_player(str))
	{
            write("No such player.\n");
	}
        else
	{
            write("Cannot confine a player who is not logged in.\n");
        }

        return 1;
    }

    player->set_default_start_location(MASTER);
    player->move_living("X", this_object(), 1);
    write("Ok.\n");
    return 1;
}

void
init()
{
    ::init();
    post_init();

    add_action(confine, "confine");
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    post_leave_inv(ob, to);
}
