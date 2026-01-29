inherit "/std/room";

#include "/d/Emerald/defs.h"

int query_sickness();
int set_sickness(int a);
int do_open(string str);
int do_close(string str);
int set_window(int i);
string do_enter();

int sickness; /* 0 = sick kid, 1 = healed */
int window; /* 1 = open, 0 = closed (default) */

object outside_room;

void create_room()
{
    if(!LOAD_ERR(LEAH_DIR + "house2-bedroom"))
	outside_room = find_object(LEAH_DIR + "house2-bedroom");
    set_short("Outside a small house");
    set_long("   You are standing outside a small house in Leah. "+
	"You are enclosed on the south, west, east by bushes, and "+
	"the north is the outside wall of a house.\n\n"+
	"There are no obvious exits.\n");

    add_item(({"bushes", "bush"}), "The bushes surround you. Which "+
	"side of the bushes do you want to look at? East, west, or "+
	"south?\n");

    add_item(({"east bushes", "eastern bushes", "east bush", "eastern bush"}),
	"The eastern bushes are a fairly plain shaped hedge. There is a "+
	"single branch sticking out without any vegitation on it.\n");

    add_item(({"branch", "single branch"}), "The branch is sticking out "+
	"of the eastern bushes. It appears to be fairly strong. You "+
	"notice some talon marks on it from what appears to be a fairly "+
	"large bird.\n");

    add_item(({"south bushes", "southern bushes", "south bush",
		 "southern bush"}),
	"The southern bushes are a filled with red roses. Their sweet "+
	"smell fills the air.\n");

    add_item(({"west bushes", "western bushes", "west bush",
		 "western bush"}),
	"The western bushes are a fairly plain shaped hedge. They are "+
	"filled with bright green foilage.\n");

    add_item("window", VBFC_ME("window_desc"));

    add_prop(OBJ_S_SEARCH_FUN, "search_bushes");

    add_cmd_item("window", "enter", VBFC_ME("do_enter"));
}

string
search_bushes(object player, string what)
{
    object feather;

    if(!member_array(what, ({ "east bushes", "eastern bushes",
				  "east bush", "eastern bush"})))
    	return "Your search reveals nothing special.\n";
    if(query_searched())
    	return "Your search reveals nothing special.\n";
    seteuid(getuid());
    feather = clone_object(LEAH_DIR + "obj/eagle_feather");
    feather->move(player);
    set_searched(1);
    return "You find a feather in the bushes!\n";
}

string window_desc()
{
	if(window)
	  {
		return "The window is openened, letting the nice warm breeze "+
			"enter the house.\n";
	  }
	return "The window is opened about a fingerswidth, letting a "+
		"hint of a warm breeze into the house.\n";
}

int set_window(int i)
{
	window = i;
	return 1;
}

int query_sickness()
{
	return sickness;
}

int set_sickness(int a)
{
	sickness = a;
}

int do_open(string str)
{
	NF("Open what?\n");
	if(str != "window")
		return 0;
	window = outside_room->query_window();
	NF("But the window is already opened!\n");
	if(window)
		return 0;
	NF("The window seems stuck!\n");
	if(!outside_room->set_window(1))
		return 0;
	window = 1;
	TP->catch_msg("You slide the window open and feel the warm "+
		"breeze buffet against your face.\n");
	tell_room(outside_room, "The window suddenly slides open!\n");
	return 1;	
}

int do_close(string str)
{
	NF("Close what?\n");
	if(str != "window")
		return 0;
	window = outside_room->query_window();
	NF("But the window is already closed! You can't seem to get it "+
		"the last fingerwidth closed.\n");
	if(!window)
		return 0;
	NF("The window seems stuck open!\n");
	if(!outside_room->set_window(0))
	return 0;
	window = 0;
	TP->catch_msg("You slide the window closed and feel the warm "+
		"breeze stop.\n");
	tell_room(outside_room, "The window suddenly closes!\n");
	return 1;	
}

string do_enter()
{
	NF("But the window is closed! You can't fit through that small "+
		"of an opening!\n");
	window = outside_room->query_window();
	if(!window)
		return 0;
	TP->catch_msg("You climb through the window.\n");
	set_dircmd("window");
	TP->move_living("through the window", LEAH_DIR + "house2-bedroom",
		0, 0);
	return "";	
}

init()
{
	add_action("do_open", "open");
	add_action("do_close", "close");
	::init();
}
