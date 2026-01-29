/* Trapper, a "1.st edition" by Ilin */
/* Coded 21/10/1993 */

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
   add_name("trapper");
   add_name("calvin");
   set_name("trapper");
   set_race_name("human");
   set_short("Sickly human");
   set_long("The repulsive trapper looks very sick.\n"
         + "His shabby clothes are almost falling apart at the seams \n"
         + "as you look at him. There is a foul stench about him.\n");

   
   /* set physical properties */
   add_prop(CONT_I_WEIGHT,63000);
   add_prop(CONT_I_HEIGHT,1700);
   
   set_gender(0);
   
   /* stats -    STR  DEX  CON  INT  WIS  DIS */
   set_stats(({   15,  15,  16,  17,  17,  15}));
   set_hp(150);
   set_alignment(-100);
   
   /* Set unarmed attacks and armour classes. */
   set_all_hitloc_unarmed(16);
   set_all_attack_unarmed(16,16);
   set_pick_up(90);

   seq_new("do_things");
   seq_addfirst("do_things", ({"@@fart","say Shove off! Or gimme your money."}));
   
   /* Set the all important skills. */
   
   set_skill(SS_UNARM_COMBAT, 15);
   set_skill(SS_PARRY, 18);
   set_skill(SS_DEFENSE,17);
   
   set_act_time(5);
   add_act("emote smells of rotted, wet fur.");
   add_act("emote gropes at your pockets. ");
   
   set_chat_time(5);
   add_chat("By all the Gods! You are uglier than my dead gran'ma!");
   add_chat("Don't push your luck!");
   add_chat("Now don't get cheeky with me!"); 
}


void
attack_aggressor(string who)
{
   object obj;
   
   if (obj = present(who, environment()))
      command("kill " + who);
}


