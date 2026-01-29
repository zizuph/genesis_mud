 // Cook          (/d/Avenir/common/bazaar/NPC/cook.c)
 // creator(s):    Glinda, may 95
 // last update:
 // purpose:       Works in the kitchen of the inn.
 //
 // note:
 // bug(s):
 // to-do:


inherit "/d/Avenir/inherit/monster.c";

#include "/d/Avenir/common/bazaar/bazaar.h"
#include <language.h>


create_monster()
{
   set_name("cook");
   set_race_name("human");
   set_adj("fanatic");
   set_short("fanatic cook");
   set_long("The cook barely glances at you before returning to work " +
            "with preparing food for the guests. You have seldom seen " +
            "anyone perform his job with such passion. His skill at " +
            "cutting vegetables is amazing, his knife moving so quickly " +
            "you cannot make out the blade. In his other "
              +"hand he holds a large silver platter.\n");

   default_config_npc(87);
   set_skill(SS_WEP_KNIFE,80);
   set_skill(SS_DEFENCE,80);
   set_skill(SS_UNARM_COMBAT,60);
   set_skill(SS_AWARENESS,50);
   add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop("_live_m_attack_thief", "thief_fun");
   set_act_time(1);
   add_act("emote fanatically chops up a carrot.");
   add_act("wipe forehead");
   add_act("emote slices some potatoes with amazing speed.");
   add_act("emote skillfully skins a fish.");
   add_act("emote crushes a cockroach with his foot.");
   add_act("wipe hands");
   add_act("emote scratches his behind.");
   add_act("emote swiftly swats a fly with his hands.");
   add_act("swear");

   set_cact_time(1);
   add_cact("say Get out!!");
   add_cact("say I'm gonna skin you like a bloody eel and feed you " +
            "to the customers!");
   add_cact("say I'm gonna chop you up like a bloody potato!");
   add_cact("say I'm gonna crush you like a cockroach!");

}

arm_me()
{
   object wep;
   object arm;

   clone_object(OBJ+"misc/platter")->move(TO);
   wep=clone_object(WIELD + "c_knife");
   wep->move(TO);
   arm=clone_object(WORN + "apron");
   arm->move(TO);
   command("wield all");
   command("wear all");
}


thief_fun(object thief, object victim, object ob)
{
    set_alarm(3.0, 0.0, &command("kill "+
          thief->query_real_name()));
    set_alarm(1.0, 0.0, &command("shout You die "
          +"for that worm!"));
}
