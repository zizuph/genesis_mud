/*
 *  The Shire-guild shadow
 *                        Tricky 9-4-'92
 *
 *  Updated on the 6-3-94 by Mylos.
 */
inherit "/std/guild/guild_lay_sh";

#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/sys/const.h"
#include "/d/Shire/common/guild/shire_defs.h"
#include "defs.h"

#define SUBLOC "_shire_subloc"

//   Prototpes
void remove_protect_effect();

int alarm_id;
static int prot;

/*
 * Added by Nick
 */
string query_guild_style_lay() { return "cleric"; }
string query_guild_name_lay() { return "Shire"; }


query_guild_tax_lay()
{
   return GUILD_TAX;
}

/*
 * Function name: query_guild_keep_player
 * Description:   Test if we want to keep the player in the guild.
 *                If we discover a goblin we will keep him, just to throw him
 *                out the proper way later.
 * Arguments:     ob - the player.
 * Returns:       1 if keeping, 0 if not.
 */
int
query_guild_keep_player(object ob)
{
    ob->add_subloc(SUBLOC, this_object());
    return 1;
}


#if 0

/*
 * Keep our guild tax updated.
 * This looks spiffy, but does not work for some reason. At least,
 * I think it does not work (and I am too lazy to test it at this
 * moment). 
 */
query_learn_pref(stat)
{
    int val, *learn_pref;

    if (stat == SS_LAYMAN)
    {
        val = GUILD_TAX;

        /* Test to see if they are in a guild that forbids using our spells */
        if (this_object()->query_guild_name_occ() != "Solamnian Knights")
            val -= ;

        return val;
    }

    if (stat == -1)
    {
        learn_pref = query_shadow_who()->query_learn_pref(-1);
        val = SHIRE_BASE_TAX;   /* Minimum tax */

        /* Test to see if they are in a guild that forbids using our spells */
        if (this_object()->query_guild_name_occ() != "Solamnian Knights")
            val += SHIRE_SPELL_TAX;

        learn_pref[SS_LAYMAN] = val;
        return learn_pref;
    }

    /* Take care not to use this_object() here! Infinite recursion! */
    return query_shadow_who()->query_learn_pref(stat);
}

#endif

/***************************************************************************
 *
 *   Shire-specific stuff
 */

#define MALE_TITLES ({ "Minor Hinling", "Hinling", "Yallaren Hinling", \
                       "Wanderer", "Experienced Wanderer", \
                       "Striker", "Fang", \
                       "Ring Bearer", "Shield Bearer", "Flag Bearer", \
                       "Apprentice Champion", "Champion", \
                       "Clan Apprentice", "Clan Member", "Clan Leader", \
                       "Clan Chieftain", \
                       "Hero", "Deputy-Hero", "Sheriff-Hero", \
                       "Lesser Krondar", "Krondar", "Greater Krondar", \
                       "Sheriff", "Lesser Master", \
                       "Master", "Greater Master", "Apprentice Bantor", \
                       "Bantor", "Wizened Bantor", "Brilliant Bantor", \
                       "Sorceror", "High White Sorceror" })

#define FEMALE_TITLES ({ "Minor Maiden", "Maiden", "Yallaren Maiden", \
                         "Wanderer", "Experienced Wanderer", \
                         "Striker", "Amazon", "Ring Mistress", \
                         "Shield Mistress", "Flag Mistress", \
                         "Apprentice Champion", "Champion", \
                         "Clan Apprentice", "Clan Member", "Clan Leader", \
                         "Clan Chieftain", \
                         "Heroine", "Deputy-Heroine", \
                         "Sheriff-Heroine", "Lesser Krondress", "Krondress",\
                         "Greater Krondress", "Sheriff", \
                         "Yallaren Lady", "Lady", "Greater Lady", \
                         "Apprentice Bantress", "Bantress", \
                         "Wizened Bantress", "Brilliant Bantress", \
                         "Sorceress", \
                         "High White Sorceress" })


/*
 * Function name:   query_guild_title_lay()
 * Description:     Gets the name of the layman guild.
 * Returns:         Title.
 */
string 
query_guild_title_lay()
{
    int stat;
    object who;
    string council_str, my_name;

    who = query_shadow_who();
    stat = who->query_base_stat(SS_LAYMAN) / 3;
    my_name = who->query_real_name();

    seteuid(getuid());
    if (SHIRE_COUNCIL->is_council_member(my_name))
        council_str = " and Council member";
    else
        council_str = "";

    if (stat < 0)
	stat = 0;
    if (stat > 31)
	stat = 31;

    if (who->query_gender() == G_FEMALE)
	return FEMALE_TITLES[stat] + council_str + " of the Shires";
    else
	return MALE_TITLES[stat] + council_str + " of the Shires";
}


#define PROUDNESS ({ "a fresh", "a puzzled", "a startled", "an average", \
                     "an interested", "an interesting", "a proud", "a great", \
                     "an adored", "a widely adored" })

/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - Our subloc
 *                me      - I
 *                for_obj - The looker
 * Returns:       The string the looker shall see
 */
string
show_subloc(string subloc, object who, object for_obj)
{
    string str;
    int tmp;

    if (subloc != SUBLOC)
        return query_shadow_who()->show_subloc(subloc, who, for_obj);

    if (who->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (for_obj == who)
        str = "You are ";
    else
        str = capitalize(who->query_pronoun()) + " is ";

    if (who->query_wiz_level())
        str += "greatly admired";
    else
    {
        tmp = who->query_base_stat(SS_LAYMAN) / 10;

        if (tmp > 9)
            tmp = 9;

        seteuid(getuid());
        if (SHIRE_COUNCIL->is_council_member(who->query_real_name()))
            str += "a respected Council";
        else
            str += PROUDNESS[tmp];
    }

    return str + " member of the glorious Hin Warrior guild.\n";
}

/*
 * External functions
 */

int
set_protect_spell_time(int val)
{
    alarm_id = set_alarm(itof(val),0.0,&remove_protect_effect());
    prot = 1;
    return 1;
}

int
query_protect_spell_time()
{
    return ftoi(get_alarm(alarm_id)[2]);
}

void
remove_protect_effect()
{
    query_shadow_who()->catch_message("The protection spell wears off.\n");
    prot = 0;
}

void
reduce_hit_point(int val)
{
    /*
     * We're allowed the give 50% help in combat.
     * Here we give something between 25% and 50% help.
     */

    if (prot)
        val = ((50 + random(25)) * val) / 100;
    query_shadow_who()->reduce_hit_point(val);
}

