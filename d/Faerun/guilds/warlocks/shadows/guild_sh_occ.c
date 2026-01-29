/* /d/Faerun/guilds/warlocks/shadows/guild_sh_occ.c
 *
 * Guildshadow for Warlocks of Faerun, Nerull 2018
 *
 */

inherit "/std/guild/guild_occ_sh";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <composite.h>
#include "/std/combat/combat.h"
#include "../guild.h"


/*
 * Global variables
 */
public int      query_guild_not_allow_join_occ(object player, 
                string type, string style, string name);
static int      query_guild_keep_player(object ob);
public void     init_occ_shadow(string str);
int             query_guild_level_occ();
public void     check_demand();
int             war_defensive = 0;
int             war_incognito = 0;


// Default titles
static string *titles = ({ NONPATR_TITLE1,
                           NONPATR_TITLE2,
                           NONPATR_TITLE3,           
                           NONPATR_TITLE4,
                           NONPATR_TITLE5,
                           NONPATR_TITLE6,
                           NONPATR_TITLE7,
                           NONPATR_TITLE8,           
                           NONPATR_TITLE9,
                           NONPATR_TITLE10,
                           NONPATR_TITLE11,
                           NONPATR_TITLE12,
                           NONPATR_TITLE13,           
                           NONPATR_TITLE14,
                           NONPATR_TITLE15,
                           NONPATR_TITLE16,
                           NONPATR_TITLE17,
                           NONPATR_TITLE18,           
                           NONPATR_TITLE19,
                           NONPATR_TITLE20,
});


// Patron 1 titles
static string *titles_patr1 = ({ PATR1_TITLE1,
                                 PATR1_TITLE2,
                                 PATR1_TITLE3,           
                                 PATR1_TITLE4,
                                 PATR1_TITLE5,
                                 PATR1_TITLE6,
                                 PATR1_TITLE7,
                                 PATR1_TITLE8,           
                                 PATR1_TITLE9,
                                 PATR1_TITLE10,
                                 PATR1_TITLE11,
                                 PATR1_TITLE12,
                                 PATR1_TITLE13,           
                                 PATR1_TITLE14,
                                 PATR1_TITLE15,
                                 PATR1_TITLE16,
                                 PATR1_TITLE17,
                                 PATR1_TITLE18,           
                                 PATR1_TITLE19,
                                 PATR1_TITLE20,
});


// Patron 2 titles
static string *titles_patr2 = ({ PATR2_TITLE1,
                                 PATR2_TITLE2,
                                 PATR2_TITLE3,           
                                 PATR2_TITLE4,
                                 PATR2_TITLE5,
                                 PATR2_TITLE6,
                                 PATR2_TITLE7,
                                 PATR2_TITLE8,           
                                 PATR2_TITLE9,
                                 PATR2_TITLE10,
                                 PATR2_TITLE11,
                                 PATR2_TITLE12,
                                 PATR2_TITLE13,           
                                 PATR2_TITLE14,
                                 PATR2_TITLE15,
                                 PATR2_TITLE16,
                                 PATR2_TITLE17,
                                 PATR2_TITLE18,           
                                 PATR2_TITLE19,
                                 PATR2_TITLE20,
});


// Patron 3 titles
static string *titles_patr3 = ({ PATR3_TITLE1,
                                 PATR3_TITLE2,
                                 PATR3_TITLE3,           
                                 PATR3_TITLE4,
                                 PATR3_TITLE5,
                                 PATR3_TITLE6,
                                 PATR3_TITLE7,
                                 PATR3_TITLE8,           
                                 PATR3_TITLE9,
                                 PATR3_TITLE10,
                                 PATR3_TITLE11,
                                 PATR3_TITLE12,
                                 PATR3_TITLE13,           
                                 PATR3_TITLE14,
                                 PATR3_TITLE15,
                                 PATR3_TITLE16,
                                 PATR3_TITLE17,
                                 PATR3_TITLE18,           
                                 PATR3_TITLE19,
                                 PATR3_TITLE20,
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


int
query_war_defensive()
{
    return war_defensive;
}


void
set_war_defensive(int i)
{
    war_defensive = i;
}


int
query_war_incogn()
{
    return war_incognito;
}


void
set_war_incogn(int i)
{
    war_incognito = i;
}


public void
add_soul()
{
    setuid();
    seteuid(getuid());

    int i;

    object *member;

    object expel_obj;

    member = users();

    shadow_who->add_cmdsoul(WARLOCK_GUILDDIR + "souls/guild_soul");

    object mana_shadow = clone_object("/d/Genesis/specials/guilds/shadows/mana_shadow");

    mana_shadow->shadow_me(shadow_who);

    shadow_who->add_cmdsoul("/d/Genesis/specials/guilds/souls/spell_manager_soul");

    shadow_who->add_cmdsoul(WARLOCK_GUILDDIR + "spells/lay_guild_magic");

    shadow_who->update_hooks();

    /*for(i=0;i<sizeof(member);i++)
    {
        if (WARLOCK_MASTER->is_occ_warlock(member[i]->query_name()))
        {
            if (member[i] != shadow_who)
            {
                tell_object(member[i], ">>"+shadow_who->query_name()
                + " awakens!<<\n");

            }
        }
    }*/
}


int
query_guild_level_occ()
{
    return MIN(WARLOCK_MAX_RANK_MEMBER, 
    query_shadow_who()->query_stat(SS_OCCUP) / 10);
}


string
query_guild_title_occ()
{
    // Patron 1 titles
    if (WARLOCK_MASTER->is_patr1_warlock(shadow_who->query_name()))
    {
        if (query_shadow_who()->query_stat(SS_OCCUP) >= 200)
        {
            return "Chosen of Asmodeus, the Lord of the Nine Hells";
        }
        
        return titles_patr1[query_guild_level_occ()];
    }
    
    // Patron 2 titles
    if (WARLOCK_MASTER->is_patr2_warlock(shadow_who->query_name()))
    {
        if (query_shadow_who()->query_stat(SS_OCCUP) >= 200)
        {
            return "Emissary of the King in Yellow, Bringer of Madness and Despair";
        }
        
        return titles_patr2[query_guild_level_occ()];
    }
    
    // Patron 3 titles
    if (WARLOCK_MASTER->is_patr3_warlock(shadow_who->query_name()))
    {
        if (query_shadow_who()->query_stat(SS_OCCUP) >= 200)
        {
            return "Grand Consumer of Infant Flesh, Emissary of Baba Zirana";
        }
        
        return titles_patr3[query_guild_level_occ()];
    }

    return titles[query_guild_level_occ()];
}


public string
query_guild_name_occ()
{
    return WARLOCK_NAME;
}


public string
query_guild_style_occ()
{
    return TYPE_LAY;
}


public int
query_guild_tax_occ()
{
    return TAX_LAY;
}


public mixed
query_guild_trainer_occ()
{
    return WARLOCK_GUILDDIR + "rooms/train";
}


public int
query_guild_not_allow_join_occ(object player, string type, string style, string name)
{
    if (::query_guild_not_allow_join_occ(player, type, style, name))
    return 1;
}


public int
query_guild_keep_player(object ob)
{
    return 1;
}


public string *query_spells()
{
    object spell_obj;

    if (!objectp(spell_obj = present(WARLOCK_SPELL_OBJECT, shadow_who)))
    {
        return 0;
    }

    return m_indexes(spell_obj->query_spell_map()) + ({});
}


public void
init_occ_shadow(string str)
{
    object guild_emblem, who = query_shadow_who();

    setuid();
    seteuid(getuid());

    ::init_occ_shadow();
    
    set_alarm(60.0, 0.0, check_demand);
    
    set_alarm(0.0, 0.0, add_soul);
    
    // Clone the guild object   
    // Archfiend
    if (WARLOCK_MASTER->is_patr1_warlock(who->query_name()))
    {
        if (!present("patr1_guild_object", who))
        {
            clone_object(GUILD_ITEM1)->move(who, 1);
        }
            
    }
    
    // Great Old One
    if (WARLOCK_MASTER->is_patr2_warlock(who->query_name()))
    {
        if (!present("patr2_guild_object", who))
        {
            clone_object(GUILD_ITEM2)->move(who, 1);
        }
            
    }
        
    // Archfey
    if (WARLOCK_MASTER->is_patr3_warlock(who->query_name()))
    {
        if (!present("patr3_guild_object", who))
        {
            clone_object(GUILD_ITEM3)->move(who, 1);
        }
       
    }
    
    if (!present("nopatron_guild_object", who) || 
    !WARLOCK_MASTER->is_patr1_warlock(who->query_name()) ||
    !WARLOCK_MASTER->is_patr2_warlock(who->query_name()) ||
    !WARLOCK_MASTER->is_patr3_warlock(who->query_name()))
    {
        clone_object(GUILD_ITEM4)->move(this_player(), 1);
    }
}


public void remove_shadow()
{
    object emblem, who = query_shadow_who();

    query_top_shadow()->remove_mana_shadow();

    shadow_who->remove_cmdsoul("/d/Genesis/specials/guilds/souls/spell_manager_soul");
    shadow_who->remove_cmdsoul(WARLOCK_GUILDDIR + "souls/guild_soul");

    shadow_who->update_hooks();

    /* Remove any instances of the guild emblem on the player */
    while (emblem = present(GUILD_ITEM_NAME, who))
    {
        emblem->remove_object();
    }

    ::remove_shadow();
}


/*void
linkdeath_hook(int i)
{
    int j;

    j = i;

    object *member = users();

    for(j = 0; j < sizeof(member);j++)
    {
        if (WARLOCK_MASTER->is_occ_warlock(member[j]->query_name()))
        {
            if (member[j] != shadow_who)
            {
                if (i == 1)
                {
                    tell_object(member[j], "(("+shadow_who->query_name()
                    +" enters the mist))\n");
                }

                if (i == 0)
                {
                    tell_object(member[j], "(("+shadow_who->query_name()
                    +" arrives from the mist))\n");
                }
            }
        }
    }
    shadow_who->linkdeath_hook(i);
}*/


/*void
remove_object()
{
    int i;
    object *obs = users();

    if(calling_function(-1) == "quit")
    {
        for(i = 0; i < sizeof(obs); i++)
        {
            if (WARLOCK_MASTER->is_occ_warlock(obs[i]->query_name()))
            {
                tell_object(obs[i], ">>"+shadow_who->query_name()
                + " left the realms<<\n");
            }
        }
    }
    
    shadow_who->remove_object();
}*/


int query_warlock()
{
    return 1;
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


varargs public string
demand_desc1(object for_obj = query_shadow_who())
{
    return "Your patron "+PATRON1_NAME+", demands that you return "
    +"and peform a Ritual of the Soul!\n";
}


varargs public string
demand_desc2(object for_obj = query_shadow_who())
{
    return "Your patron "+PATRON2_NAME+", demands that you return "
    +"and peform a Ritual of the Mind!\n";
}


varargs public string
demand_desc3(object for_obj = query_shadow_who())
{
    return "Your patron "+PATRON3_NAME+", demands that you return "
    +"and peform a Ritual of the Blood!\n";
}


varargs public string
demand_desc11(object for_obj = query_shadow_who())
{
    return "Your patron "+PATRON1_NAME
    +", demands that you collect a soul through Immolation!\n";
}


varargs public string
demand_desc22(object for_obj = query_shadow_who())
{
    return "Your patron "+PATRON2_NAME
    +", demands that you absorb magical energies into your "
    +"mind by Desecration!\n";
}


varargs public string
demand_desc33(object for_obj = query_shadow_who())
{
    return "Your patron "+PATRON3_NAME
    +", demands that you Consume the blood of an infant!\n";
}


int
beckoning_whispers(object playah, int i)
//beckoning_whispers()
{
    int x = random(4);
    
    int warl = i;
    
    if (WARLOCK_MASTER->is_patr1_warlock(query_shadow_who()->query_name()) 
    || WARLOCK_MASTER->is_patr2_warlock(query_shadow_who()->query_name())
    || WARLOCK_MASTER->is_patr3_warlock(query_shadow_who()->query_name()))
    {
       return 1;
    }
      
    if (warl >= MIN_PATRON_LEVEL)
    {
        switch(x)
        {
            case 0:
            playah->catch_msg("You hear faint whispers echoing "
            +"in your mind, saying: "
            +"Come mortal...Come! Select One of uss..One of us! Find "
            +"uss..forge the Bond! Are you ready to become a Warlock?\n");
            break;
        
            case 1:
            playah->catch_msg("You hear faint whispers echoing in "
            +"your mind, saying: "
            +"Mortal, we deem you worthy! Seek us, find us, select One of "
            +"us for the Bonding! Riches and Power..yess..yess, it will all "
            +"be Yours! Make Haste as a powerful Warlock you will become!\n");
            break;
        
            case 2:
            playah->catch_msg("You hear faint whispers echoing "
            +"in your mind, saying: "
            +"Use our gift and return to the temple, mortal. Seek us out, and "
            +"Select properly as the time has come. It's the time for "
            +"your ascension...your time to become a Warlock!\n");
            break;
        
            case 3:
            playah->catch_msg("You hear faint whispers echoing in "
            +"your mind, saying: "
            +"So you want power? riches? We expect you immediately. Seek us, "
            +"Select One of us..and create the Bond! We will give you..."
            +"Everything! A powerful Warlock you will become!\n");
            break;
        
            return 1;
        }
    }

    return 1;
}


public void check_demand()
{
    if (!interactive(query_shadow_who()))
    {
        return;
    }
    
    int patron_level = query_guild_level_occ();
    
    set_alarm(CHECK_DEMAND_ALARM, 0.0, check_demand);
    
    set_alarm(3.0, 0.0, &beckoning_whispers(query_shadow_who(), patron_level));
  
    if (WARLOCK_MAPPINGS->query_desecration_primer(query_shadow_who()->query_name())== 1)
    {
        if (!present("rit_cooldown_obj", this_player()))
        {
            if (WARLOCK_MASTER->is_patr1_warlock(query_shadow_who()->query_name()))
            {
                if (WARLOCK_MAPPINGS->query_desecration_power(query_shadow_who()->query_name()) >= SPELL_END)
                {
                    return;
                }
                
                query_shadow_who()->catch_msg(demand_desc1());
                
            }
                
            if (WARLOCK_MASTER->is_patr2_warlock(query_shadow_who()->query_name()))
            {
                if (WARLOCK_MAPPINGS->query_desecration_power(query_shadow_who()->query_name()) >= SPELL_END)
                {
                    return;
                }
                
                query_shadow_who()->catch_msg(demand_desc2());
                
            }
                
            if (WARLOCK_MASTER->is_patr3_warlock(query_shadow_who()->query_name()))
            {
                if (WARLOCK_MAPPINGS->query_desecration_power(query_shadow_who()->query_name()) >= SPELL_END)
                {
                    return;
                }
                
                query_shadow_who()->catch_msg(demand_desc3());
                
            } 
        }          
    }
    
    if (WARLOCK_MAPPINGS->query_desecration_primer(query_shadow_who()->query_name())== 0)
    {
        if (!present("rit_cooldown_obj", this_player()))
        {
            if (WARLOCK_MASTER->is_patr1_warlock(query_shadow_who()->query_name()))
            {
                if (WARLOCK_MAPPINGS->query_desecration_power(query_shadow_who()->query_name()) >= SPELL_END)
                {
                    return;
                }
                
                query_shadow_who()->catch_msg(demand_desc11());
                
            }
                
            if (WARLOCK_MASTER->is_patr2_warlock(query_shadow_who()->query_name()))
            {
                if (WARLOCK_MAPPINGS->query_desecration_power(query_shadow_who()->query_name()) >= SPELL_END)
                {
                    return;
                }
                
                query_shadow_who()->catch_msg(demand_desc22());
                
            }
                
            if (WARLOCK_MASTER->is_patr3_warlock(query_shadow_who()->query_name()))
            {
                if (WARLOCK_MAPPINGS->query_desecration_power(query_shadow_who()->query_name()) >= SPELL_END)
                {
                    return;
                }
                
                query_shadow_who()->catch_msg(demand_desc33());
                
            }       
        }          
    }
    
    return;
}



