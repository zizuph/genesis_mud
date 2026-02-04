/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * berrybush.c
 *
 * A berry bush. Mortricia 920823
 * Modified by Sorgum 941226
 * Modified by Goldberry February 2001
 */

#include "/d/Terel/include/Terel.h"

inherit STDOBJECT;

#include <ss_types.h>
#include <cmdparse.h>
#include <herb.h>

#define HERB_FILE    TER_HERB + "ramira"

static int berries = 0;

/*
 * Function name: create_object
 * Description:   Default constructor.
 */
public void
create_object()
{
    ::create_object();
    
    set_name("berry-bush");
    add_name("bush");
    set_adj("small");
    set_short("small berry-bush");
    set_long("@@my_long");
    add_prop(OBJ_I_VALUE,  5 + random(5));
    add_prop(OBJ_I_WEIGHT, 79);
    add_prop(OBJ_I_VOLUME, 107);
    add_prop(OBJ_M_NO_GET, 1);
}

/*
 * Function name: my_long
 * Description:   Returns the long description, which depends on how many
 *                berries there are.
 */
public string
my_long()
{
    string s;

    s = "It's a small berry-bush. ";
    if (berries >= 2) {
        s += "There are some red berries on it.";
    } else if (berries == 1) {
        s += "There is one red berry left on it.";
    } else {
        s += "It used to have some berries on it, but you notice " +
            "that someone has picked them.";
    }
    return s + "\n";
}

/*
 * Function name: wither
 * Description:   destroy the object and give a message to the room.
 */
public void
wither()
{
    tell_room(ETO, "The " + short() + " withers rapidly into dust.\n");
    remove_object();
}

/*
 * Function name: do_pick
 * Description:   Handle the pick action
 * Returns:       1/0
 */
public int
do_pick(string str)
{
    object herb;

    NF("Pick what?\n");
    if (!str) return 0;
    if (str != "berry" && str != "berries" &&
        str != "red berry" && str != "red berries") return 0;

    if (berries <= 0) {
        NF("There are no berries left.\n");
        return 0;
    }

    write("You pick a red berry from the "+short()+".\n");
    say(QCTNAME(TP) + " picks a berry from the " + short() + ".\n");

    FIX_EUID;
    herb = clone_object(HERB_FILE);
    if (herb->move(TP)) {
        write("You drop the " + herb->short() + ".\n");
        herb->move(ETP);
    }
    berries--;
    if (berries <= 0)
        set_alarm(7.0, -1.0, wither);
    return 1;
}

/*
 * Function name: init
 * Description:   Add the 'command items' of this object.
 */
public void
init()
{
    ::init();
    add_action(do_pick, "pick");
}


/*
 * Function name: set_berries
 * Description:   set the number of berries on the bush.
 * Arguments:     n - the number of berries
 */
public void
set_berries(int n)
{
    if (n <= 0)
        berries = 1;
    else
        berries = n;
}
