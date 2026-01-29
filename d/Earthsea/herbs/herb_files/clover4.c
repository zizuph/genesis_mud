/*  Coded by Amelia, 6/97
 *  This is to be used only in Earthsea for a small
 *  find-the-four-leaf-clover newbie quest in Ten Alders :P
 */
inherit "/std/herb";

#include <herb.h>
#include <macros.h>
#include "/sys/stdproperties.h"

int CC, EFFECT;

void
create_herb()
{
    set_name(({"leaf"}));
    add_name(({"herb", "clover"})); 
    set_adj(({"clover","quatrefoil","small", "four-leaf" }));
    set_herb_name("four-leaf clover");
    set_pname("four-leaf clovers");
    add_pname("leaves");
    set_short("small quatrefoil leaf");
    set_pshort("small quatrefoil leaves");
    set_unid_long("A small quatrefoil green leaf, divided in "+
      "four parts.\n");
    set_id_long(break_string("A leaf of the genus Quatrifolium, "+
	"or rare four-leaf clover. It is a symbol of good fortune!\n",
	70));
    set_id_diff(7);
    set_find_diff(3);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY, 1);
    EFFECT = 35 ;
    CC = (4 * EFFECT) + (EFFECT * EFFECT) / 5;
    set_effect(HERB_SPECIAL,"", EFFECT);
    set_ingest_verb("eat");
    set_herb_value(CC);
    set_decay_time(5000);
}

int
special_effect()
{
    object tp = this_player();

    tp->catch_msg("This is your lucky day!\n");
    return 1;
}

int
query_lucky_clover()
{
    return 1;
}
