/*
 * This file is IGARD_NPC + "shopkeeper.c"
 *
 * Which is modified from:
 *
 * The file /d/Gondor/morgul/npc/ithil_orc.c
 *
 * Olorin, July 1993
 * General upgrade, Olorin, February 1996
 * Last modified by Alto, October 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/rohan/isengard/igard/npc/igard_monster.c";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../igard_defs.h"

public int      find_home();
public int      go_back_home();

object revenge, HOME;


public void
create_igard_orc()
{
}

nomask void
create_igard_monster()
{
    int     rnd = random(31);
 
    set_name("orc");
    set_pname("orcs");
    set_race_name("orc");
    set_adj("slack-jawed");
    add_adj("toothless");
    set_long("This old orc appears to have seen his fair share of "
        + "battle, but from the looks of things, his days of burning "
        + "and looting are long past. He stares at you with a somewhat "
        + "vacant glare in his blood-shot clouded eyes, wondering if "
        + "perhaps you would like to purchase some of the armours he "
        + "maintains in stock.\n");
    
    default_config_npc( 45 + rnd / 3);
    set_base_stat(SS_INT, 25 + rnd / 2);
    set_base_stat(SS_WIS, 25 + rnd / 2);
    set_base_stat(SS_DIS, 55 + rnd / 6);

    set_alignment(-250-rnd*10);

    set_skill(SS_WEP_SWORD,  45 + rnd / 3);
    set_skill(SS_WEP_CLUB,   45 + rnd / 3);
    set_skill(SS_WEP_KNIFE,  45 + rnd / 3);
    set_skill(SS_PARRY,      45 + rnd / 2);
    set_skill(SS_DEFENCE,    45 + rnd / 2);
    add_prop(CONT_I_HEIGHT,   150 + rnd / 2);
    add_prop(CONT_I_WEIGHT, 75000 + rnd * 400);
    add_prop(CONT_I_VOLUME, 70000 + rnd * 400);    
    add_prop(LIVE_I_SEE_DARK, 4);

    set_alarm(1.0, 0.0, &find_home());

    set_chat_time(15 + random(15));
    add_chat("You can look, but don't touch!");
    add_chat("You looks untrustworthy to me. We could be friends, I fink.");
    add_chat("I was great warrior, and if you believe me not, just ask "
        + "all them people I killed!");
    add_chat("We needs to suit up the lads. Boss says big fight coming "
        + "soon wiff the horse boys.");
    add_chat("I needs more room for this junk!");
    add_chat("Don't be starting no trouble, y'hear? Killin' you would "
        + "take more energy than you're worth.");
    add_chat("Want some armour?");

    set_cchat_time(5 + random(10));
    add_cchat("Die, scum!");
    add_cchat("I'll rip your throat out, maggot!");
    add_cchat("Hold still and it will hurt less!");
    add_cchat("Scum! The Boss will have your heart on a stick.");
    add_cchat("Run while you can, little mouse!");
    add_cchat("I'm going to eat your liver, you know.");

    set_act_time(15 + random(15));	
    add_act("burp");
    add_act("get all from corpse");
    add_act("hiss");
    add_act("grin");		
    add_act("fart");		

    set_cact_time(2 + random(2));
    add_cact("scream"); 
    add_cact("emote grits his teeth and charges."); 
    add_cact("growl"); 
    add_cact("frown"); 
    add_cact("yawn"); 



    create_igard_orc();
}


int
find_home()
{
    HOME = environment(TO);
    return 1;
}

int
go_back_home()
{
    object foe;

    if (Victim->query_prop("_enemy_of_igard"))
    {
    foe = Victim;
    }

    if (environment(TO) == HOME)
    {
    return 1;
    }

    if ((TO->query_attack() != 0) || ((objectp(present(foe, ENV(TO))))
        && CAN_SEE(TO, foe)))
    {
    TO->command("kill " + foe->query_real_name());
    set_alarm(60.0, 0.0, &go_back_home());
    return 1;
    }

    tell_room(environment(TO), "The " + (implode(query_adjs()," ")) + " " 
        + TO->query_race() + " adjusts his armours, peers dangerously around "
        + "and returns to his post.\n", ({TO}));

    tell_room(HOME, "The " + (implode(query_adjs()," ")) + " " 
        + TO->query_race() + " arrives at his post, dusting off his "
        + "armours after a recent melee.\n");

    TO->move_living("M", HOME, 1, 0);

    return 1;
}

void
do_die(object killer)
{
    setuid();
    seteuid(getuid());

    tell_room(ENV(TO), "With his last breath, the slack-jawed toothless "
        + "male orc cries for help.\n");

    revenge = clone_object(IGARD_OBJ + "ambush_object");
    revenge->move(ENV(TO));

    ::do_die(killer);
}

