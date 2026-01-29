#pragma strict_types
#include "/d/Avenir/common/common.h"
#include "../defs.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <terrain.h>

inherit "/std/key";

void
create_key()
{

    set_short("small metal key");
    set_long("It is a small metal key looking " +
        "exactly like most small metal keys do.\n");
    add_name("key");
    set_key("_tower_chest_key");
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_WEIGHT, 100);    // Fish weights 100 g
    setuid();
    seteuid(getuid());
}
