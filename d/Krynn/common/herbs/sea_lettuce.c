/* Sea Lettuce by Teth, March 2,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("alga");
    set_adj(({"sheet-like", "green"}));
    set_herb_name("sea lettuce");
    set_short("sheet-like green alga");
    set_pshort("sheet-like green algae");
    set_pname(({"algae", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a sheet-like green alga. It was probably " +
        "picked nearshore or in the intertidal zone."));
    set_id_long(BSN("This is a sheet-like green alga, an herb found " +
        "in nearshore oceans and intertidal areas. Sea lettuce (Ulva " +
        "lobata) is a brilliant green colour. It is commonly called " +
        "sea lettuce due to its similarity in appearance to lettuce leaves. " +
        "It is highly edible, aiding a tired person, but has no other " +
        "known use."));
    set_herb_value(47);
    set_id_diff(2);
    set_find_diff(2);
    set_effect(HERB_HEALING,"fatigue",1);
    set_decay_time(3000);
    set_amount(4);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
