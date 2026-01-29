/* created by Aridor 07/11/93
 *
 * Fixed by Stralle @ Genesis 000919
 * Arman - Reduced time until crumble by roughly half
 */

#pragma strict_types

inherit "/std/container";

#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>

void
create_container()
{
    set_name("statue");
    set_pname("statues");
    add_name("corpse");
    add_pname("corpses");
    add_adj("stone");
    set_short("stone statue");
    set_pshort("stone statues");
    set_long("It's a stone statue and it looks very solid! You think " +
             "you can make out draconian features on the statue's face.\n");

    add_prop(CONT_I_WEIGHT, 200000);
    add_prop(CONT_I_MAX_WEIGHT, 270000);
    add_prop(CONT_I_VOLUME, 200000);
    add_prop(CONT_I_MAX_VOLUME, 400000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_NO_REM, 1);
    add_prop(OBJ_I_NO_GET, 1);

    set_alarm(itof(random(10) + 10),0.0,"do_crumble");
}

void
do_crumble()
{
    object *ob;
    int i, size;

    this_object()->change_prop(CONT_I_NO_REM, 0);
    tell_room(E(TO), "The stone statue crumbles to dust.\n");
    ob = all_inventory(this_object());
    
    for (i = 0, size = sizeof(ob) ; i < size ; i++)
    {
        ob[i]->move(environment(this_object()));
        if (!ob[i]->query_no_show() && !ob[i]->query_prop(OBJ_I_INVIS))
            tell_room(E(TO), C(LANG_ASHORT(ob[i])) + " drop" +
                ((ob[i]->num_heap() > 1) ? " " : "s ") +
                "to the ground.\n");
    }

    this_object()->remove_object();
}
