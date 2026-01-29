/*
 *	/d/Gondor/guilds/bnumen/bnumen_sh.c
 *
 *	Copyright (c) 1994, 1997 by Christian Markus
 *
 *	The guild shadow for the Black Numenoreans of Gondor
 *
 *	Created: Olorin, 04-nov-1994
 *          using /d/Gondor/common/guild2/morgul_shadow.c by Olorin
 *
 *  Snarfed from Olorin's stuff.
 *  Palmer Aug 2006 
 *
 *  Cleaned up the file and removed old stuff and updated objects
 *  that made these old calls. Toby, 2006-10-26
 */
#pragma no_inherit
#pragma save_binary
#pragma strict_types

inherit "/std/guild/guild_race_sh.c";

#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/bnumen/lib/bnumen_defs.h"

/*
 * Guild tax calculation:
 * Shop in bnumen guild:				1.00%
 * Skills:	trading:	50 levels, 20 tax:	0.33%
 *		axe:		50 levels, 20 tax:	0.50%
 *		herbalism:	50 levels, 30 tax:	0.50%
 *		spellcraft:	50 levels, 30 tax:	0.50%
 * General skill levels lowered:
 *              awareness       50 levels, 20 tax:      0.33%
 *              language        50 levels, 20 tax:      0.33%
 *              climb           50 levels, 20 tax:      0.33%
 * Sum:							3.82%
 * Actual tax:						4.00%
 */
#define GUILD_TAX              4
#define TRAINER		(GUILD_DIR + "rooms/train_hall")
#undef DEBUG
#ifdef DEBUG
#define DEBUG_MSG(x) shadow_who->catch_msg(file_name(TO)+": "+x+"\n");
#else
#define DEBUG_MSG(x)
#endif

/*
 *	Prototypes:
 */
public    nomask int   query_bnumen_level();
public    nomask int   update_bnumen_level(int val);
private        void    remove_bnumen(object pl, string house, string reason);
private        void    remove_bnumen_from_house(object pl, string house, string reason);

/*
 * Global variables
 */
static  string  Black_Numenoreans_House;
static  int     Subloc_Lev;

/*
 * Function name: query_guild_tax_race
 * Description:   What's the tax to pay at this guild?
 * Returns:       the tax this guild wants
 */
public nomask int
query_guild_tax_race()
{
    return GUILD_TAX;
}

/*
 * Function name: query_guild_trainer_race
 * Description:   Return one or more references to the object that defines
 *                sk_train_max for the player. The returned refernce can
 *                be a string reference, an object pointer or an array of
 *                those.
 * Returns:       See description.
 */
public nomask mixed
query_guild_trainer_race()
{
    return TRAINER;
}

/*
 * Function name: query_guild_style_race
 * Description:   What style is this guild?
 * Returns:       "race"
 */
public nomask string
query_guild_style_race()
{
    return GUILD_STYLE;
}

/*
 * Function name: query_guild_name_race
 * Description:   Returns the name of the guild this shadow represents
 * Returns:       The name of the guild
 */
public nomask string
query_guild_name_race()
{
    return GUILD_NAME;
}

/*
 * Function name: query_guild_not_allow_join_race
 * Description:   Test if this guild allows a player to join another
 * Arguments:     type  - the type of guild to join
 *                style - the style of the guild
 *                name  - the name of the guild to join
 * Returns:       1 - this guild does not allow member 
 *                    to join the other guild
 */
public nomask int
query_guild_not_allow_join_race(object player, string type, 
                                   string style, string name)
{
    /*
     * We do not restrict guild membership of the bnumen.
     * But we have to prevent the player from joining another
     * race guild as long as he or she is still a member of
     * this guild:
     */
    if (::query_guild_not_allow_join_race(player, type, style, name))
        return 1;

    return 0;
}

/*
 * Function name: query_guild_keep_player
 * Description:   called by autoload_shadow in the guild shadow
 *                which is called when the player logs in,
 *                check if we want to keep the player in this guild
 * Arguments:     player - the player object
 * Returns:       1 - keep player, 0 - kick him out.
 */
private int
query_guild_keep_player(object ob)
{
    string  race = ob->query_race();

    if ((race != BNUMEN_RACE) && (race != "ghost"))
    {
    	write("Only humans can belong to the Houses of the Black Numenoreans!\n");
        /*
         * We use our own function to remove the player.
         * Therefore, we return always 1.
         */
        set_alarm(1.0, 0.0, &remove_bnumen(ob, ob->query_bnumen_house(),
            "was removed (race = "+race+") from"));
    }

    return 1;
}

/*
 * Function name: set_bnumen_house
 * Description:	  set the House the member belongs to
 * Arguments:     the name of the House
 * Returns:       1 - success, 0 - the House does not exist.
 */
public nomask int
set_bnumen_house(string str)
{
    str = CAP(LOW(str));

    if (member_array(str, BNUMEN_HOUSES) < 0)
    {
	// To permit joining without a House:
	if (LOW(str) != BNUMEN_NO_HOUSE)
	    return 0;
	else
	    Black_Numenoreans_House = "";
    }
    else
    {
	    Black_Numenoreans_House = str;
    }
    return 1;
}

/*
 * Function name: query_bnumen_house
 * Description:   returns the House the bnumen belongs to
 * Returns:       the name of the House
 */
public nomask string
query_bnumen_house()
{
    if (!strlen(Black_Numenoreans_House))
        return "";
    return Black_Numenoreans_House;
}

/*
 * Function name: query_guild_title_race
 * Description  : This function should return the race title of the player.
 *                This function is called only for mortals.
 * Returns      : string - the title for the player.
 *                The title will be incorporated in the format
 *                "the <race title>, <occ title> and <lay title>"
 *                if the player is a member of all major guild types.
 */
public nomask string
query_guild_title_race()
{
    return "Black Numenorean";
    /*
    Make a check if player want to display house instead? (Toby)
    Remember if so to make the same check in query_guild_family_name
    and set it to 1 if so..
    if (bnumen.0 something check display)
        return "of family "+Black_Numenoreans_House;
    */
} 

/*
 * Function name: query_guild_family_name
 * Description  : if the race guild consists of families that give their
 *                members a family name instead of a title, this
 *                function should return true. It moves the article
 *                'the' to the occupational title of the member giving:
 *                "<race title>, the <occ title> and <lay title>"
 *                if the player is a member of all major guild types.
 * Returns      : int - true if the function query_guild_title_race()
 *                returns the family name and not a normal guild title.
 */
public nomask int
query_guild_family_name()
{
    return 0;
}

/*
 *	Function name:	query_def_post
 *	Description:	return the subrace specific post office
 *					this should be set only by the race guild!
 *	Returns:		the path name to the post office
 */
public nomask string
query_def_post() { return BNUMEN_POST; }


/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - our subloc id
 *                me      - my player object
 *                for_obj - the player object of the onlooker
 * Returns:       the string the onlooker shall see
 */
string
show_subloc(string subloc, object me, object for_obj)
{
    int    hs,
           hl,
           mmp;
    string str,
	       house;

    if (subloc != BNUMEN_S_SUBLOC)
        return shadow_who->show_subloc(subloc, me, for_obj);

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (for_obj == me)
    {
        str = "You have ";
    }
    else
    {
        str = CAP(me->query_pronoun()) + " has ";
    }

    return (str + "the regal bearing of a black numenorean.\n");
}


/*
 * Function name: set_bnumen_lord_level
 * Description:   set the rank of the bnumen to Lord
 * Returns:       1/0 - success/failure
 */
public nomask int
set_bnumen_lord_level()
{
    // Only the master object may set this variable!
    if (MASTER_OB(previous_object()) != BNUMEN_MASTER)
        return 0;
    if (query_bnumen_level() < DL_SUB_LORD)
        return 0;
    shadow_who->set_skill(SS_BNUMEN_LEVEL, DL_LORD);
    return 1;
}


/*
 * Function name: second_life
 * Description:   Handles all that should happen to a dying player.
 * Argument:      Object that caused the kill.
 * Returns:       True if the living object should get a second life
 */
public int
second_life(object killer)
{
    if ((shadow_who->query_hp() <= 0) && (query_bnumen_level() >= DL_LORD))
    {
	/*
	 * A Lord or a Lady of the Black Numenoreans loses his or her rank in death:
	 */
        seteuid(getuid());
        BNUMEN_MASTER->remove_lord_through_death(shadow_who->query_name());
    }

    return shadow_who->second_life(killer);
}

/*
 * Function name: remove_bnumen_from_house
 * Description:   remove a player from a House
 *                This function is used to allow a player to join
 *                another house of the bnumen after being released
 *                by the Lord or Lady of his old house.
 * Arguments:     pl     - object pointer to the member
 *                house  - the name of the House
 *                reason - why do we remove the player?
 * Returns:       1/0 - success/failure
 */
public nomask int
remove_bnumen_from_house(object pl, string house, string reason)
{
    if (!objectp(pl) || (pl != shadow_who))
        return 0;

    pl->catch_msg("You are removed from the House of "+house+"!\n");
    seteuid(getuid());
    return BNUMEN_MASTER->remove_bnumen_from_house(pl, house, reason);
}

/*
 * Function name: remove_bnumen
 * Description:   remove a player from the guild
 *                (Should only happen if the player joins another guild
 *                At present, this is only called if the player
 *                has changed race and is not a human anymore.)
 * Arguments:     pl     - object pointer to the member
 *                house  - the name of the House
 *                reason - why do we remove the player?
 * Returns:       1/0 - success/failure
 */
private int
remove_bnumen(object pl, string house, string reason)
{
    if (!objectp(pl) || (pl != shadow_who))
	return 0;

    pl->catch_msg("You are removed from the Houses of the Black Numenoreans!\n");
    seteuid(getuid());
    return BNUMEN_MASTER->remove_bnumen(pl, house, reason);
}

/*
 * Function name: add_bnumen_soul
 * Description:   add the bnumen soul
 */
public nomask void
add_bnumen_soul()
{
    if (!objectp(shadow_who))
        return;

    shadow_who->add_cmdsoul(BNUMEN_SOUL);
    shadow_who->update_hooks();
}

/*
 * Function name: init_race_shadow
 * Description:   This function is called from autoload_shadow and may
 *                be used to initialize the shadow when it is loaded.
 * Arguments:     The argument string sent to autoload_shadow.
 */
public nomask void
init_race_shadow(mixed arg)
{
    string  nh,
            name,
            lname;

    FIX_EUID;

    shadow_who->add_subloc(BNUMEN_S_SUBLOC, TO);

    if (!BNUMEN_MASTER->keep_player(shadow_who))
    {
        set_alarm(0.0, 0.0, &remove_bnumen(shadow_who, 0,
            "was removed (shadow) from"));
        return;
    }
    DEBUG_MSG("checked keep_player in BNUMEN_MASTER");

    nh = BNUMEN_MASTER->query_bnumen_house(name = shadow_who->query_name());

    // if (!strlen(nh) && interactive(shadow_who))
 
    if (!strlen(nh) && interactive(shadow_who) && !shadow_who->query_wiz_level())
    {
	write_file(BNUMEN_LOG, name + 
		   " is not logged as member of the Black Numenoreans! " +
		   ctime(time()) + ".\n");
    }

    if (nh != BNUMEN_NO_HOUSE)
	   set_bnumen_house(nh);

    if (query_bnumen_level() == DL_LORD)
    {
        if ((lname = BNUMEN_MASTER->query_house_lord(nh))
            != shadow_who->query_name())
        {
            update_bnumen_level(DL_SUB_LORD);
            if (strlen(lname))
                shadow_who->catch_msg("You have been replaced as head of the House of "
                  + nh + " by " + lname + ".\n");
            else
                shadow_who->catch_msg("You are no longer head of the House of "
				      + nh + ".\n");
        }
        else if (shadow_who->query_wiz_level())
        {
            shadow_who->catch_msg("As wizard, you cannot remain head of the "
				  + "House of " + nh + "!\n");
            shadow_who->set_bnumen_level(DL_SUB_LORD);
            BNUMEN_MASTER->remove_lord_from_tree(shadow_who->query_name(), nh);
        }
    }

    // If the soul is not added from an alarm, there is a problem with ghosts
    set_alarm(0.0, 0.0, add_bnumen_soul);
}

public int
query_guild_leader_race()
{
    return (shadow_who->query_skill(SS_BNUMEN_LEVEL) == DL_LORD);
}

/************************************************************************* 
 *                                                                       *
 * All functions regarding the internal skill. This skill is involved in *
 * the rank of the members.                                              *
 *                                                                       *
 *************************************************************************/

/*
 * Function name: query_bnumen_level
 * Description:   return the level of the bnumen within the guild,
 *                the level is stored as a skill number
 *                (SS_BNUMEN_LEVEL)
 * Returns:       the level
 */
public nomask int
query_bnumen_level()
{
    setuid();
    seteuid( getuid() );

   /* if (strlen(Black_Numenoreans_House))
	   return shadow_who->query_skill(SS_BNUMEN_LEVEL);
    return 0;
    */
    return shadow_who->query_skill(SS_BNUMEN_LEVEL);
}

/*
 * Function name: update_bnumen_level
 * Description:   updates the level of the bnumen skill
 * Argument:      val - the new level
 * Returns:       1/0 - success/failure
 */
public nomask int
update_bnumen_level(int val)
{
    int new_level;

     /*  if ((val < 0) || (val > DL_SUB_LORD))
            return 0;

       if (!strlen(Black_Numenoreans_House))
          return 0;
      */

    new_level = query_bnumen_level() + val;

    shadow_who->set_skill(SS_BNUMEN_LEVEL, new_level);

    if(new_level < 2)
       shadow_who->set_skill(SS_BNUMEN_LEVEL, 1);

    if(new_level > 100000)
       shadow_who->set_skill(SS_BNUMEN_LEVEL, 100000);

    return 1;
}


/*
 * Function name: set_skill
 * Description:   internal checks if the skill to be set is SS_BNUMEN_LEVEL
 * Arguments:     skill - the skill number
 *                val   - the new value
 * Returns:       1/0   - success/failure
 *
 * Remove this later? (Toby)
 */
public int
set_skill(int skill, int val)
{
    if (skill != SS_BNUMEN_LEVEL)
      return shadow_who->set_skill(skill, val);

 //  ??    ::set_skill(int skill, int val);

    return update_bnumen_level(val);
}


/*
 * Function name: query_guild_skill_name
 * Description:   When a players uses the skills command he should get the
 *                the skill names, not the 'special' string.
 * Arguments:     type - the number of the skill
 * Returns:       0 if no skill of mine, else the string.
 */
public mixed
query_guild_skill_name(int type)
{
    if (type == SS_BNUMEN_LEVEL)
    {
        if (objectp( this_player() ) && this_player()->query_wiz_level())
        {
            return "BNumen Level";
        }
        else
        {
            return "";
        }
    }
    return 0;
}

