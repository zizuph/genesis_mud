inherit "/std/monster";
inherit "/std/act/seqaction";
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <comb_mag.h>
#include <wa_types.h>

#define PATH "/d/Terel/mecien/valley/"
#define TP this_player()
#define TO this_object()
#define ENV environment

object sword;


create_monster(){
   
   set_name("vercus");
   set_race_name("human");
   set_living_name("vercus");
   set_adj("black-haired");
   add_adj("wizened");
   add_name("warlock");
   add_name("evoker");
   
   set_scar(2);
   show_scar(({"right shoulder", "forehead"}));
   
   set_title("the High Evoker of the Abyss");
   set_stats(({ 101, 111, 167, 134, 150, 76 }));
   set_skill(SS_DEFENCE, 120);
   set_skill(SS_PARRY, 50);
   set_skill(SS_WEP_SWORD, 75);
   set_skill(SS_UNARM_COMBAT, 55);
   
   set_appearance(99);
   set_alignment(-980);
   set_hp(9999);
   set_mana(9999);
   
   set_long("A charismatic man, standing medium height, his eyes\n"
  +"and hair now gray, fingers tips with sharp black claws. An aura\n" +
  "darkness seems to gather about him.\n");


   seq_new("do_things");
    seq_addfirst("do_things", "@@equip");
   set_chat_time(5);
   add_chat("We shall soon take the Shrine and desecrate its altars!");
   add_chat("Mystics are a breed of vile swine..");
   add_chat("I have killed many mystics in my time");
   add_chat("It is true, the prophet shall die at my hands");
   add_chat("I shall make all prostrate before my idols");
   add_chat("We must worship the Beast");
   
   
    add_ask("for absolution", "@@absolve", 1);
     add_ask(({"about curse", "about mystic curse", "mystic curse", "curse"}),
  "The warlock hisses: That foul power! If you bring me the robe of the holy cantor from " +
  "the Shrine, I can absolve you of it. Just bring it to me and ask for absolution and it shall be done!\n");

   setuid();
   seteuid(getuid(this_object()));
   
   set_act_time(1);
   add_act("smile satan");
   add_act("emote chews on his finger.");
    add_act("@@heal");
   set_cchat_time(1);
   add_cchat("You pitiful fool!");
   add_cchat("I am beyond your power!");
   
   set_cact_time(2);
   add_cact("@@battle");
   add_cact("@@wisk");
   add_cact("@@flame");
   add_cact("@@summon");
   add_cact("@@pain");
   
   set_all_hitloc_unarmed(60);
}

heal(){
  TO->heal_hp(40);
}

absolve(){
  object robe, who, curse;

  robe = present("holy_cantor_robe", TP);
  curse = present("mystic_curse", TP);
   who = TP;

  if(robe){
      command("shout AH! You have brought me the foul garment!");
  set_alarmv(2.0, -1.0, "remove_curse", ({ curse, who }));
   tell_room(ENV(TP), QCTNAME(TP) + " kneels down before " + QTNAME(TO) + " and hands him a white robe.\n", TP);
  TP->catch_msg("You kneel before the warlock and hand him the robe.\n");
  robe->remove_object();
  return 1;
   }
command("shout You have brought me nothing!");
command("shout But I shall indeed give you something!");
attack_object(TP);
wisk();
return 1;
}

equip(){
  object robe;
    robe = clone_object("/d/Terel/mecien/robe");
   robe->move(TO);
   command("wear robe");
}

remove_curse(object curse, object who){

   who->catch_msg("The warlock places his hand upon your head.\n");
 tell_room(ENV(who), QCTNAME(TO) + " places his hand upon " +
    QTNAME(who) + "'s head.\n", who);
  curse->remove_object();
   who->heal_hp(500);
    who->add_mana(100);
  return 1;
}

battle(){
   if(!sword){
      sword = clone_object("/d/Terel/mecien/bsword");
      sword->move(TO);
   }
   if(sword->query_wielded()){
      set_alarm(3.0, -1.0, "regen");
      return 1;
   }
   command("wield weapon");
   command("shout You are a fool to fight me!");
}

special_attack(object enemy){
   object me;
   mixed *strike;
   
   me = TO;
   if(random(3)) return 0;
   
   strike = enemy->hit_me(70 + random(70), MAGIC_DT, me, -1);
   
   me->catch_msg("You evoke the sinister demon powers!\n");
   if(strike[0] < 1){
      enemy->catch_msg(QCTNAME(me) + " tried to touch you but missed!\n");
      tell_watcher(QCTNAME(enemy) + " avoids the touch of " + QTNAME(me) +
         ".\n", enemy);
      return 1;
   }
   
   enemy->catch_msg(QCTNAME(me) + " touches you with his hand and it " +
      "eats away at your flesh!\n");
   tell_watcher(QCTNAME(me) + " touches " + QTNAME(enemy) +
      " with his hand, it spreads forth a foul darkness that seems to eat " +
      "away " + QTNAME(enemy) + "'s flesh!\n", enemy);
   if(enemy->query_hp() <= 0)
      enemy->do_die(me);
   return 1;
   
}
regen(){
   tell_room(ENV(TO), QCTNAME(TO) + " is surrounded by a purple aura.\n");
   TO->heal_hp(120 + random(250));
}

wisk(){
   object who, place;
   int loc;
   who = TO->query_attack();
   command("cackle satan");
   tell_room(ENV(TO), QCTNAME(TO) + " intones strange words and points a finger at " +
      QCTNAME(who) + ".\n", who);
   who->catch_msg(QCTNAME(TO) + " intones strange words and points at you.\n");
   loc = random(3);
   if(loc = 0) place = "/d/Terel/mecien/dark/n1";
   if(loc = 1) place = who->query_default_start_loc();
   if(loc = 2) place = "/d/Terel/common/town/mansion/entrance";
   set_alarmv(3.0, -1.0, "gone", ({ who, place }));
}

gone(object who, object place){
   tell_room(ENV(who), QCTNAME(who) + " fades into darkness!\n", who);
   who->catch_msg("You are covered by darkness!\n");
   who->move_living("M", place);
}

pain(){
   object who;
   who = TO->query_enemy();
   tell_room(ENV(TO), QCTNAME(TO) + " mumbles some arcane words.\n");
   who->catch_msg("A biting pain tears into your chest!\n");
   who->heal_hp(-(who->query_hp()/4));
   
}

summon(){
   
   object mon;
   
   setuid();
   seteuid(getuid());
   tell_room(ENV(TO), QCTNAME(TO) + " raises his hands and a black flame arises!\n");
   mon=clone_object("/d/Terel/mecien/mountains/hound");
   if (!mon)
      say("Failed to summon the hound!\n");
   mon->move_living("M", ENV(TO));
   tell_room(ENV(TO), "A black hound takes shapes from the flames.\n");
   mon->attack_object(TO->query_attack());
   mon->set_follow("vercus");
   return 1;
}

flame(){
   
   object EN;
   
   EN = TO->query_attack();
   tell_room(ENV(TO), QCTNAME(TO) + " calls up a blazing fire!\n");
   EN->catch_msg("You are burned by the flames.\n");
   EN->hit_me(60 + random(100), MAGIC_DT, TO, -1);
}



