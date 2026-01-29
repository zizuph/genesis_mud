/* Key to the monkey's cage. ~solace/puzzle/objects/cage_key */

inherit "/std/key";

#include "../defs.h"
#include "/sys/language.h"
#include "/sys/stdproperties.h"

void create_key()
{
    set_name("key");
    set_adj("small");
    add_adj("brass");
    set_long("This is a small brass key with the number "+LANG_WNUM(CAGE_KEY)+
        " stamped into it.\n");

    set_key(CAGE_KEY);

    add_prop(OBJ_I_VALUE, 10);

    add_prop(OBJ_I_WEIGHT, 500); // Half a kilo.
    add_prop(OBJ_I_VOLUME, 100); // 10th of a litre.

    add_prop(OBJ_S_WIZINFO, "This key opens the monkey's cage.\n");
}
