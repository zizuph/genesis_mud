/*
 *
 * A player has this object when mounted on a steed.
 *
  ChangeLog:
  May 17, 2004 Palmer - 
    removed second "buy ticket" from hboard due to global
    changes in ship captains
 */
 
 
inherit "/std/object";
inherit "/lib/commands";

#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <adverbs.h>
#include "/d/Shire/sys/defs.h"
#include "../bree_stables.h"

object steed;
object rider;


/* Function Prototypes */
public int hhalt();
public int hsnort();
public int hhelp();
public int hboard();
public int htboard();
public int hscrape(string str);
public int hnuzzle(string str);
public int hgallop(string str);
public int hdrink(string str);
public int hpack();
public int no_stealth(string str);
public int no_dcall(string str);
public object query_steed();

void create_object()
{
    set_name("__rider_object");
    set_no_show();
    add_prop(OBJ_I_NO_DROP, 1);
}



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
    write("You can't be stealthy while riding your steed.\n");
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

/*
Shows status of horse's soak/stuff/fatigue

*/
public int
hglance()
{
    int fatigue, soaked, stuffed;
    object rider, steed;
    string thirst="", hunger="", tired="";

    steed = query_steed();
    rider = steed->query_driver();
    soaked = steed->query_soaked();
    stuffed = steed->query_stuffed();
    fatigue = steed->query_fatigue();

    if (soaked > 24000)
        thirst = "Your steed is not thirsty.";
    if (soaked <= 24000 && soaked > 20000)
        thirst = "Your steed is thirsty.";
    if (soaked <= 20000 && soaked > 10000)
        thirst = "Your steed is very thirsty.";
    if (soaked <= 10000)
        thirst = "Your steed is extremely thirsty.";

    if (stuffed > 6000)
        hunger = "Your steed is not hungry.";
    if (stuffed <= 6000 && stuffed > 2000)
        hunger = "Your steed is hungry.";
    if (stuffed <= 2000 && stuffed > 1000)
        hunger = "Your steed is very hungry.";
    if (stuffed <= 1000)
        hunger = "Your steed is extremely hungry.";

    if (fatigue > 275)
        tired = "Your steed is not tired.";
    if (fatigue <= 275 && fatigue > 225)
        tired = "Your steed is tired.";
    if (fatigue <= 225 && fatigue > 100)
        tired = "Your steed is very tired.";
    if (fatigue <= 100)
        tired = "Your steed is extremely tired.";

    write(thirst + "\n");
    write(hunger + "\n");
    write(tired + "\n");
    return 1;
}


int
hboard()
{
    object rider;
    object steed = query_steed();
    rider = steed->query_driver();

    if (!present("ship", environment(rider)))    
    {
        notify_fail("There is no ship present!\n");
	return 0;
    }    

    rider->command("buy ticket");
    // rider->command("buy ticket");
    rider->command("board");
    return 1;
}



int
htboard()
{
    object rider, steed, *team, coin, ticket;
    int i;
    
    steed = query_steed();
    rider = steed->query_driver();

    if (!present("ship", environment(rider)))    
    {
        notify_fail("There is no ship present!\n");
	return 0;
    }    

    team = rider->query_team_others();
    /*
    if (!sizeof(team))
    {
        hboard();
        return 1;
    }
    */
    coin = present("gold coin", rider);
    if (!coin)
    {
        coin = present("platinum coin", rider);
        if (!coin)
        {

            notify_fail("You haven't got enough money to pay the captain!\n");
	    return 0;
        }
    }

    for (i = 0; i < sizeof(team); i++)
    {
        if (present(team[i],environment(rider)))
        {
            rider->command("buy ticket");
            ticket = present("ticket", rider);
            ticket->move(team[i]);
	    // Buy second ticket for steed, if mounted
	    if (present("__rider_object", team[i]))
	    {
                rider->command("buy ticket");
                ticket = present("ticket", rider);
                ticket->move(team[i]);
            }
	    	    
            team[i]->command("board");
        }
    }
    
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
            notify_fail("Your steed is unable to drink here.\n");
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



/* Function name: set_steed
 * Description:   Set the steed for which this rider object is meant.
 * Arguments:     object steed
 */
public void set_steed(object o)
{
    steed = o;
}

/* Function name: query_steed
 * Description:   Query the steed for which this rider object is meant.
 * Returns:       object steed
 */
public object query_steed()
{
    return steed;
}

/* Function name: set_rider
 * Description:   Set the rider for which this rider object is meant.
 * Arguments:     object rider
 */
public void set_rider(object o)
{
    rider = o;
}

/* Function name: query_rider
 * Description:   Query the rider for which this rider object is meant.
 * Returns:       object rider
 */
public object query_rider()
{
    return rider;
}

/* Action. See steed.c#dismount */
public int dismount(string s)
{
    return steed->dismount(s);
}

/* Action. See steed.c#do_auto_mount */
public int auto_mount(string s)
{
    return steed->do_auto_mount(s);
}

/* Action. See steed.c#auto_dismount */
public int auto_dismount(string s)
{
    return steed->do_auto_dismount(s);
}

/* Adds the actions. */
public void init()
{
    add_action(dismount, "dismount");
    add_action(auto_mount, "automount");
    add_action(auto_dismount, "autodismount");
    add_action(hboard, "hboard");
    add_action(htboard, "htboard");
    add_action(hhalt, "hhalt");
    add_action(hsnort, "hsnort");
    add_action(hhelp, "hhelp");
    add_action(hscrape, "hscrape");
    add_action(hnuzzle, "hnuzzle");
    add_action(hgallop, "hgallop");
    add_action(hdrink, "hdrink");
    add_action(hpack, "hpack");
    add_action(hglance, "hglance");

    // Mask functions people shouldn't use while leading steed
    // add_action(no_dcall, "dcall");
    add_action(no_stealth, "stealth"); // Rangers
    add_action(no_stealth, "rstealth"); // Rangers
    add_action(no_stealth, "tiptoe"); // Secret Society

    ::init();
}
