/*
 * coded by Amelia for Ten Alders 4/13/97
 * the witch's garden
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/gont/tenalders/std/base_herb_room";

#include "/d/Earthsea/herbs/herb_sets/garden_herbs.h"
#include "garden_tells.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

private object bird;
private int key_found = 0, coins_found = 0;

public void
create_herb_room()
{
    set_short("A spring");
    set_long("You enter a secluded area " +
        "of the garden, surrounded by bushes on " +
        "three sides. To the west is a small pool " +
        "bubbling from a natural spring right out of " +
        "a cleft between some rocks. The water looks " +
        "very pure and fresh and makes a musical " +
        "sound as it splashes into the pool. Overhead the " +
        "branches from a large oak tree provide some shade.\n");
    add_item((({"branches", "oak tree", "tree", "shade" })),
        "The branches from a large oak tree to the southwest " +
        "extend over this area providing some shade from the " +
        "hot sun. One long limb droops down lower than the rest.\n");
    add_item((({"limb", "long limb"})),
        "The limb from the oak tree holds a small nest in the " +
        "fingertips of its twigs.\n");
    add_item((({"nest", "small nest"})),
        "You can't really get a good look at the nest from here.\n");
    add_cmd_item((({"tree", "oak tree", "branch", "limb", "branches"})),
        "climb", "You can't seem to get a good hold to climb it " +
        "from here.\n");
    add_item("plants",
        "Many types of plants grow here including " +
        "common garden plants and some which " +
        "have planted themselves from the wild.\n");
    add_item((({"pool", "water", "spring", "natural spring"})),
        "The spring water looks pure enough to drink. You can see " +
        "some shiny objects lying on the bottom of the pool.\n");
    add_item((({"objects", "shiny objects"})),
        "It looks as though some coins and other objects, " +
        "possibly fallen from someone's pockets as they leaned " +
        "over to take a drink, have fallen into the pool.\n");
    add_item((({"herb", "herbs"})),
        "Green and dark purple herbs scent the air.\n");
    add_item((({"bushes", "bush"})),
        "Thick and impenetrable bushes surround this small " +
        "area, making it a quiet private spot.\n");
    add_item((({"cleft", "rocks"})),
        "There is a cleft between some large rocks by the " +
        "bushes to the left, from where a spring of natural " +
        "clear water bubbles.\n");
    add_prop(OBJ_I_CONTAIN_WATER, -1);
    set_up_herbs(select_herb_files(GARDEN_HERBS), GARDEN_LOCATIONS, 3);
    set_tell_time(80);
    add_tell("Sunlight reflects on the surface of " +
        "the pool.\n");
    add_tell("Clear water trickles from the spring into the pool.\n");
    add_tell("You seem to hear a song in the music of the " +
        "bubbling spring.\n");
    add_tell("You inhale the fresh fragrance of herbs.\n");
    add_exit("witch_garden_6", "southwest");
    add_prop(OBJ_S_SEARCH_FUN, "find_key");
    reset_room();
}

public void
reset_room()
{
    ::reset_room();

    key_found = 0;
    coins_found = 0;

    if(!objectp(bird))
    {
        bird = clone_object("/d/Earthsea/gont/tenalders/npc/baby_bird");
        bird->move(this_object());
        bird->command("emote falls from above.");
    }
}

public string
find_key(object player, string str)
{
    object key;

    if(str == "pool" || str == "water" || str == "spring" ||
        str == "bottom of the pool" || str == "natural spring")
    {
        if(!key_found)
        {
            key_found = 1;
            key = clone_object("/d/Earthsea/gont/tenalders/obj/items/brass_key");
            key->move(player);
            return "You find something shiny!\n";
        } else if(!coins_found) {
            coins_found = 1;
            (MONEY_MAKE_SC(random(10)))->move(player);
            return "You find some coins!\n";
        }
    }

    return herb_search(player, str);
}

public int
water_animal(string arg);

public int
drink_message(object tp)
{
    write("Bending down you scoop up some water in " +
        "your hands and get a refreshing drink.\n");
    tell_room(environment(tp), QCTNAME(tp) +
        " bends down and drinks some water from the spring.\n",
        ({ tp }));
    return 1;
}

public int
drink(string str)
{
    object tp = this_player(), env = environment(tp), to = this_object();
    int dmax = tp->drink_max();
    string dummy;

    if (to->is_steed())
    {
        return water_animal(str);
    }

    if(!str || !parse_command(str,env,
        "%w [from] [the] [pool] / [spring]", dummy) ||
        dummy != "water")
    {
        return notify_fail("Drink what?\n");
    }

    if(tp->drink_soft(dmax / 10, 1))
    {
        tp->drink_soft(dmax / 10);
        drink_message(tp);
        return 1;
    } else if(tp->drink_soft(dmax / 15, 1)) {
        tp->drink_soft(dmax / 15);
        drink_message(tp);
        return 1;
    } else if(tp->drink_soft(dmax / 20, 1)) {
        tp->drink_soft(dmax / 20);
        drink_message(tp);
        return 1;
    }

    write("You cannot drink more from the spring.\n");
    return 1;
}

public int
water_animal(string arg)
{
    object animal, tp = this_player();
    int i, amount;

    if(!arg || !parse_command(arg, this_object(),
        "[the] %o [from] [at] [the] [river]", animal) ||
        !living(animal))
    {
        return notify_fail("Water what, where?\n");
    }

    if(animal->query_driver() == tp)
    {
        return notify_fail("You cannot water " + QTNAME(animal) +
            " while riding it!\n");
    }

    if(animal->query_leader() != tp)
    {
        return notify_fail("You must be leading " + QTNAME(animal) +
            " to water it!\n");
    }

    say(QCTNAME(tp) + " leads " + tp->query_possessive() + " " +
        animal->short() + " to the spring and waters " +
        animal->query_objective() + ".\n");
    write("You lead your " + animal->short() +
        " to the spring and water " + animal->query_objective() +
        ".\n");

    amount = animal->drink_max() / 20;

    for(i=0; i<20; i++)
    {
        animal->drink_soft(amount);
    }

    animal->drink_soft(animal->drink_max() - animal->query_soaked());
    return 1;
}

public void
init()
{
    ::init();
    add_action(drink, "drink");
    add_action(water_animal, "water");
}
