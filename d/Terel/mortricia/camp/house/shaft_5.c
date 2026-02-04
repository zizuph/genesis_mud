/* A shaft room. Mortricia 920927 */
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
#define TENT_DIR        CAMP_DIR + "tent/"

int has_hole;
object spectre;

public void
move_here(object ob)
{
    ob->move(TO);
}

public void
reset_room()
{
    if (!spectre) {
        spectre = clone_object(HAUN_DIR + "spectre");
        set_alarm(8.0, -1.0, &move_here(spectre));
    }
    remove_exit("down");
    has_hole = 0;
}

public void
create_room()
{
    set_short("Shaft");
    set_long(
        "You are standing at the end of the shaft. " +
        "The workers that made this shaft probably got " +
        "bored when they reached this point. Another " +
        "explanation would be that they discovered " +
        "something dangerous down here and decided not " +
        "to dig any further. There are piles of garbage on the ground.\n"
    );
    add_item("piles", "The garbage the workers left behind lies in piles.\n");
    add_item("garbage", "It's all kind of trash, nothing useful.\n");
    add_cmd_item("piles", "move", "@@reveal_hole");
    add_cmd_item("garbage", "move", "@@reveal_hole");
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_HIDE, 100);

    add_exit(HAUN_DIR + "shaft_4", "east", "@@check");

    reset_room();
}

public int
check()
{
    if (spectre && present("spectre", TO)) {
        spectre->command("scream");
    }
    return 0;
}

public int
further()
{
    if (spectre && present(spectre) && TP->query_ghost() == 0) {
        if (spectre == TP) return 0;
        spectre->command("scream");
        TP->catch_msg(QCTNAME(spectre) +
	              " stops you from going there!\n");
        say(QCTNAME(TP) + " was pushed back by " +
	    QTNAME(spectre) + ".\n");
        return 1;
    }
    return 0;
}

public string
reveal_hole()
{
    if (has_hole) return "You move around some garbage.\n";

    add_exit(HAUN_DIR + "circ", "down", 0);
    has_hole = 1;
    write("As you move around the garbage you reveal a hole.\n");
    return "";
}
