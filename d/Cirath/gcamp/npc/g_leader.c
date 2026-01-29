inherit "/d/Cirath/std/gith";
#include "/d/Cirath/common/defs.h"
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>
#include <wa_types.h>
#include "/d/Cirath/common/introfnc.h"

#define RNDADJ ({"massive", "muscular", "huge", "lanky", "evil-looking"})
#define RNDADJ2 ({"scaly","grinning","hunchbacked","smelly","powerful"})
#define RNDWEP ({"fury","g_sword4","g_sword4","g_sword4"})[random(4)]

mixed attackers;

create_monster()
{
   set_name("windreaver");
    set_living_name("windreaver");
   add_name("gith");
   set_title("the Lord of the Gith, Ruler of the Ringing Mountains "
   	+"and Epoch of the Black Winds");
   set_race_name("gith");
   set_adj("lean");
   add_adj("bright-eyed");
   set_long("Something about this gith makes you think he is not "
   	+"the typical marauder.  While he stands the same height as "
   	+"the other ones, he is more muscular and walks with a grace "
   	+"you have not seen among the others here.  The bright gleam "
   	+"of both evil and intelligence sparkles in his eyes.  This "
   	+"is truly a foe you would rather not make.\n");
   set_alignment(-600);
   set_stats(({250,275,255,140,140,160}));
   set_skill(SS_WEP_SWORD,100);
   set_skill(SS_PARRY,80);
   set_skill(SS_AWARENESS,70);
   set_skill(SS_DEFENCE,90);
   set_act_time(9);
   add_act("say You really should not be here.");
   add_act("say Its almost time for another raid on Tyr.");
   add_act("hmm");
   add_act("smile sadistically");
   add_act("chuckle amusedly");
   set_cact_time(9);
   add_cact("say Don't say I didn't warn you!");
   add_cact("growl angrily");
   add_cact("roar loudly");
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(LIVE_I_SEE_DARK,5);
}

void
arm_me()
{
//   clone_object(GITH_WEP + RNDWEP)->move(TO);
    clone_object(GITH_WEP + "fury")->move(TO);
   command("wield all");
   clone_object(GITH_ARM+ "g_body4")->move(TO);
   clone_object(GITH_ARM + "g_helm4")->move(TO);
   clone_object(GITH_ARM + "g_shield2")->move(TO);
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
     environment(TO)-> foo();
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
        command("say That was very unwise!");
        command("kill " + lower_case(ob->query_real_name()));
    }
}


int
special_attack(object enemy)
{
    int attacktype, bonk, i;
    mixed* hitresult;
    string how;
    object me, *ob;
    attacktype = random(3);
    if (attacktype == 1)
    {
   hitresult = enemy->hit_me(450 + random(250), W_SLASH,TO,-1);
    how = "almost slicing";
    if (hitresult[0] > 0) how = "barely cutting";
    if (hitresult[0] > 15) how = "slicing cleanly";
    if (hitresult[0] > 30) how = "deeply slashing";
    if (hitresult[0] > 50) how = "cutting deeply";
    if (hitresult[0] > 75) how = "fiercely slicing deep";

   enemy->catch_msg(QCTNAME(TO) + " ducks under your blow and "+
		"counters it with a slash of "+  HIS_HER(TO)+" "
                   + query_weapon(-1)[0]->short()+", " +how+ 
                   " into you.\n");

    tell_watcher(QCTNAME(TO)+" slashes out at "+QCTNAME(enemy)+
     " with " + HIS_HER(TO) +" "
   		+ query_weapon(-1)[0]->short()+", "+how
	    +" into "+ HIM_HER(enemy) +".\n",TO, enemy);
                 
		if(enemy->query_hp() <= 0) enemy->do_die(TO);
        return 1;
	}

    if (attacktype == 2)
    {
    hitresult = enemy->hit_me(350 + random(150), W_BLUDGEON,TO,-1);
    how = "amazed at such a weak assault";
    bonk = 0;
    if (hitresult[0] > 0)  { how = "slightly stunned"; bonk = 10; }
    if (hitresult[0] > 15) { how = "mildly disoriented"; bonk = 20;  }
    if (hitresult[0] > 30) { how = "mentally stunned"; bonk = 30; }
    if (hitresult[0] > 50) { how = "incredibly disoriented"; bonk = 40; }
    if (hitresult[0] > 75) { how = "massively stunned"; bonk = 50; }

   enemy->catch_msg("As "+QTNAME(TO) + " weaves snakelike in front "
    		+"of you, you feel your senses grow numb and your "
    		+"muscles go slack.  You feel "+how+".\n");

   tell_watcher(QCTNAME(TO)+" intently stares at "+QCTNAME(enemy)+
                 " while weaving serpentlike before him.  "+
                 QCTNAME(enemy)+" seems to go limp.\n",
		TO,enemy);
    if (bonk>0) { enemy->add_attack_delay(bonk, 1); }

	if(enemy->query_hp() <= 0) enemy->do_die(TO);

        return 1;
    }

    return 0;
}


