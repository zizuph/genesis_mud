/* Gopheroo to bounce around the west Calian moors.

   Gopher Coded by Digit.

   Modified by Maniac into this ridiculous creature, 5/5/95, 21.6.95
  
   Updated by Maniac, 3/4/99
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

#define A_KICK 0
#define H_HEAD 0
#define H_BODY 1

void
create_monster()
{
    string *adjs = ({"mad", "crazy", "hyperactive", "lunatic" });
 
    set_name("gopheroo");
    set_race_name("gopheroo");
    set_adj(adjs[random(sizeof(adjs))]);
    set_long("This furry little creature is a strange cross between "+
       "a gopher and a kangaroo!\n");
    set_base_stat(SS_STR,3);
    set_base_stat(SS_DEX,5);
    set_base_stat(SS_CON,6);
    set_base_stat(SS_INT,10);
    set_base_stat(SS_WIS,10);
    set_base_stat(SS_DIS,10);

    set_attack_unarmed(A_KICK,3,3,W_BLUDGEON,100,"hind feet");
    set_hitloc_unarmed(H_HEAD,({7,7,7,7}),12,"head");
    set_hitloc_unarmed(H_BODY,({7,7,7,7}),88,"body");
    set_alignment(50);

    set_act_time(1);
    add_act("bounce uncontrollably"); 
    add_act("bounce madly");
    add_act("bounce fanatically");
    add_act("emote scrabbles around trying to make a burrow.");
    add_act("emote bounces around energetically.");

    set_restrain_path(ROAD+"m"); /* restrict it to the moor */
    set_random_move(2);

    set_hp(1000);
    add_prop(CONT_I_WEIGHT, 2000);
    add_prop(CONT_I_MAX_WEIGHT, 3000);
    add_prop(CONT_I_VOLUME, 2000);
    add_prop(CONT_I_MAX_VOLUME, 3000);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_m_in("bounces in");
    set_mm_in("bounces in.");
    set_m_out("bounces away");
    set_mm_out("bounces away");
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
    enemy->catch_msg(QCTNAME(me)+" bounces up and head-butts you"+
                     how+"!\n");
    tell_watcher(QCTNAME(me)+" bounces up and head-butts "+
                 QTNAME(enemy)+how+"!\n",enemy);
    if(enemy->query_hp() <=0)
       enemy->do_die(me);
    return 1;
}
