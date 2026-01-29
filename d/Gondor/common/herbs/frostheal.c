 /*
  * frostheal.c
  *
  * by Elessar
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
    set_name("leaf");
    set_adj(({"gray", "fuzzy"}));
    set_herb_name("frostheal");
    set_short("gray fuzzy leaf");
    set_pshort("gray fuzzy leaves");
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a small, grayish fuzzy leaf from a diminutive "
      + "creeping plant. Its virtue is unknown."));
    set_id_long(BSN("This grayish fuzzy leaf comes from the Frostheal plant, "
      + "a plant found at higher elevations than any other plant, often "
      + "growing at the very edge of eversnow. It will make people who eat "
      + "it more cold-resistant."));

    set_effect(HERB_ENHANCING, "cold", 20);
    add_effect(HERB_CURING, "madwort", 30+random(31));

    set_id_diff(67);
    set_find_diff(6);
    set_decay_time(3600);
    set_herb_value(720);
    set_dryable();
}

