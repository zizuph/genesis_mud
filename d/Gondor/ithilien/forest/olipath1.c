/*
 * /d/Gondor/ithilien/forest/olipath1.c
 *
 * Coded by Elessar.
 *
 * Modification log:
 * 30-Dec-1997, Gnadnar: general revision
 * 
 */

#pragma strict_types

inherit "/d/Gondor/std/room";

#include "/d/Gondor/defs.h"
#include <stdproperties.h>

object        *Haradrim = allocate(2);
//object      *Scout = allocate(2);

public int    do_smell(string arg);

public void
create_gondor()
{
    set_short("A broad trail in the Ithilien forest");
    set_long(
    "A broad trail winds through the forest and disappears over "+
    "a small hill to the east. "+
    "Along the trail, broken branches are hanging from the trees, as "+
    "if something huge has made its way through here. "+
    "A strange smell wafts down the trail from the east.\n");

    add_item( ({ "branches", "tree", "forest", "trees" }), 
    "Several of the trees along the broad trail have broken "+
    "branches, or have been overturned or even uprooted. "+
    "Something of great strength has passed through here!\n");
    add_item( ({ "small hill", "hill" }), 
    "The ground rises slightly to the east.\n");
    add_item( ({ "trail", "tracks" }), 
    "The trail is strange; some ordinary "+
    "footprints left by men are here, but they pale in comparison "+
    "to the large round prints the size of tree-trunks!\n");
    add_prop(ROOM_S_DIR, ({ "east", "great beast" }) );

    add_exit(ITH_DIR+"forest/haradcamp1a", "north", 0);
    add_exit(ITH_DIR+"forest/haradcamp3a", "south", 0);
    add_exit(ITH_DIR+"forest/olicamp", "east", 0);
    add_exit(ITH_DIR+"forest/haradcamp2", "west", 0);


    reset_room();
}

public void
reset_room()
{
    clone_npcs(Haradrim, NPC_DIR+"haradrim", 5.0);
//    clone_npcs(Scout, HAR_NPC_DIR + "ithilien_scout", 5.0);
}

public void
init()
{
    ::init();
    add_action(do_smell, "smell");
    add_action(do_smell, "sniff");
    add_action(do_smell, "inhale");
}

/*
 * Function name:    do_smell
 * Description:        handle attempts to smell/sniff
 * Arguments:        string arg -- whatever the player typed
 * Returns:        1 if we understand arg, 0 if not
 */
public int
do_smell(string arg)
{
    if ( !arg || arg == "smell" || arg == "strange smell" )
    {
    write("The smell is reminiscent of a barnyard, but "+
        "much much stronger.");
    return 1;
    }
    return 0;
}
