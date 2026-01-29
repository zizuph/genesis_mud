#include "local.h"
#include "/d/Krynn/common/defs.h"
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include RND_MEET

#define A_BITE  1

#define H_HEAD  1
#define H_BODY  2

inherit C_FILE

void create_creature()
{
    set_race_name("hare");
    add_name("rabbit");
    set_adj("brown");
    set_short("brown hare");
    set_long("Ears pricked and nose twitching, this hare knows better than "
        + "to stay in one place for long.\n");
    set_m_in("hops in");
    set_m_out("hops");
    default_config_creature(1);

    set_skill(SS_AWARENESS, 30);
    
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(CONT_I_VOLUME, 2200);
    add_prop(CONT_I_WEIGHT, 3000);

    set_attack_unarmed(A_BITE, 10, 15, W_IMPALE, 100, "teeth");

    set_hitloc_unarmed(H_HEAD, 1, 30, "head");
    set_hitloc_unarmed(H_BODY, 1, 70, "body");
}

void escape(object player)
{
    this_object()->stop_fight(player);
    player->stop_fight(this_object());
    tell_room(environment(this_object()), QCTNAME(this_object())
        + " darts into the forest and out of sight.\n");
    this_object()->move(GET_RANDOM_ROOM(FOREST), 1);
}

void notify_meet_init()
{
    ::notify_meet_init();
    if(CAN_SEE(this_object(), this_player()) && CAN_SEE_IN_ROOM(this_object()))
    {
        this_player()->catch_tell("You hear something dart away as you "
            + "approach.\n");
        tell_room(environment(this_object()), QCTNAME(this_object())
        + " darts into the forest and out of sight.\n", this_player());
        this_object()->move(GET_RANDOM_ROOM(FOREST), 1);
    }
}

void attacked_by(object ob)
{
    ::attacked_by(ob);
    set_alarm(0.5, 0.0, &escape(ob));
}

void do_die(object killer)
{
    object corpse = clone_object("/std/corpse");
    corpse->set_name(query_name());
    corpse->add_name(QUEST_ITEM_HARE_CORPSE);
    corpse->change_prop(CONT_I_WEIGHT, query_prop(CONT_I_WEIGHT));
    corpse->change_prop(CONT_I_VOLUME, query_prop(CONT_I_VOLUME));
    corpse->add_prop(CORPSE_S_RACE, query_race_name());
    corpse->add_prop(CONT_I_TRANSP, 1);
    corpse->change_prop(CONT_I_MAX_WEIGHT, query_prop(CONT_I_MAX_WEIGHT));
    corpse->change_prop(CONT_I_MAX_VOLUME, query_prop(CONT_I_MAX_VOLUME));
    corpse->set_leftover_list(query_leftover());
    corpse->add_prop(CORPSE_AS_KILLER,
        ({killer->query_real_name(), killer->query_nonmet_name()}));
        corpse->move(environment(this_object()), 1);
    corpse->move(environment(this_object()), 1);
    
    if(killer->query_prop(PLAYER_I_GOT_NIGHTBIRD_HUNT))
        killer->add_prop(PLAYER_I_KILLED_NIGHTBIRD_HARE, 1);
    
    ::do_die(killer);
}

