#include "/d/Earthsea/sys/properties.h"
#include <macros.h>

public int
water_animal(string arg);

public int
drink_water(string arg)
{
    object tp = this_player();
    object to = this_object();

    if (to->is_steed())
    {
      return water_animal(arg);
    }
    if(!arg)
    {
        return notify_fail("Drink water from what?\n");
    }

    if(arg == "water")
    {
        return notify_fail("Drink water from the river?\n");
    }

    if(parse_command(arg, this_object(),
        "[the] 'water' 'from' / 'at' [the] 'river'"))
    {
        if(!tp->drink_soft(tp->drink_max() / 20))
        {
            write("You cup your hands under the water, but you are " +
                "too full to drink any more!\n");
            say("Water overflows from " + QTNAME(tp) +
                "'s cupped hands.\n");
            tp->drink_soft(tp->drink_max() - tp->query_soaked());
        } else {
            write("You cup your hands in the river and drink " +
                "of the ice cold mountain water.\n");
            say(QCTNAME(tp) + " cups " + tp->query_possessive() +
                " hands in the river and drinks the water.\n");
        }

        return 1;
    }
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
        animal->short() + " to the river and waters " +
        animal->query_objective() + ".\n");
    write("You lead your " + animal->short() +
        " to the river and water " + animal->query_objective() +
        ".\n");

    amount = animal->drink_max() / 20;

    for(i=0; i<20; i++)
    {
        animal->drink_soft(amount);
    }

    animal->drink_soft(animal->drink_max() - animal->query_soaked());
    return 1;
}
