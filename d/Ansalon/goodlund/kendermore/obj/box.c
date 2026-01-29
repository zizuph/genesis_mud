/* Gift box for Kendermore. Gwyneth 05/17/99 */

#pragma save_binary

inherit "/lib/keep";
inherit "/std/receptacle";
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"
#include "/d/Ansalon/common/defs.h"

void
create_container()
{
    set_name("box");
    set_pname("boxes");
    set_adj("small");
    add_adj("wooden");
    set_short("small wooden box");
    set_pshort("small wooden boxes");
    set_long("This is a small hinged box with a carving of rose on the lid. " +
        "There is a small lock keeping it shut.\n");
    add_item("lock", "It looks easy to pick. No kender would own this box!\n");
    set_keep(1);
    add_prop(CONT_I_VOLUME, 500);
    add_prop(CONT_I_WEIGHT, 500);
    add_prop(CONT_I_MAX_VOLUME, 5000);
    add_prop(CONT_I_MAX_WEIGHT, 5000);
    add_prop(OBJ_I_VALUE, 50);
    add_prop(CONT_I_CLOSED, 1);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_LOCK, 1);
    set_key(BOX_KEY);
    set_pick(10);
}

