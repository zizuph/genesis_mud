 
/* graveyard/wep/phantom_blade.c  is clone by graveyard/npc/phantom_knight.c */
 
inherit "/std/weapon";
 
#include <wa_types.h>
#include <formulas.h>
#include "/d/Emerald/defs.h"
#include <tasks.h>
 
 
void
create_weapon()
{
 
    if(!IS_CLONE)
        return;
 
    set_name("blade");
    set_long( "A long narrow blade, with strange ancient runes "+
        "carved along it. It seems to radiate some kind of magical power.\n"
         );
    set_adj("phantom");
 
    add_item(({"runes","rune"}),"@@rune_description");
 
    set_hit(28);  /* stats of a good broadsword + a bit for magic property */
    set_pen(33);
 
    set_wt(W_SWORD);
    set_dt(W_SLASH);
 
    set_hands(W_RIGHT);
 
    add_prop(OBJ_I_VOLUME,7500);
    add_prop(OBJ_I_WEIGHT,3000);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(28,33) - random(100) + 200);
 
}
 
 
string
rune_description()
{
    int success;
 
    success = this_player()->resolve_task(TASK_DIFFICULT, ({TS_INT,
        SS_LANGUAGE}));
 
    if (success < 0)
        return  "You study the runes carefully, but you cannot "+
            "decipher them.\n" ;
 
    return  "The runes look like the kind used to give special "+
        "powers to weapons, and bless the warrior using it with luck during "+
        "battles.\n" ;
}
