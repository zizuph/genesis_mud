/* coded by Amelia 4/12/97
*  for use in Roke Ten Alders area 
*  herb with possible medicinal uses
*/
inherit "/std/herb";

#include <herb.h>
#include <macros.h>
#include "defs.h"


int CC;
int EFFECT = 25;


void
create_herb()
{
    set_name("leaf");
    add_name("wintergreen");
    set_adj("oval-shaped");
    add_adj(({"green", "evergreen"}));
    set_pname(({"leaves", "herbs", "wintergreens"}));
    set_herb_name("wintergreen leaf");
    set_short("oval-shaped leaf");
    set_pshort("oval-shaped leaves");
    add_name("herb");
    set_unid_long("A dark, evergreen oval-shaped leaf "+
      "with a long vinelike stem.\n");
    set_id_long(break_string("A wintergreen leaf, which grows on "+
	"a vinelike plant, the Gaultheria procumbens, "+
	"and is particularly common in mountain forests. "+
	"The oil from the fragrant leaf is known to "+
	"have medicinal properties.\n", 70));
    CC = (5 * EFFECT) + (EFFECT * EFFECT)/4;
    set_id_diff(25);
    set_find_diff(3);
    set_effect(HERB_SPECIAL, "", EFFECT);
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


void
special_effect()
{
    object tp = this_player();

    tp->catch_msg("As you eat the leaf, a cool "+
      "refreshing feeling comes over you.\n");
    tp->catch_msg("You feel healthier.\n");
    tp->heal_hp(EFFECT);
}
