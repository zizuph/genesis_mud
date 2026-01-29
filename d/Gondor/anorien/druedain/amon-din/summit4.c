/*
 *  This is summit4.c
 *
 *  July 1995 by Gorboth
 */

inherit "/d/Gondor/anorien/druedain/amon-din/din_master";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/elessar/lib/clock.h"

void
create_room()
{
    set_north(1);
    set_west(2);

    add_view("The hillside falls away not far from the corner of"
           + " the building, revealing a breathtaking vista.");

    set_short("near the corner of a buiding atop Amon Din");
    set_long("@@describe");

    add_item(({"trail","path","pathway","ground"}), BSN(
       "There is no beauty to the path, as it is little more than"
     + " trodden earth which has hardened over the years to form a"
     + " visible trail. It leads north and west from here."));
    add_item(({"corner","building"}), BSN(
       "The northern and western faces of this building meet at a"
     + " corner here, which the path winds its way around. The stone"
     + " walls look sturdy, but unremarkable. It is hard to tell what"
     + " such a building might contain within."));
    add_item(({"corner","face","faces","wall","walls"}), BSN(
       "The two visible walls of the building extend out from the"
     + " corner beside the path. The western wall extends a brief"
     + " distance and encounters a tree. A door apparently leads"
     + " into the building along that wall. North, the wall extends"
     + " most of the length of the summit, passing next to the tall"
     + " tower in that direction."));
    add_item(("tree"), BSN(
       "The tree to the west is very large, and rises nearly as high"
     + " as the tall tower to the north. As you stand watching, a"
     + " black bird of some kind is visible in the high branches of"
     + " the treetop."));
    add_item(("bird"), BSN(
       "It is difficult to say for certain, but from this distance it"
     + " looks to be a magpie."));
    add_item(("door"), "It lies to the west. A closer look can be"
                     + " found there.\n");
    add_item(({"tower", "tall tower","thin tower"}), "@@exa_tower");

    add_exit(AMON_DIR + "summit5", "west");
    add_exit(AMON_DIR + "summit3", "north");
}

string
describe()
{
    string ld,
           time = tod();

    ld = "The path winds around the corner of a building here and"
       + " can be followed to the north and west. A large tree is"
       + " visible growing beside the wall to the west, where the path"
       + " runs up to a door. Directly north, a tall and thin tower"
       + " rises high into the "+time+" sky";

    if (rq_stage() >= RQ_STAGE_WAR)
    {
        ld += " where flames leap from its lofty basin.";
    }
    else
        ld += ".";

    return BSN(ld);
}

string
exa_tower()
{
    string ttxt;

    ttxt = "The tower rises not more than twenty paces to the north"
         + " from here. Long and slender, its frame extends high into"
         + " the air placing it in easy view of anything within miles."
         + " A basin rests atop the tower";

    if (rq_stage() >= RQ_STAGE_WAR)
    {
        ttxt += ", flames leaping from its rim.";
    }
    else
        ttxt += ", ever prepared to deliver its signal.";

    return BSN(ttxt);
}
