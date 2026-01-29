inherit "/std/herb";

#include <herb.h>
#include <macros.h>

int CC, EFFECT;

void
create_herb()
{
    set_name(({"pinch", "dust", "pollen", "pinch of golden dust",
	"pinch of corn pollen", "herb"}));
    set_adj("golden");
    add_adj("corn");
    set_pname(({"pinches of golden dust", "pinches of corn pollen",
	"herbs", "pinch of pollen", "pinch of dust"}));
    set_herb_name("corn pollen");
    set_short("pinch of golden dust");
    set_pshort("pinches of golden dust");
    set_unid_long("A pinch of golden dust grains.\n");
    set_id_long(break_string("A small amount of golden "+
	"pollen from a corn plant, or Zea mays. Some believe it "+
	"has magical properties.\n", 70));
    EFFECT = 35;
    CC = (4 * EFFECT) + (EFFECT * EFFECT) / 5;

    set_id_diff(25);
    set_effect(HERB_HEALING, "mana", EFFECT);
    set_ingest_verb("eat");
    set_herb_value(CC);
    set_find_diff(4);
    set_decay_time(5000);
}
