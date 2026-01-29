/*
 * Mace for the the Insectmen of Kryptgarden
 * by Finwe, July 2005
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

#define ADJ1        "brilliant"
#define ADJ2        "silvery"
#define WEAPON      "mace"
#define WEP_TYPE    W_CLUB
#define DAMAGE      W_BLUDGEON | W_IMPALE



int hit = 35,
    pen = 35;
    
void
create_faerun_weapon()
{

    set_name("club");
    add_name(WEAPON);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + WEAPON); 
    set_long("This is a " + short() + ". The " + WEAPON + " was forged by ancient dwarves and plundered from one of their hordes. The mace shines with an inner light. Its broad head is studded, and its hilt is wrapped in white, cut leather. A thong hangs from the base of its handle.\n");

    add_item(({"thong"}),
        "It is double looped and hangs from the base of the handle. It is made of a strip of white leather.\n");
    add_item(({"head"}),
        "The head is a round ball and covered with studs.\n");
    add_item(({"handle", "hilt"}),
        "It is made of smooth wood and wrapped in white, cut leather.\n");
    add_item(({"leather", "white cut leather"}),
        "The leather is tanned and smooth. It is wrapped around the hilt and provides the wielder a good grip on the handle.\n");
    

    set_hit(hit);
    set_pen(pen);
    set_wt(WEP_TYPE); 
    set_dt(DAMAGE); 

    add_prop(OBJ_I_WEIGHT,2500);
    add_prop(OBJ_I_VOLUME,1500);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(hit,pen));

    set_hands(W_ANYH); 
}
