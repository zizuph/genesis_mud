#pragma save_binary
#pragma strict_types

inherit "/std/herb";

#include <herb.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_herb()
{
    set_name("bean");
    set_short("light green bean");
    add_pname(({"herbs", "beans"}));
    set_pshort("light green beans");
    set_adj(({"light", "green", "lima", "whitish", "kidney-shaped" }) );
    set_herb_name("lima bean");
    set_id_long(BSN("This is a tasty whitish-geen bean. " 
      + "The lima bean is said to have been brought to Middle-Earth "
      + "from Numenor during the second expedition of Tar-Aldarion, "
      + "but it now may be found under cultivation in many lands."));
    set_unid_long("This looks like an ordinary light green, "
      + "kidney-shaped bean.\n");
    set_ingest_verb("eat");
    set_id_diff(20);
    set_find_diff(2);
    set_effect(HERB_HEALING, "fatigue", 3);
    set_dryable();
    set_decay_time(5400);
    set_herb_value(24);
    set_amount(5);
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 5);
}

