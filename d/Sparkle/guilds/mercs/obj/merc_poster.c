/*
 * /d/Genesis/guilds/merc/obj/merc_poster.c, by Morrigan 12 July, 2002
 * 
 * This object is for placement around the realms, to allow
 *    mercenaries to make themselves available for hire, and
 *    for other players to be able to see who is available.
 *
 */

inherit "/std/object";

#include "../merc.h"
#include <stdproperties.h>
#include <composite.h>
#include <macros.h>

public void create_object()
{
    set_name("poster");
    set_short("poster nailed to the wall");
    set_pshort("posters nailed to the wall");
    set_long("@@long_desc");
    add_cmd_item("poster", "read", "@@long_desc");
    add_prop(OBJ_M_NO_GET, "The poster cannot be taken.\n");

    /* Well, this guild is currently closed, and it seems that this poster
     * has been added to certain rooms around the realm. I'm not sure which
     * rooms those are, so the following seems like the easiest solution
     * for now. (Gorboth)
     */
    set_no_show_composite(1);
    set_alarm(0.0, 0.0, remove_object);
}

public string long_desc()
{
    string names, merc_message, *list;

    /* Make sure the join room is loaded */
    MJOIN->teleledningsanka();

    list = MJOIN->update_hirelist();

    if (sizeof(list) == 0)
        names = "No names have been written on the poster yet.";
   else if (sizeof(list) == 1)
        names = "The name "+COMPOSITE_WORDS(list)+" has been "+
            "written in ink below.";
   else
        names = "The names "+COMPOSITE_WORDS(list)+" have been "+
            "written in ink below.";

    merc_message = (IS_MERC(this_player()) ? "You may 'sign' or 'erase' "+
        "your name on the poster.\n" : "");

    return "The image of a black dragon covers the poster, over " +
        "which is written: Maligant's Mercenaries for Hire. " +
        names+"\n" + merc_message;
}

public int add_name(string str)
{
    string name, *list, verb = query_verb();
    object merc = this_player();

    /* Make sure the join room is loaded */
    MJOIN->teleledningsanka();

    list = MJOIN->update_hirelist();

    notify_fail("What?\n");
    if (!IS_MERC(merc))
	return 0;

    name = merc->query_name();

    notify_fail("You can only "+verb+" your name "+
	"to the poster.\n");
    if (str != "name" && str != name && str != lower_case(name))
        return 0;

    notify_fail("Your name is already on the list, you need not "+
        verb+" it again.\n");
    if (member_array(name, list) != -1)
        return 0;

    MJOIN->add_hirelist(name);
    merc->catch_msg("You "+verb+" your name on the poster "+
        "in order to notify others that you are available for hire.\n");
    tell_room(environment(merc), QCTNAME(merc)+" "+verb+
	"s "+merc->query_possessive()+" name on the poster.\n", merc);
    return 1;
}

public int remove_name(string str)
{
    string name, *list, verb = query_verb();
    object merc = this_player();

    /* Make sure the join room is loaded */
    MJOIN->teleledningsanka();

    list = MJOIN->update_hirelist();

    notify_fail("What?\n");
    if (!IS_MERC(merc))
	return 0;

    name = merc->query_name();

    notify_fail("You can only "+verb+" your name "+
	"from the poster.\n");
    if (str != "name" && str != name && str != lower_case(name))
        return 0;

    notify_fail("Your name is not on the list, therefore you cannot "+
        verb+" it.\n");
    if (member_array(name, list) == -1)
        return 0;

    MJOIN->remove_hirelist(name);
    merc->catch_msg("You "+verb+" your name from the poster, "+
        "as you are no longer available to be hired.\n");
    tell_room(environment(merc), QCTNAME(merc)+" "+verb+
	"s "+merc->query_possessive()+" name from the poster.\n", merc);
    return 1;
}


public void init()
{
    ::init();

    add_action("add_name", "sign");
    add_action("add_name", "write");
    add_action("remove_name", "erase");
}
