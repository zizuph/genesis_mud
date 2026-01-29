/*
 * hall.c
 * Town hall
 * Haven town
 * Created by Tibbit, 11 Mar 1998
 */

#include "../local.h"

inherit HAVENINBASE;

object citizen1,citizen2,citizen3,citizen4,seeker;

void
reset_haven()
{
    reset_euid();

    if(!citizen1)
        (citizen1 = clone_object(HNPC + "citizen_" +
            (random(2) ? "m" : "f")))->move(TO);
    if(!citizen2)
        (citizen2 = clone_object(HNPC + "citizen_" +
            (random(2) ? "m" : "f")))->move(TO);

    if((!seeker) && (random(4)))
        (seeker = clone_object(HNPC+"seeker"))->move(TO);
}

void
create_haven()
{
    set_short("Haven town hall");

    set_long("You have stepped inside the town hall of the "+
        "citizens of Haven. The room is bare, the wooden walls "+
        "without decoration; yet it feels somehow homey and welcoming. "+
        "The wooden floor has been swept clean and the windowsills "+
        "carefully dusted."+
        "\n");

    add_item(({"hall","town hall","room"}),
        "The town hall is constructed entirely of wood, and is "+
        "quite simple yet somehow more comfortable than the finest "+
        "palace.\n");
    add_item(({"wall","walls","wooden wall","wooden walls"}),
        "The walls are bare.\n");
    add_item("wood","This type of wood is common in the "+
        "surrounding forests.\n");
    add_item(({"window","windows"}),
        "Light is allowed into the room by several large windows.\n");
    add_item(({"sill","sills","windowsill","windowsills"}),
        "The window sills are completely free of dust.\n");

    add_exit(HROOM+"st3","east");

}

