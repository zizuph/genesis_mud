/*
 * Wizards of High Sorcery
 * The shadow object for the players.
 *
 * by Rastlin 950522
 */

/*
 * TODO:
 *   alignment check
 *   Better show_subloc
 *   Have a look on the level functions, merge?
 */

/*
 * MODIFICATIONS:
 * Changed the level functions to be based purely on the
 * level modifier (promotions/demotions) for apprentices.
 * Needs to have the modifier reset for apprentices who
 * graduate (take the Test apparantly)
 * Karath March 15th 1997
 */
#pragma strict_types
#pragma no_inherit

#include "../../local.h"
#include "../local.h"
#include <ss_types.h>
#include <const.h>
#include <macros.h>
#include <wa_types.h>

inherit "/std/guild/guild_occ_sh";

static int gHood;

/* Prototypes */
public string query_wohs_title();



/****************************************************
 * Misc internal functions
 ****************************************************/
/*
 * Function:	s_alignment_check
 * Description:	Check if the player holds the right alignment
 *		versus the robe color, otherwise change it.
 * Arguments:	player - The player to check
 */
static void
s_alignment_check(object player)
{
    /* Don't check any alignment yet */
}

/*
 * Function:	s_allow_other_guilds
 * Description:	Check if the player is allowed to have joined
 *		other guilds.
 * Arguments:	player - The player to check
 * Returns:	1 -- Ok, 0 -- Not ok.
 */
static int
s_allow_other_guilds(object player)
{
    if (player->query_guild_name_lay())
        return 0;

    return 1;
}

/*
 * Function name: s_run_check
 * Description:   Check and see if we need to restore anything to
 *                the player.
 * Arguments:     player - The player to check
 */
static void
s_run_check(object player)
{

    int i;

	setuid();
	seteuid( getuid( this_object() ) );

    i = ADMIN->restore_player(player);

    if (i == 1)
        return;

    player->catch_msg("Arrghh!! It seems that you have been hit by a " +
      "bug. The Tower of Wayreth tried to make a " +
      "restoration but failed. Try to rejoin at the " +
      "Tower, if that doesn't work. You better talk " +
      "to a Krynn-wizard or someone from the " +
      "'playerarch' team.\n");

    if (i)
        player->catch_msg("Reason for failing: It was not possible to " +
          "shadow player, other shadows are blocking.\n");
    else
        player->catch_msg("Reason for failing: Player has the shadow " +
          "without being a member.\n");
}

/****************************************************
 * Redefined functions from the shadow
 ****************************************************/
/*
 * Function name: query_guild_style_occ
 * Description:	  Return the style of the guild
 */
public string
query_guild_style_occ()
{
    return GUILD_TYPE;
}

/*
 * Function name: query_guild_name_occ
 * Description:	  Return the name of the guild
 */
public string
query_guild_name_occ()
{
    return GUILD_NAME;
}

/*
 * Function name: query_guild_tax
 * Description:   Set the initial tax
 */
public int
query_guild_tax_occ()
{
	setuid();
	seteuid( getuid( this_object() ) );

    if(ADMIN->query_member_type(shadow_who) == TYPE_APPRENTICE)
  		return 20; // apprentices pay 20% tax
    return 35;
}

/*
 * Function name: query_def_post
 * Description:   We change the default post office for our members.
 * Returns:       The new postoffice
 */
public string
query_def_post()
{
    return WTOWER + "post";
}

/*
 * Function name: query_guild_keep_player
 * Description:	  Called from the autoload function to determin
 *		  if we should keep the player or not.
 * Arguments:	  ob - The player object
 * Returns:	  1 -- Keep the player, 0 -- Dont keep the player
 */
public int
query_guild_keep_player(object player)
{
    if (!s_allow_other_guilds(player))
        return 0;

    if (!player->query_wiz_level())
    player->add_subloc(WOHS_SUB, TO);

    set_alarm(180.0, 0.0, &s_alignment_check(player));

    /* Check so that everything is correct */
    set_alarm(2.0, 0.0, &s_run_check(player));

    return 1;
}

/*
 * Function name: query_guild_not_allow_join_occ
 * Description:   Check if we allow that the player joins another guild
 * Arguments:	  player - The player
 *		  type, style, name - The type, style and name of the
 *		  intended guild
 * Returns:	  1 if we do not allow, else 0
 */
public int
query_guild_not_allow_join_occ(object player, string type, string style,
  string name)
{
    if (::query_guild_not_allow_join_occ(player, type, style, name))
        return 1;

    NF("Magic-users devotes their lives to magic and magic only.\n");
    if (type == "layman")
        return 1;

    return 0;
}

/*
 * Function name: query_guild_title_occ
 * Description:	  Find the occupational title of the magic-user.
 * Returns:	  The occupational magic-user title.
 */
public string
query_guild_title_occ()
{
    return query_wohs_title();
}

/*
 * Function name: query_guild_skill_name
 * Description:   Hide the name for the player, but show the skill-
 *                description to the wizards.
 * Arguments:     skill - The skill number.
 * Returns:       The skill description or false.
 */
public mixed
query_guild_skill_name(int skill)
{
    if (skill == SS_WOHS_LEVEL_MOD)
    {
        if (objectp(TP) && TP->query_wiz_level())
            return "(WoHS Level modifier)";
        else
            return "";
    }

    return 0;
}

/*
 * Function:     query_guild_leader_occ
 * Description:  This function is called to test if a member is a
 *               guild leader, if so, give them 75 max mail limit.
 * Returns:      1 if the person is a leader, 0 if not.
 */

public int
query_guild_leader_occ()
{
    return (IS_CONCLAVE(RNAME(shadow_who)));
}

/***********************************/

/*
 * Function:	show_subloc
 * Description:	This function is called each time someone looks at us
 * Arguments:	subloc  - Our subloc
 *		me      - I
 *		for_obj - The looker
 * Returns:	The string the looker shall see
 */
public string
show_subloc(string subloc, object me, object for_obj)
{
    string str, conclave = "";
    object ob;

    if (subloc != WOHS_SUB)
        return shadow_who->show_subloc(subloc, me, for_obj);

    if (!(ob = P(GUILD_OBJECT, me)))
        return "";

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "You are a member of the Wizards of High Sorcery.\n";

    if (for_obj == me)
        str = "You are";
    else
        str = C(PRONOUN(me)) + " is";

    //if (IS_CONCLAVE(RNAME(me)))
    //    conclave = " and " + L(str) + " the " + query_wohs_title();

    str = str + " a member of the Wizards of High Sorcery" + conclave + ".\n";

    return str;
}

public mixed
query_guild_trainer_occ()
{
    return ({ NORMAL_SKILLS, MAGE_SKILLS });
}

/****************************************************
 * New functions that might be handy
 ****************************************************/
public void
set_wohs_hooded(int i) { gHood = i; }

public int
query_wohs_hooded() { return gHood; }

public int
query_is_wohs()
{
    return 1;
}

/****************************************************
 * Level and title handling
 ****************************************************/
/*
 * Function name: query_wohs_base_level
 * Description:   The base level of the wizard
 * Returns:       The base level
 */
public int
query_wohs_base_level()
{
    int stat, nlevels;

    setuid();
    seteuid( getuid( this_object() ) );

    stat = shadow_who->query_stat(SS_OCCUP),
    nlevels = ADMIN->query_number_levels();

    if (stat > 160)
        stat = 160;

    return ((nlevels - 1) * stat) / 160;
}

/*
 * Function name: query_wohs_order_level
 * Description:   The level without fixed levels for conclave
 * Returns:       The level
 */
public int
query_wohs_order_level()
{
    int asize, level, nlevels;

    setuid();
    seteuid( getuid( this_object() ) );

    nlevels = ADMIN->query_number_levels();

    /* Half of the levels, without reward */
    if(ADMIN->query_member_type(shadow_who) == TYPE_APPRENTICE)
      {
	level = 0;
      } else { level = query_wohs_base_level() / 2; }

    level += shadow_who->query_skill(SS_WOHS_LEVEL_MOD);

    if (ADMIN->query_member_type(shadow_who) == TYPE_APPRENTICE)
    {
        asize = ADMIN->query_size_apprentice_titles();
        if (level >= asize)
            level = asize - 1;
    }
    else
    {
        if (IS_CONCLAVE(RNAME(shadow_who)))
        {
            if (ADMIN->query_wohs_head() == RNAME(shadow_who))
                return nlevels * 2 + level;
            else
                return nlevels + level;
        }
    }

    if (level >= nlevels)
        level = nlevels - 1;
    else
    if (level < 0)
        level = 0;

    return level;
}

/*
 * Function name: query_wohs_level
 * Description:	  What level has the wizard achieved
 * Returns:	  The level
 */
public int
query_wohs_level()
{
    int nlevels;
    int stat;
    int level;
    int asize;

    setuid();
    seteuid( getuid( this_object() ) );

    nlevels = ADMIN->query_number_levels();


    if (IS_CONCLAVE(RNAME(shadow_who)))
    {
        if (ADMIN->query_wohs_head() == RNAME(shadow_who))
            return nlevels + 1;
        else
            return nlevels;
    }

    /* 3/4 of the levels, without reward */
    if(ADMIN->query_member_type(shadow_who) == TYPE_APPRENTICE)
      {
	level = 0;
      } else { level = (3 * query_wohs_base_level()) / 4; }

    level += shadow_who->query_skill(SS_WOHS_LEVEL_MOD);

    if (ADMIN->query_member_type(shadow_who) == TYPE_APPRENTICE)
    {
        asize = ADMIN->query_size_apprentice_titles();
        if (level >= asize)
            level = asize - 1;
    }
    else
    {
        if (level >= nlevels)
            level = nlevels - 1;
        else
        if (level < 0)
            level = 0;
    }

    return level;
}

/*
 * Function name: change_level_mod
 * Description:   Change the level modifier
 * Arguments:     lev - The number of levels to change
 */
public void
change_level_mod(int lev)
{
    shadow_who->set_skill(SS_WOHS_LEVEL_MOD, shadow_who->query_skill(
        SS_WOHS_LEVEL_MOD) + lev);
}

public string
query_wohs_pretitle()
{
    if (IS_CONCLAVE(RNAME(shadow_who)))
        return "Archmage";

    return "";
}

/*
 * Function:	query_wohs_title
 * Description:	Find the title of this magic-user.
 * Returns:	The title of this magic-user.
 */
public string
query_wohs_title()
{
    int sex;
	string name;
	string order;

    setuid();
    seteuid( getuid( this_object() ) );

    sex = shadow_who->query_gender();

    //string *titles;
    name = RNAME(shadow_who);

    order = ADMIN->query_member_order(name);

    if (name == ADMIN->query_wohs_head())
        return HEAD_TITLE;

    if (IS_CONCLAVE(name))
    {
        if (sex == G_FEMALE)
            switch (order)
        {
        case TYPE_WHITE:
            return WHITE_F_CONCLAVE_TITLE;
        case TYPE_BLACK:
            return BLACK_F_CONCLAVE_TITLE;
        case TYPE_RED:
            return RED_F_CONCLAVE_TITLE;
        }
        else
            switch (order)
        {
        case TYPE_WHITE:
            return WHITE_M_CONCLAVE_TITLE;
        case TYPE_BLACK:
            return BLACK_M_CONCLAVE_TITLE;
        case TYPE_RED:
            return RED_M_CONCLAVE_TITLE;
        }
    }

    return ADMIN->query_title(order, query_wohs_level(), sex);
}

/**********************************************************
 * Shadowed functions within the player object
 **********************************************************/
/*
 * Function name: set_alignment
 * Description:	  Sets the alignment of a player, we will check if
 * 	          the magic-user is about to change order.
 * Arguments:	  a - The amount of points
 */
public void
set_alignment(int a)
{
    object robe;

    shadow_who->set_alignment(a);

    setuid();
    seteuid( getuid( this_object() ) );

    if (ADMIN->query_member_type(shadow_who) == TYPE_APPRENTICE)
        return;

    if ((robe = P(GUILD_OBJECT, shadow_who)))
        if ((robe->query_wohs_change_order(shadow_who->query_alignment())))
            write("You are about to loose your magical powers!\n");
}

/*
 * The following two functions, wield and wear_arm. Blocks the player
 * from wearing and wielding anything except their guild items.
 */
/*
public string
wield(object wep)
{
    string str = MASTER_OB(wep);

    if (!((wep->query_wt() == W_POLEARM || (wep->query_wt() == W_KNIFE))) &&
    (member_array(str, GUILD_ALLOW_WIELD) == -1)
    {
        return "You decide not to wield the " + wep->short() +
        " since it will only disrupt you when using your magic.\n";
    }
    return shadow_who->wield(wep);
}

public string
wear_arm(object arm)
{
    string str = MASTER_OB(arm);

    if ((member_array(str, GUILD_ALLOW_WEAR) == -1) ||
      (!(arm->query_at() & (A_FINGERS | A_NECK))))
    {
        return "You decide not to wear the " + arm->short() +
        " since it will only disrupt you when using your magic.\n";
    }
    return shadow_who->wear_arm(arm);
}
*/

