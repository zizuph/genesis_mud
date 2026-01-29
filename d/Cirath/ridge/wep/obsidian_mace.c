/* A standard weapon for patrolling guards in the employ of Kalak. 
   Code (c) 1998 to Damian Horton (aka Dethraine).
*/
#pragma strict_types 
#pragma save_binary

inherit "/std/weapon";
#include "defs.h"
#include "/sys/wa_types.h"
#include <formulas.h>

void create_weapon()
{
    set_name("mace");
    set_short("ordinary obsidian mace");
    set_long("This ordinary weapon consists of a carefully "+
        "crafted, heavy, hunk of obsidian attached to a bone "+
        "handle. This makes for a crude, but effective weapon.\n");
        
    set_adj("obsidian");
    add_adj("ordinary");

    set_hit(28);
    set_pen(21);
    likely_dull=2;
    likely_corr=0;
    likely_break=15;

    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 7200);
    add_prop(OBJ_I_VOLUME, 2230);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(28,21)-random(100));
}
