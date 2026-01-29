#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/silvanesti/shadow/local.h"
#include <macros.h>
#include <stdproperties.h>
#pragma save_binary
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

inherit "/std/weapon";

int rand;

nomask
create_weapon()
{
  set_name("brainmasher");
  set_short("jewelled keen brainmasher");
  set_long("@@long_desc");
  set_default_weapon(40,44,W_CLUB,W_BLUDGEON,W_ANYH);
  add_name("hammer");
  add_name("warhammer");
  add_pname("hammers");
  add_pname("warhammers");
  set_adj("jewelled keen");
  add_adj("jewelled");
  add_adj("keen");

  add_prop(OBJ_I_VOLUME,2000+random(10)*150);
  add_prop(OBJ_I_WEIGHT,2500+random(10)*200);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(45,45)*2);
        
  add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
  add_prop(MAGIC_AM_ID_INFO,({
    "The warhammer glows with magic.\n",10,
    "The jewels in the handle seem to be the source of the power.\n",20,
    "The weapon bashes mana out of enemy heads and can stun.\n",50}));
  add_prop(MAGIC_AM_MAGIC,({70,"evocation"}));
  add_prop(OBJ_S_WIZINFO,"Drains mana and stuns victims.\n");
}
      
public varargs int
did_hit(int aid,string hdesc, int phurt, object enemy, int dt, int phit, int
dam) 
{    
  object attacker = query_wielded();
  if (phurt < 0)
    return ::did_hit(aid,hdesc,phurt,enemy,dt,phit,dam);
  else
  {
    rand = random(7);
    if (rand == 0)
    {
      enemy->add_mana(-1*(random(50)+1));
      attacker->catch_msg("You bash some sense out of " + QTNAME(enemy) +
        ".\n");
      enemy->catch_msg(QCTNAME(attacker) + " bashes some sense out of you.\n");
      tell_room(E(enemy),QCTNAME(attacker) + " bashes some sense out of " +
        QTNAME(enemy) + ".\n",({attacker,enemy}));
      return ::did_hit(aid,hdesc,phurt,enemy,dt,phit,dam);
    }

    else if (rand == 1)
    {
      if(!P("jkhammer_stun",enemy))
      {
        attacker->catch_msg("You bash " + QTNAME(enemy) + " so hard " + 
          enemy->query_pronoun() + " loses " + enemy->query_possessive() +
          " senses.\n");
        setuid();
        seteuid(getuid());
        clone_object(SOBJ + "jkhammer_stun")->move(enemy);   
      }
      return ::did_hit(aid,hdesc,phurt,enemy,dt,phit,dam);
    } 
  }
}

string
long_desc()
{
  return "an exquisite warhammer.\n";
}
   
