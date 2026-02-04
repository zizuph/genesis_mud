/* 
 */
#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;

#include <wa_types.h>
#include <stdproperties.h>

string adj();
string adj1;

public void
create_terel_armour()
{
    adj1 = adj();
    set_name("boots");
    add_name(adj1+ "boots");
    set_short("pair of "+adj1+" boots");
    set_pshort("pairs of "+adj1+" boots");
    set_adj(adj1);
    set_long("A "+short()+" mostly worn by men. They look sturdy.\n");

    set_default_armour(35, A_FEET, 0, 0);
    set_armour_size(MEDIUM);


    add_prop(OBJ_I_WEIGHT, 350);
    add_prop(OBJ_I_VOLUME, 250);
    add_prop(OBJ_I_VALUE,  950);
}

string adj()
{
    string *adjs;
    adjs = ({"grey","tan","black", "brown"});
    return adjs[random(sizeof(adjs))];
}


