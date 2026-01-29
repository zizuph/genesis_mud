/*
--------------------------------------------------
  Last edited :
-----------------01-02-95 19.41-------------------
  This is an axe used in Thornlin/Lossarnach/Gondor
  for the militia men there...
  Used the /d/Genesis/doc/examples/weapons/axe.c
  coded by Mercade as an example

  By Boromir Feb 95
--------------------------------------------------
*/

inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define WEAPON_HIT 13
#define WEAPON_PEN 17

void
create_weapon()
{
    set_name(({"axe","light axe","broad-bladed axe","metal axe","light broad-bladed metal axe","light metal axe","light metal axe","broad-bladed metal axe"}));
    add_pname("axes");

    set_adj(({"light","broad-bladed","metal"}));

    set_short("light broad-bladed metal axe");
    set_pshort("light broad-bladed metal axes");

    set_long(break_string("This is a light axe with a broad metal blade "+ 
	"made from iron. It is well kept, but not of high "+
	"quality. It looks more like the tool of a peasant than the "+
	"weapon of a soldier.", 75) + "\n");

    set_hit(WEAPON_HIT);
    set_pen(WEAPON_PEN);
    set_wt(W_AXE);
    set_dt( (W_SLASH | W_BLUDGEON) );
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(WEAPON_HIT, WEAPON_PEN));
}

