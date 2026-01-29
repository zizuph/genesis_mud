/*
 * Club for the Bullywugs
 * by Finwe, July 2007
 */
#pragma save_binary
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

inherit FAERUN_WEP_BASE;

#define ADJ1 "battered"
#define ADJ2 "spiked"
#define WEAPON  "club"

int hit = 35 + random(5),
    pen = 35 + random(5);
void
create_faerun_weapon()
{

    set_name("club");
    add_name(WEAPON);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + WEAPON); 
    set_long("This is a " + short() + ". It is a long rod with a round ball on it. Surrounding the ball are eight long spikes. The spikes extend outward and look like they can rip through flesh easily.\n");

    set_hit(hit);
    set_pen(pen);
    set_wt(W_CLUB); 
    set_dt(W_BLUDGEON | W_IMPALE); 

    add_prop(OBJ_I_WEIGHT,1500);
    add_prop(OBJ_I_VOLUME,1500);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(hit,pen));

    set_hands(W_ANYH); 
}
