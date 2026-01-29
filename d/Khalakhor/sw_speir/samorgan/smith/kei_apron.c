inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/d/Cirath/defs.h"

void create_armour()
{
    set_name("apron");
    set_short("leather apron");
    set_long("Hide taken from the larger lizards of Athas, particularly "+
             "mekillots, makes a think and protective leather. This apron " +
             "has a long, wide bib to protect the chest from shards of " +
             "white hot metal or stone.\n");
    set_adj("leather");

    set_ac(10);
    set_at(A_NECK);

    add_prop(OBJ_I_WEIGHT, 250);
    add_prop(OBJ_I_VOLUME, 1225);
}
