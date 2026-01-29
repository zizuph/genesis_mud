/*
 * By Korat
 *
 * Cotillion - 2006-04-20
 * - Fixed call of ::did-hit
 *
 * Petros - 2008-07-25
 * - Removed obsolete tell_watcher call.
 * Zignur - 2017-12-18 buffed hit and pen
 *
 *  2021-08-22 Meton Changed phurt misses to greater range
 *      Tip from Cotillion to let it be larger in case more was added.
 */

inherit "/d/Kalad/std/weapon.c";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by korat */

void
create_weapon()
{
    ::create_weapon();
    set_name("saber");
    add_name("sword");
    set_adj("adorned");
    add_adj("sharp");
    set_long("This saber, a slightly curved sword with two cutting edges "+
	     "is adorned with precious stones along the hilt. Being "+
	     "excellently forged, the stones helps the wielder rather than "+
	     "hinder, to have a good grip on it.\n");

    /* Zignur Buffed hit/pen */
    set_hit(35);
    set_pen(35);
    set_wt(W_SWORD);
    set_dt(W_SLASH);
    add_prop(OBJ_I_VALUE,1200);
    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VOLUME, 3000);
}

unwield(object what)
{
    if((E(TO)->id("urian")) && (E(TO)->query_hp() > 0))
    {
	tell_room(E(E(TO)), "The High Lord manages to hold onto "+
		  "the sword.\n", E(TO));
	return "The sword cannot be unwielded!";
    }
    return 0;
}

public mixed did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
    string mine_msg;
    string your_msg;
    string other_msg;
    object wielder = query_wielded();
   
    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    /* Change the combat messages */
    switch(phurt)
    {
    case -100..79:
	break;
    default:
	mine_msg="You salute "+QTNAME(enemy)+" with raising the saber in "+
	    "the air, and prepare to finnish "+enemy->query_possessive()+
	    " life.\n";
	your_msg=QCTNAME(wielder)+" raises the saber in the air and salutes "+
	    QTNAME(enemy)+", preparing for the final blow.\n";
	other_msg=QCTNAME(wielder)+" raises his saber in the air and "+
	    "salutes "+QTNAME(enemy)+", preparing for the final blow that will "+
	    "kill "+QTNAME(enemy)+".\n";
	wielder->catch_msg(mine_msg);
	enemy->catch_msg(your_msg);
	wielder->tell_watcher(other_msg,enemy);
	break;
    }
    return 0;
}


