inherit "/std/receptacle";

#include <stdproperties.h>

public void
create_receptacle()
{
    set_name("footlocker");
    set_adj("long");
    add_adj("wooden");
    set_pshort("long wooden footlockers");

    set_long("This long wooden footlocker sits at the foot of the " +
        "bed. A steel lock keeps those who have no business opening " +
        "the locker from prying into the captain's belongings.\n");

    add_prop(CONT_I_WEIGHT, 2500);
    add_prop(CONT_I_MAX_WEIGHT, 10000);
    add_prop(CONT_I_VOLUME, 1000);
    add_prop(CONT_I_MAX_VOLUME, 3000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_CLOSED, 1);
    add_prop(CONT_I_LOCK, 1);
    add_prop(OBJ_M_NO_GET, 1);

    set_pick(75);
    /* Set the id of the key for the chest */
    set_key("FOOTLOCKER_KEY_ID");
}
