/* This comment tells emacs to use c++-mode  -*- C++ -*- */
/*
 * furs.c made for std_goblin_grd.c 
 * Tomas  -- Dec. 1999
 */

#include <wa_types.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;


public void
create_terel_armour()
{
    set_name("fur"); 
   set_short("warm fur");
   set_pshort("furs");
    set_pname("furs");
    set_adj(({"heavy","warm"}));
    set_long("Warm fur sewn together from various furry woodland creatures. " +
       "It looks like it would keep you warm in the winter.\n");
    set_default_armour(15, A_ROBE, 0, 0);
    set_armour_size(SMALL);
    set_af(this_object());
    set_am(({ 2, 2, -4}));
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_COLD_WEATHER_PROTECT, 1);
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

