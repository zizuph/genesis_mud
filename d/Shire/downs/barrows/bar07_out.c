/* A barrow passage in the downs, leading out
 * Based on Dondon's downs
 * -- Finwe, December 2001
 */

#include "/d/Shire/sys/defs.h"
#include "../local.h"
#include <ss_types.h>

inherit BAR_BASE;


void
create_barrow_room()
{
    set_short("A dark shaft beneath the Barrows");
    set_long("You stand in a tall earthen shaft beneath a barrow. " +
        "It rises upwards with the top hidden in darkness. An iron " +
        "ladder is attached to a wall and leads up the shaft. " +
        "There is a hole in the ceiling where you fell through.\n");

    set_add_shaft_functions();


    reset_shire_room();
    add_prop(ROOM_I_LIGHT, 0);
    add_exit(BAR_DIR + "bar07_05", "up","@@climb_out@@");
}

void
init()
{   
    ::init();
    add_action("climb_ladder", "climb");

}

void reset_shire_room()
{
}

string climb_ladder(string str)
{
    if (str =="ladder" || str == "iron ladder")
    {
        write("You climb the ladder and reach the top of the shaft. " +
            "You start clawing at the dirt and within a few minutes, " +
            "the top collapses and you hoist yourself out of the shaft.\n");
        say(QCTNAME(TP)+ " climbs the ladder and disappears into the darkness.\n");
        TP->move_living("M", "/d/Shire/downs/road/road18",1);
// what people at the road will see when players come out of the downs.
        say("The ground suddenly collapses and "+QCTNAME(TP)+
            " climbs out of the barrow. The hole suddenly collapses " +
            "in on itself.\n");
        return "";
    }
    NF("Climb what, the ladder?\n");
}