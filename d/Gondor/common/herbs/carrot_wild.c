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
    set_name("carrot");
    set_short("little green-topped orange carrot");
    set_pshort("little green-topped orange carrots");
    set_adj(({"little","green-topped","orange","tasty","crunchy"}));
    set_herb_name("little orange carrot");
    set_id_long(BSN("This little orange carrot is a member of the "
      + "Carrota species of the genus Daucus. The wild carrot is a "
      + "woody orange root. The wild carrot is a ubiquitous food source "
      + "throughout Eriador and Beleriand."));
    set_unid_long("This little orange carrot looks like an ordinary carrot.\n");
    set_ingest_verb("eat");

    set_effect(HERB_HEALING,"fatigue",3);
    set_id_diff(15);
    set_find_diff(5);
    set_decay_time(3600);
    set_herb_value(18);
    set_amount(20);
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 24);

    set_dryable();
}

