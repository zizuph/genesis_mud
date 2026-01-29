#pragma strict_types

inherit "/std/guild/guild_occ_sh";

#include "guild.h"

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "special_attacks.c"

//#include "slam_special.c"   
/* 18.08.2003 , Blizzard*/

#include "stand_special.h"

#define SHADOW_CONVERTER    "/d/Ansalon/guild/neidar/lib/shadow_converter"
#define DO_NEIDAR_SHADOW_CONVERSION     1

#define GUILD_SUBLOC  GUILD_NAME + " subloc"
#define MAX_GUILD_LEVEL 24
#define PUNISH_FILE     "/d/Ansalon/guild/dwarf/log/punish"
#define RETIRED_FILE    "/d/Ansalon/guild/dwarf/log/elder_retired"

#define ARMYMASTER      "/d/Krynn/common/warfare/armymaster"

#define CLANTITLE_NUM   query_shadow_who()->query_skill(SS_CLANTITLE)
#define MIN_CLANTITLE   0
#define MAX_CLANTITLE   8

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
                                
string *punishlist = ({ });
string *retiredlist = ({ });


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
 /*   Removed, 12.02.2004, Blizzard
    int tax = GUILD_TAX;
    string *areas = ARMYMASTER->query_areas_of_army("Free People");
    if (member_array("Estwilde Plains", areas) < 0)
	tax += 2;
 */
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
    /* throw out non-dwarves */
    if((who->query_race() != "dwarf") && (who->query_race() != "ghost"))
    {
	return "Only dwarves can be a member of this clan!\n";
    }

    if((who->query_region_title() == "kayolin mountain dwarf") ||
      (who->query_region_title() == "thorbardin mountain dwarf") ||
      (who->query_region_title() == "zhakar mountain dwarf"))
    {
	return "Only hill dwarves may be a member of the clan! Not " +
	"Mountain dwarves!\n";
    }

    if(who->query_race_name() == "gully dwarf")
    {
	return "Gully dwarves may not be clan members!!!\n";
    }

    if(who->query_guild_member("Angmar Army"))
    {
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
	return;
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
	return;
    query_shadow_who()->clear_bit(3,4);
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
    string str = query_shadow_who()->query_real_name();


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


    if(member_array(str, punishlist) >= 0)
    {
	set_alarm(2.0, 0.0, banish_member);
    }
    if(member_array(str, retiredlist) >= 0)
    {
	set_alarm(3.0,0.0, retire_elder);
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
    /* This checks to make sure that the new guild is not occupational */
    if (::query_guild_not_allow_join_occ(player, type, style, name))
	return 1;

    /* We don't want our members joining magic guilds */
    if (style == "magic")
    {
	player->catch_msg("No respectable dwarf can cast spells!\n");
	return 1;
    }


    return 0;
}

/* Function name: query_guild_level_occ
 * Description:   What is the member's level within the guild?
 * Returns:	  int - the level
 */
int
query_guild_level_occ()
{
    return MIN(MAX_GUILD_LEVEL, query_shadow_who()->query_stat(SS_OCCUP) /7);
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
        return;
    
    if ( num > MAX_CLANTITLE )
        return;

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
        return 0;
    
    if ( CLANTITLE_NUM > MAX_CLANTITLE )
        return 0;

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
        ClanAdj = "";
    else
        ClanAdj += " ";

    if ( query_shadow_who()->query_gender() == G_FEMALE )
        ClanTitle = ClanAdj + fclantitles[CLANTITLE_NUM];
    else
        ClanTitle = ClanAdj + mclantitles[CLANTITLE_NUM];
    
    if ( query_shadow_who()->test_bit("Ansalon",3,4) )
    {
	if( !query_shadow_who()->query_guild_title_lay() )
	    ClanTitle = "Dwarven Elder, " + ClanTitle;
	else
	    ClanTitle = "Dwarven Elder and " + ClanTitle;
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
    
    if(query_shadow_who()->test_bit("Ansalon",3,3) &&
      query_shadow_who()->test_bit("Ansalon",3,4))
	return "Disgraced Dwarf of the Neidar Clan, Exile " +
	"of Iron Delving";

    if(query_shadow_who()->test_bit("Ansalon",3,3))
	return "Thane of the Hill Dwarves";

    if ( (CLANTITLE_NUM > MIN_CLANTITLE) && (CLANTITLE_NUM <= MAX_CLANTITLE) )
    {
        ClanTitle = query_clantitle();
        
        if ( stringp(ClanTitle) )
            return ClanTitle;
    }
    
    if(query_shadow_who()->query_gender() == G_FEMALE &&
      query_shadow_who()->test_bit("Ansalon",3,4))
	if(!query_shadow_who()->query_guild_title_lay())
	    return "Dwarven Elder, " +ftitles[query_guild_level_occ()];
	else
	    return "Dwarven Elder and " +ftitles[query_guild_level_occ()];

    if(query_shadow_who()->query_gender() == G_FEMALE)
	return ftitles[query_guild_level_occ()];

    if(query_shadow_who()->test_bit("Ansalon",3,4))
	if(!query_shadow_who()->query_guild_title_lay())
	    return "Dwarven Elder, " +titles[query_guild_level_occ()];
	else
	    return "Dwarven Elder and " +titles[query_guild_level_occ()];

    return titles[query_guild_level_occ()];
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
    if (type == SS_GUILD_SPECIAL_SKILL)
    {
	return "axe chop";
    }
    if (type == SLAM_SPECIAL_SKILL)
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
 * Returns:	  int 1/0 - occupational guild leader or not.
 */

public int
query_guild_leader_occ()
{
    if(query_shadow_who()->test_bit("Ansalon",3,3) &&
      query_shadow_who()->test_bit("Ansalon",3,4))
      return 0;  /* Banished member */
    else if(query_shadow_who()->test_bit("Ansalon",3,3))
      return 1;  /* Thane */
    else if(query_shadow_who()->test_bit("Ansalon",3,4))
      return 1;  /* Elder */
    else
      return 0;  /* Normal member */
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
    return ({ GUILD_DIR + "train" });
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

    if (guild_emblem = clone_object(GUILD_EMBLEM))
    {    
	guild_emblem->move(who, 1);
    }

    /* add the guild's soul to the player */
    who->add_cmdsoul(GUILD_CMDSOUL);
    who->update_hooks();

    //Check if the person needs to be demoted
    if (!ADMIN->query_guild_leader(who) && who->test_bit("Ansalon",3,3)
        && !who->test_bit("Ansalon",3,4))
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
            who->clear_bit(3,4);
    }

    /* add the guild subloc */
    who->add_subloc(GUILD_SUBLOC, this_object());

}

void
convert_to_new_neidar_shadow(object player)
{
    setuid();
    seteuid(getuid());     

    SHADOW_CONVERTER->convert_neidar_shadow(player);
}

/*
 * Function name: init_occ_shadow()
 * Description:   This function is called from autoload_shadow and may
 *                be used to initialize the shadow when it's loaded.
 * Arguments:     The argument string sent to autoload_shadow.
 */
void init_occ_shadow(string arg)
{
    ::init_occ_shadow(arg); 

    if (DO_NEIDAR_SHADOW_CONVERSION)
    {
        // This code now just calls and converts to the new shadow stuff.
        set_alarm(1.0, 0.0, &convert_to_new_neidar_shadow(shadow_who));
        return;
    }
    
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
    object emblem, who = query_shadow_who();

    /* Remove special skills */ 
    who->remove_skill(SS_GUILD_SPECIAL_SKILL);
    who->remove_skill(SLAM_SPECIAL_SKILL);
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

    /* If the player is using our start location, remove it */
    if (who->query_default_start_location() == GUILD_STARTLOC)
    {
	who->set_default_start_location(who->query_def_start());
    }

    /* Remove the guild soul */
    who->remove_cmdsoul(GUILD_CMDSOUL);
    who->update_hooks();


    log_file(ELDER_LIST, extract(ctime(time()), 4, 15)+ " "+
      C(who->query_real_name())+ " left the clan.\n", -1);
    /* Remove the guild shadow.  This also resets tax to 0. */
    remove_guild_occ();
}
