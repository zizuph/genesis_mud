/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * chainmail.c 
 * worn by house4_captain.c
 * Tomas 11/19/1999
 */


#include <wa_types.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

public void
create_terel_armour()
{
    set_name("chainmail");
    set_short("grey chainmail");
   set_pshort("grey chainmails");
    set_adj("grey");
    set_long("The suit of chainmail looks well made. " +
       "Its steel links have been polished to a high buff. " + 
       "The inner-lining is made of soft yet durable cloth.\n"); 

    set_adj(({"light"}));

    set_default_armour(30, A_BODY, 0, 0);
    
    add_prop(OBJ_I_VALUE,            500);
    add_prop(OBJ_I_WEIGHT,          5000);
}
