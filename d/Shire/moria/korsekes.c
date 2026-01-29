    
#pragma save_binary

inherit "/std/weapon";
inherit "/lib/keep";

#include <stdproperties.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include "/d/Shire/sys/defs.h"

#define WEAPON_HIT 50
#define WEAPON_PEN 48


void create_weapon()
{

    set_name("korsekes");
    set_adj("nasty");
    set_short("nasty korsekes");
    set_long("A nasty spear with two outer prongs set at a 45 " +
      "degree angle in order to catch and deflect the enemy's weapon. " +
      "The tip has three barbs designed to tear flesh when it " +
      "is withdrawn.\n");

    set_hit(WEAPON_HIT);
    set_pen(WEAPON_PEN);

    set_wt(W_POLEARM);
    set_dt(W_SLASH|W_IMPALE);

    set_hands(W_BOTH);
    set_wf(this_object());

    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_WEIGHT,  1200);
    add_prop(OBJ_I_VOLUME,  1200);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(WEAPON_HIT, WEAPON_PEN) +
      (90+random(21)) / 100);

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1); /* it is magic */
    add_prop(MAGIC_AM_MAGIC,({ 10, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO,({"This korsekes radiates an evil magic.\n",1,
    "It withdraws the magic energy from enemies.\n",25,
    "It can be used to feign an attack, tricking your enemy into attacking you.\n",66 }));
    set_keep();
}


public mixed 
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
    object wielder = query_wielded();

    switch(phurt)
    {
    case -1:
    case -2:
	wielder->catch_msg("You jab the "+short()+" but it "+
	  "misses completely.\n");
	enemy->catch_msg(QCTNAME(wielder)+" jabs the "+short()+ 
	  " but it misses you completely.\n");
	wielder->tell_watcher(QCTNAME(wielder)+" jabs the "+short()+
	  " at "+QTNAME(enemy)+", but misses.\n",enemy);
	break;
    case 0:
	wielder->catch_msg("You narrowly miss "+QTNAME(enemy)+
	  " with your "+short()+".\n");
	enemy->catch_msg(QCTNAME(wielder)+" narrowly misses you "+ 
	  "with the "+short()+".\n");
	wielder->tell_watcher(QCTNAME(wielder)+" jabs the "+short()+
	  " at "+QTNAME(enemy)+" and narrowly misses.\n",enemy);
	break;
    case 1..5:
	wielder->catch_msg("You poke a hole into the "+
	  hdesc+" of the "+enemy->query_race_name()+" with "+
	  "the "+short()+".\n");
	enemy->catch_msg("You feel a hole open on your "+hdesc+
	  " as the "+short()+" jabs into you.\n");
	wielder->tell_watcher(QCTNAME(wielder)+" pokes a small hole "+
	  "into the "+hdesc+" of "+QTNAME(enemy)+" with the "+short()+
	  ".\n",enemy);
	break;
    case 6..10:
	wielder->catch_msg("You tear small piece of flesh out "+
	  "of the "+hdesc+" of the "+enemy->query_race_name()+
	  " as you withdraw the "+short()+".\n");
	enemy->catch_msg("You lose small chunks of flesh as the "+short()+
	  " tears into your "+hdesc+".\n");
	wielder->tell_watcher(QCTNAME(wielder)+" tears small chunks of "+
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
	wielder->tell_watcher(QCTNAME(wielder)+" tears a deep wound into "+
	  "the "+hdesc+" of "+QTNAME(enemy)+" with the "+short()+
	  ".\n",enemy);
	break;
    case 41..60:
	wielder->catch_msg("Your "+short()+" tears large "+
	  "chunks of flesh from the "+hdesc+" of the "+
	  enemy->query_race_name()+".\n");
	enemy->catch_msg(QCTNAME(wielder)+" tears large chunks of "+
	  "flesh from your "+hdesc+" with "+HIS_HER(wielder)+
	  " "+short()+".\n");
	wielder->tell_watcher(QCTNAME(wielder)+" tears large chunks of "+
	  "flesh from the "+hdesc+" of "+QTNAME(enemy)+" with the "+
	  short()+".\n",enemy);
	break;
    case 61..80:
	wielder->catch_msg("Your "+short()+" leaves nothing but "+
	  "ribbons of flesh hanging from the "+hdesc+" of "+
	  "the "+enemy->query_race_name()+".\n");
	enemy->catch_msg(QCTNAME(wielder)+" reduces the "+
	  "flesh of your "+hdesc+" to mere ribbons with "+
	  HIS_HER(wielder)+" "+short()+".\n");
	wielder->tell_watcher(QCTNAME(wielder)+" reduces the flesh "+
	  "of the "+hdesc+" of "+QTNAME(enemy)+" to ribbons with the "+
	  short()+".\n",enemy);
	break;
    case 81..90:
	wielder->catch_msg("Your "+short()+" almost tore "+
	  "through the "+hdesc+" of the "+enemy->query_race_name()+".\n");
	enemy->catch_msg("The "+short()+" almost tore right through "+
	  "your "+hdesc+".\n");
	wielder->tell_watcher("The "+short()+" wielded by "+QTNAME(wielder)+
	  " almost tore through the "+hdesc+" of "+QTNAME(enemy)+
	  ".\n",enemy);
	break;
    default:
	wielder->catch_msg("Blood spurts like a geiser as "+
	  "your "+short()+" punctures the "+hdesc+" of the "+
	  enemy->query_race_name()+".\n");
	enemy->catch_msg("Your "+hdesc+" is punctured when the "+short()+
	  " gouges into it, spouting blood like a geiser.\n");
	wielder->tell_watcher("You gag as the "+short()+
	  " wielded by "+QTNAME(wielder)+" punctures "+
	  "the "+hdesc+" of "+QTNAME(enemy)+", showering you with blood.\n",enemy);
	break;
    }
    
    if (phurt > 0)
    {
	drain_me(enemy,dam/3);
    }
    
    return 1;
}

int try_hit(object enemy)
{
    int skill, stat, skill_e, stat_e, pen, perf, pdam;
    mixed *hitresult;
    object me, enmy;
    string text, ptext;

    me = query_wielded();
    enmy = me->query_enemy();
    skill = me->query_skill(SS_WEP_POLEARM);
    stat = me->query_stat(SS_STR);
    skill_e = enemy->query_skill(SS_DEFENCE);
    stat_e = enemy->query_stat(SS_DEX);

    // We want to cap the stat at around 100 if the stats get too
    // high (above 110)
    if (stat > 110)
        stat = 90 + random(20);
    if (stat_e > 110)
        stat_e = 90 + random(20);


    if ((random(100) < (skill/2)) &&
      (random(skill+stat) > random(skill_e+stat_e)))
    {
    pen = F_PENMOD(40+random(stat/4), skill);
    hitresult = enemy->hit_me(pen, W_IMPALE, me, -1);
    perf = hitresult[2] * 100 / pen;
    pdam = hitresult[0];
    
    if (enemy->query_hp() <= 0)
    {
        enemy->do_die(me);
        return 0;
    }
    }
    return 1; /* Try hit */
}

string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + query_keep_recover();
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
    init_keep_recover(arg);
}
    