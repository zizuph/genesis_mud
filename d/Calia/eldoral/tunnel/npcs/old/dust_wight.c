/*
 *  Undead creature, the dust wight.
 *  Raises up from the sand as the player walks through it.
 *  These sort of hateful creatures are formed by a conjuration
 *  of elemental earth and negative energy. They seek to tear down
 *  and destroy all creations of stone and metal, and if they have
 *  to kill living creatures to do that, so much the better.
 *
 *  Attacks: It uses stoneline fists to hit with.
 *           It has a petrifying cloud, trying to affect as many
 *           targets at the same time. If a target is affected he
 *           turn to stone for a couple of rounds.
 *           When a target turns to stone, the wight turns to
 *           attack him, trying to break him into rubble.
 * 
 *  Navarre April 8th 2007
 */

#include <wa_types.h>
#include <ss_types.h>
#include <poison_types.h>
#include <stdproperties.h>
#include <const.h>
#include "/d/Genesis/gems/gem.h"
#include "defs.h"

inherit "/std/monster";
inherit "/std/combat/unarmed";

#define A_FISTS 0

#define H_HEAD 0
#define H_BODY 1
#define H_ARMS 2
#define H_LEGS 3


string* gems = ({"diamond_black", "pearl_black", "moonstone", "diamond",
                 "bloodstone", "carnelian", "topaz_yellow"});

string* adjs1 = ({"huge", "large", "small", "tall"});
string* adjs2 = ({"grainy", "granular", "dusty", "gravelly", "crumbling"});

string adj1 = ONE_OF(adjs1);
string adj2 = ONE_OF(adjs2);

int can_disappear = 3;

void arm_me();

void
create_monster()
{
    set_name("undead");
    add_name("soulless being");
    add_name("wight");
    add_name("sand wight");
    
    add_prop(LIVE_I_NO_CORPSE,1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_I_RES_EARTH, 100);
    add_prop(LIVE_I_SEE_INVIS, 50);
    
    // Doubt anyone thinks this guy looks like the image of perfection.
    add_prop(NPC_I_NO_LOOKS, 1);

    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    set_race_name("wight");
    set_adj(adj1);
    add_adj(adj2);
    set_short(adj1 + " " + adj2 + " wight");
    add_prop(LIVE_I_NO_FOOTPRINTS, 1);
    set_gender(G_NEUTER);
    set_aggressive(1);
    add_prop(LIVE_I_UNDEAD, 100);
    
    set_long("This haggard creature stands in a small cloud of dust. " +
	     "Its stonelike features seem eroded and crumbling, like " +
	     "an ancient statue battered by the elements.\n");

    set_stats(({130+random(30),130+random(30),130+random(30),
                130+random(30),130+random(30),130+random(30)}));
    set_hp(query_max_hp());

    //Paralyze, Hard to kill as it merge into the sand
    //Good damage special
    set_exp_factor(150);

    set_skill(SS_DEFENCE, 100);
    
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_UNARM_COMBAT, 60+random(40));
    set_alignment(-600 -random(300));


    set_attack_unarmed(A_FISTS, 60, 60, W_BLUDGEON, 100, "stonelike fists");

    set_hitloc_unarmed(H_HEAD, 50, 10, "head");
    set_hitloc_unarmed(H_BODY, 50, 50, "body");
    set_hitloc_unarmed(H_ARMS, 50, 20, "arms");
    set_hitloc_unarmed(H_LEGS, 50, 20, "legs");
    set_alarm(0.0, 0.0, &arm_me());
}

void
arm_me()
{
    for(int i = 0; i < 7; i++)
    {
        clone_object("/d/Genesis/gems/obj/"+ONE_OF(gems))->move(TO, 1);
    }
}


int
find_interactive(object ob)
{
    return interactive(ob);
}


int randomize_func()
{
    return random(2);
}

int
special_attack(object enemy)
{
    mixed *hitresult;
    string how;
    object *players;
    object stun_obj;
    
    object me = this_object();

    players = filter(all_inventory(environment(me)), find_interactive);
    find_player("navarrejr")->catch_tell("Size of players are: "+sizeof(players)+".\n");
    sort_array(players, randomize_func);
    find_player("navarrejr")->catch_tell("Size of sorted players are: "+sizeof(players)+".\n");
    for(int i = 0; i < sizeof(players); i++)
    {
	if(present("_petrifying_object", players[i]))
	{
	    find_player("navarrejr")->catch_tell("Petri object found in "+players[i]->query_real_name()+".\n");

	    find_player("navarrejr")->catch_tell("query attack is: "+me->query_attack()->query_real_name()+"\n");
	    if(!players[i] == me->query_attack())
	    {
		find_player("navarrejr")->catch_tell("Do we ever get here?\n");
		enemy = players[i];
		tell_room(environment(me), "Sensing "+QTNAME(enemy)+" is helpless, " +
			  QTNAME(me)+" turns to attack "+HIM(enemy)+".\n", ({me, enemy}));
		enemy->catch_msg("Sensing that you are helpless, "+QTNAME(me)+" turns to attack you.\n");
		me->attack_object(enemy);
		break;
	    }
	}
    }
    if (!random(3))
    {
	if(!random(3))
	{
	    tell_room(environment(me), "With a quick gesture "+QTNAME(me)+
		      " emits a cloud of dust-like particles, which sticks to your body " +
		      "in a fine layer.\n", me);

	    for(int i = 0; i < sizeof(players); i++)
	    {
		stun_obj = present("_petrifying_object", players[i]);
		if(stun_obj)
		{
		    stun_obj->renew_time();
		}
		else
		{
		    clone_object(TUN_OBJECTS+"petrifying_object")->move(players[i], 1);
		}
	    }
	}
	else
	{
	    hitresult = enemy->hit_me(500+random(250), W_BLUDGEON, me, -1);
	    if(enemy->query_hp() < 1)
	    {
		if(present("_petrifying_object", enemy))
		{
		    tell_room(environment(me), QCTNAME(me)+" batters "+QTNAME(enemy) +
			      " into a pile of rubble.\n", ({me, enemy}));
		    enemy->catch_msg(QCTNAME(me) + " batters you into a pile of rubble.\n");
		    enemy->add_prop(LIVE_I_NO_CORPSE, 1);
		    clone_object(TUN_OBJECTS+"rubble")->move(environment(me), 1);
		}
		enemy->do_die(me);
	    }

	    switch (hitresult[0])
            {
	        case 0:
                    enemy->catch_msg(QCTNAME(me) + " reaches out for you, but you move out of its reach.\n");

                    tell_room(environment(me), QCTNAME(me) + " reaches out for " +
			      QTNAME(enemy)+ ", but "+HE(enemy)+" moves out of its reach.\n", ({enemy, me}));

                    break;

                default:
                    enemy->catch_msg(QCTNAME(me) + " slams your body with joint fists.\n");

                    tell_room(environment(me), QCTNAME(me) + " slams its joint fists into the body of "+
			      QTNAME(enemy)+".\n", ({me, enemy}));
	    }
	}
	return 1;
    }
    return 0;
}

varargs public mixed
hit_me(int wcpen, int dt, object attacker, int attack_id, int target_hitloc = -1)
{
    mixed hit;
    int hp;
    hit = ::hit_me(wcpen, dt, attacker, attack_id, target_hitloc);

    hp = this_object()->query_hp();
    if(hp < 400)
    {
	if(!random(3) && can_disappear)
	{
	    tell_room(environment(this_object()), QCTNAME(this_object())+
		      " suddenly melds into the sand and is gone!\n", this_object());
	    can_disappear--;
	    this_object()->move(ROOMS+"wight_room", 1);
	}
    }
    return hit;
}

