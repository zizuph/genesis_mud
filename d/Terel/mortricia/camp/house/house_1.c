/* A haunted room. Mortricia 920927 */
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#include "/d/Terel/common/terel_defs.h"

#define TP              this_player()
#define TO              this_object()

#define CAMP_DIR        MORTRICIADIR + "camp/"
#define HAUN_DIR        CAMP_DIR + "house/"

object guard;

public void
reset_room()
{
    if (!guard) {
        guard = clone_object(CAMP_DIR + "guard");
        guard->move(TO);
    }
}

public void
create_room()
{
    set_short("Entrance");
    set_long(
        "You are in the entrance of the strange tent. " +
        "The canvas is painted in many colours. " +
        "You can leave the tent by going north. The western " +
        "exit is simply an opening in the canvas. " +
        "There is also a ladder that goes downwards through " +
        "a hole in the ground. " +
        "An iron sign.\n"
    );
    
    add_item(({"canvas"}),
        "The canvas reflects the light in many colours. " +
        "Drawings of ghostly creatures have been made on it " +
        "as well. You have never before seen such creatures.\n"
    );
    add_item(({"exit", "exits"}),
        "Which exit do you mean? The western, northern, or the " +
        "hole?\n"
    );
    add_item(({"northern exit"}),
        "Through the northern exit you see the camp.\n"
    );
    add_item(({"western exit"}),
        "The western exit is simply an opening in the canvas. " +
        "You can't see (or even imagine) what is behind it.\n"
    );
    add_item(({"hole", "ladder"}),
        "There is a wooden ladder in the hole in the ground.\n"
    );
    add_item(({"sign", "iron sign"}),
        "It's an ordinary sign with readable letters on it.\n"
    );
    add_cmd_item(({"sign", "iron sign"}), "read",
        "The sign reads:\n" +
        "  West from here you may enter the Haunted House.\n" +
        "  No entrance fee (but it may cost you your life).\n"
    );

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(HAUN_DIR + "house_10", "down", "@@try_down");
    add_exit(HAUN_DIR + "house_2" , "west" , "@@try_west");
    add_exit(CAMP_DIR + "camp_09" , "north", "@@try_north");

    reset_room();
}

int
try_down()
{
    if (TP->query_wiz_level() || TP->query_npc()) return 0;
    if (guard && CAN_SEE(guard, TP)) {
        write("The guard stops you from going there.\n");
    } else {
        write("An invisible force stops you from going there.\n");
    }
    say(QCTNAME(TP) + " tried to go down but failed.\n");
    return 1;
}

int
try_west()
{
    if (guard && CAN_SEE(guard, TP)) {
        guard->command("sigh");
        guard->command("say Don't get lost in there!");
    }
    write("You hear some distant screams.\n");
    return 0;
}

void
go_down(object ob)
{
    int i;

    ob->command("down");
    for (i=0; i<random(3); i++)
	ob->command("south");
}

int
try_north()
{
    if (TP->query_npc() && TP->query_race_name() == "soul") {
        set_alarm(3.0, -1.0, &go_down(TP));
	return 1;
    }
    return 0;
}
