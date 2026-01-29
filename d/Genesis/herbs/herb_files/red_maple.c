/* Coded by Ckrik June 1998
*  for decoration in Oranea, quest, and possible magical value.
*/
inherit "/std/herb.c";

#include <herb.h>
#include <macros.h>
#include "defs.h"


int CC, EFFECT;

void
create_herb()
{
  set_name("leaf");
  set_pname("leaves");
  add_name("herb");
  add_pname("herbs");
  add_name("maple leaf");
  add_pname("maple leaves");
  add_adj("red");
  set_short("red seven-pointed leaf");
  set_pshort("red seven-pointed leaves");
  set_herb_name("red maple leaf");
  EFFECT = 10;
  CC = (5 * EFFECT) + (EFFECT * EFFECT)/4;
  set_unid_long("A red seven-pointed leaf. It is very beautiful.\n");
  set_id_long(break_string("This is the leaf of a red maple tree. " +
			   "The leaves of such a tree stays " +
			   "red even during spring and summer and " +
			   "falls in autumn. People often collect " +
			   "these leaves just for its beauty.\n",70));
  set_id_diff(5);
  set_find_diff(0);
  set_ingest_verb("eat");
  set_herb_value(CC);
  set_decay_time(3000);
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
