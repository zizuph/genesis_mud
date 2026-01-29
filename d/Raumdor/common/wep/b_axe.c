inherit "/std/weapon";
#include "/d/Raumdor/defs.h"

/* Sarr */


void
create_weapon()
{
    ::create_weapon();
    set_name("battleaxe");
    set_adj("lochaber");
    add_adj("black");
    set_short("black lochaber battleaxe");
    set_long("This is a very nasty looking axe. The blade is made out "+
    "of some pure black steel, and it curves back into nasty, sharp "+
    "points. There are barbs along the edges to cause more pain to "+
    "an enemy than damage. The wooden haft looks old, and there are "+
    "are black iron bands wraped around it.\n");
    set_dt(W_SLASH);
    set_wt(W_AXE);
    set_hit(24);
    set_pen(30);
    add_prop(OBJ_I_WEIGHT,7000);
    add_prop(OBJ_I_VOLUME,4000);
    add_prop(OBJ_I_VALUE,500);
}
