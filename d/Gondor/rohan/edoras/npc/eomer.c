/*
 * Gwyneth 4 November 2000 - Replaced ~elessar/lib/goodkill.h with
 *                           /d/Gondor/common/lib/logkill.c
 */
inherit "/d/Gondor/rohan/edoras/npc/team";
#include "/d/Gondor/common/lib/logkill.c" 
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"

create_monster() 
{
  if (!IS_CLONE)
    return;
  set_living_name("eomer");
  set_name(({"doorward","guard","eomer","Eomer"}));
  add_name("rohirrim");
  set_race_name("human");
  set_adj(({"tall","golden-haired"}));
  set_short("tall, golden-haired Doorward of Theoden");
  set_long(BS("This is Hama, the Doorward of Theoden. He is the chief guard of the gates to the golden hall Meduseld. " +
    "Like most Rohirrim, he is taller than other men. His golden hair is braided on his shoulders.\n"));
  default_config_npc(80);
  set_base_stat(SS_CON,95);
  set_base_stat(SS_STR,95);
  set_hp(5000);
  set_skill(SS_WEP_SWORD, random(10)+90);
  set_skill(SS_DEFENCE, random(10)+90);
  set_skill(SS_PARRY, random(10)+90);
  set_alignment(500+random(250));
  set_chat_time(5);
  add_chat("Hail, comers from afar!");
  add_chat("Welcome to Meduseld!");
/*
  add_chat("I am the Doorward of Theoden, Hama is my name.");
  add_chat("Here I must bid you lay aside your weapons before you enter.");
*/
  add_chat("It is the will of Theoden that you lay aside your weapons!");
  add_chat("This is the house of Theoden.");
  add_chat("Lay down your weapons, if you would not fight against all the men in Edoras.");
  add_cchat("Forth Eorlingas! Kill these intruders!");
  add_cchat("To arms, Eorlingas! Intruders at Meduseld! To arms!");
  add_cchat("Guards! Help!");
  seq_new("do_things");
  seq_addfirst("do_things",({"@@get_armed","say I am the Doorward of Theoden, Hama is my name.","present me","say Here I must bid you lay aside your weapons before you enter."}));
}

get_armed()
{
  object wep, arm;
  seteuid(getuid(this_object()));
  wep = clone_object("/d/Gondor/rohan/edoras/obj/guardsword");
  wep->move(this_object());
  command("wield sword");
  arm = clone_object("/d/Gondor/rohan/edoras/obj/corslet");
  arm->move(this_object());
  command("wear armour");
  arm = clone_object("/d/Gondor/rohan/edoras/obj/roshield");
  arm->move(this_object());
  command("wear armour");
}

/* solemnian prestige */
query_knight_prestige() {return (-12);}
