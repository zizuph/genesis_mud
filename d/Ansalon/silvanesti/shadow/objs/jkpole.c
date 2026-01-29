#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/silvanesti/shadow/local.h"
#include <macros.h>
#include <stdproperties.h>
#pragma save_binary
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

inherit "/std/weapon";

int charger = 0;

nomask
create_weapon()
{
  set_name("blackbane");
  set_short("jewelled keen blackbane");
  set_long("@@long_desc");
  set_default_weapon(40,40,W_POLEARM,W_IMPALE,W_BOTH);
  add_name("partisan");
  add_pname("partisans");
  set_adj("jewelled keen");
  add_adj("jewelled");
  add_adj("keen");

  add_prop(OBJ_I_VOLUME,1500+random(10)*150);
  add_prop(OBJ_I_WEIGHT,1000+random(10)*100);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(45,45)*2);

  add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
  add_prop(MAGIC_AM_ID_INFO,({
    "The partisan glows with magic.\n",10,
    "The jewels in the shaft seem to be the source of the power.\n",20,
    "The weapon hates evil and will irradicate all it can.\n",50}));
  add_prop(MAGIC_AM_MAGIC,({70,"abjuration"}));
  add_prop(OBJ_S_WIZINFO,"Damages evil according to how evil.\n");
}

public varargs int
did_hit(int aid,string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
  object attacker = query_wielded();
  if (phurt < 0)
    return ::did_hit(aid,hdesc,phurt,enemy,dt,phit,dam);
  else
  {
    if (enemy->query_alignment() >= 0)
      return ::did_hit(aid,hdesc,phurt,enemy,dt,phit,dam);
    else
    {
      charger++;
      if (charger < 6)
        return ::did_hit(aid,hdesc,phurt,enemy,dt,phit,dam);
      else
      {
        enemy->set_hp(enemy->query_hp() + enemy->query_alignment()/2);
        if (enemy->query_alignment() > -200)
        {
          attacker->catch_msg("A small force shoots from your partisan " +
            "and hits " + QTNAME(enemy) + " in " + enemy->query_possessive() +
            " " + hdesc + ".\n");
          enemy->catch_msg("A small force shoots from " + QTPNAME(attacker) +
            " partisan and hits you in your " + hdesc + ".\n");
          tell_room(E(enemy),"A small force shoots from " + QTPNAME(attacker) +
            " partisan and hits " + QCTNAME(enemy) + " in " +
            enemy->query_possessive() + " " + hdesc + ".\n",({enemy,attacker}));
        }
        else if (enemy->query_alignment() > -400)
        {
          attacker->catch_msg("A fiery burst leaps from your partisan " +
            "and burns " + QTNAME(enemy) + " in " + enemy->query_possessive() +
            " " + hdesc + ".\n");
          enemy->catch_msg("A fiery burst leaps from " + QTPNAME(attacker) + 
            " partisan and burns your " + hdesc + ".\n");
          tell_room(E(enemy),"A fiery burst leaps from " + QTPNAME(attacker) + 
            " partisan and burns " + QTPNAME(enemy) + " " + hdesc + ".\n",
            ({enemy,attacker}));
        }
        else if (enemy->query_alignment() > -600)
        {
          attacker->catch_msg("A bright beam of energy streaks from your " +
            "partisan and strikes " + QTNAME(enemy) + " forcefully in " +
            enemy->query_possessive() + " " + hdesc + ".\n");
          enemy->catch_msg("A bright beam of energy streaks from " +
            QTPNAME(attacker) + " partisan and strikes you forcefully in " +
            "your " + hdesc + ".\n");
          tell_room(E(enemy),"A bright beam of energy streaks from " +
            QTPNAME(attacker) + " partisan and strikes " + QTNAME(enemy) +
            " forcefully in " + enemy->query_possessive() + " " + hdesc + 
            ".\n",({enemy,attacker}));
        }
        else if (enemy->query_alignment() > -800)
        {
          attacker->catch_msg("A pure light smites " + QTNAME(enemy) + 
            " on " + enemy->query_possessive() + " " + hdesc + " trying " +
            "to purge the evil.\n");
          enemy->catch_msg("A pure light coming from " + QTPNAME(attacker) +
            " partisan smites you on your " + hdesc + ".\n");
          tell_room(E(enemy),"A pure light coming from " + QTPNAME(attacker) +
            " partisan smites " + QTNAME(enemy) + " on " +
            enemy->query_possessive() + " " + hdesc + ".\n",({enemy,attacker}));
        }
        else
        {
          attacker->catch_msg("A holy bolt from your partisan engulfs " +
            QTNAME(enemy) + " and sears " + enemy->query_possessive() +
            " flesh with a purging flame.\n");
          enemy->catch_msg("A holy bolt from " + QTPNAME(attacker) + 
            " partisan engulfs you and sears your flesh with a " +
            "purging flame.\n");
          tell_room(E(enemy),"A holy bolt from " + QTPNAME(attacker) +
            " partisan engulfs " + QTNAME(enemy) + " and sears " +
            enemy->query_possessive() + " flesh with a purging flame.\n",
            ({attacker,enemy}));
         }
         charger = 0;
         return 1;
      }
    }
  }
}



string
long_desc()
{
  return "An exquisite partisan with " + charger + " of its jewels glowing.\n";
}
