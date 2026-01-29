/* Coded by Ckrik June 1998.
*/
inherit "/std/herb.c";

#include <herb.h>
#include <macros.h>
#include "defs.h"


int CC, EFFECT;

void
create_herb()
{
  set_name("vine");
  set_pname("vines");
  add_name("herb");
  add_pname("herbs");
  add_name("sea kelp");
  add_pname("sea kelps");
  add_name("kelp");
  add_pname("kelps");
  set_adj("slippery");
  add_adj("brown");
  set_short("slippery brown vine");
  set_pshort("slippery brown vines");
  set_herb_name("sea kelp");
  EFFECT = 20;
  CC = (5 * EFFECT) + (EFFECT * EFFECT)/4;
  set_unid_long("A slippery brown vine.\n");
  set_id_long(break_string("This is sea kelp, found growing only " +
			   "in the sea. It looks like a part of a " +
			   "long vine. This piece of kelp must " +
			   "have been washed up onto a beach " +
			   "by the waves. It is rumoured that " +
			   "this plant is very nutritious.\n",70));
  set_effect(HERB_HEALING, "fatigue", EFFECT);
  set_id_diff(45);
  set_find_diff(4);
  set_ingest_verb("eat");
  set_herb_value(CC);
  set_decay_time(3000);
  set_dryable();
}
