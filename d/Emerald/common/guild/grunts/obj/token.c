/* A smelly little token. Coded on 24/01/2000 by Tulix V.                  */
/* This particular object will allow Grunts to join the guild, even when   */
/* the domain is closed.                                                   */
/* This object will become obsolete when Emerald re-opens.                 */

/* Note - this file does not use the usual guild.h, as a fail-safe.        */

inherit "/lib/guild_support";
inherit "/std/object";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "../guild_backup.h"

#define NF(x)         notify_fail(x)
#define TP            this_player()

#pragma strict_types

/* Prototype functions */
public int join(string str);
public int my_leave(string str);

public void
create_object()
{
    set_name("token");
    set_pname("tokens");
    set_adj("smelly");

    set_short("smelly little token");
    set_pshort("smelly little tokens");
    set_long("This token is a symbol of the Grunts guild. It allows " +
        "potential members to join and leave, even when the caves " +
        "are not accessible.\n" +
        "To join the Grunts guild, the command is <want to smell>.\n " +
        "To leave the Grunts guild, the command is <hate the smell>.\n" +
        "This token will disappear when the caves are accessible.\n");

    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_WEIGHT, 2);
    add_prop(OBJ_I_VALUE,  0);
    add_prop(OBJ_M_NO_SELL, "You can't see why anyone would buy this.\n");

    add_prop(MAGIC_AM_ID_INFO, ({ 
        "The token is not magical at all!\n", 0,
        "The token is a piece of crap!\n", 20,
        "You just wasted a perfectly good spell.\n", 40,
        "The token is about as magical as a non-magical thing.\n", 80 }) );
    
    add_prop(OBJ_S_WIZINFO, "This token is a temporary measure until the " +
        "Emerald domain is opened again.\nUntil then, you can only join " +
        "or leave using this token.\nAsk Tulix for more details.\n");

}

/*
 * Function name:   enter_env
 * Description:     called when this object enters a new environment
 * Arguments:       env: destination environment
 *                  old: previous environment
 */
public void
enter_env(object env, object old)
{
    ::enter_env(env, old);
    
    if (interactive(env))
    {
        if ((env->query_race_name() != "goblin") && !(env->query_wiz_level()))
        {
            env->catch_msg("The token crumbles to dust.\n");
            this_object()->remove_object();
        }
    }
    
    return;
}

/*
 * Function name:   init
 * Description:     add commands to all players who carry the token
 */
public void
init()
{
    ::init();

    add_action( join,     "want"  );
    add_action( my_leave, "hate"  );
}

/*
 * Function name:   join
 * Description:     see if player is fit to join guild, and make them a member
 * Arguments:       str: string containing the rest of the 'join' command
 * Returns:         1 if command successful, 0 if not.
 */
public int
join(string str)
{
    mixed why;
    object shadow;
 
    /* Verify that the player used the correct command to join */
    if (str!="to smell")
    {
	NF("Want to what? Smell perhaps?\n");
	return 0;
    }

    /* Check to see if the player already belongs to a race guild */
    if (TP->query_guild_member(GUILD_TYPE))
    {
	write("Tsk! Tsk! No way you can join two race guilds.\n");
	return 1;
    }
    
    setuid();
    seteuid(getuid());

    /* We should now be able to add the guild shadow successfully */
    shadow = clone_object(GUILD_SHADOW);

    if (stringp(why = shadow->acceptable_grunts_member(this_player())))
    {
        write(why);
        shadow->remove_shadow();
        return 1;
    }

    if (shadow->add_grunts_shadow(this_player()) != 1)
    {
	shadow->remove_shadow();
        write("Could not make you a member for some reason.\n");
	return 1;
    }

    write("Ok.\n");    
    return 1;
}
 
/*
 * Function name:   my_leave
 * Description:     remove player from the guild
 * Arguments:       str: string containing the rest of the 'leave' command
 * Returns:         1 if command successful, 0 if not.
 */
public int
my_leave(string str)
{
    /* Verify that the player used the correct command to leave */
    if (str!="the smell")
    {
	NF("What do you hate? The smell perhaps?\n");
	return 0;
    }
 
    /* Check to see if the player belongs to the Grunts guild */
    if (TP->query_guild_name_race() != GUILD_NAME)
    {
	NF("You can't leave a guild you are not a member of.\n");
	return 0;
    }
    
    this_player()->remove_grunts_member();
    write("Ok.\n");
    return 1;
}

