/*
 * Common longsword for Imladris
 * By Finwe, February 2002
 */
inherit "/std/weapon";

#include "/d/Shire/sys/defs.h"
#include "../local.h"
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <filter_funs.h>
#include <composite.h>
#include <options.h>


//string long_func();

/*prototype*/

void
create_weapon()
{
    set_name(({"sword", "longsword"}));
    set_pname(({"swords", "longswords"}));
    set_adj("runed");
    set_adj("ancient");
    set_short("ancient runed longsword");
    //set_long("@@long_func@@");

    
	set_long("This longsword was forged by the elves of Imladris. " +
	    "It is made of steel and looks ancient. At the top of the " +
        "crossguard, intricate designs are etched onto the blade " +
        "and rise partway up the sword. The blade is long and " +
        "looks dangerous when wielded properly. The blade is " +
        "long and comes to a sharp point.\n");

    set_default_weapon(40,35, W_SWORD, W_SLASH | W_IMPALE, W_BOTH);
    set_wf(TO);


    add_prop(OBJ_I_VOLUME, 3600);
    add_prop(OBJ_I_WEIGHT, 11500);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(45,40)); /* magic sword */

    add_item(({"designs", "design", "intricate designs", 
            "intricate design", "fancy ornamentation", "flourishes"}),
      "The designs are flourishes and fancy ornamentation that " +
      "decorate the blade. They are very intricate and show great " +
      "skill by elven metalsmiths.\n");
    add_item(({"crossguard"}),
        "It is a horizontal bar at the base of the blade that " +
        "protects the wielder. The bar is curves upwards slightly.\n");
    add_item(({"handle"}),
        "The handle of the blade is long and made of dark wood. " +
        "It is slightly ridged to provide a good grip.\n");
    add_item(({"pommel"}),
        "The pommel of the sword extends from the base of the " +
        "handle. It is made of steel and is rounded.\n");
}

mixed 
wield(object weapon)
{
	write("You wield the longsword and prepare to defend yourself.\n");
	TP->tell_watcher(QCTNAME(TP) + " wields an elven longsword.\n");
	return 1;
}


mixed
unwield(object what)
{
    return 0;
}

public mixed 
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
    object wielder = query_wielded();
 
    switch(phurt)
    {
    case -1:
    case -2:
//        if (!wielder->query_option(OPT_GAG_MISSES))
            wielder->catch_msg("You lunge for "+QTNAME(enemy)+
            " but miss.\n");
//        if (!enemy->query_option(OPT_GAG_MISSES))
        enemy->catch_msg(QCTNAME(wielder)+" lunges for "+
            "you with " +HIS_HER(wielder)+" "+ short()+
            " but misses.\n");
        wielder->tell_watcher_miss(QCTNAME(wielder)+" lunges for "+
        QTNAME(enemy)+" but misses.\n",enemy);
        break;
    case 0:
        if (!wielder->query_option(OPT_GAG_MISSES))
            wielder->catch_msg("You barely miss "+QTNAME(enemy)+
              " with your "+short()+".\n");
        if (!enemy->query_option(OPT_GAG_MISSES))
            enemy->catch_msg(QCTNAME(wielder)+" barely misses you "+ 
              "with the "+short()+".\n");
        wielder->tell_watcher_miss(QCTNAME(wielder)+" swings the "+
            short()+" at "+QTNAME(enemy)+" and barely misses.\n",enemy);
        break;
    case 1..5:
        wielder->catch_msg("You rip open a shallow wound into the "+
          hdesc+" of the "+enemy->query_race_name()+" with "+
          "the "+short()+".\n");
        enemy->catch_msg("You feel a fresh wound open on your "+hdesc+
          " as the "+short()+" tears into you.\n");
        wielder->tell_watcher(QCTNAME(wielder)+" rips open a "+
          "shallow wound into the "+hdesc+" of "+QTNAME(enemy)+ 
          " with the "+short()+".\n",enemy);
        break;
    case 6..10:
        wielder->catch_msg("You hack chunks of flesh out "+
          "of the "+hdesc+" of the "+enemy->query_race_name()+
          " with the "+short()+".\n");
        enemy->catch_msg("You lose small chunks of flesh as the "+short()+
          " hacks into your "+hdesc+".\n");
        wielder->tell_watcher(QCTNAME(wielder)+" hacks small chunks of "+
          "flesh out of the "+hdesc+" of "+QTNAME(enemy)+" with the "+
          short()+".\n",enemy);
        break;
    case 11..20:
        wielder->catch_msg("Your "+short()+" rips into the "+hdesc+
          " of "+QTNAME(enemy)+", shredding flesh as it goes.\n");
        enemy->catch_msg("The flesh of your "+hdesc+" is shredded as the "+
          short()+" rips into it.\n");
        wielder->tell_watcher(QCTNAME(wielder)+" shreds the flesh on "+
          "the "+hdesc+" of "+QTNAME(enemy)+" with "+
          HIS_HER(wielder)+" "+short()+".\n",enemy);
        break;
    case 21..40:
        wielder->catch_msg("Your "+short()+" tears a deep wound "+
          "into the "+hdesc+" of the "+enemy->query_race_name()+".\n");
        enemy->catch_msg(QCTNAME(wielder)+" tears a deep "+
          "wound into your "+hdesc+" with "+HIS_HER(wielder)+
          " "+short()+".\n");
        wielder->tell_watcher(QCTNAME(wielder)+" tears a deep " +
            "wound into the "+hdesc+" of "+QTNAME(enemy)+
            " with the "+short()+ ".\n",enemy);
        break;
    case 41..60:
        wielder->catch_msg("Your "+short()+" shreds large "+
          "chunks of flesh from the "+hdesc+" of the "+
          enemy->query_race_name()+".\n");
        enemy->catch_msg(QCTNAME(wielder)+" shreds large chunks of "+
          "flesh from your "+hdesc+" with "+HIS_HER(wielder)+
          " "+short()+".\n");
        wielder->tell_watcher(QCTNAME(wielder)+" shreds large chunks of "+
          "flesh from the "+hdesc+" of "+QTNAME(enemy)+" with the "+
          short()+".\n",enemy);
        break;
    case 61..80:
        wielder->catch_msg("You plunge your "+short()+" into "+
          "the "+hdesc+" of the "+enemy->query_race_name()+". " +
          "Blood sprays all over you.\n");
        enemy->catch_msg(QCTNAME(wielder)+" plunges "+HIS_HER(wielder)+
            short()+" into your "+hdesc+". "+HE_SHE(wielder)+" pulls out "+
            HIS_HER(wielder)+short()+ " and gets sprayed by blood.\n");
        wielder->tell_watcher(QCTNAME(wielder)+" plunges "+
            HIS_HER(wielder)+short()+" into into the "+hdesc+" of the"+ 
            enemy->query_race_name()+". "+CAP(HE_SHE(wielder))+" pulls out "+
            HIS_HER(wielder)+short()+ " and gets sprayed by blood.\n");
        break;
    case 81..90:
        wielder->catch_msg("Your "+short()+" almost severs the "+
            hdesc+" of the "+enemy->query_race_name()+". Blood " +
            "sprays everywhere.\n");
        enemy->catch_msg("The "+short()+" almost severs your "+hdesc+
            ". Your blood sprays everywhere.\n");
        wielder->tell_watcher(QTNAME(wielder)+"'s "+short()+
            " almost severed "+QTNAME(enemy)+"'s "+hdesc+". " +
            "Blood sprays all over from the wound.\n");
        break;
    default:
        wielder->catch_msg("In one fell swoop, you raise your " +
            short()+" above your head and send it crashing onto "+
            "the "+hdesc+" of the "+enemy->query_race_name()+
            ", killing "+HIM_HER(enemy)+" instantly.\n");
        enemy->catch_msg(QCTNAME(wielder)+" crashes "+
            HIS_HER(wielder)+short()+" into your "+hdesc+
            ", killing you.\n");
        wielder->tell_watcher(QTNAME(wielder)+" raises "+
            HIS_HER(wielder)+" " +short()+" high above "+
            HIS_HER(wielder)+" head and sends it crashing down " +
            "onto the "+hdesc+" of the "+enemy->query_race_name()+
            ", killing "+HIM_HER(enemy)+" instantly.\n");
        break;
    }
    return 1;
}

