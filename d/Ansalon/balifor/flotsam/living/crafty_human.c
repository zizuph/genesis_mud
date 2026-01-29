#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"
#include <ss_types.h>
#include <wa_types.h>

inherit AM_FILE

#define WEP "/d/Ansalon/balifor/flotsam/obj/weapon/long_dagger"
#define ARM ARMOUR + "brobe"

void
create_krynn_monster()
{
   if (!IS_CLONE)
      return;
   
   set_name("human");
   set_race_name("human");
   set_adj("crafty");
   set_short("crafty human");
   set_long("This crafty human seems to be in the " +
      "middle of some illicit dealings. He is not pleased " +
      "at your intrusion.\n");
   
   set_stats(({70,70,70,100,70,100}));
   set_alignment(-10);
   set_knight_prestige(50);
   
   set_act_time(10);
   add_act("say Intruder! Ice him!");
   add_act("emote looks around the room in disgust.");
   
   set_cact_time(5);
   add_cact("close window");
   add_cact("say Intruder! Ice 'em!");
   
   
   set_skill(SS_DEFENCE, 50);
   set_skill(SS_PARRY, 50);
   set_skill(SS_WEP_KNIFE, 60);
   add_prop(NPC_I_NO_RUN_AWAY, 1);
   set_aggressive(1);
   
}

int
special_attack(object enemy)
{
   int    attacktype,
   pen,
   wloc;
   
   mixed  hitres;
   
   string *hitloc,
   how,
   weapon;
   
   if (!sizeof(query_weapon(-1)))
      return 0;

   attacktype = random(5);
   
   hitloc = ({ "left arm", "right arm",
         "body", "left leg", "right leg" });
   
   weapon = query_weapon(-1)[0]->query_short();
   
   if (attacktype == 1)
      {
      pen = 400 + random(200);
      
      hitres = enemy->hit_me(pen, W_IMPALE, TO, -1);
      
      wloc = random(5);
      
      if (hitres[0] <= 0)
         how = "his " + weapon + " just missing";
      if (hitres[0] > 0)
         how = "his " + weapon + " barely nicking the skin of";
      if (hitres[0] > 10)
         how = "sinking the tip of his " + weapon + " into";
      if (hitres[0] > 20)
         how = "his " + weapon + " penetrating";
      if (hitres[0] > 40)
         how = "thrusting his " + weapon + " deeply into";
      if (hitres[0] > 60)
         how = "almost burying his " + weapon + " to the hilt in";
      
      enemy->catch_msg(QCTNAME(TO) + " sidesteps your defences "
         + "and stabs viciously at you, " + how + " your " 
         + hitloc[wloc] + ".\n");
      
      tell_room(E(TO), QCTNAME(TO) + " sidesteps " + QCTNAME(enemy)
         + "'s defences and stabs viciously at " + OBJECTIVE(enemy)
         + ", " + how + " " + POSSESSIVE(enemy) + " " + hitloc[wloc]
         + ".\n", ({ enemy, TO }));
      
      if (enemy->query_hp() <= 0)
         {
         enemy->do_die(TO);
       }
      
      return 1;
   }
   
   return 0;
}


void
arm_me()
{
   seteuid(getuid(this_object()));
   clone_object(WEP)->move(this_object(),1);
   command("wield all");
   clone_object(ARM)->move(TO,1);
   command("wear all");
   
}
