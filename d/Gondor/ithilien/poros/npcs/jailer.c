/*
 *   /d/Gondor/ithilien/poros/npcs/jailer.c
 *
 *   This is the Haradan jailer of the corsairs.
 *
 *   Talisan,  February 1996
 */

#pragma strict_types

inherit "/d/Gondor/ithilien/poros/npcs/corsair_master";

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <money.h>

#include "/d/Gondor/defs.h"

//      Prototypes
void    get_money();
void    get_key();

public void
create_corsair()
{
    set_name("corsair jailer");
    add_name(({"jailer", "corsair", "pirate", "haradan"}));
    set_adj("sadistic");
    add_adj("haradan");
    set_long(BSN("There is a cruel and sadistic air about this tall and "
      + "fierce-looking man. He serves as the corsairs' jailer and chief "
      + "interrogator, a job he seems to enjoy immensely. He wear the red sash "
      + "and garb of a former Royal Haradan Guardsmen; you feel this individual "
      + "would be quite competent in battle."));

    default_config_npc(80 +random(5));

    set_base_stat(SS_STR, 90 +random(5));
    set_base_stat(SS_DEX, 105 +random(5));

    set_skill(SS_WEP_SWORD, 95 +random(5));
    set_skill(SS_DEFENSE, 80 +random(5));
    set_skill(SS_PARRY, 80 +random(5));
    set_skill(SS_BLIND_COMBAT, 70 +random(5));
    set_skill(SS_AWARENESS, 85 +random(5));

    set_alignment(-100);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(CONT_I_HEIGHT, 200 +random(10));
    add_prop(CONT_I_WEIGHT, 72500 +random(30*500));
    add_prop(CONT_I_VOLUME, 70000 +random(30*500));

    set_chat_time(3 +random(3));
    add_chat("It's not my fault they usually die; they're just weak.");
    add_chat("Nothing like a good whipping to start your day off right.");
    add_chat("Torture is an art!");
    add_chat("You shouldn't cut too deeply, just enough to remove the skin.");
    add_chat("Have you talked to the Captain yet? He needs someone to help him with a task.");
    add_chat("In my youth I was a member of the Royal Guard of Harad.");
    add_chat("At least the corsairs pay a decent wage.");
    add_chat("Raiding Gondor is child's play!");
    add_chat("The Rangers are weak, and the Mages are arrogant fools! Surely Harad will rule Middle-earth in the end.");
    add_chat("Angmar who?");

    set_cchat_time(2);
    add_cchat("The Goddess will have your soul!");
    add_cchat("Die Jackal!");
    add_cchat("Fool, you deserve to die!");
    add_cchat("After I defeat you, I will torture you for days!");
    add_cchat("Have a taste of Haradan steel!");
    add_cchat("You are nothing!");

    set_act_time(4 +random(3));
    add_act("grin sadi");
    add_act("get all");
    add_act("get all from corpse");
    add_act("cackle");
    add_act("twinkle evil");
    add_act("laugh evil");
    add_act("ponder the best way to skin a dwarf.");
    add_act("emote cracks his whip at you.");

    set_cact_time(2 +random(2));
    add_cact("snarl");
    add_cact("ponder contemptible fools...");
    add_cact("scream");
    add_cact("grin");
    add_cact("shout For Harad!");

}

public void
arm_me()
{
    clone_object(POROS_DIR + "armours/studded_leather")->move(this_object());
    clone_object(POROS_DIR + "armours/shield")->move(TO);
    clone_object(POROS_DIR + "armours/helmet")->move(TO);
    command("wear all");

    clone_object(POROS_DIR + "weapons/scimitar")->move(this_object());
    command("wield all");
    clone_object(POROS_DIR + "weapons/whip")->move(this_object());

    get_money();
    get_key();
}

void
get_money()
{
    MONEY_MAKE_SC(30 +random(20))->move(TO);
    MONEY_MAKE_GC(3 +random(3))->move(TO);
}

void
get_key()
{
    clone_object(POROS_DIR + "obj/key_cell")->move(TO);
}

int
query_knight_prestige() {return 100;}
