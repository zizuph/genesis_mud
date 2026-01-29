/* sld_chtn: A shield made from the shell of a giant insect. */
inherit "/d/Kalad/std/armour";
#include <wa_types.h>
#include "defs.h"

void create_armour()
{
    ::create_armour();
    set_name("shield");
    set_short("huge pink chitin shield");
    set_long("With the attachment of some leather straps, the cleaned out "+
             "shell of a giant pink insect has been turned into an "+
             "excellent, albeit smelly, shield.\n");
    set_adj("huge");
    add_adj("chitin");
    add_adj("pink");

    set_ac(30);
    set_am(({-1,0,1}));
    set_at(A_SHIELD);

    add_prop(OBJ_I_WEIGHT, 9000);
    add_prop(OBJ_I_VOLUME, 4500);
}
