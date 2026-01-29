#pragma save_binary

inherit "/std/monster";
#include "/sys/ss_types.h"
#include "/sys/macros.h"

create_monster()
{
   if (!IS_CLONE)
      return;
   set_name("sam");
   set_race_name("hobbit"); 
   set_adj(({"nice","friendly"}));

   set_long("The hobbit seems friendly to you, and he smiles all the time.\n");

   default_config_npc();
   set_alignment(75);
   set_base_stat(SS_CON, 50);
   set_hp(1000);
   seq_new("do_echo");
   seq_addfirst("do_echo","@@make_noise");

   set_chat_time(2);
   add_chat("echo: The hobbit pees in a corner.");
   add_chat("And ain't it a lovely day?");

   add_cchat("Why do you hit me?");
   add_cchat("Please, I mean you no harm.");
   add_cchat("You horrible beast!");

   set_living_name("sam");
}

init() {
   add_action("my_say","say",0);
}

make