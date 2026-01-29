/*  lotulis.c: The Trident of Lyden, revised by Serpine 11/23/95 
*   2010/09/17 Lavellan, commented out unnecessary query_keepable redefine
*   as it was preventing the file being compiled.
*
*   Recoded to be axe if wielded by gladiators, since it was an arena
*   gift. Meton 2020
*
*  2021-08-22 Meton Changed phurt misses to greater range
*      Tip from Cotillion to let it be larger in case more was added.
*   2021-11-07 Meton Added keep function
*/
 
#pragma strict_types  
 
inherit "/std/weapon";
#include <wa_types.h>
#include <ss_types.h>
#include "../local.h"

void
create_weapon()
{
    set_name("lotulis");
    set_adj("gigantic");
    add_adj("obsidian");
    set_short("gigantic obsidian lotulis");
    set_long("@@long_description");
    set_hit(47);
    set_pen(52);
    set_wt(W_POLEARM);
    set_dt(W_SLASH | W_IMPALE | W_BLUDGEON);
    set_hands(W_BOTH);
    set_wf(TO);
    add_prop(OBJ_M_NO_BUY, "I'll just keep that, sorry.");
    add_prop(OBJ_I_WEIGHT, 28000);
    add_prop(OBJ_I_VOLUME, 8000);
 
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({ 50, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO,
           ({"Only the mighty may wield this weapon.", 10,
             "This weapon was forged for the arena warrior: "
                +"Uncaring and strong.", 25,
             "A lethal weapon created for the neutral and "
                +"titanically strong to slay humans: "
                +"Truly this is Lyden's perfect weapon.", 50 }));
    add_prop(OBJ_S_WIZINFO,
             "Requires a 80 Strength, 50 Polearm, and alignment "
            +"from 500 to -500 to wield. Does x1.5 damage to humans. "
            +"Changes to axe (skill req too) if wielded by gladiator."
            +"Owned by Lyden (/d/Cirath/athas/a_tyr/npcs/lyden.c)");
    set_keep(1);

}


//nomask int query_keepable()  { return 1; }
 
int
did_hit(int aid, string hdesc, int phurt,
        object enemy, int dt, int phit, int dam)
{
    object me = ENV(TO);
 
    ::did_hit();
 
    if(enemy->query_race() != "human") return 0;
 
    enemy->heal_hp((-dam/2));
 
    if(enemy->query_hp()<=0)
    {
        me->catch_msg("You rip open the belly of "+QTNAME(enemy)
            +" with the dreaded Lotulis of Lyden, allowing "
            +HIS_HER(enemy)+" entrails to escape.\n");
        me->tell_watcher(QCTNAME(me)+" tears open the belly of "
            +QTNAME(enemy)+" with the Lotulis of Lyden.\n", enemy);
        enemy->do_die(query_wielded());
        return 1;
    }
 
    switch(phurt)
    {
      case -100..-1:
        me->catch_msg(QCTNAME(enemy)+" leaps to avoid your Lotulis.\n");
        enemy->catch_msg("You feel a wave of heat as you manage to leap "
            +"over the swipe of "+QTNAME(me)+"'s Obsidian Lotulis.\n");
        me->tell_watcher(QCTNAME(me)+" narrowly avoids lopping off "
            + "the foot "
            +"of "+QTNAME(enemy)+" with "+HIS_HER(me)+" Lotulis.\n",
            enemy);
        break;
      case 0..4:
        me->catch_msg("You tear a grissly path through the flesh of "
            +QTNAME(enemy)+"'s "+hdesc+" with the Obsidian Lotulis.\n");
        me->tell_watcher(QCTNAME(me)+" tears a grissly path through the flesh "
            +QTNAME(enemy)+"'s "+hdesc+" with "+HIS_HER(me)+" Lotulis.\n",
            enemy);
        enemy->catch_msg(QCTNAME(me)+" rips into your "+hdesc+" with the "
            +"Obsidian Lotulis of Lyden. The wound burns like fire.\n");
        break;
      case 5..8:
        me->catch_msg("You smashed the Lotulis so hard into "+
            HIS_HER(enemy)+" "+hdesc
            +", that "+QTNAME(enemy)+" staggers around numbly.\n");
        me->tell_watcher(QCTNAME(enemy)+" is staggered by the tremendous "
            +"overhead Lotulis strike of "+QTNAME(me)+".\n", enemy);
        enemy->catch_msg("Your "+hdesc+" feels numb from the devastating "
            +"overhead strike by the Lotulis of "+QTNAME(me)+".\n");
        break;
      case 9..16:
        me->catch_msg("You notice the skin on the "+hdesc+" of "
            +QTNAME(enemy)+" smoke where your Lotulis slices it.\n");
        me->tell_watcher("The "+hdesc+" skin of "
            +QTNAME(enemy)+" literally "
            +"smokes when struck by "+QTNAME(me)+".\n", enemy);
        enemy->catch_msg("You note with dismay that the wounds to your "
            +hdesc+" left by "+QTNAME(me)+" actually smoke.\n");
        break;
      case 17..32:
        me->catch_msg(QCTNAME(enemy)+" shakes violently from your blow.\n");
        me->tell_watcher("Struck in the "+hdesc+" by "+QTNAME(me)+", "
            +QTNAME(enemy)+" seems to shake violently.\n", enemy); 
        enemy->catch_msg("Your "+hdesc+" muscles spasm wildly when struck "
            +"by the super-hot Lotulis wielded by "+QTNAME(me)+".\n"); 
        break;
      case 33..64:
        me->catch_msg("You smell burning flesh as you slice through the "
            +hdesc+" of "+QTNAME(enemy)+".\n");
        me->tell_watcher("As "+QTNAME(me)+" slashes "+QTNAME(enemy)
            +" you smell burning flesh. How odd.\n", enemy);
        enemy->catch_msg("Your flesh ignites for a brief second as your "
            +hdesc+" is sliced by "+QTNAME(me)+".\n");
        break;
      default:
        me->catch_msg("The Obsidian Lotulis goes red hot as it contacts "
            +"the bones in the "+hdesc+" of "+QTNAME(enemy)+".\n");
        enemy->catch_msg("As "+QTNAME(me)+" rams his Lotulis into you, "
            +"it feels as if the bones of your "+hdesc+" are melting.\n");
        me->tell_watcher(QCTNAME(enemy)+" screams in burning agony as the "
            +"Lotulis of "+QTNAME(me)+" drives into "+HIS_HER(enemy)+" "+hdesc+".\n",
            enemy);
        break;
    }
 
    return 1; 
}

/*
*   Function name: wield
*   Description  : Changes weapon type if wielder is Gladiator.
*   Arguments    : 
*   Returns      : 
*/
mixed
wield(object ob)
{

    if (TP->query_guild_name_occ() == "Gladiator guild")
    {
        if((TP->query_alignment() < 500) && (TP->query_alignment() > -500) &&
        (TP->query_base_stat(SS_STR) > 79) &&
        (TP->query_skill(SS_WEP_AXE) > 49))
        {
            TO->set_wt(W_AXE);
            TO->set_dt(W_SLASH | W_BLUDGEON);
            write("The weapon makes you feel warm inside. You scan the "
                + "area for your next victim, wishing to test its "
                + "power.\n"
                + "As a gladiator, this weapon seems to suit your "
                + "training well.\n");
            return 0;
        }
    }
    TO->set_wt(W_POLEARM);

    if((TP->query_alignment() < 500) && (TP->query_alignment() > -500) &&
       (TP->query_base_stat(SS_STR) > 79) &&
       (TP->query_skill(SS_WEP_POLEARM) > 49))
    {
        write("The weapon makes you feel warm inside. You scan the area "
             +"for your next victim, wishing to test its power.\n");
        return 0;
    }
 
    TP->heal_hp(-(50 + random(100)));
    return "The lotulis burns your hands, leaving horrible scars.\n";
}

/*
*   Function name: unwield
*   Description  : Reverts weapon to polearm
*   Arguments    : 
*   Returns      : 
*/
mixed
unwield(object ob)
{
    TO->set_wt(W_POLEARM);
    TO->set_dt(W_SLASH | W_IMPALE | W_BLUDGEON);
    return 0;
}

/*
*   Function name: long_description
*   Description  : Varies description based on OCC guild.
*   Arguments    : 
*   Returns      : 
*/
string
long_description()
{
    if (TP->query_guild_name_occ() == "Gladiator guild")
    {
        write("This is the largest weapon you have EVER seen, easily "
            + "capable of skewering an inix. A recurved crescent blade, "
            + "made of obsidian, is mounted on each end of the long "
            + "shaft. It looks difficult to wield, yet incredibly lethal. "
            + "In fact, its blades seem warm to the touch.\n"
            + "This is a mighty gladiatorial weapon, and you know how "
            + "to handle it with the skills you have learned.\n");
        return "";
    }

    write("This is the largest weapon you have EVER seen, easily "
            + "capable of skewering an inix. A recurved crescent blade, "
            + "made of obsidian, is mounted on each end of the long "
            + "shaft. It looks difficult to wield, yet incredibly lethal. "
            + "In fact, its blades seem warm to the touch.\n");
    return "";
}