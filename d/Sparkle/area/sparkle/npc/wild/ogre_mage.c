#pragma save_binary
#pragma strict_types

inherit "/std/monster";

#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include <stdproperties.h>

#include "defs.h"

string face();

void
create_monster()
{
    if (!IS_CLONE)
        return;

    seteuid(getuid(this_object()));

    set_race_name("ogre mage");
    set_name("maharuk");
    set_living_name("maharuk");
    add_name("ogre");
    add_name("mage");
    set_adj(face());

    set_long("He eyes you suspiciously, looking for valuables.\n"+
             "He looks quite determined and very strong.\n");

    set_base_stat(SS_STR, random(14)+10);
    set_base_stat(SS_DEX, 14);
    set_base_stat(SS_CON, 15);
    set_base_stat(SS_INT, 9);
    set_base_stat(SS_WIS, 12);
    set_base_stat(SS_DIS, 10);
    set_hp(1000); /* reduced to correct level according to con. */

    add_prop(CONT_I_WEIGHT, 140000);
    add_prop(CONT_I_HEIGHT, 2100);
    add_prop(CONT_I_VOLUME, 110000);

    set_random_move(20);
    set_aggressive(0);
    set_attack_chance(1);
    set_alignment(-300 - random(200));


    set_skill(SS_WEP_POLEARM, 27);
    set_skill(SS_WEP_SWORD, 19);
    set_skill(SS_WEP_KNIFE, 11);
    set_skill(SS_WEP_CLUB, 4);
}

string
face()
{
    string *faces;
    faces = ({"veteran", "grim", "grumpy", "experienced", "sturdy", "massive",
              "big", "nasty", "angry", "mean", "dirty", "ugly", "foul",
              "brutal", "battered", "savage", "ugly", "ugly"});
    return faces[random(sizeof(faces))];
}

void
arm_me()
{
    MONEY_MAKE(random(150)+150,"copper")->move(TO);
    MONEY_MAKE(random(50)+25, "silver")->move(TO);

    setuid (); seteuid (getuid ());

    clone_object(S_LOCAL_WEP_DIR + "halberd")->move(TO);
    clone_object(S_COMMON_WEP_DIR + "knife")->move(TO);
    command("wield halberd");
}

