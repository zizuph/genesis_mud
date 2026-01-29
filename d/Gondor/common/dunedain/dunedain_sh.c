/*
 *    /d/Gondor/common/dunedain/dunedain_sh.c
 *
 *    Copyright (c) 1994, 1997 by Christian Markus
 *
 *    The guild shadow for the Dunedain of Gondor
 *
 *    Created: Olorin, 04-nov-1994
 *          using /d/Gondor/common/guild2/morgul_shadow.c by Olorin
 *
 *    Modification log:
 *    12-Feb-1997, Olorin:    General revision.
 *    16-Nov-1999, Morbeche:  Updated skills to reflect mudlib changes.
 *    27-Oct-2002, Gwyneth:   Added runtime prevention.
 *    10-Jan-2019, Finwe:     Clean up, Fix bug that doest boot non-humans  
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
#include "/d/Gondor/common/dunedain/lib/dunedain_defs.h"

/*
 * Guild tax calculation:
 * Shop in dunedain guild:                           1.00%
 * Skills:      trading:        50 levels, 20 tax:   0.33%
 *              axe:            50 levels, 20 tax:   0.50%
 *              herbalism:      50 levels, 30 tax:   0.50%
 *              spellcraft:     50 levels, 30 tax:   0.50%
 * General skill levels lowered:
 *              awareness       50 levels, 20 tax:   0.33%
 *              language        50 levels, 20 tax:   0.33%
 *              climb           50 levels, 20 tax:   0.33%
 * Sum:                                              3.82%
 * Actual tax:                                       4.00%
 */
#define GUILD_TAX              4
#define TRAINER        (GUILD_DIR + "rooms/train_hall")
#undef DEBUG
#ifdef DEBUG
#define DEBUG_MSG(x) shadow_who->catch_msg(file_name(TO)+": "+x+"\n");
#else
#define DEBUG_MSG(x)
#endif

/*
 *    Prototypes:
 */
public  nomask int     query_dunadan_level();
private        void    remove_dunadan(object pl, string house, string reason);
private        void    remove_dunadan_from_house(object pl, string house, string reason);

/*
 * Global variables
 */
static  string  Dunedain_House;
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
     * We do not restrict guild membership of the dunedain.
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

    setuid();
    seteuid(getuid());

//    if ((race != DUNEDAIN_RACE) && (race != "ghost"))
    if(ob->query_race() != "human")
    {
        write("Only humans can belong to the Houses of the Dunedain!\n");
        /*
         * We use our own function to remove the player.
         * Therefore, we return always 1.
         */
        set_alarm(1.0, 0.0, &remove_dunadan(ob, ob->query_dunadan_house(),
            "was removed (race = "+race+") from"));
        return 0;
    }

    return 1;
}

/*
 * Function name: set_dunadan_house
 * Description:      set the House the dunadan belongs to
 * Arguments:     the name of the House
 * Returns:       1 - success, 0 - the House does not exist.
 */
public nomask int
set_dunadan_house(string str)
{
    str = CAP(LOW(str));

    if (member_array(str, DUNEDAIN_HOUSES) < 0)
    {
    // To permit joining without a House:
    if (LOW(str) != DUNEDAIN_NO_HOUSE)
        return 0;
    else
        Dunedain_House = "";
    }
    else
    {
    Dunedain_House = str;
    }
    return 1;
}

/*
 * Function name: query_dunadan_house
 * Description:   returns the House the dunadan belongs to
 * Returns:       the name of the House
 */
public nomask string
query_dunadan_house()
{
    if (!strlen(Dunedain_House))
        return "";
    return Dunedain_House;
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
    if (!strlen(Dunedain_House))
        return "Dunadan";
    return "of the House of "+Dunedain_House;
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
    return 1;
}

/*
 *    Function name:    query_def_post
 *    Description:    return the subrace specific post office
 *                    this should be set only by the race guild!
 *    Returns:        the path name to the post office
 */
public nomask string
query_def_post() { return DUNEDAIN_POST; }

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
    if (type == SS_DUNEDAIN_LEVEL)
        return "";

    return 0;
}

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
           str2,
           house;

    if (subloc != DUNEDAIN_S_SUBLOC)
        return shadow_who->show_subloc(subloc, me, for_obj);

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";
    if (for_obj == me)
    {
    str = "You are ";
        str2 = "You have ";
    }
    else
    {
    str = CAP(me->query_pronoun()) + " is ";
        str2 = CAP(me->query_pronoun()) + " has ";
    }

    if (for_obj != me && me->query_prop("_RoN_incognito_"))
        return str2 + "the bearing of the noble blood of Westernesse.\n";
    switch (query_dunadan_level())
    {
    case DL_LORD:
    switch (me->query_gender())
    {
    case 1:
        str += "the Lady";
        break;
    default:
    case 0:
        str += "the Lord";
        break;
    }
    break;
    default:
    case 0..99:
    str += "a dunadan";
    break;
    }
    if (strlen(house = query_dunadan_house()))
        str += (" of the House of "+query_dunadan_house());
    return (str + ".\n");
}

/*
 * Function name: query_dunadan_level
 * Description:   return the level of the dunadan within the guild,
 *                the level is stored as a skill number
 *                (SS_DUNEDAIN_LEVEL)
 * Returns:       the level
 */
public nomask int
query_dunadan_level()
{
    if (strlen(Dunedain_House))
    return shadow_who->query_skill(SS_DUNEDAIN_LEVEL);
    return 0;
}

/*
 * Function name: set_dunadan_level
 * Description:   set the level of the dunadan in the guild
 * Argument:      val - the new level
 * Returns:       1/0 - success/failure
 */
public nomask int
set_dunadan_level(int val)
{
    if ((val < 0) || (val > DL_SUB_LORD))
        return 0;

    if (!strlen(Dunedain_House))
    return 0;

    shadow_who->set_skill(SS_DUNEDAIN_LEVEL, val);
    return 1;
}

/*
 * Function name: set_dunadan_lord_level
 * Description:   set the rank of the dunadan to Lord
 * Returns:       1/0 - success/failure
 */
public nomask int
set_dunadan_lord_level()
{
    // Only the master object may set this variable!
    if (MASTER_OB(previous_object()) != DUNEDAIN_MASTER)
        return 0;
    if (query_dunadan_level() < DL_SUB_LORD)
        return 0;
    shadow_who->set_skill(SS_DUNEDAIN_LEVEL, DL_LORD);
    return 1;
}

/*
 * Function name: set_skill
 * Description:   internal checks if the skill to be set is SS_DUNEDAIN_LEVEL
 * Arguments:     skill - the skill number
 *                val   - the new value
 * Returns:       1/0   - success/failure
public int
set_skill(int skill, int val)
{
    if (skill != SS_DUNEDAIN_LEVEL)
        return shadow_who->set_skill(skill, val);

    return set_dunadan_level(val);
}

/*
 * COMMENTING OUT FOR NOW
 * TL-May 14, 2006--this is bad code
 * Function name: second_life
 * Description:   Handles all that should happen to a dying player.
 * Argument:      Object that caused the kill.
 * Returns:       True if the living object should get a second life
 */
/*
public int
second_life(object killer)
{
    if ((shadow_who->query_hp() <= 0) && 
    (query_dunadan_level() >= DL_LORD))
    {
        seteuid(getuid());
        DUNEDAIN_MASTER->remove_lord_through_death(shadow_who->query_name());
    }

    return shadow_who->second_life(killer);
}
*/

/*
 * Function name: remove_dunadan_from_house
 * Description:   remove a player from a House
 *                This function is used to allow a player to join
 *                another house of the dunedain after being released
 *                by the Lord or Lady of his old house.
 * Arguments:     pl     - object pointer to the member
 *                house  - the name of the House
 *                reason - why do we remove the player?
 * Returns:       1/0 - success/failure
 */
public nomask int
remove_dunadan_from_house(object pl, string house, string reason)
{
    if (!objectp(pl) || (pl != shadow_who))
        return 0;

    pl->catch_msg("You are removed from the House of "+house+"!\n");
    seteuid(getuid());
    return DUNEDAIN_MASTER->remove_dunadan_from_house(pl, house, reason);
}

/*
 * Function name: remove_dunadan
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
remove_dunadan(object pl, string house, string reason)
{
    if (!objectp(pl) || (pl != shadow_who))
    return 0;

    pl->catch_msg("You are removed from the Houses of the Dunedain!\n");
    seteuid(getuid());
    return DUNEDAIN_MASTER->remove_dunadan(pl, house, reason);
}

/*
 * Function name: add_dunedain_soul
 * Description:   add the dunedain soul
 */
public nomask void
add_dunedain_soul()
{
    if (!objectp(shadow_who))
        return;

    shadow_who->add_cmdsoul(DUNEDAIN_SOUL);
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
    string  dh,
            name,
            lname;

    FIX_EUID;

    shadow_who->add_subloc(DUNEDAIN_S_SUBLOC, TO);

    if (!DUNEDAIN_MASTER->keep_player(shadow_who))
    {
        set_alarm(0.0, 0.0, &remove_dunadan(shadow_who, 0,
            "was removed (shadow) from"));
        return;
    }
    DEBUG_MSG("checked keep_player in DUNEDAIN_MASTER");

    dh = DUNEDAIN_MASTER->query_dunadan_house(name = shadow_who->query_name());
/*
    if (!strlen(dh) && interactive(shadow_who))
*/
if (!strlen(dh) &&
interactive(shadow_who) && !shadow_who->query_wiz_level())
    {
    write_file(DUNEDAIN_LOG, name + 
           " is not logged as member of the Dunedain! " +
           ctime(time()) + ".\n");
    }

    if (dh != DUNEDAIN_NO_HOUSE)
    set_dunadan_house(dh);

    if (query_dunadan_level() == DL_LORD)
    {
        if ((lname = DUNEDAIN_MASTER->query_house_lord(dh))
            != shadow_who->query_name())
        {
            set_dunadan_level(DL_SUB_LORD);
            if (strlen(lname))
                shadow_who->catch_msg("You have been replaced as head of the House of "
                  + dh + " by " + lname + ".\n");
            else
                shadow_who->catch_msg("You are no longer head of the House of "
                      + dh + ".\n");
        }
        else if (shadow_who->query_wiz_level())
        {
            shadow_who->catch_msg("As wizard, you cannot remain head of the "
                  + "House of " + dh + "!\n");
            shadow_who->set_dunadan_level(DL_SUB_LORD);
            DUNEDAIN_MASTER->remove_lord_from_tree(shadow_who->query_name(), dh);
        }
    }

    // If the soul is not added from an alarm, there is a problem with ghosts
    set_alarm(0.0, 0.0, add_dunedain_soul);
}

public int
query_guild_leader_race()
{
    return (shadow_who->query_skill(SS_DUNEDAIN_LEVEL) == DL_LORD);
}

/*
 * Function name: set_dunedain_house
 * Description:      Interface to set_dunadan_house for 
 *                backwards compatibility.
 * Arguments:     the name of the House
 * Returns:       1 - success, 0 - the House does not exist.
 */
public nomask int
set_dunedain_house(string str)
{
    return set_dunadan_house(str);
}

/*
 * Function name: query_dunedain_house
 * Description:      Interface to query_dunadan_house for 
 *                backwards compatibility.
 * Returns:       the name of the House
 */
public nomask string
query_dunedain_house()
{
    return query_dunadan_house();
}

/*
 * Function name: query_dunedain_level
 * Description:   Interface to query_dunadan_level for
 *                backwards compatibility
 * Returns:       the level
 */
public nomask int
query_dunedain_level()
{
    return query_dunadan_level();
}

/*
 * Function name: set_dunedain_level
 * Description:   Interface to set_dunadan_level for
 *                backwards compatibility
 * Argument:      val - the new level
 * Returns:       1/0 - success/failure
 */
public nomask int
set_dunedain_level(int val)
{
    return set_dunadan_level(val);
}
