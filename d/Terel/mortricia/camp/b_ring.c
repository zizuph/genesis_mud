/*
    A bonus ring. Mortricia 920922
 */

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include "/sys/wa_types.h"
#include <stdproperties.h>

#define CAMP_DIR             MORTRICIADIR + "camp/"

void inscript(string str);

create_terel_armour()
{
    set_name("ring");
    set_short("golden ring");
    set_adj("golden");
    add_prop(OBJ_I_VALUE, 10);
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 10);

    inscript("Love, Tecla.");
    set_armour_size(ANY_SIZE);

    set_default_armour(1, A_FINGERS, 0, 0);
}

inscript(string str)
{
    string intro;

    intro = "It's a golden ring with an inscription which reads:\n";

    TO -> set_long(intro + str + "\n");
}
