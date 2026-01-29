/* /d/Raumdor/guilds/the_order/shadows/theorder_sh_lay_melee.c
 *
 * 
 *
 */

inherit "/std/guild/guild_lay_sh";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <composite.h>
#include "/std/combat/combat.h"
#include "../guild.h"


/*
 * Global variables
 */
public int      query_guild_not_allow_join_lay(object player, 
                string type, string style, string name);
static int      query_guild_keep_player(object ob);
public void     init_lay_shadow(string str);
int             query_guild_level_lay();


static string *o_titleslay_m = ({ LAYMELEE1,
                                  LAYMELEE2,
                                  LAYMELEE3,           
                                  LAYMELEE4,
                                  LAYMELEE5,
                                  LAYMELEE6,
                                  LAYMELEE7,
                                  LAYMELEE8,           
                                  LAYMELEE9,
                                  LAYMELEE10,
                                  LAYMELEE11,
                                  LAYMELEE12,
                                  LAYMELEE13,           
                                  LAYMELEE14,
                                  LAYMELEE15,
                                  LAYMELEE16,
                                  LAYMELEE17,
                                  LAYMELEE18,           
                                  LAYMELEE19,
                                  LAYMELEE20,
});




/*
 * Function name : query_guild_skill_name
 * Description  : Standard function to return a name for the guild's
 *                special skills in order to print them out nicely
 *                when a player uses the 'skills' command, rather than
 *                seeing 'special'.
 * Arguments     : int type - the number of the skill assigned by the
 *                 liege of the domain
 * Returns       : 0 if no skill of this guild, else the string.
 */
/*public mixed
query_guild_skill_name(int type)
{
    if (type == SS_ART)
    {
        return "assassination";
    }
    return 0;
}*/


public void
add_soul()
{
    setuid();
    seteuid(getuid());

    shadow_who->add_cmdsoul(THEORDER_GUILD_DIR 
    + "souls/theorder_guild_soul_lay_melee");

    shadow_who->update_hooks();
}


int
query_guild_level_lay()
{
    return MIN(THEORDER_MAX_RANK_LAY_MEMBER_MELEE, 
    query_shadow_who()->query_stat(SS_LAYMAN) / 10);
}


string
query_guild_title_lay()
{
	if (query_shadow_who()->query_stat(SS_LAYMAN) >= 200)
	{
		return "Emissary of the King in Yellow, Bringer of Madness and Despair";
	}
	
	return o_titleslay_m[query_guild_level_lay()];
}


public object
query_top_shadow()
{
	object last_me, me;
	me = shadow_who;
	last_me = me;
    
	while (me = shadow(me, 0))
	{
		last_me = me;
	}
    
	return last_me;
}


public string
query_guild_name_lay()
{
    return THEORDER_GUILD_NAME_LAY_MELEE;
}


public string
query_guild_style_lay()
{
    return TYPE_LAY_MELEE;
}


public int
query_guild_tax_lay()
{
    return TAX_LAY_MELEE;
}


public mixed
query_guild_trainer_lay()
{
    return ({ THEORDER_GUILD_DIR + "rooms/f",
           });
}


public int
query_guild_not_allow_join_lay(object player, string type, 
string style, string name)
{
    if (::query_guild_not_allow_join_lay(player, type, style, name))
    return 1;
}


public int
query_guild_keep_player(object ob)
{
    return 1;
}


public void
init_lay_shadow(string str)
{
    object guild_emblem, who = query_shadow_who();

    setuid();
    seteuid(getuid());

    ::init_lay_shadow();
    
    set_alarm(0.0, 0.0, add_soul);
    
    // Clone the guild object   
    if (THEORDER_MASTER->is_lay_theorder_melee(who->query_name()))
    {
        if (!present("theorder_guild_object_lay_melee", who))
        {
            clone_object(THEORDER_LAY_ITEM_MELEE)->move(who, 1);
        }         
    }
}


public void remove_shadow()
{
    object emblem, who = query_shadow_who();  

    shadow_who->remove_cmdsoul(THEORDER_GUILD_DIR 
    + "souls/theorder_guild_soul_lay_melee");

    shadow_who->update_hooks();

    /* Remove any instances of the guild emblem on the player */
    while (emblem = present("theorder_guild_object_lay_melee", who))
    {
        emblem->remove_object();
    }

    ::remove_shadow();
}


int query_theorder_lay_melee()
{
    return 1;
}




