/*Cold Weather healing herb for Terel
 * Tomas  -- Dec. 1999
 *
 */

inherit "/std/herb";
#include "/sys/herb.h"

create_herb()
{
  set_name("berry");
  add_name("herb");
  add_pname(({"herbs", "berries", "whitehorns"}));
  set_short("small white berry");
  set_adj(({"small", "white"}));
  set_herb_name("whitehorn");
  set_id_long("The berry Whitehorn receives its name from its white "+
     "colour and the small stem socket which looks similar to a tiny horn. "+
     "Its properties are rumoured to accelarate wound healing dramatically.\n");
  set_unid_long("A small white berry with a horn-shaped stem socket.\n");
  set_effect(HERB_HEALING,"hp",115);
  set_dryable();
  set_ingest_verb("eat");
  set_id_diff(75);
  set_find_diff(8);
  set_decay_time(4000);
  set_herb_value(1200);
}


