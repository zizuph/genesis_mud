/* Smooth Camas by Teth, Feb.18,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("leaf");
    set_adj(({"linear", "keeled"}));
    set_herb_name("smooth camas");
    set_short("linear keeled leaf");
    set_pshort("linear keeled leaves");
    set_pname(({"leaves", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a linear keeled leaf. It was " +
        "probably picked from a lily-like herb in a meadow."));
    set_id_long(BSN("This is a leaf of smooth camas, an herb found " +
        "in temperate meadows. Smooth camas (Zygadenus elegans) is a " + 
        "herb that grows to about 60 cm high. The flower is yellowish " +
        "white or greenish white. It begins growth early in spring, " +
        "and is known to be poisonous."));
    set_effect(HERB_POISONING,"herb",50);
    set_poison_file(KRPOISON + "camasp");
    set_herb_value(20);
    set_id_diff(33);
    set_find_diff(7);
    set_decay_time(3500);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
