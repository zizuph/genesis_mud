/* This comment tells emacs to use c++-mode  -*- C++ -*- */
/*
 * robe.c
 * for use with Stronghold dwarves  std_dwf_warrior.c
 * Tomas  -- Jan 2000
 */

#include <wa_types.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

public void
create_terel_armour()
{
    set_name("robe");
    set_pname("robes");
    add_name("white fur-lined robe");
    set_long("It's a white robe lined with warm fur to help keep the wear " +
       "warm during harsh weather.\n");
    set_adj(({"white","fur-lined"}));
    set_default_armour(20, A_ROBE, 0, 0);
    set_am(({ 2, 2, -4}));

    set_armour_size(SMALL);
    add_prop(OBJ_I_WEIGHT, 800);
    add_prop(OBJ_I_VOLUME, 500);
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


