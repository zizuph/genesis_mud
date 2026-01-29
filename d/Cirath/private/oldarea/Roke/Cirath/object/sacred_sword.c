inherit "/std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>
#include <filter_funs.h>
#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"

int light = 0;

void
create_weapon()
{
   set_name("sword");
   add_name("not flaming not black and not a broadsword");
   add_name("inquisitor");
   add_name("magig");
   set_short("inquisitor sword");
   set_long(break_string("This blade, made by long time dead smiths, "+
        "is made of the best metal from SSAB, stainless of course. Made of "+
        "metal from the dark mountains north of Ciubori, long time ago. "+
        "The blade seems to live by itself. Many small sparkles of energy "+
        "are playing on the blade. You realize that this energy can be hard "+
        "to conquer.\n",76));
   set_adj("magic");
   set_adj("shimmering");
   set_default_weapon(56, 58, W_SWORD, W_SLASH | W_IMPALE, W_ANYH, TO);
   add_prop(OBJ_I_WEIGHT, 20000); 
   add_prop(OBJ_I_VOLUME, 10100); 
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(56, 58) + random(150));
   add_prop(OBJ_M_NO_BUY, 1);
   add_prop(MAGIC_AM_MAGIC, ({ 90, "enchantment" }));
   add_prop(MAGIC_AM_ID_INFO, ({ 
        ({ 100, break_string("This sword has the ability to shock your "+
        "enemy in fight due to its own energy. The power is hard to "+
        "control and "+
        "you better be careful with it. However your enemy won't hurt you "+
        "while shocked. Remember when recharged it will cause all creatures "+
        "in the same room go blind when wielded.\n", 76) }),
        ({ 80, break_string("This sword has its own life it seems, you "+
        "can observe small blue light beams on the blade. It will most "+
        "surely need to recharge once in a while. It is so powerful "+
        "that only a single light beam will shock your enemy.\n", 76) }),
        ({ 60, break_string("This sword you better be careful with. It has "+
        "a soul and it has many effects. Pray to the blade that it will "+
        "serve you. The beams would most surely stunn your enemy.\n",76)}),
        ({ 40, break_string("The swords's blade alomst has a real soul. "+
        "You think that it can deliver a stunning blow so powerful yor enemy "+
        "won't do anything for a while. The energy somehow seems to be able "+
        "to fade away.\n", 76) }),
        ({ 20, break_string("This is a magic weapon and you can almost "+
        "feel the power coursing through it. "+
        "You better be careful with it.\n", 76) }), })
        );
}

init()
{
  ::init();
  call_out("lighter",1);
}

int print_light_txt(int new)
{
  if (light != new)
  {
    if(new == 0)
    {
      write("The inquisitor sword's light sparks disappears.\n");
      say("The inquisitor sword sparks stops glowing.\n");
    }
    else if(new == 1)
    {
      write("The inquisitor sword begins to glow with a strange light. \n"+
            "Small sparkles are trickeling on the blade. \n");
      say("The inquisitor sword begins to glow with a strange "+
          "light.\n"+
          "Small blue sparkles are dancing on the blade.\n");
    }
    else if(new == -1)
    {
      write("The inquisitor sword starts emitting darkness.\n");
      say("The inquisitor sword starts emitting darkness. "+
          "absorbing all light \n");
    }
    else write("Hmmm You inquisitor sword doesn't work properly.\n");
  }
}

int lighter()
{
  int l;

  l = random(10);
  if (l > 7)
  {
    add_prop(OBJ_I_LIGHT,2);
    print_light_txt(1);
  }
  else if (l < 3)
  {
    add_prop(OBJ_I_LIGHT,-1);
    print_light_txt(-1);
  }
  else
  {
    add_prop(OBJ_I_LIGHT,0);
    print_light_txt(0);
  }

  call_out("lighter",500);
}

public int
wield(object wep)
{  
   if (TP->query_stat(SS_STR) <160)
   {
      write("You are not worthy to wield this mighty sword.\n");
      return -1;
   }
   if (TP->query_skill(SS_WEP_SWORD) <60)
   {
      write("You are not worthy to wield this mighty sword.\n");
      return -1;
   }
   if(TP->query_alignment() <= 1000)
   {
        write("You are not worthy to wield this mighty sword.\n");
        return -1;
   }
   if(TP->query_stat(SS_INT) <= 160)
   {
        write("You are not worthy to wield this mighty sword.\n");
        return -1;
   }
   if(TP->query_mana() < 1300)
   {
        write("You don't feel mentally strong enough to wield this "+
              "mighty sword.\n");
        return -1;
   }
   else
        write("With huge effort and with all your mental power your holy "+
              "creature managed to wield the inquisitor sword.\n");
        TP->add_prop(LIVE_I_SEE_DARK, 2);
   return 0;
}

unwield(object o)
{
    if(o!=this_object())
        return 0;

    query_wielded()->catch_msg("You unwield the inquisitor sword and feel "+
        "the magic disappear.\n");
/*
 * Something like this is needed too
    query_wielded()->change_prop(LIVE_I_SEE_DARK, 0);
 */
    return 1;
}

/*
 * Function name: tell_watcher
 * Description:   Send the string from the fight to people that want them
 * Arguments:     The string to send
 */
static void
tell_watcher(string str, object enemy)
{
    object me,*ob;
    int i;

    me = query_wielded();
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->query_see_blood())
            ob[i]->catch_msg(str);
}

varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
        int phit, int dam)
{
    string msg;
    object wielder, shock;

    wielder = query_wielded();
    if (wielder->query_mana() < 100)
    {
         wielder->catch_msg("You feel so mentally exhausted that you "+
         "unwield your inquisitor sword.\n");
         enemy->catch_msg("Your opponent is so mentally weak. The "+
         "inquisitor unwields itself.\n");
         wielder->command("unwield all");
    } 
    if (phurt == -1)
    {
        wielder->catch_msg("The inquisitor sword hesitates and "+
                "misses " + QTNAME(enemy) + ".\n");
        enemy->catch_msg(QCTNAME(wielder)+"'s inquisitor sword hesitates and misses your "+
                "body.\n");
        
/*
 * Added by Arren, change msg to what you want
 */
        msg = "'s inquisitor sword hesitates and misses!\n";
        tell_watcher(QCTNAME(wielder) + msg, enemy);
    }
    else if (phurt == 0)
    {
        wielder->catch_msg(QCTNAME(enemy)+" swings the inquisitor sword near "+ hdesc+".\n");
        enemy->catch_msg(QCTNAME(wielder) +" swings the inquisitor sword near your "+hdesc+".\n");
        tell_watcher(QCTNAME(wielder)+" swings the inquisitor sword near the "+hdesc+
            " of "+QTNAME(enemy)+ ".\n", enemy);
    }
    else
/*
 *  phurt >= 1 means damage
 *  phurt stands for %hurt so phurt == 1 means 1% of max hp
 */
    {
        switch(phurt)
        {
              case 1..2:
                query_wielded()->catch_msg("Your inquisitor sword slashes the body of "+
                             QTNAME(enemy)+"'s body.\n");
                enemy->catch_msg(QCTNAME(wielder)+"'s inquisitor sword slashes your "+
                    "body.\n");
                tell_watcher(QCTNAME(wielder)+"'s inquisitor sword slashes the "+hdesc+
                    " of "+QTNAME(enemy)+ ".\n", enemy);
                break;

             case 3..5:
                query_wielded()->catch_msg("You smile merrily as your inquisitor sword sinks into "+
                    QTNAME(enemy)+"'s body.\n");
                enemy->catch_msg(QCTNAME(wielder)+" smiles merrily, as the inquisitor sword sinks into "+
                    "your "+hdesc+".\n");
                tell_watcher(QCTNAME(wielder)+" smiles merrily, as the inquisitor sword sinks into the "+hdesc+
                    " of "+QTNAME(enemy)+ ".\n", enemy);
                break;

             case 6..9:
                 query_wielded()->catch_msg("You feel a strange force within the sword assist you to destroy "+
                    QTNAME(enemy)+"'s "+hdesc+".\n");
                enemy->catch_msg(QCTNAME(wielder)+"'s inquisitor sword starts to act by itself and hits "+
                    "your "+hdesc+".\n");
                tell_watcher(QCTNAME(wielder)+"'s inquisitor sword starts to act by itself and hits the "+hdesc+
                    " of "+QTNAME(enemy)+".\n", enemy);
                break;

             case 10..14:
                 query_wielded()->catch_msg("As the power grow stronger in the inquisitor sword,  "+
                    QTNAME(enemy)+"'s body is engulfed in flames.\n");
                enemy->catch_msg(QCTNAME(wielder)+"' inquisitor sword engulfs you in flames "+
                    "and you can smell the smell of your own burnt flesh.\n");
                tell_watcher(QCTNAME(wielder)+"'s inquisitor sword engulfs the "+hdesc+
                    " of "+QTNAME(enemy)+ " in flames.\n", enemy);
                break;
             
             case 15..21:
                 query_wielded()->catch_msg("The world becomes more clear as your inquisitor sword  "+
                    "sinks deep into "+QTNAME(enemy)+"'s "+hdesc+".\n");
                enemy->catch_msg(QCTNAME(wielder)+"'s inquisitor sword managed to find a weak spot on your "+
                    hdesc+".\n");
                tell_watcher(QCTNAME(wielder)+"'s inquisitor sword managed to find a weak spot on the "+hdesc+
                    " of "+QTNAME(enemy)+ ".\n", enemy);
                break;

             case 22..30:
                 query_wielded()->catch_msg("Your inquisitor sword flashes red and blue as it hits "+
                    QTNAME(enemy)+"'s "+hdesc+".\n");
                enemy->catch_msg(QCTNAME(wielder)+"'s inquisitor sword flashes red and blue as it hits the "+hdesc+
                    " of "+QTNAME(enemy)+ ".\n", enemy);
                tell_watcher(QCTNAME(wielder)+"'s inquisitor sword flashes red and blue as it hits the "+hdesc+
                    " of "+QTNAME(enemy)+ ".\n", enemy);
                break;

             case 31..42:
                 query_wielded()->catch_msg("Your inquisitor sword deals your opponent a heavy blast on "+
                    QTNAME(enemy)+"'s "+hdesc+".\n");
                enemy->catch_msg(QCTNAME(wielder)+"'s inquisitor sword deals you a heavy blast on your "+
                    hdesc+".\n");
                tell_watcher(QCTNAME(wielder)+"'s inquisitor sword deals the "+hdesc+
                    " of "+QTNAME(enemy)+ "a heavy blast leaving a smell of burnt flesh behind.\n", enemy);
                break;

             case 43..55:
                 query_wielded()->catch_msg("Your inquisitor sword explodes with an earthquaking noise and hits "+
                    QTNAME(enemy)+"'s "+hdesc+", very hard.\n");
                enemy->catch_msg(QCTNAME(wielder)+"'s inquisitor sword explodes with an earthquaking noise and hits "+
                    "body, very hard.\n");
                tell_watcher(QCTNAME(wielder)+"'s inquisitor sword explodes with an earthquaking noise and hits "+
                    "the "+hdesc+" of "+QTNAME(enemy)+ ", very hard.\n", enemy);
                break;

             case 56..70:
                 query_wielded()->catch_msg("Your inquisitor sword makes a devastating jump and smashes "+
                    QTNAME(enemy)+"'s body.\n");
                enemy->catch_msg(QCTNAME(wielder)+"'s inquisitor sword makes a devastating jump and smashes "+
                    "your body almost to a pulp.\n");
                tell_watcher(QCTNAME(wielder)+"'s inquisitor sword makes a devastating jump and smashes the "+
                     hdesc+" of "+QTNAME(enemy)+ ", very hard.\n", enemy);
                break;

             case 71..100:
                 query_wielded()->catch_msg("Your inquisitor sword vibrates with power when it hits "+
                    QTNAME(enemy)+"'s head, with a skullbreaking sound.\n");
                enemy->catch_msg(QCTNAME(wielder)+"'s inquisitor sword seems to vibrate with power "+
                    "and it hits you with enormous energy.\nYou seem to be crushed!\n");
                tell_watcher(QCTNAME(wielder)+"'s inquisitor sword seems to vibrate with power when it hits"+
                    "the head of "+QTNAME(enemy)+ ", with a skullbreaking sound.\n", enemy);
                break; 

                default:
/*
 * this is the same message as massacre
 */
                wielder->catch_msg("The inquisitor sword makes a final and enourmous blow on "+
                    QTNAME(enemy)+"'s head. The head seems to fall off.\n");
                enemy->catch_msg("The inquisitor sword makes a final and enourmous blow on your "+
                    "head. You almost lost your head.\n");
                tell_watcher(QCTNAME(wielder)+"'s inquisitor sword makes a final and enourmous blow on "+
                    "the head of "+QTNAME(enemy)+ ". The head seems to fall off.put testsword.c\n", enemy);
                break;
        }

        if(!random(5) && !present("inq_beam_shock", enemy))
        {
           wielder->catch_msg("The inquisitor sword starts to glow and "+
           "great beams of lights hits "+ QTNAME(enemy)+
           ", and "+QTNAME(enemy)+" looks stunned.\n");
           enemy->catch_msg("A light beam hits you! \nYou feel stunned by "+
           "the shock, you can't move.\n");
           tell_watcher(QCTNAME(wielder)+" inquisitor sword starts to glow and "+
           "great beams of light hits "+hdesc+
                    " of "+QTNAME(enemy)+ ",\n"+(QTNAME(enemy))+" looks stunned. \n", enemy);
           TP->add_mana(-30);
           setuid();
           seteuid(getuid());
           shock = clone_object(OBJ+"shock");
           shock->move(enemy,1);
           shock->start_time();
        }
    }
    return 1;
}

int
try_hit(object t)
{
  if(t->query_alignment() > 1000)
  {
      query_wielded()->catch_msg("The inquisitor swords starts to glow red "+
          "and it hurts you very bad.\n");
      tell_room("As "+QCTNAME(wielder)+"'s inquisitor sword realizes that "+
          "you are holy it hits "+QCTNAME(wielder)+"instead.\n");
      TP->heal_hp(-400);
  }
  return 1;
}
