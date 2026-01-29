/* Gollum, a prelimenary version by Ilin(trying to code */
/* Coded 12/10/1993 */

inherit "/std/monster";            
inherit "/std/act/action";         
inherit "/std/act/chat";          
#include "/sys/stdproperties.h"  
#include "/sys/ss_types.h"      
#include "/sys/macros.h"

void
create_monster()
{
   if (!IS_CLONE)
      return;
   
   
   trig_new("%w 'attacks' %s","react_attack");
   
   /* Set name, race, short description and long description */
   set_name("gollum");
   add_name("smeagol");
   set_race_name("hobbit");
   set_short("Gollum");
   set_long(break_string("This spindly, twisting creature smirks at you. "
         + "It has once been a hobbit, but now it bears little "
         + "resemblance to that merry race. It's huge, glaring "
         + "eyes gleams in dull yellow, as it watches your every "
         + "move. Even though he grovels before you, you sense the "
         + "danger that he represents.\n",70));

   
   /* set physical properties */
   add_prop(CONT_I_WEIGHT,30000);
   add_prop(CONT_I_HEIGHT,1000);
   
   set_gender(0);
   
   /* stats -    STR  DEX  CON  INT  WIS  DIS */
   set_stats(({   50,  50,  50,  50,  50,  50}));
   set_hp(4000);
   set_alignment(-400);
   
   /* Set unarmed attacks and armour classes. */
   set_all_hitloc_unarmed(30);
   set_all_attack_unarmed(30,30);
   
   seq_new("do_things");
   seq_addfirst("do_things", ({"@@grin","say Nice master...nice masssster."}));
   
   /* Set the all important skills. */
   
   set_skill(SS_UNARM_COMBAT, 20);
   set_skill(SS_PARRY, 50);
   set_skill(SS_DEFENSE,50);
   
   set_act_time(5);
   add_act("emote peers suspiciously at you.");
   add_act("emote rubs his greenish hands in gleeful anticipation. ");
   
   set_chat_time(5);
   add_chat("Smeagol wants Precious, pretty Preciousssss....");
   add_chat("It's mine, I saysss...Mine!");
   add_chat("So sssad, they stole It from poor Smeagol."); 
}


void
attack_aggressor(string who)
{
   object obj;
   
   if (obj = present(who, environment()))
      command("kill " + who);
}

                                                                                                                                                                                                                                                                                                                                             
