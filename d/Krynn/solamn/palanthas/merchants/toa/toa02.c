/* Mortis 9.2014
 */

#include "../../local.h"
#include CLOCKH

inherit TOA_ROOMBASE;

int wandering_guard;
object tdoor, wguard;

void defend_door(object picker);

string
query_to_jail()
{
    return "west";
}

void
reset_palan_room()
{
    wandering_guard = 0;
}

void
create_palan_room()
{
    SHORT("The central room on the ground floor of the Tower of Arms");
    LONG("You stand in a great chamber atop a massive stairway descending "
    + "west. The chink of armour and clump of bootsteps echo from the "
    + "corridors. An iron door is recessed into the east wall.\n");

    ITEM(({"stair", "stairs", "flight", "flights", "flight of stairs",
           "stairway"}), "A massive stairway descends west. The steps "
    + "are worn but still nearly perfect and smooth. They have recently "
    + "been polished and gleam beautifully.\n");
    ITEM(({"corridor", "corridors"}), "Marble corridors extend from here.\n");

    EXIT(TOA + "toa04", "north", 0, 0);
    EXIT(TOA + "toa08", "south", 0, 0);
    EXIT(TOA + "toa01", "west", 0, 0);

    tdoor = clone_object(TOA + "doors/toa_lieutenant_door1");
    tdoor->move(TO);

    reset_palan_room();
}

void
auto_door()
{
    tdoor->reset_door();
}

void
defend_door(object picker)
{
    string warn_msg;

    if (wandering_guard > 0)
    {
        return;
    }

    if (random(10) == 1)
    {
        wguard = clone_object(TOA + "living/toa_guard");
        wguard->move(TO);
        picker->catch_msg("A wandering guard marches in and catches you in "
        + "the act of breaking and entering.\n");
        wguard->command("asay angr Hey, what are you doing!?!");
        wguard->attack_func(picker);
        wandering_guard++;
    }
    else
    {
        warn_msg = one_of_list(({"Bootsteps echo down the corridor nearby.\n",
        "Did you hear bootsteps coming?\n", "Armour clinks and janks nearby. "
        + "Someone may be coming.\n"}));

        TP->catch_msg(warn_msg);
    }
}