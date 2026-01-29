//-*-C++-*-
// file name:    ~Avenir/common/herbs/perelus.c
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
    set_adj(({ "firm", "tan" }));
    set_short("firm tan fungus");
    add_pname(({"food", "foods", "foodstuff","perelus","fungi"}));
    set_herb_name("perelus");

    set_id_long("This fungal blossum has a firm light tan colored outer "+
        "shell. "+
        "Its called a Perelus by the denizens of the Utterdark and is "+
        "frequently used as a food source.\n");

    set_unid_long("This fungal blossum has a firm light tan colored outer "+
        "shell.\n");

    set_ingest_verb("eat");

    set_id_diff(22);
    set_find_diff(2);
    set_decay_time(1600);
    set_herb_value(30);
    set_amount(65);
    set_dryable();

}
