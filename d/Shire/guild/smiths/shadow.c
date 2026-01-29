/*
 *   Smiths Guild shadow (craftsman branch smith)
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
 *
 *   Ported to Craft slot - Palmer 13 July 2006
 *
 *   21-July-2006 Palmer
 *     Added 'help smiths news' and news notification when logging in
 */

#pragma strict_types;

inherit "/std/guild/guild_craft_sh.c";

#include "/d/Shire/guild/smiths/smiths.h"

public mixed
query_guild_trainer_craft() { return SMITHS_GUILD_TRAINER; }

int
query_guild_tax_craft() { return CRAFTSMAN_GUILD_TAX; }

string
query_guild_name_craft() { return GUILD_NAME; }

string
query_guild_style_craft() { return GUILD_STYLE; }

/*
 * Function name: query_allow_join_craft
 * Description:   Test if this guild allowed a player to join another
 * Arguments:     type  - the type of guild to join
 *                style - the style of the guild
 *                name  - the name
 * Returns:       1 - I allow member to join another guild
 */
int
query_guild_not_allow_join_craft(object player, string type,
                                   string style, string name)
{
    /* there is currently no restrictions */

    return ::query_guild_not_allow_join_craft(player, type, style, name);
}

static int
query_guild_keep_player(object shadow_who)
{
    return 1;
}

public string
query_guild_title_craft()
{
    int ttl;

    if (!shadow_who->query_prop("_smith_i_title"))
        return "";

    string title = "";

    // We can remove this next reboot:
    ttl = shadow_who->query_prop(SMITHS_ITEMS_FORGED);
    if (ttl == 0)
    {
        ttl = SMITHS_MASTER_OBJ->sm_query_forged_total(shadow_who);
        shadow_who->add_prop(SMITHS_ITEMS_FORGED, ttl);
    }

    //switch(shadow_who->query_base_stat(SS_CRAFT))
    switch(ttl)
    {
    case 0..200:
    title = "Fresh";
    break;
    case 201..400:
    title = "Novice";
    break;
    case 401..600:    
    title = "Young";
    break;
    case 601..800:
    title = "Untried";
    break;
    case 801..1000:
    title ="Hopeful";
    break;
    case 1001..1200:
    title ="Juvenile";
    break;
    case 1201..1400:
    title ="Apprentice";
    break;
    case 1401..1600:
    title ="Developing";
    break;
    case 1601..1800:
    title ="Practiced";
    break;
    case 1801..2000:
    title ="Minor";
    break;

    // Trained titles

    case 2001..4300:
    title ="Capable";
    break;
    case 4301..6600:
    title ="Efficient";
    break;
    case 6601..9200:
    title ="Competent";
    break;
    case 9201..11500:
    title ="Skilled";
    break;
    case 11501..13800:
    title ="Proficient";
    break;
    case 13801..16100:
    title ="Experienced";
    break;
    case 16101..18400:
    title ="Greater";
    break;
    case 18401..20700:
    title ="Seasoned";
    break;
    case 20701..23000:
    title ="Exceptional";
    break;
    case 23001..25000:
    title ="Remarkable";
    break;

    
    // Accomplished Titles
    case 25001..27500:
    title ="Well-known";
    break;
    case 27501..30000:
    title ="Talented";
    break;
    case 30001..32500:
    title ="Professional";
    break;
    case 32501..35000:
    title ="Brilliant";
    break;
    case 35001..37500:
    title ="Marvelous";
    break;
    case 37501..40000:
    title ="Superior";
    break;
    case 40001..42500:
    title ="Famous";
    break;
    case 42501..45000:
    title ="Master";
    break;
    case 45001..47500:
    title ="Legendary";
    break;
    case 47501..50000:
    title ="Mythical";
    case 50001..999999:
    title ="Elder Mythical";
    break;
    }

    // other guild title functionallity
    if (shadow_who->test_bit("krynn", 1, 0))
       title += " Armoury Master of Vingaard Keep";
      else if ((UNION_MASTER)->query_is_member(shadow_who))
        title += " Smith of the Flame";
    else 
       title += " Blacksmith";

    return title;
}

void
add_soul(int news)
{
    int ttl_items_forged = SMITHS_MASTER_OBJ->sm_query_forged_total(shadow_who);

    //shadow_who->add_prop(SMITHS_ITEMS_FORGED, ttl_items_forged);
    if (news)
        shadow_who->catch_tell("\n\n< Blacksmiths >  See 'help smiths news' for news since you last awoke.\n\n");
    //shadow_who->add_cmdsoul("/d/Shire/guild/smiths/smiths_craft_soul");
    shadow_who->add_cmdsoul("/d/Shire/guild/smiths/soul");
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
init_craft_shadow(string arg)
{
    int news = 0;

    if (shadow_who->query_login_time() <= file_time(SMITHS_NEWS))
        news = 1;
    ::init_craft_shadow();
    // If the soul is not added from an alarm, there is a problem with ghosts
    set_alarm(0.5, 0.0, &add_soul(news));
}


/*
 * Function name: query_guild_incognito_craft
 * Description:   Define this function so that it returns true if
 *                the player's guild affiliation should be unknown.
 * Returns:       1/0 - unknown/not
 */
public int
query_guild_incognito_craft()
{
    int result;

    if (IS_KNIGHT(shadow_who))
       result = 1;

    if (IS_UNION(shadow_who))
       result = 1;

    return result;
}
