/* Ashlar, 21 Aug 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <macros.h>

inherit SEWER_BASE;

#define BELOW_HUT   NSEWER + "below_hut"

void
reset_neraka_room()
{
}

string
long_descr()
{
    return "This is a tunnel in the sewers beneath Neraka. " +
    "The tunnel is wide enough for four men to walk abreast, and it " +
    "is just as high. " + water_desc() + "The tunnel leads west, " +
    "and in the north wall there is a spillway chute is emptying a " +
    "trickle of water into the tunnel.\n";
}

void
create_neraka_room()
{
    set_short("in the sewers");
    set_long("@@long_descr");

    add_lsewer_items();
    add_item(({"chute","spillway","spillway chute"}),
    "The chute slants upwards, and a trickle of water runs " +
    "through it, emptying out in the tunnel.\n");
    add_item(({"trickle","trickle of water"}),
    "It is just a small trickle, but it seems marginally less dirty " +
    "than the water that is already collected at the bottom of the " +
    "tunnel.\n");
    add_cmd_item(({"chute","spillway","spillway chute","through chute",
    "through spillway","through spillway chute"}),
    ({"enter","crawl","climb"}),
    ({"@@enter_chute","@@enter_chute","@@enter_chute"}));
    add_item("north wall","The north wall has a spillway chute set " +
    "about knee-height above the floor.\n");

    add_lsewer_herbs();
    remove_prop(ROOM_I_LIGHT);

    reset_room();

    add_exit(NSEWER + "s6", "west");
}

string
enter_chute()
{
    object room;
    
    if(LOAD_ERR(BELOW_HUT))
    {
        write("Could not load file <"+BELOW_HUT+">!\nPlease make " +
        "a bugreport of this!\n");
        return "A wrongness in time and space makes you unable to " +
        "enter the chute.\n";
    }
    room = find_object(BELOW_HUT);
    if (sizeof(FILTER_LIVE(all_inventory(room))))
        return "You peer into the spillway chute and you think you see " +
        "someone else in there. Since the chute is very tight you decide " +
        "not to enter it.\n";

    write("You enter the spillway chute. It is slippery, but you " +
    "manage to move forward anyway. The chute is longer than you expected, " +
    "and you crawl for quite some time until you arrive at a place where " +
    "light shines down from a grating above.\n");
    if (TP->move_living("M",room))
    {
        return "For some reason, you are unable to enter the chute. " +
        "Please leave a bugreport of this.\n";
    }
    tell_room(TO, QCTNAME(TP) + " enters the spillway chute.\n", TP);
    return "";
}
