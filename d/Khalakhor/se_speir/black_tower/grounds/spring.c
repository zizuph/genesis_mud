/*
 * spring
 *
 * This room is the location of the black spring behind
 * the black tower.
 * As the spring may be purified during one of the quests
 * contained in the area, we set up the room to time the
 * duration of the purification (it lasts only a few
 * minutes). We do this simply by an alarm to 'unpurify'
 * the pool, but in order to make the descriptions
 * look right, we'll also record the time of purification
 * so we can adjust the pool description as it gradually
 * goes from black to clear and back again during those
 * few minutes. It takes 1 minute to clear, stays
 * completely pure for 2 minutes, then begins to 
 * become poison again over the following 3 minutes.
 *
 * Khail - July 7/97
 */
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <time.h>
#include "grounds.h"
#include "/d/Khalakhor/sys/defs.h"

#define HEALING 500
#define MANA    50
inherit STDGROUNDS;

int purified;

public void
taint_again()
{
    if (!purified)
        return;

    purified = 0;
    tell_room(TO, "The water from the spring is now " +
        "a pure black again.\n");
}

public void
set_purified()
{
    if (purified)
        return;

    purified = time();
    tell_room(TO, "The water from the spring is now " +
        "crystal clear and as cold as ice!\n");
    set_alarm(180.0, 0.0, taint_again);
}

public int
query_purified()
{
    return purified;
}

public string
query_time_left()
{
    return CONVTIME(360 - (time() - purified));
}
    
public string
water_long()
{
    int index;

    index = time() - purified;

    if (index <= 180)
        return "cold, clear";
    return "thick, black";
}
    
public string
exa_pool()
{
    int index;
    string desc;

    index = time() - purified;

    switch (index)
    {
        case 0..30:    /* Purified up to 30 sec ago */
            desc = "The water of the pool is a murky " +
                "black, but the clear water that is now " +
                "pouring in from the spring is slowly " +
                "clearing it.\n";
            break;
        case 31..60:   /* Purified between 31 & 60 secs. ago */
            desc = "The water of the pool has been " +
                "almost completely purified, only a " +
                "few tendrils of blackness remain " +
                "within.\n";
            break;
        case 61..180:  /* Water clear from 1 to 3 minutes. */
            desc = "The pool of water is as clear as " +
                "crystal and as cold as ice.\n";
            break;
        case 181..240:
            desc = "The black water from the spring is " +
                "beginning to taint the clear water " +
                "in the pool again.\n";
            break;
        case 241..300:
            desc = "The water in the pool is almost " +
                "as completely black again, only a few " +
                "traces of clear water remain around " +
                "the edges.\n";
            break;
        default:
            desc = "The water within the pool is as " +
                "black as coal, and smells nowhere " +
                "near as coal. Thinking the water " +
                "to be only mildly poisonous would " +
                "be over-optimistic, juding from " +
                "appearance.\n";
    }
    return desc;
}

public string
exa_spring()
{
    int index;
    string desc;

    index = time() - purified;

    switch (index)
    {
        case 0..180:    
            desc = "Water, as clear as crystal and " +
                "as cold as ice, bubbles up through "+
                "the spring.\n";
            break;
        default:
            desc = "The water coming up out of the " +
                "spring looks like very thin oil, " +
                "it smells terrible and is completely " +
                "black without even a hint of " +
                "transparancy.\n";
    }
    return desc;
}

public void
create_khalakhor_room()
{
    set_short("beside a black spring");
    set_long("You've arrived at the end of the grounds " +
        "around the far side of the tower. Here, a " +
        "spring trickles " + VBFC_ME("water_long") +
        " water from the ground to form a pool amidst " +
        "a grove of dead oak trees. The reflection of " +
        "the towers shifts eerily upon the surface of " +
        "the water, as if trying to escape from " +
        "beneath it.\n");

    add_item(({"pool"}), VBFC_ME("exa_pool"));
    add_item(({"spring", "water"}),
        VBFC_ME("exa_spring"));

    create_add_items();
    add_exit(GROUNDS + "grounds_12", "north");
}

public int
do_drink(string str)
{
    int index;
    object poison;

    index = time() - purified;

    if (!str || !strlen(str))
        return 0;

    if (str == "water")
    {
        write("Drink water from where, the spring or the pool?\n");
        return 1;
    }

    if (parse_command(str, TP, "[water] 'from' [the] 'spring'"))
    {
        if (index > 180)
        {
            write("You take a cautious sip of the black " +
                "water coming from the spring and " +
                "immediately regret it!\n");
            say(QCTNAME(TP) + " takes a cautious sip of the " +
                "black water coming from the spring and a " +
                "look of horror crosses " +
                HIS_HER(TP) + " face!\n");
            reset_euid();
            poison = clone_object(OBJ + "spring_poison");
            poison->full_strength();
            poison->move(TP, 1);
            return 1;
        }
        write("You take a healthy mouthful of the clear " +
            "water coming from the spring. You shiver " +
            "uncontrollably for a moment as the water is " +
            "so cold it takes your breath away, yet it " +
            "leaves a feeling of vigour in it's wake.\n");
        say(QCTNAME(TP) + " drinks a healthy mouthful of " +
            "the clear water coming from the spring.\n");
        TP->command("$shiver");
        TP->heal_hp(HEALING);
        TP->add_mana(MANA);
        return 1;
    }
    if (parse_command(str, TP, "[water] 'from' [the] 'pool'"))
    {
        if (index > 60 && index <= 180)
        {
            write("You take a healthy mouthful of the clear " +
                "water in the pool. You shiver " +
                "uncontrollably for a moment as the water is " +
                "so cold it takes your breath away, yet it " +
                "leaves a feeling of vigour in it's wake.\n");
            say(QCTNAME(TP) + " drinks a healthy mouthful of " +
                "the clear water in the pool.\n");
            TP->command("$shiver");
            TP->heal_hp(HEALING);
            TP->add_mana(MANA);
            return 1;
        }
        write("You take a cautious sip of the black " +
            "water in the pool and " +
            "immediately regret it!\n");
        say(QCTNAME(TP) + " takes a cautious sip of the " +
            "black water in the pool and a " +
            "look of horror crosses " +
            HIS_HER(TP) + " face!\n");
        reset_euid();
        poison = clone_object(OBJ + "spring_poison");
        if (index < 30)
            poison->full_strength();
        else if (index <= 60)
            poison->half_strength();
        else if (index < 240)
            poison->third_strength();
        else if (index < 300)
            poison->half_strength();
        else
            poison->full_strength();
        poison->move(TP, 1);
        return 1;
    }
    return 0;
}


public void
init()
{
    ::init();
    add_action(do_drink, "drink");
}