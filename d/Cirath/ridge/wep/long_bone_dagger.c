/* This is a long-bladed bone dagger.
   Code (c) 1998 Damian Horton */

#pragma strict_types 
#pragma save_binary

inherit "/std/weapon";
#include "defs.h"
#include "/sys/wa_types.h"
#include <formulas.h>

void create_weapon()
{
    set_name("dagger");
    add_name("knife");
    set_short("long-bladed bone dagger");
    set_long("A long-bladed bone dagger. Likely to break, but "+
        "perfectly useful for stabbing someone until that time.\n");

    set_adj("bone");
    add_adj("long-bladed");

    set_hit(16);
    set_pen(16);

    likely_dull=18;
    likely_corr=0;
    likely_break=20;

    set_wt(W_KNIFE);
    set_dt(W_IMPALE);
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 3300);
    add_prop(OBJ_I_VOLUME, 800);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(16,16)-random(75));
}
