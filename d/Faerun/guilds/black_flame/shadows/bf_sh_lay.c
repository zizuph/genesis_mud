/* /d/Faerun/guilds/black_flames/shadows/bf_sh_lay.c
 *
 * Guildshadow for the Order of the Black Flames, Nerull 2022
 *
 */

inherit "/std/guild/guild_lay_sh";
inherit "/lib/commands";

#include <comb_mag.h>
#include <files.h>
#include <hooks.h>
#include <log.h>
#include <login.h>
#include <money.h>
#include <std.h>
#include <wa_types.h>
#include <macros.h>
#include <const.h>
#include <ss_types.h>
#include <filter_funs.h>
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


// Default titles
static string *titles = ({ "Black Flame Initiate",
                           "Black Flame Adept",
                           "Black Flame Acolyte",
                           "Devotee of Black Fire",
                           "Fury of the Black Flame",
                           "Pillar of Black Fire",
                           "Righteous Fire",
                           "Devoted Pyre of the Black Flame",
                           "Zealeous Pyre of the Black Flame, Torch of the Faith",
                           "Black Flame Zealot",  
});


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


public mixed
query_guild_skill_name(int type)
{
    if (type == SS_ANATOMY)
    {
        return "anatomy";
    }
    return 0;
}


public void
add_soul_lay()
{
    setuid();
    seteuid(getuid());

    shadow_who->add_cmdsoul(BF_GUILD_DIR 
    + "souls/bf_guild_soul_lay");
	
	object mana_shadow = clone_object("/d/Genesis/specials/guilds/shadows/mana_shadow");

    mana_shadow->shadow_me(shadow_who);

    shadow_who->add_cmdsoul("/d/Genesis/specials/guilds/souls/spell_manager_soul");

    shadow_who->add_cmdsoul(BF_GUILD_DIR + "spells/lay_guild_magic");

    shadow_who->update_hooks();
}


public string *query_spells()
{
    object spell_obj;

    if (!objectp(spell_obj = present(BF_SPELL_OBJECT, shadow_who)))
    {
        return 0;
    }

    return m_indexes(spell_obj->query_spell_map()) + ({});
}


public string
customize_guild_spell_effect_messages(object *effects, string message_text)
{
    mixed active_effect_spells = map(all_inventory(this_player()),
        &->query_spell_names()) - ({ 0 });
		
    if (!sizeof(active_effect_spells)) return 0;

    string *possible_spells = ({ });
    foreach(string *spell : active_effect_spells)
    {
        possible_spells -= spell;
        possible_spells += spell;
    }

    return "\n                     Currently Active Spells \n"
        + "                     ======================== \n\n"
        + break_string("You can cast " 
        + COMPOSITE_WORDS(sort_array(possible_spells))
        + ".", 71) + "\n";
}


int
query_guild_level_lay()
{
    return MIN(10, 
    query_shadow_who()->query_stat(SS_LAYMAN) / 35);
}


string
query_guild_title_lay()
{
    // Fire knives are trainers and military advisors for
    // the Black flames, therefore no title.
    if (this_player()->query_guild_name_occ() == "Fire Knives")
    {
        return "";
    }
    
    if (query_shadow_who()->query_stat(SS_LAYMAN) >= 350)
    {
        return "Black Flame Zealot";
    }
    
    return titles[query_guild_level_lay()];
}


public string
query_guild_name_lay()
{
    return LAY_BF_GUILD_NAME;
}


public string
query_guild_style_lay()
{
    return TYPE_LAY;
}


public int
query_guild_tax_lay()
{
    return TAX_LAY;
}


public mixed
query_guild_trainer_lay()
{
    return ({ BF_GUILD_DIR + "rooms/bf_train",
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
    object who = query_shadow_who();
    
    setuid();
    seteuid(getuid());

    ::init_lay_shadow();
	
	// Clone the guild object   
    if (BF_MASTER->is_lay_bf(who->query_name()))
    {
        if (!present("_bf_bandolier", who))
        {
            clone_object(BF_GUILD_ITEM_LAY)->move(who, 1);
        }         
    }
       
    set_alarm(0.0, 0.0, add_soul_lay);
}


public void remove_shadow()
{
    object emblem, who = query_shadow_who();

    shadow_who->remove_cmdsoul(BF_GUILD_DIR 
    + "souls/bf_guild_soul_lay");
	
	who->remove_mana_shadow();

    shadow_who->remove_cmdsoul("/d/Genesis/specials/guilds/souls/spell_manager_soul");

    shadow_who->update_hooks();
    
    ::remove_shadow();
}


int query_bf_lay()
{
    return 1;
}