 /*
  *  /d/Gondor/common/herbs/peanut.c
  *  An herb of southern Gondor.
  *  Eating the peanuts descreases fatigue slightly.
  *  Modified from /d/Gondor/common/herbs/dill.c by Olorin.
  * 
  *  June 19, 2001, Serif.
  */

#pragma save_binary
#pragma strict_types

inherit "/std/herb.c";

#include <herb.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_herb()
{
    set_name("nuts");
    add_name(({"nut", "nuts"}));
    set_adj(({"handful", "of", "dun-coloured", "thin-shelled"}));
    set_herb_name("peanuts");
    set_short("handful of thin-shelled nuts");
    set_pshort("handfuls of thin-shelled nuts");
    set_ingest_verb("eat");
    set_unid_long("This is a handful of dun-coloured thin-shelled "
        + "nuts.\n");
    set_id_long("This is a handful of peanuts. Peanuts (Arachis "
        + "hypogaea) are the ripe fruit of a low-growing herb of the "
        + "legume family. The plant prefers warm climates, growing to "
        + "a foot or two in height. After flowering, thin-shelled nuts "
        + "develop underground. The nuts are a source of protein enjoyed "
        + "by many large animals.\n");

    set_effect(HERB_HEALING, "fatigue", 1);
    set_id_diff(18);
    set_find_diff(5);
    set_decay_time(10000);
    set_herb_value(72);
    add_prop(OBJ_I_WEIGHT, 60);
    add_prop(OBJ_I_VOLUME, 60);
    set_amount(60);
    set_dryable();
}
