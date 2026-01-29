/*
 *  The Huckleberry, needed as ingredient for the "tend" and "cure" spell.
 *                          Tricky, 17-9-92
 */

inherit "/std/herb.c";

#include "/sys/herb.h"
#include "defs.h"
#include <macros.h>
#include "/sys/stdproperties.h"

create_herb()
{
    set_name(({"berry","_cure_spell_ingr1_","_tend_spell_ingr_"})); 
   set_adj(({"green"}));
   set_short("green berry");
   set_herb_name("huckleberry");
   set_id_long("This green berry is small and looks similar to " +
        "another well known plant, Athelas, or Kingsfoil. Though " +
        "not as strong, the Huckleberry can be helpful for casting " +
        "healing spells.\n");
   set_unid_long("This is some kind of green berry that looks edible.\n");
   set_ingest_verb("eat");
   set_id_diff(27);
   set_find_diff(4);
   set_effect(HERB_HEALING,"hp",5); /* You can eat it */
   set_decay_time(1800);
   set_herb_value(211);
}
query_recover() { return MASTER + ":"+query_herb_recover(); }
init_recover(arg) { init_herb_recover(arg); }
