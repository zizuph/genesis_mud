inherit "/std/weapon";
#include <wa_types.h>
#include <ss_types.h>
#include "defs.h"

void
create_weapon()
{
    set_name("axe");
    set_adj("mithril");
    add_adj("razor-edged");
    set_short("mithril razor-edged axe");
    set_long("This axe is etched in gold runes, and its mithril "
      +"head is sharp enough to shave with. The haft is crafted "
      +"from what looks to be a rib from a giant. Worn leather "
      +"wrappings cover the end of the rib and form it into what "
      +"appears to be a well used grip. This is truly a magnificent "
      +"weapon.\n");
   add_item(({"runes","golden runes"}),"The runes shine with a "
        +"bright mystical glow.\n");
    set_hit(40);
   set_pen(35);
    set_wt(W_AXE);
    set_dt(W_SLASH);
     set_hands(W_ANYH);
    set_wf(TO);
    add_prop(OBJ_M_NO_BUY, "I'll just keep that, sorry.");
   add_prop(OBJ_I_WEIGHT, 20000);
    add_prop(OBJ_I_VOLUME, 4000);

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({ 50, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO,
           ({"This weapon is made of a mystical bend of metals.", 10,
            "It has been enchanted to give penalties against most "
            +"races found in Athas and other worlds.", 25,
             "It is a lethal weapon made for warriors with the "
            +"strength and constitution of an immortal. "
            +"In the right hands, this is a weapon of immense power.", 50 }));
    add_prop(OBJ_S_WIZINFO,
                "Requires a 175 STR and CON as well as a 90 axe skill."
  +" It also does double damage to all races except humans.");
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

    if(enemy->query_race_name() == "human") return 0;

    enemy->heal_hp(-dam);

    if(enemy->query_hp()<=0)
    {
        me->catch_msg("You slam your axe down upon the head of "+QTNAME(enemy)
            +" cleaving "
            +HIS_HER(enemy)+" head in two.\n");
        tell_watcher(QCTNAME(me)+" cleaves the head of "
            +QTNAME(enemy)+" in half with his axe.\n", enemy);
        enemy->do_die(query_wielded());
        return 1;
    }

    switch(phurt)
    {
      case -1:
        me->catch_msg(QCTNAME(enemy)+" barely avoids your axe.\n");
        enemy->catch_msg("You feel the air move as "+QTNAME(me)
      +"'s axe barely misses you.\n");
        tell_watcher(QCTNAME(me)+" barely misses the body of "
            +QTNAME(enemy)+" with "+HIS_HER(me)+" axe.\n",
            enemy);
        break;
      case 0..4:
        me->catch_msg("You make a small slit in "
            +QTNAME(enemy)+"'s "+hdesc+" with the mithril axe.\n");
        tell_watcher(QCTNAME(me)+" makes a bloody gash in "
            +QTNAME(enemy)+"'s "+hdesc+" with "+HIS_HER(me)+" axe.\n",
            enemy);
        enemy->catch_msg(QCTNAME(me)+" rips into your "+hdesc+" with a "
            +"razor-edged axe. Blood pours freely down your side.\n");
        break;
      case 5..8:
        me->catch_msg("You embed the razor-edged axe deep into the "+hdesc
            +"of "+QTNAME(enemy)+". He steps back from the impact.\n");
        tell_watcher(QCTNAME(enemy)+" is staggered by the tremendous "
            +"overhead axe strike of "+QTNAME(me)+".\n", enemy);
        enemy->catch_msg("Your "+hdesc+" feels like it has been crushed "
            +"by the vicious blow from the axe of "+QTNAME(me)+".\n");
        break;
      case 9..16:
   me->catch_msg("The flesh peels away on the "+hdesc+" of "
            +QCTNAME(enemy)+" where your axe embeds in it.\n");
        tell_watcher("The skin on the "+hdesc+" of "+QTNAME(enemy)+" is "
            +"sheared away by a blow from "+QTNAME(me)+".\n", enemy);
        enemy->catch_msg("Your "+hdesc+" flares with pain as it is struck "
        +" by "+QTNAME(me)+"'s axe.\n");
        break;
      case 17..32:
        me->catch_msg(QCTNAME(enemy)+" shakes violently from your blow.\n");
    tell_watcher(QCTNAME(me)+"'s axe sinks deep into the "+hdesc+" of "
            +QTNAME(enemy)+". He seems to shake violently.\n", enemy);
        enemy->catch_msg("Your "+hdesc+" muscles spasm wildly when struck "
            +"by the mithril axe wielded by "+QTNAME(me)+".\n");
        break;
      case 33..64:
        me->catch_msg("You feel the axe bite deeply as it enters the "
            +hdesc+" of "+QTNAME(enemy)+".\n");
        tell_watcher("As "+QTNAME(me)+" slashes "+QTNAME(enemy)
            +", blood splashes out of the wound freely.\n", enemy);
        enemy->catch_msg("Your flesh feels as if it is on fire as your "
            +hdesc+" is sliced by "+QTNAME(me)+".\n");
        break;
      default:
        me->catch_msg("The axe thumps loudly as it breaks "
            +"the bones in the "+hdesc+" of "+QTNAME(enemy)+".\n");
        enemy->catch_msg("As "+QTNAME(me)+" slams his axe into you, "
            +"it feels as if the bones of your "+hdesc+" are broken.\n");
        tell_watcher(QCTNAME(enemy)+" screams in pain as the "
            +"axe of "+QTNAME(me)+" is smashed into their "+hdesc+".\n",
            enemy);
        break;
    }

    return 1;
}

public mixed
wield(object ob)
{
    object  tp = this_player();

    if((TP->query_base_stat(SS_CON) > 174) &&
       (TP->query_base_stat(SS_STR) > 174) &&
       (TP->query_skill(SS_WEP_AXE) > 89))
   {
    TP->catch_msg("You grip the haft of the razor-edged mithril "
        +"axe fiercely, magic coursing up your arm.\n");
    say(QCTNAME(this_player()) + " takes hold of the haft of "
        +"the razor-edged mithril axe, a slight smile creeping "
        +"across "+ HIS_HER(TP) +" face.\n");
        return 1;
    }

    TP->heal_hp(-(50 + random(100)));
    return "Pain spirals up your arm as you attempt to wield "
        +"the razor-edged mithril axe.\n";

}


public mixed
unwield(object wep)
{
   object wr = TO->query_wielded();
   wr->catch_tell("You release your grip on the mithril axe.\n");
//  TP->remove_prop(LIVE_I_SEE_DARK);
    return 1;
}

string
query_recover()
{
    return 0;
}

