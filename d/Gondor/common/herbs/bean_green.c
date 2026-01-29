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
    set_short("little green bean");
    add_pname(({"herbs", "beans"}));
    set_pshort("little green beans");
    set_adj(({"little", "green", }));
    set_herb_name("green bean");
    set_id_long("This is a green bean. "
      + "It is said to have been brought to Rhovanion and Eriador "
      + "from the plains east and north of the Sea of Rhun by Ilgwett the "
      + "daughter of Marach of the Third House of Men in the early First Age, "
      + "but it now may be found under cultivation in many lands.\n");
    set_unid_long("This green bean looks like an ordinary bean.\n");
    set_ingest_verb("eat");
    set_id_diff(20);
    set_find_diff(1);
    set_effect(HERB_HEALING, "fatigue", 0);
    set_decay_time(3600);
    set_herb_value(6);
    set_amount(1);
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 4);
}

