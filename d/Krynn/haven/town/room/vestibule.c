/*
 * vestibule.c
 * Vestibule of the Seeker Temple
 * Haven town
 * Created by Tibbit, 11 Mar 1998
 */

#include "../local.h"

inherit HAVENINBASE;

object citizen1,seeker1;

void
reset_haven()
{
    reset_euid();

    if(!citizen1)
        (citizen1 = clone_object(HNPC + "citizen_" +
            (random(2) ? "m" : "f")))->move(TO);

    if(!seeker1)
        (seeker1 = clone_object(HNPC+"seeker"))->move(TO);

}

void
create_haven()
{
    set_short("Vestibule of the Seekers' Temple");

    set_long("This small room is the vestibule, or entryway, "+
        "to the temple of the Seekers, the religious men who reside "+
        "here in Haven and who teach the ways of the new gods. "+
        "This is by far the finest building in town, painted a "+
        "white both inside and out. The temple proper lies just "+
        "east of here, while the town's main street is to the west."+
        "\n");

    add_item(({"building","temple"}),
        "This is the temple of the Seekers, the largest and finest "+
        "buiding in the town of Haven.\n");
    add_item(({"paint","painting","white","wall","walls"}),
        "The walls of this building are painted gleaming white, "+
        "in contrast to the wood-colored homes of the local citizens.\n");
    add_item(({"temple","temple proper"}),
        "The inner sanctum of the Seekers' temple is to the east.\n");

    add_exit(HROOM+"st3","west");
    add_exit(HROOM+"temple","east");

}

