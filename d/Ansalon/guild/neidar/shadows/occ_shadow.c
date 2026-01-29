/*
 *  Carnak 2016-12-28:      Added the query_guild_keep_player to the function
 *                          init_guild_member (and commented out DEBUG messages)
 *                          to fix an issue with guild members not being
 *                          punishable.
 *
 *  Arman 2019-04-24:       Added features associated with the Doomseeker
 *                          faction of the Neidar dwarves.
 */

#pragma strict_types

inherit "/std/guild/guild_occ_sh";

#include "../guild.h"
#include "/d/Krynn/clubs/warfare/defs.h"

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <time.h>
#include <language.h>
#include <formulas.h>

#define GUILD_SUBLOC  GUILD_NAME + " subloc"
#define MAX_GUILD_LEVEL 24
#define MAX_DOOM_LEVEL 13
#define PUNISH_FILE     SAVE_PATH + "punish"
#define RETIRED_FILE    SAVE_PATH + "elder_retired"

#define ARMYMASTER      "/d/Krynn/common/warfare/armymaster"

#define CLANTITLE_NUM   query_shadow_who()->query_skill(SS_CLANTITLE)
#define MIN_CLANTITLE   0
#define MAX_CLANTITLE   8

#define MEMBERS ("/d/Ansalon/log/" + MEMBERS_LOG)

#define LIVE_I_NO_DRAGONFEAR   ("_live_i_no_dragonfear")

#define HIS(x)        ((x)->query_possessive())
#define HE(x)         ((x)->query_pronoun())

#define DOOM_SKIN     (GUILD_SPECIALS + "doom_skin")

static string *titles = ({"Bloodbrother of the Neidar Clan",
  "Clansman of Iron Delving",
  "Shieldbearer of Iron Delving",
  "Solemn Shieldbearer of Iron Delving",
  "Raw Axeman of Iron Delving",
  "Axeman of Iron Delving",
  "Hardened Axeman of Iron Delving",
  "Bold Axeman of Iron Delving",
  "Warrior of the Neidar Clan",
  "Scarred Warrior of the Neidar Clan",
  "Experienced Warrior of the Neidar Clan",
  "Respected Warrior of the Neidar Clan",
  "Skilled Warrior of the Neidar Clan",
  "Fierce Warrior of the Neidar Clan",
  "Venerable Warrior of the Neidar Clan",
  "Battlerager of the Neidar Clan",
  "Stubborn Battlerager of the Neidar Clan",
  "Wild Battlerager of the Neidar Clan",
  "Fearless Battlerager of the Neidar Clan",
  "Mighty Ogreslayer of the Neidar Clan",
  "Renowned Trollslayer of the Neidar Clan",
  "Epic Giantslayer of the Neidar Clan",
  "Legendary Hero of the Neidar Clan",
  "Clan Warleader of the Hill Dwarves",
  "Clan Chieftain of the Hill Dwarves",});

static string *ftitles = ({"Bloodsister of the Neidar Clan",
  "Maiden of Iron Delving",
  "Shieldbearer of Iron Delving",
  "Solemn Shieldbearer of Iron Delving",
  "Raw Axemaiden of Iron Delving",
  "Axemaiden of Iron Delving",
  "Hardened Axemaiden of Iron Delving",
  "Bold Axemaiden of Iron Delving",
  "Warrior of the Neidar Clan",
  "Whiskered Warrior of the Neidar Clan",
  "Experienced Warrior of the Neidar Clan",
  "Respected Warrior of the Neidar Clan",
  "Skilled Warrior of the Neidar Clan",
  "Fierce Warrior of the Neidar Clan",
  "Venerable Warrior of the Neidar Clan",
  "Battlerager of the Neidar Clan",
  "Stubborn Battlerager of the Neidar Clan",
  "Wild Battlerager of the Neidar Clan",
  "Fearless Battlerager of the Neidar Clan",
  "Mighty Ogreslayer of the Neidar Clan",
  "Renowned Trollslayer of the Neidar Clan",
  "Epic Giantslayer of the Neidar Clan",
  "Legendary Heroine of the Neidar Clan",
  "Clan Warleader of the Hill Dwarves",
  "Clan Matriarch of the Hill Dwarves",});

static string *mclantitles = ({ "Warrior of the Neidar Clan",
                                "Warrior of the Neidar Clan",
                                "Battlerager of the Neidar Clan",
                                "Ogreslayer of the Neidar Clan",
                                "Trollslayer of the Neidar Clan",
                                "Giantslayer of the Neidar Clan",
                                "Hero of the Neidar Clan",
                                "Clan Warleader of the Hill Dwarves",
                                "Shieldbearer of the Neidar Clan",
                             });

static string *fclantitles = ({ "Warrior of the Neidar Clan",
                                "Warrior of the Neidar Clan",
                                "Battlerager of the Neidar Clan",
                                "Ogreslayer of the Neidar Clan",
                                "Trollslayer of the Neidar Clan",
                                "Giantslayer of the Neidar Clan",
                                "Heroine of the Neidar Clan",
                                "Clan Warleader of the Hill Dwarves",
                                "Shieldbearer of the Neidar Clan",
                             });

static string *doomtitles = ({  "Honour-seeking Pilgrim of the Hill Dwarves",
                                "Oathsworn Doomseeker of the Hill Dwarves",
                                "Unfulfilled Doomseeker of the Hill Dwarves",
                                "Bloodied Doomseeker of the Hill Dwarves",
                                "Committed Doomseeker of the Hill Dwarves",
                                "Reckless Doomseeker of the Hill Dwarves",
                                "Dangerous Doomseeker of the Hill Dwarves",
                                "Death-seeking Doomslayer of the Hill Dwarves",
                                "Deeply-scarred Doomslayer of the Hill Dwarves",
                                "Death-dealing Doomslayer of the Hill Dwarves",
                                "Devastating Doomslayer of the Hill Dwarves",
                                "Supreme Doomslayer of the Hill Dwarves",
                                "Almighty Doomslayer of the Hill Dwarves",
                                "Invincible Doomslayer of the Hill Dwarves",
                             });
                                
string *punishlist = ({ });
string *retiredlist = ({ });

static object   skin_obj;

void
death_mark_initiated()
{
    shadow_who->catch_msg("You receive a message from the Thane of the Neidar:\n\n"+   
        "     _____________________________________________________ \n"+
        "    / \\                                                   \\ \n"+
        "   /___|                                                   | \n"+
        "   |\\_/___________________________________________________/ \n"+
        "    \\                                                     \\ \n"+
        "     \\                                                     \\ \n"+
        "      |   Your dishonour has extended beyond the pale       | \n"+
        "      |   of acceptance to the Hill Dwarves of Krynn.       | \n"+
        "      |                                                     | \n"+
        "      |   Your Thane has death-marked you. No longer        | \n"+
        "      |   are you shunned, but actively hunted to           | \n"+
        "      |   expunge the shame you have caused the dwarven     | \n"+
        "      |   nations. Upon your death you will be expelled     | \n"+
        "      |   from the Neidar Clan.                             | \n"+
        "      |                                                     | \n"+
        "     /                                                     / \n"+
        "    /_____________________________________________________/_ \n"+
        "   |/\\                                                      \\ \n"+
        "   \\\\_|                                                      | \n"+
        "    \\/______________________________________________________/ \n\n\n");

     return;
}

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
    setuid();
    seteuid(getuid());

    if (ADMIN_MANAGER->query_is_doomseeker(query_shadow_who()))
        return DOOM_TAX;
    else
        return GUILD_TAX; 
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

public object
query_doomseeker_skin()
{
    if (!objectp(skin_obj))
    {
        if(LOAD_ERR(DOOM_SKIN))
            return 0;
        
        setuid();
        seteuid(getuid());
        
        skin_obj = clone_object(DOOM_SKIN);
    }
    
    return skin_obj;
}

/*
 * Function name: acceptable_neidar_member
 * Description:   test to see if the player is an acceptable member of this
 *                guild.
 * Arguments:     object who - the player to test
 * Returns:       0 or a string message saying why the player isn't acceptable
 */
mixed
acceptable_neidar_member(object who)
{
    /* throw out non-dwarves */
    if((who->query_race() != "dwarf") && (who->query_race() != "ghost"))
    {
    /*    who->catch_tell("DEBUG: You were not a dwarf and therefore " +
                        "not an acceptable member, you were a : " + 
                        who->query_race()+".\n");
                        */
        return "Only dwarves can be a member of this clan!\n";
    }

    if((who->query_region_title() == "kayolin mountain dwarf") ||
       (who->query_region_title() == "thorbardin mountain dwarf") ||
       (who->query_region_title() == "zhakar mountain dwarf"))
    {
    /*    who->catch_tell("DEBUG: You were not an acceptable member " +
                        "because you were a dwarf from the wrong region.\n");
                        */
        return "Only hill dwarves may be a member of the clan! Not " +
               "Mountain dwarves!\n";
    }

    if(who->query_race_name() == "gully dwarf")
    {
    /*    who->catch_tell("DEBUG: You were not an acceptable member " +
                        "because you were a Gully Dwarf.\n");
                        */
        return "Gully dwarves may not be clan members!!!\n";
    }

    if(who->query_race_name() == "minotaur")
    {
    /*    who->catch_tell("DEBUG: You were not an acceptable member " +
                        "because you were a minotaur.\n");
                        */
        return "Minotaurs may not be clan members!!!\n";
    }

    if(who->query_race_name() == "ogre")
    {
    /*    who->catch_tell("DEBUG: You were not an acceptable member " +
                        "because you were an ogre.\n");
                        */
        return "Ogres may not be clan members!!!\n";
    }

    if(who->query_guild_member("Angmar Army"))
    {
    /*    who->catch_tell("DEBUG: You were not an acceptable member " +
                        "because you were an angmar.\n");
                        */
        return "We don't want goblin kissing soldiers in the clan!\n";
    }
    return 0;
}

void
banish_member()
{
    restore_object(PUNISH_FILE);

    if(query_shadow_who()->test_bit("Ansalon",3,4) &&
       query_shadow_who()->test_bit("Ansalon",3,3))
    {
        return;
    }

    write("Two gruff looking dwarves approach you, the " +
      "larger one saying: You have been exiled from the Clan by " +
      "the Thane of the Hill Dwarves! You are no longer welcome " +
      "in Iron Delving!\nTwo gruff looking dwarves storm off.\n");
    say("Two gruff looking dwarves approach " +QTNAME(query_shadow_who())+
      ", the larger of the two saying: You have been exiled from " +
      "the Clan by the Thane of the Hill Dwarves! You are no longer "+
      "welcome in Iron Delving!\nTwo gruff looking dwarves " +
      "storm off.\n");
    query_shadow_who()->set_bit(3,4);
    query_shadow_who()->set_bit(3,3);
}

void
retire_elder()
{

    string str = query_shadow_who()->query_real_name();

    write("You have been retired as an advisor of the Thane.\n");
    restore_object(RETIRED_FILE);
    retiredlist -= ({str});
    save_object(RETIRED_FILE);
    if(BANISHED(query_shadow_who()))
    {
        return;
    }
    query_shadow_who()->clear_bit(3,4);
}


/* 
 * Function name: query_guild_keep_player
 * Description:   Test if we want to keep the player in the guild.
 * Arguments:     ob - the player.
 * Returns:       1 if keeping, 0 if not.
 */
int
query_guild_keep_player(object ob)
{
    mixed why;
    string str = query_shadow_who()->query_real_name();

    if (stringp(why = acceptable_neidar_member(ob)))
    {
        ob->catch_msg(why);

        /* Normally we would just return 0 here, and the player would be
         * removed from the guild.  We want to make sure a few cleanup
         * actions happen, though, so we'll return 1 here and remove
         * the member ourselves.
         */
         
    /*    query_shadow_who()->catch_tell("DEBUG: You are removed as occ " +
        "member because you were not an acceptable member.\n");
        */
        set_alarm(1.0, 0.0, remove_occ_member);

        return 1;
    }

    if (EXILE_MASTER->query_is_exile(str))
    {
    /*    query_shadow_who()->catch_tell("DEBUG: You were banished since " +
        "you were exiled.\n");
        */
        set_alarm(2.0, 0.0, banish_member);
    }
    else if (member_array(str, punishlist) >= 0)
    {
    /*    query_shadow_who()->catch_tell("DEBUG: You were banished because " +
        "you were on the punish list.\n");
        */
        set_alarm(2.0, 0.0, banish_member);
    }
    else if (member_array(str, retiredlist) >= 0)
    {
    /*    query_shadow_who()->catch_tell("DEBUG: You were retired from being " +
        "an eldar as you were on the retire elder list.\n");
        */
        set_alarm(3.0,0.0, retire_elder);
    }
    return 1;
}



/* 
 * Function name: query_guild_not_allow_join_occ
 * Description:          Check if we allow the player to join another guild.
 * Arguments:     player - the player
 *                  type, style, name - the type, style and name of the
 *                        intended guild.
 * Returns:          1 if we do not allow, else 0
 */
int
query_guild_not_allow_join_occ(object player, string type, string style,
  string name)
{
    /* This checks to make sure that the new guild is not occupational */
    if (::query_guild_not_allow_join_occ(player, type, style, name))
    {
        return 1;
    }
    return 0;
}

/* Function name: query_guild_level_occ
 * Description:   What is the member's level within the guild?
 * Returns:          int - the level
 */
int
query_guild_level_occ()
{
    return MIN(MAX_GUILD_LEVEL, query_shadow_who()->query_stat(SS_OCCUP) /7);
}

/* Function name: query_def_post
 * Description:   We change the default post office for our members.
 * Returns:          string - the path to the new postoffice
 */
string
query_def_post() 
{
    /* Only bother using the guild's post office if the player is
     * using the guild's start location.
     */
    if (this_player()->query_default_start_location() == GUILD_STARTLOC)
    {
        return GUILD_POST;
    }
    return query_shadow_who()->query_def_post();
}

/* Function name: set_clantitle
 * Description  : Sets the special title of the Neidar member.
 * Arguments    : int num  - title number ( 0 - true title, 1-= warrior,
 *                           2 - battlerager, 3 - ogreslayer, 4 - trollslayer,
 *                           5 - giantslayer, 6 - hero, 7 - warleader
 */
public varargs void
set_clantitle(int num = 0)
{
    if ( num < MIN_CLANTITLE )
    {
        return;
    }

    if ( num > MAX_CLANTITLE )
    {
        return;
    }
    query_shadow_who()->set_skill(SS_CLANTITLE, num);
    
}

/* Function name: query_clantitle
 * Description  : Returns the special title of the Neidar member
 */
public mixed
query_clantitle()
{
    int    TitleValue  = 0;
    string ClanAdj     = "";
    string ClanTitle   = "";
    
    if ( CLANTITLE_NUM < MIN_CLANTITLE )
    {
        return 0;
    }

    if ( CLANTITLE_NUM > MAX_CLANTITLE )
    {
        return 0;
    }

    TitleValue = query_shadow_who()->query_average_stat() +
                 query_shadow_who()->query_stat(SS_DIS) +
                 query_shadow_who()->query_stat(SS_OCCUP);
    TitleValue = MAX(0, (TitleValue / 3));
    
    switch ( TitleValue )
    {
        case 0..100:
            ClanAdj = "Stubborn";
        break;
        case 101..120:
            ClanAdj = "Great";
        break;
        case 121..134:
            ClanAdj = "Fearless";
        break;
        case 135..149:
            ClanAdj = "Mighty";
        break;
        case 150..164:
            ClanAdj = "Glorious";
        break;
        case 165..187:
            ClanAdj = "Legendary";
        break;
        default:
            ClanAdj = "Mythical";
        break;
    }    
 
 /* Clan Warleader do not need adjective - we clear it. 
  */    
    if ( CLANTITLE_NUM == 7 )
    {
        ClanAdj = "";
    }
    else
    {
        ClanAdj += " ";
    }

    if ( query_shadow_who()->query_gender() == G_FEMALE )
    {
        ClanTitle = ClanAdj + fclantitles[CLANTITLE_NUM];
    }
    else
    {
        ClanTitle = ClanAdj + mclantitles[CLANTITLE_NUM];
    }
    
    if ( query_shadow_who()->test_bit("Ansalon",3,4) )
    {
        if( !query_shadow_who()->query_guild_title_lay() )
	{
            ClanTitle = "Dwarven Elder, " + ClanTitle;
	}
        else
	{
            ClanTitle = "Dwarven Elder and " + ClanTitle;
	}
    }
    return ClanTitle; 
}

/*
 * Function name: query_guild_title_occ
 * Description:   Return the member's guild title
 * Returns:       string - the title
 */
string 
query_guild_title_occ()
{
    string ClanTitle;

    if(ADMIN_MANAGER->query_death_mark(query_shadow_who()))
    {
        if(IS_DOOMSEEKER(query_shadow_who()))
            return "Death-Marked Doomseeker of the Neidar Clan, " +
               "Exile of Iron Delving";
        else
            return "Death-Marked Dwarf of the Neidar Clan, " +
               "Exile of Iron Delving";
    }
    
    if(query_shadow_who()->test_bit("Ansalon",3,3) &&
      query_shadow_who()->test_bit("Ansalon",3,4))
    {
        if(IS_DOOMSEEKER(query_shadow_who()))
            return "Disgraced Doomseeker of the Neidar Clan, Exile " +
                "of Iron Delving";
        else
            return "Disgraced Dwarf of the Neidar Clan, Exile " +
                "of Iron Delving";
    }

    if(IS_DOOMSEEKER(query_shadow_who()))
    {
        return doomtitles[MIN(MAX_DOOM_LEVEL, 
            query_shadow_who()->query_stat(SS_OCCUP) / 15)];
    }

    if(query_shadow_who()->test_bit("Ansalon",3,3))
    {
        return "Thane of the Hill Dwarves";
    }

    if ( (CLANTITLE_NUM > MIN_CLANTITLE) && (CLANTITLE_NUM <= MAX_CLANTITLE) )
    {
        ClanTitle = query_clantitle();
        
        if ( stringp(ClanTitle) )
	{
            return ClanTitle;
	}
    }
    
    if (query_shadow_who()->query_gender() == G_FEMALE &&
        query_shadow_who()->test_bit("Ansalon",3,4))
    {
        if (!query_shadow_who()->query_guild_title_lay())
	{
            return "Dwarven Elder, " +ftitles[query_guild_level_occ()];
	}
        else
	{
            return "Dwarven Elder and " +ftitles[query_guild_level_occ()];
	}
    }

    if(query_shadow_who()->query_gender() == G_FEMALE)
    {
        return ftitles[query_guild_level_occ()];
    }

    if(query_shadow_who()->test_bit("Ansalon",3,4))
    {
        if(!query_shadow_who()->query_guild_title_lay())
	{
            return "Dwarven Elder, " +titles[query_guild_level_occ()];
	}
        else
	{
            return "Dwarven Elder and " +titles[query_guild_level_occ()];
	}
    }
    return titles[query_guild_level_occ()];
}

/* 
 * Function name: query_guild_skill_name
 * Description:   Give a names for the guild's special skills
 * Arguments:     type - the number of the skill
 * Returns:          0 if no skill of mine, else the string.
 */
mixed
query_guild_skill_name(int type)
{
    if (type == SS_GUILD_SPECIAL_SKILL)
    {
        return "axe chop";
    }
    if (type == BATTLERAGING_SKILL)
    {
        return "battleraging";
    }

    return 0;
}

/* 
 * Function name: query_guild_leader_occ
 * Description:   Define this function to return true 
 *                if the person is a leader of his/her occupational guild,
 *                in council-membership
 * Returns:          int 1/0 - occupational guild leader or not.
 */

public int
query_guild_leader_occ()
{
    int council_member = 0; // Normal Member, aka not leader.

    if(query_shadow_who()->test_bit("Ansalon",3,3) &&
       query_shadow_who()->test_bit("Ansalon",3,4))
    {
        council_member = 0;  /* Banished member */
    }
    else if(IS_DOOMSEEKER(query_shadow_who()))
    {
        council_member = 0;  /* Self-exiled member */
    }
    else if(query_shadow_who()->test_bit("Ansalon",3,3))
    {
        council_member = 1; /* Thane */
    }
    else if(query_shadow_who()->test_bit("Ansalon",3,4))
    {
        council_member = 1;  /* Elder */
    }
    return council_member;
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
    return ({ GUILD_ROOMS + "train",
              GUILD_ROOMS + "ancestor_tree" });
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

    if (!present(GUILD_EMBLEM_ID, who))
    {   
        guild_emblem = clone_object(GUILD_EMBLEM);
        guild_emblem->move(who, 1);        
    }

    // Add to warfare system if not already a member.
    if(!IS_CLUB_MEMBER(who))
    {
        CLUB_MANAGER->add_member(who);
        CLUB_MANAGER->set_warfare_army(who, "Neidar Clan");
        who->catch_tell("You have been granted a dark steel chit " +
            "as token for supporting the Neidar Clan in " +
            "the War of the Lance!\n");
    }

    // If not listed with a data file, add here
    if(!IS_MEMBER(who))
    {
        ADMIN_MANAGER->add_member(who);
    }

    // Clone the warfare club object
    if (!present("_warfare_club_object_", who))
    {
        clone_object(WAR_OBJ)->move(who, 1);
    }

    /* add the guild's soul to the player */
    if(!IS_DOOMSEEKER(who))
        who->add_cmdsoul(GUILD_SOULS +"cmdsoul");
    else
        who->add_cmdsoul(DOOMSEEKER_SOUL);

    who->update_hooks();

    //Check if the person needs to be demoted
    if (!ADMIN->query_guild_leader(who) && who->test_bit("Ansalon",3,3) &&
        !who->test_bit("Ansalon",3,4))
    {
        who->clear_bit(3,3);
        who->catch_msg("You have been removed as Thane!\n");
    }

    //Check if the person needs the bit
    if (ADMIN->query_guild_leader(who) && !who->test_bit("Ansalon",3,3))
    {
        who->set_bit(3,3);

        //Remove their Elder setting
        if (who->test_bit("Ansalon",3,4))
	{
            who->clear_bit(3,4);
	}
    }

    // Add elders to admin manager data file if not there already
    if(IS_ELDER(who) && !ADMIN_MANAGER->query_is_elder(who))
    {
        ADMIN_MANAGER->add_elder(who);
    }

    // Add Thane to admin manager data file if not there already
    if(IS_THANE(who) && !ADMIN_MANAGER->query_is_thane(who))
    {
        ADMIN_MANAGER->add_thane(who);
    }

    // Add Thane to admin manager data file if not there already
    if(IS_EXILED(who) && !ADMIN_MANAGER->query_is_exile(who))
    {
        ADMIN_MANAGER->add_exile(who);
    }

    if(ADMIN_MANAGER->query_death_mark(who))
    {
        // DEBUG("Council vote open");
        set_alarm(4.0, 0.0, death_mark_initiated);
    }

    /* add the guild subloc */
    who->add_subloc(GUILD_SUBLOC, this_object());

    // Add the special guild objects

    if(!IS_DOOMSEEKER(who))
    {
        object stubborn = clone_object(STUBBORN_OBJ);
        stubborn->move(who, 1);
        stubborn->start();
        object armour_master = clone_object(ARMOUR_MASTER_OBJ);
        armour_master->move(who, 1);
        armour_master->start(); 
        object neidar_block = clone_object(NEIDAR_BLOCK_OBJ);  
        neidar_block->set_effect_caster(who);
        neidar_block->move(who, 1);
        neidar_block->start();
    }
    else
    {
        object doom_regen = clone_object(DOOM_REGEN_OBJ);
        doom_regen->move(who, 1);
        doom_regen->start();

        /* Add no fear properties to the Doomseeker. */
        who->add_prop(NPC_I_NO_FEAR, 1);
        who->add_prop(LIVE_I_NO_DRAGONFEAR, 1);

        // Load the skin object and move it to the player if successful.
        if (query_doomseeker_skin())
            skin_obj->init_doomseeker_skin(shadow_who);
    }
    
    object tireless = clone_object(TIRELESS_OBJ);
    tireless->move(who, 1);
    tireless->start();
    
    query_guild_keep_player(shadow_who);
}

/*
 * Function name: init_occ_shadow()
 * Description:   This function is called from autoload_shadow and may
 *                be used to initialize the shadow when it's loaded.
 * Arguments:     The argument string sent to autoload_shadow.
 */
void init_occ_shadow(string arg)
{
    /* delay for a moment so that the player completes all
     * of login before we continue
     */
    set_alarm(1.0, 0.0, init_guild_member);
}

/* 
 * Function name: add_occ_shadow
 * Description:   Shadow an object with this shadow
 * Arguments:     object who - the object to shadow
 * Returns:       as shadow_me in /std/guild/guild_base.c
 */
int add_occ_shadow(object who)
{
    return shadow_me(who, "occupational", GUILD_STYLE, GUILD_NAME);
}

/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - Our subloc
 *                  me      - I
 *                  for_obj - The looker
 * Returns:          The string the looker shall see
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
        str = "You are ";
    }
    else
    {
        str = capitalize(me->query_pronoun()) + " is ";
    }

    return str + "a member of the Neidar Clan.\n";
}

/*
 * Function name: remove_occ_member
 * Description:   remove this member from the guild
 */
void
remove_occ_member()
{
    setuid();
    seteuid(getuid());
    
    object emblem, who = query_shadow_who();

    /* Remove special skills */ 
    who->remove_skill(SS_GUILD_SPECIAL_SKILL);
    who->remove_skill(BATTLERAGING_SKILL);
    who->remove_skill(WEAPON_SPEC_SKILL);
    who->remove_skill(SS_CLANTITLE);
    
    /* Clear the player's guild stat */
    who->clear_guild_stat(SS_OCCUP);

    /* Penalty for leaving: loose 1/4 of total combat exp */
    who->add_exp(-(who->query_exp_combat()) / 4, 1);

    /* Remove any instances of the guild emblem on the player */
    while (emblem = present(GUILD_EMBLEM_ID, who))
    {
        emblem->remove_object();
    }

    if (objectp(skin_obj))
    {
        skin_obj->remove_object();
    }

    /* If the player is using our start location, remove it */
    if (who->query_default_start_location() == GUILD_STARTLOC)
    {
        who->set_default_start_location(who->query_def_start());
    }

    /* Remove the guild soul */
    if(!IS_DOOMSEEKER(who))
        who->remove_cmdsoul(GUILD_SOULS+"cmdsoul");
    else
        who->remove_cmdsoul(DOOMSEEKER_SOUL);

    who->update_hooks();

    if (!who->query_wiz_level())
    {
        log_file(ELDER_LIST, extract(ctime(time()), 4, 15)+ " "+
          capitalize(who->query_real_name())+ " left the clan.\n", -1);

        write_file(MEMBERS, who->query_name() + " left " + 
          extract(ctime(time()), 4, 15)+", StatAvg: "+who->query_average_stat()+
          ", Race: "+who->query_race()+", Align: "+who->query_alignment()+"\n");
    }

    // If listed with a data file, remove here
    if(IS_MEMBER(who))
    {
        ADMIN_MANAGER->remove_exile(who);
        ADMIN_MANAGER->remove_death_mark(who);
        ADMIN_MANAGER->remove_elder(who);
        ADMIN_MANAGER->remove_thane(who);
        ADMIN_MANAGER->remove_doomseeker(who);
        ADMIN_MANAGER->remove_member(who);
    }

    who->remove_prop(NPC_I_NO_FEAR);
    who->remove_prop(LIVE_I_NO_DRAGONFEAR);
    
    /* Remove the guild shadow.  This also resets tax to 0. */
    remove_guild_occ();
}

public void
remove_neidar_objs()
{
    object * objs;
    
    objs = filter(all_inventory(shadow_who), &->is_neidar_armour_master_object());
    objs->remove_object();
    objs = filter(all_inventory(shadow_who), &->is_neidar_stubborn_object());
    objs->remove_object();
    objs = filter(all_inventory(shadow_who), &->is_neidar_tireless_object());
    objs->remove_object();
    objs = filter(all_inventory(shadow_who), &->is_neidar_block_evade());
    objs->remove_object();
    objs = filter(all_inventory(shadow_who), &->is_neidar_regeneration_object());
    objs->remove_object();
}

public void
remove_shadow()
{
    remove_neidar_objs();    
    destruct();
}

void
kick_renegade_from_guild()
{
    remove_occ_member();
}

public void
do_die(object killer)
{
    object ob;  
    int time2;
    time2 = time();

    seteuid(getuid());

    if (query_shadow_who()->query_hp() > 0)
        return query_shadow_who()->do_die(killer);

    if(IS_DOOMSEEKER(query_shadow_who()))
    {
        mapping list = ADMIN_MANAGER->query_doomseeker_tree();
        string name = query_shadow_who()->query_real_name();
        mixed * carving_details = list[name];
        int time = carving_details[0];
        string death_details = carving_details[1];
        string killer_string;

        if(killer->query_npc())
            killer_string = LANG_ASHORT(killer);
        else if(!killer)
            killer_string = "an unknown foe";
        else     
            killer_string = killer->short();

        if(!strlen(death_details))
        {
            death_details = capitalize(HE(query_shadow_who()))+ 
                " took a death-oath on " +
                TIME2FORMAT(time, "d mmm yyyy")+
                ", which was fulfilled on " + 
                TIME2FORMAT(time2, "d mmm yyyy")+ " in battle " +
                "against " +killer_string+ ". ";
        }
        else
        {
            death_details += capitalize(HE(query_shadow_who()))+ 
                " again took a death-oath on " +
                TIME2FORMAT(time, "d mmm yyyy")+
                ", which was fulfilled on " + 
                TIME2FORMAT(time2, "d mmm yyyy")+ " in battle " +
                "against " +killer_string+ ". ";        
        }

        tell_object(query_shadow_who(), "With your death, " +
            "you have redeemed your honour and fulfilled " +
            "your death-oath.\nYou are no longer a Doomseeker!\n");

        mapping doom_list = ADMIN_MANAGER->query_neidar_doomseeker_list();
        int old_stat = doom_list[name];

        /* reset guild stat back to what it previously was */
        query_shadow_who()->set_guild_stat(SS_OCCUP, F_STAT_TO_EXP(old_stat));

        ADMIN_MANAGER->remove_doomseeker(query_shadow_who());
        ADMIN_MANAGER->remove_doomseeker_tree(name);
        ADMIN_MANAGER->add_doomseeker_tree(name, time, death_details);
    }
    
    if(ADMIN_MANAGER->query_death_mark(query_shadow_who()))
    {
      tell_object(query_shadow_who(), "With your death, " +
         "you are expelled from the Neidar Clan.\n");
      set_alarm(2.0, 0.0, kick_renegade_from_guild);
    }

    return query_shadow_who()->do_die(killer);
} 

public void
notify_you_killed_me(object victim)
{

    int stat_av = victim->query_average_stat();
    string vic_short;

    if(victim->query_npc())
        vic_short = victim->short();
    else
        vic_short = capitalize(victim->query_real_name());

    if(IS_DOOMSEEKER(shadow_who))
    {

    // Add to total kills and stat average to the slayer tally
        ADMIN_MANAGER->increase_doomseeker_kills(shadow_who);
        ADMIN_MANAGER->increase_doomseeker_average(shadow_who, stat_av);

    // Add health status for average health ratio checks
        int ratio = ftoi((itof(shadow_who->query_hp()) / 
            itof(shadow_who->query_max_hp())) * 100.0);
        ADMIN_MANAGER->increase_doomseeker_health(shadow_who, ratio);

    // Check if kill is their biggest yet
        mapping list = ADMIN_MANAGER->query_greatest_kill();
        string name = shadow_who->query_real_name();

        if(!m_sizeof(list))
        {
            ADMIN_MANAGER->add_greatest_kill(name, stat_av, vic_short);
        }
        else if(!IN_ARRAY(name, m_indexes(list)))
        {
            ADMIN_MANAGER->add_greatest_kill(name, stat_av, vic_short);
        }
        else
        {
            mixed * kill_details = list[name];
            int stat = kill_details[0];

            if(stat < stat_av)
            {
                ADMIN_MANAGER->add_greatest_kill(name, stat_av, vic_short);
            }
        }
    }

    shadow_who->notify_you_killed_me(victim);
}

public mixed
wear_arm(object armour)
{
    int result = shadow_who->wear_arm(armour); 
    
    if (query_doomseeker_skin())
        skin_obj->update_doomseeker_skin();
    
    return result;
}
public mixed
remove_arm(object armour)
{
    int result = shadow_who->remove_arm(armour);
    
    if (query_doomseeker_skin())
        skin_obj->update_doomseeker_skin();
    
    return result;
}