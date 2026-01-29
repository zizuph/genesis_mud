/*
 * /d/Gondor/guilds/militia/emotes.c
 *
 * This code is copyright (c) 2001 by Scott A. Hardy and Alyssa Hardy.
 * Genesis is a game currently run through Chalmers University.
 * Scott and Alyssa Hardy have seen the 1991 document of Genesis'
 * called 'legal', and they do not forfeit any of their intellectual
 * property rights as that document supposes they would.  They are the
 * sole and complete owners of this code, which as of April 2001 they are
 * loaning to Genesis.  Genesis does not own this code, or
 * have any right to transfer it to anyone.  By its ongoing
 * use and storage of his code, Genesis acknowledges and agrees
 * to all of the above.
 *
 * Emotes for the Thornlin Militia
 *
 * Gwyneth and Auberon, March 4, 2001
 *
 * Modification log:
 */

#include <macros.h>
#include <language.h>
#include <wa_types.h>
#include <files.h>
#include <options.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <adverbs.h>
#include <cmdparse.h>

#define IS_MEMBER(x) (x->query_guild_member(MILITIA_NAME))

/* Function name: maloft
 * Description  : Emote for the Militia of Thornlin to hold a weapon aloft
 * Arguments    : string str - as entered by the player
 * Returns      : 1 on success, 0 on failure
 */
int
maloft(string str)
{
    object weapon, *weapons = this_player()->query_weapon(-1);

    if (!sizeof(weapons))
    {
        notify_fail("You have no weapon to do that with.\n");
        return 0;
    }

    weapon = find_wep(this_player(), 0);
    if (!objectp(weapon))
        weapon = weapons[0];

    write("You hold your " + weapon->short() + " aloft victoriously.\n");
    all(" holds " + this_player()->query_possessive() + " " + weapon->short() +
        " aloft victoriously.");
    return 1;
}

/* Function name: mblink
 * Description  : Emote for the Militia of Thornlin to blink
 * Arguments    : string str - as entered by the player
 * Returns      : 1 always
 */
int
mblink(string str)
{
    write("You blink your eyes rapidly to clear your vision.\n");
    all(" blinks " + this_player()->query_possessive() + " eyes rapidly " +
        "to clear " + this_player()->query_possessive() + " vision.");
    return 1;
}

/* Function name: mchew
 * Description  : Emote for the Militia of Thornlin to chew on a twig
 * Arguments    : string str - as entered by the player
 * Returns      : 1 always
 */
int
mchew(string str)
{
    write("You chew idly on a twig you found somewhere.\n");
    allbb(" chews idly on a twig " + this_player()->query_pronoun() +
        " found somewhere.");
    return 1;
}

/* Function name: mcrouch
 * Description  : Emote for the Militia of Thornlin to crouch down
 * Arguments    : string str - as entered by the player
 * Returns      : 1 on success, 0 on failure
 */
int
mcrouch(string str)
{
    object *oblist, weapon;
    string wep_short;

    weapon = find_wep(this_player(), 0);

    if (objectp(weapon))
    {
        wep_short = weapon->short();

        if (!strlen(str))
        {
            write("You crouch down, holding your " + wep_short + " out " +
                "defensively.\n");
            all(" crouches down, holding " + this_player()->query_possessive() +
                " " + wep_short + " out defensively.");
            return 1;
        }
        else
        {
            /* Find if the argument is valid */
            oblist = parse_this(str, "[down] [against] [the] %i");

            if (!sizeof(oblist))
            {
                notify_fail("Crouch down [against whom]?\n");
                return 0;
            }

            if (sizeof(oblist) > 1)
                oblist = ({ oblist[0] });

            actor("You crouch down, pointing your " + wep_short + " towards", 
                oblist, ".");
            target(" crouches down, pointing " + 
                this_player()->query_possessive() + " " + wep_short +
                " towards you.", oblist);
            all2act(" crouches down, pointing " +
                this_player()->query_possessive() + " " + wep_short +
                " towards", oblist, ".");
            return 1;
        }
    }
    else
    {
        if (!strlen(str))
        {
            write("You crouch down, holding your arms out defensively.\n");
            all(" crouches down, holding " + 
                this_player()->query_possessive() + " arms out defensively.");
            return 1;
        }
        else
        {
            /* Find if the argument is valid */
            oblist = parse_this(str, "[down] [against] [the] %i");

            if (!sizeof(oblist))
            {
                notify_fail("Crouch down [against whom]?\n");
                return 0;
            }

            if (sizeof(oblist) > 1)
                oblist = ({ oblist[0] });

            actor("You crouch down defensively, keeping a close eye on " +
                "every move that", oblist, " makes.");
            target(" crouches down defensively, keeping a close eye on " +
                "your every move.", oblist);
            all2act(" crouches down defensively, keeping a close eye on " +
                "every move that", oblist, " makes.");
            return 1;
        }
    }
}

/* Function name: mglare
 * Description  : Emote for the Militia of Thornlin to glare around
 * Arguments    : string str - as entered by the player
 * Returns      : 1 on success, 0 on failure
 */
int
mglare(string str)
{
    object *oblist;
 
    if (!strlen(str))
    {
        write("You narrow your eyes, glaring suspiciously around the area.\n");
        all(" narrows " + this_player()->query_possessive() + " eyes, " +
            "glaring suspiciously around the area.\n");
        return 1;
    }

    /* Find if the argument is valid */
    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Glare at [whom]?\n");
        return 0;
    }

    actor("You narrow your eyes, glaring angrily at", oblist, ".");
    target(" narrows " + this_player()->query_possessive() + " eyes " +
        "suspiciously, glaring angrily at you.", oblist);
    all2actbb(" narrows " + this_player()->query_possessive() + " eyes " +
        "suspiciously, glaring angrily at", oblist, ".");
    return 1;
}

/* Function name: mgrasp
 * Description  : Emote for the Militia of Thornlin to grasp another's hand
 * Arguments    : string str - as entered by the player
 * Returns      : 1 on success, 0 on failure
 */
int
mgrasp(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        notify_fail("Grasp who's shoulder?\n");
        return 0;
    }

    /* Find if the argument is valid */
    oblist = parse_this(str, "%i");

    if (!sizeof(oblist))
    {
        notify_fail("Grasp who's shoulder?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
        oblist = ({ oblist[0] });

    actor("You grasp", oblist, "'s shoulder firmly in a fond gesture " +
        "of comradeship.");
    target(" grasps your shoulder firmly in a fond gesture of " +
        "comradeship.", oblist);
    all2actbb(" grasps", oblist, "'s shoulder firmly in a fond gesture " +
        "of comradeship.");
    return 1;
}

/* Function name: mgreet
 * Description  : Emote for the Militia of Thornlin to greet another
 * Arguments    : string str - as entered by the player
 * Returns      : 1 on success, 0 on failure
 */
int
mgreet(string str)
{
    object *oblist;
    string his_her;

    if (!strlen(str))
    {
        notify_fail("Greet who?\n");
        return 0;
    }

    /* Find if the argument is valid */
    oblist = parse_this(str, "[the] %i");
 
    if (!sizeof(oblist))
    {
        notify_fail("Greet who?\n");
        return 0;
    }
 
    if (sizeof(oblist) > 1)
        oblist = ({ oblist[0] });
 
    his_her = this_player()->query_gender() == G_FEMALE ? "hers" : "his";
    if (this_player()->query_gender() == G_NEUTER)
        his_her = "its";

    actor("You clasp", oblist, "'s hand in both of yours, greeting " +
        oblist[0]->query_objective() + " warmly.");
    target(" clasps your hand in both of " + his_her + ", greeting you " +
        "warmly.", oblist);
    all2actbb(" clasps", oblist, "'s hand in both of " + his_her + 
        ", greeting " + oblist[0]->query_objective() + " warmly.");
    return 1;
}

/* Function name: mlean
 * Description  : Emote for the Militia of Thornlin to lean on their weapon
 * Arguments    : string str - as entered by the player
 * Returns      : 1 always
 */
int
mlean(string str)
{
    object weapon = find_wep(this_player(), 1);
    string wep_short;

    if (!objectp(weapon))
    {
        notify_fail("You don't have an appropriate weapon to lean on.\n");
        return 0;
    }

    wep_short = weapon->short();

    write("You plant your " + wep_short + " into the ground and lean on it " +
        "wearily.\n");
    all(" plants " + this_player()->query_possessive() + " " + wep_short +
        " into the ground and leans on it wearily.");
    return 1;
}

/* Function name: mlick
 * Description  : Emote for the Militia of Thornlin to lick their lips
 * Arguments    : string str - as entered by the player
 * Returns      : 1 on success, 0 on failure
 */
int
mlick(string str)
{
    object *oblist;
    string has_have, he_they;

    if (!strlen(str))
    {
        write("You lick your parched lips, longing for a pint of cool ale.\n");
        all(" licks " + this_player()->query_possessive() + " parched lips, " +
            "longing for a pint of cool ale.");
        return 1;
    }

    /* Find if the argument is valid */
    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Lick your lips at [whom]?\n");
        return 0;
    }

    if (sizeof(oblist) == 1)
    {
        he_they = oblist[0]->query_pronoun();
        has_have = " has ";
    }
    else
    {
        he_they = "they";
        has_have = " have ";
    }

    actor("You lick your lips as you look at", oblist, ", hoping " +
        he_they + has_have + "a cool pint of ale.");
    target(" licks " + this_player()->query_possessive() + " lips as " +
        this_player()->query_pronoun() + " looks at you, hoping you have a " +
        "pint of cool ale.", oblist);
    all2actbb(" licks " + this_player()->query_possessive() + " lips " +
        "as " + this_player()->query_pronoun() + " looks at", oblist, ", " +
        "hoping " + he_they + has_have + "a cool pint " +
        "of ale.");
    return 1;
}

/* Function name: filter_militia
 * Description  : Runs them through a filter
 * Arguments    : object who - who to filter
 * Returns      : 1 if shown, 0 if not
 */
int
filter_militia(object who)
{
    /* Don't list non militia */
    if (!IS_MILITIA(who))
        return 0;

    /* Always list the person doing the list */
    if (who == this_player())
        return 1;

    /* Wizards see juniors invis folks */
    if (this_player()->query_wiz_level())
        return 1;

    /* Invis wizards aren't shown. */
    if (who->query_wiz_level() && who->query_invis())
        return 0;

    /* Jr's are not shown. */
    if (extract(who->query_real_name(), -2) == "jr")
        return 0;

    return 1;
}

/* Function name: mil_online
 * Description  : Gets a list of online militia
 * Returns      : A list of members
 */
object *
mil_online()
{
    object *list = users();
#ifdef STATUE_WHEN_LINKDEAD
#ifdef OWN_STATUE
    list += filter(all_inventory(find_object(OWN_STATUE))-list,
      &not() @ &->query_npc());
#endif OWN_STATUE
#endif STATUE_WHEN_LINKDEAD
    return sort_array(filter(list, filter_militia));
}

/* Function name: mlist
 * Description  : Emote for the Militia of Thornlin to list the members
 *                of the Militia on duty, borrowed from the kender.
 * Arguments    : string str - as entered by the user, unused
 * Returns      : 1 always
 */
int
mlist(string str)
{
    object *members;
    int index, size;

    members = mil_online();
    size = sizeof(members);

    if (!size)
    {
        write("There are no other members in the game.\n");
        return 1;
    }
    else
    {
        for (index = 0; index < size; index++)
        {
            str = members[index]->query_name() + ", the ";
            str += members[index]->query_militia_title();
            if (!interactive(members[index]))
                str = "(off-duty) " + str;
            write(str + "\n");
        }
    }
    return 1;
}

/* Function name: mrub
 * Description  : Emote for the Militia of Thornlin to rub their hands
 *                together
 * Arguments    : string str - as entered by the player
 * Returns      : 1 always
 */
int
mrub(string str)
{
    write("You briskly rub your hands together, trying to warm them.\n");
    all(" briskly rubs " + this_player()->query_possessive() + " hands " +
        "together, trying to warm them.");
    return 1;
}

/* Function name: msay
 * Description  : The local dialect
 * Arguments    : string str - as entered by the player
 */
public int
msay(string str)
{
    int i, skill;
    object *others;

    if (!strlen(str))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (str == "?")
    {
        write("Msay <message>\n");
        return 1;
    }
    if (this_player()->query_skill(SS_LANGUAGE) < 15)
    {
        write("Speaking the local Thornlin dialect is currently beyond " +
            "your ability.\n");
        return 1;
    }

    if (this_player()->query_option(OPT_ECHO))
    {
        write("You use the Thornlin dialect to say: " + 
            str + "\n");
    }
    else
    {
        write("Ok.\n");
    }

    others = all_inventory(environment(this_player())) - ({ this_player() });
    for (i = 0; i < sizeof(others); i++) 
    {
        if (!interactive(others[i]))
        {
            continue;
        }
    
        skill = others[i]->query_skill(SS_LANGUAGE);
        if ((IS_MEMBER(others[i]) && (skill > 19)) || (skill > 60))
        {
            tell_object(others[i], this_player()->query_The_name(others[i]) +
                " speaks in the Thornlin dialect.\n" + 
                capitalize(this_player()->query_pronoun()) + " says: " + str + "\n");
        }
        else
        {
            tell_object(others[i], this_player()->query_The_name(others[i]) +
                " says something in a strange language.\n");
        }
    }
  
    return 1;
}

/* Function name: msigh
 * Description  : Emote for the Militia of Thornlin to sigh in relief
 * Arguments    : string str - as entered by the player
 * Returns      : 1 on success, 0 on failure
 */
int
msigh(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You heave a sigh of relief.\n");
        all(" heaves a sigh of relief.");
        return 1;
    }

    /* Find if the argument is valid */
    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Sigh in relief at [who]?\n");
        return 0;
    }

    actor("You heave a sigh of relief as you look at", oblist, ".");
    target(" heaves a sigh of relief as " + this_player()->query_pronoun() +
        " looks at you.", oblist);
    all2act(" heaves a sigh of relief as " + this_player()->query_pronoun() +
        " looks at", oblist, ".");
    return 1;
}

/* Function name: mwipe
 * Description  : Emote for the Militia of Thornlin to wipe their brow
 * Arguments    : string str - as entered by the player
 * Returns      : 1 always
 */
int
mwipe(string str)
{
    write("You wipe the back of your hand across your forehead.\n");
    allbb(" wipes the back of " + this_player()->query_possessive() +
        " hand across " + this_player()->query_possessive() + " forehead.");
    return 1;
}
