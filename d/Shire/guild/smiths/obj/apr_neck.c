/* apprentice necklace - guild item for the smiths guild */

#pragma save_binary;

inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "smiths.h"

string forger;
int quality;

void
create_armour()
{
    set_name("necklace");
    add_adj("iron");
    set_long("This necklace is newly forged by a hopeful apprentice.\n");

    set_ac(0);
    set_am(({ 0, 0, 0 }));

    set_at(A_NECK);

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_VOLUME, 20);
    add_prop(OBJ_I_WEIGHT, 50);
}

string
query_forger() {
   return forger;
}

int
query_quality() {
   return quality;
}

void
set_quality(int number) {
   quality=number;
}

void
set_forger(string str) {
   forger=str;
}
