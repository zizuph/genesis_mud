/* Base code for kirk manachs
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           1/5/98     Created
** Tapakah        8/2021     Refactored
*/

#pragma no_clone
#pragma strict_types

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <filter_funs.h>

#include "/d/Khalakhor/sys/paths.h"
#include "defs.h"

inherit BASE_NPC;

#define  MAX_WIS_ADJUST   10    /* 0 to 9 added to SS_WIS of monk         */
#define  HP_TO_WIS_FACTOR 5     /* raw hit hp = FACTOR * adjusted SS_WIS  */
#define  CAST_DELAY       5.0   /* delay from spell cast to effect        */
#define  HIT_CHANCE       5     /* 20% chance of special attack occurring */
 
int casting=0;                  /* is monk concentrating on a spell?      */
 
#define  ADJ1 (({                                                       \
                 "elderly","balding","young","stern","solemn","contemplative", \
                 "stout","quiet","mysterious","pious","sturdy","prayerful", \
                 "pale","wizened","studious","ascetic","humble","stoical","dark", \
                 "middle-aged","energetic","calm","reverent","devout","tanned" \
               }))
#define  ADJ2 (({                                                       \
                 "black-haired","red-haired","grey-haired","white-haired", \
                 "brown-haired","blond-haired", "black-bearded","red-bearded", \
                 "grey-bearded","white-bearded","brown-bearded","blond-bearded", \
                 "blue-eyed","brown-eyed","green-eyed","white-eyed","grey-eyed", \
                 "yellow-eyed","black-eyed","long-faced","round-faced"  \
               }))
 
string
defans () {
   command("say Perhaps you should ask that of Abbot Semion.");
   return "";
}

void
set_wander (string rpath, string home, int sec)
{
  set_restrain_path(rpath);
  set_monster_home(home);
  set_random_move(sec);
}

void
vest_me (string *vest)
{
  int i;
  for (i=0; i<(sizeof(vest)); i++)
    (clone_object(SR_ARMOUR+vest[i]))->move(TO);
  TO->command("wear all");
}
 
void
set_random_manach_desc (string name)
{
  string adj1=ADJ1[(random(sizeof(ADJ1)))];
  string adj2=ADJ2[(random(sizeof(ADJ2)))];
  if (!IS_CLONE)
    return;
  set_name(name);
  add_name(SR_NPC_ID);
  add_name("monk");
  set_adj(({adj1,adj2}));
  set_short(adj1+" "+adj2+" "+name);
}
 
void
set_manach_stats (int stat)
{
  set_stats(({stat*9/10,stat*9/10,stat,stat*11/10,stat*11/10,stat*9/10}));
  set_skill(SS_WEP_POLEARM, stat);
  set_skill(SS_PARRY,       stat);
  set_skill(SS_DEFENCE,     stat);
  set_alignment(stat*10);
  set_random_size_descs();
  add_prop(ATTACK_TEAM,SR_TEAM);
  add_prop(NPC_M_NO_ACCEPT_GIVE," can not accept gifts from you.\n");
  add_prop(NPC_I_NO_LOOKS, 1);
}
 
varargs void
setup_base_manach (int stat, string name="manach")
{
  set_random_manach_desc(name);
  set_manach_stats(stat);
  set_default_answer(defans);
}

void
attacked_by (object enemy)
{
  string  my_team_id = (TO->query_prop(ATTACK_TEAM));
  object  TR         = ENV(TO);
  object *inv        = (FILTER_PRESENT_LIVE(all_inventory(TR))) - ({TO});
  int     i;

  // if enemy gone or i'm not on a team, nothing to do
  if (! objectp(enemy) && stringp(my_team_id))
    return;

  // do normal attacked_by
  ::attacked_by(enemy);

  // check living in room. If on our team, call attacker
  for (i=0; i<sizeof(inv); i++) {
    if ((inv[i]->query_prop(ATTACK_TEAM) == my_team_id) /* same team */
        && ! inv[i]->query_prop(ATTACK_PASSIVE)
        && ! inv[i]->query_attack())                     /* !fighting */
      inv[i]->command("$kill " + OB_NAME(enemy));
  }
}
 
/*
** do_conjure - spell effect of conjuring the wooden staff
*/
void
do_conjure (object me)
{
  object staff;
  casting=0;
  seteuid(getuid());
  staff=clone_object(SR_WEAPON+"staff");
  staff->move(me);
  me->command("emote beseechingly chants: Dedim Rhodendum da Irgalach!");
  tell_room(environment(me),"In a flash of light, a "+(staff->query_short())+
            " appears in the upraised hands of "+QTNAME(me)+"!\n");
  me->command("emote lowers his head and stares calmly ahead.");
  me->command("wield staff");
}
 
/*
** do_enflame - spell effect of inflaming the staff
*/
void
do_enflame (object me)
{
  object staff=present(SR_STAFF_ID,me);
  casting=0;
  if (!(objectp(staff))) return;
  me->command("wield staff"); /* just in case */
  me->command("emote vigoursly chants: Ferrach Sagradem da Rhiannon!");
  staff->enflame(me->query_stat(SS_WIS));
  me->command("emote lowers his head and smiles confidently.");
}
 
/*
** do_throw - spell effect of throwing an arc/sheet of fire at enemies
*/
void
do_throw (object me)
{
  object  staff=present(SR_STAFF_ID,me);
  object* enemy=(me->query_enemy(-1)); /* get list of enemies */
  object  room=environment(me);
  int     i,hp,adj_wis,res;
  casting=0;
 
  /* make sure there are still enemies and monk has a flaming staff */
  if (!(pointerp(enemy)))  return;
  if (!(objectp(staff)))   return;
  if (!(staff->enflamed())) return;
 
  /* preparatory emotes */
  me->command("wield staff"); /* just in case */
  me->command("emote boldly chants: Searum da Ilfidach ta Sean Rhian!");
  me->command("emote swings his "+(staff->query_short())+" through the "+
              "air arcing out a sheet of fire!");
 
  /* hit each enemy */
  for (i=0; i<sizeof(enemy); i++) {
    /* calculate hit hp based on randomly-adjusted monk WIS and */
    /* the fire resistance of the enemy                         */
    adj_wis = (me->query_stat(SS_WIS)) + random(MAX_WIS_ADJUST);
    res     = (enemy[i])->query_magic_res(MAGIC_I_RES_FIRE);
    hp      = (adj_wis * HP_TO_WIS_FACTOR);
    hp      = -((hp * (100-res)) / 100);
    tell_room(room,QCTNAME(enemy[i])+" is engulfed in the flames!\n",
              enemy[i]);
    (enemy[i])->catch_msg("You are engulfed in the arc of fire!\n");
    (enemy[i])->heal_hp(hp);
  }
}
 
/*
** special_attack - main function
*/
int
special_attack (object victim)
{
  object me= this_object();
  object staff;
  string wdesc;
 
  if (casting)            return 1;       /* no attacks while casting  */
  if (random(HIT_CHANCE)) return 0;       /* normal attack % of time   */
 
  /* if no staff, conjure the staff */
  staff=present(SR_STAFF_ID,me);
  if (!(objectp(staff))) {
    me->command("emote raises his fists above his head and gazes upward!");
    me->command("emote begins to entone a prayerful chant.");
    casting=1;
    set_alarm(CAST_DELAY,0.0,&do_conjure(me));
    return 1;
  }
 
  /* if staff not wielded, wield it and continue normal attack */
  if (!(objectp((staff->query_wielded())))) {
    me->command("wield staff");
    return 0;
  }
 
  /* if staff is not flaming, enflame it */
  wdesc=(staff->query_short());
  if (!(staff->enflamed())) {
    me->command("emote raises his "+wdesc+" over his head and gazes "+
                "upward!");
    me->command("emote begins to entone a prayerful chant.");
    casting=1;
    set_alarm(CAST_DELAY,0.0,&do_enflame(me));
    return 1;
  }
 
  /* has staff, is wielded and flaming, use throw fire */
  me->command("emote raises his "+wdesc+" over his shoulder like a "+
              "club and closes his eyes!");
  me->command("emote begins to entone a prayerful chant.");
  casting=1;
  set_alarm(CAST_DELAY,0.0,&do_throw(me));
  return 1;
}

void
hook_return_intro_new (string str)
{
  command("introduce myself");
  command("bow " + str);
  command("emote holds out his hands.");
  command("say The harmony of Ardaugh be with you, "+capitalize(str)+"!");
  (find_player(lower_case(str)))->add_introduced(lower_case(query_name()));
}
