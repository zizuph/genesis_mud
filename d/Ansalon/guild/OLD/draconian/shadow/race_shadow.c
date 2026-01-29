#pragma strict_types

inherit "/std/guild/guild_race_sh";

#include "../guild.h"

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <wa_types.h>
#include <composite.h>

// Defines
#define MAX_GUILD_LEVEL 21
// Prototypes
public object query_top_shadow();
static int gLast_id;
public object gLast_weapon;

string gDracType;
int gAurak_died = 0;

/* Prototypes */
void remove_race_member();

/* 
 * Function name: query_guild_tax_race
 * Description:   Give the amount of tax the guild charges
 * Returns:       int - The tax amount
 */
int
query_guild_tax_race() 
{ 
    return 0;  //No guild tax for race guild
}

/*
 * Function name: query_guild_style_race
 * Description:   return the guild style for this guild
 * Returns:       string - the style
 */
string
query_guild_style_race()
{
    return GUILD_STYLE;
}

/*
 * Function name: query_guild_name_race
 * Description:   return the guild's name
 * Returns:       string - the guild name
 */
string
query_guild_name_race()
{
    return GUILD_NAME_RACE;
}

/*
 * Function name: acceptable_member
 * Description:   test to see if the player is an acceptable member of this
 *                guild.
 * Arguments:     object who - the player to test
 * Returns:       0 or a string message saying why the player isn't acceptable
 */
mixed
acceptable_member(object who)
{
    return 0;
}
      
/* 
 * Function name: query_guild_keep_player
 * Description:   Test if we want to keep the player in the guild.
 * Arguments:     ob - the player.
 * Returns:	  1 if keeping, 0 if not.
 */
int
query_guild_keep_player(object ob)
{
    mixed why;

    if (stringp(why = acceptable_member(ob)))
    {
	    ob->catch_msg(why);

        /* Normally we would just return 0 here, and the player would be
         * removed from the guild.  We want to make sure a few cleanup
         * actions happen, though, so we'll return 1 here and remove
         * the member ourselves.
         */

        set_alarm(1.0, 0.0, remove_race_member);

        return 1;
    }

    return 1;
}

/* 
 * Function name: query_guild_not_allow_join_race
 * Description:	  Check if we allow the player to join another guild.
 * Arguments:     player - the player
 *		  type, style, name - the type, style and name of the
 *			intended guild.
 * Returns:	  1 if we do not allow, else 0
 */
int
query_guild_not_allow_join_race(object player, string type, string style,
				string name)
{
    /* This checks to make sure that the new guild is not race */
    if (::query_guild_not_allow_join_race(player, type, style, name))
        return 1;

    return 0;
}

/* Function name: query_guild_level_occ
 * Description:   What is the member's level within the guild?
 * Returns:	  int - the level
 */
int
query_guild_level_race()
{
    return MIN(MAX_GUILD_LEVEL, SW->query_stat(SS_RACE) / 50);
}
    
/* Function name: query_def_post
 * Description:   We change the default post office for our members.
 * Returns:	  string - the path to the new postoffice
 */
string
query_def_post() 
{
    return SW->query_def_post();
}

/*
 * Function name: query_guild_title_race
 * Description:   Return the member's guild title
 * Returns:       string - the title
 */
string 
query_guild_title_race()
{
    return 0;
}
    
/* 
 * Function name: query_guild_skill_name
 * Description:   Give a names for the guild's special skills
 * Arguments:     type - the number of the skill
 * Returns:	  0 if no skill of mine, else the string.
 */
mixed
query_guild_skill_name(int type)
{
    return 0;
}

/*
 * Function name: query_guild_trainer_race
 * Description:   Returns the skill trainers for the guild
 * Returns:       string * - an array of paths to the guild's
 *                trainers.
 */
mixed
query_guild_trainer_race()
{
    return ({ GUILD_DIR + "joinroom" });
}

public void
do_die(object killer)
{
	object corpse;
	
	if (gDracType == "aurak")
	{
		if (gAurak_died == 1)
		{
			setuid();
			seteuid(getuid());
        
			corpse = clone_object("/d/Krynn/common/objects/lightning");
			corpse->move(environment(TO));
			::SW->do_die(killer);
		}
		else
		{
			gAurak_died = 1;
			tell_room(environment(TO), QCTNAME(TO) + " died.\n", TO);
			killer->catch_msg("You killed " + QTNAME(TO) + ".\n");
			SW->catch_msg("\nYou die.\nWait! You are still alive and gone berserk!\n");
			//killer->notify_you_killed_me(TO);
			tell_room(environment(SW), "No! The draconian is still alive and goes berserk!\n");
			SW->add_tmp_stat(0, 100, 1);
			SW->add_tmp_stat(1, 90, 1);
			SW->add_tmp_stat(2, 10, 1);
			SW->add_tmp_stat(3, -50, 1);
			SW->add_tmp_stat(4, -50, 1);
			SW->add_tmp_stat(5, 100, 1);
			SW->heal_hp(500);
			// Set an alarm to kill the player after 25 sec.
			set_alarm(25.0, 0.0, ::SW->do_die(killer));
			return;
		}
    }	
	if (gDracType == "kapak")
	{
		setuid();
		seteuid(getuid());
		corpse = clone_object("/d/Krynn/common/monster/acid_remains");
		tell_room(environment(TO),"The draconian melts down into a pool of liquid!\n");
        corpse->move(environment(TO));
		::SW->do_die(killer);
    }
	if (gDracType == "sivak")
	{
		setuid();
		seteuid(getuid());
        corpse = clone_object("/d/Krynn/common/monster/flame_remains");
		tell_room(environment(TO),"The draconian bursts into flames!\n");
        corpse->move(environment(TO));
		::SW->do_die(killer);
    }
	if (gDracType == "bozak")
	{
		tell_room(environment(TO),"BANG! The bones of the draconian explode!\n");

		object *things = all_inventory(environment(TO));
		int i = sizeof(things);
		//while (i--)

        if (!things[i]->query_ghost())
			/* Don't hurt myself :-) I'm dead, right? */
			if (things[i]->query_prop(LIVE_I_IS))
				/* Its alive, hurt it! */
               if (things[i] != TO)
				   	/* Don't hurt yourself */
				  if (things[i]->query_race() != "draconian")
					/* Don't hurt other draconians */
                     //bozak_hurt_one(things[i]);			
		::SW->do_die(killer);
    }
	if (gDracType == "baaz")
	{
		object *gBaaz_inv = all_inventory(SW);
	
		object statue, wep;
		string wep_sh;
		set_alarm(0.0, 0.0, remove_object);
		tell_room(E(SW), "The draconian turns into stone!\n");
		statue = clone_object("/d/Krynn/common/monster/stonecorpse");
		gBaaz_inv->move(statue, 1);
		statue->move(E(SW));
		wep = killer->query_weapon(gLast_id);
		if ((wep == gLast_weapon) && !wep->query_prop(OBJ_I_IS_MAGIC_WEAPON) &&
			(wep->weapon_type()!="missile weapon") &&
			(wep->query_dt() & W_SLASH || wep->query_dt() & W_IMPALE))
		{
			if (random(killer->query_stat(SS_DEX)) > random(60))
			{ 
				killer->catch_msg("Just at the last moment are you able to " +
					"pull your " + wep->short() + " free.\n");
				return 0;
			}
			wep->unwield_me();
			if (wep->move(statue) == 0)
			{
				killer->catch_msg("Oh no! The weapon is stuck in the " +
					"stone!\n");
				wep_sh = wep->short();
				tell_room(environment(SW),QCTNAME(killer) + " lets go of " +
					killer->query_possessive() + " " + wep_sh +
					", since it got stuck in the stone.\n", killer);
					killer->catch_msg("You let go of your " + wep_sh + ".\n");
				return 0;
			}
		}   
	}
	::SW->do_die(killer);
}

/*
 * Function name: hit_me
 * Description:   Get the id of the object that hit us. Then call the
 *                original hit_me.
 *                Only used for Baaz draconians!
 * Arguments:     wcpen       - The wc-penetration
 *                dt          - damagetype, use MAGIC_DT if ac will not
 *                              help against this attack.
 *                attacker    - Object hurting us
 *                attack_id   - Special id saying what attack hit us. If you
 *                              have made a special attack, let the id be -1
 * Returns:       The hitresult as given by the external combat object.
 */
public mixed 
hit_me(int wcpen, int dt, object attacker, int attack_id)
{
	if (gDracType != "baaz")
		return (::SW->hit_me(wcpen, dt, attacker, attack_id));

    gLast_id = attack_id;
    if (attack_id >= 0 && objectp(attacker))
    {
        gLast_weapon = attacker->query_weapon(attack_id);
        gLast_id = attack_id;
    }
    else
        gLast_weapon = 0;
    return (::SW->hit_me(wcpen, dt, attacker, attack_id));
}

/*
 * Function name: init_guild_member
 * Description:   Add necessary guild items to the player and
 *                do any other kind of initialization necessary.
 */
void
init_guild_member()
{
    object guild_cloak;

    /* clone the guild cloak and move it to the player */

    setuid();
    seteuid(getuid());
    
    if (guild_cloak = clone_object(GUILD_CLOAK))
    {    
        guild_cloak->move(SW, 1);
    }

    /* add the guild's soul to the player */
    SW->add_cmdsoul(GUILD_CMDSOUL);
    SW->update_hooks();

    /* add the guild subloc */
    SW->add_subloc(GUILD_SUBLOC, TO);
	SW->add_prop(LIVE_I_NO_CORPSE, 1); //Don't leave a corpse
	
	string color;
	
	/* setup specific draconian type abilities */
    switch (gDracType)
    {
      case "baaz":
        color = "brass";
		break;
	  case "kapak":
        color = "copper";
		break;
      case "bozak":
        color = "bronze";
		break;
      case "sivak":
        color = "silver";
		break;		
      case "aurak":
        color = "gold";
		break;
	  default:
        color = "colorless";
		break;
	}
	
	SW->catch_tell("Welcome Draconian of Krynn!\n"+
	                "You take a deep breath of air as you feel invigorated by "+
					"the "+color+" dragon blood flowing in your veins.\n");
}

/*
 * Function name: start_player
 * Description:   This is called when the player logs in.
 */
public void
start_player()
{
    SW->start_player();
    init_guild_member();
}

/* 
 * Function name: add_race_shadow
 * Description:   Shadow an object with this shadow
 * Arguments:     object who - the object to shadow
 * Returns:       as shadow_me in /std/guild/guild_base.c
 */
int add_race_shadow(object who, string dracType)
{
    int ret = shadow_me(who, "race", GUILD_STYLE, GUILD_NAME_RACE);
	gDracType = dracType;

    if (ret == 1)
    {
        init_guild_member();
		log_file("drac_join", SW->query_real_name() + " joined - " +
          extract(ctime(time()), 4, 15) + " - " +gDracType+ "\n");
    }

    return ret;
}

/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - Our subloc
 *		  me      - I
 *		  for_obj - The looker
 * Returns:	  The string the looker shall see
 */
string
show_subloc(string subloc, object me, object for_obj)
{
    string str;

    if (subloc != GUILD_SUBLOC)
        return me->show_subloc(subloc, me, for_obj);

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
		return "";

    if (for_obj == me)
		str = "You have ";
    else
		str = capitalize(me->query_pronoun()) + " has ";

    switch (gDracType)
    {
      case "kapak":
	  {
		str = str + "the scaled copper coloured skin of a kapak draconian from Krynn.";
		break;
	  }
      case "aurak":
	  {
		str = str + "the scaled gold coloured skin of an aurak draconian from Krynn.";
		break;
	  }
      case "bozak":
	  {
		str = str + "the scaled bronze coloured skin of a bozak draconian from Krynn.";
		break;
	  }
      case "sivak":
	  {
		str = str + "the scaled silver coloured skin of a sivak draconian from Krynn.";
		break;
	  }
      case "baaz":
	  {
		str = str + "the scaled bronze coloured skin of a baaz draconian from Krynn.";		
        break;
	  }
	  default:
	  {
		str = str + "the scaled skin of a draconian from Krynn.";
        break;
	  }
	}
	return str + "\n";
}

/*
 * Function name: remove_race_member
 * Description:   remove this member from the guild
 */
void
remove_race_member()
{
    object cloak;

    /* Clear the player's guild stat */
    SW->clear_guild_stat(SS_RACE);

    /* Remove any instances of the guild cloak on the player */
    while (cloak = present(GUILD_CLOAK_ID, SW))
    {
        cloak->remove_object();
    }

    /* If the player is using our start location, remove it */
    if (SW->query_default_start_location() == GUILD_STARTLOC)
    {
        SW->set_default_start_location(SW->query_def_start());
    }

    /* Remove the guild soul */
    SW->remove_cmdsoul(GUILD_CMDSOUL);
	SW->remove_subloc(GUILD_SUBLOC, TO);
	SW->reset_race_name();
    SW->update_hooks();
    log_file("drac_leave", SW->query_real_name() + " left - " +
        extract(ctime(time()), 4, 15) + " - " +gDracType+ "\n");
	
    /* Remove the guild shadow.  This also resets tax to 0. */
    remove_guild_race();
	
	::remove_shadow();    
}

/*
 * Function name: query_top_shadow
 * Description:   Because shadows exist in layers, sometimes you need
 *                to reference functions in a shadow above you. Calling
 *                functions can fail if one doesn't call from the top
 *                shadow. this function allows one to obtain the
 *                top most shadow, giving access to all functions.
 * Returns:       object - top level shadow
 */
public object
query_top_shadow()
{
    object last_me, me;
    
    me = shadow_who;
    last_me = me;
    while (me = shadow(me, 0))
    {
        // loop through to find the top level shadow who
        last_me = me;
    }   
    
    // We return now the top level shadow
    return last_me;
}

/* Function name: autoload_shadow
 * Description:   Get the saved string from the autoload_shadow string.
 */
void
init_race_shadow(mixed arg)
{
	string dracType;
	
    if (arg && sscanf(arg,"%s",dracType) == 1) //found!
		gDracType = dracType;
	
	SW->set_all_hitloc_unarmed(2); // Minor bonus to unarmoured locations (scales)
	                                       // to compensate for dragon-slaying effects										   
    SW->set_race_name("draconian");
}

/* 
 * Function name: query_drac_type
 * Description:   Returns the draconian type
 * Arguments:     None
 * Returns:       string - The drac type
 */
string query_drac_type()
{
    return gDracType;
}
