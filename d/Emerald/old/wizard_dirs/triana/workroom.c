#pragma save_binary
inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>
#include "/secure/std.h"
#include "/d/Avenir/common/common.h"

string intruder_status();
int unbar_func(string arg);
int go_back();
int lock_status;
create_room()
{
	::create_room();
	lock_status = 0;
	set_short("Forest Glade");
	set_long("you find yourself standing in the middle of a forest " +
	"clearing. You are totally surrounded by a dense growth of trees. " +
	"Under your feet grow vines, moss, flowers. Through the middle " +
	"of this area, runs a gently gurgling river. Birds chirp and " +
	"animals frolic through the forest. You have a complete feeling of peace here." +
	"@@intruder_status@@" + "\n");

	add_exit("/d/Genesis/start/human/town/common.c", "common", "@@wiz_check@@");
    add_prop(ROOM_I_LIGHT, 1);
}
void
init()
{
	::init();
	add_action("do_pose", "emote");
	add_action("do_pose", ":");
	add_action("unbar_func", "unbar", 0);
}

int
do_pose(string str)
{
	say(QCTNAME(this_player()) + " " + str + "\n");
	write("You emote: " + METNAME + " " + str + "\n");
	return 1;
}

int wiz_check()
{
	if(!TP->query_wiz_level())
	return 1;
	else
		return 0;
}

int go_back()
{
	object last_room;
	if (!(last_room=TP->query_prop(LIVE_O_LAST_ROOM)))
		return 1;
	TP->catch_msg("You try to find the home of Triana but you are lost in a dense fog and are magically returned to where you started from.\n\n");
		TP->move(last_room);
		return 1;
}

string intruder_status()
{
	if(lock_status)
	return "The forest is surrounded by a dense fog.\n";
	return " \n";
}

unbar_func(string arg)
{
	if(TP->query_real_name() !="triana")
	{
	TP->catch_msg("Only Triana can control the magic of this room.\n\n");
		return 1;
	}
	lock_status=1-lock_status;
	tell_room(TO, QCTNAME(TP) + "incants a spell and the forest is surrounded by a dense fog.\n\n");
	return 1;
}

enter_inv(object ob, object from)
{
    if(interactive(ob) && lock_status && ob != find_living("triana"))
	{
		ob->catch_msg("\n\n Sorry, Triana would like to be left alone at the moment.  Please try agian later or ask her if you may enter \n\n");
		tell_room(TO, QCTNAME(ob) + " tried to enter\n\n");
		ob->move(from);
		}
	if(!find_living("triana"))
{
	ob->catch_msg("\n\n Tri is not in right now please try later. \n\n");
		ob->move(from);
}
}

