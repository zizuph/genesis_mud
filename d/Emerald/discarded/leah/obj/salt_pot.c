/* Its a salt pot. You can get salt from it, funnily enough. */
/* Coded by Tulix, 24/4/93 */

inherit "/std/container";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

void
create_container()
{
    object salt;
    int i;

    seteuid(getuid());
    set_name("pot");
    set_short("salt pot");
    set_pshort("salt pots");
    set_adj("salt");
    add_adj("wooden");
    set_long("Its a small wooden salt pot, that belongs on a dining table.\n");

    add_prop(CONT_I_WEIGHT, 20); /* weights 20g */
    add_prop(CONT_I_MAX_WEIGHT, 30); /* holds 10g of salt max */
    add_prop(CONT_I_VOLUME, 30); /* takes up 30ml */
    add_prop(CONT_I_MAX_VOLUME, 50); /* can take 20ml of salt max */

    if (IS_CLONE)
    {
        salt=clone_object("/d/Emerald/obj/village/salt.c");
        salt->move(this_object());
    }
}
