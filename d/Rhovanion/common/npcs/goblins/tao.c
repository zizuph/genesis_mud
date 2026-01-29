#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit AM_FILE

void
create_krynn_monster()
{
   set_name("tao");
   set_living_name("tao");
   set_title("the Retired Captain of the Army of Angmar");
   set_adj("huge");
   set_adj("scarred");
   set_race_name("goblin");
   set_long("A huge old goblin. You are sure that he is " +
           "an experienced angmarian warrior. Perhaps " +
           "even one of the strongest soldiers. " +
           "His merciless grin is terrifying. " +
           "He has enough strenght to smash everyone but " +
           "he is looking quite calm at the moment" +
           ".\n");
   set_gender(G_MALE); 
   set_short("huge scarred male goblin");

   set_stats(({180+random(70),170+random(40),180+random(80),60,160+random(80),110}));
   add_prop(LIVE_I_SEE_DARK, 5);
   add_prop(LIVE_I_QUICKNESS, 100);
   add_prop(OBJ_I_RES_MAGIC, 20);
   
    
   set_skill(SS_WEP_CLUB,100);
   set_skill(SS_DEFENCE, 90+random(11));
   set_skill(SS_PARRY,80+random(21));
   set_skill(SS_AWARENESS, 70);
   set_skill(SS_BLIND_COMBAT, 70+random(31));

   set_act_time(2);
   add_act("emote grins mercilessly.");
   add_act("emote stares at you.");
   add_act("emote eats some rotten food.");
   add_act("emote chews something.");
   add_act("emote spits on you.");
   add_act("emote burps and grins.");
   add_act("emote farts happily.");
   set_alignment(-800);

   add_ask("whip","say Wheep ? Ughm... I have it!",1);
   add_ask("angmar","shout Angmar!!! Angmar Forever!!!",1); 

   trig_new("%w 'introduces' %s", "react_to_intro");

}

void
react_to_intro(string who, string garbage)
 { 
  set_alarm(2.0,0.0,"return_intro",who);
 }

int
special_attack(object enemy)
{

if (random(4)) return 0;
command("emote runs madly around and strikes everybody in the cave.");
enemy->heal_hp(random(300)*(-1)+30);

set_intoxicated(1000);

}  

int react_intro(string who)
{
    if (who)
    {
        who = lower_case(who);
        if(find_player(who))
        {
            set_alarm(1.0,0.0,"return_intro", who);
        }
        return 1;
    }
}

void return_intro(string who)
{
    command("lick " + who);
    set_alarm(1.0,0.0,"command","introduce me to all");
}

void
arm_me()
{
clone_object("/d/Rhovanion/common/weapons/wlw")->move(TO,1);
clone_object("/d/Rhovanion/common/armours/helm_sup")->move(TO,1);
clone_object("/d/Rhovanion/common/armours/shield_sup")->move(TO,1);
clone_object("/d/Rhovanion/common/armours/ob_plate")->move(TO,1);
clone_object("/d/Rhovanion/common/armours/goblin/tao_greaves")->move(TO,1);
clone_object("/d/Rhovanion/common/armours/goblin/tao_bracers")->move(TO,1);

 command("wield all");
 command("wear all");

}

