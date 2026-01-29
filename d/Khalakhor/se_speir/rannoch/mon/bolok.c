/* File         : /d/Khalakhor/se_speir/rannoch/npc/bolok.c
 * Creator      : Darragh@Genesis
 * Date         : 00-10-04      
 * Purpose      : Npc in the Loch Rannoch area.
 * Related Files: 
 * Comments     : 
 * Modifications: Re-written 01-03-24
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Khalakhor/std/npc/wildlife";
inherit "/std/act/attack";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <language.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/defs.h"

#define A_BITE 0
#define A_TUSK 0

#define H_HEAD 0
#define H_BODY 1
#define H_TAIL 2
#define H_RARM 3
#define H_LARM 4
#define H_RLEG 5
#define H_LLEG 6

public void setup_acts();
public void setup_cacts();

public void
create_khalakhor_wildlife()
{
    set_name("bolok");
    set_race_name("boar");
    set_adj("huge");
    add_adj("foul-tempered");
    set_short("huge foul-tempered boar");
    set_long("This boar is the biggest, ugliest, smelliest, most foul-" +
        "tempered boar you have ever seen. From its mouth protrudes two " +
        "really long, razor-sharp tusks. With those tusks and the sheer, " +
        "raw aggressiveness reflected in its eyes, you do not doubt it " +
        "could, and happily would, tear you to pieces.\n");

    set_stats(({ 160, 180, 200, 50, 40, 200 }));

    refresh_living();
    set_stuffed(1200);

    set_skill(SS_DEFENCE, 80);
    set_skill(SS_BLIND_COMBAT, 80);
    set_skill(SS_UNARM_COMBAT, 90);
    set_skill(SS_AWARENESS, 70);

    set_attack_unarmed(A_BITE, 40, 60, W_IMPALE, 30, "jaws");
    set_attack_unarmed(A_TUSK, 70, 90, W_SLASH, 30, "tusks");

    set_hitloc_unarmed(H_HEAD, 25, 10, "head");
    set_hitloc_unarmed(H_BODY, 20, 50, "body");
    set_hitloc_unarmed(H_RARM, 15, 10, "right foreleg");
    set_hitloc_unarmed(H_LARM, 15, 10, "left foreleg");
    set_hitloc_unarmed(H_RLEG, 15, 7, "right hindleg");
    set_hitloc_unarmed(H_LLEG, 15, 7, "left hindleg");

    set_restrain_path("/d/Khalakhor/se_speir/rannoch/room");
    set_random_move(1);

    set_aggressive(1);
    set_attack_chance(100);
    add_prop(NPC_I_NO_FEAR,1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_QUICKNESS, 15);
    add_prop(LIVE_I_SEE_DARK, 15);
    add_prop(CONT_I_WEIGHT, 20000);
    add_prop(CONT_I_VOLUME, 10000);
    add_prop(CONT_I_HEIGHT, 40);

    set_m_in("charges in");
    set_m_out("trots");

    setup_acts();
    setup_cacts();

    set_alignment(0);

}

public void aggressive_attack(object victim)
{
   string lcname=lower_case(victim->query_name());
 
   (query_follow() != lcname);
   set_follow(lcname);
   ::aggressive_attack(victim);
}

public void
setup_acts()
{

    set_act_time(5);
    
    add_act("emote stares hatefully at you.");
    add_act("emote pokes around on the ground.");
}

public void
setup_cacts()
{
    set_cact_time(5);

    add_cact("emote drools excessively while staring at you with " +
             "its small, hateful eyes.");
    add_cact("emote flashes its razor sharp teeth " +
             "at you while snarling viciously.");
    add_cact("emote emits a series of loud grunts and squeals.");
    add_cact("emote tosses its head back and forth wildly.");

}

