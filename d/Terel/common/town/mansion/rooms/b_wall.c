/* Behind the wall, inside the chimney. Mortricia 930501 */
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Terel/common/terel_defs.h"

#define TP             this_player()
#define TO             this_object()
#define WHERE          MANSION + "rooms/in_water"
#define ON_THE_WAY     MANSION + "rooms/u_lattice"

public void
init()
{
    ::init();
    add_action("do_climb", "climb", 0);
    add_action("go_down", "down");
    add_action("go_down", "d");
}

public void
create_room()
{
    object sword;

    set_short("inside chimney");
    set_long(
        "You are standing on a lattice inside an old chimney. " +
        "The walls are covered with black soot.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_item(({"lattice", "grating", "trellis"}),
        "It's a lattice work made of iron. " +
        "It's rather fine-meshed so there is no risk to fall " +
        "through it. Far below you think you see some water.\n");
    add_item(({"wall", "walls", "soot"}),
        "The walls are full of black soot. When you examine the soot " +
        "you notice some iron handles.\n");
    add_item(({"handles", "iron handles"}),
        "The iron handles seem to be securely fastened into " +
        "the wall. They look climbable.\n");

    add_exit(MANSION + "rooms/s_stair2", "north", 0);

    seteuid(getuid(TO));
    sword = clone_object(MANSION + "obj/ksword");
    sword->move(TO);

}

public int
do_climb(string what)
{
    notify_fail("Climb what?\n");
    if (!what) return 0;
    if (what != "handles" && what != "iron handles" &&
        what != "the handles" && what != "the iron handles" &&
        what != "on handles" && what != "on the handles") return 0;
    notify_fail("Uhum... You realise that climbing here is above your "+
                "capability.\n");
    if (TP->query_skill(SS_CLIMB) < 20) return 0;
    write("You climb up in the chimney.\n");
    say(QCTNAME(TP) + " climbs upwards.\n");
    TP->move_living("M", MANSION+"rooms/chimney");
    return 1;
}

public void
move_item(object ob)
{
    object on_the_way;

    on_the_way = find_object(ON_THE_WAY);
    if (on_the_way)
        tell_room(on_the_way, "SPLASH! Something hit the water.\n");
    if (ob) {
        tell_room(TO, "The "+ob->short()+" vanishes through the lattice.\n");
        ob->move(WHERE);
    }
}

public void
enter_inv(object ob, object from)
{
    int vol;

    ::enter_inv(ob, from);
    
    if (living(ob)) return;
    
    vol = ob->query_prop(OBJ_I_VOLUME);
    if (vol < 900 && random(vol) < 80)
        set_alarm(1.0, -1.0, &move_item(ob));
}

public int
go_down(string str)
{
    if (str) return 0;
    notify_fail("You are far too big to get through the lattice work.\n");
    if (TP->query_ghost() == 0) return 0;
    write("You float down through the lattice work.\n");
    say(QCTNAME(TP)+" floats down through the lattice work.\n");
    TP->move_living("M", MANSION+"rooms/u_lattice");
    return 1;
}
