
/*    
    A crab to go near the rocks in the Calia sea area. 

    coder(s):    Amelia

    history:    
              22.5.95    created          Amelia
              06.2.96    changes made in description    Jaacar
              29/8/96    modifications made             Maniac
             13/11/00    last update?                   ?
               2/9/10    typo                           Lavellan 
               2/9/10    improved special calculation   Lavellan 
 */

inherit "/d/Calia/std/sea_creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <const.h>

#include "defs.h"

#define A_BITE  0
#define A_PINCERS 1

#define H_HEAD 0
#define H_BODY 1


void
create_creature()
{
    string adj; 

    adj = ({"brown", "pink", "black", "grey"})[random(4)]; 

    set_name("crab");
    set_race_name("crab");
    set_short("small " + adj + " crab");
    set_adj("small");
    add_adj(adj);
    set_gender(G_NEUTER);
    set_long("A small " + adj + " crab that lives in the "+
             "rocks nearby. It has small pincers that "+
             "look very sharp.\n");

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1); 
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(CONT_I_VOLUME, 300);
    add_prop(CONT_I_WEIGHT, 300);

    set_stats(({10,10,10,3,3,12}));

    set_skill(SS_SWIM, 50);
    set_skill(SS_UNARM_COMBAT, 3);
    set_skill(SS_DEFENCE, 3);

    set_aggressive(1);
    set_alignment(-20);

    set_hp(query_max_hp());

    add_leftover(SEA_LEFTOVERS+"crab_meat", "meat", 1, 0, 0, 0); 

    set_attack_unarmed(A_BITE, 8, 8, W_SLASH, 25, "teeth");
    set_attack_unarmed(A_PINCERS, 8, 8, W_SLASH, 75, "pincers");
    set_hitloc_unarmed(H_HEAD, ({2,2,2,2}), 30, "head");
    set_hitloc_unarmed(H_BODY, ({5,5,5,5}), 70, "body");

    add_cact("emote bites your big toe.");
    add_cact("emote climbs up your leg and bites your knee.");
    add_cact("emote scrambles up your arm and tickles you in the armpit.");
    add_cact("emote climbs up the back of your leg and pinches your " +
             "butt.");
    add_act("emote runs around in circles on the sea bottom.");
    add_act("emote crawls behind a rock.");
    add_act("emote climbs up your leg and bites your knee.");
}


int
special_attack(object enemy)
{
    object me;
    mixed *hitresult;
    string how;

    me = this_object();

    if (random(10))
	return 0;                         /* Continue with the attack. */

    hitresult = enemy->hit_me(random(25)+5, W_IMPALE, me, -1);

    if (hitresult[3] == 0)
         how = " without effect";
    if (hitresult[3] > 0)
         how = " with tearing force";
    if (hitresult[3] > 10)
         how = " with sickening force";
    if (hitresult[3] > 20)
        how = " with dismembering force";
    
    enemy->catch_msg(QCTNAME(me)+" pinches you fiercely with its claws! "+
                     " You are hit"+how+".\n");
    tell_watcher(QCTNAME(me)+" pinches "+QTNAME(enemy)+
                 " fiercely with its claws! "+QCTNAME(enemy)+
                 " is hit"+how+".\n",enemy);

    if(enemy->query_hp() <= 0)
	  enemy->do_die(me);

    return 1;
}

