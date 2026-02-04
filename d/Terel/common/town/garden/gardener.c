
inherit "/std/monster";
#include "/sys/ss_types.h"
#include <macros.h>
#include <stdproperties.h>

#define ETO   environment(this_object())


create_monster()
{
   set_name("Linoris");
   add_name("elf");
   add_name("gardener");
   add_name("linoris");
   set_long("This smiling elf is garbed in a shining green\n" +
      "tunic and breeches, a purple cloak and hat. His face is\n" +
      "jovial and alive. He has violet eyes and gold hair.\n");
   
   set_stats(({ 40, 60, 30, 34, 20, 20}));
   set_alignment(450);
    set_short("Linoris the gardener");
   set_race_name("elf");
   set_skill(SS_DEFENCE, 30);
   set_skill(SS_SPELLCRAFT, 50);
   set_skill(SS_SWIM, 70);
   set_hp(9000);
   set_mana(9000);
    add_prop(LIVE_I_ALWAYSKNOWN,1);
   
   set_all_attack_unarmed(35);
   set_all_hitloc_unarmed(33);
   
   enable_commands();
   set_act_time(1);
   add_act("@@prune");
   add_act("smile");
   add_act("@@frolic");
   add_act("@@trim");
   add_act("@@sing_poem");
   add_act("@@weed");
   add_act("giggle");
   
   set_chat_time(5);
   add_chat("I love my garden!");
   add_chat("Evergreens are a sign of many blessings...");
   add_chat("Peace be unto you.");
   add_chat("There is always work to do here.");
   add_chat("Have you been to the arbor shrine?");
   add_chat("The minstrels like my garden!");
}

public string
prune(){
   tell_room(ETO,"The gardener prunes a tree.\n");
   return "";
}
public string
trim(){
   tell_room(ETO,"The gardener trims the hedges.\n");
   return "";
}
weed(){
   tell_room(ETO,"The gardener removes some weeds from the ground.\n");
   return 1;
}
sing_poem(){
   tell_room(ETO,"Linoris sings an ancient poem in honor of the stars.\n");
   return 1;
}
frolic(){
   tell_room(ETO,"The gardener dances about the garden merrily.\n");
   return 1;
}

