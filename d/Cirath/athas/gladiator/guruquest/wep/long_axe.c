/* This is the weapon Derryn wields when there are too many  
   enormous obsidian battleaxes already within the game.
   Code (c) 1998 Damian Horton
   Updated for Raumdor, March 2001.
*/

#pragma strict_types 
#pragma save_binary

#include "/sys/wa_types.h"
#include <formulas.h>
#include "/d/Cirath/defs.h"

inherit "/std/weapon";

void create_weapon()
{
    set_name("battleaxe");
    add_name("axe");
    set_short("long-handled obsidian battleaxe");
    set_long("This weapon consists of a long thick shaft of "+
        "agafari wood which supports a finely carved blade of "+
        "glossy obsidian. The unusually long handle provides "+
        "the wielder of this weapon with great range, though "+
        "it also necessitates the use of two hands.\n");

    set_adj("long-handled");
    add_adj("obsidian");
    add_adj("battle");

    set_hit(38);
    set_pen(38);
    likely_dull=17;
    likely_corr=1;
    likely_break=15;

    set_wt(W_AXE);
    set_dt(W_SLASH|W_BLUDGEON);
    set_hands(W_BOTH);

    add_prop(OBJ_I_WEIGHT, 12900);
    add_prop(OBJ_I_VOLUME, 9900);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(38,38) - random(100) +
	     random(100));
}





