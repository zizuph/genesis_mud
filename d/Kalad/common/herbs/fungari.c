inherit "/std/herb";
#include "/d/Kalad/defs.h"
#include <poison_types.h>
#include <herb.h>


void
create_herb()
{
    set_name("mushroom");
    add_adj("red");
    add_adj("black-spotted");
    set_short("red black-spotted mushroom");

    set_id_long("This is the legendary fungari, a very valuable herb "+
    "that is found only in the most remote of swamps. It bright red "+
    "in color, with many black spots. When eaten, it is said to "+
    "cure even the vilest of poisons.\n");

    set_unid_long("This a very red mushroom with many black spots. "+
    "It is rather small, with a thick stem.\n");

    set_herb_name("fungari");
    set_amount(5);
    set_decay_time(1500);
    set_id_diff(50);
    set_find_diff(12);
    set_herb_value(4000);
    set_ingest_verb("eat");
    set_effect(HERB_CURING,"all",100);
}
