
inherit "/std/monster";
#include "/sys/ss_types.h"
#include <stdproperties.h>
#include <macros.h>

create_monster()
{
   set_race_name("dark elf");
   set_name("dark elf");
   add_name("luitenant");
   add_name("elf");
   add_name("dark elf");
   add_name("keeper");
   add_name("warrior");
   set_short("dark elf luitenant");
   set_pshort("dark elf luitenants");
   set_long("These evil creatures are the opposers of all light\n" +
      "and truth. They seek utter darkness for the world. They are pale\n"
      +"beings with dark hair, their beauty being that of the\n"
      +"shadows. They are wicked things.\n"
      +"This one being a luitenant, a great warrior.\n");
   
   set_stats(({ 66, 72, 68, 45, 45, 50}));
   set_alignment(-266);
   
   set_skill(SS_PARRY, 75);
   set_skill(SS_DEFENCE, 75);
   set_skill(SS_SPELLCRAFT, 60);
   set_skill(SS_WEP_SWORD, 78);
   set_skill(SS_WEP_POLEARM, 80);
   set_hp(9000);
   set_mana(9000);
   
   set_all_hitloc_unarmed(25);
   seq_new("do_things");
   seq_addfirst("do_things", "@@equip_me");
   
   set_act_time(5);
   set_chat_time(5);
   
   
}

equip_me(){
   
   object sword, helm, chain, shield;
   seteuid(getuid(this_object()));
   
   sword=clone_object("/d/Terel/mecien/dark/obj/evil_spear");
   sword->move(this_object());
   command("wield spear");
   helm=clone_object("/d/Terel/mecien/dark/obj/helmet");
   helm->move(this_object());
   command("wear helmet");
   chain=clone_object("/d/Terel/mecien/dark/obj/chainmail");
   chain->move(this_object());
   command("wear chainmail");
   shield=clone_object("/d/Terel/mecien/dark/obj/bshield");
   shield->move(this_object());
   command("wear shield");
}

