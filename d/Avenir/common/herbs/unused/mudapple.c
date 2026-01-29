//-*-C++-*-
// file name:    ~Avenir/common/herbs/mudapple.c
// creator(s):   Casca, 01/02/00
// last update:
// purpose:      Dark foodstuff
// note: 
// bug(s):
// to-do:

inherit "/std/herb";
#include <herb.h>
#include "/d/Avenir/common/common.h"

create_herb()
{
    set_name("ball");
    add_name("herb");
    add_name("fungus");
    set_adj(({ "lumpy", "brown" }));
    set_short("lumpy brown fungus");
    add_pname(({"food", "foods", "foodstuff","mud apples","fungi"}));
    set_herb_name("mud apple");

    set_id_long("This lumpy sporophoric fungus is a dusky shade of brown. "+
        "Its know as a mud apple and while not real tasty its one of the "+
        "staple foodstuffs of the Utterdark.\n");

    set_unid_long("This lumpy sporophoric fungus is a dusky shade of "+
        "brown.\n");

    set_ingest_verb("eat");
    set_id_diff(15);
    set_find_diff(2);
    set_decay_time(2000);
    set_herb_value(30);
    set_amount(50);
    set_dryable();

}
