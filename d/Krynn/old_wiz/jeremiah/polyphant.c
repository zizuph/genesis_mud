/* 

   Poly - The retired war elephant.(He knew Hanibal!)

   Coded ........: 94/12/21
   By ...........: Jeremiah

   Latest update : 95/03/25
   By ...........: Jeremiah

*/
   
#include "/d/Krynn/common/defs.h"
inherit M_FILE

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>


inherit "/std/act/domove"; /* Include this if you want the creature to move */
inherit "/std/act/action"; /* Include this if you want your creature to act */

/*
 * Prototypes
 */
void return_intro(string who);

   
int    heal, glasses;
string ret_str;

void
create_krynn_monster()
{
   int i;
   
   glasses = 0; /* no glasses */
   ret_str = "";

   set_name("poly");
   set_race_name("elephant");
   set_title("Veteran of the 3rd Punic wars");
   set_appearance(200);
   set_adj("huge");
   add_adj("grey");
   set_gender(G_MALE);

   set_long("@@long_descr");
   
   for (i = 0; i < 6; i++)
   set_base_stat(i, 200 + random(20));
   
   set_hp(query_max_hp());
   
   set_skill(SS_DEFENCE, 100);
   set_skill(SS_UNARM_COMBAT,90);

   set_knight_prestige(-5);
   
   set_alignment(400);
      
   set_attack_unarmed(0, 95, 90, W_IMPALE, 40, "tusks");
   set_attack_unarmed(1, 75, 70, W_BLUDGEON, 30, "left front leg");
   set_attack_unarmed(2, 75, 70, W_BLUDGEON, 30, "right front leg");
    
   set_hitloc_unarmed(0, 100, 20, "head");
   set_hitloc_unarmed(1, 90, 40, "body");
   set_hitloc_unarmed(2, 90, 20, "left front leg");
   set_hitloc_unarmed(3, 90, 20, "right front leg");
   
   add_prop(LIVE_I_SEE_DARK, 100);
   add_prop(NPC_I_NO_RUN_AWAY, 1);
   add_prop(CONT_I_VOLUME, 5679000);
   add_prop(CONT_I_WEIGHT, 5784000);

   set_default_answer("Poly says: hmmm....   Dunno about that!\n");
   add_ask(({"jeremiah", "Jeremiah"}), VBFC_ME("jer_hint"));

   trig_new("%w 'introduces' %s", "react_to_intro");
   trig_new("%w 'hugs' 'you'%s", "react_to_hug");

   set_alarm(30.0,180.0,"do_sneeze");
   set_alarm(45.0,180.0,"check_change");
   set_alarm(30.0,120.0,"do_peek");
}

string
long_descr()
{
   ret_str = "This is a huge male elephant. His skin is greyish and looks " +
             "very thick. You discover that his body is covered with many " +
             "scars. Two big white tusks points at you. A heavy looking " +
             "trunk sticks out from the middle of his face. You are quite " +
             "sure, that he would be a tough opponent.\n" +
             "Hmmm he does look friendly though.\n";


   if(!glasses)
   {
      return ret_str;
   }
   else
   {
      ret_str = ret_str + "He is wearing a pair of small round spectacles " +
                "and he is reading a newspaper. 'Le Genesis Soir'\n";

      return ret_str;
   }
}



jer_hint()
{
   if (P("jeremiah",E(TO)))
   {
      command("say Jeremiah ??, he's right there");
      command("point at jeremiah");
      command("say Ask him yourself!");
   }
   else
   {
      command("say He's not here right now!");
      command("scratch head");
      command("say and I don't really know where he is!");
   }
   return "";
}
 

void
react_to_intro(string who, string garbage)
{
   set_alarm(1.0, 0.0, &return_intro(who));
}


void
return_intro(string who)
{
   who = L(who);
   if (P(who,E(TO)))
   {
      command("introduce myself");
   }
}


void
react_to_hug(string who, string garbage)
{
   who = L(who);
   if (P(who,E(TO)))
   {
      command("hug " + who);
   } 
}


void
do_sneeze()
{
   switch(random(3))
   {
   case 0 : command("sneeze");
            break;
   case 1 : command("cough");
            break;
   case 2 : command("grumble");
            break;
   default : command("");
             break;
   }
}


void 
check_change()
{
   int ran;

   ran = random(2);

   if (ran == 0)
   { 
      if(!glasses)
      {
         glasses = 1;
         command("emote wears a pair of small round spectacles.");
         command("emote unfolds a newspaper and starts to read.");
      }
   }
   if (ran == 1)
   {
      if(glasses)
      {
         glasses = 0;
         command("emote removes the small round spectacles.");
         command("emote folds the newspaper and puts it away.");
      } 
   }
}            

void 
do_peek()
{
   if (glasses)
   {
      command("emote looks at you over the edge of his newspaper.");
   }
   else
   {
      command("twiddle");
   }
}

   
