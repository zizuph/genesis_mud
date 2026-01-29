#pragma strict_type

#include "defs.h"
#include <composite.h>

#define GAS_DAM   400

inherit UNDEAD;

public void
arm_me()
{
    clone_object(WEP + "lochaber1")->move(TO);
    tell_room(environment(), "The death lord draws forth " +
        "a lochaber axe from the very shadows themselves.\n");
    command("wield all");
    clone_object(ARM + "death_plate_2")->move(TO);
    tell_room(environment(), "The death lord seems to pull " +
        "the shadows about itself, where they coalesce into a dark " +
        "plate armour.\n");
    command("wear all");
}

public string
check_my_equip()
{
    object *obarr = all_inventory(TO);
    string str;
    object *my_wielded,
           *my_worn;
    int i;

    my_wielded = ({});
    my_worn = ({});

    for (i = 0; i < sizeof(obarr); i++)
    {
        if (obarr[i]->query_wielded() == TO)
            my_wielded += ({obarr[i]});
        if (obarr[i]->query_worn() == TO)
            my_worn += ({obarr[i]});
    }
    if (sizeof(my_wielded))
        str = "wielding " + COMPOSITE_DEAD(my_wielded);
    else
        str = "";
    if (sizeof(my_worn))
    {
        if (strlen(str))
            str += ", and clad in ";
        else
            str += "clad in ";
        str += COMPOSITE_DEAD(my_worn) + ", ";
    }
    return str;
}

public void
create_monster()
{
    set_name("lord");
    add_name("undead");
    add_name(DEATH_LORD);
    set_adj("death");
    set_race_name("human");
    set_short("death lord");
    set_long("Before you stands a monster straight out of " +
        "the depths of nightmares. Humanoid in shape, the " +
        "figure could be death itself, without the robes " +
        "and scythe. Horrible green flames burn where " +
        "eyes should be, but nothing else that could be " +
        "described as a face can be seen. In fact, it " +
        "appears to have no physical form at all, except " +
        "for a hazy, black mist, @@check_my_equip@@and " +
        "those nerve-wracking eyes." +
        "\n");
    create_undead_monster(UNDEAD_LORD);
    always_block = 1;
}

public int
special_attack(object enemy)
{
    object *armours,
           *weapons;
    int i,
        no_effect,
        phit;
    string message1,
           message2;

    if (random(8))
        return 0;

    enemy->catch_msg(QCTNAME(TO) + " exhales a stream of reddish-" +
        "yellow gas at you!\n");
    tell_watcher(QCTNAME(TO) + " exhales a stream of reddish-"+
        "yellow gas at " + QTNAME(enemy) + "!\n", enemy);

    armours = filter(all_inventory(enemy), &->check_armour());
    armours = filter(armours, &not() @ &->query_prop(OBJ_I_BROKEN));
    armours = filter(armours, &not() @ &->query_prop(OBJ_M_NO_DROP));
    weapons = filter(all_inventory(enemy), &->check_weapon());
    weapons = filter(weapons, &not() @ &->query_prop(OBJ_I_BROKEN));
    weapons = filter(weapons, &not() @ &->query_prop(OBJ_M_NO_DROP));

    if (enemy->query_magic_res(MAGIC_I_RES_ACID) > random(100))
    {
        tell_object(enemy, "The gas, however, has no effect " +
            "on you.\n");
        tell_watcher("The gas, however, has no effect on " +
            enemy->query_objective() + ".\n", enemy);
        no_effect = 1;
    }

    for (i = 0; i < sizeof(armours); i++)
    {
        if (armours[i]->query_magic_res(MAGIC_I_RES_ACID) <= random(100))
        {
            enemy->catch_msg("Your " + armours[i]->short() + 
                " corrodes a bit in the gas!\n");
            armours[i]->set_condition(armours[i]->query_condition() + 1);
        }
    }
    for (i = 0; i < sizeof(weapons); i++)
    {
        if (weapons[i]->query_magic_res(MAGIC_I_RES_ACID) <= random(100))
        {
            enemy->catch_msg("Your " + weapons[i]->short() + 
                " corrodes a bit in the gas!\n");
            weapons[i]->set_corroded(weapons[i]->query_corroded() + 1);
        }
    }

    if (no_effect)
        return 1;

    phit = enemy->hit_me(GAS_DAM, MAGIC_DT, TO, -1)[0];
    switch(phit)
    {
        case -1:
            message1 = "The gas makes you itch for a moment, " +
                "but nothing more.\n";
            message2 = "The gas makes " + enemy->query_objective() +
                " itch for a moment, but nothing more.\n";
            break;
        case 0:
            message1 = "Your eyes water a little, but nothing " +
                "that bothers you much.\n";
            message2 = capitalize(enemy->query_possessive()) +
                " eyes water a little, but nothing that seems "+
                "to bother " + enemy->query_objective() + 
                " a whole lot.\n";
            break;
        case 1..30:
            message1 = "Your eyes begin to burn and itch " +
                "painfully.\n";
            message2 = "You notice " + enemy->query_possessive() +
                " eyes look like they're burning painfully.\n";
            break;
        case 31..66:
            message1 = "The gas seems to stick to your skin, " +
                "leaving painful burns on it.\n";
            message2 = "The gas seems to stick to " +
                enemy->query_possessive() + " skin, leaving " +
                "painful burns on it.\n";
            break;
        case 67..99:
            message1 = "The gas gets into your lungs, searing " +
               "them badly.\n";
            message2 = capitalize(enemy->query_pronoun()) + 
               " inhales some of the gas, and seems barely able " +
               "to bite back a scream of agony.\n";
            break;
        default:
            message1 = "The gas completely envelops you, and " +
                "the pain is simply too much.\n";
            message2 = "The gas completely envelops " +
                enemy->query_objective() + ", and the " +
                "pain appears to be too much. " +
                capitalize(enemy->query_pronoun()) + " collapses " +
                "to the ground in a heap.\n";
    }

    tell_object(enemy, message1);
    tell_watcher(message2, enemy);

    if (enemy->query_hp() <= 0)
        enemy->do_die(TO);

    return 1;
}

public int
second_life(object killer)
{
    killer->add_prop(LIVE_I_BEAST_QUEST,
        killer->query_prop(LIVE_I_BEAST_QUEST) | BQ_KILLED_LORD);
    return 0;
}

