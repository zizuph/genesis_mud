/*
 * /d/Kalad/common/noble/wep/f_axe.c
 * Purpose    : Magical axe.  Increases damage done, but quickly
 *              sucks mana.
 * Located    : 
 * Created By : Sarr
 * Modified By: Sarr, Rico, Toby 970724
 * First Modif: 12.Feb.97
 * Fysix, 9802, fixed the entirely buggy damage calculation
 *  still should be somewhat more sophisticated than it is now.
 * 1999/03/02 ?
 * 2011/07/12 Lavellan, fixed OBJ_M_NO_SELL to OBJ_M_NO_BUY
 */

inherit "/d/Kalad/std/weapon";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

#include "/d/Kalad/defs.h"
#include <tasks.h>

void
create_weapon()
{
   ::create_weapon();

   set_name("battle-axe");
   add_name("axe");
   set_adj("humming");
   add_adj("fire");
   set_short("humming fire battle-axe");
   set_long("This large and powerful looking axe is made of strange "+
      "red steel. Along the ebony handle, you see strange red runes "+
      "carved. The blade is very shiny, and even glows a bit. A very "+
      "quiet hum is emitting from it.\n");

   set_hands(W_BOTH);
   set_hit(45);
   set_pen(48);
   // This value will affect spell damage for spellcasters.
   set_magic_spellpower(48);
   set_spellpower_elements(({ SS_ELEMENT_FIRE }));
   set_wt(W_AXE);
   set_dt(W_SLASH);
   set_wf(TO);

   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
   add_prop(OBJ_S_WIZINFO, "This is a magical fire axe. You need "+
      "a strength of 100 to wield it, and when you do wield it, it "+
      "gives you fire protection. It is light and deadly, and further "+
      "it has a fire special that does (2 * random(80)) points of "+
      "damage every other round or so (and takes 100 mana points). "+
      "Failure to wield results in (100 + (2 * random(250))) points "+
      "of mana lost. Big drawback in this, is that it can take down "+
      "mana rather quick.\n");
   add_prop(MAGIC_AM_MAGIC, ({ 70, "enchantment" }));
   add_prop(MAGIC_AM_ID_INFO,({
      "The enchanted runes appear to include elemental themes. Beware "+
         "the blade of fire if you be weak of mind and strength!\n", 10,
      "This weapon appears to have been crafted for a warrior of great "+
         "strength and of strong mind.\n", 15,
      "The weapon flashes with a pride in its own elemental potency;\n"+
         "any failure to master the weapon would surely incur the wrath "+
         "upon the possessor's mind.\n", 22,
      "This axe was forged in the pits of a volcano, and thus "+
         "gives the wielder protection from that element. But beware, "+
         "the price of the axe is taxed upon your mind.\n", 30,
      "Arms and hands of great strength may untap the fury of the blazing "+
         "fires which forged this magnificent weapon as a great "+
         "burning umbra swirls about its blade. Be prepared for a "+
         "taxing burden upon your mind.\n", 50,
      }));
   add_prop(OBJ_I_WEIGHT, 7000);
   add_prop(OBJ_I_VOLUME, 2820);
   add_prop(OBJ_M_NO_STEAL, 1);
   //add_prop(OBJ_M_NO_SELL, 1);
   add_prop(OBJ_M_NO_BUY, 1);
}

mixed
wield(object ob)
{
   set_this_player(E(ob));

   if(TP->query_npc())
   {
      set_hit(70);
      set_pen(70);
    return 1;
   }
   if(TP->resolve_task(TASK_DIFFICULT,({TS_STR,TS_WIS})) < 0)
   {
      write("As you grasp the handle the axe glows bright red.\n"+
         "A powerful force shoots up your arm, searing your brain!\n"+
         "You feel your brain turn to mush.\n");
        TP->add_mana(-(100 + (2 * random(250))));
      say(QCTNAME(TP) + " grips the axe, and it glows bright red. But "+
         "then so does " + QTNAME(TP) + ", and " + HIS(TP) + " eyes "+
         "roll back as " + HE(TP) + " lets go of the handle!\n");
      return "You let go of the handle.\n";
   }

   write("You grab the handle, and the axe bursts into flames! You "+
      "bask in the heat.\n");
   TP->add_magic_effect(ob);
   ob->set_short("flaming fire battle-axe");
   ob->add_adj("flaming");
   say(QCTNAME(TP)+" grabs the handle of the axe and it's blade "+
      "bursts into flames!\n");

   return 1;
}

int
unwield(object ob)
{
   set_this_player(query_wielded());
   write("As you release the flaming battle-axe the flames "+
      "vanish!\n");

   set_hit(40);
   set_pen(48);

   say(QCTNAME(TP)+" lets go of the flaming battle-axe and the "+
      "flames vanish!\n");
   TP->remove_magic_effects(ob);
   ob->set_short("humming fire battle-axe");

   return 0;
}

public mixed
did_hit(int aid,
        string hdesc,
        int phurt,
        object enemy,
        int dt,
        int phit,
        int dam)
{
   int    firedam;
   object me = query_wielded();

   if(phurt > 0 && (me->query_mana() > 100))
   {
      firedam = (2 * random(80));
      me->catch_msg("A plume of flame leaps out of the "+
         TO->query_short() + " and slams into " + QTNAME(enemy)+
         "'s chest, and " + HE(enemy) + " burns.\n");
      enemy->catch_msg("A plume of flame leaps out of " + QTNAME(me)+
         "'s " + TO->query_short() + " and slams into your chest. "+
         "You burn badly.\n");
      tell_room(E(me), "A plume of flame leaps out of " + QCTNAME(me)+
         "'s " + TO->query_short() + " and slams into " + QTNAME(enemy)+
         "'s chest, burning him.\n", ({me, enemy}));
      me->add_mana(-100);
      firedam = firedam * (100 -
         enemy->query_magic_res(MAGIC_I_RES_FIRE)) / 100;
      enemy->heal_hp(-firedam);
      if(enemy->query_hp() <= 0)
         enemy->do_die(me);
   }

   return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}


varargs mixed
query_magic_protection(string prop, object what)
{
   if((what == query_wielded()) && (prop == MAGIC_I_RES_FIRE))
      return ({70, 0});
   else
      return ::query_magic_protection(prop, what);
}

void 
appraise_object(int num)
{
    ::appraise_object(num);
    write(item_spellpower_desc());
}

string 
stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
}
