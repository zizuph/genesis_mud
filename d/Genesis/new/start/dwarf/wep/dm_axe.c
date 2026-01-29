/* Written by Nuf
 * /d/Genesis/new/start/dwarf/wep/dm_axe.c
 */

#pragma strict_types

inherit "/std/weapon";

#include "wep.h"
#include <stdproperties.h>
#include <wa_types.h>

/* Prototypes */
public void create_weapon();

/* Defines */

public void
create_weapon()
{
    ::create_weapon();
    set_name("_axe_from_dwarven_mountain");
    add_name("axe");
    set_long("The handle is made out of oak, and moss has begun to "+
             "grow on it. The edge is made of steel, and it has "+
             "oxided a little.\n" );
    set_short("oak handled axe");
    set_pshort("oak handled axes");
  
    set_hit(5 + random(3));
    set_pen(5 + random(5));
    
    set_wt(W_AXE);
    set_dt(W_BLUDGEON & W_SLASH);
    set_hands(W_ANYH);

    /* Properties */
    add_prop(OBJ_I_WEIGHT, 4000 + random(5)*100); 
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
    add_prop(OBJ_I_VALUE, 10);
}
