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
    set_name("leaf");
    add_name(({"spinach leaf", "spinach"}));
    set_pname("leaves");
    add_adj(({"dark green", "green", "spinach"}));
    EFFECT = 20;
    set_herb_name("spinach");
    set_short("dark green leaf");
    set_pshort("dark green leaves");
    add_name("herb");
    add_pname("herbs");
    set_unid_long("A dark green wrinkled leaf. It comes "+
      "from a small bush that grows in the ground.\n");
    set_id_long(break_string("A spinach leaf. It is a highly "+
	"nutricious plant, or Spinacia oleracea, "+
	"which is rumoured to increase one's "+
	"strength if eaten regularly.\n", 70));
    CC = (5 * EFFECT) + (EFFECT * EFFECT)/4;
    set_id_diff(20);
    set_find_diff(3);
    set_effect(HERB_ENHANCING, "str", EFFECT);
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
