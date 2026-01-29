inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
string
random_extra()
{
   int i;
   i = random(10);
   if(i < 1)
      return "cruel";
   else if (i < 2)
      return "vicious";
   else if (i < 3)
      return "sadistic";
   else if (i < 4)
      return "savage";
   else if (i < 5)
      return "brutal";
   else if (i < 6)
      return "malevolent";
   else if (i < 7)
      return "demonic";
   else if (i < 8)
      return "devilish";
   else if (i < 9)
      return "unholy";
   else
      return "hateful";
}
/* by Antharanos */
void
create_monster()
{
    string extra;
    extra = random_extra();
    set_name("drow");
    add_name("raider");
    set_race_name("drow");
    set_adj(extra);
    set_pshort(extra + " drow");
    set_long("A cold-blooded and completely ruthless drow surface raider, "+
      "here on a mission to spread violence and chaos and above all, to "+
      "enlighten the foolish surface races of the power of Lolth and her "+
      "children, the drow!\n");
    set_stats(({125,150,125,25,25,100}));
    set_alignment(-750);
    set_skill(SS_WEP_SWORD,90);
    set_skill(SS_DEFENCE,75);
    set_skill(SS_PARRY,75);
    set_skill(SS_AWARENESS,60);
    set_skill(SS_BLIND_COMBAT,90);
    set_skill(SS_2H_COMBAT,60);
    set_skill(SS_HIDE,50);
    set_skill(SS_SNEAK,50);
    set_act_time(2);
    add_act("say Quarvalsharess zhah ultrin!");
    add_act(({"kill human","kill dwarf","kill gnome","kill hobbit","kill "+
       "goblin","kill minotaur","kill half-elf","kill kender"}));
    set_cact_time(2);
    add_cact("say Undraeth ultrin!");
    add_cact(({"kill human","kill dwarf","kill gnome","kill hobbit","kill "+
       "goblin","kill minotaur","kill half-elf","kill kender"}));
    set_random_move(10);
    set_knight_prestige(750);
    add_speak("Death to the surface dwellers!\n");
    set_default_answer("What is it you ask of me?!?\n");
    add_ask(({"death"}),"It is what awaits the pitiful humans of this "+
       "city!\n");
    add_ask(({"lolth"}),"She is the goddess, ruler of all!\n");
    add_ask(({"drow"}),"We are the true chosen ones, destined to destroy "+
       "all before us.\n");
    add_prop(LIVE_I_SEE_DARK,10);
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(NPC_I_NO_RUN_AWAY,1);

    equip(({
        "/d/Kalad/common/wild/pass/wep/dw_sword",
        "/d/Kalad/common/wild/pass/arm/dw_helm",
        "/d/Kalad/common/wild/pass/arm/dw_chain",
        "/d/Kalad/common/wild/pass/arm/piwafwi",
        "/d/Kalad/common/wild/pass/arm/dw_boots",
        CPASS(arm/dw_shield)
    }));

    set_alarm(3.0, 0.0, "departure");
}

void
return_drow(object obj)
{
   if(present(obj, environment()))
      {
      command("say Elghinn plynn rivven!");
      command("bow " + (obj->query_real_name()));
      command("say Quarvalsharess zhah ultrin!");
   }
}

void
emote_hook(string emote, object actor, string adverb)
{
    if(emote == "dgreet" || emote == "drespect")
        set_alarm(2.0,0.0,"return_drow",actor);
}

departure()
{
   command("grin mercilessly");
   command("enter theportaltothesurfaceworld");
}

void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      {
      command("say Wael! Elghinn plynn dos!");
      command("kill " + lower_case(ob->query_real_name()));
   }
}

int
special_attack(object enemy)
{
   object me;
   mixed *hitresult;
   string how;
   me = TO;
   if(random(15))
      return 0;
   hitresult = enemy->hit_me(250 + random(250), W_BLUDGEON, me, -1);
   how = " with little success";
   if(hitresult[0] > 0)
      how == "";
   if(hitresult[0] > 5)
      how = " bruisingly";
   if(hitresult[0] > 10)
      how = " painfully";
   if(hitresult[0] > 15)
      how = " very painfully";
   if(hitresult[0] > 20)
      how = " painfully hard";
   if(hitresult[0] > 25)
      how = " incredibly hard";
   if(hitresult[0] > 30)
      how = " with devastating effectiveness";
   if(hitresult[0] > 35)
      how = " with a fatal blow";
   me -> catch_msg("You attempt to hit your opponent in a vital spot!\n"+
      capitalize(enemy->query_pronoun()) + " is hit"+
      how + ".\n");
   enemy -> catch_msg(QCTNAME(me) + " attempts to hit you in a vital spot!\n"+
      "You are hit" + how + ".\n");
   tell_watcher(QCTNAME(me) + " attempts to hit " + QTNAME(enemy) + " in a vital spot!\n"+
      capitalize(enemy->query_pronoun()) + " is hit" +
      how + ".\n", enemy);
   if(enemy->query_hp() <= 0)
      enemy->do_die(me);
   return 1;
}
