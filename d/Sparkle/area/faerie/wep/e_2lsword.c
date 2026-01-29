/*
 * Two-handed Longsword for elf npcs
 * by Finwe, August 2004
 */
#pragma save_binary
#pragma strict_types

inherit "/std/weapon";
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <macros.h>
#include "defs.h"

//string long_func();

int hit  = 30,
    pen  = 35,
    nhit = 29,
    npen = 29;
string adj1 = "polished",
       adj2 = "bright",
       wep  = "longsword"; 

#define DEBUG_WHO find_player("finwe")

#undef DEBUG_WHO
#ifdef DEBUG_WHO
#define DEBUG(s)  DEBUG_WHO->catch_msg(s + "\n")
#else
#define DEBUG(s)
#endif

#define IS_CADET(x)    ((x)->query_guild_name_lay() == "Cadets of Gelan") 
#define NPC_SUBLOC   "_elf_ears"

void
create_weapon()
{
    set_name("sword");
    add_name("longsword");
    add_adj(adj1);
    add_adj(adj2);
    set_short(adj1 + " " + adj2 + " " + wep);
    set_long("This " + short() + " is was forged by elves. It is wielded " +
        "by their guards in defending their lands. The extremely sharp " +
        "blade is made from steel, but it seems unusually lighter than " +
        "normal.\n");

    set_hit(hit);
    set_pen(pen);
    set_likely_dull(4);
    set_likely_corr(1);
    set_likely_break(1);

    add_prop(OBJ_I_WEIGHT,2000);
    add_prop(OBJ_I_VOLUME,950);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(hit,pen)+random(200));
    add_prop(MAGIC_AM_MAGIC,({60,"enchantment"}));
    add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
    add_prop(OBJ_S_WIZINFO,"The "+short()+" will have a greater hit/pen " +
        "when wielded by cadets. Otherwise, the weapon uses nhit and npen " +
        "values.\n"); 
    set_wt(W_SWORD); 
    set_dt(W_SLASH | W_IMPALE); 

    set_hands(W_BOTH); 

    set_wf(TO);
}

mixed
wield(object wep)
{
    if (IS_CADET(TP)) 
    {
	    TO->set_hit(hit);
	    TO->set_pen(pen);
    }
    else 
    {
	    TO->set_hit(nhit);
	    TO->set_pen(npen);
    }
    
    write("You wield the "+short()+".\n");
    tell_room(ENV(TP),QCTNAME(TP)+" wields the "+short()+".\n",TP);

    return 1;
}

mixed
unwield(object wep)
{
    
    TO->set_hit(nhit);
	TO->set_pen(npen);

    write("You unwield the "+short()+".\n");
    tell_room(ENV(TP),QCTNAME(TP)+" unwields the "+short()+".\n",TP);

    return 1;
}

