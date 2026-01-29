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

inherit "/std/receptacle";

void
create_container()
{

    set_short("small oilskin sack");
    add_name("sack");
    add_name("oilskin");
    add_name("_sack");
    set_long("@@desc_long");
    add_prop(CONT_I_MAX_VOLUME, 100000); // 100 litre
    add_prop(CONT_I_MAX_WEIGHT, 10000); // 10 Kg
    add_prop(CONT_I_WEIGHT, 50);       // Sack weights 50 g
    add_prop(CONT_I_VOLUME, 50);       // Volume of the sack = 50ml
    add_prop(OBJ_I_RES_WATER, 100);
    add_prop(CONT_I_CLOSED, 1);
    setuid();
    seteuid(getuid());
}

string
desc_long()
{
    string text;

    text = "This is an oilskin sack. Made of oilskin " +
        "this sack will keep anything stored in it " +
        "completely safe from water.";

    text+="\n";
    return text;
}

