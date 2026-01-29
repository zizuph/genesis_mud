/*
 * /d/Gondor/clubs/storytellers/rooms/.c
 */
inherit "/d/Gondor/std/room";
#include "/d/Gondor/defs.h"
#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>

string read_sign();
int check_exit();

object door;

void
create_gondor()
{
    set_short("a small hallway on the second floor");
    set_long("The small hallway leads ends to the north in a " +
        "stairwell. Beyond a doorway to the south is a sitting" +
        "room with a rocking chair in clear view. Next to a " +
        "door in the east wall here hangs a sign. To the west, " +
        "there is a short door that is open on the top half, " +
        "with an attendant on the other side\n");
    add_item(({"chair", "rocking chair"}),
        "It looks like a nice and sturdy rocking chair.\n");
    add_item(({"wall", "walls", "stone", "smooth stone", "white stone",
        "smooth white stone"}),
        "The walls are made of white stone and smooth to the touch.\n");
    add_item(({"doorway", "sittingroom", "sitting room"}),
        "It is arched with smooth white stones. Beyond it is another " +
        "sittingroom.\n");
    add_item("sign", &read_sign());
    add_cmd_item("sign", "read", &read_sign());
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_exit(STORYT_DIR + "rooms/sittingroom2", "south", 0, 0);
    add_exit(STORYT_DIR + "rooms/2ndfloor", "north", 0, 0);
    add_exit(STORYT_DIR + "rooms/bathhall", "west", check_exit, 0);
    (door = clone_object(STORYT_DIR + "obj/2f_door_out"))->move(TO);
}

public nomask string
read_sign()
{
    write(read_file(STORYT_DIR + "misc/sign3.txt"));
    return "";
}

int
check_exit()
{
    object leader, *team;
    int i, size;

    if (IS_STORYTELLER(this_player()))
    {
        write("The attendant recognizes you as a storyteller, and "+
            "allows you to pass.\n");
        return 0;
    }

    if (!objectp(leader = this_player()->query_leader()))
        team = this_player()->query_team();
    else
        team = leader->query_team() + ({ leader });

    for (i = 0, size = sizeof(team); i < size; i++)
        if (IS_STORYTELLER(team[i]))
        {
            write("The attendant sees that you are with "+
                team[i]->query_the_name(this_player())+", and allows "+
                "you to pass.\n");
            return 0;
        }

    write("The attendant tells you that you may only enter in the "+
        "company of a storyteller.\n");
    return 1;
}
