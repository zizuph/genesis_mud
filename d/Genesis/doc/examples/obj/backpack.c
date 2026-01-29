inherit "/d/Genesis/std/pack";
inherit "/lib/keep"; 

/* Inherit this to add help functionality to the backpack. */
inherit "/lib/help";

#include <stdproperties.h>

void
create_pack()
{
    set_name("backpack");
    add_adj("leather");
    set_long("A leather pack which can be worn on the back.\n");

    set_mass_storage(1); 

    set_keep(1); 

    add_prop(CONT_I_WEIGHT, 4500);
    add_prop(CONT_I_MAX_WEIGHT, 150000);
    add_prop(CONT_I_VOLUME, 8000);
    add_prop(CONT_I_MAX_VOLUME, 150000);

    add_prop(OBJ_I_VALUE, 450);

    /* Add a help topic on "backpack" */
    add_help_topic("backpack",
        "A backpack offers additional commands \"fill\" and \"empty\".\n");

    /* Add a help topic on "fill" and "empty".
     * In fact they both refer to the same file. */
    add_help_topic("fill",  "/d/Genesis/doc/examples/obj/backpack_help");
    add_help_topic("empty", "/d/Genesis/doc/examples/obj/backpack_help");
}
