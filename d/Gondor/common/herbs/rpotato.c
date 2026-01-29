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
    set_name("potato");
    set_short("little red potato");
    add_pname(({"herbs", "potatoes"}));
    set_pshort("little red potatoes");
    set_adj(({"little", "red", }));
    set_herb_name("red potato");
    set_id_long(BSN("This red potato is a member of the "
      + "Tuberosum species of the genus Solanum. The Dunland red "
      + "potato, although small and lumpy, is both tasty and nutritious. "
      + "The red potato is said to have been introduced into the "
      + "Gwathlo valley by the Stoor hobbits which once inhabited "
      + "this land."));
    set_unid_long("This red potato looks like an ordinary potato.\n");
    set_ingest_verb("eat");

    set_effect(HERB_HEALING, "fatigue", 10);
    set_id_diff(10);
    set_find_diff(1);
    set_decay_time(7200);
    set_herb_value(96);
    set_amount(35);
    add_prop(OBJ_I_WEIGHT, 35);
    add_prop(OBJ_I_VOLUME, 30);
    set_dryable();
}

