/* Gateguard at Thranduil's Cavern's made on april 26. 1993 */
/* Coded 24/4/1993 */

inherit "/std/monster";            /* For some reason, lots of monsters */
inherit "/std/act/action";         /* seem to have these statements.    */
inherit "/std/act/chat";           /* I guess mine had better have them */
#include "/sys/stdproperties.h"    /* aswell, otherwise they might feel */
#include "/sys/ss_types.h"         /* a bit left out.                   */
#include "/sys/macros.h"

void
create_monster()
{
   if (!IS_CLONE)
      return;
   
   /* Let guards help each other. */
   trig_new("%w 'attacks' %s","react_attack");
   
   /* Set name, race, short description and long description */
   add_name("gateguard");
   add_name("gateguard1");
   add_name("guard");
   set_name("eldaran");
   set_race_name("elf");
   set_short("Gateguard");
   set_long(break_string("It's Eldaran, on of Thranduil's Gateguards. "
         + "He is a dark elf, obviously of Silvan "
         + "origin. He looks competent in fights, "
         + "and you should think about it twice "
         + "before attacking him. \n",70));
   
   /* set physical properties */
   add_prop(CONT_I_WEIGHT,50000);
   add_prop(CONT_I_HEIGHT,1500);
   
   set_gender(0);
   
   /* stats -    STR  DEX  CON  INT  WIS  DIS */
   set_stats(({   50,  50,  50,  50,  50,  50}));
   set_hp(10000);
   set_alignment(400);
   
   /* Set unarmed attacks and armour classes. */
   set_all_hitloc_unarmed(30);
   set_all_attack_unarmed(30,30);
   
   seq_new("do_things");
   seq_addfirst("do_things", ({"@@arm_me","say Stay out!"}));
   
   /* Set the all important skills. */
   set_skill(SS_WEP_SWORD, 50);
   
   set_skill(SS_UNARM_COMBAT, 20);
   set_skill(SS_PARRY, 50);
   set_skill(SS_DEFENSE,50);
   
   set_act_time(5);
   add_act("emote carefully looks over the forest.");
   add_act("emote looks over you, carefully.");
   
   set_chat_time(5);
   add_chat("What are you doing here? Thranduil is not at home.");
   add_chat("Get lost, you don't belong here.");
}

arm_me()
{
   object armour, weapon;
   
   seteuid(getuid());
   
   armour=clone_object("/d/Rhovanion/common/armours/brigadine");
   armour->move(this_object());
   
   weapon=clone_object("/d/Rhovanion/common/weapons/gsword");
   weapon->move(this_object());
   
   command("wear " + armour->query_name());
   command("wield " + weapon->query_name());
}


string
react_attack(string who, string dummy)
{
   if (strlen(who))
      {
      who = lower_case(who);
      if (who != "andruil")
         call_out("attack_aggressor",2,who);
      command("smile");
   }
}

void
attack_aggressor(string who)
{
   object obj;
   
   if (obj = present(who, environment()))
      command("kill " + who);
}

