/* A chimney. Mortricia 930501 */
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Terel/common/terel_defs.h"

#define TP             this_player()
#define TO             this_object()

public void
reset_room()
{
    object scroll;

    if (present("scroll")) return;
    scroll = clone_object(MANSION + "obj/scroll");
    scroll->move(TO);
}

public void
create_room()
{
    set_short("inside chimney");
    set_long("You are standing on a small niche in an old chimney.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_item(({"wall", "walls", "soot"}),
        "The walls are full of black soot. When you examine the soot " +
        "you notice some iron handles.\n");
    add_item(({"handles", "iron handles"}),
        "The iron handles seem not to be securely fastened " +
        "in the wall. You shouldn't try to climb further " +
        "upwards.\n");

    add_exit(MANSION + "rooms/b_wall", "down", 0);

    reset_room();
}

public void
landing(object who)
{
    if (!who) return;
    
    who->catch_msg("OOUCH! Your body hits the lattice real hard!\n");
    who->move_living("comes falling down", MANSION+"rooms/b_wall");
    who->reduce_hit_point(50);
    who->do_die(TO);
    who->command("$drop all");
}

public void
falling(object who)
{
    if (!who) return;
    who->catch_msg("...pictures of your entire life visualize " +
        "before your eyes...\n");
    set_alarm(1.0, -1.0, &landing(who));
}

public int
do_climb(string what)
{
    notify_fail("Climb what?");
    if (!what) return 0;
    if (what != "handles" && what != "iron handles") return 0;
    write("You start to climb upwards but one of the iron handles " +
          "suddenly disappears under your foot. You begin to fall...\n");
    say(QCTNAME(TP) + " starts to climb upwards, but " +
        TP->query_pronoun()+" suddenly falls down with a scream.\n");
    set_alarm(1.0, -1.0, &falling(TP));
    return 1;
}

public void
init()
{
    ::init();
    add_action(do_climb, "climb", 0);
}
