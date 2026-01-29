/* This is Avena second weapon, an excellent knife 
   Code (c) 1998 Damian Horton
   Redone for Raumdor, March 2001.
*/

#pragma strict_types 
#pragma save_binary

inherit "/std/weapon";
#include "/d/Cirath/defs.h"
#include "/sys/wa_types.h"
#include <formulas.h>

void create_weapon()
{
    set_name("knife");
    set_short("elegant bone knife");
    set_long("An elegantly sculpted knife carved from bone. Its foot "+
             "long blade is very sharp, and it is excellently balanced.\n"); 
    set_adj("elegant");
    add_adj("bone");

    set_hit(20);
    set_pen(20);

    likely_dull=20;
    likely_corr=2;
    likely_break=20;

    set_wt(W_KNIFE);
    set_dt(W_SLASH);
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 1200);
    add_prop(OBJ_I_VOLUME, 800);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(20,20)+random(150)-random(100));
}







