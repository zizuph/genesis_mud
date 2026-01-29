/*
   Pax Tharkas.

   pyros.c
   -------

   Coded ........: Jeremiah
   By ...........: 95/04/02
   
   Latest update : Jeremiah
   By ...........: 95/04/30


   Pyros is Ember(the dragon, ember.c) in human form. He will change to 
   his dragon form if attacked or ordered so by Verminaard.

*/

#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include "/d/Krynn/common/defs.h";
#include "/d/Krynn/pax/local.h";
inherit M_FILE

inherit "/std/act/domove";  /* Allows Pyros to move */
inherit "/std/act/action";  /* Allows Pyros to act  */


void
create_krynn_monster()
{
   string str;

   set_name("pyros");
   set_race_name("human");
   set_long("He is a slender human, slight of build with dark black hair, " +
            "a thin face, and slanting red eyes. His facial features are "  +
            "vaguely elven. He is dressed in crimson robes.\n"); 

   add_name(({"human", "pyros", "ember"}));
   set_adj("dark-haired");
   add_adj("red-eyed"); 
   set_gender(G_MALE);
   add_prop(OBJ_I_COLORABLE, 1);


   set_stats(({120,180,120,180,180,200}));
   set_skill(SS_DEFENCE,      100);
   set_skill(SS_PARRY,        100);
   add_prop(LIVE_I_QUICKNESS, 150);
   add_prop(LIVE_I_SEE_DARK,  100);
   add_prop(NPC_I_NO_RUN_AWAY,  1);

   set_alignment(-1000);
   set_knight_prestige(1000);

   set_all_hitloc_unarmed(45);

/*   
   set_act_time(3);
   add_act("emote looks intensely at you. You feel his gaze penetrating " +
           "deep into your mind, as if he could read your innermost " +
           "thoughts.");

   add_act("peer");

   add_act("say My lord, the preparations for the invasion are " +
           "almost ready.");

   add_act("say Sire, rumours have it, that the clerics of paladine has " +
           "returned to Krynn. Our dark queen will be most displeased.");

   add_act("smirk");

   add_act("say The discs of Mishakal has been recovered. This is most " +
           "disturbing. Who is taking care of things around Solace?");
*/
}	


equip_me()
{
    command("wear all");
    command("wield all");
}

 
int
special_attack(object enemy)
{
   int attacktype;

   attacktype = random(15);

   if (attacktype == 1)
   {
   }

   return 0;
}


void
transform(object enemy)
{
   tell_room(E(TO), "Suddenly the contours of " + QTNAME(TO) + 
             " starts to fade and blur. His face grows longer " +
             "and reptilelike, his skin turns brilliantly red and starts " +
             "to crackle up, like some sort of scales. His arms moves " +
             "backwards, and emerges as a huge pair of red leathery " +
             "wings. Sharp talons grows from his feet, and his entire " +
             "figure grows, rising tall into the air above you. " +
             "Suddenly you realize, that you are facing a huge red " +
             "dragon!\n", TO);

   seteuid(getuid(TO));
   clone_object(PMONSTER + "ember")->move(E(TO));
   present("ember",E(TO))->kill_enemy(enemy);
   remove_object();
}


void
attacked_by(object ob)
{
   object *arr;
   int i;

   ::attacked_by(ob);
   arr = (object *)query_team_others();
   for (i = 0; i < sizeof(arr); i++)
      arr[i]->notify_ob_attacked_me(TO,ob);

   transform(ob);
}

void
notify_ob_attacked_me(object friend, object attacker)
{
   if(query_attack())
      return;

   set_alarm(1.0, 0.0, &transform(attacker));
}


public void
attack_object(object ob)
{
   if (ob->query_real_name() == "verminaard")
   {
      tell_room(E(TO), "The dark-haired red-eyed human shakes his "
        + "head slightly, and stops the attack.\n", TO);

      return;
   }

   ::attack_object(ob);
   set_alarm(1.0, 0.0, "transform", ob);
}
