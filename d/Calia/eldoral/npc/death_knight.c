#pragma strict_type

#include "defs.h"
#include <composite.h>

#define FROST_PEN 300

inherit UNDEAD;

/*
 * Function name: arm_me
 * Description  : Clones knight's equip and forces wield/wear.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
arm_me()
{
    seteuid(getuid());

    clone_object(WEP + "claymore")->move(TO);
    tell_room(environment(), "The death knight draws forth " +
        "a claymore from the very shadows themselves.\n");
    command("wield all");
    clone_object(ARM + "death_plate")->move(TO);
    tell_room(environment(), "The death knight seems to pull " +
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
    set_name("knight");
    add_name("undead");
    add_name(DEATH_KNIGHT);
    set_adj("death");
    set_race_name("human");
    set_short("death knight");
    set_long("The dark figure before you appears to be a " +
        "death knight. Once flesh and bone, the figure " +
        "is now nothing more than a wraith-like " +
        "apparition, @@check_my_equip@@" +
        "with burning red points of light where " +
        "its eyes once were. " +
        "An aura of fear radiates from it, and you " +
        "can't help but feel even the light flees from " +
        "its presence, as the darkness seems to thicken " +
        "into a cloak around its shoulders. " +
        "\n");
    create_undead_monster(UNDEAD_KNIGHT);
}

public int
special_attack(object enemy)
{
    int i,
        dam,
        phit;
    string message1,
           message2;

    if (random(10))
        return 0;

    enemy->catch_msg(QCTNAME(TO) + " draws back its arm, and " +
        "casts forth a sphere of intense cold at you!\n");
    tell_watcher(QCTNAME(TO) + " draws back its arm, and " +
        "casts forth a sphere of intense cold at " + QTNAME(enemy) +
        ".\n", enemy);

    if (enemy->query_res_magic(MAGIC_I_RES_COLD) > random(100))
    {
        tell_object(enemy, "The intense cold chills you a " +
            "bit, but leaves you otherwise undamaged.\n");
        tell_watcher("The intense cold leaves " + QTNAME(enemy) +
            "shivering a bit, but that's it.\n", enemy);
        return 1;
    }
    
    phit = enemy->hit_me(FROST_PEN, MAGIC_DT, TO, -1)[0];
    switch(phit)
    {
        case -1:
            message1 = "The frost gives you only a light chill.\n";
            message2 = "The frost seems to give " + 
                enemy->query_objective() + " only a light chill.\n";
            break;
        case 0:
            message1 = "The frost makes you shiver a bit, but " +
                "nothing too painful.\n";
            message2 = "The frost makes " + enemy->query_objective() +
                " shiver a bit, but it doesn't appear too painful.\n";
            break;
        case 1..25:
            message1 = "You feel small sections of your skin " +
                "freeze painfully, but it's not too bad.\n";
            message2 = "Small sections of " + 
                enemy->query_possessive() + " skin appear " +
                "to have frozen painfully.\n";
            break;
        case 26..50:
            message1 = "The frost penetrates deep beneath your " +
                "skin, painfully freezing a fair amount of " +
                "tissue.\n";
            message2 = "The frost penetrates deep beneath " +
                enemy->query_possessive() + " skin, and appears " +
                "to be fairly painful.\n";
            break;
        case 51..75:
            message1 = "The frost sears your skin with a cold " +
                "intense enough it feels like flames.\n";
            message2 = "The frost sears " + 
                enemy->query_possessive() + " skin with a very " +
                "intense cold.\n";
            break;
        case 76..99:
            message1 = "Frostbite sets in, with a stabbing pain " +
                "so sharp you wonder if it will claim a body " +
                "part.\n";
            message2 = "Frostbite appears to have settled into " +
                enemy->query_objective() + " deeply and " +
                "painfully.\n";
            break;
        default:
            message1 = "The intense cold stops your heart completely!\n";
            message2 = "Suddenly, " + enemy->query_pronoun() + 
                "clutches at " + enemy->query_possessive() + " chest " +
                "and stiffens up!\n";
    }

    tell_object(enemy, message1);
    tell_watcher(message2, enemy);
    if (enemy->query_hp() <= 0)
        enemy->do_die(TO);
    return 1;
}

