/* coded by Amelia 4/12/97
*  for use in Roke Ten Alders area 
*  herb with possible medicinal uses
*/
inherit "/std/herb";

#include <herb.h>
#include <macros.h>
#include "defs.h"


int CC;
int EFFECT = 20;

void
create_herb()
{
    set_name("flower");
    set_pname("flowers");
    set_adj(({"large", "blue"}));
    set_short("large blue flower");
    set_pshort("large blue flowers");
    set_herb_name("blue gentian flower");
    add_name(({"gentian", "herb", "blue gentian flower"}));
    add_pname(({"gentians", "herbs", "blue gentian flowers"}));
    set_unid_long(break_string("A large bright-blue flower. "+
	"Its petals radiate out like a fringe from a yellow "+
	"center.\n",70));
    set_id_long(break_string("A large bright-blue flower, "+
	"known commonly as a blue gentian flower, or Gentiana "+
	"catesbaei. This variety is found in mountain "+
	"fields and cultivated in herb gardens, since it "+
	"has medicinal properties.\n",70));
    CC = (5 * EFFECT) + (EFFECT * EFFECT)/4;
    set_id_diff(25);
    set_find_diff(3);
    set_effect(HERB_HEALING, "hp", EFFECT);
    set_ingest_verb("eat");
    set_herb_value(CC);
    set_decay_time(3000);
}
