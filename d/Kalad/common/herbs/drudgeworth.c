inherit "/std/herb";
#include "/d/Kalad/defs.h"
#include <poison_types.h>
#include <herb.h>

/* A very poisonous herb , Sarr */

void
create_herb()
{
    set_name("mushroom");
    add_adj("slimy");
    add_adj("black");
    set_short("slimy black mushroom");
    set_id_long("This is a large looking mushroom that is very slimy. "+
    "It is known as drudgeworth, and can be easily identified by its "+
    "jet-black color and slimy skin, as well as its somewhat rancid "+
    "odor. It is not poisonous, but is said to slow down reaction time "+
    "when eaten.\n");

    set_unid_long("This is a large mushroom that is very wet and "+
    "slimy. It is jet-black in color, and smells somewhat rancid.\n");

    set_herb_name("drudgeworth");
    set_amount(10);
    set_decay_time(1000);
    set_id_diff(35);
    set_find_diff(4);
    set_herb_value(30);
    set_ingest_verb("eat");
    set_effect(HERB_ENHANCING,"dex",-8);
}

