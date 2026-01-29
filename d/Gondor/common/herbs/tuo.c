#pragma save_binary
#pragma strict_types

inherit "/std/herb.c";

#include <herb.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_herb()
{
    set_name("lichen");
    set_adj(({"green", "pale"}));
    set_herb_name("tuo");
    set_short("piece of pale green lichen");
    set_pshort("pieces of pale green lichen");
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a piece of a pale green lichen. "
      + "It was probably picked from a tree."));
    set_id_long(BSN("This is a piece of Tuo, a pale green lichen "
      + "from the forests of Gondor. It is said to be strengthening "
      + "when eaten, for a short time. That is also the reason for the name."));

    set_effect(HERB_ENHANCING, "str", 50);

    set_id_diff(50);
    set_find_diff(6);
    set_decay_time(7200);
    set_herb_value(688);
}

