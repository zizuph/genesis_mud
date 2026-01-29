inherit "/d/Shire/std/room";

#include "/d/Shire/common/defs.h"

object old_man;

void
create_shire_room()
{
    set_short("The Greenway");
    set_long("You are travelling on an old road winding its " +
             "way through the fields surrounding it. The " +
             "tracks on the road are quite fresh and imply " +
             "that the road is in constant use. You can hear " +
             "the birds sing in the distance. There is a " +
             "big log lying by the road.\n");    

    add_item(({ "field", "fields" }), "The crop on the fields are bending to "
	     + "the wind\n");
    add_item(({ "track", "tracks" }), "The tracks are mostly made by wagons "
	     + "and mules. There are also a few that indicate horses.\n");
    add_item(({ "bird", "birds" }), "They are only small black specks in the "
	     + "sky.\n");
    add_item(({ "log", "bench" }),
	     "This was once a big pine tree, but someone made a "+
	     "bench out of it.\n");

    add_exit(GWAY_DIR + "gw2", "north", "@@tree_north@@",0);
    add_exit("/d/Gondor/common/shirelink", "southeast", 0);
    /*   add_exit(STAND_DIR + "gw4", "south", 0);*/
    add_exit("/d/Shire/common/hollin/f0000", "northeast", 0);
    add_exit("/d/Shire/sarnford/eroad1", "west");
    add_exit("/d/Shire/common/obj/club/tree","northwest",0,1);
    reset_shire_room();

}

void
reset_shire_room() 
{
    if (!old_man)
    {
		old_man = clone_object(STAND_MONSTER + "old_man");
	old_man->move(this_object());

    }
}

int
blocked() 
{
    if (this_player()->query_wiz_level()) {
        write("This is not open to public");
        return 0;
    }

    write("Passage in that direction is blocked by the big log.\n");
    return 1;
}

void
init()
{
    ::init();

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

void tree_north()
{
    tell_room("/d/Shire/bree/rooms/road/treetop_fort.c", QCTNAME(TP) + 
        " heads north up the Greenway highway.\n");
}