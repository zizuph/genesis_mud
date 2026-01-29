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
    set_name("fruit");
    set_pname(({"fruits", "herbs"}));
    add_adj(({"bergamot", "pear-shaped", "small", "sour"}));
    add_name("herb");
    set_short("small pear-shaped fruit");
    set_pshort("small pear-shaped fruits");
    set_herb_name("bergamot");
    set_unid_long(break_string("A small green pear-shaped "+
	"fruit with a hard rind.\n", 70));
    set_id_long(break_string("A green pear-shaped "+
	"fruit which grows on a small spiny tree, known commonly "+
	"as bergamot. The fruit is very sour, but the rind "+
	"from this fruit yields a wonderful fragrance, used "+
	"in the distillation of perfumes, especially the "+
	"exquisite chypre. Citrus aurantium bergamia is "+
	"also known as the prince's pear.\n", 70));
    CC = (5 * EFFECT) + (EFFECT * EFFECT)/4;
    set_id_diff(25);
    set_find_diff(3);
    set_effect(HERB_SPECIAL, "", EFFECT);
    set_ingest_verb("eat");
    set_herb_value(CC);
    set_decay_time(3000);
}

void
special_effect()
{
    object tp = this_player();

    tp->catch_msg("Oh, sour!\n");
    tp->heal_hp(EFFECT);
    tp->command("$grimace");
    tp->catch_msg("You feel healthier.\n");
}
