/*
 * File Name        : pirate_shadow.c
 * By               : Elmore.
 * Inspiration from : The Neidar Guild by Arman.
 *                    Occ_fighter Guild by Unknow.
 * Date             : Nov. 2000.
 * Description      : Contrains the shadow for the pirates
 *                    guild. Also handles the special attack
 *                    'stab' from the file: stab_special_attack.c
 *
 */

#pragma strict_types
inherit "/std/guild/guild_lay_sh";

#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <options.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include "/std/combat/combat.h"

/* the code for special attacks is in a seperate file
 * for easier debugging.  It's common to find all of
 * the code for a special attack in the soul, but placing
 * most of the code in the shadow can often make handling
 * specials easier.
 */

#define GUILD_SUBLOC  GUILD_NAME + " subloc"
#define MAX_GUILD_LEVEL 21

#define SW shadow_who

static string *MaleTitles = ({
    "Deck Swappy of the Bloodsea",
    "Experienced Deck Swappy of the High Seas",
    "Cabinboy of the Bloodsea",
    "Learned Cabinboy of the High Seas",
    "Raider of the Bloodsea",
    "Drunken Raider of the High Seas",
    "Swashbuckler of the Bloodsea",
    "Wanted Swashbuckler of the High Seas",
    "Freebooter of the Bloodsea",
    "Feared Freebooter of the High Seas",
    "Buccaneer of the Bloodsea",
    "Deadly Buccaneer of the High Seas",
    "Corsair of the Bloodsea",
    "Dreaded Corsair of the High Seas",
    "Cutthroat of the Bloodsea",
    "Veteran Cutthroat of the High Seas",
    "Pirate of the Bloodsea",
    "Notorious Pirate of the High Seas",
    "Scourge of the Bloodsea",
    "Scurvy Scourge of the High Seas",
    "Pirate Lord of the Bloodsea",
    "Legendary Pirate Lord of the High Seas",
});

static string *FemaleTitles = ({
    "Deck Swappy of the Bloodsea",
    "Experienced Deck Swappy of the High Seas",
    "Cabingirl of the Bloodsea",
    "Learned Cabingirl of the High Seas",
    "Raider of the Bloodsea",
    "Drunken Raider of the High Seas",
    "Swashbuckler of the Bloodsea",
    "Wanted Swashbuckler of the High Seas",
    "Freebooter of the Bloodsea",
    "Feared Freebooter of the High Seas",
    "Buccaneer of the Bloodsea",
    "Deadly Buccaneer of the High Seas",
    "Corsair of the Bloodsea",
    "Dreaded Corsair of the High Seas",
    "Cutthroat of the Bloodsea",
    "Veteran Cutthroat of the High Seas",
    "Pirate of the Bloodsea",
    "Notorious Pirate of the High Seas",
    "Scourge of the Bloodsea",
    "Scurvy Scourge of the High Seas",
    "Pirate Lady of the Bloodsea",
    "Legendary Pirate Lady of the High Seas",
});

/* Prototypes */
void remove_lay_member();
void check_banished();

/* 
 * Function name: query_guild_tax_lay
 * Description:   Give the amount of tax the guild charges
 * Returns:       int - The tax amount
 */
int
query_guild_tax_lay() 
{ 
    return GUILD_TAX; 
}


/*
 * Function name:   query_enemy
 * Description:     Gives information of recorded enemies. If you want to
 *                  know currently fought enemy (if any) call query_attack()
 * Arguments:       arg: Enemy number (-1 == all enemies)
 * Returns:         Object pointer to the enemy
 */
public int
query_not_attack_me(object who, int aid)
{
    int success, weapon_skill, alco_skill;
    object attack_ob;
    mixed attack;
    string attack_desc;
    
    if (SW->query_prop(LIVE_I_STUNNED))
        return SW->query_not_attack_me(who, aid);

    if (random(sizeof( SW->query_enemy(-1) )))
        return SW->query_not_attack_me(who, aid);
	
    // STAGGER ONLY IF WE ARE MORE THEN 50% INTOXICATED.
    if ((100*SW->query_intoxicated() + 1) / (SW->intoxicated_max()+1) < 50)
        return SW->query_not_attack_me(who, aid);
   
    alco_skill = 100;
/*
    enemy_speed  = who->query_prop(LIVE_I_QUICKNESS);
    pirate_speed = SW->query_prop(LIVE_I_QUICKNESS);
*/  
    attack_ob = who->query_combat_object();
    attack = attack_ob->query_attack(aid);

    // ATTACK WAS PROBABLY MAGICAL OR SOMETHING...    
    if (attack == 0)
        return SW->query_not_attack_me(who, aid);

    attack_desc = attack_ob->cb_attack_desc(aid);
    weapon_skill = attack[ATT_SKILL];
/*
    success = SW->resolve_task(TASK_DIFFICULT,({TS_DEX, pirate_speed, alco_skill}),
              who,({weapon_skill * 2, SS_AWARENESS * 2, enemy_speed,}));
*/
    success = SW->resolve_task(TASK_ROUTINE,({TS_DEX, alco_skill}),
              who,({SS_AWARENESS, weapon_skill}));

    // STAGGER HAS NOT SUCCEDED
    if (success <= 0)
        return SW->query_not_attack_me(who, aid);
	
    switch (random(4))
    {
    case 0:
	SW->catch_msg("You begin to stagger violently first to the "+
		"left then to the right causing "+who->query_the_name(SW)+
		" to miss you completely with "+HIS(who) +" "+attack_desc+".\n");
	who->catch_msg(SW->query_The_name(who) +
		" staggers violently first to the left "+
		"then to the right, causing you to miss "+ HIM(SW)+
		" completely with your "+attack_desc+".\n");
	SW->tell_watcher(QCTNAME(SW)+" staggers violently around, first to "+
		"left then to the right, causing "+QTNAME(who)+ " to miss "+
		HIM(SW)+" completely with "+HIS(who)+
		attack_desc+".\n", who);
	break;

    case 1:
	SW->catch_msg("Your vision begins to blur as you quickly run "+
		"forward in an attempt to keep your balance. Your sudden "+
		"movement causes "+who->query_the_name(SW)+
		" to miss you with the blow.\n");
	who->catch_msg(SW->query_The_name(who) +
		" quickly runs forward in an attempt to keep "+ HIS(SW)+
		" balance: "+C(HIS(SW))+
		" sudden movement causes you to miss "+HIM(SW)+" with your blow.\n");
	SW->tell_watcher(QCTNAME(SW) +
		" quickly runs forward, in an attempt to keep "+HIS(SW)+
		" balance. "+C(HIS(SW))+" sudden movement causes "+
		QTNAME(who)+ " to miss "+HIM(SW)+" with "+HIS(who)+
		" blow.\n", who);
	break;

    case 2:
	SW->catch_msg("As "+who->query_the_name(SW)+
		" attempts to hit you with "+HIS(who)+ " "+attack_desc+
		", you manage to dodge the "+
		"attack by quickly staggering to the left.\n");
	who->catch_msg(SW->query_The_name(who) +
		" staggers quickly to the left, "+
		"causing you to miss "+ HIM(SW)+ " completely with "+
		"+your "+attack_desc+".\n");
	SW->tell_watcher(QCTNAME(SW) + " manages to dodge the attack by "+
		"quickly staggering to the left.\n", who);
	break;

    default:
	SW->catch_msg("As "+who->query_the_name(SW)+
		" attempts to hit you with "+HIS(who)+ " "+attack_desc+
		", you manage to dodge the "+
		"attack by quickly staggering to the right.\n");
	who->catch_msg(SW->query_The_name(who) +
		" staggers quickly to the right, "+
		"causing you to miss "+ HIM(SW)+ " completely with "+
		"your"+ attack_desc+".\n");
	SW->tell_watcher(QCTNAME(SW) + " manages to dodge the attack by "+
		"quickly staggering to the right.\n", who);
    }
    return 1;
}

/*
 * Function name: query_guild_style_lay
 * Description:   return the guild style for this guild
 * Returns:       string - the style
 */
string
query_guild_style_lay()
{
    return GUILD_STYLE;
}

/*
 * Function name: query_guild_name_lay
 * Description:   return the guild's name
 * Returns:       string - the guild name
 */
string
query_guild_name_lay()
{
    return GUILD_NAME;
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
    /* Allow everyone to join */
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

        set_alarm(1.0, 0.0, remove_lay_member);

        return 1;
    }

    return 1;
}

/* 
 * Function name: query_guild_not_allow_join_lay
 * Description:	  Check if we allow the player to join another guild.
 * Arguments:     player - the player
 *		  type, style, name - the type, style and name of the
 *			intended guild.
 * Returns:	  1 if we do not allow, else 0
 */
int
query_guild_not_allow_join_lay(object player, string type, string style,
				string name)
{
    /* This checks to make sure that the new guild is not layman */
    if (::query_guild_not_allow_join_lay(player, type, style, name))
        return 1;

    return 0;
}

/* Function name: query_guild_level_lay
 * Description:   What is the member's level within the guild?
 * Returns:       int - the level
 */
int
query_guild_level_lay()
{
    return MIN(MAX_GUILD_LEVEL, query_shadow_who()->query_stat(SS_LAYMAN) /8);
}
    

/*
 * Function name: query_guild_title_lay
 * Description:   Return the member's guild title
 * Returns:       string - the title
 */
string 
query_guild_title_lay()
{
    string title;

    if(shadow_who->test_bit("Ansalon",3,6))
    {
        if(query_shadow_who()->query_gender() == G_FEMALE)
            return FemaleTitles[query_guild_level_lay()] + " and Press Ganger of the Pirates";
        else
            return MaleTitles[query_guild_level_lay()] + " and Press Ganger of the Pirates";
    }

    if(shadow_who->test_bit("Ansalon",3,1))
    {
        return "Legendary Pirate King";
    }

    if(shadow_who->test_bit("ansalon",3,2))
    {
        if(query_shadow_who()->query_gender() == G_FEMALE)
            return FemaleTitles[query_guild_level_lay()] + " and Press Ganger of the Pirates";
        else
            return MaleTitles[query_guild_level_lay()] + " and Press Ganger of the Pirates";
    }

    if(query_shadow_who()->query_gender() == G_FEMALE)
        return FemaleTitles[query_guild_level_lay()];
    else
        return MaleTitles[query_guild_level_lay()];
}


/* Function name: query_def_post
 * Description:   We change the default post office for our members.
 * Returns:	  string - the path to the new postoffice
 */
string
query_def_post() 
{
    /* Only bother using the guild's post office if the player is
     * using the guild's start location.
     */
    //if (this_player()->query_default_start_location() == GUILD_STARTLOC)
   // {
    //    return GUILD_POST;
   // }

    return query_shadow_who()->query_def_post();
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
//    if (type == SS_SPECIAL_STAGGER)
//    {
//        return "alcohol lore";
//    }

    return 0;
}

/*
 * Function name: query_guild_trainer_lay
 * Description:   Returns the skill trainers for the guild
 * Returns:       string * - an array of paths to the guild's
 *                trainers.
 */
mixed
query_guild_trainer_lay()
{
    return ({ GUILD_ROOM + "pirate_train" });
}

/*
 * Function name: init_guild_member
 * Description:   Add necessary guild items to the player and
 *                do any other kind of initialization necessary.
 */
void
init_guild_member()
{
    object guild_emblem, who = query_shadow_who();

    /* clone the guild emblem and move it to the player */

    setuid();
    seteuid(getuid());

    if(!P("_pirates_sash_ansalon",who))
    {
        guild_emblem = clone_object(GUILD_EMBLEM);
        guild_emblem->move(who, 1);
    }

    /* add the guild's soul to the player */
    who->add_cmdsoul(GUILD_CMDSOUL);
    who->update_hooks();

    /* add the guild subloc */
    who->add_subloc(GUILD_SUBLOC, this_object());

    who->catch_msg("Welcome Pirate of the Bloodsea!\n");

    check_banished();
}

/*
 * Function name: start_player
 * Description:   This is called when the player logs in.
 */
public void
start_player()
{
    SW->start_player();
    set_alarm(2.5, 0.0, init_guild_member);
}

/* 
 * Function name: add_lay_shadow
 * Description:   Shadow an object with this shadow
 * Arguments:     object who - the object to shadow
 * Returns:       as shadow_me in /std/guild/guild_base.c
 */
int add_lay_shadow(object who)
{
    int ret = shadow_me(who, "layman", GUILD_STYLE, GUILD_NAME);

    if (ret == 1)
    {
        init_guild_member();
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
    {
        return me->show_subloc(subloc, me, for_obj);
    }

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    {
	return "";
    }

    if (for_obj == me)
    {
	str = "You have ";
    }
    else
    {
	str = capitalize(me->query_pronoun()) + " has ";
    }

    return str + "the mark of a " + GUILD_NAME + ".\n";
}

/*
 * Function name: remove_lay_member
 * Description:   remove this member from the guild
 */
void
remove_lay_member()
{
    object emblem, who = query_shadow_who();

    /* Remove special skills */ 
//    who->remove_skill(SS_GUILD_SPECIAL_SKILL);

    /* Clear the player's guild stat */
    who->clear_guild_stat(SS_LAYMAN);

    // Clear the press ganger bits.
    if (who->test_bit("ansalon",3,2))
        who->clear_bit(3,2);

    /* Remove any instances of the guild emblem on the player */
    while (emblem = present(GUILD_EMBLEM_ID, who))
    {
        emblem->remove_object();
    }

    /* If the player is using our start location, remove it */
    if (who->query_default_start_location() == GUILD_STARTLOC)
    {
        who->set_default_start_location(who->query_def_start());
    }

    /* Remove the guild soul */
    who->remove_cmdsoul(GUILD_CMDSOUL);
    who->update_hooks();

    /* Remove the guild shadow.  This also resets tax to 0. */
    remove_guild_lay();
}


/* Check the log file to see if this player has been banished by the 
   Pirate King, if he has, remove him from the guild and log it.
*/
void
check_banished()
{
    mixed names, names_tmp = ({});
    string output = "", name, t, outputw = "";
    int size, i = -1, pos;

    names = explode(read_file(GUILD_LOG+"pirate_log.txt"), "\n");

    size = sizeof(names);
    while(++i < size)
    {
        if ((pos = sscanf(names[i], "%s banished %s", name, t)) == 2)
      	{
            if (member_array(name, names_tmp) == -1)
                    names_tmp += ({ name });

        }
        else
        {
            if (sscanf(names[i], "%s left %s", name, t) == 2)
	        if ((pos = member_array(name, names_tmp)) != -1)
                names_tmp = exclude_array(names_tmp, pos, pos);
        }
    }

    size = sizeof(names_tmp);
    i = -1;

    while(++i < size)
    {
        if (names_tmp[i] == query_shadow_who()->query_met_name())
        {
//          we clear the ganger bit so upon next joining noone will mess things up.
            if(query_shadow_who()->test_bit("ansalon",3,6))
          	    query_shadow_who()->clear_bit(3, 6);
 
            write("------------------------------------------------------------------------\n");
            write("You have been forced to walk the plank back the life of the land lubber!\n");
            write("You have been banished from the Pirates of the Bloodsea!\n");
            write("------------------------------------------------------------------------\n");
            query_shadow_who()->command("$sigh");
            write_file(GUILD_LOG+"pirate_log.txt", TP->query_name() + " left " + 
                       extract(ctime(time()), 4, 15)+
                       ", StatAvg: "+TP->query_average_stat()+
                       ", Race: "+TP->query_race()+
                       ", Align: "+TP->query_alignment()+"\n");

//          if the player starts in the guild. Transport him out of the guild.
             if (query_shadow_who()->query_default_start_location() == GUILD_STARTLOC)
                 query_shadow_who()->move_living("the room", GUILD_ROOM + "pirate_cave.c", 1, 0);

            remove_lay_member();
        }
    }
}