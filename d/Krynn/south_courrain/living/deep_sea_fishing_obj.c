
/* 
    Object that allows fishing for catching of big sports fish
    for fishing code ( /d/Krynn/common/fishing/ )

    Saved in /d/Krynn/south_courrain/living/ so it can be
    spawned through the /d/Krynn/south_courrain/courrain_placer.c

    Arman, March 2021
 */ 

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit M_FILE

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("herring");
    add_name("school");
    add_name("birds");
    add_name("seabirds");
    add_name("_deep_sea_fish_school");
    add_adj("agitated");

    set_short("agitated school of herring");
    set_long("A flock of circling seabirds dive into the water " +
        "here, attracted to the school of herring that have " +
        "been forced into a tight bait ball by unseen but " +
        "likely large underwater predators.\n");
    set_gender(G_NEUTER);

    set_stats(({100, 100, 100, 100, 100, 100}));
    set_hp(query_max_hp());


    set_alignment(0);
    set_knight_prestige(0);
    set_skill(SS_SWIM, 100);
    set_skill(SS_AWARENESS, 100);
    add_prop(CONT_I_HEIGHT, 600);
    add_prop(CONT_I_WEIGHT, 490000);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_I_NO_LOOKS, 1); 
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_NO_BODY, 1); 
    add_prop(LIVE_I_NO_CORPSE, 1);  

    set_act_time(6);
    add_act("emote shimmers as many flail to the " +
        "surface in a panic.\n");
    add_act("emote contracts into a dazzling defensive bait ball, before " +
        "breaking apart chaotically as seabirds dive bomb at great " +
        "speed into the ball.\n");

    add_prop(OBJ_M_NO_ATTACK,"Whatever the creature is beneath you, " +
       "it is too deep for you to attack from here.\n");

    setuid();
    seteuid(getuid());
}

void
fish_leaves(object enemy)
{
    object monster;
    int monster_type;
    string message = "The school of herring swiftly departs these " +
         "waters.\n";

    if(!CAN_SEE(TO, enemy))
        return;

    tell_room(E(TO), message);

    TO->remove_object();
}


void
init_living()
{
    if(living(TP))
        set_alarm(7.0,0.0, "fish_leaves", TP);
    ::init_living();
}


