/* l_triden.c: The Trident of Lyden, revised by Milashk 08/20/01 */

#pragma strict_types

inherit "/std/weapon";
#include <wa_types.h>
#include <ss_types.h>
#include "defs.h"

void
create_weapon()
{
    set_name(({"lotulis", "trident"}));
    set_adj("gigantic");
    add_adj("obsidian");
    set_short("gigantic obsidian lotulis");
    set_long("This is the largest weapon you have EVER seen, easily "
            +"capable of skewering an inix. A recurved crescent blade, "
            +"made of obsidian, is mounted on each end of the long "
            +"shaft. It looks difficult to wield, yet incredibly lethal. "
            +"In fact, its blades seem warm to the touch.\n");
    set_hit(40);
    set_pen(40);
    set_wt(W_POLEARM);
    set_dt(W_SLASH | W_IMPALE | W_BLUDGEON);
    set_hands(W_BOTH);
    set_wf(TO);
    add_prop(OBJ_M_NO_BUY, "I'll just keep that, sorry.");
    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VOLUME, 3000);

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({ 50, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO,
           ({"Only the mighty may wield this weapon.", 10,
             "This weapon was forged for the arena warrior: "
             +"Uncaring and strong.", 25,
             "A lethal weapon created for the most disciplined and "
            +"titanically strong wielder, made specifically to slay "
            +"humans: Truly this is Lyden's perfect weapon.", 50 }));
    add_prop(OBJ_S_WIZINFO,
	"Requires a 100 Strength and Discipline and 50 "+
	"polearm to wield."
            +" Does x1.5 damage to humans. "
            +"Owned by Lyden (/d/Cirath/athas/a_tyr/npcs/lyden.c)");
}

nomask int query_keepable()  { return 1; }

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
      case -1:
        me->catch_msg(QCTNAME(enemy)+" leaps to avoid your Lotulis.\n");
        enemy->catch_msg("You feel a wave of heat as you manage to leap "
            +"over the swipe of "+QTNAME(me)+"'s Obsidian Lotulis.\n");
        me->tell_watcher(QCTNAME(me)+" narrowly avoids lopping off the foot "
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
        me->catch_msg("You smashed the Lotulis so hard into "+HIS_HER(enemy)+
    hdesc+", that "+QTNAME(enemy)+" staggers around numbly.\n");
        me->tell_watcher(QCTNAME(enemy)+" is staggered by the tremendous "
            +"overhead Lotulis strike of "+QTNAME(me)+".\n", enemy);
        enemy->catch_msg("Your "+hdesc+" feels numb from the devastating "
            +"overhead strike by the Lotulis of "+QTNAME(me)+".\n");
        break;
      case 9..16:
        me->catch_msg("You notice the skin on the "+hdesc+" of "
            +QTNAME(enemy)+" smoke where your Lotulis slices it.\n");
        me->tell_watcher("The "+hdesc+" skin of "+QTNAME(enemy)+" literally "
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
   +"Lotulis of "+QTNAME(me)+" drives into "+HIS_HER(enemy)+
   hdesc+".\n",enemy);
        break;
    }

    return 1;
}

mixed
wield(object ob)
{
   if((TP->query_base_stat(SS_STR) > 99) &&
      (TP->query_base_stat(SS_DIS) > 99) &&
       (TP->query_skill(SS_WEP_POLEARM) > 49))
    {
        write("The weapon makes you feel warm inside. You scan the area "
             +"for your next victim, wishing to test its power.\n");
        return 0;
    }

    TP->heal_hp(-(50 + random(100)));
    return "The lotulis burns your hands, leaving horrible scars.\n";
}


