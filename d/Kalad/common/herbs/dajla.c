inherit "/std/herb";
#include "/d/Kalad/defs.h"
#include <poison_types.h>
#include <herb.h>



void
create_herb()
{
    set_name("mushroom");
    add_adj("tiny");
    add_adj("black");
    set_short("tiny black mushroom");

    set_id_long("A commonly found mushroom among the damp areas of "+
    "Raumdor, this fungi is very small and completely black. It is "+
    "called Dajla, named after a warlock who was said to eat them "+
    "in a stew. However, for normal people, eating it can be fatal.\n");

    set_unid_long("This is strange and small mushroom. It is completely "+
    "jet-black. It has a strange spicy odor.\n");

    set_herb_name("dajla");
    set_amount(50);
    set_decay_time(1000);
    set_id_diff(30);
    set_find_diff(3);
    set_ingest_verb("eat");
    set_effect(HERB_HEALING,"hp",-400);
}
