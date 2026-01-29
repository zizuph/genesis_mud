/*********************************************************************
 * - shirt.c                                                       - *
 * - A whitw shirt for the shops in the                            - *
 * - Gentleman's club                                              - *
 * - Created by Damaris 10/2001                                    - *
 *********************************************************************/
#pragma strict_types

inherit "/std/armour";

#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

void create_armour()
{
    set_short("white satin shirt");
    set_name("shirt");
    set_adj(({"white", "satin"}));
    set_long("This is a "+ short() +". This is special attire for "+
      "gentleman. The satin is used to show "+
      "off nobility and style.\n");
    set_ac(10 + random(5));
    set_at(A_TORSO);
    set_am( ({-1,3,-2 }) );

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(query_ac()) + 100);
}

public string
query_recover()
{
return MASTER;
}
