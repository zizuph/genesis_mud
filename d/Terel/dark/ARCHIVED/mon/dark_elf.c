#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;
#include "/sys/ss_types.h"
#include <stdproperties.h>
#include <macros.h>

public void
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
      "and truth. They seek utter darkness for the world. They are dark\n"
      +"beings with white hair, their beauty being that of the\n"
      +"shadows. They are wicked things.\n");
   
   set_stats(({ random(50) + 50, random(50)+50, random(50)+60, 
                       random(50) + 60, random(50) + 60, random(50) + 60}));
   set_alignment(-250-random(500));
   
   set_skill(SS_PARRY, 80);
   set_skill(SS_DEFENCE, 80);
   set_skill(SS_SPELLCRAFT, 60);
   set_skill(SS_WEP_SWORD, 80);
   set_skill(SS_WEP_POLEARM, 80);
   set_skill(SS_WEP_KNIFE,80);
   set_skill(SS_2H_COMBAT, 80);
   set_skill (SS_AWARENESS,  80);
   set_hp(9000);
   set_mana(9000);
   add_prop(LIVE_I_QUICKNESS,50);
   add_prop(LIVE_I_SEE_DARK, 3);
    add_prop(OBJ_M_HAS_MONEY, random(1000));
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

void
equip_me(){
   
   object sword, shield, helm, chain, cloak, boots;
   FIX_EUID;
   
   switch(random(5))
   {
       case 0:  sword=clone_object(DARK_DIR+"obj/halberd")->move(TO);
                    command("wield halberd");
                    shield=clone_object(DARK_DIR+"obj/bshield")->move(TO);
                    command("wear shield");
                    break;

       case 1:  sword=clone_object(DARK_DIR+"obj/ssword")->move(TO);
                    command("wield sword");
                    shield=clone_object(DARK_DIR+"obj/bshield")->move(TO);
                    command("wear shield");
                    break;

       case 2:  sword=clone_object(DARK_DIR+"obj/sabre")->move(TO);
                    command("wield sabre");
                    shield=clone_object(DARK_DIR+"obj/bshield")->move(TO);
                    command("wear shield");
                    break;

       case 3:  sword=clone_object(DARK_DIR+"obj/sabre")->move(TO);
                    command("wield sabre");
                    shield=clone_object(DARK_DIR+"obj/ddagger")->move(TO);
                    command("wield dagger");
                    break;

       case 4:  sword=clone_object(DARK_DIR+"obj/ssword")->move(TO);
                    command("wield sword");
                    shield=clone_object(DARK_DIR+"obj/ddagger")->move(TO);
                    command("wield dagger");
                    break;
    }


   helm=clone_object("/d/Terel/dark/obj/helmet")->move(TO);
   command("wear helmet");
   chain=clone_object("/d/Terel/dark/obj/chainmail")->move(TO);
   command("wear chainmail");
   cloak=clone_object("/d/Terel/dark/obj/cloak")->move(TO);
   command("wear cloak");
   boots=clone_object("/d/Terel/dark/obj/boots")->move(TO);
   command("wear boots");
}

