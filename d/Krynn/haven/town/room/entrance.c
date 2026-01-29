
/*
 * entrance.c
 * Entrance gate to the town of Haven
 * Tibbit, 17 Feb 1998
 *
 */

#include "../local.h"

inherit HAVENBASE;

object citizen1;

void
reset_haven()
{
    reset_euid();

    if(!citizen1)
        (citizen1 = clone_object(HNPC+"citizen_"+
            (random(2)?"m":"f")))->move(TO);
}

void
create_haven()
{
    add_my_desc(
        "A sturdy wooden bridge leads over a small "+
        "creek and into the town of Haven, to the east."+
        "\n"
        );

    add_item("bridge","You stand on a bridge, solidly "+
        "built from the wood of nearby trees. "+
        "It leads into the town of Haven.\n");
    add_item("creek","A small creek, not much more than "+
        "a trickle of water in a shallow gully, "+
        "passes beneath the bridge.\n");
    add_item("town","The modest town of Haven "+
        "stands just to the east.\n");

    add_exit(HROOM+"st1","east");
    add_exit(RDIR+"road10","west");

}


