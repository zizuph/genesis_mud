/*
 * Child's Bedroom Closet in the vampire manor
 * Louie 2006
 */
#pragma strict_types
#include "defs.h"

inherit VAMP_ROOM_DIR + "vamp_room";

#include <stdproperties.h>
//proto
int do_feel(string str);
void do_dream_1(object tp);
void do_dream_2(object tp);
void do_dream_3(object tp);
void do_dream_4(object tp);
void do_dream_5(object tp);
void do_dream_6(object tp);

void create_vamp_room()
{
    set_short("closet");
    set_long("This is the bedroom closet.  It is simply a "+
        "small square room.  Anything that existed in this room "+
        "has long since been removed, leaving only bare stone walls.  "+
        "The bedroom is to the west.  "+
        "\n");

    add_exit("childbedroom.c", "west");

    add_item(({"west","bedroom"}),
        "To the west is to the bedroom.\n");

    add_item(({"wall","walls","bare walls","bare wall"}),
        "The walls of the closet are completely bare, although "+
        "there is a large substance of some sort on the east "+
        "wall.  "+
        "\n");

    add_item(({"substance","east wall"}),
        "The substance is dark and very old, and " +
        "appears to be a mass of dried blood.  "+
        "It is in the shape of a wide arch and is quite thick, "+
        "creating a raised texture that could even be felt.  "+
        "\n");
}

void
init() {
    ::init();
    add_action(do_feel, "touch");
    add_action(do_feel, "feel");
}

int
do_feel(string str)
{
    if (!strlen(str)){
        notify_fail("Feel what?\n");
        return 0;
    }

    if (str != "substance" && str != "blood"
        && str != "large substance"
        && str != "the blood"
        && str != "mass of dried blood"
        && str != "texture"
        && str != "arch of blood"
        && str != "raised texture"
        && str != "texture of blood"
        && str != "shape")
    {
        notify_fail("Feel the blood?\n");
        return 0;
    }

    object tp = this_player();
    tp->catch_msg("You reach out and run a finger along the "+
        "mass of dried blood, feeling every little bump "+
        "and crevice of the arch.\n");
    say(QCTNAME(tp)+" reaches out and runs a finger along the "+
        "east wall.\n");

    set_alarm(2.5, 0.0, &do_dream_1(tp));
    return 1;
}

void
do_dream_1(object tp)
{
    if (!tp || !(interactive(tp)))
    {
        return;
    }

    tp->catch_msg("Suddenly a pain pierces your mind, and you "+
        "are aware of a dual consciousness; you know you are "+
        "viewing the past "+
        "as well as the present.\n\n");

    set_alarm(7.0, 0.0, &do_dream_2(tp));

}

void
do_dream_2(object tp)
{
    if (!tp || !(interactive(tp)))
    {
        return;
    }

    tp->catch_msg("You are viewing down upon the child's bedroom, "+
        "where a golden haired girl - you somehow know her name is "+
        "Isabella - is sleeping soundly.  "+
        "A dark shape glides into the room, a tall thin man with "+
        "long straight black hair, and skin the color of milk.  "+
        "He leans over the child, mouth agape and fangs glistening...  "+
        "\n\n");

    set_alarm(12.0, 0.0, &do_dream_3(tp));

}
void
do_dream_3(object tp)
{
    if (!tp || !(interactive(tp)))
    {
        return;
    }

    tp->catch_msg("With a roar an enormous red-bearded man (his name "+
        "is Bear, you realize) charges into the room and smashes "+
        "the thin man into the wall.  "+
        "Isabella wakes and screams, and immediately runs to "+
        "the closet.  "+
        "The thin man and Bear struggle momentarily, locked in mortal "+
        "combat...  "+
        "\n\n");

    set_alarm(13.0, 0.0, &do_dream_4(tp));

}

void
do_dream_4(object tp)
{
    if (!tp || !(interactive(tp)))
    {
        return;
    }

    tp->catch_msg("Isabella cowers in the closet, watching in horror "+
        "as the thin man lifts Bear and slams him into the bed, "+
        "shattering the thick wood of its base.  "+
        "The thin man picks Bear up with one hand, and with the other "+
        "slices his long glass talons across Bear's throat.  "+
        "Blood sprays in an arc through the air, covering the eastern "+
        "wall of the closet...  "+
        "\n\n");

    set_alarm(15.0, 0.0, &do_dream_5(tp));

}

void
do_dream_5(object tp)
{
    if (!tp || !(interactive(tp)))
    {
        return;
    }

    tp->catch_msg("Isabella screams and runs from the room, down the hall, "+
        "and to the northern balcony.  "+
        "The thin man walks behind her, blood dripping from his right "+
        "hand and mouth.  "+
        "Isabella looks down briefly at the sheer cliff face to the water "+
        "below and whispers \"Please let me fly, please let me fly\".  "+
        "Without a sound, she leaps from the balcony into the darkness.  "+
        "\n\n");

    set_alarm(6.0, 0.0, &do_dream_6(tp));

}

void
do_dream_6(object tp)
{
    if (!tp || !(interactive(tp)))
    {
        return;
    }

    tp->catch_msg("The visions fade from your mind.  "+
        "\n");
}

/*
You are viewing down upon the child's bedroom, where a golden haired
girl - you somehow know her name is Isabella - is sleeping soundly.  
A dark shape glides into the room, a tall thin man with long straight
black hair, and skin the color of milk.  He leans over the child, mouth
agape and fangs glistening...

With a roar an enormous red-bearded man (his name is Bear, you realize)
charges into the room and smashes the thin man into the wall.  Isabella
wakes and screams, and immediately runs to the closet.  The thin man
and Bear struggle momentarily, locked in mortal combat...

Isabella cowers in the closet, watching in horror as the thin man lifts
Bear and slams him into the bed, shattering the thick wood of its base.
The thin man picks Bear up with one hand, and with the other slices his
long glass talons across Bear's throat.  Blood sprays in an arc through
the air, covering the eastern wall of the closet...

Isabella screams and runs from the room, down the hall, 
and to the northern balcony.  The thin
man walks behind her, blood dripping from his right hand and mouth.
Isabella looks down briefly at the sheer cliff face to the water
below and whispers 'Please let me fly, please let me fly'.  Without
a sound, she leaps from the balcony into the darkness.

The visions fade from your mind.

*/