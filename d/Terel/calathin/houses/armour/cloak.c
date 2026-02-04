/*
 * CLOAK.C for mercenary guards.
 * Tomas, 11/19/1999
 */

#include <wa_types.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

public void
create_terel_armour()
{
    set_name("cloak");
   set_short("fur-lined cloak");
   set_pshort("fur-lined cloaks");
    set_adj(({"fur-lined"}));
    set_pname("cloaks");
    set_long("The fur-lined cloak is made from durable " +
             "material. The fur lining within the cloak looks like " +
             "it would keep the wearer warm and cozy. " +
             "The cloak was made to wrap around the body.\n");

    set_default_armour(15, A_ROBE, 0, 0);
    set_am(({ 2, 2, -4}));

    add_prop(OBJ_I_WEIGHT, 1500);
    add_prop(OBJ_I_VOLUME, 700);
}



mixed
wear_terel_armour(object ob)
{

   TP->add_prop("wearing_fur",1);

   return 0;

}


mixed
remove(object ob)
{
   
    TP->remove_prop("wearing_fur");

    return 0;
}


