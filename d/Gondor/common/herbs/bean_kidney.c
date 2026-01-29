#pragma save_binary
#pragma strict_types

inherit "/std/herb";

#include <herb.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_herb()
{
    set_name("bean");
    set_short("little red bean");
    add_pname(({"herbs", "beans"}));
    set_pshort("little red beans");
    set_adj(({"little", "red", "kidney", "kidney-shaped", "red" }));
    set_herb_name("kidney bean");
    set_id_long(BSN("This is a kidney bean. " 
      + "It is said to have been brought to Middle-Earth "
      + "from Numenor during the second expedition of Tar-Aldarion, "
      + "but it now may be found under cultivation in many lands."));
    set_unid_long("This looks like an ordinary red, kidney-shaped bean.\n");
    set_ingest_verb("eat");
    set_id_diff(15);
    set_find_diff(1);
    set_effect(HERB_HEALING, "fatigue", 0);
    set_dryable();
    set_decay_time(3600);
    set_herb_value(8);
    set_amount(1);
    add_prop(OBJ_I_WEIGHT, 2);
    add_prop(OBJ_I_VOLUME, 2);
}

