/* 
 *  A small tree trunk for trolls to wield.
 *  /d/Gondor/ithilien/emyn-arnen/obj/tree_trunk.c
 *  Spring 2004 by Serif
 */

#pragma strict_types

inherit "/std/weapon.c";
inherit "/lib/keep.c";

#include <formulas.h>
#include <macros.h>
#include <ss_types.h>  
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"

public void
create_weapon()
{
    set_name(({"club", "cudgel", "weapon", "trunk"}));
    set_pname("cudgels");
    add_pname("clubs");
    add_pname("trunks");
    set_short("knotted tree trunk");
    set_pshort("knotted tree trunks");
    set_long("This is the knotted trunk of a tree.\n");
    set_adj(({"knotted", "tree"}));
    set_default_weapon(30, 40, W_CLUB,
         W_BLUDGEON, W_BOTH, 0);
    set_likely_corr(0);
    set_likely_dull(0);
    set_likely_break(5);
    add_prop(OBJ_I_WEIGHT,97500+random(5000));
    add_prop(OBJ_I_VOLUME,29500+random(1000));
    add_prop(OBJ_I_VALUE, 100);

    set_wf(TO);
}

public mixed 
wield(object wep)
{
    if(TP->query_stat(SS_STR) < 175)   
    {     
    TP->catch_msg("You are not strong enough to wield this tree trunk.\n");
    return -1;
    }

    if(TP->query_race_name() == "troll")
    {
        TP->catch_msg("You heft the knotted tree trunk "+
            "in both your hands.\n");
        say(QCTNAME(TP) + " hefts " + TP->query_possessive() + " " + short() + " "
            + "in both hands.\n");
        set_hit(40 + (wielder->query_stat(SS_DEX) / 10));
        set_pen(40 + (wielder->query_stat(SS_STR) / 10));
        TP->update_weapon(TO);
        return 1;
    }

    else 
    return;
}

public int
unwield(object wep)  
{
        WRITE("You release your "+short()+".");
        say(QCTNAME(TP) + " releases " + TP->query_possessive() + " " 
            + short() + ".");
        TO->set_pen(40);
        TO->set_hit(30);
    return 1;
}

