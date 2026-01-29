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
    set_name("fruit");
    add_name(({"herb", "tomato"}));
    add_adj(({"bright red", "bright", "red"}));
    add_pname("herbs");
    set_short("bright red fruit");
    set_pshort("bright red fruits");
    EFFECT = 15;
    CC = (5 * EFFECT) + (EFFECT * EFFECT)/4;
    set_herb_name("tomato");
    set_unid_long(break_string("A bright red fruit, about "+
	"the size of a small apple, but it is not an apple.\n",70));
    set_id_long(break_string("A bright red, ripe tomato, "+
	"or Lycopersicon esculentum. Sometimes referred to "+
	"as a love apple, it is rumoured to inflame the "+
	"passions. A common ingredient in love potions.\n",70));
    set_id_diff(25);
    set_find_diff(6);
    set_effect(HERB_HEALING, "mana", EFFECT);
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

