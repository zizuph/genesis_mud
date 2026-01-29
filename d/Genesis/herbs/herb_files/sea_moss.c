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
  set_name("moss");
  set_pname("mosses");
  add_name("herb");
  add_pname("herbs");
  add_name("sea moss");
  add_pname("sea mosses");

  set_adj("slippery");
  add_adj("brown");
  set_short("slippery brown moss");
  set_pshort("slippery brown moss");
  set_herb_name("sea moss");
  EFFECT = 10;
  CC = (5 * EFFECT) + (EFFECT * EFFECT)/4;
  set_unid_long("A slippery brown vine.\n");
  set_id_long(break_string("This is sea moss, found growing only " +
			   "in the sea. This moss must " +
			   "have been washed up onto a beach " +
			   "by the waves. It seems to be of " +
			   "the variety that has some medicinal value.\n",
			   70));
  set_effect(HERB_HEALING, "hp", EFFECT);
  set_id_diff(45);
  set_find_diff(5);
  set_ingest_verb("eat");
  set_herb_value(CC);
  set_decay_time(3000);
  set_dryable();
}

string
query_recover()
{
  return MASTER + ":" + query_herb_recover();
}

void
init_recover(string arg)
{
  init_herb_recover(arg);
}
