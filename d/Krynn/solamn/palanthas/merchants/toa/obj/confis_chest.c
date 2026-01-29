/* 
 * Chest of confiscated items in the Tower of Arms in Palanthas. It is
 * difficult to pick, and it is trapped.
 *
 * Mortis 9.2014
 */

#pragma strict_types

inherit "/std/receptacle";

#include "../../../local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#define FOUND_CONFIS_TRAP1    "_i_found_confis_trap1"

string my_long();

void
create_container()
{
    set_name("lockbox");
    add_name("box");
    set_adj("iron");
    set_short("iron lockbox");
    set_long("Knocking on the lockbox reveals it is thick and sturdy. Well "
    + "bolted together, as well as to the floor, you're not likely to force "
    + "your way into it.\n" + "@@my_long@@");
    ITEM(({"lock on lockbox", "lockbox lock"}), "The lockbox's lock keyhole "
    + "is slim and hard to peer into.\n" + "@@my_long@@");
    set_key("confis_chest_key");
    add_prop(CONT_I_IN, 1);
    add_prop(CONT_I_RIGID, 0);
    add_prop(CONT_I_TRANSP, 0);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 7500);
    add_prop(OBJ_M_NO_GET, "The chest is iron band-bolted to the floor and "
    + "cannot be taken.\n");
    add_prop(CONT_I_MAX_WEIGHT, 30000);
    add_prop(CONT_I_MAX_VOLUME, 30000);
    add_prop(CONT_I_CLOSED, 1);
    add_prop(CONT_I_LOCK, 1);
}

string
my_long()
{
    if (TP->query_skill(SS_AWARENESS) > (30 + random(50)))
    {
        TP->add_prop(FOUND_CONFIS_TRAP1, 1);
        return "You notice a black wire within the lockbox's keyhole. Some "
        + "keys might hit that wire if they weren't made right.\n";
    }
    return "";
}