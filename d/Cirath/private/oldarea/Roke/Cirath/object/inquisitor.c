inherit "/std/monster";
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"

#define INQ_LOG          (MONSTER + "inquis.log")
#define CEX if (!combat_extern) combat_reload()

int has_introduced=0;

void
create_monster()
{
    set_name("Lord Pius");
    add_name("pius");
    set_short("old white-bearded human");
    set_pshort("leader");
    set_race_name("human");
    set_gender(0);
    set_adj("old");
    add_adj("wise");
    set_long("This is the leader of the Holy Temple Order.\n"+
             "He seems to control huge powers.\n");
    set_base_stat(SS_STR, 160+random(20));
    set_base_stat(SS_DEX, 160+random(10));
    set_base_stat(SS_CON, 160+random(10));
    set_base_stat(SS_INT, 161+random(5));
    set_base_stat(SS_WIS, 160+random(5));
    set_base_stat(SS_DIS, 160+random(5));
    set_skill(SS_WEP_SWORD,80+random(10));
    set_skill(SS_WEP_CLUB,40+random(10));
    set_skill(SS_PARRY,90+random(5));
    set_skill(SS_DEFENCE,100+random(10));
    set_skill(SS_AWARENESS,100);
    set_skill(SS_SPELLCRAFT,100);
    set_skill(SS_FORM_ENCHANTMENT,60);
    set_skill(SS_FORM_CONJURATION,100);
    set_skill(SS_FORM_ABJURATION,60);
    set_skill(SS_FORM_ILLUSION,40);
    set_skill(SS_FORM_TRANSMUTATION,40);
    set_skill(SS_FORM_DIVINATION,20);
    set_skill(SS_ELEMENT_DEATH,100);
    set_skill(SS_ELEMENT_AIR,60);
    set_skill(SS_ELEMENT_FIRE,60);
    set_alignment(1801);
    add_prop(CONT_I_HEIGHT,170+random(20));
    add_prop(CONT_I_WEIGHT,65000+random(10000));
    add_prop(CONT_I_VOLUME,50000+random(20000)); 
    add_prop(LIVE_I_SEE_DARK,100);   
    add_prop(NPC_M_NO_ACCEPT_GIVE,0);
    add_prop(LIVE_I_SEE_INVIS,100);
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(LIVE_I_UNDEAD,50);
    add_prop(OBJ_I_RES_MAGIC,70);
    add_prop(OBJ_I_RES_DEATH,70);
    add_prop(OBJ_I_RES_LIFE,70);
    add_prop(OBJ_I_RES_WATER,20);
    add_prop(OBJ_I_RES_AIR,70);
    add_prop(OBJ_I_RES_EARTH,40);
    add_prop(OBJ_I_RES_FIRE,20);
    add_prop(OBJ_I_RES_COLD,60);
    add_prop(OBJ_I_RES_POISON,100);
    add_prop(OBJ_I_RES_ELECTRICITY,30);
    call_out("arm_me",1);
    set_chat_time(50);
    add_chat("Why are you here?\n");
    set_act_time(5);
    add_act("hmm");
    add_act("smile coldly");
    add_cact("wield sword");
    trig_new("%w 'introduces' %s", "react_introduce");

}

arm_me()
{
  seteuid(getuid(TO));
  clone_object(OBJ+"sacred_obj")->move(TO);
  clone_object(OBJ+"sacred_sword")->move(TO);
  clone_object(OBJ+"sacred_robe")->move(TO);
  command("wield all");
  command("wear all");
  command("wear brooch");
  say("I hate to be disturbed!");
}
void
react_introduce()
{
  if (!has_introduced)
  {
    call_out("introduce_me", 4);
    has_introduced=1;
    call_out("remove_int",15);
  }
}

void
introduce_me()
{
  command("introduce myself");
}

void
remove_int()
{
  has_introduced=0;
}

string
query_title()
{
  return "the III, High Inquisitor, Leader of The Holy Temple Order and Defender of All good";
}
int do_die(object killer)
{
   if (query_hp() > 0) 
      return 0;
   if (!killer) killer = previous_object();
   tell_object(killer,"You make a devastating blow on Pius throat.\n");
   write_file(INQ_LOG,TP->query_real_name()+" killed Pius the III, killers average stat was ("+killer->query_average_stat()+") "+
     extract(ctime(time()),4,15)+"\n");
   ::do_die(killer);
   move_all_to(E(TO));
   TO->remove_object();
   return 1;
}
