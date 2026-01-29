#pragma save_binary
#pragma strict_types

inherit "/std/monster";

#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <money.h>
#include <stdproperties.h>

#include "defs.h"

string  face();
void    get_weapon();
void    get_money();

public void
create_monster()
{
    set_race_name("uruk");
    set_name("uruk");
    set_adj(face());

    set_long("This warrior has no love to spare for those of your kind.\n"+
             "He would probably sell his mother for a copper.\n");

    set_base_stat(SS_STR, random(8)+10);
    set_base_stat(SS_DEX, 9);
    set_base_stat(SS_CON, 10);
    set_base_stat(SS_INT, 6);
    set_base_stat(SS_WIS, 8);
    set_base_stat(SS_DIS, 9);
    set_attack_chance(90);

    add_prop(CONT_I_WEIGHT, 90000);
    add_prop(CONT_I_HEIGHT, 1900);
    add_prop(CONT_I_VOLUME, 88000);

    set_skill(SS_WEP_SWORD, 15);
    set_skill(SS_UNARM_COMBAT, 10);

    set_all_hitloc_unarmed(5);

    setuid (); seteuid (getuid ());

    set_alarm(4.0 + 4.0 * rnd(), 0.0, get_weapon);
    get_money();
}

string
face()
{
    string *faces =
        ({"veteran", "grim", "grumpy", "experienced", "sturdy", "massive",
          "big", "nasty", "angry", "mean", "dirty", "ugly", "foul",
          "brutal", "battered", "savage", "ugly", "ugly"});
    return faces[random(sizeof(faces))];
}

void
get_weapon()
{
    object ob;

    setuid (); seteuid (getuid ());

    if (random(20))
        ob = clone_object(OBJ_DIR + "ssword");
    else
        ob = clone_object(OBJ_DIR + "lsword");

    ob->move(this_object());
    command("grin");
    command("wield sword");
    command("say Ok you bastard. Make me happy!");
    command("spit elf");
    set_aggressive(1);
}

void
get_money()
{
    setuid (); seteuid (getuid ());
    MONEY_MAKE_CC(25 + random(40))->move(this_object());
    MONEY_MAKE_SC( 5 + random(10))->move(this_object());
}

