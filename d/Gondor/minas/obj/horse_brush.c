/*
 * /d/Gondor/minas/obj/horse_brush.c
 *
 * A brush for the Royal Stables
 *
 * Alto 17 April 2001
 *
 */
 
inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

object actor, here, *env;

void
create_object()
{
    set_name("brush");
    add_name("_minas_horse_brush_");
    set_adj("small");
    add_adj("wooden");
    set_short("small wooden brush");
    set_pshort("small wooden brushes");
    set_pname("brushes");
    set_long("A small wooden brush with stiff bristles. Although "
        + "it does not look like the kind of brush a person might "
        + "want to run through their hair, it does look ideal for "
        + "brushing the hair on a horse. You see a small inscription "
        + "on the back side.\n");
    add_item(({"inscription", "small inscription"}), "The inscription "
        + "reads: Property of the Royal Stables.\n");
    add_item(({"bristles"}), "They are stiff and made of wire.\n");
    add_prop(OBJ_I_VALUE, 50);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_WEIGHT, 100);
    seteuid(getuid(TO));
}

void
init()
{
   ::init();
   add_action("brush_thing", "brush");
}

int
brush_thing(string str)
{
    actor = TP;
    here = environment(TP);
    env = all_inventory(here);

    if (sizeof(filter(env, &->id("_porter_q_horse_")))) return 0;

    if (!strlen(str))
        NF0("Brush what?\n");

    write("You would feel guilty using this brush for anything other "
        + "than grooming the horses in the Royal Stables.\n");

    return 1;
}
