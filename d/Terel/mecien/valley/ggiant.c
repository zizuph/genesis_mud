inherit "/std/monster";
#include "/sys/ss_types.h"
#include <wa_types.h>
#include "/sys/macros.h"
#include <money.h>
#include <language.h>
#include <stdproperties.h>


create_monster() {
   
   if (!IS_CLONE)
      return;
   
   set_name("thodus");
   set_race_name("giant");
   set_adj("monstrous");
   
   set_long("A giant of legend, its strength matched only by its evil.\n");
   
   /* str,  dex,  con,  int,  wis,  dis */
   set_stats(({ random(60)+100,   85,   120,   37,   37,   100}));
   
   set_hp(20000); /* reduced to correct level according to con. */
   
   set_alignment(-500);
   set_skill(SS_WEP_SWORD, 80);
   set_skill(SS_WEP_CLUB, 80);
   set_skill(SS_WEP_MISSILE, 55);
   set_skill(SS_DEFENCE, 70);
   set_skill(SS_PARRY, 60);
   
   add_prop(CONT_I_WEIGHT, 2000000);
   add_prop(CONT_I_HEIGHT, 113000);
   add_prop(CONT_I_VOLUME, 570000);
   add_prop(CONT_I_MAX_VOLUME, 9999999);
   add_prop(CONT_I_MAX_WEIGHT, 9999999);
   /* add_prop(OBJ_I_NO_INS, 1); */
   
   set_all_hitloc_unarmed(60);
   set_attack_chance(40);
   set_random_move(1);
   seq_new("do_things");
   seq_addfirst("do_things", ({
            "@@equip_me", "@@initsay", "chuckle", "growl"}));
}


object wpn;
equip_me() {
   
   seteuid(getuid(this_object()));
   
   MONEY_MOVE(random(1)+1, "platinum", 0, this_object());
   MONEY_MOVE(random(5)+1, "gold", 0, this_object());
   MONEY_MOVE(random(20)+10, "silver", 0, this_object());
   MONEY_MOVE(random(300)+50, "copper", 0, this_object());
   
   wpn = clone_object("/d/Terel/mecien/club");
   wpn -> move(this_object());
}

initsay() {
   
   string *messages;
   int num, lines, i;
   
   messages = ({
         ({
               "say I am certain you will make an excellent foe.",
               "chuckle",
               "say I will dispatch you very soon.",
               "grin",
               "wield "+ wpn->query_name()
          }),
         ({
               "spit",
               "say You are no warrior!",
               "cackle",
               "wield "+ wpn->query_name(),
               "say You are quite pathetic."
          }),
         ({
               "yawn",
               "say I'll just get my "+ wpn->query_name() +" ready.",
               "wield "+ wpn->query_name(),
               "spit",
               "say Ok. I'm ready."
               
          }) ,
         ({
               "yawn",
               "say Have you come to revere me?",
               "sigh",
               "say You are unworthy.",
               "wield "+ wpn->query_name()
          }),
         ({
               "say You are a suitable sacrifice for It",
               "wield "+ wpn->query_name(),
               "smile"
          }),
         ({
               "say I will lay out your entrails as an offering.",
               "wield "+ wpn->query_name(),
               "grin"
          }),
         ({
               "wield "+ wpn->query_name(),
               "smile"
          }),
         ({
               "wield "+ wpn->query_name(),
               "smile"
          }),
         ({
               "wield "+ wpn->query_name(),
               "smile"
          }),
         ({
               "wield "+ wpn->query_name(),
               "smile"
          }),
         ({
               "say Run while you still have a chance.",
               "smile",
               "wield "+ wpn->query_name()
          })
          });
   
   num = random(sizeof(messages));
   lines = sizeof(messages[num]);
   
   for (i=0 ; i < lines ; i++) {
      command(messages[num][i]);
   }
   set_attack_chance(75);
   set_aggressive(1);
}



find_someone(name)
{
   object ob;
   
   ob = find_player(name);
   
   if (!ob)
      return 0;
   
   move_living("X",environment(ob));
   return 0;
}
