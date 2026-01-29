inherit "/std/monster";
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <comb_mag.h>
#include <wa_types.h>

#define PATH "/d/Terel/mecien/valley/"

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
   set_stats(({ 101, 89, 96, 112, 120, 76 }));
   set_skill(SS_DEFENCE, 100);
   set_skill(SS_PARRY, 50);
   set_skill(SS_WEP_SWORD, 75);
   set_skill(SS_UNARM_COMBAT, 55);
   
   set_appearance(99);
   set_alignment(-766);
   set_hp(9999);
   set_mana(9999);
   
  clone_object("/d/Terel/mecien/robe")->move(TO);
  
  set_long("He is a charismatic man, standing medium height, with sharp\n"
  + "blackened claws, his hair and eyes now gray.\n");

  command("wear robe");
   set_chat_time(5);
   add_chat("We shall soon take the Shrine and desecrate its altars!");
   add_chat("Mystics are a breed of vile swine..");
   add_chat("I have killed many mystics in my time");
   add_chat("It is true, the prophet shall die at my hands");
   add_chat("I shall make all prostrate before my idols");
   add_chat("We must worship the Beast");
   
   enable_commands();
   
   seteuid(getuid(this_object()));
   clone_object("/d/Terel/mecien/bsword")->move(this_player());
   
   set_cchat_time(1);
   add_cchat("You pitiful fool!");
   add_cchat("I am beyond your power!");
   
   set_cact_time(1);
   add_cact("@@flame");
   add_cact("@@summon");
   add_cact("@@pain");
   add_cact("grin demonically");
   
   set_all_hitloc_unarmed(60);
}

pain(){
}

summon(){
   
   object mon;
   
   seteuid(getuid(this_object()));
   say(QCTNAME(this_object()) + " raises his hands and a black flame arises!\n");
   mon = clone_object("/d/Terel/mecien/mountains/hound");
   mon->move_living("X", environment(this_object()));
  mon->command("kill " + this_object()->query_enemy()->query_real_name());
   mon->set_follow("vercus");
   return 1;
}

flame(){
   
   object EN;
   
}



