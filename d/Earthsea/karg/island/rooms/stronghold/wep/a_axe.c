inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "defs.h"

#define MANA_COST 80

int lightning=0;

void create_weapon()
{
 set_name("waraxe");
 add_name("axe");
 add_name("weapon");
 set_adj("white");
 add_adj("sharp-bladed");
 set_short("white sharp-bladed waraxe");
 set_wt(W_AXE);
 set_wf(TO);
 set_dt(W_SLASH|W_BLUDGEON);
 set_pen(43+random(4));
 set_hit(40+random(6));
 set_hands(W_LEFT);
 set_likely_dull(-1000);
 set_likely_break(-1000);

 add_prop(OBJ_I_WEIGHT,7000);
 add_prop(OBJ_I_VOLUME,7000);
 add_prop(OBJ_I_VALUE,1);
 add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
 add_prop(OBJ_M_NO_STEAL,1);
 add_prop(OBJ_M_NO_BUY,"I won't sell this glorious weapon!\n");

 set_long("@@long_desc");
}

void init()
{
 ::init();
 add_action("rub","rub");
}

int meet_requerements(object pl)
{
 if(pl->query_stat(SS_STR)<140 || pl->query_stat(SS_DEX)<140 ||
    pl->query_stat(SS_WIS)<120 || pl->query_stat(SS_DIS)<120 ||
    pl->query_skill(SS_WEP_AXE)<80) return 0;

 return 1;
}

mixed wield(object weapon)
{
 if(!meet_requerements(TP)) return "You try to wield the axe , but "+
   "suddenly words echo in your head : \"You are not worthy...\"\n";

 write("As you wield the "+short()+" it starts to glow with white "+
   "shimmering light.\n");
 say("As "+QTNAME(TP)+" wields the "+short()+" it starts to glow with "+
   "white shimmering light.\n");

 set_adj("shimmering");
 set_short("shimmering sharp-bladed waraxe");

 return 1;
}

mixed unwield(object weapon)
{
 object wldr=query_wielded();

 wldr->catch_msg("As you unwield the "+short()+" the shimmering light "+
   "seems to fade away.\n");
 tell_room(ENV(wldr),"As "+QTNAME(wldr)+" unwields the "+short()+" the "+
   "shimmering light seems to fade away.\n",wldr);

 add_adj("sharp-bladed");
 set_short("white sharp-bladed waraxe");

 return 1;
}

int rub(string str)
{
 object wldr=query_wielded();

 if(!wldr) return 0;

 NF("Rub what?\n");
 if(str!="handle" || !str) return 0;

 wldr->catch_msg("You rub the handle of the "+short()+".\n");
 tell_room(ENV(wldr),QCTNAME(wldr)+" rubs the handle of the "+short()+
   ".\n",wldr);

 if(lightning)
  {
   lightning=0;
   tell_room(ENV(wldr),"The humming noice suddenly stops and "+
     "lightnings disappear from the blade of the "+short()+".\n");
   return 1;
  }

 if(wldr->query_skill(SS_SPELLCRAFT)<20) 
   wldr->catch_msg("Low humming noice stats coming from the "+short()+
     ", but suddenly stops.\n"); 
 else
  {
   tell_room(ENV(wldr),"The "+short()+" starts producing low humming "+
     "noice and small lightnings start blazing all over its blade.\n");
   lightning=1;
  }

 return 1;
}

public varargs int did_hit(int aid,string hdesc,int phurt,object enemy,
int dt,int phit, int dam)
{
 object wldr=query_wielded();
 int skill=wldr->query_skill(SS_WEP_AXE)*3+
   wldr->query_skill(SS_SPELLCRAFT)/2;
 int dmg;

 if(wldr && lightning && random(skill)>random(350) && 
   wldr->query_mana()>=MANA_COST)
  {
   if(!wldr->query_npc()) wldr->add_mana(-MANA_COST);
   dmg=skill/3+random(20);
   dmg=dmg*(100-enemy->query_magic_res(MAGIC_I_RES_ELECTRICITY))/100;
   enemy->catch_msg("Blue bolt of lightning leaves the blade of the "+
     short()+" and hits you with loud hissing!\n");
   tell_room(ENV(wldr),"Blue bolt of lightning leaves the blade of "+
     "the "+short()+" and hits "+QTNAME(enemy)+" with loud hissing!\n",
     enemy);
   enemy->heal_hp(-dmg);
   if(enemy->query_hp()<0)
    {
     enemy->catch_msg("With a bone crashing sound a bolt penetrates "+
       "through your chest and explodes inside, tearing you apart.\n");
     tell_room(ENV(enemy),"With a bone crashing sound a bolt "+
       "penetrates through "+QTPNAME(enemy)+" chest and explodes "+
       "inside, tearing "+OBJ(enemy)+" apart.\n",enemy);
     enemy->do_die(wldr);
    }
  }

 return ::did_hit(aid,hdesc,phurt,enemy,dt,phit,dam);
}

string long_desc()
{
 string res="This axe is magnificent. It's well balanced, its blade "+
   "is very sharp and will never dull.";

 if(query_wielded()) res+=" Its blade glows with white shimmering "+
   "light , that almost blinds you.";
 if(lightning) res+=" Small lightnings are blazing all over its blade.";

 return res+"\n";
}

void check_still_worthy()
{
 object wldr=query_wielded();
 if(!wldr) return;

 if(meet_requerements(wldr)) return;

 wldr->catch_msg("You are no longer worthy to wield this axe!\n");
 unwield_me();
}

void leave_env(object from, object to)
{
 from->remove_a_axe_shadow();
 ::leave_env(from,to);
}

void enter_env(object inv, object from)
{
 object sh;

 if(!living(inv)) return;

 setuid();
 seteuid(getuid());
 sh=clone_object(STRHOLD_WEP+"a_axe_sh");
 sh->set_axe(TO);
 sh->shadow_me(inv);

 ::enter_env(inv,from);
}

