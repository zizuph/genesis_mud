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
    set_name("weed");
    add_name(({"leaf", "plants", "herb", "cinquefoil"}));
    set_herb_name("cinquefoil");
    add_pname(({"herbs", "plants", "weeds", "leaves"}));
    set_adj("silvery");
    EFFECT = 20;
    CC = (5 * EFFECT) + (EFFECT * EFFECT)/4;
    set_short("silvery weed");
    set_pshort("silvery weeds");
    set_unid_long(break_string("A weed with oblong, serrated "+
	"leaves that are dark-green on top and covered in "+
	"silvery hairs beneath.\n",70));
    set_id_long(break_string("A cinquefoil weed, or Potentilla "+
	"anserina. It has oblong serrated leaves that are "+
	"dark-green on top and covered in silvery hairs "+
	"beneath. Cinquefoil, or silverweed, commonly "+
	"known as five-finger grass because of the shape "+
	"of its leaves, is known for its remedial "+
	"effects.\n", 70));
    set_id_diff(25);
    set_find_diff(6);
    set_effect(HERB_HEALING, "hp", EFFECT);
    set_ingest_verb("eat");
    set_herb_value(CC);
    set_decay_time(3000);
}
