inherit "/std/room";
#define TCASTLE_DIR "/d/Emerald/telseron/towncastle"
 
#include "/d/Emerald/defs.h"
#include <filter_funs.h>
#include <composite.h>
#include <macros.h>
 
#define	IS_LIEING	"_player_i_is_lying"
#define	LIE_SUBLOC	"subloc_lying"

#define SOUTH_ROOM      (TCASTLE_DIR + "passage")
#include <options.h>

int do_lie(string arg);
int do_rise(string arg);
int do_emote(string arg);

void
create_room()
{
    set_short("Large bedroom");
    set_long( "You are in a rather large, pleasant-looking "+
	     "bedroom. A dark passageway leads to the south.\n" );
 
    add_prop(ROOM_I_INSIDE, 1);
 
    add_item("bed", "@@bed_desc2@@");
    add_item("under bed",  "You can't seem to find a way to "+
             "look there, as the bed extends all "+
             "the way to the floor.\n");
 
    add_my_desc("@@bed_desc@@", this_object());
 
    add_exit(SOUTH_ROOM, "south");

    setuid();
    seteuid(getuid());
}
 
void
leave_inv(object ob, mixed to)
{
    ::leave_inv(ob, to);
    if (ob->query_prop(IS_LIEING))
    {
	ob->remove_prop(IS_LIEING);
	ob->unset_no_show_composite();
	ob->remove_subloc(LIE_SUBLOC);
    }
}
 
void
init()
{
    ::init();

    /* Invisible and hidden people should not be here. */
    if (this_player()->query_prop(OBJ_I_INVIS) ||
	this_player()->query_prop(OBJ_I_HIDE))
    {
	write("You walk out of the room again being invisible to some.\n");
	this_player()->move(SOUTH_ROOM, 1);

	if (environment(this_player()) == this_object())
	{
	    write("Being persistant?\n");
	    this_player()->remove_object();
	}
	return;
    }

    add_action(do_lie, "lie");
    add_action(do_lie, "enter");
    add_action(do_rise, "rise");
    add_action(do_emote, "emote");
    add_action(do_emote, ":");
}

int
do_lie(string arg)
{
    notify_fail(capitalize(query_verb()) + " what?\n");
    if (query_verb() == "lie" && arg != "in bed" && arg != "on bed")
	return 0;
    else if (query_verb() == "enter" && arg != "bed")
	return 0;
    notify_fail("But you ARE in the bed!\n");
    if (this_player()->query_prop(IS_LIEING))
	return 0;
    this_player()->add_prop(IS_LIEING, 1);
    this_player()->set_no_show_composite(1);
    this_player()->add_subloc(LIE_SUBLOC, this_object());
    write("You crawl onto the bed and lie down.\n");
    say(QCTNAME(this_player()) + " crawls onto the bed and lies down.\n");
    return 1;
}
 
int
do_rise(string arg)
{
    notify_fail("Rise what?\n");
    if (arg && arg != "from bed")
	return 0;
    notify_fail("But you aren't IN the bed!\n");
    if (!this_player()->query_prop(IS_LIEING))
	return 0;
    this_player()->remove_prop(IS_LIEING);
    this_player()->unset_no_show_composite();
    this_player()->remove_subloc(LIE_SUBLOC);
    write("You get up from the bed.\n");
    say(QCTNAME(this_player()) + " climbs out of the bed.\n");
    return 1;
}
 
int
filter_lying(object ob)
{
    return ob->query_prop(IS_LIEING);
}
 
int
filter_remove_lie(object ob)
{
    ob->unset_no_show_composite();
    return 1;
}
 
int
filter_add_lie(object ob)
{
    ob->set_no_show_composite(1);
}
 
string
bed_desc()
{
    object *obs;
    string str;
 
    obs = FILTER_OTHER_LIVE(all_inventory());
    obs = filter(obs, filter_lying);
    filter(obs, filter_remove_lie);
    str = "There is a huge bed standing in the middle of the room.";
    if (sizeof(obs) > 1)
	str += " " + COMPOSITE_LIVE(obs) + " are lying in it.";
    else if (sizeof(obs))
	str += " " + COMPOSITE_LIVE(obs) + " is lying in it.";
    str += "\n";
    filter(obs, filter_add_lie);
    return str;
}
 
string
bed_desc2()
{
    object *obs;
    string str;
 
    obs = FILTER_OTHER_LIVE(all_inventory());
    obs = filter(obs, filter_lying);
    filter(obs, filter_remove_lie);
    str = "It is a HUGE bed!";
    if (sizeof(obs) > 1)
	str += " " + COMPOSITE_LIVE(obs) + " are lying in it.";
    else if (sizeof(obs))
	str += " " + COMPOSITE_LIVE(obs) + " is lying in it.";
    str += "\n";
    filter(obs, filter_add_lie);
    return str;
}
 
nomask string
show_subloc(string subloc, object on, object for_ob)
{
    string str;
 
    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) ||
	subloc != LIE_SUBLOC)
	return "";
    if (for_ob == on)
	str = "You are";
    else
	str = capitalize(on->query_pronoun()) + " is";
    return str + " lying in the huge bed.\n";
}
 
int
do_emote(string arg)
{
    notify_fail("Emote what?\n");
    if (!arg)
	return 0;
    say(QCTNAME(this_player()) + " " + arg + "\n");
    if (this_player()->query_option(OPT_ECHO))
	write("You emote: " + this_player()->query_name() + " " + arg + "\n");
    else
	write("Ok.\n");
    return 1;
}

/*
 * Function name: query_prevent_snoop
 * Description  : This function will prevent mortals from being snooped in
 *                this room by most wizards.
 * Returns      : int 1 - always.
 */
int
query_prevent_snoop()
{
    return 1;
}
