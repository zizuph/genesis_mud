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
   set_name("pawnrose");
   add_name(({ "rose" }));
   add_name(({"_cure_spell_ingr2_"}));
   set_adj(({"green"}));
   set_short("green rose");
   set_pshort("green roses");
   set_herb_name("pawnrose");
   set_id_long("This green rose is a Pawnrose, as used to strengthen " +
        "magical spells that need strengthening.\n");
   set_unid_long("This is some kind of uncommon green rose.\n");
   set_ingest_verb("eat");
   set_id_diff(35);
   set_find_diff(2);
   set_effect(HERB_HEALING,"hp",-13); /* Don't eat it! */
   set_decay_time(1800);
   set_herb_value(410);
}

query_recover() { return MASTER+":"+ query_herb_recover();  }
init_recover(arg)  { init_herb_recover(arg); }
