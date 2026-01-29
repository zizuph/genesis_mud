/* 
 * An dirty pillow used as a key to sleep at the bandits
 * Ruthlessly stolen from the Prancing Pony in the Shire
 * -- Finwe, September 2006
 */
inherit "/std/key";

#include <stdproperties.h>

create_key()
{
    ::create_key();

    set_name("pillow");
    add_name("bandit_inn_key");
    set_pname("pillows");
    set_short("dirty pillow");
    set_pshort("dirty pillows");
    set_adj(({"fluffy", "dirty"}));
    set_long("This is a fluffy, dirty pillow used by bandits in Faerun. " +
        "It is well used, thread bare, and dirty but looks comfortable. " +
        "This pillow allows you to sleep in their sleeping quarters.\n");

    add_prop(OBJ_I_VALUE, 60);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
