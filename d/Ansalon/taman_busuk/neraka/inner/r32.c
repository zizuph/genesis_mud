/* Ashlar, 20 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit INNER_OUT;

object gNpc, g1, g2;

void
reset_neraka_room()
{
    if (!objectp(gNpc))
    {
        setuid();
        seteuid(getuid());

        gNpc = clone_object("/d/Ansalon/guild/new_pot/obj/living/fallorn");
        gNpc->arm_me();
        gNpc->move(this_object());
        gNpc->set_patrol_time(150);
        gNpc->set_patrol_path(({"sw", "sw", "s", "s", "s", "s", "s", "s",
            "se", "e", "e", "ne", "n", "e", "e", "n", "n", "n", "nw", "n",
            "n", "nw", "w", "w" }));
        gNpc->set_patrol_loop();
        gNpc->start_patrol();
    }

    if (!objectp(g1))
    {
        g1 = clone_npc(NNPC + "templeguard");
        g1->arm_me();
        g1->move(this_object());
    }
    if (!objectp(g2))
    {
        g2 = clone_npc(NNPC + "templeguard");
        g2->arm_me();
        g2->move(this_object());
    }
}

void
create_neraka_room()
{
    set_short("on the Queen's Way");
    set_extra_long("You are walking along the Queen's Way, the main street " +
        "of Neraka. The street leads southwest and east, flanked on both " +
        "sides by the tall city walls. To the north, an archway leads " +
        "through the city wall, while a small alley leads south.");

    add_item_citywalls();
    add_item_street1();
    add_item("archway","The archway is the entrance to a short tunnel " +
        "through the city wall.\n");
    add_item(({"tunnel","short tunnel"}),
        "The short tunnel leads through the city wall.\n");
    add_item("alley","The small alley leads south.\n");

    add_exit(NINNER + "r31", "east");
    add_exit(NINNER + "r33", "southwest");
    add_exit(NINNER + "g1", "north");
    add_exit(NINNER + "al3", "south");

    reset_neraka_room();
}


