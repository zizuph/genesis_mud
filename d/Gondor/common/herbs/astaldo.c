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
    set_adj("brown");
    set_adj("broad-headed");
    set_herb_name("astaldo");
    set_short("brown broad-headed mushroom");
    set_pshort("brown broad-headed mushrooms");
    set_ingest_verb("eat");
    set_unid_long("This is a brown mushroom with a broad head on "
      + "a pale stalk.\n");
    set_id_long(BSN("This is a brown broad-headed mushroom, known "
      + "as Astaldo. It is known to make you more brave and disciplined "
      + "when eaten, but is often confused with other similar brown "
      + "mushrooms. It originates from Gondor."));
    set_herb_value(644);
    set_id_diff(43);
    set_find_diff(4);
    set_effect(HERB_ENHANCING,"dis", 40);
    set_decay_time(4600);
}

