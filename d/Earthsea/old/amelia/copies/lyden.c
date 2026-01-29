inherit "/std/monster";
inherit "/std/act/action";

#include </d/Roke/common/defs.h>
#include <ss_types.h>
#include "/sys/wa_types.h"
#include <macros.h>
#include "/d/Roke/Athas/gladiator/guruquest.h"

mixed attackers;
int has_introduced=0;

void
create_monster ()
{
   set_living_name("lyden");
   set_name("lyden");
   set_race_name("human");
   add_adj("gargantuan");
   add_adj("powerful");
   set_short("powerful gargantuan human");
   set_long("This man is a gladiator from Athas. Lucky for "+
      "him he has a sturdy endurance and was able to escape the "+
      "plague. Although he managed to get free, he still wanders the "+
      "area looking for a worthy opponent to fight.\n");
   
   set_stats(({ 200, 170, 170, 75, 75, 200}));
   set_skill(SS_UNARM_COMBAT, 75);
   set_skill(SS_WEP_POLEARM, 100);
   set_skill(SS_BLIND_COMBAT, 100);
   set_skill(SS_DEFENCE, 100);
   set_skill(SS_PARRY, 100);
   set_title("Independent Gladiator of World Renown");
   set_alignment(-100);
   
   heal_hp(10000);
   
   set_all_hitloc_unarmed(50);
   
   set_act_time(6);
   add_act("emote looks you up and down and laughs harshly at your"+
      " puny body.");
   add_act("emote breaks a cinder block over his head."+
      " Women run to take their children off the street.\n");
   add_act("spit");
   add_act("emote stomps on the ground, causing the earth to"+
      " tremble and shake.");
   set_chat_time(4);
   add_chat("I am the greatest fighter in the world!");
   add_chat("No one can defeat me!");
   add_chat("I challenge anyone to a fair fight!...\n"+
      "Hell! I challenge anyone to an unfair fight!");
   add_chat("Are you even brave enough to attack, small one?");
   set_cchat_time(3);
   add_cchat("You were brave enough to attack, but are you smart"+
      " enough to flee?");
   add_cchat("I will do away with you quickly, flea!");
   add_cchat("Why do you persist? You have no chance of defeating me!");
   add_cchat("Is that the best you can do?");
   add_cchat("I must confess, you really are one of the most"+
      " pitiful warriors I have ever seen.");
   add_cchat("I WILL KILL YOU!!!");
   
   trig_new("%w 'introduces' %s", "react_introduce");
   
   call_out("arm_me",1);
}
arm_me()
{
   seteuid(getuid(TO));
   clone_object("/d/Roke/Athas/weapons/trident")->move(TO);
   clone_object("/d/Roke/Athas/armours/greaves")->move(TO);
   clone_object("/d/Roke/Athas/armours/vhelm")->move(TO);
   clone_object("/d/Roke/Athas/armours/gaunt")->move(TO);
   
   command("wear all");
   command("wield all");
   
}

query_knight_prestige(){return 400;}

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

attacked_by(ob)
{
   ::attacked_by(ob);
   
   if (!pointerp(attackers)) attackers = ({});
   
   if (member_array(ob,attackers) == -1)
      attackers += ({ob});
}

do_die(killer)
{
   object cuir;
   
   if (query_hp() > 0) return;
   
   if (sizeof(attackers) <= 1)
      if (cuir = present(CUIR_ID,killer))
      {
      cuir->report_kill(LYDEN);
#ifdef GURUDEBUG
         killer->catch_msg("Yes, a guru kill!\n");
#endif
   }
   ::do_die(killer);
}
