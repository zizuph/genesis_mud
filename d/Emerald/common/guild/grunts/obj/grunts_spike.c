/* A spike. Coded on 28/01/2000 by Tulix V.                                */
/* This particular object will allow Grunts to join the guild, even when   */
/* the domain is closed.                                                   */

inherit "/lib/guild_support";
inherit "/std/object";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "../guild.h"

/* Define the default warcry given to the grunts */
#define DEFAULT_WARCRY   "GrUntz rOol!!!"
#define NF(x)            notify_fail(x)
#define TP               this_player()

#define BUGGY            0

#pragma strict_types

/* Global variables to be saved */
public string *recruits; /* A list of all Grunts recruited by this Grunt */
public string *heritage; /* The order in which grunts were recruited */
public string warcry;    /* Warcry to shout at your enemies */
static string recruiter; /* We don't want to save this variable */

/* Prototype functions */
public int join(string str);
public void set_recruiting_grunt(object grunt);
public void tidy_up();

public void
create_object()
{
    set_name("spike");
    set_pname("spikes");
    set_adj("smelly");

    set_short("smelly little spike");
    set_pshort("smelly little spikes");
    set_long("This spike is a symbol of the Grunts guild. It allows " +
        "potential members to join and leave, even when the caves " +
        "are not accessible.\n" +
        "To join the Grunts guild, the command is <want to smell>.\n");

    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_WEIGHT, 2);
    add_prop(OBJ_I_VALUE,  0);
    add_prop(OBJ_M_NO_DROP, "You'd better hang on to this.\n");
    add_prop(OBJ_M_NO_SELL, "You can't see why anyone would buy this.\n");

    add_prop(MAGIC_AM_ID_INFO, ({ 
        "The spike is not magical at all!\n", 0,
        "The spike is a piece of crap!\n", 20,
        "You just wasted a perfectly good spell.\n", 40,
        "The spike is about as magical as a non-magical thing.\n", 80 }) );
    
    add_prop(OBJ_S_WIZINFO, "This spike allows Grunts to recruit others. " +
        "Ask Tulix for more details.\n");

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


    if (BUGGY)
        write("Shadow added...\n");

    /* Need to account for 1st generation grunts with no warcry saved */
    if (file_size(GRUNTS_WARCRY_DIR + recruiter + ".o")>=6)
    {
        restore_object( GRUNTS_WARCRY_DIR + recruiter );
        if (BUGGY)
            write("Recruiter file restored...\n");
    }
    else
    {
        warcry = DEFAULT_WARCRY;
        if (BUGGY)
            write("Warcry variable set to default (" + warcry + ")...\n");
    }

    if ( sizeof(recruits) == 0 )
    {
        recruits = ({ this_player()->query_name() });
        if (BUGGY)
            write("Recruits variable created...\n");
    }
    else
    {
        recruits += ({ this_player()->query_name() });
        if (BUGGY)
            write("Recruits variable appended with new recruit...\n");
    }

    if ( sizeof(heritage) == 0 )
    {
        heritage = ({ });
        if (BUGGY)
            write("Heritage variable created for recruiter...\n");
    }
    
    /* Save the recriters new recruitment list */
    save_object ( GRUNTS_WARCRY_DIR + recruiter );
    if (BUGGY)
        write("Recruiter file saved...\n");

    /* New recruits do not get the recruit list of their recruiter */
    recruits = ({ });

    if ( sizeof(heritage) == 0 )
    {
        heritage = ({ recruiter });
        if (BUGGY)
            write("Heritage variable created for recruit...\n");
    }
    else
    {
        heritage += ({ recruiter });
        if (BUGGY)
            write("Heritage variable appended for recruit...\n");
    }

    /* Save the new recruit's heritage (and blank recruit list) */
    save_object( GRUNTS_WARCRY_DIR + this_player()->query_real_name() );
    if (BUGGY)
        write("Recruit file saved...\n");

    write("Ok.\n");    
    set_alarm( 2.0, 0.0, tidy_up );
    return 1;
}
 
public void
set_recruiting_grunt(object grunt)
{
    recruiter = grunt->query_real_name();
}

public void
tidy_up()
{
    object grunt;

    grunt = environment(this_object());

    if (interactive(grunt))
        grunt->catch_msg("The spike goes back to it's owner's collar.\n");

    remove_object();
}
