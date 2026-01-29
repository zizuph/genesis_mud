#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/silvanesti/shadow/local.h"
#include <macros.h>
#include <stdproperties.h>
#pragma save_binary

inherit "/std/weapon";

#include "/sys/wa_types.h"
#include "/sys/formulas.h"


/*
 * Function name: reset_weapon
 * Description:   Reset the weapon
 * Arguments:     arg: The reset argument.
 */

nomask
create_weapon()
{
          set_name("backstabber");
          set_short("jewelled keen backstabber");
          set_long("@@long_desc");
          set_default_weapon(40, 40, W_KNIFE, W_IMPALE, W_ANYH);
          set_pshort("jewelled keen backstabbers");
          set_pname("backstabbers");
          add_name("knife");
          add_name("dagger");
          add_name("stiletto");
          add_pname("knives");
          add_pname("daggers");
          add_pname("stilettos");
          set_adj("jewelled keen");
          add_adj("jewelled");
          add_adj("keen");

          add_prop(OBJ_I_VOLUME,500+random(30)*10);
          add_prop(OBJ_I_WEIGHT,500+random(30)*10);
          add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(45,45)*3/2);

          add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
          add_prop(MAGIC_AM_ID_INFO,({
            "The dagger glows with magic.\n",10,
            "The jewels in the hilt seem to be the source of the power.\n",25,
            "The weapon strikes on its own, doing extra damage.\n",50}));
          add_prop(MAGIC_AM_MAGIC,({70,"enchantment"}));
          add_prop(OBJ_S_WIZINFO,"Dagger strikes out doing extra damage to " +
            "an enemy's back.\n");
}

public varargs int
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
  object attacker = query_wielded();
  if (phurt < 0)
    return ::did_hit(aid,hdesc,phurt,enemy,dt,phit,dam);

  if (random(5) == 0)
  {
    dam = ((dam*5)/4)-50;
    enemy->hit_me(dam,MAGIC_DT,attacker,-1,A_BACK);
    if(enemy->query_hp() <= 0)
    {
      attacker->catch_msg("You twist the dagger in " + QTPNAME(enemy) +
        " back until all of the life has been drained from " +
        enemy->query_possessive() + " body.\n");
      enemy->catch_msg(QCTNAME(attacker) + " twists the dagger in your " +
        "back until all of the life has been drained from your body.\n");
      tell_room(E(attacker),QCTNAME(attacker) + " twists the dagger in " +
        QTPNAME(enemy) + " back until all of the life has been drained " +
        "from " + enemy->query_possessive() + " body.\n",({attacker,enemy}));
      enemy->do_die(attacker);
    }
    else
    {
      if (dam < 50)
      {
        attacker->catch_msg("You barely manage to stick your dagger into " +
          QTPNAME(enemy) + " back.\n");
        enemy->catch_msg(QCTNAME(attacker) + " barely manages to stick " +
          attacker->query_possessive() + " dagger into your back.\n");
        tell_room(E(enemy),QCTNAME(attacker) + " barely manages to stick " +
          attacker->query_possessive() + " dagger into " + QTPNAME(enemy) +
          " back.\n",({attacker,enemy}));
      }
      else if (dam < 100)
      {
        attacker->catch_msg("You carve up " + QTPNAME(enemy) + " back with " +
          " your dagger.\n");
        enemy->catch_msg(QCTNAME(attacker) + " carves up your back with " +
          attacker->query_possessive() + " dagger.\n");
        tell_room(E(enemy),QCTNAME(attacker) + " carves up " + QTPNAME(enemy) +
          " back with " + attacker->query_possessive() + " dagger.\n",
          ({enemy,attacker}));
      }
      else if (dam < 150)
      {
        attacker->catch_msg("You stab your dagger into " + QTPNAME(enemy) +
          " back, twisting it for added pain.\n");
        enemy->catch_msg(QCTNAME(attacker) + " stabs " +
          attacker->query_possessive() +
          " dagger into your back, twisting it for added pain.\n");
        tell_room(E(enemy),QCTNAME(attacker) + " stabs " +
          attacker->query_possessive() + " dagger into " + QTPNAME(enemy) +
          " back, twisting it for added pain.\n",({enemy,attacker}));
      }
      else if (dam < 200)
      {
        attacker->catch_msg("You powerfully drive your dagger into " +
          QTPNAME(enemy) + " back, ripping a nasty wound.\n");
        enemy->catch_msg(QCTNAME(attacker) + " powerfully drives " +
          attacker->query_possessive() + " dagger into your back, " +
          "ripping a nasty wound.\n");
        tell_room(E(enemy),QCTNAME(attacker) + " powerfully drives " +
          attacker->query_possessive() + " dagger into " + QTPNAME(enemy) +
          " back, ripping a nasty wound.\n",({enemy,attacker}));
      }
      else
      {
        attacker->catch_msg("You plunge your dagger deeply into " +
          QTPNAME(enemy) + " back, tearing at " + enemy->query_possessive() +
          " internal organs.\n");
        enemy->catch_msg(QCTNAME(attacker) + " plunges " +
          attacker->query_possessive() + " dagger deeply into your back, " +
          "tearing at your internal organs.\n");
        tell_room(E(enemy),QCTNAME(attacker) + " plunges " +
          attacker->query_possessive() + " dagger deeply into " + QTPNAME(enemy) +
          " back, tearing at " + enemy->query_possessive() + " internal organs.\n",
          ({enemy,attacker}));
      }
    }
    return 1;
  }
  else
    return ::did_hit(aid,hdesc,phurt,enemy,dt,phit,dam);
}

public mixed
wield (object what)
{
  if (TP->query_stat(1) > 100 &&
      TP->query_skill(3) >= 60 &&
      TP->query_skill(54) >= 60)
  {
    TP->catch_msg("The jewels of the dagger glow brightly as you " +
      "grasp the hilt.\n");
    return 0;
  }

  TP->add_mana(-100 - random(200));
  TP->set_hp(TP->query_hp() - 100 - random(200));
  if (TP->query_hp() >= 0)
    TP->do_die();
  return "You cringe in pain as the power within the dagger lashes " +
    "out at you.\n";
}

mixed
unwield (object what)
{
  TP->catch_msg("The jewels of the dagger dim as you disconnect " +
    "yourself from its power.\n");
  return 0;
}

string
long_desc()
{
  return "An exquisite dagger with a blade of about six inches.  " +
    "Beautiful jewels are set into the hilt and seem warm to the " +
    "touch.  The blade seems extra sharp and able to do some " +
    "vicious damage to anyone unfortunate enough to be struck by " +
    "it.\n";
}
