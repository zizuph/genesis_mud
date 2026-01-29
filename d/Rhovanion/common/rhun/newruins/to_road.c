/* Author: Modred 950816 */


inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h";

create_room()
{
    set_short("By the ruins");
    set_long("You stand at the end of a wide"+
    " dirt road. To the south you see the ruins of a great"+
    " black structure rise against the blue sky, and from"+
    " the southwest a mild breeze from the sea brings you"+
    " the smell of the sea. You can follow the road back"+
    " to northeast, or walk south towards the ruins.\n");


    add_exit(RHUN_DIR + "newruins/gates", "south");
    add_exit(RHUN_DIR + "roads/section9/d", "northeast");


    add_item(({ "ruin","ruins","building","structure", "walls" }),"As you look south,"+
    " you see the ruins of a great building, with grey walls"+
    " surrounding it. It looks like an ancient fortress of some kind.\n");

    add_item(({ "road",}),"This is a wide dirt road curving south"+
    " towards the ruins of a great building. There is no traffic"+
    " and weeds have begun to grow in the old wheeltracks.\n");
}

