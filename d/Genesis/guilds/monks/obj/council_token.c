/*
 * File:     council_token.c
 * Created:  Cirion, 1999.03.02
 * Purpose:  Token which council members may bestow upon a
 *           worthy player. They can only give one away once
 *           every month.
 * Log:
 *
 */
#pragma strict_types
#pragma save_binary

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

inherit "/std/object";
inherit "/lib/wearable_item";
inherit MONKLIB;

private string    council_member;
private string    for_who;

varargs void
remove_token(string str = "unknown reason")
{
    if(environment(this_object())->query_wiz_level())
        environment(this_object())->catch_tell(" --- Removing monk council "
            + "because: " + str + "\n");

    m_log ("Council token (" + query_short () + ", " + query_long ()
        + ") from " + environment (this_object ())->query_name ()
        + " because: " + str);

    remove_object();
}

void
config_council_token(string who)
{
    mixed      info;
    string    *parts;
    int        i;
    string     adj;
    int        location;
    string     short_desc;
    string     long_desc;

    info = MANAGER->get_council_info(who);

    council_member = who;

    add_prop(OBJ_S_WIZINFO, "This object is a trinket that a "
        + "monk council member may create and configure and "
        + "bestow upon another player. The council member that "
        + "created this object was: "
        + capitalize(council_member) + "\n");

    if(!pointerp(info))
    {
        set_alarm(1.0, 0.0, &remove_token("get_council_token(" + who + ") "
            + "returned null"));
        return;
    }

    if((sizeof(info) < 4))
    {
        set_alarm(1.0, 0.0, &remove_token("get_council_token(" + who + ") "
            + "returned invalid array (size=" + sizeof(info) + ")"));
        return;
    }

    if(info[1] == MONK_TOKEN_NONE)
    {
        set_alarm(1.0, 0.0, &remove_token("token was revoked"));
        return;
    }

    location = info[0];
    short_desc = info[1];
    long_desc = info[2];

    set_short(short_desc);
    set_long(long_desc + "\n");


    // get adjectives from the short desc. E.g.,
    // "thin, golden necklace" -> ({ "thin", "golden" })
    parts = explode(short_desc, " ");
    set_name(parts[sizeof(parts)-1]);
    add_name("_token_" + who);

    for(i = 0; i < sizeof(parts) - 1; i++)
    {
        adj = parts[i];
        sscanf(adj, "%s,", adj); // parse out trailing ,
        add_adj(adj);
    }

    config_wearable_item(location, 1, 1, this_object());

}

void
move_config(object to_who, string council_name)
{
    config_council_token(council_name);
    move(to_who, 1);
}

void
create_object ()
{
    set_name("_token");
    add_name(({"token"}));

    // add the file name as a name for easy use with present()
    add_name(MASTER_OB(this_object()));

    // we really can only guess at plausable weight and volume
    // for the object
    add_prop(OBJ_I_VALUE,    0);
    add_prop(OBJ_I_WEIGHT,  750);
    add_prop(OBJ_I_VOLUME,  750);

    add_prop (OBJ_M_NO_DROP, "You would not want to leave it "
        + "lying around. You can 'destroy' it if you no longer "
        + "want it.\n");
}


void
leave_env(object from, object to)
{
    wearable_item_leave_env(from, to);
    ::leave_env(from, to);
}

void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    // if we came from nowhere, we must have been
    // cloned into the person.
    if(living(to) && !from)
        for_who = to->query_real_name();
}

/*
 * Function name: query_auto_load
 * Description:   This object is auto-loading. Save the council
 *                member in the autoload string so the whole thing
 *                can recover.
 * Returns:       string - the auto-load string.
 */
string
query_auto_load()
{
    object who = environment(this_object());

    // only autoload for the person to whom it was given, or
    // wizards.
    if(who->query_wiz_level() || (who->query_real_name() == for_who))
        return MASTER + ":" + council_member;
    else
        return 0;
}

/* 
 * Function name: init_arg
 * Description:   Called when autoloading. This will get the name
 *                of the council member so we can query the
 *                MANAGER for the rest of the information.
 * Arguments:     string arg - the auto-load argument.
 */
void
init_arg(string arg)
{
    string who;

    who = arg;

    if(who)
        config_council_token(who);
    else
        {
        set_alarm(1.0, 0.0, &remove_token("council token init_arg() was null"));
        }
}


void
appraise_object(int num)
{
    ::appraise_object(num);
    write("This token was given by " + capitalize(council_member) + ".\n");
    appraise_wearable_item();
}


public int do_destroy (string arg)
{
    string prop = "_live_o_destroy_do_token";
    object tp = this_player ();
    object ob;

    if (!strlen (arg) || 
        parse_command (arg, environment (), "[the] %o", ob) != 1 ||
        ob != this_object ())
    {
        notify_fail ("Destroy what? The " + short () + "?\n");
        return 0;
    }
    
    if (tp->query_prop (prop) != this_object ())
    {
        tp->add_prop (prop, this_object ());
        write ("Destroy the " + short (tp) + " forever? Type the "
            + "command again the really do it.\n");
        return 1;
    }

    write ("You destroy the " + short (tp) + " forever.\n");
    remove_token (tp->query_name () + " voluntarily destroyed it");
    return 1;
}


public void init ()
{
    ::init ();
    add_action (do_destroy, "destroy");
}

