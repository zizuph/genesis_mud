/* This key is needed for the Heraldry quest, to open the door in the lair. */
/* Coded by Tulix, 20/4/1993 */

inherit "/std/key";
#include "/sys/stdproperties.h"

create_key()

{
    set_adj("worn");
    add_adj("iron");
    set_long("It is a worn iron key, that has seen a lot of use.\n");
    add_prop(OBJ_I_WEIGHT, 50); /* weighs 50g */
    add_prop(OBJ_I_VOLUME, 15); /* vol 15ml   */
    add_prop(OBJ_I_VALUE, 50);  /* value 50cc */
}
