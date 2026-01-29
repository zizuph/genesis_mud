/*
 * /d/Genesis/guilds/merc/obj/message_object, by Morrigan 10/2002
 *
 * This autoloading object stores the default strings for use by the 
 *     mhail, mfarewell, and mkill emotes, and assigns them to props
 *     for use by mercenaries.
 */

#pragma save binary

inherit "/std/object";

#include "/d/Krynn/common/defs.h"
#include "../merc.h"
#include <macros.h>
#include <stdproperties.h>

void do_stuff();

string Mhail_message, Mfare_message, Mkill_message;

create_object()
{
    set_name("merc message object");
    add_name(MESSAGE_OBJECT_NAME);
    set_short(MESSAGE_OBJECT_NAME);
    set_long("The merc message object should not be visible.");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);

    set_no_show(1);
}

init()
{
    set_alarm(0.5, 0.0, "do_stuff");

    ::init();
}

string
query_auto_load()
{
    object owner = E(TO);
    string tmp;

    /* Blank out any current variable values */
    Mkill_message = "none";
    Mhail_message = "none";
    Mfare_message = "none";

    /* Get the current default messages from the props */
    if (strlen(tmp = owner->query_prop(MERC_S_DEFAULT_BATTLECRY)))
        Mkill_message = tmp;

    if (strlen(tmp = owner->query_prop(MERC_S_DEFAULT_HAIL)))
        Mhail_message = tmp;

    if (strlen(tmp = owner->query_prop(MERC_S_DEFAULT_FAREWELL)))
        Mfare_message = tmp;

    /* Don't autoload if no default messages are set */
    if (Mkill_message == "none" &&
	Mhail_message == "none" &&
	Mfare_message == "none")
	return "";

    return MASTER_OB(this_object()) + ":" + Mhail_message + "|" +
	Mfare_message + "|" + Mkill_message;
}

void
init_arg(string str)
{
    int i = sscanf(str, "%s|%s|%s", Mhail_message, Mfare_message, Mkill_message);
}

void do_stuff()
{
    object owner = E(TO);

    /* If there are no messages set, remove this object */
    if (Mkill_message == "none" &&
	Mhail_message == "none" &&
	Mfare_message == "none")
    {
        remove_object();
	return;
    }

    if (strlen(Mhail_message))
        owner->add_prop(MERC_S_DEFAULT_HAIL, Mhail_message);

    if (strlen(Mfare_message))
        owner->add_prop(MERC_S_DEFAULT_FAREWELL, Mfare_message);

    if (strlen(Mkill_message))
        owner->add_prop(MERC_S_DEFAULT_BATTLECRY, Mkill_message);

    return;
}

/*
 * Function   : enter_env
 * Description: merges duplicate items, happens sometimes.
 */
public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    remove_name("_merc_message_object_");

    if (present("_merc_message_object_", ENV(TO)))
    {
        set_alarm(1.0,0.0, &remove_object());
	    return;
    }

    add_name("_merc_message_object_");
}