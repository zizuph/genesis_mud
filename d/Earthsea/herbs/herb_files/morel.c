inherit "/std/herb";

#include <herb.h>
#include <macros.h>

int CC, EFFECT;

void
create_herb()
{
    set_name(({"mushroom"}));
    add_name(({"fungus", "morel", "herb"}));
    set_adj(({"sponge", "brown", "spongelike"}));
    set_herb_name("morel");
    set_pname("mushrooms");
    add_pname(({"herbs", "fungi"}));
    set_short("spongelike fungus");
    set_pshort("spongelike fungi");
    set_unid_long("A brown spongelike fungus.\n"); 
    set_id_long(break_string("A morel mushroom, of the genus "+
	"Morchella. It looks like a small sponge "+
	"on a stalk. Like its other mushroom relatives, "+
	"it has medicinal properties.\n", 70));
    EFFECT = 35;
    CC = (4 * EFFECT) + (EFFECT * EFFECT) / 5;

    set_id_diff(25);
    set_effect(HERB_HEALING, "mana", EFFECT);
    set_ingest_verb("eat");
    set_herb_value(CC);
    set_find_diff(4);
    set_decay_time(5000);
}
