/*
 *  This is tree1.c
 *
 *  July 1995 by Gorboth
 */

inherit "/d/Gondor/common/room";

#include <macros.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("in the branches at the base of a tree atop Amon Din");
    set_long(BSN(
       "Large branches extend in all directions here, aside from those"
     + " which have been hewn away to accomodate the side of a nearby"
     + " building. A pathway leading up to the building is visible"
     + " through these low limbs. The thick trunk of this tree"
     + " continues up for some distance."));
    add_item(("view"), BSN(
       "Unfortunately, the thick branches extending from the trunk"
     + " prevent much of a viewpoint from here."));
    add_item(({"branches","branch","limbs","limb"}), BSN(
       "The branches at the base of this pine are long and sturdy."
     + " Limbs of similar size continue a good distance up the length"
     + " of the tree."));
    add_item(({"tree","pine"}), BSN(
       "This is a large and very old pine tree. The size of its trunk,"
     + " and the heigth of its tip bear testimony to the many years it"
     + " has weathered atop this mount."));
    add_item(("trunk"), BSN(
       "This trunk is at least four feet in diameter, and stands quite"
     + " close to the side of a nearby building."));
    add_item(("tip"), BSN(
       "The tip of this tree is high above and quite out of view. It"
     + " may be possible to reach it by climbing up the tall trunk,"
     + " however."));
    add_item(("building"), BSN(
       "It is quite obvious that this building is not as old as the"
     + " tree due to the fact that limbs have been sawed away to make"
     + " room for its nearest wall."));
    add_item(({"path","pathway"}), BSN(
       "The pathway leads up to a doorway which enters the building"
     + " quite close to here."));
    add_item(({"door","doorway"}), BSN(
       "It is not far from here, but the branches obscure most of its"
     + " detail. Perhaps a closer look would help."));

    add_exit(AMON_DIR + "summit5", "pathway");
    add_exit(AMON_DIR + "tree2.c", "up", "@@climb_up", 6);
}

int
climb_up()
{
    int  climb = TP->query_skill(SS_CLIMB);
    int  diff = random(20)+5;

    if (climb < diff)
    {
        write(BSN("You attempt to climb farther up the tree, but cannot"
                + " seem to find any good holds."));
        say(QCTNAME(TP) + " tries to climb up the trunk, but fails.\n");
        return 1;
    }
    else
        write("You climb up the sturdy branches to a higher level.\n");
        return 0;
}
