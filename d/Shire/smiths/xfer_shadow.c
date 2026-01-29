/*
 *   Smiths Guild shadow (layman branch smith)
 *
 *   Copyright Shire 1996
 *
 *   Coded by Morinir/ Lars Madsen
 *
 *   Based upon Herald shadow coded by Dunstable
 *   And Ohtari shadow coded by Boron
 *   by permission from Boron and Olorin
 *
 *   Modified to reflect changes made within the guild. This includes new 
 *   titles, new skills, new admission/acceptance criteria, and the 
 *   removal of the council.
 *   Glaurung 1-2-98
 *   Sep-21-2002 - Added Knights of Solamnia functionality
 *   Updated titles--for the last time so they are more fair.
 *   Finwe, February 2004
 *   May 23 2004 - Added Shadow Union functionality
 *   November 21 2004 - Added Mage functionality
 */

#pragma strict_types;
#pragma save_binary;

inherit "/std/guild/guild_lay_sh.c";

#include "/d/Shire/smiths/smiths.h"

public mixed
query_guild_trainer_lay() { return SMITHS_GUILD_TRAINER; }

int
query_guild_tax_lay() { return LAYMAN_GUILD_TAX; }

string
query_guild_name_lay() { return GUILD_NAME; }

string
query_guild_style_lay() { return GUILD_STYLE; }

/*
 * Function name: query_allow_join_lay
 * Description:   Test if this guild allowed a player to join another
 * Arguments:     type  - the type of guild to join
 *                style - the style of the guild
 *                name  - the name
 * Returns:       1 - I allow member to join another guild
 */
int
query_guild_not_allow_join_lay(object player, string type,
                                   string style, string name)
{
    /* there is currently no restrictions */

    return ::query_guild_not_allow_join_lay(player, type, style, name);
}

static int
query_guild_keep_player(object shadow_who)
{
    if (shadow_who->query_race()=="goblin")
    {
        write("Due to your race you are expelled from the smiths guild.\n");
        remove_smith_guild_member(shadow_who);
        log_membership(shadow_who->query_name() +" was removed from the guild "+
            " due to race.\n");
        return 0;
    }

    return 1;
}

public string
query_guild_title_lay()
{

    string title="";

//    switch(TP->query_stat(SS_LAYMAN))
    switch(shadow_who->query_base_stat(SS_LAYMAN))
    {
// Beginner titles
    case 0..3:
    title = "Fresh";
    break;
    case 4..7:
    title = "Novice";
    break;
    case 8..11:    
    title = "Young";
    break;
    case 12..15:
    title = "Untried";
    break;
    case 16..19:
    title ="Hopeful";
    break;
    case 20..23:
    title ="Juvenile";
    break;
    case 24..27:
    title ="Apprentice";
    break;
    case 28..31:
    title ="Developing";
    break;
    case 32..35:
    title ="Practiced";
    break;
    case 36..39:
    title ="Minor";
    break;

// Trained titles
    case 40..44:
    title ="Capable";
    break;
    case 45..49:
    title ="Efficient";
    break;
    case 50..54:
    title ="Competent";
    break;
    case 55..59:
    title ="Skilled";
    break;
    case 60..64:
    title ="Proficient";
    break;
    case 65..69:
    title ="Experienced";
    break;
    case 70..74:
    title ="Greater";
    break;
    case 75..79:
    title ="Seasoned";
    break;
    case 80..84:
    title ="Exceptional";
    break;
    case 85..89:
    title ="Remarkable";
    break;

// Accomplished Titles
    case 90..95:
    title ="Well-known";
    break;
    case 96..101:
    title ="Talented";
    break;
    case 102..107:
    title ="Professional";
    break;
    case 108..113:
    title ="Brilliant";
    break;
    case 114..119:
    title ="Marvelous";
    break;
    case 120..125:
    title ="Superior";
    break;
    case 126..131:
    title ="Famous";
    break;
    case 132..137:
    title ="Master";
    break;
    case 138..143:
    title ="Legendary";
    break;
    case 144..999:
    title ="Mythical";
    break;
//    default:
//    title ="Supreme";
//    break;
    }

// other guild title functionallity
    if (shadow_who->test_bit("krynn", 1, 0))
       title += " Armoury Master of Vingaard Keep";
      else if ((UNION_MASTER)->query_is_member(shadow_who))
        title += " Smith of the Flame";
//      else if (IS_MAGE)
//        title += " Dark Smith of Mordor";
    else 
       title += " Blacksmith";

    return title;
//    return "Blacksmith";
}

void
add_soul()
{
    shadow_who->add_cmdsoul("/d/Shire/guild/smiths/smiths_craft_soul");
    shadow_who->update_hooks();
}

public string
query_guild_skill_name(int num)
{
    switch (num)
    {
        case SS_FORGING:
            return "forging";

        case SS_MENDING_ARMOURS:
            return "mending armours";

        case SS_MENDING_WEAPONS:
            return "mending weapons";
    }
}

public void
init_lay_shadow(string arg)
{
    ::init_lay_shadow();
    // If the soul is not added from an alarm, there is a problem with ghosts
    set_alarm(0.1, 0.0, add_soul);
}

/*
 * Function name: query_guild_incognito_lay
 * Description:   Define this function so that it returns true if
 *                the player's guild affiliation should be unknown.
 * Returns:       1/0 - unknown/not
 */
public int
query_guild_incognito_lay()
{
    int result;

    if (IS_KNIGHT(shadow_who))
       result = 1;

    if (IS_UNION(shadow_who))
       result = 1;

    return result;
}
