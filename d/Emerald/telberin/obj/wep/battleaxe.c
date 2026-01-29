/*
 *  /d/Emerald/telberin/obj/wep/battleaxe.c
 *
 *  This is a standard issue weapon for the Telberin Arms Shop
 *
 *  Copyright (c) August 2004, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/weapon.c";
inherit "/lib/keep.c";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

/* prototypes */
public void        create_weapon();


/*
 * Function name:        create_weapon
 * Description  :        set up the weapon
 */
public void
create_weapon()
{
    set_name( ({ "battleaxe", "axe", "weapon" }) );
    set_adj( ({ "shiny", "elven" }) );

    set_short("shiny elven battleaxe");
    set_long("This hefty weapon was crafted by the smiths of"
      + " Telberin. Its long shaft is fit with a heavy"
      + " double-sided axe head which looks as if it could"
      + " do serious damage in combat.\n");

    set_default_weapon(22, 38, W_AXE, W_SLASH, W_BOTH, 0);

    add_prop(OBJ_I_WEIGHT,5000);
    add_prop(OBJ_I_VOLUME,1400);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(21,37)+random(200)-100);
} /* create_weapon */

