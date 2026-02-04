/*
 * rugged_fur.c
 *
 * Britanica 160322
 */
#pragma strict_types

#include <wa_types.h>
#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
mixed short_desc();

/*
 * Function name: create_terel_armour
 * Description  : constructor.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_terel_armour()
{
    set_name("fur");
    add_name("cloak");
    set_pname("furs");
    add_pname("cloaks");
    set_adj("dirty");
    set_short(short_desc());
    set_long("This appears to be a cloak poorly crafted cloak " 
      + "from lapin and other small furry creatures. Red and yellow " 
      + "stripes have been dyed across the fur which seem to be slowly " 
      + "decaying. Despite the poor condition, this cloak might " 
      + "provide a little protection from the cold before it falls " 
      + "apart completely.\n");
    set_default_armour(10, A_ROBE, 0, 0);
    set_am(({ 1, 1, -2}));
    add_prop(OBJ_I_WEIGHT, 1500);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, 250);
}

/*
 * Function name: short_desc
 * Description  : Sets adjectives, plural name to random value.
 * Arguments    : n/a
 * Returns      : the single short description (to be used with set_short)
 */
mixed
short_desc()
{
    switch(random(4))
    {
        case 0:
            set_pshort("ragged furs");
            add_adj("ragged");
            return "ragged fur";
        case 1:
            set_pshort("patchwork furs");
            add_adj("patchwork");
            return "patchwork fur";
        case 2:
            set_pshort("lapin furs");
            add_adj("lapin");
            return "lapin fur";
        case 3:
            set_pshort("striped furs");
            add_adj("striped");
            return "striped fur";
        default:
            set_pshort("dirty furs");
            return "dirty fur";
    }
}