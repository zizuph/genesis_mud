/*
 * /d/Gondor/common/lib/worm_find.c
 * 
 * This should be inherited in rooms that one can find
 * and dig up earthworms in. Be sure to add init_worms
 * to the inheriting room's init:
 *
 * public void
 * init()
 * {
 *     ::init();
 *
 *     init_worms();
 * }
 *
 * Worm configuration functions available:
 *
 * set_worms(int)
 *    Set the number of worms found in the room with bare hands.
 *    One will find twice as many worms if a spade is held.
 *    Default: 2
 *
 * set_dig_time(int)
 *    Set the time it takes to dig.
 *    Default: 4 seconds
 *
 * Coded by Gwyneth
 * June 12, 2000
 */

#include <macros.h>
#include <math.h>
#include <ss_types.h>
#include "/d/Gondor/defs.h"

#define WORM "/d/Gondor/common/guild/obj/earthworm.c"

/* Prototypes */
public int worm_dig(string str);
public void find_worms();
public void stop_dig();
nomask void set_worms(int number);
public int query_worm_num();
nomask void set_dig_time(int number);
public int query_dig_time();
public void reset_worms();
public void init_worms();

/* Global variable */
int gWorms = 2;
int gWormsFound = 0;
int gDigTime = 4;
int gDigAlarm;

/*
 * Function name : worm_dig
 * Description   : Checks if one can dig for worms, adds the prop
 *                 to the room with the right time.
 */
public int
worm_dig(string str)
{
    int ident = 94783651;
    object stun;
    string pname = TP->query_real_name();


    if(!str)
    {
        notify_fail("Dig for what?\n");
        return 0;
    }

    str = lower_case(str);

    if (!parse_command(str, ({ }), "[in] [the] [ground] [earth] [here] " +
        "[for] 'worms' / 'earthworms' / 'worm' / 'earthworm'"))
    {
        notify_fail("Dig for what?\n");
        return 0;
    }

    /* Fails if the player's awareness skill is less than a random
       number between 30 and 40. Trying over again multiple times
       will always give the same random number for the same person. */
    if ((TP->query_skill(SS_AWARENESS)) < (30 +
        NAME_TO_RANDOM(pname, ident, 11)))
    {
        notify_fail("You look all around, but can't seem to find " +
            "any worms.\n");
        return 0;
    }

    if (gWormsFound >= gWorms)
    {
        notify_fail("The earth seems freshly disturbed, and you " +
            "can find no worms.\n");
        return 0;
    }

    write("You start to dig around for worms.\n");
    tell_room(TO, QCTNAME(TP) + " starts to dig in the ground.\n", TP);

    /* Alarm must be called before paralyze is removed, or the stop
       function will be called, removing this alarm. */
    gDigAlarm = set_alarm(itof(query_dig_time()) - 0.1, 0.0, &find_worms());

    stun = clone_object("/std/paralyze");
    stun->set_stop_object(TO);
    stun->set_stop_fun("stop_dig");
    stun->set_stop_verb("stop");
    stun->set_remove_time(query_dig_time());
    stun->set_fail_message("You are busy digging for worms. Maybe " +
        "you should 'stop' before trying anything else.\n");
    stun->set_stop_message("You stop digging for worms.\n");
    stun->move(TP, 1);

    return 1;
}

public void
find_worms()
{
    /* Spade must be held for an extra worm to be found. */
    if((present("regrowth_spade", TP))->query_held())
    {
        write("You dig deeply in the soil " +
            "with your small spade and find some nice juicy worms.\n");

        /* Spades give one more worm. */
        clone_object(WORM)->move(TP);
    }
    else
    {
        write("You dig around in the soil with " +
            "your bare hands and find a nice juicy worm.\n");
    }

    clone_object(WORM)->move(TP);

    tell_room(TO, QCTNAME(TP) + " finds something in the ground.\n", TP);

    gWormsFound++;    
}

/* Function name : stop_dig
 * Description   : removes the alarms when digging is stopped
 */
public void
stop_dig()
{
    remove_alarm(gDigAlarm);
}

/*
 * Function name : set_worms
 * Description   : Use this to set the number of worms found per
 *                 room with bare hands.
 * Arguments     : int worm_num - the number of worms to find
 */
nomask void
set_worms(int worm_num)
{
    gWorms = worm_num;    
}

/*
 * Function name : query_worm_num
 * Description   : Returns the number of worms found in the room
 *                 with bare hands.
 * Returns       : The number of worms found in the room.
 */
public int
query_worm_num()
{
    return gWorms;
}

/*
 * Function name : set_dig_time
 * Description   : Use this to set the digging time to find worms
 * Arguments     : int dig_time - time it takes to dig
 */
nomask void
set_dig_time(int dig_time)
{
    gDigTime = dig_time;    
}

/*
 * Function name : query_dig_time
 * Description   : Returns the digging time.
 * Returns       : The time it takes to dig for worms.
 */
public int
query_dig_time()
{
    return gDigTime;
}

/* Function name : reset_worms
 * Description   : Refreshes the worms in the room
 */
public void
reset_worms()
{
    gWormsFound = 0;
}

/*
 * Function name : init_worms
 * Description   : Add commands to livings in the room.
 */
public void
init_worms()
{
    add_action(worm_dig, "dig");

    set_alarm(2400.0, 2400.0, &reset_worms());
}
