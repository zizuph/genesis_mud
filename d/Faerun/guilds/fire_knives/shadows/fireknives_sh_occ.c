/* /d/Faerun/guilds/fire_knives/shadows/fireknives_sh_occ.c
 *
 * Guildshadow for Fire Knives of Faerun, Nerull 2018
 *
 */

inherit "/std/guild/guild_occ_sh";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <composite.h>
#include "/std/combat/combat.h"
#include "../guild.h"

#include "fire_combat_msg.c"


/*
 * Global variables
 */
public int      query_guild_not_allow_join_occ(object player, 
                string type, string style, string name);
static int      query_guild_keep_player(object ob);
public void     init_occ_shadow(string str);
int             query_guild_level_occ();
int             fireknife_incognito = 0;
int             autosneak_on = 0;


// Default titles
static string *titles = ({ FIREKNIVES_TITLE0,
                           FIREKNIVES_TITLE1,
                           FIREKNIVES_TITLE2,
                           FIREKNIVES_TITLE3,           
                           FIREKNIVES_TITLE4,
                           FIREKNIVES_TITLE5,
                           FIREKNIVES_TITLE6,
                           FIREKNIVES_TITLE7,
                           FIREKNIVES_TITLE8,           
                           FIREKNIVES_TITLE9,
                           FIREKNIVES_TITLE10,
                           FIREKNIVES_TITLE11,
                           FIREKNIVES_TITLE12,
                           FIREKNIVES_TITLE13,           
                           FIREKNIVES_TITLE14,
                           FIREKNIVES_TITLE15,
                           FIREKNIVES_TITLE16,
                           FIREKNIVES_TITLE17,
                           FIREKNIVES_TITLE18,           
                           FIREKNIVES_TITLE19,
                           FIREKNIVES_TITLE20,                          
                           FIREKNIVES_TITLE21,
                           FIREKNIVES_TITLE22,           
                           FIREKNIVES_TITLE23,
                           FIREKNIVES_TITLE24,
                           FIREKNIVES_TITLE25,
                           FIREKNIVES_TITLE26,
                           FIREKNIVES_TITLE27,           
                           FIREKNIVES_TITLE28,
});


// Default titles
static string *gauge_titles = ({ FIREKNIVES_GAUGE_TITLE0,
                           FIREKNIVES_GAUGE_TITLE1,
                           FIREKNIVES_GAUGE_TITLE2,
                           FIREKNIVES_GAUGE_TITLE3,           
                           FIREKNIVES_GAUGE_TITLE4,
                           FIREKNIVES_GAUGE_TITLE5,
                           FIREKNIVES_GAUGE_TITLE6,
                           FIREKNIVES_GAUGE_TITLE7,
                           FIREKNIVES_GAUGE_TITLE8,           
                           FIREKNIVES_GAUGE_TITLE9,
                           FIREKNIVES_GAUGE_TITLE10,
                           FIREKNIVES_GAUGE_TITLE11,
                           FIREKNIVES_GAUGE_TITLE12,
                           FIREKNIVES_GAUGE_TITLE13,           
                           FIREKNIVES_GAUGE_TITLE14,
                           FIREKNIVES_GAUGE_TITLE15,
                           FIREKNIVES_GAUGE_TITLE16,
                           FIREKNIVES_GAUGE_TITLE17,
                           FIREKNIVES_GAUGE_TITLE18,           
                           FIREKNIVES_GAUGE_TITLE19,
                           FIREKNIVES_GAUGE_TITLE20,                          
                           FIREKNIVES_GAUGE_TITLE21,
                           FIREKNIVES_GAUGE_TITLE22,           
                           FIREKNIVES_GAUGE_TITLE23,
                           FIREKNIVES_GAUGE_TITLE24,
});


void
set_autosneak(int a)
{
    autosneak_on = a;
}
 
 
int
query_autosneak()
{
    return autosneak_on;
}


public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
    int hiding, retval, val, bval, did_sneak;
    object me;
 
    me = shadow_who;
 
    if (!me->query_prop(LIVE_I_SNEAK) &&
        autosneak_on &&
        query_verb() &&
        !(me->query_prop(OBJ_I_LIGHT) && (me->query_prop(OBJ_I_LIGHT) >
            environment(me)->query_prop(OBJ_I_LIGHT))) &&
        !(objectp(me->query_attack()))
        )
    {
        hiding = environment(me)->query_prop(ROOM_I_HIDE);

        bval = me->query_skill(SS_SNEAK) * 2 + me->query_skill(SS_HIDE) / 3;
        bval = (bval - hiding) / 2;
 
        if (hiding >= 0 && bval > 0)
        {
            val = bval + random(bval);
            me->add_prop(OBJ_I_HIDE, val);
            me->add_prop(LIVE_I_SNEAK, 1);
            did_sneak = 1;
        }
        if (!did_sneak)
            tell_object(me, "You failed to sneak.\n");
    }
    
    retval = me->move_living(how, to_dest, dont_follow, no_glance);
    
    if (!did_sneak)
        return retval;
 
    hiding = environment(me)->query_prop(ROOM_I_HIDE);

    bval = me->query_skill(SS_HIDE);
    bval = (bval - hiding) / 2;
 
    set_this_player(me);
    
    int my_light_level = me->query_prop(OBJ_I_LIGHT);    
    int my_env_light_level = environment(me)->query_prop(OBJ_I_LIGHT);
    
    if (hiding < 0 || bval <= 0)
    {
        write("It's too difficult to hide in here, you're visible again.\n");
        me->reveal_me(0);
    }
    /*else if (my_light_level >= 1)
    {
        write("You can't hide here, shining like that!\n");
        me->reveal_me(1);
    }*/
       
    // Providing more ligh to a room than the environment itself makes sense.
    // Providing More darkness to the environment != you are shining or making it
    // easier to be detected. Darkness is Darkness, and all see in darkness works
    // vs infinite levels of darkness, so this is redundant. Nerull 2021.  
    // the else if is replaced with 'else if (my_light_level >= 1)' above.
    /*else if (me->query_prop(OBJ_I_LIGHT) && (me->query_prop(OBJ_I_LIGHT) > environment(me)->query_prop(OBJ_I_LIGHT)))
    {
        write("You can't hide here, shining like that!\n");
        me->reveal_me(1);
    }*/
 
    val = bval + random(bval);
    
    me->add_prop(OBJ_I_HIDE, val);
    
    return retval;
}


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
public mixed
query_guild_skill_name(int type)
{
    if (type == SS_ART)
    {
        return "assassination";
    }
    return 0;
}


// CURRENT
public int
check_seen(object for_obj)
{
    if (member_array(for_obj, shadow_who->query_team_others()) > -1)
        return !(!objectp(for_obj) || shadow_who->query_no_show() ||
                (!for_obj->query_wiz_level() &&
                (for_obj->query_prop(LIVE_I_SEE_INVIS) <
                shadow_who->query_prop(OBJ_I_INVIS))));
    
    return shadow_who->check_seen(for_obj);
} /* check_seen */


// ORIGINAL
/*
 * Function name: check_seen
 * Description:   True if this object can be seen by a given object
 * Arguments:     for_obj: The object for which visibilty should be checked
 * Returns:       1 if this object can be seen.
 */
/*public int
check_seen(object for_obj)
{
    if (!objectp(for_obj) ||
        obj_no_show ||
        (!for_obj->query_wiz_level() &&
         (for_obj->query_prop(LIVE_I_SEE_INVIS) <
          this_object()->query_prop(OBJ_I_INVIS) ||
          for_obj->query_skill(SS_AWARENESS) <
          this_object()->query_prop(OBJ_I_HIDE))))
    {
        return 0;
    }
	
    return 1;
}*/


// MODIFIED
/*public int
check_seen(object for_obj)
{
    if (member_array(for_obj, shadow_who->query_team_others()) > -1)
        return !(!objectp(for_obj) || shadow_who->query_no_show() ||
                (!for_obj->query_wiz_level() &&
                (for_obj->query_prop(LIVE_I_SEE_INVIS) <
                shadow_who->query_prop(OBJ_I_INVIS) ||
                (for_obj->query_skill(SS_AWARENESS) / 2) <
                this_object()->query_prop(OBJ_I_HIDE))));
    
    return shadow_who->check_seen(for_obj);
} /* check_seen */


int
query_fireknife_incogn()
{
    return fireknife_incognito;
}


void
set_fireknife_incogn(int i)
{
    fireknife_incognito = i;
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

    shadow_who->add_cmdsoul(FIREKNIVES_GUILD_DIR 
    + "souls/fireknives_guild_soul");

    shadow_who->update_hooks();
}


int
query_guild_level_occ()
{
    return FIREKNIVES_MAPPINGS->query_assassin_rank(query_shadow_who()->query_name());
}


int
query_assassin_gauge_level()
{
    return FIREKNIVES_MAPPINGS->query_assassin_gauge(query_shadow_who()->query_name());
}


string
query_assassin_gauge_title()
{
    return gauge_titles[query_assassin_gauge_level()];
}


/*public string
show_subloc(string subloc, object me, object for_obj)
{
    string str;
    
    if (query_fireknife_incogn() == 1)
    {
    
        if (subloc != "Fireknives subloc")
        {
            return me->show_subloc(subloc, me, for_obj);
        }
        
        if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        {
            return "";
        }
        
        if (for_obj == me)
        {
            str = "You are";
        }
        else
        {
            str = capitalize(me->query_pronoun()) + " is";
        }
        
        return str + " a "+query_assassin_gauge_title()+".\n";
    }
    
    return "";
}*/


string
query_guild_title_occ()
{
    if (query_fireknife_incogn() == 1)
    {
        if (FIREKNIVES_MASTER->is_occ_boss_fireknife(query_shadow_who()->query_name()) == 1)
        {
            return "Elder, Keeper of Tradition";
        }
    
        if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(query_shadow_who()->query_name()) == 1)
        {
            return "Inquisitor";
        }
        
        if (FIREKNIVES_MASTER->is_occ_thefist_fireknife(query_shadow_who()->query_name()) == 1)
        {
            return "Fist";
        }
		
	    if (FIREKNIVES_MASTER->is_occ_retired_council(query_shadow_who()->query_name()) == 1)
		{
			 return titles[query_guild_level_occ()]+", Councillor to the High Table";
		}
	
		if (FIREKNIVES_MASTER->is_occ_librarian(query_shadow_who()->query_name()) == 1)
        {
             return "The Archivist and "+titles[query_guild_level_occ()]+""+query_assassin_gauge_title()+"";
        }
        
        if (FIREKNIVES_MASTER->is_occ_whisper(query_shadow_who()->query_name()) == 1)
        {
             return "The Whisper and "+titles[query_guild_level_occ()]+""+query_assassin_gauge_title()+"";
        }
        
        return titles[query_guild_level_occ()];
    }
    
    return "";
}


string
query_guild_title_occ_internal()
{
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(query_shadow_who()->query_name()) == 1)
    {
        return "The Elder, Keeper of Tradition";
    }
    
    if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(query_shadow_who()->query_name()) == 1)
    {
        return "The Inquisitor";
    }
    
    if (FIREKNIVES_MASTER->is_occ_thefist_fireknife(query_shadow_who()->query_name()) == 1)
    {
        return "The Fist";
    }
	
	if (FIREKNIVES_MASTER->is_occ_retired_council(query_shadow_who()->query_name()) == 1)
    {
         return titles[query_guild_level_occ()]
		 +" and Councillor to the High Table"+query_assassin_gauge_title()+"";
    }
	
	if (FIREKNIVES_MASTER->is_occ_librarian(query_shadow_who()->query_name()) == 1)
    {
         return "The Archivist and "+titles[query_guild_level_occ()]+""+query_assassin_gauge_title()+"";
    }
    
    if (FIREKNIVES_MASTER->is_occ_whisper(query_shadow_who()->query_name()) == 1)
    {
         return "The Whisper and "+titles[query_guild_level_occ()]+""+query_assassin_gauge_title()+"";
    }
    
    return titles[query_guild_level_occ()]+""+query_assassin_gauge_title()+"";
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
query_guild_name_occ()
{
    return FIREKNIVES_GUILD_NAME;
}


public string
query_guild_style_occ()
{
    return TYPE_OCC;
}


public int
query_guild_tax_occ()
{
    return TAX_OCC;
}


public mixed
query_guild_trainer_occ()
{
    return ({ FIREKNIVES_GUILD_DIR + "rooms/ft",
              FIREKNIVES_GUILD_DIR + "rooms/ti",
              FIREKNIVES_GUILD_DIR + "rooms/guru",
           });
}


public int
query_guild_not_allow_join_occ(object player, string type, 
string style, string name)
{
    if (::query_guild_not_allow_join_occ(player, type, style, name))
    return 1;
}


public int
query_guild_keep_player(object ob)
{
    return 1;
}


void
expel_me()
{
    if (FIREKNIVES_MASTER->is_occ_fireknife(shadow_who->query_name()) == 0)
    {
        shadow_who->command("betray the fire knives outfit");
    }
}


void
add_evade_ob_base()
{
	setuid();
	seteuid(getuid());
    
	object evade_obj_base, defended, top_shadow;
	//object * regen_objs;
    
	top_shadow = query_top_shadow();
    
	defended = top_shadow->query_shadow_who();
    
	evade_obj_base = clone_object(FIREKNIVES_REGEN_BASE_OBJ);
	evade_obj_base->set_effect_caster(defended);
	evade_obj_base->set_effect_target(defended);
	evade_obj_base->move(defended, 1);
	evade_obj_base->start();
}


public void
init_occ_shadow(string str)
{
    object guild_emblem, who = query_shadow_who();

    setuid();
    seteuid(getuid());

    ::init_occ_shadow();
    
    set_alarm(0.0, 0.0, add_soul);
    
    set_alarm(1.0, 0.0, add_evade_ob_base);
    
    clone_object(FIREKNIVES_GUILD_DIR + "obj/expel_obj")->move(shadow_who, 1);
    set_alarm(1.0, 0.0, &expel_me());
    
    // Clone the guild object   
    if (FIREKNIVES_MASTER->is_occ_fireknife(who->query_name()))
    {
        if (!present("fireknife_guild_object", who))
        {
            clone_object(GUILD_ITEM)->move(who, 1);
        }         
    }
    
    if (who->query_skill(1527001))
    {
        int oldskill;
        
        oldskill = who->query_skill(1527001);
        
        who->set_skill(152701, oldskill);
        
        who->remove_skill(1527001);
    }
}


public void remove_shadow()
{
    object emblem, who = query_shadow_who();

    shadow_who->remove_cmdsoul(FIREKNIVES_GUILD_DIR 
    + "souls/fireknives_guild_soul");

    shadow_who->update_hooks();

    /* Remove any instances of the guild emblem on the player */
    while (emblem = present(GUILD_ITEM_NAME, who))
    {
        emblem->remove_object();
    }

    ::remove_shadow();
}


int query_fireknife()
{
    return 1;
}




