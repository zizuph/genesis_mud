#pragma save_binary
#pragma strict_types

inherit "/std/herb.c";

#include <herb.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_herb()
{
    set_name("berry");
    set_short("little blue berry");
    set_pshort("little blue berries");
    set_adj(({"little", "blue", }));
    set_herb_name("blueberry");
    set_id_long(BSN("This is a common blueberry. Although it is " +
        "often mistaken by the uninitiated for the much rarer and more "+
        "valuable herb Attanar, the blueberry has only a mild purgative "+
        "and restorative effect."));
    set_unid_long("This blue berry looks like an ordinary berry. "+
        "You don't know what it's for.\n");
    set_ingest_verb("eat");
    set_id_diff(15);
    set_find_diff(1);
    set_effect(HERB_HEALING, "fatigue", 2);
    set_decay_time(3600);
    set_herb_value(18);
    set_amount(2);
    add_prop(OBJ_I_WEIGHT,2);
    add_prop(OBJ_I_VOLUME,2);
    
}

