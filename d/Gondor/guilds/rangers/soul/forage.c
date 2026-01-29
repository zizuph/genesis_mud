/*
 * /d/Gondor/guilds/rangers/soul/forage.c
 *
 * Included in the soul. The forage ability allows a player to forage
 * for food when outside at a small fatigue and mana cost.
 * Originally coded by Mayhem in April 1994.
 *
 * Modification log:
 * March 1997, Olorin: Revision. Combined two separate functions into 
 *                     forage_animal().
 * 13 April 2001 Gwyneth: General cleanup and move -- also added the 
 *                         ability to find fish in a water room.
 */

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include "/d/Gondor/defs.h"

#define SMALL_HUNT_COST     5
#define LARGE_HUNT_COST     10
#define GONDOR_I_HUNTING    "_gondor_i_hunting"
#define GONDOR_I_HUNTED     "_gondor_i_hunted"
#define MAX_HUNT            2

public int forage_animal(object player, string size);

/* Function name: forage
 * Description  : 
 * Arguments    : string str - the argument
 * Returns      : 1 on success, 0 on failure
 */
public int
forage(string str)
{
    int speed;
    object tp = this_player(),
           room;
 
    if (!strlen(str))
    {
        notify_fail("Forage for what?\n");
        return 0;
    }
 
    if (objectp(tp->query_attack()))
    {
        notify_fail("You cannot hunt for food while fighting!\n");
        return 0;
    }
    else if (tp->query_prop(GONDOR_I_HUNTING))
    {
        notify_fail("You are already foraging for food!\n");
        return 0;
    }
    else if ((room = environment(tp))->query_prop(ROOM_I_INSIDE))
    {
        notify_fail("You can only hunt for game out in the open.\n");
        return 0;
    }

    if (parse_command(str, ({}), " [for] [small] 'game' / 'animals' "))
    {
        speed = ((50 - tp->query_skill(SS_HUNTING)) / 2 + 10);
        speed = (speed <= 10 ? 10 : speed);
        write("You start foraging for some small animals to eat.\n");
        say(QCTNAME(tp) + " starts foraging for food.\n");
        tp->add_prop(GONDOR_I_HUNTING, 1);
        set_alarm(itof(speed), 0.0, &forage_animal(tp, "small"));
        return 1;
    }

    if (parse_command(str, tp, " [for] [big] [large] 'game' / 'animals' "))
    {
        speed = ((50 - tp->query_skill(SS_HUNTING)) / 2 + 20);
        speed = (speed <= 10 ? 10 : speed);
        write("You start foraging for some large animals to eat.\n");
        say(QCTNAME(tp) + " starts foraging for food.\n");
        tp->add_prop(GONDOR_I_HUNTING, 1);
        set_alarm(itof(speed), 0.0, &forage_animal(tp, "large"));
        return 1;
    }

    notify_fail("Forage for what?\n");
    return 0;
}

/*
 * Function name: forage_animal
 * Description  : Called from the forage alarm
 * Arguments    : object player - the hunter
 *                string size - the size of the animal
 */
public int 
forage_animal(object player, string size)
{
    int food_amount,
        cost,
        task;
    object animal,
           room;
    string animal_type;
 
    if (!objectp(player))
        return 0;
 
    set_this_player(player);
    room = environment(player);
    player->remove_prop(GONDOR_I_HUNTING);
    if (room->query_prop(ROOM_I_INSIDE))
    {
        notify_fail("You cannot forage for food indoors!\n");
        return 0;
    }
    else if (environment(player)->query_prop(GONDOR_I_HUNTED) >= MAX_HUNT)
    {
        write("You notice this area has already been hunted " +
            "in a few times, and decide not to over-hunt the area.\n");
        tell_room(environment(player), QCTNAME(player) + " returns " +
            "empty-handed from hunting.\n", player);
        return 1;
    }

    switch (size)
    {
    default:
    case "small":
        cost = SMALL_HUNT_COST;
        task = TASK_ROUTINE;
        break;
    case "large":
        cost = LARGE_HUNT_COST;
        task = TASK_DIFFICULT;
        break;
    }
 
    if (player->query_mana() < cost)
    {
        write("The strain is too great for you to concentrate on foraging.\n");
        return 1;
    }
    else if (player->query_fatigue() < cost)
    {
        write("Your weary bones refuse to forage for food.\n");
        return 1;
    }

    player->add_mana(cost);
    player->add_fatigue(cost);
 
    if (player->resolve_task(task, ({ TS_WIS, SS_HUNTING })) <= 0)
    {
        write("You search all around for " + size + " game animals, " +
              "but are unable to find any.\n");
        say(QCTNAME(player) + " searches all around but can not " +
            "seem to catch anything to eat.\n", player);
        return 1;
    }
 
    if ((room->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER) ||
        (room->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER))
    {
        switch(size)
        {
        default:
        case "small":
            switch (random(3))
            {
            case 0:
                animal_type = "minnow";
                food_amount = 40;
                break;
            case 1:
                animal_type = "sunfish";
                food_amount = 60;
                break;
            default:
                animal_type = "perch";
                food_amount = 100;
                break;
            }
            break;
        case "large":
            switch(random(3))
            {
            case 0:
                animal_type = "carp";
                food_amount = 480;
                break;
            case 1:
                animal_type = "catfish";
                food_amount = 510;
                break;
            default:
                animal_type = "bass";
                food_amount = 250;
                break;
            }
            break;
        }
    }
    else
    {
        switch (size)
        {
        default:
        case "small":
            switch (random(6))
            {
            case 0:
                animal_type = "coney";
                food_amount = 70;
                break;
            case 1:
                animal_type = "pheasant";
                food_amount = 80;
                break;
            case 2:
                animal_type = "squirrel";
                food_amount = 50;
                break;
            case 3:
                animal_type = "quail";
                food_amount = 55;
                break;
            case 4:
                animal_type = "duck";
                food_amount = 65;
                break;
            default:
                animal_type = "pig";
                food_amount = 100;
                break;
            }
            break;
        case "large":
            switch (random(6))
            {
            case 0:
                animal_type = "deer";
                food_amount = 480;
                break;
            case 1:
                animal_type = "moose";
                food_amount = 510;
                break;
            case 2:
                animal_type = "boar";
                food_amount = 450;
                break;
            case 3:
                animal_type = "elk";
                food_amount = 495;
                break;
            case 4:
                animal_type = "goat";
                food_amount = 445;
                break;
            default:
                animal_type = "yak";
                food_amount = 455;
                break;
            }
            break;
        }
    }

    room->add_prop(GONDOR_I_HUNTED, room->query_prop(GONDOR_I_HUNTED) + 1);
    write("You successfully catch and prepare " + LANG_ADDART(animal_type) + 
        " for cooking.\n");
    say(QCTNAME(player)+" catches " + LANG_ADDART(animal_type) +
        " for dinner.\n");
 
    setuid(); 
    seteuid(getuid());
 
    animal = clone_object(OBJ_DIR + "animal_corpse");
    animal->set_name(animal_type);
    animal->set_animal_type(animal_type);
    animal->set_food_amount(food_amount);
    animal->move(room);

    /* Task support */
    if (TP->query_prop(RANGER_I_TASK) == COOK_TASK)
    {
        if (sizeof(TP->query_prop(RANGER_O_COOK_TASK)))
            TP->add_prop(RANGER_O_COOK_TASK,
              TP->query_prop(RANGER_O_COOK_TASK) + ({ animal }));
        else
            TP->add_prop(RANGER_O_COOK_TASK, ({ animal }));
    }
 
    return 1;
}
