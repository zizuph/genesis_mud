/*
 *  This is tree3.c
 *
 *  July 1995 by Gorboth

 *  Modification Log:  Recoded to accomodate longer periods of time
 *                     between armaggeddons (Gorboth, Oct. 2004)
 */

inherit "/d/Gondor/anorien/druedain/amon-din/din_master";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void reset_room();

void
create_room()
{
    add_view("The lands extend out for what seems to be an endless"
            + " distance like a vast map before you. A better vantage"
            + " point than this is almost unimaginable.");

    set_short("in the high branches of a tree atop Amon Din");
    set_long(BSN(
       "The branches have thinned somewhat here, thus allowing for"
     + " what is without a doubt the most dazzling view from this summit."
     + " Above, the highest points of the tree wave slightly in the"
     + " soft breeze. The roof of a building is visible below,"
     + " and it seems one might descend in that direction."));

    add_item(({"branches","branch","limb","limbs","needles"}), BSN(
       "Branches splay out in all directions from the center of"
     + " this tall tree. Though less in number and shorter in length,"
     + " they still make seeing in most directions impossible."));
    add_item(({"building","roof","rooftop"}), BSN(
       "It is far below, quite inaccessible from this point."));
    add_item(({"tree","center"}), BSN(
       "Even so near to its top, this tree is impressive and strong,"
     + " having weathered many a storm upon this hilltop."));

    add_exit(AMON_DIR + "tree2", "down");

    setuid();
    seteuid(getuid());

    enable_reset();
    reset_room();
}

void
reset_room()
{
    object   nest;

    if (!(nest = present("bird_nest_at_amon_din", this_object())))
    {
        clone_object(AMON_DIR + "obj/bird_nest")->move(TO);
    }

    nest->reset_container();
}
