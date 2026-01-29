/*
 *  The Vampyr-guild shadow
 *                        Tricky 9-4-'92
 *              And now altered by Mylos for purposes of 
 *              the vampyr's guild on emerald  19.11.92
 *
 * Changed on the 24.1.94 to accomodate new level names.    Mylos.
 *
 * Changed on the 24.2.94 to allow for the query_guild_title_occ()
 * that Mercade patched in to the guilds.     Mylos.
 *
 */

inherit "/std/guild/guild_occ_sh";

#include "default.h"
#include "/d/Genesis/login/login.h"
#include <ss_types.h>
#include <language.h>

#define CLOAK_ID        "vamp_cloak"

void change_lust(int lust);
void notify_you_killed_me(object ob);

/*
 * Guild titles
 */

#define TITLES ({  "Servile Undead of the Shadow Elements", \
                        "Lesser Ward of the Shadow Elements", \
                        "Ward of the Shadow Elements", \
                        "Undead Walker of the Shadow Elements", \
                        "Ordainer of the Shadow Elements", \
                        "Lesser Celebdhel of the Shadow Elements", \
                        "Celebdhel of the Shadow Elements", \
                        "Ancient Walker of the Shadow Elements", \
                        "BlackWalker of the Shadow Elements", \
                        "Tribune of the Shadow Elements", \
                        "Novice BloodHunter of the Dark Elements", \
                        "BloodHunter of the Dark Elements", \
                        "NightStalker of the Dark Elements", \
                        "NightLord of the Dark Elements", \
                        "Raukamur of the Dark Elements", \
                        "Noble Raukamur of the Dark Elements", \
                        "Inquisitor of the Dark Elements", \
                        "Grand Inquisitor of the Dark Elements", \
                        "Legate of the Dark Elements", \
                        "Prince of the Dark Elements", \
                        "Moloch of the Deaths Elements", \
                        "Ordainer Moloch of the Deaths Elements", \
                        "BloodStalker of the Deaths Elements", \
                        "BloodMaster of the Deaths Elements", \
                        "BloodLord of the Deaths Elements", \
                        "Raukamur of the Deaths Elements", \
                        "Gogonaur of the Deaths Elements", \
                        "Noble Raukamur of the Deaths Elements", \
                        "Ashamite of the Deaths Elements", \
                        "Noble Gogonaur of the Deaths Elements" })

#define VAMPYR_SUB        "vampyr_subloc"

/*
 * Function name: query_guild_tax
 * Description  : Set the initial tax
 */
query_guild_tax_occ()
{
   return 19; /* The cloak_tax construction doesn't seem to work!? */
}

/* Function name: query_guild_not_allow_join_occ
 * Description:   Check if we allow that the player joins another guild.
 * Arguments:     player - the player
 *                type, style, name - the type, style and name of the
 *                intended guild.
 * Returns:       1 if we do not allow, else 0
 */
int
query_guild_not_allow_join_occ(object player, string type, string style,
 string name)
{
    if (::query_guild_not_allow_join_occ(player, type, style, name))
        return 1;

    notify_fail("We vampyrs don't want thieves in our ranks.\n");
    if (style == "thief")
        return 1;

    return 0;
}

/* Function name: query_guild_skill_name
 * Description:   When a players uses the skills command he should get the
 *                the skill names, not the 'special' string.
 * Arguments:     type - the number of the skill
 * Returns:       0 if no skill of mine, else the string.
 */
mixed
query_guild_skill_name(int type)
{
    if(type != 70001)
        return 0;

    return VAMP_SKILL_DESC[0];
}

/* Function name: query_vampyr_level
 * Description:   Get the players numerical guild level
 * Returns:       The numeric guild level
 */
int
query_vampyr_level()
{
    return shadow_who->query_base_stat(SS_OCCUP) / 4;        
}

/* Function name: notify_you_killed_me
 * Description:   This is called each time the vampyr kills something.
 * Arguments:     ob - the object that was killed
 */
void
notify_you_killed_me(object ob)
{
   int lust, align;

   align = ob->query_alignment();
 
   if(ob->query_guild_name_occ() == GUILD_NAME)
        lust = -300;

   if(align >=0)
        lust = (align / 10);

   if(!ob->query_npc())
        lust = -200;

   else
        lust = (align / 20);

   shadow_who->notify_you_killed_me(ob);
   call_out("change_lust", 1);
}

/* Function name: change_lust
 * Description:   When a player has killed something or should change the 
 *                bloodlust for some other reason, call this function.
 * Arguments:     lust - the bloodlust to add.
 */
void
change_lust(int lust)
{
    object ob;

    if (lust > 0)
    {
        shadow_who->set_skill(SS_LUST, shadow_who->query_skill(SS_LUST) +
                              lust);
    } else if (lust == 0) {
        shadow_who->set_skill(SS_LUST, shadow_who->query_skill(SS_LUST) +
                         query_vampyr_level());
    } else {
        shadow_who->set_skill(SS_LUST, shadow_who->query_skill(SS_LUST) +
                         lust);
    }

    if(shadow_who->query_skill(SS_LUST) < 0 &&
        (member_array("/d/Emerald/soul/vamp_soul", 
        shadow_who->query_cmdsoul_list()) >= 0)) {
        shadow_who->catch_msg("You have started to decay, you have lost "+
           "many of your skills.\n");
        shadow_who->remove_cmdsoul("/d/Emerald/soul/vamp_soul");
        shadow_who->add_cmdsoul("/d/Emerald/soul/vamp_pun");
        shadow_who->update_hooks();
        return;
    }
    else if(shadow_who->query_skill(SS_LUST) >= 0 &&
        (member_array("/d/Emerald/soul/vamp_pun",
        shadow_who->query_cmdsoul_list()) >= 0)) {
        shadow_who->catch_msg("The decay stops. You have your skills "+
           "back.\n");
        shadow_who->remove_cmdsoul("/d/Emerald/soul/vamp_pun");
        shadow_who->add_cmdsoul("/d/Emerald/soul/vamp_soul");
        shadow_who->update_hooks();
        return;
    }
}

/* Function name: query_def_post
 * Description:   We change the default post office for our members.
 * Returns:       The new postoffice
 */
string 
query_def_post()
{
    return "/d/Emerald/room/keep/post";
}

/* Function name: query_guild_title_occ
 * Description:   This function returns the vampyr guild title if the player.
 * Returns:       New title
 */
string
query_guild_title_occ()
{
   int stat;

   stat = query_vampyr_level();

   if(stat < 0)
        stat = 0;
   if(stat > 29)
        stat = 29;

   if(present("_vamp_regal_object_", shadow_who))
        return "Ruling Undead of the Prime Planes";

   if(present("_vamp_lord_object_", shadow_who))
        return "Lord of the Etherial Planes";

   if(present("_vamp_master_object_", shadow_who))
        return "Undead Master of the Nether Planes";

   return TITLES[stat];
}

/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - Our subloc
 *                me      - I
 *                for_obj - The looker
 * Returns:       The string the looker shall see
 */
string
show_subloc(string subloc, object me, object for_obj)
{
    string str;

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (subloc != VAMPYR_SUB)
        return shadow_who->show_subloc(subloc, me, for_obj);

    if (for_obj == me)
        str = "You are ";
    else
        str = capitalize(me->query_pronoun()) + " is ";

    return str + "an Undead.\n";
}

/*
 * Function name: query_guild_style_occ
 * Description:   Get the style of this guild
 * Returns:       String describing guild style
 */
string
query_guild_style_occ()
{
    return GUILD_STYLE;
}

/*
 * Function name: query_guild_name_occ
 * Description:   Get the name of this guild
 * Returns:       String naming guild
 */
string
query_guild_name_occ()
{
    return GUILD_NAME;
}

/* 
 * Function name: communicate(string str)
 * Description:   This takes care of the 'say' parts for the guild, whereby
 *                the vampyr will lapse into old speach, ie thou's and thy's
 *                etc.,
 *                String that is spoken (slightly altered)
*/
public int
communicate(string str) 
{
    string verb;

    verb = query_verb();
    if (str == 0)
        str = "";
    if (strlen(verb) && verb[0] == "'"[0])
        str = extract(verb, 1) + " " + str;

    say(QCTNAME(this_object()) + " hisses:" + " " + str + "\n");

    if (this_player()->query_get_echo())
        write("You hiss: " + str + "\n");
    else
        write("Ok.\n");

    return 1;
}

/*
 * Give the player a 10% bonus to STR and DEX if dark, 10% loss
 * if the room is lighted.  Inside rooms will have no bonus loss
 * even when lighted.
 */
int
query_stat(int stat)
{
    int value;

    value = shadow_who->query_stat(stat);
    if (stat == SS_STR || stat == SS_DEX) {
        if (environment(shadow_who)->query_prop(OBJ_I_LIGHT) > 0) {
            if (!environment(shadow_who)->query_prop(ROOM_I_INSIDE))
                value = value * 9 / 10;
        }
        else
            value = value * 11 / 10;
    }
    return value;
}

