/*
 * /d/Kalad/common/wild/pass/npc/genie_earth.c
 * Purpose    : A powerful elemental, he is used for a quest
 * Located    : /d/Kalad/common/wild/pass/desert/mount/p1
 * Created By : Antharanos ??.??.??
 * Modified By:
 */

#pragma strict_types
#include "/d/Kalad/defs.h"
inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed";
#define A_WOEARTH 0
#define A_ROCKS 1
#define H_HEAD 0
#define H_BODY 1
#define H_LARM 2
#define H_RARM 3
#define H_LEGS 4

/* by Antharanos */
// Polished by Ibun 2007-05-11

void
create_monster()
{
    int i;
    set_name("dao");
    add_name("genie");
    set_race_name("genie");
    set_adj("guardian");
    set_short("guardian genie of Earth");
    set_long("A hulking and massive figure that stands just over eleven "+
        "feet in height, possessed of a body blessed with rippling, taut "+
        "muscles. His earth grey skin tone seems to suit him well, for the "+
        "figure is as solid as the earth itself.\n");
    for(i = 0; i < 3; i++)
    set_base_stat(i, 175 + random(50));
    set_base_stat(3, 100);
    set_base_stat(4, 100);
    set_base_stat(5, 150);
    set_alignment(-1200);
    set_knight_prestige(1200);
    set_skill(SS_UNARM_COMBAT,100);
    set_skill(SS_DEFENCE,100);
    set_skill(SS_BLIND_COMBAT,100);
    set_skill(SS_AWARENESS,100);
    set_act_time(6);
    add_act("emote stares at you with stern, cruel eyes.");
    add_act("say No mortal can defeat a genie in combat.");
    add_act("say Only the bearer of the sacred feather may pass.");
    set_cact_time(6);
    add_cact("emote laughs cruelly.");
    add_cact("emote smirks in contempt.");
    add_cact("say Prepare to meet T'har, foolish mortal!");
    add_speak("Only the bearer of the sacred feather of Nathla may pass. "+
        "All other mortals shall die if they engage me in combat.\n");
    set_default_answer("The guardian genie of Earth answers your query "+
        "with silence.\n");
    set_attack_unarmed(A_WOEARTH, 50, 50, W_BLUDGEON, 50, "massive right fist");
    set_attack_unarmed(A_ROCKS, 40, 40, W_BLUDGEON, 50, "massive left fist");
    set_hitloc_unarmed(H_HEAD, ({ 75, 75, 75 }), 15, "stern-visaged face");
    set_hitloc_unarmed(H_BODY, ({ 100, 100, 100 }), 45, "muscular body");
    set_hitloc_unarmed(H_LARM, ({ 75, 75, 75 }), 10, "massive left arm");
    set_hitloc_unarmed(H_RARM, ({ 75, 75, 75 }), 10, "massive right arm");
    set_hitloc_unarmed(H_LEGS, ({ 90, 90, 90 }), 20, "enormous legs");
    add_prop(LIVE_I_SEE_DARK,100);
    add_prop(LIVE_I_SEE_INVIS,100);
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(CONT_I_WEIGHT,750000);
    add_prop(CONT_I_VOLUME,750000);
    add_prop(OBJ_I_RES_MAGIC,100);
    //trig_new("%w 'waves' 'the' 'feather' 'ever' 'so' 'slightly.\n' %s","react_banish");
}

void
banished()
{
    TO->command("scream");
    TO->command("shout Nooooooooooooooo!!!");
    say(QCTNAME(TO) + " is banished back to the elemental plane of Earth.\n");
    TO->move_living("into the gateway to the elemental plane of Earth",
        "/d/Kalad/common/wild/pass/desert/mount/banished1");
    return;
}


int
react_banish(string who, string dummy)
{
   if(who)
      {
      who = lower_case(who);
      set_alarm(4.0,0.0,"return_banish",who);
      return 1;
   }
}
void
return_banish(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
   {
      command("banished intotheelementalplaneoffireforever");
   }
}

int
special_attack(object enemy)
{
    object me;
    mixed *hitresult;
    string how;
    me = TO;
    if (random(6))
        return 0;
    hitresult = enemy->hit_me(800 + random(600), W_BLUDGEON, me, -1);
    how = " with little force";
    if(hitresult[0] > 0)
        how == "";
    if(hitresult[0] > 5)
        how = " with force";
    if(hitresult[0] > 10)
        how = " with great force";
    if(hitresult[0] > 15)
        how = " with tremendous force";
    if(hitresult[0] > 20)
        how = " with unearthly force";
    if(hitresult[0] > 25)
        how = " with such force that the sickening sound of bones " +
            "splintering and internal organs exploding echos " +
            "across the mountains";
    if(hitresult[0] > 30)
        how = " with unearthly force";
    me -> catch_msg("You hurl a great chunk of earth at your opponent!\n"+
        capitalize(enemy->query_pronoun()) + " is crushed" + how + ".\n");
    enemy -> catch_msg(QCTNAME(me) + " hurls a great chunk of earth at you!\n"+
        "You are crushed" + how + ".\n");
    tell_watcher(QCTNAME(me) + " hurls a great chunk of earth at " +
        QTNAME(enemy) + " with lethal force!\n"+
        capitalize(enemy->query_pronoun()) + " is crushed" + how + ".\n",enemy);
    if(enemy->query_hp() <= 0)
        enemy->do_die(me);
    return 1;
}

int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
    if(aid == A_WOEARTH)
    {
        tell_object(enemy, "A giant wall of earth suddenly forms before you!\n");
        tell_object(enemy, "It rushes into you and slams you with " +
            "unbelievable force!\n");
        enemy -> heal_hp(-500);
    }

    if(aid == A_ROCKS)
    {
        tell_object(enemy, "A hail of fist-sized rocks pounds " +
            "you from above!\n");
        tell_object(enemy, "You are battered brutally by the attack!\n");
        enemy -> heal_hp(-250);
    }
    return 0;
}

