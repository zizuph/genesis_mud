/* coded by Amelia 4/12/97
*  for use in Roke Ten Alders area 
*  herb with possible medicinal uses
*/
inherit "/std/herb";

#include <herb.h>
#include <macros.h>
#include "defs.h"


int CC, EFFECT;

void
create_herb()
{
    set_name("floweret");
    add_pname("herbs");
    add_adj("green");
    set_short("green floweret");
    set_pshort("green flowerets");
    add_name("broccoli");
    add_name("flower");
    add_pname("broccolies");
    EFFECT = 30;
    CC = (5 * EFFECT) + (EFFECT * EFFECT)/4;
    set_herb_name("broccoli");
    set_unid_long("A small green flower that grows on "+
      "a stalk close to the ground.\n");
    set_id_long(break_string("This is a floweret "+
	"from a broccoli plant, or Brassica oleracea italica, "+
	"which is known for strengthening the mind.\n",70));
    set_id_diff(25);
    set_find_diff(6);
    set_effect(HERB_HEALING, "mana", EFFECT);
    set_ingest_verb("eat");
    set_herb_value(CC);
    set_decay_time(3000);
}
