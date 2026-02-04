/* This comment tells emacs to use c++-mode  -*- C++ -*- */
/*
 * bigwolf.c pelt  
 * Tomas  -- Dec. 1999
 */

#include <wa_types.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;


public void
create_terel_armour()
{
    set_name("pelt"); 
    set_pname("pelts");
    set_adj(({"white","wolf"}));
    set_long("A large white pelt from what looks like a wolf. " +
       "It looks like it might offer the wearer protection from " +
       "the weather.\n");
   set_short("white pelt");
   set_pshort("white pelts");
    set_default_armour(30, A_ROBE, 0, 0);
    set_af(this_object());
    set_am(({ 1, -2, 1}));
    add_prop(OBJ_I_WEIGHT, 7000);
    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_COLD_WEATHER_PROTECT, 2);
    set_armour_size(MEDIUM);
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

