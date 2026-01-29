inherit "/std/monster";
#include "/sys/ss_types.h"
#include "/sys/wa_types.h"
#include "/d/Shire/common/defs.h"
#include "/d/Shire/common/make_money.h"
#include "/d/Shire/prestige.h"
#include "/d/Shire/common/lib/goodkill.h"

void arm_me();
void re_intro();
void introduce_me();

int not_intro, intro_id, re_intro_id;

void
create_monster()
{
   set_name("rosa");
   set_title("Baggins, Keeper of the Michel Delving Mathom House");
   set_living_name("_rosa_");
   add_name(({"doorman","doorwoman","guide"}));
   set_race_name("hobbit");
   set_adj(({"bored","spinster"}));
   set_gender(1);

   set_long("This old woman hobbit is in charge of the "+
   "Michel Delving mathom house. She looks very prim and proper, "+
   "and probably knows where every single mathom in the museum is.\n");

   set_stats(({30,55,32,17,40,29}));

   MAKE_MONEY;
   set_skill(SS_DEFENSE, 29);
   set_skill(SS_UNARM_COMBAT, 30 + random(12));
   set_skill(SS_AWARENESS, 30 + random(19));

   set_chat_time(6);
   add_chat("Welcome to the mathom house!");
   add_chat("Have you seen Bilbo's wonderful mail-shirt?");
   add_chat("How are you today?");
   add_chat("Bandobras Took's riding gear is most impressive!");
   add_chat("Some things in the mathom house you can take with you.");
   add_chat("Some things in the mathom house must remain here.");
   add_chat("Have you seen Old Toby's pipe?");
   add_chat("Just because you've seen it already doesn't mean you can't see it again!");
   add_chat("I love my job.");

     trig_new("%w 'introduces' %s", "react_introduce");
   set_act_time(10);
   add_act("whistle inno");
   add_act("smile tir");
  add_act("eyebrow hope");

   add_ask(({"mail-shirt","mail","shirt","bilbo"}),VBFC_ME("ask_bilbo"));
   add_ask(({"took","bandobras","gear","riding gear",}),VBFC_ME("ask_bandobas"));
   add_ask(({"old toby","old toby's pipe","toby's pipe"}),VBFC_ME("ask_toby"));


}

void
arm_me()
{
   object tunic;

   tunic = clone_object(BREE_DIR + "arm/ltunic");
   tunic->move(TO);
   command("wear all");

}

string
ask_bilbo()
{
   command("say Oh yes, that mad Bilbo's mail-shirt is in there.");
   command("say It gleams like silver, you know.");
   command("say He brought it back from his travels with those dwarves.");
   return "";

}

string
ask_bandobas()
{
   command("say The only hobbit to ever ride a horse!");
   command("say That's Bandobras Took, for sure. He was four feet ");
   command("say five inches tall and saved the Shire from orcs!");
   command("say We have his riding gear in our museum.");
   return "";

}

string
ask_toby()
{
   command("say Good old Toby!");
   command("say He developed the art of smoking pipe-weed into ");
   command("say the way we have it today.");
   command("say We have his favorite pipe stored in memory of him.");
   return "";

}


void
react_introduce(string person,string who)
{
   if (not_intro)  
      return;
   if (intro_id)
      {   
      if (ftoi(get_alarm(intro_id)[2]) != 0)
         {
         intro_id = set_alarm(4.0,0.0,&introduce_me());
      }
   }
}

void
introduce_me()
{
   command("introduce me");
   not_intro = 1;
   if (re_intro_id)
      {
      if (ftoi(get_alarm(re_intro_id)[2]) != 0)
         {
         re_intro_id = set_alarm(15.0,0.0,&re_intro());
       }  
   }
}

void
re_intro()
{
    not_intro = 0;
}
