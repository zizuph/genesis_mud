/* An elf-slaying and human-slaying mace
 * Last Modification: Olorin, July 1994
 * Mod log: 14-Sep-94, Olorin: moved the destruction on dropping the mace
 *                             from the VBFC of OBJ_M_NO_DROP to leave_env, as
 *                             a query_prop(OBJ_M_NO_DROP) doesn't not
 *                             necessarily mean that someone is actually
 *                             dropping it!
 * 
 * Modification log:
 * Olorin 04-Sep-1996     Made keepable 
 * Rohim  2002-11-09      Modified did_hit to handle parries as dodges.
 * Serif 11/28/03         Cleaned up BSN etc., made one-handed, added half-
 *                        elves as victims, reduced damage against undead
 * Toby 2006-09-25        Added new line in wield/unwield.
 * 
 */
#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep";

#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <options.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <tasks.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"

#define HIS(x)		x->query_possessive()
#define HE(x)       x->query_pronoun()

void
create_weapon()
{
   set_name("mace");
   add_name("weapon");
   set_adj(({"black", "heavy"}));
   set_short("black heavy mace");
   set_pshort("black heavy maces");
   set_long("This is a large black mace, ice-cold to the touch, "
       + "made from some strange metal unknown to you. Veins of inlaid "
       + "gems line the spiked head.\n");
   add_item(({"gems","veins"}), "There are red gemstones inlaid in the "
       + "spiked head of the mace.");
   add_item(({"head"}),("The head of the mace holds nasty spikes, and "
       + "veins of red gems inlaid in between the spikes.\n"));

   set_default_weapon(40,40,W_CLUB,W_BLUDGEON,W_ANYH,0);
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(40, 40)+random(1000)-500);
   add_prop(OBJ_I_WEIGHT,
	  (F_WEIGHT_DEFAULT_WEAPON(50, W_CLUB) + random(2000) + 500));
   add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
   add_prop(GONDOR_M_MORGUL_NO_SELL, 1);
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
   add_prop(MAGIC_AM_MAGIC,({ 40, "enchantment" }));
   add_prop(OBJ_S_WIZINFO,
       "This mace is a nasty magical weapon wielded by evil wraiths in "
       + "Minas Morgul, the city of evil in Gondor. The wraith is in file "
       + "/d/Gondor/morgul/npc/ithil_wraith.c and is a nasty opponent to "
       + "meet. Especially for humans and elves, since this mace is elf- and "
       + "human-slaying! And there is only a small chance that the mace is "
       + "actually possible to get, if you can kill the wraith, for it will "
       + "most often dissolve when the wraith loses its grip on it. "
       + "The mace is WC 40, but does between 1.5x and 2x damage on elves "
       + "and on humans. It has a weaker effect on the undead, causing only "
       + "half the normal damage. Hit and pen are slightly better for "
       + "undead wielders./n");
    add_prop(MAGIC_AM_ID_INFO,
      ({"The black mace seems to be magical.\n",10,
       "The hand of the undead will wield this mace with great effect.\n",25,
       "It is made for elf- and man-slaying!\n",40,
       "A soulless body will resist the effects of this weapon.\n",60}));

    set_wf(TO);
}

varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    if ((enemy->query_prop("_live_i_undead") > 0)) 
    {
   
    object wielder;
    string undead;
//    string res;

    wielder = query_wielded();
    undead = (enemy->query_prop("_live_i_undead")); 
//    res = (enemy->query_prop("_morgul_i_sulambar_res")); 


    if ((phurt == -1 || phurt == -2) && (undead))
    {
    query_wielded()->catch_msg(
        "Your black heavy mace hesitates in your hand as you aim for " 
        + QTNAME(enemy) + ".\n");
    enemy->catch_msg("Your undead form repels " + QTNAME(query_wielded()) 
        + "'s black mace as " + HE(wielder) + " swings at you.\n");
    wielder->tell_watcher(QCTNAME(wielder)+ " struggles with "
        + HIS(wielder) + " " + short() + " as " + HE(wielder) + " aims at " 
        + (QTNAME(enemy)) + ".\n", enemy);
    }
    if ((phurt == 0) && (undead))
    {
    query_wielded()->catch_msg("Your black mace just barely misses "
        + QTNAME(enemy) + "!\n");
    enemy->catch_msg("The black mace of " + QTNAME(query_wielded())
        + " narrowly misses your undead body!\n");
    wielder->tell_watcher(QCTNAME(wielder) + " just barely misses " + QTNAME(enemy)
        + " with " + HIS(wielder) + " black heavy mace.\n", enemy);
    }

    if ((phurt > 0) && (undead))
    {
      enemy->heal_hp(dam/2);
      wielder->catch_msg("Your mace seems to slow in your hand as "
          + "it strikes your undead foe.\n");
      enemy->catch_msg(QCTNAME(query_wielded()) + " hits you with "
          + query_wielded()->query_possessive() + " heavy black mace, "
          + "but your lifeless body resists its effect somewhat.\n");
      wielder->tell_watcher(QCTNAME(wielder) + " awkwardly hits " 
          + QTNAME(enemy) + " with " + HIS(wielder) + " black heavy mace.\n", enemy);
      return 1;
    }

 //   return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    }

    if (enemy->query_race_name()!="elf" && enemy->query_race_name()!="human" 
        && enemy->query_race_name()!="half-elf")
    return 0;

    if (phurt == -1 || phurt == -2)
    {
    query_wielded()->catch_msg(
        "You swing the black mace with all your might through open air.\n");
    enemy->catch_msg("You deftly duck as " + QTNAME(query_wielded()) 
        + " swings " + query_wielded()->query_possessive() 
        + " black mace at you.\n");
    wielder->tell_watcher(QCTNAME(wielder)+" swings the black mace with all "
        + HIS(wielder) + " might through open air.\n", enemy);
    }
    else if (phurt == 0)
    {
    query_wielded()->catch_msg("Your black mace just barely misses "
        + QTNAME(enemy)+"!\n");
    enemy->catch_msg("The black mace of "+QTNAME(query_wielded())
        + " just barely misses your head!\n");
    wielder->tell_watcher(QCTNAME(wielder)+" just barely misses " 
        + QTNAME(enemy) + " with "+HIS(wielder)+" black heavy mace.\n", enemy);
    }
    else
    {
    wielder->tell_watcher(QTNAME(wielder)+"'s heavy black mace falls on "
        + QTNAME(enemy)+" with a bone breaking sound!\n", enemy);
    query_wielded()->catch_msg("The black mace falls down on the puny "        
        + enemy->query_race_name()+" with a mighty crush!\n");
    enemy->catch_msg("The black mace falls upon you with a mighty crush!\n");
    enemy->heal_hp(-(random(dam/2)+dam/2));
    }
  return 1;
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    if (!objectp(from) || !objectp(to) || !living(from))
        return;

    if (!to->query_prop(ROOM_I_IS))
        return;

    if (random(4))
        return;

    tell_room(to, "The black mace turns to dust as it hits the ground!\n");
    set_alarm(0.0, 0.0, "remove_object");
}

public int
unwield(object wep)  
{
    object  tp = TO->query_wielded();

    if (!living(tp)) {}

    return 0;

    WRITE("You release your "+short()+".\n");
    SAY(" releases "+TP->query_possessive()+" "+short()+".\n");
    set_pen(40);
    set_hit(40);
    TP->update_weapon(TO);
    return 1;
}

public mixed 
wield(object wep)
{
    if((TP->query_prop("_live_i_undead") > 0))
    {
        WRITE("You feel a special affinity for this "+short()+" as you wield it.\n");
        SAY(" wields "+TP->query_possessive()+" "+short()+".\n");
        set_hit(45);
        set_pen(45);
        TP->update_weapon(TO);
        return 1;
    }
    else
    {
        WRITE("You heft your "+short()+" carefully.\n");
        SAY(" wields "+TP->query_possessive()+" "+short()+".\n");
        set_hit(40);
        set_pen(40);
        TP->update_weapon(TO);
        return 1;
    }
}  


/*
public int
unwield(object wep)  
{
    WRITE("You release your "+short()+".");
    SAY(" releases "+TP->query_possessive()+" "+short()+".");
    set_pen(40);
    set_hit(40);
    TP->update_weapon(TO);
    return 1;
}

public mixed 
wield(object wep)
{
    if((TP->query_prop("_live_i_undead") > 0))
    {
        WRITE("You feel an special affinity for this "+short()+" as you wield it.");
        SAY(" wields "+TP->query_possessive()+" "+short()+".");
        set_hit(45);
        set_pen(45);
        TP->update_weapon(TO);
        return 1;
    }
    else
    {
        WRITE("You heft your "+short()+" carefully.");
        SAY(" wields "+TP->query_possessive()+" "+short()+".");
        set_hit(40);
        set_pen(40);
        TP->update_weapon(TO);
        return 1;
    }
}  

/*
public int
unwield(object wep)  
{
    object wielder = query_wielded();

        TP->catch_msg("You release your " + short() + ".\n");
        tell_room(QCTNAME(wielder) + " releases " + wielder->query_possessive() + " "
            + short() + ".\n");
        TO->set_pen(40);
        TO->set_hit(40);
        TP->update_weapon(TO);
    return 1;
}

public mixed 
wield(object wep)
{

    if((TP->query_prop("_live_i_undead") > 0))
    {
        TP->catch_msg("You feel a special affinity for this " + short()
            + " as you wield it.\n");
        say(QCTNAME(TP) + " wields " + TP->query_possessive() 
            + " " + short() + ".\n");
        TO->set_hit(45);
        TO->set_pen(45);
        TP->update_weapon(TO);
    return 1;
    }
    else
    {
        TP->catch_msg("You heft your " + short() + " carefully.\n");
        say(QCTNAME(TP) + " wields " + TP->query_possessive() 
            + " " + short() + ".\n");
        TO->set_hit(40);
        TO->set_pen(40);
        TP->update_weapon(TO);
    return 1;
    }
 }  
*/