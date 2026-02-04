
inherit "/std/monster";
#include "/sys/ss_types.h"
#include <stdproperties.h>
#include <macros.h>

create_monster()
{
   set_race_name("dark elf");
   set_name("dark elf");
   add_name("elf");
   add_name("dark elf");
   add_name("keeper");
   add_name("warrior");
   set_short("dark elf");
   set_pshort("dark elves");
   set_long("These evil creatures are the opposers of all light\n" +
      "and truth. They seek utter darkness for the world. They are pale\n"
      +"beings with dark hair, their beauty being that of the\n"
      +"shadows. They are wicked things.\n");
   
   set_stats(({ 50, 46, 55, 40, 40, 40}));
   set_alignment(-250);
   
   set_skill(SS_PARRY, 50);
   set_skill(SS_DEFENCE, 60);
   set_skill(SS_SPELLCRAFT, 60);
   set_skill(SS_WEP_SWORD, 65);
   set_skill(SS_WEP_POLEARM, 60);
   set_hp(9000);
   set_mana(9000);
   
   set_all_hitloc_unarmed(20);
   seq_new("do_things");
   seq_addfirst("do_things", "@@equip_me");
   
   set_act_time(5);
   set_chat_time(5);
   add_chat("All glory resides in darkness");
   add_chat("We worship Shadow");
   add_chat("Someday our people will create the Utterdark");
   add_chat("The sun is a most foul creation");
   add_chat("Demons aid us in our journeys");
   
   set_random_move(25);
   
}

equip_me(){
   
   object sword, helm, chain;
   seteuid(getuid(this_object()));
   
   sword=clone_object("/d/Terel/mecien/dark/obj/halberd");
   sword->move(this_object());
   command("wield halberd");
   helm=clone_object("/d/Terel/mecien/dark/obj/helmet");
   helm->move(this_object());
   command("wear helmet");
   chain=clone_object("/d/Terel/mecien/dark/obj/chainmail");
   chain->move(this_object());
   command("wear chainmail");
}

