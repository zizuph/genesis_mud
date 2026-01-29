#include "defs.h"
#include <stdproperties.h>
#include <composite.h>

inherit "/std/object";

#define ORC_LAIR (MINES_DIR + "orc_lair")

create_object()
{
    set_name("brooch");
    add_name("moria");
    set_short("brooch of Moria");
    set_long("@@my_long@@");
    add_prop(OBJ_S_WIZINFO,
	     "This is a brooch of control. It makes you able to " +
	     "shortcut many calls into the delicate mechanics of " +
	     "the Mines of Moria. Examine it, and you'll find the " +
	     "commands of Power.\n");
    add_prop(OBJ_M_NO_SELL, "Sell the Brooch of Control?\n");
    add_prop(OBJ_M_NO_GET, "@@wiz_check");
}

int wiz_check()
{
    return ETO && ETO->query_wiz_level();
}

init()
{
    ::init();
    if (!ETO || !ETO->query_wiz_level())
	return;
    FIXEUID;
    add_action("do_inside", "inside");
    add_action("do_start",  "start");
    add_action("do_messages", "messages");
    add_action("do_moria",  "moria");
    add_action("do_darkvis", "darkvis");
    add_action("do_place",  "place");
    add_action("do_place",  "++");
    add_action("do_dist",   "dist");
    add_action("do_dist",   "??");
}

string
query_autoload()
{
    if (!ETO->query_wiz_level())
	return 0;
    else
	return "#wiz_msg:" + ETO->query_prop("_moria_i_wiz_message") + "#";
}

void
init_arg(string what)
{
    int msg, dummy1, dummy2;
    sscanf(what, "%s#wiz_msg:%d#", dummy1, msg, dummy2);
    ETO->add_prop("_moria_i_wiz_message", msg);
}

string 
my_long()
{
    if (!TP->query_wiz_level()) {
    TO->remove_object();
	return ("This is a brooch.\n");
    }
    return "You are looking at the Brooch of Moria.\n" +
	"Commands:\n" +
	"inside moria         : Are there players within Moria?\n"+
/*	"start orc/captain    : Starts orc or the captain.\n" + */
	"messages on/off      : Enables or disables message passing.\n" +
	"moria start          : Teleports to the start of Moria.\n" +
	"moria dump           : Dumps the soldiers within Moria.\n" +
	"darkvis              : Darkvision.\n" +
	"place <ns> <ew> <ud> : (++) Places this room with coordinates.\n" +
	"dist                 : (??) Lists the distances to adjacent rooms.\n" +
	"\n\n" +
	"NOTE: Starting orcs and captain is logged, and is illegal!\n";
}

string name(object w) { return w->query_name(); }

int
do_inside(string arg)
{
    object *u;
    notify_fail("Inside where? Moria perhaps?\n");
    if (arg == "moria") {
	u = filter(users(), "inside_moria", CONTROL);
	if (!sizeof(u)) {
	    write("No player is inside Moria.\n");
	    return 1;
	} else {
	    write("Inside: " + COMPOSITE_LIVE(u)+".\n");
	    return 1;
	}
    } 
    return 0;
}

/*
int
do_start(string arg)
{
    if (arg == "orc" || arg == "soldier" || arg == "orc soldier") {
	write(ORC_LAIR->create_soldier());
	return 1;
    } else if (arg == "bolg" || arg == "captain" || arg == "urukcap") {
	write(ORC_LAIR->start_captain());
	return 1;
    }
    return notify_fail("Start orc or captain?\n");
}
*/

int
do_messages(string arg)
{
    if (arg == "on") {
	TP->add_prop("_moria_i_wiz_message", 1);
	write("Messages turned on.\n");
	return 1;
    } else if (arg == "off") {
	TP->remove_prop("_moria_i_wiz_message", 0);
	write("Messages turned off.\n");
	return 1;
    } else if (arg == "log on" || arg == "log") {
	CONTROL->enable_logging(TP);
	write("Logging messages in /d/Shire/moria/log/messages\n");
	return 1;
    } else if (arg == "log off") {
	CONTROL->disable_logging(TP);
	write("Logging messages disabled.\n");
	return 1;
    } else 
	return notify_fail("Message on|off|log on|log off\n");
}

int
do_moria(string arg)
{
    if (arg == "start") {
	TP->add_prop(LIVE_O_LAST_ROOM, "/d/Shire/common/hollin/under_wall"); 
	TP->move_living("X", MINES_DIR + "stair0");
	return 1;
    } else if (arg == "soldiers" || arg == "dump") {
	write(ORC_LAIR->dump_soldiers());
	return 1;
    } else 
	return notify_fail("Eh? moria dump|start\n");
}

int
do_darkvis(string arg)
{
    if (!strlen(arg) || arg == "on") {
	TP->add_prop(LIVE_I_SEE_DARK, TP->query_prop(LIVE_I_SEE_DARK) + 1);
	write("Ok. Darkvision now at: " + TP->query_prop(LIVE_I_SEE_DARK) +
	      "\n");
	return 1;
    } else if (arg == "off") {
	TP->add_prop(LIVE_I_SEE_DARK, 0);
	write("Ok, no dark vision ability.\n");
	return 1;
    }
}

int
do_place(string arg)
{
    int ns, ew, ud;
    mixed *pos;

    if (TP->query_name() != "Varian")
	return notify_fail("Unauthorized use.\n");

    if (!strlen(arg) || arg == "?") {
	pos = CONTROL->room_position(ETP);
	if (!sizeof(pos)) 
	    return notify_fail(sprintf("What? pos = %O\n", pos));

	write(sprintf("Pos data: %d %d %d", pos[0], pos[1], pos[2]));

	if (sizeof(pos)==4)
	    write(pos[3]);

	write("\n");
	return 1;
    }

    if (sscanf(arg, "%d %d %d", ns, ew, ud) == 3) {
	CONTROL->add_data(ETP, ns, ew, ud);
	write("Ok.\n");
	return 1;
    } else if (sscanf(arg, "%d %d %d hide", ns, ew, ud)==3) {
	CONTROL->add_data(ETP, ns, ew, ud, "hide");
	write("Ok [hidden].\n");
	return 1;
    } else
	return notify_fail("Syntax: + <ns> <ew> <ud> [hide]\n");
}

int
do_dist()
{
    CONTROL->find_dist(ETP);
    return 1;
}
