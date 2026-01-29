inherit "/d/Cirath/std/gith";
#include "/d/Cirath/common/defs.h"
#include <std.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>
#include "../defs.h"

#define RNDADJ ({"slender", "lithe", "muscular", "strong"})
#define RNDADJ2 ({"wary","serious","focused","aggressive"})
#define RNDWEP ({"g_spear3","g_club3","g_axe3","g_sword3"})[random(4)]

create_monster()
{
   set_race_name("gith");
    add_name("gith");
   set_adj(RNDADJ2[random(4)]);
   add_adj(RNDADJ[random(4)]);
   set_long("Standing taller than most of the other gith, this "
   	+"creature looks extremely powerful.  Rippling muscles "
   	+"stretch down his body, evoking an image of power and "
   	+"willingness to use that power.  His eyes watch every "
   	+"movement you make, not missing a detail.\n");
   set_alignment(-400);
   set_stats(({200,215,205,120,120,120}));
   set_skill(SS_WEP_SWORD,90);
   set_skill(SS_WEP_CLUB,90);
   set_skill(SS_WEP_POLEARM,90);
   set_skill(SS_WEP_AXE,90);
   set_skill(SS_PARRY,70);
   set_skill(SS_AWARENESS,70);
   set_skill(SS_DEFENCE,80);
   set_act_time(9);
   add_act("say This area is off limits.");
   add_act("scratch ear");
   add_act("say We are slowly bleeding the merchants of Tyr dry.");
   add_act("smile grimly");
   set_cact_time(9);
   add_cact("say A dirty spy from Tyr.  Die!");
   add_cact("emote dodges quickly around your attack.");
   add_cact("emote lashes out at you fircely.");
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(LIVE_I_SEE_DARK,5);
}

void
arm_me()
{
   clone_object(GITH_WEP + RNDWEP)->move(TO);
   command("wield all");
   clone_object(GITH_ARM+ "g_body3")->move(TO);
   clone_object(GITH_ARM + "g_helm3")->move(TO);
   clone_object(GITH_ARM + "g_shield")->move(TO);
   command("wear all");
}

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

int
special_attack(object enemy)
{
    object me;
    mixed* hitresult;
    string how;
    me=this_object();

    if(random(10)) return 0;

    hitresult = enemy->hit_me(350 + random(50), W_IMPALE, me, -1);
    how = "untouched";
    if (hitresult[0] > 0) how = "barely touched";
    if (hitresult[0] > 15) how = "a little bruised";
    if (hitresult[0] > 30) how = "hurt";
    if (hitresult[0] > 50) how = "incredibly hurt";
    if (hitresult[0] > 75) how = "massively injured";

    enemy->catch_msg(QCTNAME(me) + " leaps upon you, striking you "+
          "with "+  HIS_HER(me) +" "+ query_weapon(-1)[0]->short()
                   +".\n");
    enemy->catch_msg("You feel " + how + ".\n");

    tell_watcher(QCTNAME(me)+" leaps upon "+QCTNAME(enemy)+
                 ", striking "+ HIM_HER(enemy)+" with " + HIS_HER(me)
               +" "+query_weapon(-1)[0]->short()+".\n",me, enemy);
                 if(enemy->query_hp() <= 0) enemy->do_die(me);

    return 1;
}

