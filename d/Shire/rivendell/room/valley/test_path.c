/*
 * The terrace path along the river in Imladris
 * By Finwe, December 1997
 */
 
#include "local.h"
#include "/d/Shire/sys/defs.h"
 
inherit VALLEY_BASE;
 
void
create_valley_room()
{
 
    set_extraline("The path follows the river's edge. The river " +
        "Bruinen rushes swiftly past you as it flows south and " +
        "west. A garden grows here, surrounded by a split-rail. " +
        "The ground slopes towards the river.");
 
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
        "there. a split-rail fence surrounds the garden.\n"); 
    add_item(({"fence", "wooden fence", "split-rail fence"}),
        "The fence is constructed of timbers that have been " +
        "split in two. They are secured to posts that have been " +
        "sunk into the ground.\n");
    add_item(({"river", "river bruinen", "bruinen"}),
        "This finger of the river Bruinen rushes over west over " +
        "polished rocks. The water is clear and cold as it " +
        "comes from deep in the mountains. Its gentle music " +
        "fills the air.\n"); 
 
    add_prop(OBJ_I_CONTAIN_WATER,1);
     
    add_exit(VALLEY_DIR + "t_path10",  "north");
    add_exit(VALLEY_DIR + "t_path09",  "southwest");
 
}
void
init()
{   
    ::init();
    add_action("drink_it",    "drink");
    add_action("do_sit","sit");
    add_action("do_stand","stand");
    add_action("do_nothing","north");
    add_action("do_nothing","south");
    add_action("do_nothing","east");
    add_action("do_nothing","west");
    add_action("do_nothing","northeast");
    add_action("do_nothing","northwest");
    add_action("do_nothing","southwest");
    add_action("do_nothing","southeast");
    add_action("do_nothing","jump");
    add_action("do_nothing","tackle");
    add_action("do_nothing","dance");
    add_action("do_nothing","bow");
    add_action("do_nothing","curtsey");
    add_action("do_nothing","wiggle");
    add_action("do_nothing","strut");
    add_action("do_nothing","kill");
 
}
 
drink_it(string s)
{
   if(s=="water" || s=="water from river")
       {
            TP->catch_msg("You kneel before the river, dipping " +
                "your cupped hands into the river and get a " +
                "drink of the clear icy water. Its taste " +
                "refreshes your mind and body.\n");
 
           say(QCTNAME(TP)+" kneels before the river and gets a " +
                "drink.\n");
           TP->drink_soft(1200);
            return 1;
        }
    else
            NF("Drink what?\n");
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
        write("Sit where? On the bench?\n");
        return 1;;
    }
 
    TP->add_prop(LIVE_S_EXTRA_SHORT, " sitting on the bench");
    TP->add_prop("i_am_sat",1);
    write("You sit down on the wooden bench.\n");
    say(QCTNAME(TP)+ " sits down on the bench.\n");
    return 1;
 
}
 
int
do_stand()
{
    if(!TP->query_prop("i_am_sat"))
    {
        write("But you're not sitting down!\n");
        say(QCTNAME(TP)+ " jumps a little in the air.\n");
        return 1;
    }
 
    TP->remove_prop("i_am_sat");
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
    write("You stand up, refreshed and ready to go on your way.\n");
    say(QCTNAME(TP)+ " stands with a spring.\n");
    return 1;
 
}
 
int
do_nothing()
{
    if(TP->query_prop("i_am_sat"))
    {
        write("You can't do that sitting down!\n");
        say(QCTNAME(TP)+ " fidgets on the bench.\n");
        return 1;
    }
}
