/*

* Imladris leader object
* By Palmer
* December, 2002
*/

inherit "/d/Genesis/steed/new/leader_object.c";
inherit "/lib/commands";

#include <macros.h>
#include "/d/Shire/sys/defs.h"
#include "imladris_stables.h"

/* Function Prototypes */
public int hhelp();
public int hhome();

public int hhalt();
public int hpack();
public int hdrink(string str);
public int hboard();
public int hsnort();
public int hscrape(string str);
public int hnuzzle(string str);
public int hgallop(string str);
public int no_stealth(string str);
public int no_dcall(string str);

void
enter_env(object ob, object from)
{
    ::enter_env(ob, from);
    if (!living(ob))
    {
        return;
    }

    add_action(hhalt, "hhalt");
    add_action(hsnort, "hsnort");
    add_action(hhelp, "hhelp");
    add_action(hdrink, "hdrink");
    add_action(hhome, "hhome");
    add_action(hscrape, "hscrape");
    add_action(hnuzzle, "hnuzzle");
    add_action(hgallop, "hgallop");
    add_action(hboard, "hboard");

    /* Saddlebag: */
    add_action(hpack, "hpack"); // Show contents of pack to leader

    // Mask functions people shouldn't use while leading steed
   // add_action(no_dcall, "dcall");
    add_action(no_stealth, "stealth");
    add_action(no_stealth, "rstealth");
}


int
no_dcall(string str)
{
    write("Your dog doesn't respond, as its a bit afraid of your horse.\n");
    write("Unlead your horse and try again.\n");
    write("We're working on this problem, please use the dogs as messengers " +
          "only while you have your horse, don't let the dog follow.\n");
    return 1;
}

/*
Name: no_stealth(string str)

Desc: We over-ride Ranger's ability to stealth on/off
because of bug in base steed code that makes the
steed sneak if the leader or Rider is.

Args: string on/off or none
Rets: int 1

*/

int
no_stealth(string str)
{
    write("You can't be stealthy when leading your steed.\n");
    return 1;
}

/*

Name: hboard()
Desc: Warns player they must be mounted to use hboard.
Args: None
Returns: int 1
*/

int
hboard()
{
    write("You must be mounted, not leading your horse, to board a ship.");
    return 1;
}

/*

Name: hscrape()
Desc:  Emote showing horse scraping ground, with optional adverb
Returns: int 1 if successful, 0 if fail
*/

int
hscrape(string str)
{
    object steed = TO->query_steed();
    string *how;
    how = parse_adverb_with_space(str, "impatiently", 0);

    tell_room(ENV(TP), "The " + steed->query_short() + how[1] + " scrapes its " +
              "hooves on the ground.\n");
    return 1;
}


/*

Name: hnuzzle()
Desc: Emote to make steed nuzzle someone with optional adverb
Returns: int 1 if successful, 0 if fail
*/

int
hnuzzle(string str)
{
    object steed = TO->query_steed();
    string *how;
    object *oblist;

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
    "for a treat.\n");

    tell_room(ENV(TO), "The " + steed->query_short() + " nuzzles " + QTNAME(oblist[0]) +
               how[1] + ", hoping for a treat.\n", 0);
    return 1;
}


/*

Name: hgallop()
Desc:  Returns gallop / ride message
Returns: string

*/

int hgallop(string str)
{
    return query_steed()->hgallop(str);
}



int
hpack()
{
    object saddlebag, *contents;
    object steed = TO->query_steed();
    saddlebag = present("saddlebag", steed);
    if (saddlebag == 0)
    {
        write("You'll need a saddlebag draped over your steed first.\n");
        return 1;
    }
    contents = all_inventory(saddlebag);
    saddlebag->describe_contents(steed->query_leader(), contents);
    return 1;
}



int
hhalt()
{
    object steed = TO->query_steed();
    write("You bring your " + steed->query_short() + " to a halt.\n");
    say(QCTNAME(TP) + " brings the " + steed->query_short() + " to a halt.\n");
    return 1;
}

int
hsnort()
{
    object steed = TO->query_steed();
    tell_room(ENV(TP), "The " + steed->query_short() + " snorts loudly.\n");
    return 1;
}

int
hhome()
{
    object saddlebag;
    object steed = TO->query_steed();
    saddlebag = present("saddlebag", steed);
    if (saddlebag)
    {
        write("You'd better remove your saddlebag from your horse first.\n");
        return 1;
    }

    write("Whispering quietly in your " + steed->short() + "'s ear, you send " +
           HIM_HER(steed) + " home to Imladris.\n");
    say(QTNAME(TP) + " whispers something in the " + steed->short() + "'s ear.\n");
    tell_room(ENV(TP), "The " + steed->short() + " neighs " +
                       "in obedience and makes off at full gallop. \n");
    steed->remove_object();


    return 1;
}


int
hdrink(string str)
{
    string *words;
    int soaked, max_soaked;
    object steed = TO->query_steed();

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
        max_soaked = steed->max_drink();
        soaked = steed->query_soaked();
        if (max_soaked - soaked < 2000)
        {
            notify_fail("Your horse can't drink any more.\n");
            return 0;
        }
        steed->command("drink " + str);
        if (steed->query_soaked() == steed->drink_max())
        {
            notify_fail("Your horse can't drink any more.\n");
            return 0;
        }
        return 1;
    }

    notify_fail("Make the horse drink from what?\n");
    return 0;
}



int
hhelp()
{
    string txt;

    txt = read_file("/d/Shire/rivendell/steeds/hhelp.txt");
    TP->more(txt);
    return 1;
}
