
 /* Spirit Circle of Psuchae Lay Soul   */
 /* July 24th, 2003                     */
 /* Jaacar                              */

/* Modifications
 * 
 * Petros March 2009 - Added swjpray emote so that a Spirit Circle Elder
 *                     can accept an Elemental Worshippers applicant,
 *                     allowing them to join.
 */
 
#pragma strict_types
#pragma save_binary

inherit "/cmd/std/command_driver";

#include <stdproperties.h>
#include <macros.h>
#include <adverbs.h>
#include <ss_types.h>
#include <cmdparse.h>
#include <language.h>
#include <composite.h>
#include <options.h>
#include <wa_types.h>
#include <filter_funs.h>
#include "defs.h"
#include SPIRIT_HEADER
#include COUNCIL_HEADER

#ifndef MY
#define MY TP->query_possessive()
#endif
#ifndef HE
#define HE TP->query_pronoun()
#endif
#define SOULDESC(x) (TP->add_prop(LIVE_S_SOULEXTRA, x))

// Defines
#define I_CAN_JOIN "_i_can_join_"
#define WOR_OBJECTS "/d/Calia/worshippers/objects/"
#define WORSHIPPER_COUNCIL_ROOM "/d/Calia/guilds/elementalists/temple/worshipper_councilroom"

string
get_soul_id()
{
    seteuid(getuid());
    return "Spirit Circle of Psuchae";
}

string
my_time()
{
    return (ctime(time())[4..9] + ": ");
}

int
query_cmd_soul()
{
    seteuid(getuid());
    return 1;
}

int
is_spirit_member(object living)
{
    return living->query_guild_name_occ() == SPIRIT_GUILD_NAME;
}

int
is_worship(object living)
{
    return living->query_guild_name_lay() == WORSHIPPER_GUILD;
}

int
is_spirit(object living)
{
    return living->query_skill(SS_SPIRIT_CHOSEN);
}

string
group_desc(object looking, object *group, int cap)
{
    string *qdesc, qd;

    if (member_array(looking, group) > -1) {
        group -= ({looking});
        if (cap)
            qdesc = ({"You"});
        else
            qdesc = ({"you"});
        if (sizeof(group))
            qdesc += map(group, &->query_the_name(looking));
    }
    else {
        if (cap)
            qdesc = ({group[0]->query_The_name(looking) });
        else
            qdesc = ({group[0]->query_the_name(looking) });
        group -= ({group[0]});
        if (sizeof(group))
            qdesc += map(group, &->query_the_name(looking));
    }

    return COMPOSITE_WORDS(qdesc); 
}

int
cmd_list()
{
    write("You can use the following emotes:\n" +
    "shide                          Hide your extra title (if you have one)\n"+
    "sunhide                        Unhide your extra title (if you have one)\n"+
    "sweyes                         Your eyes dance with the power (of your\n"+
    "                               Elemental if you were a Worshipper)\n"+
    "swjoy                          Show an expression of joy\n" +
    "swjpray                        Pray for a Seeker of the Elementals (Elders only)\n" +
    "swkneel (<player>)             Kneel briefly (before <player>)\n" +
    "swsilence                      Motion for a moment of silence\n" +
//    "swwho                          Get a list of Worshippers in the Realms.\n"+
    "\n");
    return 1;
}

int
so_help(string str)
{
    if (!str)
        return 0;

    if (str == "spirit other")
    {
        write("You may get help on the following:\n\n"+
            "    help spirit other emotes - a list of Worshipper emotes\n"+
            "    help spirit other        - this list\n"+
            "\n");
        return 1;
    }

    if (str == "spirit other emotes")
    {
        cmd_list();
        return 1;
    }

    return 0;
}

int
shide()
{
    if (TP->query_prop(HIDE_LAYMAN_TITLE))
    {
        write("You have already hidden your extra title.\n");
        return 1;
    }

    write("You hide your extra title.\n");
    TP->add_prop(HIDE_LAYMAN_TITLE,1);
    return 1;
}

int
sunhide()
{
    if (!TP->query_prop(HIDE_LAYMAN_TITLE))
    {
        write("You have already unhidden your extra title.\n");
        return 1;
    }

    write("You unhide your extra title.\n");
    TP->remove_prop(HIDE_LAYMAN_TITLE);
    return 1;
}
int
swjoy()
{
    write("You show an expression of your joy.\n");
    all("'s face brightens with joy.");
    return 1;
}

int
swkneel(string str)
{
    object *who;
    NF("Kneel before who?\n");
    if (!str || str == "")
    {
        write("You kneel in prayer briefly.\n");
        all(" kneels briefly in prayer.");
        return 1;
    }
    who = parse_this(str, " %l");
    if (!sizeof(who)) return 0;
    actor("You kneel briefly before",who);
    target(" kneels briefly before you.",who);
    all2actbb(" kneels briefly before",who,".");
    return 1;
}

int
sweyes()
{
    int who;
    who = TP->query_skill(SS_PATRON_ELEMENTAL);
    
    switch (who)
    {
        case FIRE_FLAG:
            write("Your eyes flare with the power of Lord Pyros!\n");
            all("'s eyes flare like a bright red flame.");
            break;
        case EARTH_FLAG:
            write("Your eyes sparkle with the power of Lady Gu!\n");
            all("'s eyes sparkle like two perfectly cut diamonds.");
            break;
        case WATER_FLAG:
            write("Your eyes glow with the power of Lord Diabrecho!\n");
            all("'s eyes glow a bright watery blue.");
            break;
        case AIR_FLAG:
            write("Your eyes flash with the power of Lady Aeria!\n");
            all("'s eyes flash suddenly like a lightning strike.");
            break;
        default:
            write("Your eyes flash with the power!\n");
            all("'s eyes flash with power.");
            break;
    }
    return 1;
}

int
swsilence()
{
    write("You motion for a moment of silence.\n");
    all(" raises "+MY+" hand and motions for a moment of silence.");
    return 1;
}

int
swwho()
{
    object *list;
    string fire, water, earth, air;

    list = filter(users(),&operator(==)(WORSHIPPER_GUILD) @
        &->query_guild_name_lay());
    list = filter(list, &operator(!=)(100) @ &->query_invis());

    fire = implode(filter(list,&operator(==)(FIRE_FLAG) @
        &->query_skill(SS_PATRON_ELEMENTAL))->query_presentation(),
        "\n");
    water = implode(filter(list,&operator(==)(WATER_FLAG) @
        &->query_skill(SS_PATRON_ELEMENTAL))->query_presentation(),
        "\n");
    earth = implode(filter(list,&operator(==)(EARTH_FLAG) @
        &->query_skill(SS_PATRON_ELEMENTAL))->query_presentation(),
        "\n");
    air = implode(filter(list,&operator(==)(AIR_FLAG) @
        &->query_skill(SS_PATRON_ELEMENTAL))->query_presentation(),
        "\n");

    write("The following Worshippers are within the Realms:\n"+
        (strlen(fire) > 2 ? "Followers of Pyros:\n"+fire : "") +
        (strlen(water) > 2 ? "\n\nFollowers of Diabrecho:\n"+water : "") +
        (strlen(earth) > 2 ? "\n\nFollowers of Gu:\n"+earth : "") +
        (strlen(air) > 2 ? "\n\nFollowers of Aeria:\n"+air : "") +
        "\n");
 
    return 1;
}

public int
swjpray(string str)
{
    object joinob, player, target;
    string name;
    
    player = this_player();
    if (!COUNCIL_CODE->is_spirit_elder(player->query_real_name())
        && !player->query_wiz_level())
    {
        notify_fail("Only Elders may pray for someone to be accepted by "
            + "the Four Prime Elementals.\n");
        return 0;
    }
    
    setuid();
    seteuid(getuid());
    return WORSHIPPER_COUNCIL_ROOM->do_allow(str);
}

mapping
query_cmdlist()
{
    return (["help"      : "so_help",
             "shide"     : "shide",
             "sunhide"   : "sunhide",
             "sweyes"    : "sweyes",
             "swjoy"     : "swjoy",
             "swjpray"   : "swjpray",
             "swkneel"   : "swkneel",
             "swsilence" : "swsilence",
//             "swwho"     : "swwho"
             ]);
}


