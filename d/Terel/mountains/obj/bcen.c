

inherit "/std/monster";
inherit "/std/combat/unarmed";
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>

#define A_KICK 0
#define A_BASH 1
#define A_BITE 2

create_monster(){
   set_living_name("Norgudun");
   set_race_name("centaur");
set_adj(({"wild", "bronze-skinned"}));
   
 set_long(
"A wild and frightful vision. This great monster, being " +
"half-horse and half-man, is is filled with tempest, its hair long and shaggy, " +
"with a face of madness. " +
"With eyes of bloodshot olive, bronzed skin and nearly fanged mouth, this " +
"horrifying creatures appears more demonic than anything!" +
"\n");
default_config_npc(44);
set_base_stat(SS_CON, 125);
set_base_stat(SS_STR, 141);
set_base_stat(SS_DEX, 92);

set_act_time(1);
add_act("growl");
add_act("emote pulls at his hair.");
add_act("spit");
add_act("emote foams at the mouth.");
set_chat_time(1);
add_chat("When Calathin is no more, then evil will return!");
add_chat("Those witches on the hill will die by my hands!");
add_chat("I have their water!");
add_chat("Let the dragon know my name!");
add_chat("Die!");
add_chat("This world is full of fools!");
add_chat("Hate is in my heart and I am full of madness!");
set_alignment(-435);
set_aggressive(1);
set_all_hitloc_unarmed(60);
   set_hp(100000);
   set_skill(SS_DEFENCE, 85);
   set_skill(SS_WEP_AXE, 100);
    set_skill(SS_PARRY, 60);


set_random_move(5);

set_attack_unarmed(A_KICK, 66, 54, W_BLUDGEON, 45, "fierce kicking hooves");
set_attack_unarmed(A_BASH, 40, 40, W_BLUDGEON, 25, "bashing body");
set_attack_unarmed(A_BITE, 21, 15, W_IMPALE, 16, "fanged mouth");

seq_new("do_things");
seq_addfirst("do_things", "@@arm_me", "growl");
}

arm_me(){
object axe, fur, coat, misc, ob, shield, purse;
seteuid(getuid(this_object()));
command("jump");
axe = clone_object("/d/Terel/mountains/obj/haxe");
axe->move(this_object());
command("wield axe");
command("shout Death!");
fur = clone_object("/d/Terel/mountains/obj/fur");
fur->move(this_object());
command("wear coat");
coat = clone_object("/d/Terel/mountains/obj/coat");
coat->move(this_object());
command("wear coat");
purse = clone_object("/d/Terel/common/moor/sack");
purse->move(this_object());
misc = clone_object("/d/Terel/mountains/obj/mace");
misc->move(this_object());
}

