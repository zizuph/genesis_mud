#include "/d/Terel/include/Terel.h"
#include "../include/hills_defs.h"
#include <ss_types.h>
#include <options.h>
#include <money.h>

inherit STDMONSTER;
inherit "/std/act/domove";

string face();
void arm_me();

int
query_option(int opt)
{
    return (opt == OPT_UNARMED_OFF);
}
void
create_monster()
{

    set_race_name("kobold");
    set_name("weakling");
    set_adj(face());
    set_gender(MALE);
    set_long("A small dog-faced creature with grey scaly skin. " +
        "Large black eyes stare back at you wildly as you notice " +
        "many missing and broken teeth gaping from its mouth. " +
        "He looks malnourished and somewhat weary but still able " +
        "to put up a fight.\n");

    set_base_stat(SS_STR, 10 + random(5) );
    set_base_stat(SS_DEX, 10 + random(5) );
    set_base_stat(SS_CON, 10 + random(5) );
    set_base_stat(SS_INT, 9 + random(3) );
    set_base_stat(SS_WIS, 9 + random(3) );
    set_base_stat(SS_DIS, 9 + random(3) );

    add_prop(CONT_I_WEIGHT, 25000);
    add_prop(CONT_I_HEIGHT, 30000);
    add_prop(CONT_I_VOLUME, 25000);
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(LIVE_I_SEE_DARK, 5);
    add_prop(NPC_I_NO_FEAR, 1);

    set_restrain_path(HILLS_PATH);
    set_random_move(60);
    set_aggressive(1);
    set_attack_chance(50);
    set_alignment(-100 - random(100) );
   
    set_skill(SS_WEP_CLUB, 20 + random(10) );
    set_skill(SS_WEP_AXE, 10 + random(10) );
    set_skill(SS_WEP_SWORD, 10 + random(10) );
    set_skill(SS_WEP_KNIFE, 15 + random(10) );
    set_skill(SS_WEP_POLEARM, 20 + random(10) );
    set_skill(SS_2H_COMBAT, 20 + random(10) );
    set_skill(SS_DEFENCE, 15 + random(10) );
    set_skill(SS_PARRY, 15 + random(10) );
    set_skill(SS_AWARENESS, 5 + random(5) );
    arm_me();
}

string face()
{
    string *faces;
    faces = ({"half-frozen", "squallid", "feeble", "meager", "puny",
        "lethargic", "putrid", "unkempt", "sickly", "skinny",
        "starved", "pathetic", "shivering", "stunted"});
    return faces[random(sizeof(faces))];
}

void
arm_me()
{
    FIX_EUID;
    MONEY_MAKE( random(3), "silver")->move(TO);
    MONEY_MAKE( 3 + random(3), "copper")->move(TO);

    switch(random(5))
    {
        case 0:
            clone_object(HILLS_PATH + "weapon/sword")->move(TO);
            break;

        case 1:
            clone_object(HILLS_PATH + "weapon/club")->move(TO);
            break;

        case 2:
            clone_object(HILLS_PATH + "weapon/knife")->move(TO);
            break;

        case 3:
            clone_object(HILLS_PATH + "weapon/axe")->move(TO);
            break;

        case 4:
            clone_object(HILLS_PATH + "weapon/spear")->move(TO);
            break;

    }
    clone_object(HILLS_PATH + "armour/ragged_fur")->move(TO);

    command("wear all");
    command("wield all");
    return;
}
