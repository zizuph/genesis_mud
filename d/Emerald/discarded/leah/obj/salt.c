/* Salt - needed for a little quest in Emerald. Take it to the cook.        */
/* Coded by Tulix, 27/4/1993 */

inherit "/std/object";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

create_object()
{
    set_name("salt");
    set_pname("pinches of slat");
    set_short("pinch of salt");
    set_pshort("pinches of salt");
    set_long("It is common table salt, as is commonly used in cooking.\n");
    set_adj("pinch of");

    add_prop(OBJ_I_WEIGHT, 2);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_VALUE, 0);
}

void
init()
{
    ::init();
    add_action("do_taste", "taste");
    add_action("do_taste", "lick");
}

int
do_taste(string str)
{
    if (!str)
        return 0;

    if (str=="salt")
    {
        write("You taste the salt. It tastes salty: " +
              "theres a surprise!\n");
        say(QCTNAME(this_player())+" tastes some salt.\n");
        return 1;
    }
    return 0;
}
