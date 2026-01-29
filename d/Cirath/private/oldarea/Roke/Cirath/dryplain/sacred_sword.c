inherit "/std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"

int light = 0;

void
create_weapon()
{
   set_name("sword");
   add_name("magic shimmering sword");
   set_short("inquisitor sword");
   set_long(break_string("This blade, made by long time dead smiths, "+
        "is made of the best metal from ssab, stainless of course. "+
        "The blade seems to live by itself. Many small sparkles of energy "+
        "are playing on the blade. You realize that this energy can be hard "+
        "to conquer.\n",76));
   set_adj("magic");
   set_adj("shimmering");
   set_default_weapon(56, 58, W_SWORD, W_SLASH | W_IMPALE, W_ANYH,  this_object());
   add_prop(OBJ_I_WEIGHT, 20000); 
   add_prop(OBJ_I_VOLUME, 10100); 
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(56, 58) + random(150));
   add_prop(OBJ_M_NO_BUY, 1);
   add_prop(MAGIC_AM_MAGIC, ({ 90, "enchantment" }));
   add_prop(MAGIC_AM_ID_INFO, ({ 
        ({ 100, break_string("This sword has the ability to shock your "+
        "enemy in fight due to its own energy. The power is hard to controll and "+
        "you better be careful with it. However your enemy won't hurt you while "+
        "shocked. Remember when recharged it will cause all creatures in the same "+
        "room go blind when wielded.\n", 76) }),
        ({ 80, break_string("This sword has its own life it seems, you "+
        "can observe small blue light beams on the blade. It will most "+
        "surely need to recharge once in a while. It is so powerfull "+
        "that only a single light beam will shock your enemy.\n", 76) }),
        ({ 60, break_string("This sword you better be careful with. It has a soul and "+
        "it has many effects. Pray to the blade that it will serve you. "+
        "The beams would most surely stunn your enemy.\n",76)}),
        ({ 40, break_string("The swords's blade alomst has a real soul. "+
        "You think that it can deliver a stunning blow so powerful yor enemy won't do "+
        "anything for a while. The energy somehow seems to be able to fade away.\n", 76) }),
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
      say(QCTNAME(TP)+"'s inquisitor sword sparks stops glowing.\n");
    }
    else if(new == 1)
    {
      write("The inquisitor sword begins to glow with a strange light. \n"+
            "Small sparkles are trickeling on the blade. \n");
      say(QCTNAME(TP)+"'s inquisitor sword begins to glow with a strange light.\n"+
          "Small blue sparks are playing on the blade.\n");
    }
    else if(new == -1)
    {
      write("The inquisitor sword starts emitting darkness.\n");
      say(QCTNAME(TP)+"'s inquisitor sword starts emitting darkness. Absorbing all light \n");
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
   if (TP->query_skill(SS_WEP_SWORD) <80)
   {
      write("You are not worthy to wield this mighty sword.\n");
      return -1;
   }
   if(TP->query_alignment() <= 1300)
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
        write("You don't feel mentally strong enough to wield this mighty sword.\n");
        return -1;
   }
   else
        write("With huge effort and with all your mental power your holy creature managed "+
              "to wield the inquisitor sword.\n");
        TP->add_prop(LIVE_I_SEE_DARK,2);
   return 0;
}

unwield(object o)
{
    if(o!=this_object())
	return 0;

    query_wielded()->catch_msg("You unwield the inquisitor sword and feel the magic disappear.\n");
    return 1;
}

varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
        int phit, int dam)
{
    object shock;

    if (TP->query_mana() < 100)
    {
         query_wielded()->catch_msg("You feel so mentally exhausted that you unwield your inquisitor sword.\n");
         enemy->catch_msg("Yout opponent is so mentally weak. The inquisitor unwields itself.\n");
         TP->command("unwield all");
    }    
    if (phurt == -1)
    {
        query_wielded()->catch_msg("The inquisitor sword sinks into "+ QTNAME(enemy)+"'s body.\n");
        enemy->catch_msg("The inquisitor sword sinks deep into your body.\n");
    }
    else if (phurt == 0)
    {
        query_wielded()->catch_msg("The inquisitor sword hesitates and "+
                "misses " + QTNAME(enemy) + ".\n");
        enemy->catch_msg("The inquisitor sword hesitates and misses your body.\n");
    }
    else
    {
        if(!random(3) && !present("inq_beam_shock", enemy))
        {
           query_wielded()->catch_msg("The inquisitor sword starts to glow and great beams of lights "+
           "hits "+QTNAME(enemy)+", and "+QTNAME(enemy)+" looks stunned.\n");
           enemy->catch_msg("A light beam hits you! \n You feel stunned by the shock, you can't move.\n");
           TP->add_mana(-50);
	   setuid();
	   seteuid(getuid());
	   shock = clone_object("/d/Roke/Cirath/object/shock");
	   shock->move(enemy,1);
	   shock->start_time();
           return 0;
        }
        return 0;
    }
    return 0;
}

int
try_hit(object t)
{
  if(t->query_alignment() > 200)
    {
      query_wielded()->catch_msg("The inquisitor swords starts to glow red and it hurts you very bad.\n");
      tell_room("As "+QCTNAME(wielder)+"'s inquisitor sword realizes that you are good it hits "+QCTNAME(wielder)+"instead.\n");
      TP->heal_hp(-500);
    }
  return 1;
}
