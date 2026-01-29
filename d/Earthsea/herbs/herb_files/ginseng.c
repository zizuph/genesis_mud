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
    set_name(({"ginseng", "ginseng root"}));
    add_name("herb");
    add_pname("herbs");
    add_pname("roots");
    add_pname("ginsengs");
    add_adj("ginseng");
    set_adj(({"forked"}));
    add_adj("brown");
    EFFECT = 50;
    CC = (5 * EFFECT) + (EFFECT * EFFECT)/4;
    set_herb_name("ginseng");
    set_short("forked root");
    set_pshort("forked roots");
    set_pname("ginseng roots");
    add_pname("forked roots");
    add_name("root");
    set_unid_long(break_string("A brown root that forks into two "+
	"sections. It has many small roots attached to it, making "+
	"it appear hairy.\n", 70));
    set_id_long(break_string("This is the legendary ginseng root "+
	"or Panax shinseng, which is believed to have "+
	"strong medicinal properties, especially for strengthening "+
	"the mind.\n", 70));
    set_id_diff(35);
    set_find_diff(4);
    set_effect(HERB_HEALING, "mana", EFFECT);
    set_ingest_verb("eat");
    set_herb_value(CC);
    set_decay_time(3000);
}
