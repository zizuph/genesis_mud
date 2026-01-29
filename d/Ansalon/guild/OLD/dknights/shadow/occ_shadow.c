/*
 * File Name        : occ_shadow.c
 * By               : Elmore.
 * Date             : April, 2001.
 * Desc             : Occ branch of the Death Knights of Krynn.
 *                    Contains the fighter part of the DK's.
 */

#pragma strict_types

inherit "/std/guild/guild_occ_sh";

#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/dargaard/local.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <options.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <macros.h>
#include "reap.c"
#include "dassault.c"

static string *MaleTitles = ({
    "Dark Squire of Dargaard Keep",
    "Ashen Squire of Dargaard Keep",
    "Blackened Squire of Dargaard Keep",
    "Knight of the Iron Crown",
    "Death Warrior of Dargaard Keep",
    "Lord Death Warrior of Dargaard Keep",
    "Lord of the Iron Crown",
    "Knight of the Burning Sword",
    "Ashen Clerist of Dargaard Keep",
    "Black Clerist of Dargaard Keep",
    "Lord of the Burning Sword",
    "Knight of the Black Rose",
    "Death Knight of Pain",
    "Death Knight of Blood",
    "Death Knight of Dargaard Keep",
    "Lord Death Knight of Dargaard Keep",
    "Lord of the Black Rose"
    });

static string *FemaleTitles = ({
    "Dark Squire of Dargaard Keep",
    "Ashen Squire of Dargaard Keep",
    "Blackened Squire of Dargaard Keep",
    "Knight of the Iron Crown",
    "Death Warrior of Dargaard Keep",
    "Lady Death Warrior of Dargaard Keep",
    "Lady of the Iron Crown",
    "Knight of the Burning Sword",
    "Ashen Clerist of Dargaard Keep",
    "Black Clerist of Dargaard Keep",
    "Lady of the Burning Sword",
    "Knight of the Black Rose",
    "Death Knight of Pain",
    "Death Knight of Blood",
    "Death Knight of Dargaard Keep",
    "Lady Death Knight of Dargaard Keep",
    "Lady of the Black Rose"
});

/* strings that contain the alternative adjectives for this */
/* guild                                                    */
string adj1,adj2;


/* Prototypes */
void remove_occ_member();

/* 
 * Function name: query_guild_tax_occ
 * Description:   Give the amount of tax the guild charges
 * Returns:       int - The tax amount
 */
int
query_guild_tax_occ() 
{ 
    if (query_shadow_who()->test_bit("ansalon",3,8))
        return TAX_ARRAY[3];

    if (query_shadow_who()->test_bit("ansalon",3,9))
        return TAX_ARRAY[2];

    if (query_shadow_who()->test_bit("ansalon",3,10))
        return TAX_ARRAY[1];

    return TAX_ARRAY[0];
}

/*
 * Function name: query_guild_style_occ
 * Description:   return the guild style for this guild
 * Returns:       string - the style
 */
string
query_guild_style_occ()
{
    return GUILD_STYLE;
}

/*
 * Function name: query_guild_name_occ
 * Description:   return the guild's name
 * Returns:       string - the guild name
 */
string
query_guild_name_occ()
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
    if (shadow_who->query_race_name() == "human")
        return "Lord Soth does not allow your race in his undead army.\n";
    else
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

        set_alarm(1.0, 0.0, remove_occ_member);

        return 1;
    }

    return 1;
}

/* 
 * Function name: query_guild_not_allow_join_occ
 * Description:	  Check if we allow the player to join another guild.
 * Arguments:     player - the player
 *		  type, style, name - the type, style and name of the
 *			intended guild.
 * Returns:	  1 if we do not allow, else 0
 */
int
query_guild_not_allow_join_occ(object player, string type, string style,
				string name)
{
    /* This checks to make sure that the new guild is not occ */
    if (::query_guild_not_allow_join_occ(player, type, style, name))
        return 1;

    return 0;
}

/* Function name: query_guild_level_occ
 * Description:   What is the member's level within the guild?
 * Returns:       int - the level
 */
int
query_guild_level_occ()
{
            /**************************************
             * Find the OCC title using the bits: *
             * - 3,6  = Guildmaster.              *
             * - 3,7  = Council member.           *
             * - 3,8  = Rose Knight.              *
             * - 3,9  = Sword Knight.             *
             * - 3,10 = Crown Knight.             *
             **************************************/


    if (query_shadow_who()->test_bit("ansalon",3,9))
        return MIN(MAX_GUILD_LEVEL_ROSE, query_shadow_who()->query_stat(SS_OCCUP) / 14);

    if (query_shadow_who()->test_bit("ansalon",3,8))
        return MIN(MAX_GUILD_LEVEL_SWORD, query_shadow_who()->query_stat(SS_OCCUP) / 14);

    if (query_shadow_who()->test_bit("ansalon",3,7))
        return MIN(MAX_GUILD_LEVEL_CROWN, query_shadow_who()->query_stat(SS_OCCUP) / 14);

    return MIN(MAX_GUILD_LEVEL_SQUIRE, query_shadow_who()->query_stat(SS_OCCUP) / 14);
}
    

/*
 * Function name: query_guild_title_occ
 * Description:   Return the member's guild title
 * Returns:       string - the title
 */
string 
query_guild_title_occ()
{
    // Is the person the guildmaster?
    if (query_shadow_who()->test_bit("ansalon",3,11))
    {
        if(query_shadow_who()->query_gender() == G_FEMALE)
        {
            return FemaleTitles[query_guild_level_occ()] +
            " and Right Hand of Lord Soth";
        }
        else
        {
            return MaleTitles[query_guild_level_occ()]+
            " and Right Hand of Lord Soth";
        }
    }

    // Is the person a member of the council.
    if (query_shadow_who()->test_bit("ansalon",3,10))
    {
        if(query_shadow_who()->query_gender() == G_FEMALE)
        {
            return FemaleTitles[query_guild_level_occ()] +
            " and Fervent Follower of Lord Soth";
        }
        else
        {
            return MaleTitles[query_guild_level_occ()]+
            " and Fervent Follower of Lord Soth";
        }
    }

    if(query_shadow_who()->query_gender() == G_FEMALE)
        return FemaleTitles[query_guild_level_occ()];
    else
        return MaleTitles[query_guild_level_occ()];
}


/* Function name: query_def_post
 * Description:   We change the default post office for our members.
 * Returns:	  string - the path to the new postoffice
 */
string
query_def_post() 
{
//    return query_shadow_who()->query_def_post();
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
    if (type == SS_GUILD_SPECIAL_DASSAULT)
    {
        return "assault";
    }
    if (type == SS_GUILD_SPECIAL_REAP)
    {
        return "reap";
    }

    return 0;
}

/*
 * Function name: query_guild_trainer_occ
 * Description:   Returns the skill trainers for the guild
 * Returns:       string * - an array of paths to the guild's
 *                trainers.
 */
mixed
query_guild_trainer_occ()
{
    return ({GUILD_ROOM + "dknight_train", GUILD_ROOM + "laboratory"});
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
    object regen_object;
    int i;
    object *membs;

    /* clone the guild emblem and move it to the player */
    setuid();
    seteuid(getuid());
    
    if (guild_emblem = clone_object(GUILD_EMBLEM))
    {    
        guild_emblem->move(who, 1);
    }

    /* add the guild's soul to the player */
    who->add_cmdsoul(GUILD_CMDSOUL);
    who->update_hooks();

    /* add the different props */
    regen_object = clone_object(GUILD_OBJ + "regen_obj");
    regen_object->move(who,1);

    who->add_subloc(GUILD_SUBLOC, TO);
    who->add_prop(LIVE_I_NO_CORPSE, 1);
    who->add_prop(MAGIC_I_BREATH_WATER, 1);
    who->add_prop(LIVE_I_UNDEAD,"@@query_guild_stat@@");
    who->add_prop(MAGIC_I_RES_MAGIC,"@@query_resistance_stat@@");

    //Dont show the 'enter game' message if the player has just joined the guild.
    if (!who->query_prop(I_SOLVED_STEP_5))
    {
        who->catch_msg("You awaken in the strench of you own rotten flesh, still trapped on this mortal "+
                       "plane, still cursed...Hail Death Knight!\n");
    }

    membs = users();
    for(i=0;i<sizeof(membs);i++)
    {            
        if(IS_DK(membs[i])) 
        {
            tell_object(membs[i],"You hear the banshees song in you mind, "+
                                 "all crying out that " +who->query_name()+
                                 " has entered the World of Krynn.\n"); 
        }
     }
}


/*
 * Function name: start_player
 * Description:   This is called when the player logs in.
 */
public void
start_player()
{
    SW->start_player();
    set_alarm(1.0, 0.0, init_guild_member);
}


/* 
 * Function name: add_occ_shadow
 * Description:   Shadow an object with this shadow
 * Arguments:     object who - the object to shadow
 * Returns:       as shadow_me in /std/guild/guild_base.c
 */
int add_occ_shadow(string adjs, object who)
{
    int ret;

    if(stringp(adjs))
        ret = shadow_me(who, "occupational", GUILD_STYLE, GUILD_NAME, adjs);
    else
        ret = shadow_me(who, "occupational", GUILD_STYLE, GUILD_NAME);

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
 *		  arm - The looker
 * Returns:	  The string the looker shall see
 */
string
show_subloc(string subloc, object me, object arm)
{
    string str;

    if (subloc != GUILD_SUBLOC)
    {
        return me->show_subloc(subloc, me, arm);
    }

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    {
	return "";
    }

    if (query_shadow_who()->test_bit("ansalon",3,9))
    {
        if (arm == me)
        {
            if(P(DKNIGHT_PLATEMAIL,query_shadow_who()))
            {
	        str = "Your blackened solamnic platemail is decorated with the burnt "+
                      "symbol of the Rose Order.\n"+
                      "An aura of darkness and death surrounds you.\n";
            }
            else
            {
	        str = "Your charred crystal ring is decorated with the burnt "+
                      "symbol of the Rose Order.\n"+
                      "An aura of darkness and death surrounds you.\n";
            }
        }
        else
        {
            if(P(DKNIGHT_PLATEMAIL,query_shadow_who()))
            {
	        str = capitalize(HIS(me)) + " blackened solamnic platemail is decorated with the burnt "+
                      "symbol of the Rose Order.\n"+
                      "An aura of darkness and death surrounds " +HIM(me)+ ".\n";
            }
            else
            {
	        str = capitalize(HIS(me)) + " charred crystal ring is decorated with the burnt "+
                      "symbol of the Rose Order.\n"+
                      "An aura of darkness and death surrounds " +HIM(me)+ ".\n";
            }
        }
        return str;
    }

    if (query_shadow_who()->test_bit("ansalon",3,8))
    {
        if (arm == me)
        {
            if(P(DKNIGHT_PLATEMAIL,query_shadow_who()))
            {
	        str = "Your blackened solamnic platemail is decorated with the blackened symbol of the "+
                      "Sword Order.\n"+
                      "Small flames dance between the cracks in your armour.\n";
            }
            else
            {
	        str = "Your charred crystal ring is decorated with the blackened symbol of the "+
                      "Sword Order.\n"+
                      "Small flames dance between the cracks in your armour.\n";
            }

        }
        else
        {
            if(P(DKNIGHT_PLATEMAIL,query_shadow_who()))
            {
	        str = capitalize(HIS(me)) + " blackened solamnic platemail is decorated with the blackened "+
                      "symbol of the Sword Order.\n"+
                      "Small flames dance between the cracks in " +HIS(me)+ " armour.\n";
            }
            else
            {
	        str = capitalize(HIS(me)) + " charred crystal ring is decorated with the blackened "+
                      "symbol of the Sword Order.\n"+
                      "Small flames dance between the cracks in " +HIS(me)+ " armour.\n";
            }
        }
        return str;
    }

    if (query_shadow_who()->test_bit("ansalon",3,7))
    {
        if (arm == me)
        {
            if(P(DKNIGHT_PLATEMAIL,query_shadow_who()))
            {
  	        str = "Your blackened solamnic platemail is decorated with the faded symbol of the Crown Order.\n"+
                      "You bear the tattered emblem of Dargaard Keep.\n";
            }
            else
            {
  	        str = "Your charred crystal ring is decorated with the faded symbol of the Crown Order.\n"+
                      "You bear the tattered emblem of Dargaard Keep.\n";
            }
        }
        else
        {
            if(P(DKNIGHT_PLATEMAIL,query_shadow_who()))
            {
	        str = capitalize(HIS(me)) + " blackened solamnic platemail is decorated with the faded "+
                      "symbol of the Crown Order.\n"+
                      ""+capitalize(HE(me))+" bears the tattered emblem of Dargaard Keep.\n";
            }
            else
            {
	        str = capitalize(HIS(me)) + " charred crystal ring is decorated with the faded "+
                      "symbol of the Crown Order.\n"+
                      ""+capitalize(HE(me))+" bears the tattered emblem of Dargaard Keep.\n";
            }
        }
        return str;
    }

    if (arm == me)
    {
        str = "You bear the tattered emblem of Dargaard Keep.\n";
    }
    else
    {
        str = capitalize(HE(me))+" bears the tattered emblem of Dargaard Keep.\n";
    }
    return str;
    
}

/*
 * Function name: remove_occ_member
 * Description:   remove this member from the guild
 */
void
remove_occ_member()
{
    object emblem, who = query_shadow_who();

    who->remove_skill(SS_GUILD_SPECIAL_DASSAULT);
    who->remove_skill(SS_GUILD_SPECIAL_REAP);

    who->clear_guild_stat(SS_OCCUP);

    while (emblem = present(GUILD_EMBLEM_ID, who))
    {
        emblem->remove_object();
    }

    /* If the player is using our start location, remove it */
    if (who->query_default_start_location() == GUILD_STARTLOC)
    {
        who->set_default_start_location(who->query_def_start());
    }
   
    // Remove the bits.
    if (who->test_bit("ansalon",3,12))
        who->clear_bit(3,12);

    if (who->test_bit("ansalon",3,11))
        who->clear_bit(3,11);

    if (who->test_bit("ansalon",3,10))
        who->clear_bit(3,10);

    if (who->test_bit("ansalon",3,9))
        who->clear_bit(3,9);

    //The player is a council member.
    if (who->test_bit("ansalon",3,8))
        who->clear_bit(3,8);

    //The player is the guildmaster
    if (who->test_bit("ansalon",3,7))
        who->clear_bit(3,7);

    /* Remove the guild soul */
    who->remove_cmdsoul(GUILD_CMDSOUL);
    who->update_hooks();

    /* Remove the guild shadow.  This also resets tax to 0. */
    remove_guild_occ();
}

/*
 * Function name:       eat_food
 * Description:         Eats a certain amount of food.
 * Arguments:           amount: The amount of food.
 *                      ask: True if we only want to know IF we can eat this
 * Returns:             True if successfully eaten.
 */
public int
eat_food(int amount, int ask)
{
    write("Since you are an undead, you find it impossible to eat any food.\n");
    return 0;
}


/*
 * Function name:       drink_alco
 * Description:         Drinks alcohol of a certain potency
 * Arguments:           strength: The strength of the drink
 *                      ask: True if we only want to know IF we can drink this
 * Returns:             True if successfully drunk.
 */
public int
drink_soft(int amount, int ask)
{
    write("Since you are an undead, you find it impossible to drink anything.\n");
    return 0;
}


/*
 * Function name:       drink_soft
 * Description:         Drinks a certain amount of liquid
 * Arguments:           amount: The amount of the drink
 *                      ask: True if we only want to know IF we can drink this
 * Returns:             True if successfully drunk.
 */
public int
drink_alco(int strength, int ask)
{
    write("Since you are an undead, you find it impossible to drink anything.\n");
    return 0;
}


/*
 * Function name: wear_arm
 * Description:   wear an armour
 * Arguments:     The armour to be worn
 * Returns:       string - error message (armour could not be worn)
 *                1 - success (armour was worn)
 *
 *
 */
public mixed
wear_arm(object arm)
{
    object sh;
    mixed *adjs;
    int i = 0;
    int num, color_found;
    string current_desc = query_shadow_who()->short();

    adjs = arm->query_adjs();
    num = sizeof(adjs) - 1;   
 
    while (i <= num)
    {
        if (adjs[i] == "blackened" || adjs[i] == "charred" || arm->query_prop(DARGAARD_ARMOUR)) 
            color_found = 1;
        i++;
    }

    if (color_found == 0)
    {
        write("As you wear the "+arm->short()+ " flames surrounds the "+
              "armour, and it becomes blackened and charred.\n");
        arm->add_adj("blackened");
        arm->set_short("blackened " + arm->short());
        arm->set_ac(0);
        arm->set_may_not_recover();

        /* Clone the blackened armour shadow */
//        setuid();
//        seteuid(getuid());
//        sh = clone_object("/d/Ansalon/guild/dknights/shadow/arm_shadow");
//        sh->shadow(arm); 

        /* Add the shadow to the death knights autoshadow list. */
   //     query_shadow_who()->add_autoshadow("/d/Ansalon/guild/dknights/shadow/arm_shadow");
    }
    ::query_shadow_who()->wear_arm(arm);
}


public void
do_die(object killer)
{
    object room = E(TP);
    object bones, death_flag;
    object *obs = users();
    int i;
    
    shadow_who->catch_msg("You burst into flames and disappear...\n");
    tell_room(room, ""+QCTNAME(query_shadow_who())+ " bursts into flames, leaving "+
                    "only a pile of bones and ash as "+HE(query_shadow_who())+
                    " disappears.\n", ({ shadow_who }));

/*  Move the humans bones to the location where the death knight died. */
    bones = clone_object(GUILD_OBJ + "dknight_bones");
    bones->move(room, 1);

    for(i = 0; i < sizeof(obs); i++)
    {
        if(IS_DK(obs[i]))
            tell_object(obs[i],"The banshees scream out in agony and you feel an intense pain "+ 
                               "through your bones as "+shadow_who->query_name()+ " is destroyed.\n");
    }

/*  Move the death-flag to the death knight, so that he will start in the guild
    and not in Sparkle when he enteres the game again. */
    setuid();
    seteuid(getuid());

    death_flag = clone_object(GUILD_OBJ + "death_flag");
    death_flag->move(query_shadow_who());

    query_shadow_who()->do_die(killer);
}


/* return the guild stat, for the LIVE_I_UNDEAD prop */
int
query_guild_stat()
{
    return MIN(100,shadow_who->query_base_stat(SS_OCCUP));
}

/* return the guild stat, for the MAGIC_I_MAGIC_RES prop */
int
query_resistance_stat()
{
    return MIN(75,shadow_who->query_base_stat(SS_OCCUP) / 2);
}


/* Add something special for the titlel presentation */
public string
query_gender_string()
{
    return "undead";
}



/* Setting up the adjectives of the player */
void
set_dk_adj1(string adj)
{
    adj1 = adj;
}


void
set_dk_adj2(string adj)
{
    adj2 = adj;
}


string
query_dk_adj1()
{
    return adj1;
}


string
query_dk_adj2()
{
    return adj2;
}


/* Get the alternative adjectives */

mixed
query_adj(int i)
{
    if(!adj1 && !adj2)
        return shadow_who->query_adj(i);
    if(i)
        return ({adj1,adj2});
    return adj1;
}


/* Initialize shadow and set the alternative adjectives, if there */
/* are any  */
string *
parse_command_adjectiv_id_list()
{
    string *str;
    str = shadow_who->parse_command_adjectiv_id_list();
    str += ({adj1,adj2,"undead"});
    return str;
}

public void
init_occ_shadow(string arg)
{
    if(stringp(arg))
       sscanf(arg,"%s,%s",adj1,adj2);
}


/* Overwrite the hit_me method, so that the death knight will recieve double
   damage from holy weapons.    */
varargs public mixed
hit_me(int wcpen, int dt, object attacker, int attack_id, int target_hitloc = -1) 
{
    object *weps = filter(attacker->query_weapon(-1), &operator(==)(attack_id) @ &->query_attack_id());

    if (sizeof(weps)) // attacker does use a weapon for this attack
	if (member_array("holy", weps[0]->query_adjs()) > -1) // used weapon is holy
	{
	    wcpen *= 2;
	    shadow_who->catch_tell("The "+weps[0]->short(shadow_who)+" severely burns you.\n");
	}

    return shadow_who->hit_me(wcpen, dt, attacker, attack_id, target_hitloc);
}


void
remove_object()
{
    int i;
    object *obs = users();
    if(calling_function(-1) == "quit")
    {
        for(i = 0; i < sizeof(obs); i++)
        {
            if(IS_DK(obs[i]))
                tell_object(obs[i],"The banshees goes silent as as "+shadow_who->query_name()+
                                   "departs to the Abyss.\n");
        }
     }
    shadow_who->remove_object();
}


void
linkdeath_hook(int i)
{
    int j;
    object *membs = users();    

    for(j = 0; j < sizeof(membs);j++)
    {
        if(IS_DK(membs[j]))
        {
            if(i == 1)
                tell_object(membs[j],"The banshees song pause for a moment "+
                                     "as "+shadow_who->query_name()+ " enters the "+
                                     "Void.\n"); 
             if(i == 0)
                tell_object(membs[j],"The banshees song resumes their song "+
                                     "as "+shadow_who->query_name()+ " returns to "+
                                     "the World of Krynn.\n"); 
        }
    }
    shadow_who->linkdeath_hook(i);
}

