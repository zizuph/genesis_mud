
/*

THIS FILE IS OBSOLETE
Bree steeds now use ~shire/bree/rooms/town/stable/obj/rider_object.c

*/

/*
 * /d/Shire/bree/rooms/town/stable/obj/rider_object.c
 *
 * This object is carried by riders. It allows them
 * to do emotes, mount, dismount.
 *
 * By, Palmer
 * Date December 2002
 *
 * Changes:
 * 09/04/2003 - Disallowed automount while in teams due to
 * bug in /d/Genesis/steed/new/steed.c
 */

// inherit "/d/Genesis/steed/new/rider_object";
inherit "/d/Shire/bree/rooms/town/stable/obj/rider_object";
inherit "/lib/commands";

#include <macros.h>
#include <filter_funs.h>
#include <adverbs.h>
#include "/d/Shire/sys/defs.h"
#include "../bree_stables.h"

/* Function Prototypes */
public int hhalt();
public int hsnort();
public int hhelp();
public int hboard();
public int hscrape(string str);
public int hnuzzle(string str);
public int hgallop(string str);
public int hdrink(string str);
public int hpack();
public int no_stealth(string str);
public int no_dcall(string str);

/*
int
autodismount()
{
    write("Sorry, this is disabled for today while a bug is being fixed.\n");

    return 1;
}
*/


int
do_automount(string s)
{
    object steed = query_steed();
/*
    if (sizeof(this_player()->query_team_others()) !=0 )
    {
        notify_fail("Automount can not be enabled when you lead a team.\n");
        return 0;
    }
*/
    steed->do_auto_mount(s);
    return 1;
}

/*
void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!living(to))
    {
        return;
    }

    // add_action(do_automount, "automount");
    // add_action(autodismount, "autodismount");
    add_action(hboard, "hboard");
    add_action(hhalt, "hhalt");
    add_action(hsnort, "hsnort");
    add_action(hhelp, "hhelp");
    add_action(hscrape, "hscrape");
    add_action(hnuzzle, "hnuzzle");
    add_action(hgallop, "hgallop");
    add_action(hdrink, "hdrink");
    add_action(hpack, "hpack");

    // Mask functions people shouldn't use while leading steed
    // add_action(no_dcall, "dcall");
    add_action(no_stealth, "stealth"); // Rangers
    add_action(no_stealth, "tiptoe"); // Secret Society

}

*/

int
no_dcall(string str)
{
    write("Your dog doesn't respond, as its a bit afraid of steeds.\n");
    write("Dismount your steed and try again.\n");
    write("We're working on this problem, please use the dogs as messengers " +
          "only while you have your steed, don't let the dog follow.\n");

    return 1;
}


/* no_stealth(string str)

We over-rider Ranger's ability to stealth on/off
because of bug in base steed code that makes the
steed sneak if the leader or Rider is.

Note: We need to find out how Secret Society,
Thieves and Tricksters sneak.

Arguments: string on/off or none
Returns  : int 1

*/
int
no_stealth(string str)
{
    write("You can't be stealthy when leading your steed.\n");
    return 1;
}



int
hpack()
{
    object saddlebag, *contents;
    object steed = query_steed();
    saddlebag = present("saddlebag", steed);
    if (saddlebag == 0)
    {
        write("You'll need a saddlebag draped over your steed first.\n");
        return 1;
    }
    contents = all_inventory(saddlebag);
    saddlebag->describe_contents(steed->query_driver(), contents);
    return 1;
}

int
hboard()
{
    object rider;
    object steed = query_steed();
    rider = steed->query_driver();
    rider->command("buy ticket");
    rider->command("buy ticket");
    rider->command("board");
    return 1;
}



int
hhalt()
{
    object steed = query_steed();
    write("You bring your " + steed->query_short() + " to a halt.\n");
    say(QCTNAME(TP) + " brings the " + steed->query_short() + " to a halt.\n");
    return 1;
}

int
hsnort()
{
    object steed = query_steed();
    tell_room(ENV(TP), "The " + steed->query_short() + " snorts loudly.\n");
    return 1;
}

int
hhelp()
{
    write(HHELP_RIDER_MESSAGE);        /* defined in bree_stables.h */
    return 1;
}

int
hdrink(string str)
{
    string *words;
    int soaked, max_soaked;
    object steed = query_steed();

    if (!stringp(str))  // They typed 'hdrink' only
    {
        notify_fail("Make the horse drink from what?\n");
        return 0;
    }

    words = explode(str, " ");
    if (sizeof(words) < 2) // They must try at least "hdrink from something" minimum
    {
        notify_fail("Make the horse drink from what?\n");
        return 0;
    }

    if (words[0] == "from" || words[0] == "water") //hdrink water from foo || hdrink from foo
    {
        soaked = steed->query_soaked();
        if (soaked >= 24000)
        {
            notify_fail("Your steed can't drink any more.\n");
            return 0;
        }

        if (steed->command("drink " + str))
             return 1;
        else
        {
            notify_fail("Your steed doesn't need any water.\n");
            return 0;
        }
    }

    notify_fail("Make the horse drink from what?\n");
    return 0;
}

int
hscrape(string str)
{
    string *how;
    object steed = query_steed();
    how = parse_adverb_with_space(str, "impatiently", 0);

    tell_room(ENV(TP), "The " + steed->query_short() + how[1] + " scrapes its " +
              "hooves on the ground.\n");
    return 1;
}

int
hnuzzle(string str)
{
    string *how;
    object *oblist;
    object steed = query_steed();

    how = parse_adverb_with_space(str, "playfully", 0);

    if (!stringp(how[0]))
    {
        notify_fail("hnuzzle [how] at whom?\n");
        return 0;
    }
    oblist = parse_this(how[0], "[at] %l");
    if (!sizeof(oblist))
    {
        notify_fail("hnuzzle [how] at whom?\n");
        return 0;
    }
    if (sizeof(oblist) > 1)
    {
        notify_fail("You can only do this at one person at a time.\n");
        return 0;
    }
    oblist[0]->catch_tell("The " + steed->query_short() + " nuzzles you" + how[1] + ", hoping " +
    "for a lump of sugar or an apple.\n");

    tell_room(ENV(TO), "The " + steed->query_short() + " nuzzles " + QTNAME(oblist[0]) +
               how[1] + ", hoping for a lump of sugar or an apple.\n", 0);
    return 1;
}


int hgallop(string str)
{
    return query_steed()->hgallop(str);
}
