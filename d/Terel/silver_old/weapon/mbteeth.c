/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * bteeth.c
 * teeth from a bear  
 *
 * Janus 920620
 * modified by Sorgum 941002
 */

#include "/d/Terel/include/Terel.h"

inherit STDWEAPON;

#include "/d/Terel/include/recover.h"
#include <wa_types.h>
#include <formulas.h>

/*
 * Function name: create_weapon
 * Description:   create the weapon. (standard)
 */
public void
create_weapon()
{
    ::create_weapon();
    set_name(({"bearteeth","teeth"}));
    set_short("set of large bearteeth");
    set_pshort("teeth");
    set_long("A set of of large, sharp, and discolored teeth taken from a \n"+
	     "large bear. Could be used as a weapon in an emergency.\n");
    set_adj(({"sharp", "discolored", "large"}));
    set_default_weapon(8, 10, W_SWORD, W_IMPALE, W_ANYH, 0);
    add_prop(OBJ_I_WEIGHT, 600);
    add_prop(OBJ_I_VOLUME, 380);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(8, 10) + random(400));
 }



