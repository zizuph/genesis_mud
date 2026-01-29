/*
 * Oleson's Hammer, Phlan blacksmith
 * Tharizdun 2021
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

#define ADJ1        "heavy"
#define ADJ2        "two-handed"
#define WEAPON      "warhammer"
#define WEP_TYPE    W_CLUB
#define DAMAGE      W_BLUDGEON



int hit = 37 + random(5),
    pen = 40 + random(5);
void
create_faerun_weapon()
{

    set_name("club");
    add_name(WEAPON);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + WEAPON); 
    set_long("This is a " + short() + ". If there is a line between"
       +" warhammer and maul, this hammer toes that line. The oversized"
       +" handle would be nearly impossible to use one-handed for anything"
       +" smaller than an adolescent hill giant. The head is dense tempered"
       +" steel and heavy. It bears the mark of Oleson of Phlan.\n");

    set_hit(hit);
    set_pen(pen);
    set_wt(WEP_TYPE); 
    set_dt(DAMAGE); 

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(pen,W_SWORD)+random(50)-25);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(hit, pen)+random(20)-10);

    set_hands(W_BOTH); 
}
