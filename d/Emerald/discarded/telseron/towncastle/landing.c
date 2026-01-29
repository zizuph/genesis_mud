inherit "/std/room";
 
#include "default.h"
#include <macros.h>

int panel_open;

int do_enter(string arg);

void
reset_room()
{
    tell_room(this_object(), "The panel slams shut!\n");
    panel_open = 0;
}
 
void
create_room()
{
    set_short("Landing");
    set_long( "The landing is quite small. There is a panel on "+
	     "one of the walls you might enter and a ladder is leading down "+
	     "to something that looks like a passage.\n" );
 
    add_item("panel", "@@panel_desc@@");
    add_item("ladder", "It is made of wood and bolted to the wall.\n");
 
    add_cmd_item("panel", "open", "@@open_panel@@");
    add_cmd_item("panel", "close", "@@close_panel@@");
 
    add_prop(ROOM_I_INSIDE, 1);
 
    add_exit(TCASTLE_DIR + "passage_s", "down", 0);
}
 
string
open_panel()
{
    if (panel_open)
	return "But it is open!\n";
    panel_open = 1;
    say(QCTNAME(this_player()) + " opens the panel.\n");
    return "You open the panel.\n";
}
 
string
close_panel()
{
    if (!panel_open)
	return "But it is closed!\n";
    panel_open = 0;
    say(QCTNAME(this_player()) + " closes the panel.\n");
    return "You close the panel.\n";
}
 
string
panel_desc()
{
    if (panel_open)
	return "It is open, you can enter it.\n";
    return "It looks like you might be able open it.\n";
}
 
void
init()
{
    ::init();
    add_action(do_enter, "enter", 0);
}
 
int
do_enter(string arg)
{
    notify_fail("Enter what?\n");
    if (arg != "panel")
	return 0;
    notify_fail("The panel is closed.\n");
    if (!panel_open)
	return 0;
    set_dircmd(arg);
    write("As you enter the panel, it closes behind you.\n");
    this_player()->move_living("entering the panel", TCASTLE_DIR + "bedroom");
    write("There are no trace of the panel on this side.\n");
    tell_room(this_object(), "As " + QTNAME(this_player()) + " enters the "+
	      "panel, it closes behind " + this_player()->query_pronoun() +
	      ".\n");
    panel_open = 0;
    return 1;
}
