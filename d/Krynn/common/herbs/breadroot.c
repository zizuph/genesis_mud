/* Breadroot by Teth, Feb.18,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("root");
    set_adj(({"thick", "brown"}));
    set_herb_name("breadroot");
    set_short("thick brown root");
    set_pshort("thick brown roots");
    set_pname(({"roots", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a thick brown root. It was probably " +
        "picked from somewhere near open plains or prairie."));
    set_id_long(BSN("This is the root of breadroot, an herb found " +
        "in temperate open areas. Breadroot (Psoralea esculenta) is an " +
        "herb that develops blue blossoms. It is deep-rooted, " +
        "efficiently tapping underground water. The roots are edible and " +
        "contain much starch. It can be anywhere from 10-50 cm high, and " +
        "is quite drought-resistant."));
    set_herb_value(110);
    set_id_diff(30);
    set_find_diff(2);
    set_effect(HERB_HEALING,"fatigue",2);
    set_decay_time(10000);
    set_dryable();
    set_amount(10);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
