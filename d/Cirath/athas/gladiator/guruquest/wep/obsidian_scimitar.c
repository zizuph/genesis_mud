/* This is Myrdoth's second best weapon. 
   Code (c) 1998 Damian Horton
   Updated for Raumdor, March 2001
 */

#pragma strict_types 
#pragma save_binary

#include "/d/Cirath/defs.h"
#include "/sys/wa_types.h"
#include <formulas.h>

inherit "/std/weapon";

void create_weapon()
{
    set_name("scimitar");
    set_short("fine obsidian scimitar");
    set_long("The blade of this fine scimitar was elegantly carved from "+
        "obsidian. The handle is made of bone, and is ornamented in the "+
        "style of the Mikle Noth, an elvish tribe. The quality of "+
        "workmanship indicates that this was a blade designed by an elf, "+
        "for an elf.\n");
    set_adj("obsidian");
    add_adj("fine");

    set_hit(30);
    set_pen(24);
    likely_dull=5;
    likely_corr=0;
    likely_break=15;

    set_wt(W_SWORD);
    set_dt(W_SLASH);
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 6200);
    add_prop(OBJ_I_VOLUME, 2900);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(30,24)-random(100));
}
