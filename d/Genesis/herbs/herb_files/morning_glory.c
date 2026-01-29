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
    set_adj(({"velvety", "purple"}));
    set_short("velvety purple flower");
    set_pshort("velvety purple flowers");
    set_herb_name("morning glory");
    add_adj(({"morning", "glory"}));
    add_name(({"morning glory", "morning glory flower"}));
    add_pname("herbs");
    set_unid_long(break_string("A small, velvety purple "+
	"flower that grows on a vine.\n", 70));
    set_id_long(break_string("A small, velvety purple "+
	"flower, commonly known as a morning glory, or "+
	"Ipomoea. It is not to be taken internally.\n", 70));
    CC = (5 * EFFECT) + (EFFECT * EFFECT)/4;
    set_id_diff(25);
    set_find_diff(3);
    set_effect(HERB_POISONING, "herb", EFFECT);
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
