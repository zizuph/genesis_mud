/*
 * Noble's Blouse
 * -- Finwe, June 2007
 */
inherit "/std/object";
inherit "/lib/wearable_item";

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#define CLOTH_TYPE  ({"shirt", "tunic"})
#define MATERIAL    ({"silk", "cotton"})
#define COLOR       ({ "white", "red", "blue", "light-grey", "orange"})

string material, color, cloth_type;
void init_the_clothes();

void
create_object()
{
    init_the_clothes();

    set_name(cloth_type);
    add_name("shirt");
    add_name("tunic");
    add_adj(color);
    add_adj(material);
    set_short(color + " " + material + " " + cloth_type );
    set_long("This is a " + query_short() + ". It has long sleeves and is comfortable to wear. The " + cloth_type + " looks expensive and is worn by halflings.\n");

    set_slots(A_BODY | A_ARMS);
    set_layers(0);
    set_looseness(0);
    set_may_not_recover();

    add_prop(OBJ_I_VOLUME, 1000);   /* volume 1 litres */
    add_prop(OBJ_I_WEIGHT, 500);   /* weight 1/2 kilo */
    add_prop(OBJ_I_VALUE, 2);
}

void init_the_clothes()
{
    if (!material)
        material = ONE_OF_LIST(MATERIAL);
    if (!color)
        color = ONE_OF_LIST(COLOR);
    if (!cloth_type)
        cloth_type  = ONE_OF_LIST(CLOTH_TYPE);
}


string
query_recover()
{
    string rec;
    rec = MASTER + ":";

    rec += "#material#" + material;
    rec += "#color#" + color;
    rec += "#cloth_type#" + cloth_type;

    return rec;
}
void
init_recover(string arg)
{
    string dummy;
    int i_check;

    sscanf(arg, "%s#material#%s#%s", dummy, material, dummy);
    sscanf(arg, "%s#color#%s#%s", dummy, color, dummy);
    sscanf(arg, "%s#cloth_type#%s#%s", dummy, cloth_type, dummy);

    init_the_clothes();

    return;
}