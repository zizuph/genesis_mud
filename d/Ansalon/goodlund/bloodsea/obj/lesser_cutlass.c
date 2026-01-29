/*
 * What         : A short steel cutlass
 * Used by      : Standard minotaur crewmen sailing the Bloodsea
 *                /d/Ansalon/goodlund/bloodsea/obj
 * Description  : A one-handed sword.
 * Made by      : Cherek, Mar 2007
 */ 

#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include "/d/Krynn/common/defs.h"
#include <macros.h>

inherit "/std/weapon";

int HIT = 25;
int PEN = 20;

void
create_weapon()
{
    set_name("cutlass");
    add_pname(({"cutlasses"}));
    set_adj("short");
    set_adj("steel");
    set_short("short steel cutlass");
    set_long("A cutlass is often the weapon of choice by sailors. " +
             "It is robust enough to hack through heavy ropes, " +
             "canvas and wood, but also short enough to use in " +
             "relatively close quarters such as during boarding actions. \n");

    set_hit(HIT);
    set_pen(PEN);
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_ANYH);
    
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_SWORD)
             +random(1000)+random(1000));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 3 + random(200));
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));

    seteuid(getuid(TO));
}
