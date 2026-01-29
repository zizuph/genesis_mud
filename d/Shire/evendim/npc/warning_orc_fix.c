/*
 *  A guarding orc. He runs to get a task force if anybody comes near.
 *  Cloned by ~Shire/common/evendim/ev7
 *
 *  Added flee mechanics against certain sized players.
 *  - Arman, April 2020
 */

inherit "/std/monster";

#include "/d/Shire/common/defs.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/sys/state_desc.h"
#include "/d/Shire/common/make_money.h"

#define DIRS ({"southeast", "east", "east", "enter" })
#define NOT_NEWBIE(player) (player->query_average_stat() > SD_AV_VETERAN)
#define DEBUG(x)	find_player("arman")->catch_tell(x)
 
static int rooms_run;

// The orc returns to its original location after 5 minutes post-fleeing.
float return_home_time = 300.0;

object home_room;

void
return_home(object home_room)
{
    if(!home_room)
        return;

    if(home_room == environment(this_object()))
        return;

    // if in combat re-start the timer
    if(this_object()->query_attack())
    {        
        set_alarm(return_home_time, 0.0, &return_home(home_room));
        return;
    }

    tell_room(environment(this_object()), QCTNAME(this_object())+ 
        " wanders off.\n", ({ }), this_object());
    this_object()->move(home_room, 1);
    tell_room(environment(this_object()), QCTNAME(this_object())+ 
        " skulks in.\n", ({ }), this_object());

    return;
}

string
no_attack()
{

    if(this_player()->query_average_stat() > SD_AV_VETERAN)
    {
        this_player()->catch_msg("You approach " +QTNAME(this_object())+ 
            " threateningly. " +QCTNAME(this_object())+ 
            " looks incredibly alarmed!\n");
        tell_room(environment(this_player()), QCTNAME(this_player())+ 
            " approaches " +QTNAME(this_object())+ " threateningly. " +
            QCTNAME(this_object())+ " looks incredibly alarmed!\n", 
            ({ this_player() }), this_player());

        if(!home_room)
        {
            home_room = environment(this_object());
        }

        set_alarm(return_home_time, 0.0, &return_home(home_room));
        this_object()->run_away();
        return "";
    }

     return 0;
}

void 
create_monster()
{
    set_name("orc");
    add_name("_warning_orc");
    set_living_name("worc");
    set_adj(({"watching","small"}));
    set_alignment(-150 - random(50));
    set_race_name("orc");
    set_long("This orc seems to be put in an advanced position so he can\n"
          + "warn his friends if anyone approaches.\n");

    add_prop(CONT_I_WEIGHT,87000);   /* 87  Kg */
    add_prop(CONT_I_HEIGHT,153);     /* 153 cm */
    add_prop(OBJ_M_NO_ATTACK, "@@no_attack");
    set_stats(({ 30, 20, 20, 23, 25, 27}));

    set_skill(SS_UNARM_COMBAT,30);
    set_skill(SS_WEP_SWORD,30);
    set_skill(SS_DEFENCE,40);
    set_skill(SS_PARRY,30);
    set_pick_up(75);
    set_aggressive(0);
    set_attack_chance(0);

    /* Actions */
    /* Combat actions */
    set_cact_time(15);
    add_cact("shout Help! Intruders!");
    add_prop(LIVE_I_NEVERKNOWN, 1); /* You never get to meet him */

    rooms_run = 0;
    set_alarm(1.0,0.0,"arm");

    MAKE_MONEY;
}

init_living()
{
    ::init_living();

    if (interactive(this_player()))
    {
        run();
    }
}

void
arm()
{
    clone_object(EVENDIM_DIR + "wep/orc_scimitar")->move(TO);
    command("wield scimitar");
}

 /* This is the run function */
int
run()
{
    object ob;
    ob = present(this_player(), environment());

    if (!ob) 
        return 0;

    if (!CAN_SEE(this_object(), this_player()))
    {
        write("The orc doesn't see you. Maybe you can sneak by without him\n"
            + "noticing.\n");
        return 0;
    }

    command("shout Invaders!! Invaders!!");
 }

/* For the solamnic Knights */
query_knight_prestige() 
{ 
    return(25); 
}

/* These orcs can't be killed by large characters. */
public void
do_die(object killer)
{
    if(killer->query_average_stat() > SD_AV_VETERAN)
    {
        command("emote flees before the killing blow falls!");
        this_object()->remove_object();
        return;
    }

    ::do_die(killer);
}

