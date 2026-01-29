/* Rabbit that wanders west moorland in Calia.
   Coded by Digit.

   Modified, Maniac, 5/5/95, 21.6.95

   Updated, Maniac, 3/4/99
*/

#pragma save_binary

inherit "/std/monster";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <filter_funs.h>
#include "monster.h"

#define A_BITE 0
#define H_HEAD 0
#define H_BODY 1


void
create_monster()
{
    string a;
    string *adjs = ({"nervous", "quick", "tiny", "cute"});

    a = adjs[random(sizeof(adjs))];
    set_name("rabbit");
    add_name("bunny");
    set_race_name("rabbit");
    set_adj(a);
    set_long("This is a " + a + " bunny. Its fur is grey in "+
       "colour, and it seems to be well fed.\n");
    set_base_stat(SS_STR,3);
    set_base_stat(SS_DEX,4);
    set_base_stat(SS_CON,7);
    set_base_stat(SS_INT,10);
    set_base_stat(SS_WIS,10);
    set_base_stat(SS_DIS,10);

    set_attack_unarmed(A_BITE,3,3,W_IMPALE,100,"teeth");
    set_hitloc_unarmed(H_HEAD,({7,7,7,7}),12,"head");
    set_hitloc_unarmed(H_BODY,({7,7,7,7}),88,"body");
    set_alignment(50);
    set_hp(1000);

    set_act_time(2);
    add_act("emote hops around slowly.");
    add_act("emote pricks up its ears.");
    add_act("emote munches some grass.");
    add_act("emote eyes you warily."); 

    set_restrain_path(ROAD+"m"); /* restrict it to the moor */
    set_random_move(7);
 
    add_prop(CONT_I_WEIGHT, 2000);
    add_prop(CONT_I_MAX_WEIGHT, 3000);
    add_prop(CONT_I_VOLUME, 2000);
    add_prop(CONT_I_MAX_VOLUME, 3000);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_m_in("hops in");
    set_mm_in("hops in.");
    set_m_out("hops away");
    set_mm_out("hops away");
}


int
special_attack(object enemy)
{
    object me;
    mixed *hitresult;
    string how;

    me = this_object();
    if (random(5))
       return 0;
    hitresult = enemy->hit_me(5+random(20),W_IMPALE,me,-1);
    how = " without effect";
    if (hitresult[0] >0)
       how = "";
    if (hitresult[0] > 10)
       how = " hard";
    if (hitresult[0] > 20)
       how = " very hard";
    enemy->catch_msg(QCTNAME(me)+" bites you"+how+"!\n");
    tell_watcher(QCTNAME(me)+" bites "+QTNAME(enemy)+how+"!\n",enemy);
    if(enemy->query_hp() <=0)
       enemy->do_die(me);
    return 1;
}