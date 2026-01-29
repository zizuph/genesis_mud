#include "defs.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <macros.h>

inherit "/std/container";
inherit IM_TELL_FILE;

#define IO all_inventory(this_object())

create_container()
{
    set_name("boat");
    add_name("raft");
    set_short("@@my_short@@");
    add_adj(({"heavy", "wooden"}));
    set_long("@@my_long@@");
    add_item("raft", "It is a @@my_short@@.\n");

    add_prop(CONT_I_WEIGHT, 250*1000);
    add_prop(CONT_I_VOLUME,  90*1000);
    add_prop(OBJ_I_VALUE,   10);

    add_prop(CONT_I_MAX_WEIGHT, 1000*1000);
    add_prop(CONT_I_MAX_VOLUME, 1000*1000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_TRANSP, 1);

    add_prop(ROOM_I_IS, 1);
}

init()
{
    ::init();
    add_action("do_enter", "enter");
    add_action("do_leave", "leave");
    add_action("do_row", "row");
    add_action("do_row", "paddle");
    add_action("do_dir", "east");
    add_action("do_dir", "west");
    add_action("do_dir", "north");
    add_action("do_dir", "south");
    add_action("do_dir", "up");
    add_action("do_dir", "down");
}

string
my_short()
{
    if(ETO->is_lake_room())
	return "heavy wooden raft floating by the shore of the lake";
    else
	return "heavy wooden raft";
}

object
ob_raft() {
    if(!sizeof(FILTER_LIVE(IO)))
	return 0;
    else
	return FILTER_LIVE(IO)[0];
}

int
do_enter(string str)
{
    object ob = ob_raft();
    if(!str || !id(str))
	return notify_fail("Enter what? The raft mayhap?\n");
    if (ob) {
	TP->catch_msg("Unfortunately, " + QTNAME(ob) + " already sits in the raft.\n");
	return 1;
    }
    if (TP->move_living("into the raft", TO)) {
	write("You failed for some reason.\n");
	return 1;
    }
    action("$N entered the raft.\n");
    return 1;
}

int do_leave(string str)
{
    if(str && str!="raft")
	return 0;
    write("You leave the raft.\n");
    TP->move_living("from the shaft", ETO);
    return 1;
}

string
my_long()
{
    object ob = ob_raft();
    string t;
    if (ETP==ETO) {
	t = "This seems like a heavy wooden raft. It is well-made, "+
	    "but seems too heavy to carry. ";
	if(ob)
	    return t + "You notice that someone already sits in the raft.\n";
	else
	    return t;
    } else if(ETP==TO) {
	t = "You are sitting on a raft here.\n";
	if(ETO->is_lake_room())
	    return t+ETO->from_raft_desc();
	else
	    return t+"On the outside, you see:\n\n"+ETO->long();
    } else
	return "";
}

do_row(string str)
{
    seteuid(getuid());
    if(TP!=ob_raft())
	return notify_fail("But you must be in the raft to "+query_verb()+" it!\n");
    if(!str || str=="")
	return notify_fail(CAP(query_verb())+" in which direction?\n");
    if(!ETO->is_lake_room())
	return notify_fail("You can't row the raft in this room.\n");
    if(str=="lake"||str=="towards islet"||str=="islet"||ETO->allowed_dir(str))
	return ETO->row(TO, str);
    return notify_fail("You can't "+query_verb()+" in that direction.\n");
}


do_dir()
{
    if(TP!=ob_raft())
	return 0;
    if(!ETO->is_lake_room())
    {
	do_leave();
	return TP->command(query_verb());
    }
    return do_row(query_verb());
}
