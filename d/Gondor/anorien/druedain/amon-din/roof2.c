/*
 *  This is roof2.c
 *
 *  July 1995 by Gorboth
 */

inherit "/d/Gondor/anorien/druedain/amon-din/din_master";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/elessar/lib/clock.h"

create_room()
{
    set_east(1);
    set_south(2);

    add_view("The hights of this rooftop highten the effect of this"
           + " marvelous sight.");

    set_short("a rooftop on the summit of Amon Din");
    set_long("@@describe");

    add_item(({"tower","beacon tower"}), "@@exa_tower");
    add_item(({"roof","rooftop","shingles","building"}), BSN(
       "Tight shingles make up the surface of this sloped rooftop,"
     + " which runs a ways towards the northern slope of the hill."));
    add_item(({"hill","hilltop"}), BSN(
       "The hights of this hilltop are second to nothing in the"
     + " area, save for the White Mountains which obscure the"
     + " horizon to the south."));
    add_item(({"edge","southern edge","tree"}), BSN(
       "A number of branches from a large tree have grown"
     + " over the surface of this roof, almost completely covering"
     + " its southern edge."));
    add_item(({"branch","branches"}), BSN(
       "The branches are long and thick. They look strong enough to"
     + " support considerable weight."));
    add_item(({"ground","ledge","eastern ledge"}), BSN(
       "Over the side of the eastern ledge of the rooftop, the base"
     + " of the tall tower can be seen resting on the rocky ground."));
    add_item(("view"), BSN(
       "It is almost as if a map has been opened before you,"
     + " its countless points of interest to behold."));

    add_exit(AMON_DIR + "roof1", "north");
}

string
describe()
{
    string ld;

    ld = "This rooftop is long and somewhat narrow, extending for some"
       + " distance to the north. Quite close, the southern edge of the"
       + " roof is crowded by a singular tree which dwarfs its young"
       + " counterparts which line this building to the north. The"
       + " ground is visible along the eastern ledge, and the view to"
       + " the west remains majestic. Tall and somber, the beacon tower"
       + " of this summit rises directly to the east";

    if (rq_stage() >= RQ_STAGE_WAR)
    {
        ld += ", flames leaping from its basin.";
    }
    else
        ld += ".";

    return BSN(ld);
}

string
exa_tower()
{
    string ttxt;

    ttxt = "The tower is very close, and this rooftop affords a"
         + " rare view of its craftsmanship. Large stonework makes"
         + " up the bulk of its length, and far above can be seen"
         + " a wide basin composed of cement.";

    if (rq_stage() >= RQ_STAGE_WAR)
    {
        ttxt += " Flames leap high from the contents of the basin.";
    }
    return BSN(ttxt);
}

int
enter_tree(string str)
{
    if (!strlen(str))
    {
        NFN("Climb what?");
        return 0;
    }

    switch (str)
    {
        case "ground":
            NFN("How do you propose to get there?");
            return 0;
            break;
        case "tree":
        case "branch":
        case "branches":
        case "onto branch":
        case "onto branches":
            write(BSN("You carefully climb onto a large limb and into"
              + " the branches of the large tree."));
            TP->move_living("into the branches of the tree", AMON_DIR + "tree2", 1, 0);
            return 1;
            break;
        default:
            NFN("Where do you want to climb?");
            return 0;
            break;
    }
    NFN("Climb what?");
    return 0;
}

void
init()
{
    ::init();
    add_action(enter_tree, "climb");
}
