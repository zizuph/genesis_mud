inherit "/d/Terel/std/mystic";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h";

#define TO this_object()

create_monster(){
   
  ::create_monster();
   set_living_name("loreseth");
   set_name("loreseth");
    
   
   set_mystic_skills();
   set_race_name("human");
   set_adj(({"wizened", "green-eyed"}));
   
    set_blessed(1);
   set_rank(MYSTIC_ARCHON);
   set_stats(({ 90, 98, 141, 100, 100, 87 }));
    set_skill(SS_DEFENCE, 70);
  set_base_stat(SS_OCCUP, 144);
   
   set_random_move(5, 1);
   enable_auto_hail();
   set_chat_time(1);
    add_chat("I believe one day all things shall be restored");
   add_chat("It is good that evil be purged from the land");
   add_chat("I will do what I can to defend the holy place");
   add_chat("Though I may speak of Mystery, my way is plain and my path is long");
   add_chat("The wicked may enshroud me, but ever shall I cling to the sacred stone upon the hill");
   add_chat("Fire is easy to behold, but not easy to bear");
   add_chat("Those who are wise will remain");
   add_chat("I have heard tell of wicked sorcerors in the wildlands");
    add_chat("Evil creatures once stole many things of the shrine, now they lay hidden...");
    add_chat("One day, I too, will lie in the deep places, with my brethren");
    add_chat("Asrafar will watch over the Valley long after I perish");
    add_chat("In the dark place there is an evil beast that slew one of the great archons");
      add_chat("The man-horse slew the priest of Calathin back in the War of Sorcery");
    add_chat("I pray that evil will never again enter the sacred places");
   add_chat("If the evil beast is slain, some good may return to the world");
     add_ask(({"about priest", "priest", "about priest of Calathin", "priest of Calathin"}), 
  VBFC("answer1"), 1);
   add_ask(({"about beast", "about evil beast", "evil beast", "beast"}),
    VBFC("answer2"), 1);
add_ask(({"about items", "items", "sacred items", "about lost items", "treasures", 
  "about lost items", "stolen items", "about stolen items"}),
   VBFC("answer3"), 1);
   
   set_act_time(5);
    add_act("pray");
     add_act("chant");
   set_cact_time(1);
   add_cact("flammis");
   set_alignment(900);
   
   
  set_all_attack_unarmed(55);
  set_all_hitloc_unarmed(70);
}

answer1(){
TO->command("say The priests of Calathin have been taught through the ages by the Ancient Order");
}

answer2(){
TO->command("say The evil beast abides in the dark regions, a creature of magic, " +
"it has many powers, it has deadly poison and terrible fire!");
}

answer3(){
TO->command("say Lost from the shrine were many sacred things and many items that " +
"were used in defense. For in days gone by, we had many other treasures that " +
"were created for our use");
}


