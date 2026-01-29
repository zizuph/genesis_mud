/* This is a gnome alchemist who makes his home in Rust. Created
4.1.99, Bishop of Calia. */

inherit "/std/monster.c";
inherit "/d/Genesis/lib/intro.c";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <options.h>
#include <const.h>
#include <wa_types.h>
#include "defs.h"

#define ALIGN   0


void
equip_me()
{
    object spellob, armour;

    seteuid(getuid(TO));

    spellob = clone_object(RUST_SPECIALS + "alchemist_spell_obj");
    spellob->move(TO);

    armour = clone_object(RUST_ARMOURS + "alchemist_cloak");
    armour->move(TO);

    command("wear armours");
}


void
create_monster()
{
    set_name("clysus");
    add_name("clysus");
    set_race_name("gnome");

    add_adj("ancient");
    add_adj("enigmatic");

    set_title("the Master Alchemist");
    set_gender(G_MALE);

    set_long("This ancient gnome seems to barely notice you, as he" +
        " is busy pouring over old parchments and writing notes on" +
        " blank ones. He has a pronounced nose, and very" +
        " big, bushy eyebrows.\n");

    set_alignment(ALIGN);

    set_base_stat(SS_STR, 100);
    set_base_stat(SS_DEX, 130);
    set_base_stat(SS_CON, 130);
    set_base_stat(SS_INT, 180);
    set_base_stat(SS_WIS, 180);
    set_base_stat(SS_DIS, 140);

    set_skill(SS_DEFENCE, 90);
    set_skill(SS_AWARENESS, 90);
    set_skill(SS_ELEMENT_EARTH, 90);
    set_skill(SS_ELEMENT_LIFE, 90);
    set_skill(SS_FORM_ENCHANTMENT, 90);
    set_skill(SS_SPELLCRAFT, 90);

    set_hp(query_max_hp());
    set_mana(query_max_mana());


    add_prop(CONT_I_WEIGHT, 35000);
    add_prop(CONT_I_VOLUME, 35000);
    add_prop(CONT_I_HEIGHT, 90);
    add_prop(NPC_I_NO_LOOKS,1);
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(LIVE_I_SEE_INVIS,1);
    add_prop(LIVE_I_SEE_DARK,1);
    add_prop(OBJ_I_RES_POISON, 80);
}

string
which_attack()
{
    if (TO->query_hp() < (TO->query_max_hp() / 2) &&
        random(2) == 0 && TO->query_mana() > 80)
    {
        return "cast alchemistheal";
    }
    else
    if (sizeof(TO->query_enemy(-1)) > 2 &&
        TO->query_mana() > 150)
    {
        return "cast magneticfun";
    }
    else
    if (sizeof(TO->query_enemy(-1)) > 1 && random(2) == 0 &&
        TO->query_mana() > 150)
    {
        return "cast magneticfun";
    }
    else
    {
        return "hepp";
    }
}

int
special_attack(object enemy)
{
    int *hitresult, penvalue;
    string how;

    if (random(2))
    {
        return 0;
    }

    if (which_attack() == "hepp")
    {
        penvalue = 800;
        penvalue -= (8*enemy->query_prop(OBJ_I_RES_FIRE));
        hitresult = enemy->hit_me(penvalue, MAGIC_DT, TO, -1);
        switch (hitresult[0])
        {
            case 0:
                how = "unharmed";
                break;
            case 1..5:
                how = "slightly burnt";
                break;
            case 6..10:
                how = "burnt";
                break;
            case 11..20:
                how = "badly burnt";
                break;
            case 21..50:
                how = "horribly burnt";
                break;
            default:
                how = "burnt almost to a crisp";
                break;
        }
        if (enemy->query_hp() <= 0)
        {
            how = "burnt to a cinder";
        }
        tell_room(environment(enemy), QCTNAME(TO) + " somehow" +
            " produces a potion, and throws it at " + QTNAME(enemy) +
            "! It explodes on impact, and " + QTNAME(enemy) + " is " +
            how + ".\n", enemy);
        enemy->catch_msg(query_The_name(enemy) + " somehow" +
            " produces a potion, and throws it at you! It explodes" +
            " on impact, and you are " + how + ".\n");
        if (enemy->query_hp() <= 0)
        {
            enemy->do_die(TO);
        }
        return 1;
    }
    else
    {
        TO->command(which_attack());
    }
}


public void
greet(object who)
{
    if(who->query_average_stat() > 120)
    {
        command("introduce myself to " + OB_NAME(who));
        command("nod " + OB_NAME(who));
    }
    else
    {
        command("say Be quiet, child.");
    }
}

public void
introduce(object who)
{
    if(who->query_average_stat() > 120)
    {
        command("introduce myself to " + OB_NAME(who));
        command("nod " + OB_NAME(who));
    }
    else
    {
        command("say Be quiet, child.");
    }
}

void
attacked_by(object enemy)
{
    find_living("bishop")->catch_msg("Hmm?\n");
    (RUST_SPECIALS + "guard_rescue.c")->set_priority(1, TO);
    TO->add_prop(GNOME_BEEN_ATTACKED, 1);
}


