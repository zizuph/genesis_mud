#pragma save_binary
#pragma strict_types

inherit "/std/herb.c";

#include <herb.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_herb()
{
    set_name("mushroom");
    set_adj(({"brown", "broad-headed"}));
    set_herb_name("tyelka");
    set_short("brown broad-headed mushroom");
    set_pshort("brown broad-headed mushrooms");
    set_ingest_verb("eat");
    set_unid_long("This is a brown mushroom with a broad head on a pale stalk.\n");
    set_id_long(BSN("This is a brown broad-headed mushroom, known as "
      + "Tyelka. It is known to make you more agile and dexterous when "
      + "eaten, hence the name in Gondor. It originates from Ithilien "
      + "in Gondor, and grows mostly in damp places, near fresh water."));

    set_effect(HERB_ENHANCING, "dex", 20);

    set_id_diff(43);
    set_find_diff(5);

    set_decay_time(3600);
    set_herb_value(644);
    set_dryable();
}

