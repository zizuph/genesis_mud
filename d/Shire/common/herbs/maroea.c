/*
 *  The green rose, also known as Pawnrose, needed as ingredient for the
 *  "cure" spell.
 *                          Tricky, 17-9-92
 */

inherit "/std/herb.c";
#include <macros.h>
#include "/sys/herb.h"
#include "defs.h"
#include "/sys/stdproperties.h"

create_herb()
{
   set_name("maroea");
   add_name(({ "flower" }));
   set_adj(({"yellow", "drooping"}));
   set_short("yellow drooping flower");
   set_pshort("yellow drooping flowers");
   set_herb_name("maroea");
   set_id_long("This drooping yellow flower is known as Maroea. It " +
        "looks sickly because of its drooping appearance. The flowers " +
        "are made of six large petals that encircle a black center. It " +
        "is often found along riverbanks and woodland.\n");
   set_unid_long("This is some kind of drooping yellow flower.\n");
   set_ingest_verb("eat");
   set_id_diff(35);
   set_find_diff(5);
   set_decay_time(1800);
   set_herb_value(850);
    set_effect(HERB_CURING,"all",50);

}


query_recover() { return MASTER+":"+query_herb_recover(); }
init_recover(arg) { init_herb_recover(arg); }