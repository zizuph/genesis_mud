/*
 * The terrace path along the river in Imladris
 * By Finwe, December 1997
 */

#include "local.h"
#include "/d/Shire/sys/defs.h"

inherit VALLEY_BASE;
inherit "/d/Gondor/common/lib/drink_water.c";

void
create_valley_room()
{
    set_extraline("The path follows the river's edge. The river " +
        "Bruinen rushes swiftly past you as it flows south and " +
        "west. A garden grows here, surrounded by a split-rail fence. " +
        "The ground slopes towards the river.\n" +
        "An ornately carved bench sits at the edge of the river.");

    add_item(({"road","ground","path","stony path", "down"}),
        "The path is made out of flat stones that closely fit " +
        "together.\n");
    add_item(({"last homely house", "house"}),
        "The house is constructed of stone with ornately carved " +
        "dark beams. The beams  for a criss-cross and diamond " +
        "patterns across the face of the house. Gables extend from " +
        "the roof. The roof is covered with cedar shingles.\n");
    add_item(({"shingles", "cedar shingles"}),
        "The cedar shingles are weather worn but still " +
        "in good condition.\n");
    add_item("roof",
        "The roof is steeply pitched, allowing snow and " +
        "rain to roll off the house quickly and easily.\n");
    add_item("gables",
        "The extend from the roof, allowing more space in " +
        "the upper rooms.\n");
    add_item(({"beam", "beams"}),
        "The beams are made from dark oak. They are polished " +
        "to a deep luster and decorate the face of the house.\n");
    add_item("garden",
        "The garden surrounds the house. Many fruit trees, " +
        "vegetables, and edible plants can be seen growing " +
        "there. A split-rail fence surrounds the garden.\n");
    add_item(({"river", "river bruinen", "bruinen"}),
        "This finger of the river Bruinen rushes west over " +
        "polished rocks. The water is clear. Its gentle music " +
        "fills the air.\n");
    add_item(({"bench", "stone bench", "ornately carved bench"}),
        "The bench is made of a solid piece of red marble " +
        "quarried from the mountains nearby. It is " +
        "decorated with scenes from the Last Alliance.\n");
    add_item("scenes",
        "Some of the scenes include the battle on the stony " +
        "plain of Dagorlad, the fall of Gil-galad, and the " +
        "stumble of Sauron.\n");
    set_fence("They are secured to posts that have " +
        "been sunk into the ground.\n");

    set_drink_from(({"river", "river bruinen", "bruinen"}));

    add_path_herbs();

    add_exit(VALLEY_DIR + "t_path10",  "north");
    add_exit(VALLEY_DIR + "t_path08",  "southwest");
    reset_room();
}

void
reset_room()
{
    set_searched(0);
}

void
init()
{
    ::init();
    init_drink();

    add_action("do_sit",        "sit");
    add_action("do_stand",      "stand");
    add_action("do_nothing",    "north");
    add_action("do_nothing",    "southwest");
    add_action("do_nothing",    "jump");
    add_action("do_nothing",    "tackle");
    add_action("do_nothing",    "dance");
    add_action("do_nothing",    "bow");
    add_action("do_nothing",    "curtsey");
    add_action("do_nothing",    "wiggle");
    add_action("do_nothing",    "strut");
    add_action("do_nothing",    "kill");

}


string short_desc()
{
    return ("The terrace path along the Bruinen");
}


int
do_sit(string str)
{
    if(str != "on bench")
    {
        write("Sit down where? Perhaps on the bench?\n");
        return 1;;
    }

    TP->add_prop(LIVE_S_EXTRA_SHORT, " sitting on the stone bench");
    TP->add_prop("i_am_sat",1);
    write("You sit down on the ornate bench.\n");
    say(QCTNAME(TP)+ " sits down on the stone bench.\n");
    return 1;

}

int
do_stand()
{
    if(!TP->query_prop("i_am_sat"))
    {
        write("But you're not sitting down!\n");
        say(QCTNAME(TP)+ " looks at the river.\n");
        return 1;
    }

    TP->remove_prop("i_am_sat");
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
    write("You stand up, refreshed and invigorated from the rest.\n");
    say(QCTNAME(TP)+ " arises from the bench and looks around.\n");
    return 1;

}

int
do_nothing()
{
    if(TP->query_prop("i_am_sat"))
    {
        write("You can't do that sitting down!\n");
        say(QCTNAME(TP)+ " looks around.\n");
        return 1;
    }
}
