/*
* Created by: Luther
* Date: Jan 2002
*
* File: /d/Cirath/tyr/wep/guard_spear.c
* Comments: A spear...
*/

#pragma strict_types 
#pragma save_binary

inherit "/std/weapon";
#include "defs.h"
#include "/sys/wa_types.h"
#include <formulas.h>

void create_weapon()
{
    set_name("spear");
    add_name("polearm");
    set_short("bone-bladed spear");
    set_long("The blade of this crude spear is made of sharpened "+
        "bone. Though neither as strong nor as sharp as steel, it "+
        "is still capable of inflicting mortal wounds.\n");
        
    set_adj("bone-bladed");
    add_adj("bone");
    add_adj("bladed");
    
    set_hit(23);
    set_pen(26);


    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT,3450);
    add_prop(OBJ_I_VOLUME, 2990);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(21,14));
}