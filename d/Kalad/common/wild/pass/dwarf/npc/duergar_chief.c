inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#define QUEST_NAME "kabalquest"
int hammer;
string long;
object dewar;
void

/* by Korat */
create_monster()
{
   set_name("grunchor");
   add_name("duergar");
   set_race_name("dwarf");
   set_adj("cruel");
   add_adj("chief");
   set_long("This dwarf, turned evil in his lust for gold, "+
      "seems to be a lethal and ruthless leader of the duergars "+
      "in Underhome. The only way the dwarves have managed to control "+
      "him is through the everlasting promises of pure gold to "+
      "be his when the war against drows are at an end.\n");
   set_stats(({160,90,120,30,40,140}));
   set_alignment(-1000);
   set_skill(SS_UNARM_COMBAT,50);
   set_skill(SS_DEFENCE,100);
   set_skill(SS_PARRY,90);
   set_skill(SS_WEP_AXE,100);
   set_skill(SS_AWARENESS,70);
   set_title("warlord and chief of the Duergar-clan");
   set_act_time(3);
   add_act("grin demonically");
   add_act("emote chews on some meat.");
   add_act("emote stares at you with two black, evil eyes.");
   set_cact_time(3);
   add_cact("cackle");
   add_cact("say I will feast on your corpse!");
   add_speak("Get me that ring that shines so very nicely! "+
      "It is somewhere in the graveyard.\n");
   
   set_knight_prestige(500);
   add_prop(NPC_M_NO_ACCEPT_GIVE,0);
   trig_new("%w 'attacks' %s","react_attack");
}

int
react_attack(string who, string dummy){
   string *str_check;
   if(who){
      who = lower_case(who);
      str_check = explode(dummy, " ");
      if (sscanf(str_check[0],"you%s",dummy))
         {
         TO->command("emote screams: I shall slaughter you!!");
         return 1;
      }
      TO->command("shout Kill'em. Nice fun!");
      return 1;
   }
}

public void
enter_inv(object ob, object from)
{
   if(MASTER_OB(ob) != "/d/Kalad/common/wild/pass/dwarf/arm/kabal_ring")
   {
      ::enter_inv(ob, from);
      set_alarm(3.0,0.0,"drop_the_object",ob);
      return;
   }
   if(!interactive(from))
      return;
   else
      set_this_player(from);
   if(from->test_bit("Kalad",2,1))
      {
      write(query_The_name(from) + " grins at you and says: You've "+
         "brought it to me again! You stupid fool.\n");
      set_alarm(1.0,0.0,"drop_the_object",ob)
   }
   else
      {
      TO->command("say You got it ... I am rich!!");
      TO->command("thank "+from->query_real_name());
      TP->catch_msg("You feel more experienced!\n");
      TP->add_exp(10000);
      TP->set_bit(2,1);
      seteuid(getuid(TO));
      log_file(QUEST_NAME, extract(ctime(time()),4,15)+ " " +
         capitalize(TP->query_real_name()) + " rewarded with 10000 xp, "+
         "<"+TP->query_average_stat()+"> average stats.\n");
      set_alarm(2.0,0.0,"remove_the_object",ob);
   }
   ::enter_inv(ob, from);
   set_alarm(3.0,0.0,"drop_the_object",ob);
}
void
drop_the_object(object ob)
{
   command("drop all");
}
void
remove_the_object(object ob)
{
   object dewar;
   write("The duergar chief runs away with an insane "+
      "cackle echoing behind him.\n");
   if(dewar = present("grunchor",E(TP)))
      {
      dewar -> remove_object();
   }
}

