/* A weapon should always begin with these statements: */

inherit "/std/weapon";
#include "/sys/wa_types.h"  /* wa_types.h contains some definitions we want */
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Immortal/std/domain.h"
#include "/d/Immortal/shanar/shanar.h"
#include <ss_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("broadsword");
    add_name("asmo_imm_laenwep");
    add_name("laen broadsword");
    set_short("laen broadsword");
    set_long("This "+"@@query_name@@"+" looks as if it were made entirely of "+
             "glass, including the hilt and pommel. However, you "+
             "know it to be made of pure Laen. There is a spectrum "+
             "of oily colors running along it's face vertically.\n");

    /* Now, a player can refere to this weapon as 'weapon' and 'dagger'. To
     * distinguish it from other daggers, we want the player to be able to 
     * use 'small dagger' as an id too.
     */
    set_adj("laen");

    /* Now we want to set the 'to hit' value and 'penetration value' */
    set_hit(94);
    set_pen(100);

    /* The weapon type and the type of damage done by this weapon */
    set_wt(W_SWORD); 
    set_dt(W_SLASH | W_IMPALE); /* You can both 'slash' and 'impale' with it */

    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(68,72)+2000);
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(55,75)+500);
    add_prop(OBJ_I_VOLUME,query_prop(OBJ_I_WEIGHT)/5);

    /* Last, how shall it be wielded? */
    set_hands(W_ANYH); /* You can wield it in any hand. */
    set_wf(TO);
}

public int
wield()
{

  int knifeskill,swordskill;

  knifeskill=TP->query_skill(SS_WEP_KNIFE);
  swordskill=TP->query_skill(SS_WEP_SWORD);

  if (knifeskill > swordskill)
     {
      set_wt(W_KNIFE);
      set_name("knife");
      set_short("laen knife");

      TP->catch_msg("To your amazement, the broadsword suddenly "+
                    "glows with blue iridescent light and shrinks "+
                    "down to the size of a knife!\n");

      tell_room(environment(ETO),"As "+QCTNAME(ETO)+" wields the "+
                "broadsword, it suddenly glows with blue iridescent "+
                "light and shrinks down to the size of a knife!\n",TP);

      return 1;
     }
    TP->catch_msg("You grip the broadsword and grin as you somehow "+
                  "feel much more confident wielding this blade.\n");
    tell_room(environment(ETO),"As "+QCTNAME(ETO)+" wields the massive "+
              "laen broadsword, a rush of power fills "+
              ETO->query_objective()+", lighting "+ETO->query_possessive()+
              " eyes with a firey powerful red.\n",ETO);
   return 1;
}

public int
unwield()
{

    if (query_name()=="knife")
      {
       TP->catch_msg("As you stop wielding the laen knife, it "+
                     "glows blue momentarily and then expands "+
                     "into the shape of a broadsword!\n");
       tell_room(environment(TP),"As "+QCTNAME(TP)+" stops wielding "+
                 "the laen knife, it momentarily glows blue and then "+
                 "expands into the shape of a broadsword!\n",TP);

       set_wt(W_SWORD);
       set_name("broadsword");
       set_short("laen broadsword");
       return 1;
      }
   ETO->catch_msg("You feel a tremendous lack of confidence now that "+
                 "you have stopped wielding the laen broadsword.\n");
   return 1;
}

int
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{

  string bladename;
  string how;
  mixed* hitresult;
  
  bladename=TO->query_name();
  
  if (random(5)) return 0;

  how="barely scrapes";

  hitresult=enemy->hit_me(100+random(50),MAGIC_DT,query_wielded(),-1);
  if (hitresult[0]>5)
    how="burns";

  if (hitresult[0]>10)
    how="blasts";

  if (hitresult[0]>20)
    how="explodes";

  if (hitresult[0]>30)
    how="disgustingly melts";

  enemy->heal_hp(-dam);

  query_wielded()->catch_msg("A bolt of lightning bursts from the tip "+
           "of your laen "+bladename+",which "+how+" into "+
             QCTNAME(enemy)+"'s "+hdesc+"!\n");

  enemy->catch_msg("A bolt of lightning bursts from the tip of "+
          QCTNAME(query_wielded())+"'s "+
           "laen "+bladename+", which "+how+" into "+
           "your "+hdesc+"!\n");

  tell_room(environment(query_wielded()),"A bolt of lightning bursts from "+
           "the tip of "+QCTNAME(query_wielded())+"'s lean "+"@@query_name@@"+
           ",which "+how+" into "+QCTNAME(enemy)+"'s "+hdesc+"!\n",
           ({query_wielded(),enemy}) );

  return 1;

}
