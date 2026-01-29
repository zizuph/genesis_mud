/*
 *  This is roof1.c
 *
 *  July 1995 by Gorboth
 */

inherit "/d/Gondor/anorien/druedain/amon-din/din_master";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/elessar/lib/clock.h"

void
create_room()
{
    set_east(3);
    set_south(2);

    add_view("The heights of this rooftop lend an even greater"
           + " quality to this already impressive sight.");

    set_short("A rooftop on the summit of Amon Din");
    set_long("@@describe");

    add_item(({"shingles","roof","surface","slope"}), BSN(
        "The roughness of the shingles combined with the mild slope of "
      + "this roof make balancing quite easy. A drainpipe runs down"
      + " the side of the building."));
    add_item(({"drainpipe","drainpipes"}), BSN(
        "The drainpipe runs the height of the building from the roof"
      + " to the ground below."));
    add_item(("tower"), "@@exa_tower");
    add_item(({"building","wall"}), BSN(
        "This is a long, narrow building running north to south. You stand "
      + "atop the northernmost edge of the roof, and can clearly continue "
      + "along to the south. Trees grow along the eastern side of the "
      + "building."));
    add_item(({"side","sides"}), BSN(
       "Trees have grown along the eastern side of this building,"
     + " while to the west, a view of the countryside exands for"
     + "miles around."));
    add_item(({"tree","trees"}), BSN(
        "These trees are unlike those of the forest below. It could be that "
      + "they were planted along with the construction of this building and "
      + "the tower. The trees make it impossible to see the ground, and "
      + "most likely prevent persons there from seeing the rooftop. "));

    add_exit(AMON_DIR + "roof2","south");
}

int
go_down(string str)
{
    if (!strlen(str))
    {
        NFN("Climb what?");
        return 0;
    }

    if (str != "drainpipe")
    {
        NFN("What do you want to climb?");
        return 0;
    }

    write("You climb down the drainpipe to the ground.\n");
    TP->add_prop("_gondor_i_found_din_drain", 1);
    TP->move_living("down the side of the wall",AMON_DIR + "summit",1,0);

    return 1;
}

string
exa_tower()
{
    string ttxt;

    ttxt = "The diameter of this tower is actually quite narrow, measuring"
         + " perhaps 12 feet in width. The circular shaft which comprises"
         + " its base rises at least 50 feet into the air, and supports"
         + " what appears to be a large basin.";

    if (rq_stage() >= RQ_STAGE_WAR)
    {
        ttxt += " Bright flames rise from this basin, signifying that the"
              + " city of Minas Tirith is calling to its allies for aid.";
    }

    return BSN(ttxt);
}

string
describe()
{
    string ld;

    ld = "Tight shingles make up the surface of this roof, the slope"
       + " of which is slight. The roof ends abruptly to the north,"
       + " while south of here the roof extends towards a large tree"
       + " which rises against the building there. The western"
       + " side of this building runs very close to the edge of the"
       + " summit, and the view in that direction is breathtaking."
       + " Trees have grown alongside the eastern wall, obscuring the"
       + " view of the ground. Rising directly to the southeast, a"
       + " tall tower looms close";

    if (rq_stage() >= RQ_STAGE_WAR)
    {
        ld += ", flames leaping from its heights.";
    }
    else
        ld += ".";

    return BSN(ld);
}

void
init()
{
    ::init();

    add_action("go_down","climb");
}
