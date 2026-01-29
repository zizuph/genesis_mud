/*
 *  A random orc with random stuff adapted to be slightly weaker than
 *  the original random_orc.
 *  Cloned by ~Shire/common/guild/rooms/path1
 */

inherit "/std/monster";

#include "defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/language.h"
#include "/sys/stdproperties.h"

create_monster() {
   int ran;

   if (!IS_CLONE)
      return;

   seteuid(getuid());
   set_name(({"_team_leader_orc_","orc"}));
   set_pname("orcs");
   set_pshort("fat orcs");
   set_race_name("orc"); 
   set_adj("fat");
    set_alignment(-200 + random(50));
   set_long(break_string("This is an unusually fat orc.\n",70));
   add_prop(CONT_I_WEIGHT,150 * 1000);
   add_prop(CONT_I_HEIGHT,170 * 1000);
   add_prop(LIVE_I_NEVERKNOWN,1);

   set_stats(({ 24, 7, 30, 15, 15, 37 }));
   set_hp(3000); /* Heal fully */

   set_skill(SS_UNARM_COMBAT, 29);
   set_skill(SS_WEP_AXE, 35);
   set_skill(SS_DEFENCE, 25);
   set_skill(SS_PARRY, 21);
   set_pick_up(5);

   set_random_move(100);

   set_aggressive(1);
   set_attack_chance(5);

   set_chat_time(5 + random(6));
   add_chat("What are you doing here?");
   add_chat("Go away while you still live!");
   add_chat("I don't like the looks of you!");
    add_chat("I'll chop yer legs off!");
   add_chat("I'll chop yer arms off!");
    add_chat("Come here and I'll bite your head off!");

   set_cchat_time(3 + random(6));
   add_cchat("Ha! You chose the wrong one to attack!");
   add_cchat("In a moment me be getting very mad!");
   add_cchat("Who do you think you are?!?");

   /* Triggers */
   trig_new("%s 'smiles' %s", "react_smile");
   trig_new("%s 'sighs' %s", "react_sigh");

   call_out("arm",0);

}

arm() {
  clone_object(STAND_WEAPON + "orc_axe")->move(this_object());
  command("wield axe");
}

/********************************************************************
 *
 *  Some feelings to make the orc more vivid.
 *  The feelings are split in two parts: the part that is called by
 *  a trigger function, and a part that is called after a random time.
 *  This is done to get a feeling of reality in the game.
 */

react_sigh(who, dummy) {
   if (who) {
      who = lower_case(who);
      call_out("return_sigh", 4+random(9), who);
      return 1;
   }
}

return_sigh(who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say I am glad you are depressed, "
               + obj->query_nonmet_name() + ".");
      if (ran == 1)
         command("grin");
      if (ran == 2)
      {
         command("say It makes me happy to see you depressed, bloody "
              + obj->query_race_name() + ".");
         command("poke " + who);
      }
   }
}

react_smile(who, dummy) {
   if (who) {
      who = lower_case(who);
      call_out("return_smile", 4+random(9), who);
      return 1;
   }
}

return_smile(who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say Get that grin off your face, "
               + obj->query_nonmet_name() + "!");
      if (ran == 1)
         command("growl at " + who);
      if (ran == 2)
         command("say Damn " + LANG_PWORD(obj->query_race_name())
               + ", always smiling!");
   }
}

/* For the solamnic Knights */

query_knight_prestige() { return(50); }

/* The rest here is to get this mobile to be a nice buddy and if he is in a
 * team and he or a members gets attacked he will join the fight.
 */
/*
 * Function name: attacked_by
 * Description:   This function is called when somebody attacks this object
 * Arguments:     ob - The attacker
 */
void
attacked_by(object ob)
{
    object *arr;
    int i;

    ::attacked_by(ob);

    arr = (object *)query_team_others();
    for (i = 0; i < sizeof(arr); i++)
        arr[i]->notify_ob_attacked_me(this_object(), ob);
}

/*
 * Function name: notify_ob_attacked_me
 * Description:   This is called when someone attacks a team member of mine
 * Arguments:     friend - My team mate
 *                attacker - The attacker
 */
void
notify_ob_attacked_me(object friend, object attacker)
{
    if (query_attack())
        return;

    if (random(10))
        call_out("help_friend", 1, attacker);
}

/*
 * Function name: help_friend
 * Description:   Help my friends by attacking their attacker
 * Arguments:     attacker - The person who attacked my friend
 */
void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
        command("say You scum, stop fighting my friend!");
        command("kill " + lower_case(ob->query_real_name()));
    }
}

