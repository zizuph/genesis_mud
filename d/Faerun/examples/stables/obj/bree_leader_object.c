/*

* Bree leader object
* By Palmer
* Date Dec 2002
*/

inherit "/d/Genesis/steed/new/leader_object.c";
inherit "/lib/commands";

#include <macros.h>
#include "/d/Shire/sys/defs.h"
#include "../bree_stables.h"

/* Function Prototypes */
int hhalt();
int hsnort();
int hhome();
int hhelp();
int hdrink(string str);
int hpack();
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
    add_action(hhome, "hhome");
    add_action(hhelp, "hhelp");
    add_action(hdrink, "hdrink");
    add_action(hpack, "hpack");

    // Mask functions people shouldn't use while leading steed
    // add_action(no_dcall, "dcall");
    add_action(no_stealth, "stealth");
    add_action(no_stealth, "rstealth");
}


int
no_dcall(string str)
{
    write("Your dog doesn't respond, as its a bit afraid of your steed.\n");
    write("Unlead your steed and try again.\n");
    write("We're working on this problem, please use the dogs as messengers " +
          "only while you have your steed; don't let the dog follow.\n");
    return 1;
}

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
    saddlebag->describe_contents(steed->query_leader(), contents);
    return 1;
}



void
destruct_horse()
{
    object steed = TO->query_steed();
    steed->remove_object();
}

/*

What was I thinking?

int
hname(string str)
{
    Steed = query_steed();
    Steed->add_name(str);
    write("You whisper in your " + Steed->query_short() + "'s ear and tell " +
    HIM_HER(Steed) + " " + HIS_HER(Steed) +  " new name is '" + capitalize(str) + "'.\n");
     say(QCTNAME(TP) + " whispers quietly in the " + Steed->query_short() + "'s ear.\n");
    return 1;
}
*/

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
hhome()
{
    string player;
    object stable_master, room, saddlebag;
    object steed = query_steed();
    saddlebag = present("saddlebag", steed);
    if (saddlebag)
    {
        write("Whoa there! You'd better remove your saddlebag from your steed first.\n");
        return 1;
    }

    room = find_object(BREE_STABLES_DIR + "east_yard");
    player = TP->query_real_name();
    stable_master = present("keleren", room);
    stable_master->clear_list(player);

    write("Whispering quietly in your " + steed->query_short() + "'s ear, you send it " +
          "back home to the stables in Bree.\n");
    say(QTNAME(TP) + " whispers something in the " + steed->query_short() + "'s ear.\n");
    set_alarm(2.0, 0.0, &tell_room(ENV(TP), "The " + steed->query_short() + " neighs " +
              "in obedience and makes off at full gallop, heading " +
              "towards Bree. \n"));
    set_alarm(2.2, 0.0, &destruct_horse());

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

        max_soaked = steed->max_drink();
        soaked = steed->query_soaked();
        if (max_soaked - soaked < 2000)
        {
            notify_fail("Your steed can't drink any more.\n");
            return 0;
        }
        steed->command("drink " + str);
        if (steed->query_soaked() == steed->drink_max())
        {
            notify_fail("Your steed can't drink any more.\n");
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
    write(HHELP_LEADER_MESSAGE);	/* defined in bree_stables.h */
    return 1;
}
