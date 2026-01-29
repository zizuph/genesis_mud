/* Ashlar, 19 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit INNER_OUT;

object off,m1,m2;

void
reset_neraka_room()
{
    if (!objectp(off))
    {
        off = clone_npc(NNPC + "humcaptain", ({"black","red","blue"})[random(3)]);
        off->start_patrol();
        off->set_patrol_time(15);
        off->set_patrol_path(({"ne","ne","n","w","w","s","sw","w","s","s","s",
            "ne","ne"}));
    }
    if (!objectp(m1))
        m1 = clone_npc(NNPC + "minotaur");
    if (!objectp(m2))
        m2 = clone_npc(NNPC + "minotaur");
}

void
create_neraka_room()
{
    set_short("on the Queen's Way");
    set_extra_long("You are walking along the Queen's Way, the main street " +
        "of Neraka. The street leads northeast and southwest, flanked on " +
        "the northwest side by the tall city walls, and on the southeast " +
        "side by a huge arena.");

    add_item_citywalls();
    add_item_street1();
    add_item(({"arena","huge arena","arena of death"}),
        "The huge arena lies to the southeast, built against the city " +
        "wall.\n");

    add_exit(NINNER + "r19", "southwest");
    add_exit(NINNER + "r21", "northeast");

    reset_room();
}


