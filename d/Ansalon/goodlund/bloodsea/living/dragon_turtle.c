
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"
inherit AC_FILE
inherit "/d/Calia/std/sea_creature";

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>

inherit "/std/act/domove"; /* Include this if you want the creature to move */
inherit "/std/act/action"; /* Include this if you want your creature to act */
inherit "/std/act/attack";
inherit "/lib/unique";

int just_cloned = 1;    /* Used to avoid the double call of do_dragon_fear */
/* in both init_living and enter_env whenever the  */
/* dragon is cloned. var used in init_living()     */

int alarm_id = 0;       /* The id of the alarm that resets just_cloned     */  

int heal; 
int forced_attacktype = 0;

#define CLONE_MASTER    ("/d/Genesis/sys/global/unique")
#define SHIELD           "/d/Ansalon/goodlund/bloodsea/obj/dr_turtle_shell"
#define SHELL            "/d/Ansalon/goodlund/bloodsea/obj/broken_shell"

void
create_creature()
{
    int i;

    set_name("deeptooth");
    add_name("turtle");
    add_name("dragon");
    add_name("dragon turtle");
    set_short("fearsome dragon turtle");
    set_race_name("dragon turtle");
    set_adj("green");
    add_adj("ancient");
    set_gender(G_FEMALE);
    set_long("Before you is a mythical creature feared by all mariners, a " +
        "dragon turtle! This creature appears to be a cross between a giant " +
        "turtle and a dragon, and dwell in the depths of the oceans of Krynn.\n");

    set_stats(({250, 240, 200, 140, 120, 160}));

    set_hp(query_max_hp());

    set_skill(SS_DEFENCE,      100);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_SWIM, 100);
    set_skill(SS_UNARM_COMBAT, 90);

    set_knight_prestige(4500);
    set_exp_factor(150);

    set_alignment(-800);

    set_attack_unarmed(0,55,50,W_IMPALE,50,"bite");
    set_attack_unarmed(1,60,30,W_BLUDGEON,10,"tail");
    set_attack_unarmed(2,40,40,W_SLASH,20,"right claw");
    set_attack_unarmed(3,40,40,W_SLASH,20,"left claw");

    set_hitloc_unarmed(0,70,30,"head");
    set_hitloc_unarmed(1,90,50,"shell");
    set_hitloc_unarmed(2,50,10,"tail");
    set_hitloc_unarmed(3,10,10,"soft underbelly");


    add_prop(MAGIC_AM_MAGIC, ({100, "divination"}));
    add_prop(OBJ_I_RES_ACID, 80);
    add_prop(OBJ_I_RES_ELECTRICITY, 80);

    add_prop(NPC_I_NO_LOOKS, 1); 
    add_prop(LIVE_I_NEVERKNOWN, 1); 
    add_prop(LIVE_I_SEE_DARK,   100);
    add_prop(LIVE_I_QUICKNESS,  150);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(CONT_I_VOLUME,     140000);
    add_prop(CONT_I_WEIGHT,     140000);

    set_act_time(7);
    add_act("emote slaps its tail in the water furiously.");

    add_act("emote dives under the water, then surfaces right in front of you!");
    add_act("emote stares intensely at you, its eyes full of hate.");
    add_act("@@check_enemy", 1);

    set_cact_time(5);
    add_cact("emote looks at you with cold hatred in its eyes.");
    add_cact("emote opens its terrible maw and lets out a " +
      "terrifying roar!");
    add_cact("grin");

    if (CLONE_MASTER->may_clone(SHIELD, 50))
        add_leftover(SHIELD, "shell", 1, "", 0, 1);
    else
        add_leftover(SHELL, "shell", 1, "", 0, 1);

    seteuid(getuid(TO));
}

void
leave_message()
{
    tell_room(E(TO),"The fearsome dragon turtle dives into the water " +
        "and vanishes.\n", TO);
    TO->remove_object();
}


string
check_enemy()
{
   if(TO->query_attack())
     return "emote whips the water into a frenzy with its tail!";

   set_alarm(3.0, 0.0, leave_message); 
   
   return "emote looks around, obviously bored.";

}

int
test_friend(object who)
{
    if(who->query_race_name() == "dragon turtle")
        return 1;
 
    return 0;
}

int
special_attack(object enemy)
{
    int attacktype, i, penet;
    mixed* hitresult;
    string how;
    object me, *ob;

    me = this_object();

    if (forced_attacktype == 0)   /* no forced special attack this turn */
	attacktype = random(10);
    else
	attacktype = forced_attacktype;

    if (attacktype == 1)
    {
	if (forced_attacktype == 0)
	{
	    /* Dragon inhales air, and forces next attack to be cloud breath */

	    tell_room(E(TO),"The dragon turtle raises its head out of the water " + 
	      "and opens its maw ominously...\n",TO);
	    tell_room(E(TO),"You hear a sharp intake of breath.\n",TO);
	    forced_attacktype = 1;
	    return 1;
	}

	tell_room(E(TO),"Acid bursts from the dragon turtle's " +
	  "mouth. You gasp in pain as the corrosive " +
	  "acid stream engulfs you.\n",TO);

	ob =  FILTER_LIVE(all_inventory(environment(me))) - ({ me });

	/* Remove friends from breath victims */

	for (i = 0; i < sizeof(ob); i++)
	{
	    if(test_friend(ob[i]))
		ob -= ({ ob[i] });
	}

	for (i = 0; i < sizeof(ob); i++)
	{
	    penet = 150 + random(500);
	    penet -= penet * ob[i]->query_magic_res(MAGIC_I_RES_ACID) / 100;
	    hitresult = ob[i]->hit_me(penet, MAGIC_DT, me, -1);

	    how = "not harmed";
	    if (hitresult[0] > 0)                  
		how == "barely burned";
	    if (hitresult[0] > 10)
		how = "slightly burned";
	    if (hitresult[0] > 20)
		how = "burned quite badly";
	    if (hitresult[0] > 40)
		how = "burned very badly";
	    if (hitresult[0] > 60)
		how = "badly incinerated";

	    ob[i]->catch_msg("You were " + how + " by the acid breath!\n");
	    tell_watcher(QCTNAME(ob[i]) + " is " + how + " by the acid " +
	      "breath!\n", ob[i]);


	    if (ob[i]->query_hp() <= 0)
		ob[i]->do_die(me);
	}
	forced_attacktype = 0;
	return 1;
    }

    if (attacktype == 2)
    {
	if (heal == 20)
	    return 0;

	if (forced_attacktype == 0)
	{
	    tell_room(E(TO),"The eyes of the dragon turtle narrow.\n",TO);
	    forced_attacktype = 2;
	    return 1;
	}

	heal += 1;
	me->heal_hp(250);
	tell_room(E(TO),"The eyes of the dragon turtle flares up as he throws " +
	  "herself into the battle with renewed vigour.\n",TO);
	forced_attacktype = 0;
	return 1;
    }


    return 0;
}


void
dragon_fear_player(object who)
{
    if(!(QRACE(who) == "draconian") && !(QRACE(who) == "dragon turtle") &&
      !(who->query_name() == "Verminaard"))
    {
	if(!P("Dragon_fear", who))
	    clone_object("/d/Krynn/common/objects/dragon_fear")->move(who);
    }
}


void
reset_just_cloned()
{
    just_cloned = 0;
}


void
init_living()
{
    ::init_living();

    if(just_cloned)       /* See description of variable */
    {   
	if(!alarm_id)
	    alarm_id = set_alarm(2.0, 0.0, "reset_just_cloned");
	return;
    }

    set_alarm(1.0, 0.0, "dragon_fear_player", TP);   
}


void
dragon_fear_room()
{
    int    i;
    object me, *ob;

    me = TO;
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });

    for (i = 0; i < sizeof(ob); i++)
    {
	if(!(QRACE(ob[i]) == "draconian") && !(QRACE(ob[i]) == "dragon turtle") &&
	  !(ob[i]->query_name() == "Verminaard"))
	{
	    if(!P("Dragon_fear", ob[i]))
		clone_object("/d/Krynn/common/objects/dragon_fear")->move(ob[i]);
	}
    }
}


void
enter_env(object to, object from)
{
    ::enter_env(to,from);
    set_alarm(1.0, 0.0, "dragon_fear_room");
}


void
attack_enemy(object who)
{
    if(who && !query_attack() && present(who,E(TO)))
    {
	command("growl " + who->query_real_name());
	command("kill " + who->query_real_name());
    }
}

void
kill_enemy(object enemy)
{
    set_alarm(3.0, 0.0, "attack_enemy", enemy);
}


void
attack_object(object ob)
{
    if (ob->query_real_name() == "verminaard")
    {
	tell_room(E(TO), "The fearsome dragon turtle growls, and stops the "
	  + "attack.\n", TO);

	return;
    }

    ::attack_object(ob);
}


