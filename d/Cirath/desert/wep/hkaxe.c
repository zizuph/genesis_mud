inherit "/std/weapon";
#include <wa_types.h>
#include <ss_types.h>
#include "/d/Cirath/common/defs.h"

void
create_weapon()
{
    set_name("axe");
    set_adj("executioner's");
    set_short("executioner's axe");
    set_long("Extending from a long wooden shaft wrapped in sweat "
        +"stained leather is a massive axe head.  The blade of this "
        +"weapon is attached near the end of the haft by a thick "
        +"piece of sturdy steel.  The blade itself extends outward "
        +"from the handle at a 90 degree angle for about a foot before "
        +"turning 90 degrees downward and finally gently sloping "
        +"back towards the handle, where it ends 8 inches above the "
        +"grip.  The central portion of the blade "
        +"has been cut out to reduce weight and cost, but it looks "
        +"very durable, and very sharp.  Protruding from the back of "
        +"the haft is a narrow spike which looks like it could easily "
        +"pierce armour.  This axe has been crafted in the style used "
        +"by headsmen the world round, but with more thought to "
        +"usefulness in combat.\n");
    set_hit(42);
    set_pen(48);
    set_wt(W_AXE);
    set_dt(W_SLASH);
    set_hands(W_ANYH);
    set_wf(TO);
    add_prop(OBJ_M_NO_BUY, "I don't think so bub.");
    add_prop(OBJ_I_WEIGHT, 4000);
    add_prop(OBJ_I_VOLUME, 2000);

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({ 50, "psionics" }));
    add_prop(OBJ_S_WIZINFO,
             "Requires a 130 DEX and DIS as well as a 90 axe skill."
             +" It does double damage to humans.");
}

varargs void
tell_watcher(string str, object enemy, mixed arr)
{
    object *ob;
    int i, size;
    object me = ENV(TO);

    ob = all_inventory(environment(me)) - ({ me, enemy });

    if (arr)
    {
        if (pointerp(arr))
            ob -= arr;
        else
            ob -= ({ arr });
    }

    i = -1;
    size = sizeof(ob);
    while(++i < size)
    {
        if (ob[i]->query_see_blood() && CAN_SEE_IN_ROOM(ob[i]))
        {
            if (CAN_SEE(ob[i], me))
                ob[i]->catch_msg(str);
            else
                tell_object(ob[i], enemy->query_The_name(ob[i]) +
                    " is hit by someone.\n");
        }
    }
}

int
did_hit(int aid, string hdesc, int phurt,
        object enemy, int dt, int phit, int dam)
{
    object me = ENV(TO);

    ::did_hit();

    if(enemy->query_race_name() != "human") return 0;

    enemy->heal_hp(-dam);

    if(enemy->query_hp()<=0)
    {
        me->catch_msg("You wickedly split open the belly of "+QTNAME(enemy)
            +", spilling " +HIS_HER(enemy)+" insides across the ground.\n");
        tell_watcher(QCTNAME(me)+" cleanly slices the stomach of "
            +QTNAME(enemy)+", spilling "+ HIS_HER(enemy) +" innards.\n",
	    enemy);
        enemy->do_die(query_wielded());
        return 1;
    }

    switch(phurt)
    {
      case -1:
        me->catch_msg(QCTNAME(enemy)+" deftly sidesteps your blow.\n");
        enemy->catch_msg("You quickly dodge to the side as  "+QTNAME(me)
      +"'s axe sweeps towards you.\n");
     tell_watcher(QCTNAME(me)+" swings "+ HIS_HER(me)+" axe "
            +"powerfully at "
            +QTNAME(enemy)+", barely missing.\n", enemy);
        break;
      case 0..4:
        me->catch_msg("You slice weakly into "
            +QTNAME(enemy)+"'s "+hdesc+" with the executioner's axe.\n");
        tell_watcher(QCTNAME(me)+" slices weakly into "
            +QTNAME(enemy)+"'s "+hdesc+" with "+HIS_HER(me)+" axe.\n",
            enemy);
        enemy->catch_msg(QCTNAME(me)+" slices into your "+hdesc+" weakly, "
            +"opening a small wound.\n");
        break;
      case 5..8:
        me->catch_msg("You slam your executioner's axe heavily into the "+hdesc
            +" of "+QTNAME(enemy)+". Blood sprays from the wound, splashing "
            +"on your clothes.\n");
        tell_watcher(QCTNAME(enemy)+" grunts in pain as the huge axe wielded "
            +"by "+QTNAME(me)+" slams into "+HIS_HER(enemy)+" "+hdesc+".\n",
	    enemy);
     enemy->catch_msg("Pain explodes in your "+ hdesc +" as "+QTNAME(me)+
            "slams "+ HIS_HER(me)+" executioner's axe into it.\n");
        break;
      case 9..16:
              me->catch_msg(QCTNAME(enemy) + " reels as your massive "
	    +"executioner's "
            +"axe brutally smashes into "+ HIS_HER(enemy) + " "
            +hdesc+".\n");
        tell_watcher(QCTNAME(enemy)+" is staggered by a brutal swing of "
            +QTNAME(me)+"'s massive executioner's axe.\n", enemy);
        enemy->catch_msg("You stagger backwards as "+QTNAME(me)+"'s "
            +"heavily smashes into your "+hdesc+".\n");
        break;
      case 17..32:
        me->catch_msg("Your executioner's axe sinks deep into the "+hdesc+
            " of "+ QTNAME(enemy)+", sending thick streams of blood flying "
            +"through the air.\n");
    tell_watcher(QCTNAME(me)+"'s axe sinks deep into the "+hdesc+" of "
            +QTNAME(enemy)+", sending deep red blood flying through the "
            +"air.\n", enemy);
        enemy->catch_msg("You see your own blood spraying through the air "
            +"as the huge executioner's axe wielded by "+QTNAME(me)+
            " sinks deeply into your "+hdesc+".\n");
        break;
      case 33..64:
        me->catch_msg("The huge axe buries itself deeply in the "
            +hdesc+" of "+QTNAME(enemy)+", becoming slightly stuck "
            +"in "+ HIS_HER(enemy)+" mutilated flesh.\n");
        tell_watcher(QCTNAME(me)+" buries "+ HIS_HER(me) +" axe deeply "
            +"into the "+hdesc+" of "+ QTNAME(enemy)+" mutilating the "
            +"tissue there.\n", enemy);
        enemy->catch_msg(QCTNAME(me) +" buries "+ HIS_HER(me) +
            " executioner's axe deep into your "+hdesc+" getting it "
            +"slightly stuck before ripping it free of your mangled "
            +"flesh.\n");
        break;
      default:
        me->catch_msg("There is the sickening crack of bones breaking "
            +"as you embed your executioner's axe into the "+hdesc+" of "
            +QTNAME(enemy)+".\n");
        enemy->catch_msg("You feel the bones in your "+hdesc+" shatter "
            +"as "+ QTNAME(me) +" embeds "+HIS_HER(me)+" executioner's "
            +"axe in it.\n");
        tell_watcher("You hear the snapping of bones as the massive "
            +"executioner's axe wielded by "+ QTNAME(me) +" embeds "
            +"itself deep in the "+hdesc+" of "+QTNAME(enemy)+".\n",
            enemy);
        break;
    }

    return 1;
}

mixed
wield(object ob)
{
    if((TP->query_base_stat(SS_DEX) > 129) &&
       (TP->query_base_stat(SS_DIS) > 129) &&
       (TP->query_skill(SS_WEP_AXE) > 89))
    {
        write("As you wield the executioner's axe, your vision turns "
                +"scarlet for a moment, and a voice whispers into "
                +"your mind: 'Kill them all.....', and fades just as "
                +"quickly as it appeared.\n");
     say(QCTNAME(TP)+" gets a faraway look in his eye as he wields "
                +"the executioner's axe.  It almost looks as if he is "
                +"listening to some sort of inner voice.\n");
        return 1;
    }
    TP->add_panic(300 + random(100));
    return "Paranoia sets in as you fail to wield the executioner's axe.\n";
}


public mixed
unwield(object wep)
{
   object wr = TO->query_wielded();
   wr->catch_tell("You hesitantly unwield the executioner's axe, "
        +"your confidence fading without its power.\n");
   wr->add_panic(150);
    return 1;
}

