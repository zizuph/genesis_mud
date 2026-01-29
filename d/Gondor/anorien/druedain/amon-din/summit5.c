/*
 *  This is summit5.c
 *
 *  July 1995 by Gorboth
 */

inherit "/d/Gondor/anorien/druedain/amon-din/din_master.c";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/elessar/lib/clock.h"

void reset_room();

void
create_room()
{
    set_north(4);
    set_west(2);

    add_view("Looking away from the building, the view is quite"
            + " impressive here.");

    set_short("on the south side of a building atop Amon Din");
    set_long("@@describe");

    add_item(({"path","pathway"}), BSN(
       "The pathway is little more than a worn dirt trail which has"
     + " formed over many years traffic. It winds around the building"
     + " from the northeast, and ends ubruptly in front of an old"
     + " wooden door."));
    add_item(({"building","face","wall"}), BSN(
       "It is difficult to tell what purpose this building might serve"
     + " judging solely by its external appearance. It is simple and"
     + " unadorned in its construction, yet looks very well built."
     + " Sturdy as it surely is, the ravages of weather and time"
     + " are apparent and have taken their toll in places."));
     add_item(("summit"), BSN(
       "A little farther south, the hill begins to slope downwards again."));
    add_item(({"tree","massive tree"}), BSN(
       "This tree looks older even than the building, and seems to"
     + " have been pruned away on one side to make room for the nearby"
     + " wall. Many of the branches of this tall tree"
     + " reach out and crowd this path."));
    add_item(({"branch","branches"}), BSN(
       "The branches are long and thick with green pine needles."
     + " Between the branches, the huge trunk of the tree is visible."));
    add_item(("trunk"), BSN(
       "It is thick and wide, with many branches thrusting out in all"
     + " directions. This tree looks ideal for climbing purposes."));
    add_item(({"beacon","tower","beacon tower"}), "@@exa_tower");
    add_item(("roof"), BSN(
       "It is a rather high building, and the rooftop is quite out"
     + " of reach. You notice some of the branches from the tree"
     + " extending out over it."));

    add_exit(AMON_DIR + "summit4", "east");

    setuid();
    seteuid(getuid());

    enable_reset();
    reset_room();
}

string
describe()
{
    string ld;

    ld = "The path ends here at the door of a long building"
       + " which extends the length of this summit. All around, the"
       + " view from this hill remains impressive. A massive tree"
       + " grows up against this northern face of the building and"
       + " rises a great distance into the air. Visible above the"
       + " roof of the building, a tall beacon tower looms to the"
       + " northeast";

    if (rq_stage() >= RQ_STAGE_WAR)
    {
        ld += ", shining its signal brightly.";
    }
    else
        ld += ".";

    return BSN(ld);
}

string
exa_tower()
{
    string ttxt;
    string flame;

    if (rq_stage() >= RQ_STAGE_WAR)
    {
        flame = " spewing forth flame ";
    }
    else
        flame = " ";

    ttxt = "The bulk of this tower is not visible due to the building"
         + " directly in front of you to the north. Rising above the"
         + " roof of the building, the top of the tower can be seen"
         + " with a large basin" + flame + "upon its heights.";

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
        case "building":
        case "wall":
        case "up":
            NFN("The building cannot be climbed here.");
            return 0;
            break;
        case "trunk":
        case "tree":
        case "branch":
        case "branches":
            write(BSN("You climb through the branches to the base of"
              + " the large tree."));
            set_dircmd(str);
            TP->move_living("into the tree branches", AMON_DIR
              + "tree1");
            return 1;
        default:
            NFN("What do you want to climb?");
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

void
reset_room()
{
    if(!objectp(present("amon_din_storage_door_out")))
    {
        clone_object(AMON_DIR + "doors/stdoorout")->move(TO);
    }
}
