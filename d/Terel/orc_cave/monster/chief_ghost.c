/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * chief_ghost.c
 *
 * The ghost of the orcchief
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

#include <ss_types.h>
#include <wa_types.h>
#include <money.h>
#include <language.h>

#define ALIGN           -300

/*
 * Global variables
 */

static object orc_killer;
static string orc_killer_name;

void
init_living()
{
    ::init_living();
}

void
create_monster()
{
    ::create_monster();
    set_name("orcghost");
    add_name("ghost");
    set_long("He is a ghost of the orcchief.  He is even more fearsome " +
            "in his undead form.\n");
    set_race_name("ghost");
    set_gender(MALE);

    set_stats(({190, 180, 200, 120, 120, 120}));
    SET_MAX_HP;
    set_alignment(ALIGN);
    set_all_hitloc_unarmed(60);
    set_all_attack_unarmed(35, 40);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_WEP_SWORD, 100);
    
    add_prop(LIVE_I_SEE_INVIS,10);
    add_prop(LIVE_I_SEE_DARK, 99);
    add_prop(CONT_I_WEIGHT, 230000);
    add_prop(CONT_I_VOLUME, 230000);
    add_prop(CONT_I_MAX_WEIGHT, 330000);
    add_prop(CONT_I_MAX_VOLUME, 330000);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_UNDEAD,80);

    AGGRESSIVE;
    
    trig_new("%s 'moves behind' %s", "attack_killer");
    trig_new("%s 'rescues' %s", "attack_killer");    
}

void
arise()
{
     command("emote arises from the dead body of the orchief.");
     command("say " + orc_killer_name + "!  You killed me!");
     command("say Prepare to die!");
}

void
set_killer(object k)
{
     orc_killer = k;
     orc_killer_name = k->query_name();
     set_random_move(1);
     set_follow(orc_killer_name);
     set_random_move(1);     
}

void
attack_killer(string s1, string s2)
{
     aggressive_attack(orc_killer);
}

void attack()
{
     aggressive_attack(orc_killer);
}
