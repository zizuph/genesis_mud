/* Licorice by Karath, from Teth's Chicory April.,97 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("root");
    set_adj(({"strong-smelling", "gnarled", "strong smelling"}));
    set_herb_name("licorice");
    set_short("strong-smelling gnarled root");
    set_pshort("strong-smelling gnarled roots");
    set_pname(({"roots", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This root comes from a leguminous plant, and " +
        "has a very strong, somewhat sweet smell. It is has a woody " +
	"texture and tapers off into a tip."));
    set_id_long(BSN("This is the root of licorice, an herb found " +
        "in temperate open areas. The root of licorice is mostly " +
        "used by extracting the strong essence for cooking and " +
	"candymaking. Licorice is said to aid the respiratory system " +
        "and boost one's awareness by fighting fatigue."));
    set_herb_value(299);
    set_id_diff(25);
    set_find_diff(5);
    set_effect(HERB_HEALING,"fatigue",27);
    set_decay_time(8000);
    set_dryable();
    set_amount(1);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
