/*
 * Healing herb for Mirkwood
 * This herb may ONLY exist in Mirkwood/Rhovanion unless
 * otherwise approved by AoB. If this herb is planted in
 * a room, the Anna herb MUST also be present in the same
 * room.
 * Varian 2015
 */

#pragma save_binary
#pragma strict_types

inherit "/std/herb.c";

#include <herb.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

void
create_herb()
{
    set_name("fruit");
    set_adj(({"soft", "red",}));
    set_short("soft red fruit");
    set_pshort("soft red fruits");
    set_herb_name("yave");
    set_id_long(BSN("This is the rare and legendary Yave fruit. The fruit " +
            "is small and round, not to mention delicious to eat. Rumoured " +
            "to be a gift from the Valar to the Sindar, it is said that by " +
            "sharing this gift, the blessings of Kementari shall be " +
            "bestowed upon you.")); 
    set_unid_long(BSN("This is a soft red fruit. It is rather small and " +
            "round, but you do not believe you have ever seen its " +
            "like before. You think it might be good to eat however."));
    set_ingest_verb("eat");
    set_id_diff(70);
    set_find_diff(10);
    set_effect(HERB_HEALING, "hp", 120);
    set_decay_time(1800);
    set_herb_value(1000);
}
