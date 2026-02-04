 
inherit "/std/guild/guild_lay_sh";
inherit "/lib/commands";

#include "../guild.h"

#include "options.c"
#include "blood.c"
#include "drain.c"
#include "titles.c"

#include <tasks.h>     /* For difficulty and stat defines */
#include <ss_types.h>  /* For skill defines */
#include <stdproperties.h> /* For standard properties */
#include <macros.h> /* For macros */
#include <filter_funs.h> /* For easy filters */

#define BG_SUBLOC  "_bg_subloc"

public nomask object query_manager()
{
    setuid();
    seteuid(geteuid());
    LOAD_ERR(LAY_MANAGER);
    return find_object(LAY_MANAGER);
}

object
query_bg_shadow()
{
    return this_object();
}


public string
query_guild_name_lay()
{
    return LAY_GUILD_NAME;
}

public string
query_guild_style_lay()
{
    return LAY_GUILD_STYLE;
}

public int
query_guild_not_allow_join_lay(object player, string type, string style,
			       string name)
{
    if (::query_guild_not_allow_join_lay(player, type, style, name))
    {
        return 1;
    }
    if (player->query_prop(LIVE_I_UNDEAD))
    {
        write("Being undead and having fangs is the sole " 
        + "priviledge of the full vampire.\n");
        return 1;
    }
    return 0;
}

mixed
query_guild_trainer_lay()
{
    return ({ 
            LIB_DIR+"lay_train",
           });
}

/*
 * Function name: query_guild_title_lay
 * Description:   This is called to get the guild title for introductions
 *                and such.
 * Returns:       The title.
 */
string
query_guild_title_lay()
{
    /* Update the title on occasion in case the vampire has gained a level
     * recently.
     */
    if (!random(30))
    {
        update_title();
    }

	if (query_vamp_option(VOPT_INTRO_TITLE))
	{
	    if (query_vamp_option(VOPT_INTRO_PTITLE))
	    {
		return query_full_vamp_title();
	    }
    
 	    return query_vamp_title();
	}
    
	if (query_vamp_option(VOPT_INTRO_PTITLE))
	{
	    return query_personal_title();
	}

    return "";
}


public int 
query_guild_incognito_lay()
{
    if (query_vamp_option(VOPT_INTRO_TITLE))
    {
        return 0;
    }
    if (query_vamp_option(VOPT_INTRO_PTITLE))
    {
        return 0;
    }
    return 1;
}

public string query_master()
{
    return query_manager()->query_master(QSW);
}

public int
query_guild_tax_lay()
{
    return LAY_GUILD_TAX;
}

public int query_base_vamp_stat()
{
    return QSW->query_stat(SS_LAYMAN);
}

public int query_vamp_stat()
{
    return query_base_vamp_stat()
    -query_blood_modifier();
}


public int query_bloodguard()
{
    return 1;
}

public string show_subloc(string subloc, object on, object for_obj)
{
    if (subloc==BG_SUBLOC)
    {
        if (for_obj->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	        return on->show_subloc(subloc, on, for_obj);

        if (IS_VAMP(for_obj) || on==for_obj ||
        (IS_BG(for_obj) && !query_guild_incognito_lay()))
        {
            string result=
            (for_obj==on ? "You are " : capitalize(PRO(on)) + " is ");
            if (!query_master())
            {
                return result+"a Bloodguard.\n";
            }
            
            if (query_master()==for_obj->query_real_name())
            {
                return result+"your Bloodguard.\n";
            }
            return result+"the Bloodguard of " + 
                capitalize(query_master()) + ".\n";
        }
        return "";
    }

    return QSW->show_subloc(subloc,on,for_obj);
}


public void update_vamp_souls()
{
    load_drains();
    init_vamp_options();
    QSW->add_subloc(BG_SUBLOC,TO);
    QSW->add_cmdsoul(SOUL_DIR+"lay_soul");
    QSW->update_hooks();
}

public void start_player()
{
    QSW->start_player();


}

public void
init_lay_shadow(string arg)
{
    
    set_alarm(2.0,0.0,update_vamp_souls);

    if (environment(QSW))
    {
        QSW->add_prop(LIVE_I_SEE_DARK,
            QSW->query_prop(LIVE_I_SEE_DARK)+
            environment(QSW)->query_prop(VAMP_FREE_SEE_DARKNESS));
        QSW->add_prop(VAMP_FREE_SEE_DARKNESS,
            environment(QSW)->query_prop(VAMP_FREE_SEE_DARKNESS));
    }
    
    set_alarm(itof(min(60,query_vamp_stat()*2)),0.0,reduce_blood);
    
}

public int
create_bloodguard(mixed player)
{
    int result=
    shadow_me(player, "layman", LAY_GUILD_STYLE, LAY_GUILD_NAME, "");

    setuid();
    seteuid(getuid());
    write_file(BG_JOIN_LOG,ctime(time())+ ":  "+player->query_real_name()+
    " has attempted to join the Bloodguards.  Result: " +
    (result==1 ? "success" : "failure") + "\n");

    if (result==1)
    {
        query_manager()->add_member(player);
        add_blood(query_max_blood());            
        QSW->clear_guild_stat(SS_LAYMAN);
    }
    return result;
}


public void
remove_bloodguard(int silent)
{
    setuid();
    seteuid(getuid());
    write_file(BG_JOIN_LOG,ctime(time())+ ":  "+
        QSW->query_real_name()+ " has left the Bloodguards.\n");
    query_manager()->remove_member(QSW->query_real_name());
    QSW->remove_cmdsoul(SOUL_DIR+"lay_soul");
    QSW->update_hooks();
    QSW->clear_guild_stat(SS_LAYMAN);
    QSW->add_prop(LIVE_I_SEE_DARK,
        QSW->query_prop(LIVE_I_SEE_DARK)-
        QSW->query_prop(VAMP_FREE_SEE_DARKNESS));
    QSW->remove_subloc(BG_SUBLOC);
    if (!silent)
    {
        QSW->catch_tell("You feel your canines retract, and your senses "+
        "feel dull. Your bond broken with the source, you feel the gifts "+
        "vanish.\n");
    }
    remove_guild_lay();

}

/* function name: query_guild_keep_player
 * Description:   This gives you a chance to tell if you want to keep the
 *                the player when the shadow is autoloading when a player
 *                logs on.
 * Arguments:     player - the player
 * Returns:       1 - keep player, 0 - kick him out.
 */
static int
query_guild_keep_player(object player)
{
    // As of February 2010, the Bloodguard guild has been closed.
    // We set an alarm to remove bloodguards
    set_alarm(1.0, 0.0, remove_bloodguard);
    return 1;
}
