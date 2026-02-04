#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>

string adj();
string adj1;

void
create_terel_armour()
{
    adj1 = adj();
    set_name("tunic");
    set_adj(adj1);
    set_short(adj1+ " tunic");
    set_pshort(adj1+ " tunics");
    set_long("A heavy tunic, made from a coarse material, "+
             "to protect the body of it's wearer.\n");
    set_armour_size(MEDIUM);
    set_default_armour(40, A_BODY, 0, 0);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_VALUE, 1200);

}

string adj()
{
    string *adjs;
    adjs = ({"grey","tan","black", "brown"});
    return adjs[random(sizeof(adjs))];
}

