/*
 * This file is IGARD_NPC + "igard_young_uruk.c"
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

public string   long_desc();
public void     long_text();
public int      find_home();
public int      go_back_home();

object HOME;

string long_looks;

void
long_text()
{
    switch (random(3))
    {
    case 0:
       long_looks = CAP(LANG_ADDART(implode(query_adjs()," ")))
       + " uruk with short crooked legs and long arms that hang almost "
       + "to the ground. It has warty skin that still looks fresh in some "
       + "way, almost as if it were born only recently.\n";
	      break;
    case 1:
       long_looks = CAP(LANG_ADDART(implode(query_adjs()," ")))
       + " uruk from the warrens beneath Isengard. He is very short "
       + "and squat, mewling in a sqeaky voice. There is something not "
       + "altogether 'urukish' about him, although you cannot quite lay "
       + "your finger on it.\n";
	      break;
    case 2:
       long_looks = "This " + (implode(query_adjs()," "))
       + " uruk seems somehow more intelligent and clever than is usual for "
       + "his kind. He watches you with a perceptive eye, as if probing for "
       + "weaknesses. For some reason, this uruk seems almost, but not quite "
       + "human. The breeding programme below Isengard is indeed sinister.\n";
	      break;
    default:
        break;
    }
}


public void
create_igard_orc()
{
}

nomask void
create_igard_monster()
{
    int     rnd = random(31);
 
    set_name("uruk");
    set_pname("uruks");
    set_race_name("baby uruk");
    add_name("baby");
    set_adj(alignlook());
    add_adj(alignlook2());
    add_adj("baby");
    long_text();
    set_long(&long_desc());
    
    default_config_npc( 25 + rnd / 3);
    set_base_stat(SS_INT, 10 + rnd / 2);
    set_base_stat(SS_WIS, 10 + rnd / 2);
    set_base_stat(SS_DIS, 65 + rnd / 6);

    set_alignment(-250-rnd*10);

    set_skill(SS_WEP_SWORD,  25 + rnd / 3);
    set_skill(SS_WEP_CLUB,   25 + rnd / 3);
    set_skill(SS_WEP_KNIFE,  25 + rnd / 3);
    set_skill(SS_PARRY,      25 + rnd / 2);
    set_skill(SS_DEFENCE,    25 + rnd / 2);
    add_prop(CONT_I_HEIGHT,   85 + rnd / 2);
    add_prop(CONT_I_WEIGHT, 55000 + rnd * 400);
    add_prop(CONT_I_VOLUME, 55000 + rnd * 400);    
    add_prop(LIVE_I_SEE_DARK, 4);

    set_alarm(1.0, 0.0, &find_home());

    set_chat_time(15 + random(15));
    add_chat("Who are you?");
    add_chat("I think I ate some poo-poo.");
    add_chat("Who stole my pacifier!");
    add_chat("I want a blanket.");
    add_chat("I want a kitty .. to eat.");
    add_chat("Nobody loves me.");
    add_chat("They took me from mama when I was five minutes old.");
    add_chat("Please don't kill me.");
    add_chat("When I grow up, I'm going to be a soldier!");
    add_chat("I have an ouchie. Will you kiss it?");
    add_chat("Where is my bottle?");

    set_cchat_time(5 + random(10));
    add_cchat("Waaaaaaaa!");
    add_cchat("Stop, or I'll tell my dad!");
    add_cchat("Ouch that hurt!");
    add_cchat("Mommy!!!");
    add_cchat("Leave me alone, you bully!");
    add_cchat("I'm going to hold my breath until you stop trying to kill me.");

    set_act_time(15 + random(15));	
    add_act("cry");
    add_act("get all from corpse");
    add_act("pout");
    add_act("sniff");		
    add_act("whine");		

    set_cact_time(2 + random(2));
    add_cact("scream"); 
    add_cact("cry"); 
    add_cact("grovel"); 
    add_cact("frown"); 
    add_cact("cry"); 

    create_igard_orc();
}


string
long_desc()
{
    return long_looks;
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


