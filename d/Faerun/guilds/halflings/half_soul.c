// Call fifijr remove_guild_race

/*
 * half_soul.c
 * Contains emotes for the halflings of faerun,
 * and based on the Orc guild of the Shire
 * Finwe, September 2015
 */

#pragma save_binary
#pragma strict_types

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";

//inherit "/std/leftover";

#include <adverbs.h>
#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <filter_funs.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <options.h>
#include <options.h>
#include <std.h>
#include <stdproperties.h>
#include <time.h>
#include <wa_types.h>
#include "/d/Faerun/defs.h"
#include "halflings.h"

#define SOULDESC(x) (this_player()->add_prop(LIVE_S_SOULEXTRA, x))
#define MORE(x)     this_player()->more(read_file(x,2))

string  *surname_list = ({  "Angler", "Aumble", "Battlestone", 
                            "Blackwater", "Bramblefoot", "Daggersharp",
                            "Dardragon", "Deepstrider", "Hardingdale", 
                            "Hollowpot", "Merrymar", "Oleander", 
                            "Puddle", "Raftmite", "Silverfin", 
                            "Skiprock", "Tanglestrand", "Tricker", 
                            "Willowrush", "Yellowcrane" });

string
get_soul_id()
{
    return GUILD_NAME;
}

int
query_cmd_soul()
{
    return 1;
}

public mapping
query_ability_map()
{
    return ([
                "hthrow"   : HALFGLD_DIR + "hthrow",
            ]);
}

mapping query_cmdlist()
{
// command : routine
    setuid();
    seteuid(getuid());
    return ([
    /******************* COMMANDS *********************/
//    "help"      :   "s_help",
//    "hhelp"     :   "do_help",
    "hsearch"   :   "do_hsearch",
    "hsurname"  :   "do_surname_set",
    "hlist"     :   "list_halflings",

    /******************* EMOTES ***********************/

    "hadjust"   :   "do_hadjust",
    "hbattle"   :   "do_hbattle",
    "hblow"     :   "do_blow",
    "hblush"    :   "do_hblush",
    "hbow"      :   "do_hbow",
    "hbrb"      :   "do_hbrb",
    "hbrb2"     :   "do_hbrb2",
    "hbreath"   :   "do_hbreath",
    "hbreathe"  :   "do_hbreath",
    "hchatter"  :   "do_chatter",
    "hdead"     :   "do_hdead",
    "hdrum"     :   "do_hdrum",
    "hgrin"     :   "do_hgrin",
    "hhear"     :   "do_hhear",
    "hidle"     :   "do_hidle",
    "hjuggle"   :   "do_hjuggle",
    "hlaugh"    :   "do_hlaugh",
    "hlead"     :   "do_hlead",
    "hlick"     :   "do_hlick",
    "hlol"      :   "do_hlol",
    "hnap"      :   "do_hnap",
    "hnibble"   :   "do_hnibble",
    "hnote"     :   "do_hnote",
    "hpick"     :   "do_hpick",
    "hpride"    :   "do_hpride",
    "hrelax"    :   "do_hrelax",
    "hrofl"     :   "do_hrofl",
    "hrumble"   :   "do_hrumble",
    "hrummage"  :   "do_hrummage",
    "hscout"    :   "do_hscout",
    "hsing"     :   "do_hsing",
    "hsit"      :   "do_hsit",
    "hskip"     :   "do_hskip",
    "hsmooth"   :   "do_hsmooth",
    "hsniff"    :   "do_hsniff",
    "hstand"    :   "do_hstand",
    "htoes"     :   "do_htoes",
    "hwander"   :   "do_hwander",
    "hyearn"    :   "do_hyearn"
    ]);
}
/***************************** COMMANDS *********************/
int
s_help()
{
    write("Use the shortcut 'hhelp' to access the help files.\n");
    return 1;
}


int
do_help(string str)
{
    setuid();
    seteuid(getuid());

    switch (str)
    {
        case "standard":
            write(read_file(GUILD_HELP + "standard"));
            return 1;
            break;
        case "emotes":
            write(read_file(GUILD_HELP + "emotes"));
            return 1;
            break;
        case "news":
            write(read_file(GUILD_HELP + "news"));
            return 1;
            break;
        case "titles":
            write(read_file(GUILD_HELP + "titles"));
            return 1;
            break;

        default:
            write(read_file(GUILD_HELP + "standard"));
            return 1;
    }
    return 1;
}

public int
do_surname_set(string str)
{
    string list = "";
    int size = 0;

    foreach(string surname: surname_list)
    {
        size++;
        list += capitalize(surname);
        if (sizeof(surname_list) - size == 1)
            list += ", and ";
        else if (sizeof(surname_list) - size > 1)
               list += ", ";
     }

     if(!str)
     {
         write("You have the following surname options to choose from:\n\n" +
               list+ ".\n\n" +
               "If you don't want a surname, or want to remove it, choose " +
               "'none'.\n");
         return 1;
     }

     if(str == "none")
     {
         write("You no longer have a halfling surname.\n");
         SURNAME_MANAGER->remove_halfling_surname(this_player());
         return 1;
     }

     str = capitalize(str);

     if(member_array(str, surname_list) > -1)
     {
         write("You change your surname to " +str+ "!\n");
         SURNAME_MANAGER->set_halfling_surname(this_player(), str);
         return 1;
     }

     write("That isn't a halfling surname you can change to.\n");
     return 1;
}

int
list_halflings()
{
    string g_name, g_short;
    int i;
    int cnt = 0;
    object *list;
    write("\n\tThe " + GUILD_NAME + ":\n");

    list = users();

    for (i = 0; i < sizeof(list); i++)
    {
        g_name = capitalize(list[i]->query_real_name());
        if (IS_MEMBER(list[i]))
        {
            /* Don't want a jr's or wizards in the list */
            if ((extract(g_name, -2) == "jr") && (!(TP->query_wiz_level())))
            continue;
            if(!list[i]->query_invis())
            {
                if (list[i]->query_wiz_level())
                {
                    g_short = list[i]->query_guild_title_race();
                    write("\t  * " + g_name + " " + g_short);
                }
                else
                {
                    g_short = list[i]->query_guild_title_race();
                    write("\t  - " + g_name + " " + g_short);
                }
                cnt++;
            }

            if (list[i]->query_invis() && TP->query_wiz_level())
            {
                write("\t  @ (" + g_name + ")");
                cnt++;
            }
            else
            {
                if (list[i]->short())
                write("");
            }

            if (!list[i]->query_invis() || TP->query_wiz_level())
                write("\n");
        }
    }
    write("\n\n");

    if(cnt > 1)
    {
        write("There are "+cnt+" halflings awake in the world.\n");
        return 1;
    }
    else
    {
        write("You are the only halfling awake.\n");
        return 1;
    }
}


/**************************** EMOTES ************************/
int
do_hadjust()
{
    write("You give a few quick tugs on your clothes, straightening them " +
        "out and making yourself a little more presentable.\n");
    say(QCTNAME(TP) + " gives " + HIS_HER(TP) + " clothes a few quick " +
        "tugs, straightening them out and making " + HIM_HER(TP) +
        "self a little more presentable.\n");
    return 1;
}

int
do_hbattle()
{
    write("You offer up a quick prayer to Yondalla, asking for her strength " +
        "in battle.\n");
    say(QCTNAME(TP) + " offers up a quick prayer to Yondalla, asking for " +
        "her help in battle.\n");
    return 1;
}

int
do_blow()
{
    write("You grab a stained hanky from your pocket and blow your " +
        "nose loudly.\n");
    say(QCTNAME(TP) + " grabs a stained hanky from " + HIS_HER(TP) +
        " pocket and blows " + HIS_HER(TP) + " nose loudly.\n");
    return 1;
}

int
do_hblush(string str)
{
    string *how;

    how = parse_adverb_with_space(str, "shyly", 0);

    if (!stringp(how[0]))
    {
        write("Your cheeks take on a rosy hue as you blush" + how[1] + ".\n");
        say(QCTNAME(TP) + "'s cheeks take on a rosy hue as " + HE_SHE(TP) +
        " blushes" + how[1] + ".\n");
        return 1;
    }
    else
    {
        write("Your cheeks take on a rosy hue as you blush shyly.\n");
        say(QCTNAME(TP) + "'s cheeks take on a rosy hue as " + HE_SHE(TP) +
        " blushes shyly.\n");
        return 1;
    }
}

int
do_hbow()
{
    write("You drop to one knee and awkwardly bow.\n");
    say(QCTNAME(TP) + " drops to one knee and awkwardly bows.\n");
    return 1;
}

int
do_hbrb()
{
    write("You shout: I will be right back! and dash away for a minute.\n");
    say(QCTNAME(TP) + " shouts: I will be right back! and dashes away for " +
        "a minute.\n");
    return 1;
}

int
do_hbrb2()
{
    write("You shout: I am back!\n");
    say(QCTNAME(TP) + " shouts: I am back!\n");
    return 1;
}

int
do_hbreath()
{
    if (ENV(TP)->query_prop(ROOM_I_INSIDE))
    {
        write("You wrinkle your nose as you breathe the stale, indoor air.\n");
        say(QCTNAME(TP) + " wrinkles " + HIS_HER(TP) + " nose as " +
            HE_SHE(TP) + " breathes the stale indoor air.\n");
        return 1;
    }
    else
    {
        write("You take a deep breath and enjoy the fresh air outside.\n");
        say(QCTNAME(TP) + " takes a deep breath of the outside air.\n");
        return 1;
    }
}

int
do_chatter()
{
    write("You chatter inanely about nothing of importance.\n");
    say(QCTNAME(TP) + " chatters inanely about nothing of importance.\n");
    return 1;
}

int
do_hdead()
{
    write("You bow your head in quiet reverence and respect to the dead, " +
        "and feel the smile of Yondalla.\n");
    say(QCTNAME(TP) + " bows " +HIS_HER(TP) + " in quiet reverence and " +
        "respect for the dead.\n");
    return 1;
}

int
do_hdrum(string str)
{
    string *how;

    how = parse_adverb_with_space(str, "nonchalantly", 0);

    if (!stringp(how[0]))
    {
        write("You drum your fingers" + how[1] + ", waiting for something " +
            "to happen.\n");
        say(QCTNAME(TP) + " drums " + HIS_HER(TP) + " fingers" + how[1] +
            ", waiting for something to happen.\n");
        return 1;
    }
    else
    {
        write("You drum your fingers nonchalantly, waiting for something " +
            "to happen.\n");
        say(QCTNAME(TP) + " drums " + HIS_HER(TP) + " fingers nonchalantly, " +
            "waiting for something to happen.\n");
        return 1;
    }
}

int
do_hgrin(string str)
{
    string *how;

    how = parse_adverb_with_space(str, "widely", 0);

    if (!stringp(how[0]))
    {
        write("You grin" + how[1] + " from ear to ear.\n");
        say(QCTNAME(TP) + " grins" + how[1] + " from ear to ear.\n");
        return 1;
    }
    else
    {
        write("You grin" + how[0] + "from ear to ear.\n");
        say(QCTNAME(TP) + " grins" + how[0] + " from ear to ear.\n", how[1]);
        return 1;
    }
}

int do_hhear()
{
    write("You think you hear something and raise your hand, motioning " +
        "everyone to be silent.\n");
    say(QCTNAME(TP) + " thought  " + HE_SHE(TP) + " heard something, so "
        + HE_SHE(TP) + " raises " + HIS_HER(TP) + " hand, motioning everyone " +
        "to be silent.\n");
    return 1;
}

int
do_hidle()
{
    write("You idly begin to twiddle your fingers, waiting patiently for " +
        "something to happen.\n");
    say(QCTNAME(TP) + " idly begins to twiddle " + HIS_HER(TP) + " fingers, " +
        "waiting patiently for something to happen.\n");
    return 1;
}


int
do_hjuggle()
{
    if (ENV(TP)->query_prop(ROOM_I_INSIDE))
    {
        write("You look around for some rocks to juggle but don't find any " +
            "since you're inside.\n");
        say(QCTNAME(TP) + " looks around, very bored.\n");
        return 1;
    }
    else
    {
        write("You find some large rocks and grab them, then juggle them " +
            "to relieve your boredom.\n");
        say(QCTNAME(TP) + " finds some large rocks and begins to juggle " +
            "them, just to relief " + HIS_HER(TP) + " boredom.\n");
        return 1;
    }
}

int
do_hlaugh()
{
    write("A joyful and boisterous sound erupts from your belly as you " +
        "fall over laughing.\n");
    say("A joyful and boisterous sound erupts from the belly of " +
        QCTNAME(TP) + " as " + HE_SHE(TP) + " falls over laughing.\n");
    return 1;
}

int
do_hlead()
{
    write("With a mighty and inspiring cry, you bravely offer to lead " +
        "everyone to the nearest tavern!.\n");
    say("With a mighty and inspiring cry, " + QCTNAME(TP)  + " bravely " +
        "offers to lead everyone, including you, to the nearest tavern!\n");
    return 1;
}

int
do_hlick()
{
    write("You take a moment to lick your fingers, enjoying the tasty " +
        "remnants of your last meal.\n");
    say(QCTNAME(TP) + " takes a moment to lick " + HIS_HER(TP) +
        " fingers and enjoy the tasty remnants of " + HIS_HER(TP) +
        " last meal.\n");
    return 1;
}

int
do_hlol()
{
    write("You laugh out loud.\n");
    say(QCTNAME(TP) + " laughs out loud.\n");
    return 1;
}

int
do_hnap()
{
    write("Taking advantage of a special ability known only to Halflings, " +
        "you promptly close your eyes and take a quick catnap.\n");
    say("Taking advantage of a special ability known only to Halflings, " +
        QCTNAME(TP) + " promptly closes " + HIS_HER(TP) + " eyes and takes " +
        "a quick catnap.\n");
    return 1;
}

int
do_hnibble()
{
    string str = ONE_OF_LIST(({"a crust of bread",
        "a cookie",
        "an apple",
        "a hard roll",
        "a peanut",
        "a piece of cheese",
        "a heel of bread"}));

    write("You rummage through your pockets and find " + str + ". You " +
        "nibble on it until it's all gone, filling that empty feeling in " +
        "your tummy.\n");
    say(QCTNAME(TP) + " rummages through " + HIS_HER(TP) + " pockets and " +
        "finds " + str + ". " + CAP(HE_SHE(TP)) + " nibbles on it until " +
        "it's all gone.\n");
    return 1;
}

int
do_hnote()
{
    write("You grab your pocketbook and jot down a quick note to yourself.\n");
    say(QCTNAME(TP) + " grabs " + HIM_HER(TP) + " pocketbook and jots " +
        "down a quick note to  " + HIM_HER(TP) + "self.\n");
    return 1;
}

int
do_hpick()
{
    write("Using your fingers, you pick at a bit of food that got stuck " +
        "in your teeth from that last meal.\n");
    say(QCTNAME(TP) + " uses their fingers and picks at a bit of food that " +
        "is stuck in their teeth.\n");
    return 1;
}

int
do_hpride()
{
    write("You puff out your chest and swell with pride.\n");
    say(QCTNAME(TP) + " puffs out " + HIS_HER(TP) + " chest and swells " +
        "with pride.\n");
    return 1;
}

int
do_hrelax()
{
    write("You find a quiet place to step back for a moment and relax.\n");
    say(QCTNAME(TP) + " finds a quiet place to step back for a moment " +
        "and relaxes.\n");
    return 1;
}

int
do_hrofl()
{
    write("You fall down, roll around on the ground, and laugh out loud!\n");
    say(QCTNAME(TP) + " falls down, rolls around on the ground, and laughs " +
        "out loud!\n");
    return 1;
}

int
do_hrumble()
{
    write("Your tummy seems to be telling you--and everyone around you--" +
        "something. It is time to eat!\n");
    say(QCTNAME(TP) + "'s tummy is rumbling pretty loudly. It must be " +
        "time to eat!\n");
    return 1;
}

int
do_hrummage()
{
    write("You rummage through your pockets, looking for something.\n");
    say(QCTNAME(TP) + " rummages through " + HIS_HER(TP) + " pockets, " +
        "looking for something.\n");
    return 1;
}

int
do_hscout()
{
    write("Using keen eyes and sharp ears, you quickly scout out the " +
        "surrounding area.\n");
    say(QCTNAME(TP) + " uses " + HIS_HER(TP) + " keen eyes and sharp ears " +
        "to quickly scout out the surrounding area.\n");
    return 1;
}

int
do_hsing()
{
    write("You sing a joyful little song about family, friends, and " +
        "good times.\n");
    say(QCTNAME(TP) + " sings a joyful little song about family, friends, " +
        "and good times.\n");
    return 1;
}

int
do_hsit()
{
    write("You sit down, cross your feet, and wait.\n");
    say(QCTNAME(TP) + " sits down, crosses " + HIS_HER(TP) +
        " feet, and waits.\n");
    return 1;
}

int
do_hskip()
{
    write("Your feet seem to bounce lightly in the air as you begin to " +
        "skip around, enjoying everything that is good in this world.\n");
    say(QCTNAME(TP) + "'s feet seem to bounce lightly in the air as " +
        HE_SHE(TP) + " begins to skip around, enjoying everything that " +
        "is good in the world.\n");
    return 1;
}

int
do_hsmooth()
{
    write("You quickly run your fingers through your hair, smoothing " +
        "down that unruly mess!\n");
    say(QCTNAME(TP) + " quickly runs " + HIS_HER(TP) + " fingers through " +
        HIS_HER(TP) + " hair, smoothing down that unruly mess!\n");
    return 1;
}

int
do_hsniff()
{
    write("You lift your head up a little as you sniff the air. Is that " +
        "food you smell?\n");
    say(QCTNAME(TP) + " lifts " + HIS_HER(TP) + " head a little as " +
        HE_SHE(TP) + " sniff the air. Is that food " + HE_SHE(TP) +
        " smells?\n");
    return 1;
}

int
do_hstand()
{
    write("You place your arms across your chest and frown, looking " +
        "dangerous and ready for anything.\n");
    say(QCTNAME(TP) + " places " + HIS_HER(TP) + " arms across " +
        HIS_HER(TP) + " chest and frowns. " + CAP(HE_SHE(TP)) + " tries " +
        "to look dangerous and ready for anything.\n");
    return 1;
}

int
do_htoes(string str)
{
    string *how;

    how = parse_adverb_with_space(str, "happily", 0);

    if (!stringp(how[0]))
    {
        write("You wiggle your hairy toes" + how[1] + ".\n");
        say(QCTNAME(TP) + " wiggles " + HIS_HER(TP) + " toes" +
            how[1] + ".\n");
        return 1;
    }
    else
    {
        write("You wiggle your hairy feet" + how[0] + ".\n");
        say(QCTNAME(TP) + " wiggles " + HIS_HER(TP) + " feet" +
            how[0] + ".\n", how[1]);
        return 1;
    }
}

int
do_hwander()
{
    write("You begin to wander around aimlessly.\n");
    say(QCTNAME(TP) + " begins to wander around aimlessly.\n");
    return 1;
}

int
do_hyearn()
{
    write("You yearn for the comforts of your home.\n");
    say(QCTNAME(TP) + " yearns for the comforts of " + HIS_HER(TP) +
        " home.\n");
    return 1;
}

void
check_for_food(int found)
{
    object food_found, paralyze;
    string food_file = ONE_OF_LIST(FOOD_TYPES);

    TP->add_mana(-HMIN_MANA);

    if(found == 1)
    {
        food_found = clone_object(GUILD_FOOD + food_file);
        food_found->move(TP);
        write("You find " + LANG_ADDART(food_found->query_short()) + ".\n");
        say(QCTNAME(TP) + " found something tasty.\n");
    }
    else
    {
        write("But you don't find anything to eat.\n");
        say("But doesn't find what " + HE_SHE(TP) + " is looking for.\n");
    }
}

int
do_hsearch()
{
    setuid();
    seteuid(getuid());

// test time
//    float alarm_time = itof(5);

   float alarm_time = itof(30 + random(15) * 60);

    if (objectp(TP->query_attack()))
    {
        TP->catch_msg("You are unable to search your pockets during combat.\n");
        return 1;
    }

    if(TP->query_mana() <= HMIN_MANA)
    {
        write("You are too mentally exhausted to search for food.\n");
        return 1;
    }

    if(TP->query_food_flag() == 1)
    {
        write("You begin searching your pockets...\n");
        TP->set_food_flag(0);
        set_alarm(itof(5), 0.0, &check_for_food(1));
        TP->set_food_alarm(60.0);
        return 1;
    }
    else
    {
        write("You begin searching your pockets...\n");
        set_alarm(itof(5), 0.0, &check_for_food(0));
        say(QCTNAME(TP)+" pats " + HIM_HER(TP) + "self down looking for " +
            "something.\n");
        return 1;
    }
}
