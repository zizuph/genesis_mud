#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>

inherit "/std/armour";
inherit "/lib/keep";

#define MANA_SCARE 25
#define SKILL(who, what) who->query_skill(what)

object wearer;

int do_frighten(object a, object v);
int fear(string s);

void
create_armour()
{
   set_name("helmet");
   set_adj("skull");
   set_short("frightening looking skull helmet");
   set_long("This is a frightning looking skull helmet.\n"+
      "It is a full helmet, shaped as a skull, with "+
      "remains of flesh, or flesh-like material, attached "+
      "to its sides. It has obviously been used by someone "+
      "in constant fights, as it bears mark of axe and sword "+
      "cuts. The most eminent feature of this head-gear, however, "+
      "is its eye-sockets. They reek of death and destruction, "+
      "radiating an aura of evil. The whole piece would probably "+
      "cast fear on wimpy creatures with little battle experience.\n");
   set_ac( 43 );
   set_at( A_HEAD );
   set_am( ({ -2, 3, 1}) );
   set_af( this_object() );
   
   add_prop(OBJ_I_WEIGHT, 2620);
   add_prop(OBJ_I_VALUE,  5*12*12+2*12+3); /* Price: 5 g 2 s */
   add_prop(OBJ_I_VOLUME, 640);
   add_prop(MAGIC_AM_MAGIC, ({ 20, "spells" }));
   add_prop(MAGIC_AM_ID_INFO,
      ({
            "This is a magical frightening looking skull helmet.\n", 1,
            "This helmet has the ability to cast a frighten spell.\n", 20,
            "This helmet has the ability to frighten others by casting "+
            "a frighten spell. The syntax is: frighten <who>\n",45
       }) );
   add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_S_WIZINFO,"When worn, the wearer has the ability to cast " +
        "a frighten spell on its enemies.\n");
}
public wear(object to)
{
   wearer = TP;
   wearer->add_subloc("_special_look", this_object());
}
public remove(object to)
{
   wearer->remove_subloc("_special_look");
   wearer = 0;
}

string
show_subloc(mixed subloc, object on, object who)
{
   if(subloc!="_special_look")
      return "";
   if(who->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
      return "";
   if(!query_worn())
      return "";
   if(who==ETO)
      return "You look quite frightening wearing that skull helmet!\n";
   else
      return CAP(HE_SHE(ETO))+" looks quite terrifying wearing that skull helmet!\n";
}

void
init()
{
   ::init();
   add_action("cast","cast");
   add_action("fear","frighten");
}

int
cast(string str)
{
   string who;
   
   if (!str) return 0;
   if (str=="fear")
      return fear("");
   if (sscanf(str,"fear on %s",who)==1)
      return fear(who);
   return notify_fail("Cast fear on who?\n");
}

int
fear(string str)
{
   object victim;
   
   if (strlen(str))
      victim = present(str, environment(this_player()));
   else
      victim = TP->query_attack();
   
   if (!living(victim) ||
     (victim==this_player()) || 
      victim->query_prop(OBJ_M_NO_ATTACK) ||
      victim->query_prop(OBJ_I_NO_ATTACK))
   {
      return notify_fail("You can't frighten that!\n");
   }
   
   if (ETP->query_prop(ROOM_M_NO_MAGIC) ||
       ETP->query_prop(ROOM_M_NO_MAGIC_ATTACK))
   {
       return notify_fail("This is a area where noone is frightened.\n");
   }

   return do_frighten(victim, TP);
}

int
do_frighten(object victim, object attacker)
{
   int i;
   int success, alv, ala;
   string how;
   
   if(!query_worn())
   {
      return notify_fail("You must wear the skull helmet first!\n");
   }
   
   if(attacker->query_mana()<MANA_SCARE)
   {
      return notify_fail("You are too mentally exhausted to do that.\n");
   }
   
   attacker->add_mana(-MANA_SCARE);
   
   /* If low on skills, or on stats, we backfire.. */
   
   if (WIS(attacker) + INT(attacker) + DIS(attacker) + SKILL(attacker, SS_SPELLCRAFT) + 
         SKILL(attacker, SS_FORM_ABJURATION) + SKILL(attacker, SS_ELEMENT_DEATH) < 300)
   { 
      if (random(2))
      {
         attacker->catch_msg("You failed to scare "+QTNAME(victim)+".\n");
         victim->catch_msg(QCTNAME(attacker)+" tries to scare you but "+
            "fails.\n");
         tell_room(ENV(attacker),QCTNAME(attacker)+" tries to scare "+QTNAME(victim)+
            " but fails.\n",({attacker,victim}));
      }
      else if (!attacker->query_npc())
      { // Backfire!
         attacker->catch_msg("You make a pathetic attempt to scare "+
            QTNAME(victim)+" but fail!\n");
         victim->catch_msg(QCTNAME(attacker)+" makes a pathetic attempt "+
            "to scare you, but fails!\n");
         tell_room(ENV(attacker),QCTNAME(attacker)+" attempts to scare "+
            QTNAME(victim)+", but fails!\n",({attacker,victim}));
         attacker->add_panic(success/4+1);
         attacker->query_combat_object()->cb_may_panic();
      }
      return 1;
   }    
   
   
   ala = attacker->query_alignment();
   alv = victim->query_alignment();
   
   success = ala*ala + alv*alv;
   success = (victim->query_whimpy()+random(10)+1)*success/100;
   success /= 200;
   
   if (DIS(attacker)<DIS(victim))
      success += 10*(DIS(attacker)-DIS(victim));
   else
      success += (DIS(attacker)-DIS(victim));
   
   success = MIN(100, success);
   
   if (success > 0)
   {
      success = random(success)+1;
      switch(success)
      {
         case 1..10:
         attacker->catch_msg("You disturb "+QTNAME(victim)+".\n");
         victim->catch_msg(QCTNAME(attacker)+" disturbs you.\n");
         tell_room(ENV(attacker),QCTNAME(attacker)+" disturbs "+
            QTNAME(victim)+".\n",({victim,attacker}));
         break;
         case 11..40:
         attacker->catch_msg("You scare "+QTNAME(victim)+" a bit.\n");
         victim->catch_msg(QCTNAME(attacker)+" scares you somewhat.\n");
         tell_room(ENV(attacker),QCTNAME(attacker)+" scares "+
            QTNAME(victim)+" somewhat.\n",({victim,attacker}));
         break;
         case 41..60:
         attacker->catch_msg("You scare the living daylights out of "+
            QTNAME(victim)+"!\n");
         victim->catch_msg(QCTNAME(attacker)+" scares the living " +
            "daylights out of you!\n");
         tell_room(ENV(attacker),QCTNAME(attacker)+" scares the " +
            "living daylights out of "+ QTNAME(victim)+
            "!\n",({attacker,victim}));
         break;
         case 61..80:
         attacker->catch_msg("You scare "+QTNAME(victim)+
            " almost to death!\n");
         victim->catch_msg(QCTNAME(attacker)+" scares you almost " +
            "to death!\n");
         tell_room(ENV(attacker),QCTNAME(attacker)+" scares "+
            QTNAME(victim)+" almost to death!\n",({attacker,victim}));
         break;
         case 81..100:
         attacker->catch_msg(QCTNAME(victim)+"'s bones shiver " +
            "as you scare "+ HIM_HER(victim)+
            " into the valley of Death!\n");
         victim->catch_msg("Your bones shiver as "+QTNAME(attacker)+
            " scares you into the valley of Death!\n");
         tell_room(ENV(attacker),QCTNAME(victim)+"'s bones shiver as "+
            QTNAME(attacker)+" scares "+HIM_HER(victim)+
            " into the valley of Death!\n",({attacker,victim}));
         break;
       }
      victim->catch_msg("You struggle to control yourself!\n");
      
      victim->add_panic(success/4+1);
      victim->query_combat_object()->cb_may_panic();
      if(victim->query_npc())
         victim->attack_object(attacker);
   }
   else 
      {
      attacker->catch_msg("You failed to scare "+QTNAME(victim)+".\n");
      victim->catch_msg(QCTNAME(attacker)+" tries to scare you, but fails.\n");
      tell_room(ENV(attacker),QCTNAME(attacker)+" tries to scare "+
         QTNAME(victim)+", but fails.\n",({attacker,victim}));
   }
   return 1;
}

string
query_recover()
{
   return MASTER+":"+ query_arm_recover() + query_keep_recover();
}
 
void
init_recover(string arg)
{
   init_arm_recover(arg);
   
   init_keep_recover(arg);
}
