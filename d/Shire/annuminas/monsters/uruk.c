inherit "/std/monster";
inherit "/d/Shire/esgaroth/npcs/assist_friend";

#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Shire/common/defs.h"
#include "/d/Shire/common/make_money.h"


#define ORC_ID "_annuminas_id"

//  Prototypes
void arm_me();

int has_introduced=0;


int alarm_id;

create_monster()
{
//   seteuid(getuid(TO));
   if (!IS_CLONE)
      return;
   set_adj("massive");
   set_name("Morg");
   set_title("the Blood-Stained, Ruler of Annuminas");
   set_race_name("uruk");
   set_long("This is a powerful goblin lord. He is seated upon a "
 	   +"makeshift throne of humanoid skulls and rocks. He looks "
	   +"very threatening, and is slightly scary. His flesh is "
	   +"a putrid green color, and dried blood and mud cover his "
	   +"armor and exposed flesh. He looks as if he has endured "
	   +"many battles, and looks none the worse for wear.\n");
            /* STR DEX CON INT WIZ DIS */
   set_stats(({ 130, 90, 130, 40, 50, 100}));
   set_skill(SS_WEP_CLUB,90);
   set_skill(SS_DEFENCE,75);
   set_skill(SS_PARRY,75);
   set_pick_up(75);

   set_aggressive(0);
   set_attack_chance(0);
   set_act_time(5);
   add_act("grin");
   add_act("emote smashes everything with his huge club.");
   add_act("emote picks his teeth with a human rib.");
   add_act("poke all");
   add_act("emote licks the blood from his club.");
   set_chat_time(5);
   add_chat("I'll eat you and your family!");
   add_chat("Do you have any food ugly?");
   add_chat("Brijak morasrk krijn!!!");
   add_chat("Don't make me kill you!");
   add_chat("Uruks are the strongest.");
   add_chat("Me are strong! Me kill you dead!");
   set_cchat_time(5);
   add_cchat("I'll eat from your corpse!!");
   add_cchat("You attacking me? Now die stupid!");
   add_cchat("I will destroy you city dweller!");
   add_cchat("Me squash you like bug!");
   add_prop(CONT_I_WEIGHT, 150000);   /* 150 Kg  */
   add_prop(CONT_I_VOLUME, 150000);   /* 150 Ltr */
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(CORPSE_S_RACE,"goblin");

   alarm_id = set_alarm(1.0,0.0,&arm_me());
   MAKE_MONEY;
   trig_new("%w 'introduces' %s","react_introduce");
}

void
arm_me()
{
   object wep, arm;
   remove_alarm(alarm_id);
   seteuid(getuid(this_object()));
   arm = clone_object("/d/Shire/annuminas/arm/gauntlets");
   arm -> move(this_object());
   arm = clone_object("/d/Shire/annuminas/arm/greaves");
   arm -> move(this_object());
   arm = clone_object("/d/Shire/annuminas/arm/pmail");
   arm -> move(this_object());
   command("wear all");
   wep = clone_object("/d/Shire/annuminas/wep/club");
   wep -> move(this_object());
   command("wield all");
}

void
react_introduce(string person,string who)
{
   if (!has_introduced)
      {
      call_out("introduce_me",6);
      has_introduced=1;
      call_out("remove_int",30);
   }
}

void
introduce_me()
{
   command("introduce myself");
}

void
remove_int()
{
   has_introduced=0;
}
