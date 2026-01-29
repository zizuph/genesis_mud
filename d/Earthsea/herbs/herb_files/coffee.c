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
    set_name("bean");
    add_adj("brown");
    add_name(({"coffee", "herb", "coffee bean"}));
    set_short("brown bean");
    EFFECT = 10;
    CC = (5 * EFFECT) + (EFFECT * EFFECT)/4;
    set_herb_name("coffee bean");
    set_unid_long("A small brown bean.\n");
    set_id_long(break_string("This is a coffee bean. "+
	"Coffea arabica, a stimulating herb, grows on "+
	"bushes in mountainous areas.\n", 70));
    set_id_diff(25);
    set_find_diff(6);
    set_effect(HERB_HEALING, "fatigue", EFFECT);
    set_ingest_verb("eat");
    set_herb_value(CC);
    set_decay_time(3000);
}
