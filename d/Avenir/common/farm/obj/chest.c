#pragma strict_types
#include "/d/Avenir/common/common.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <terrain.h>
#include "../defs.h"

inherit "/std/receptacle";

void
create_receptacle()
{
    set_name("_sailors_chest");
    set_adj("sailors");
    set_short("sailors chest");
    set_long("@@desc_chest");
    add_name("chest");
    set_key("_tower_chest_key");
    set_pick(100);
    add_prop(CONT_I_WEIGHT, 4500);      /* It weights 4500 grams */
    add_prop(OBJ_M_NO_GET, 1);         // Cannot be taken
    add_prop(CONT_I_VOLUME, 10000);      /* 1.9 l volume (very small) */
    add_prop(CONT_I_MAX_VOLUME, 60000);  /* 6 litres of volume */
    add_prop(CONT_I_MAX_WEIGHT, 60000);  /* 6 kilos */
    add_prop(CONT_I_RIGID, 1);            /* It is a rigid object   */
    add_prop(CONT_I_CLOSED, 1);
    add_prop(CONT_I_LOCK,   1);
}

int
do_default_unlock(string str)
{
    if (TO->query_prop("_ready"))
    {
        notify_fail("You find no keyhole in the chest.\n");
        return 0;
    }

    if (!::do_default_unlock(str))
        return 0;

    return 1;
}

string
desc_keyhole()
{
    string text;

    if (!(TO->query_prop("_ready")))
        text = " You can see a small keyhole in the " +
            "front of the chest.";
     else
    text = " On the front of the chest a small coin " +
        "has been fixed.";
    return text;
}

string
desc_chest()
{
    string text;

    text = "This is a small sailors chest. Light blue in colour " +
        "and has two rope handles on each side.";
    text += desc_keyhole();
    text += "\n";
    return text;
}
