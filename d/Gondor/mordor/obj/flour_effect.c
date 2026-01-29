/*
 * /d/Gondor/mordor/obj/flour_effect.c
 *
 * This is what is cloned into the player that got some flour thrown in the
 * fact. This object generates the messages itself, so wizards will also
 * sneeze :-)
 *
 * /Mercade, 27 September 1993
 *
 * Revision history:
 * Updated code and changed to use of add_attack_delay() - 06/06/96 - By Arren
 */

inherit "/std/object";

#include "/d/Gondor/defs.h"
#include <stdproperties.h>

#define TOTAL_SNEEZE_TIME    40
#define TIME_BETWEEN_SNEEZES  4.0 /* float */
#define MINIMAL_SNEEZE_TIME  20

/*
 * Global variable
 */
object victim; /* we wanna know who he is. */

/*
 * Create the object
 */
void
create_object()
{
    set_no_show();

    set_name("_flour_sneeze_");

    add_prop(OBJ_I_VOLUME,  0);
    add_prop(OBJ_I_WEIGHT,  0);
    add_prop(OBJ_I_VALUE,   0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);

    add_prop(OBJ_S_WIZINFO,
        BSN("This object will keep a player sneezing for some time. As long " +
        "as this object is active, the victim will not be able to hit for " +
        "his/her LIVE_I_ATTACK_DELAY property will be set."));
}

/*
 * Let the victim sneeze
 */
void
do_sneeze()
{
    int i = random(6);

    set_this_player(victim);

    switch(i)
    {
    case 0:
        write(BSN("Since your head is still in a cloud of flour, you " +
            "cough each time you try to breathe."));
        LSAY("Since ", "'s head is still in a cloud of flour, " + PRONOUN(TP) +
            " coughs each time " + PRONOUN(TP) + " tries to breathe.");
        victim->command("cough");
        break;
    case 1:
        write(BSN("WRAAH-CHOOO!!! You sneeze again."));
        say("WRAAH-CHOOO!!! "); /* to get a capical in the name */
        SAY(" sneezes again.");
        break;
    case 2:
        write(BSN("You sneeze one more time! Damned flour!"));
        SAY(" sneezes one more time! Damned flour!");
        break;
    case 3:
        write(BSN("Your lungs are rapidly filling with flour, making it " +
            "almost impossible for you to breathe."));
        SAY("'s lungs are rapidly filling with flour, making it almost " +
            "impossible for " + OBJECTIVE(TP) + " to breathe.");
        victim->command("choke");
        break;
    case 4:
        write(BSN("You sound like the cloud of flour around your head is " +
            "slowly diappearing, but is it indeed?"));
        SAY(" sounds like the cloud of flour around " + POSSESSIVE(TP) +
            " head is slowly disappearing, but is it indeed?");
        break;
    case 5:
    default:
        write(BSN("With all that sneezing you hope your nose will be " +
            "clear soon."));
        LSAY("With all that sneezing, ", " looks desparate.");
        break;
    }
}

/*
 * If the flower disappears, let the victim continue his attack.
 * - But what if victim is delayed by something else? /Arren
 *
void
remove_object()
{
    victim->remove_prop(LIVE_I_ATTACK_DELAY);

    ::remove_object();
}
 */

/*
 * Make you sneeze several times and update the LIVE_I_ATTACK_DELAY prop
 * - Removed that for use of add_attack_delay() instead. /Arren
 */
void
sneeze_again()
{
    /* Don't torture the already dead. */
    if (victim->query_ghost())
    {
        set_alarm(1.0, 0.0, remove_object);
        return;
    }

    do_sneeze();

    set_alarm(TIME_BETWEEN_SNEEZES, 0.0, sneeze_again);
}

void
first_sneeze()
{
    set_this_player(victim);

    write(BSN("The flour irritates your nostrils, forcing you to sneeze!"));
    LSAY("The flour irritates ", "'s nostrils, forcing " + OBJECTIVE(TP) +
        " to sneeze!");
    victim->command("sneeze");
}

void
stop_sneezing()
{
    set_this_player(victim);

    write(BSN("Finally, the last bit of flour left your nose and lungs and " +
        "you can breathe again."));
    LSAY("Finally the last bit of flour left ", "'s nose and lungs and " +
        PRONOUN(TP) + " can breathe again.");

    set_alarm(1.0, 0.0, remove_object);
}

/*
 * Init the sneezing when called from the flour
 */
varargs void
start_the_sneeze(int sneeze_time)
{
    victim = ENV(TO);

    if ((!objectp(victim)) || (!living(victim)))
    {
        return;
    }

    if (sneeze_time < MINIMAL_SNEEZE_TIME)
    {
        sneeze_time = (TOTAL_SNEEZE_TIME + random(TOTAL_SNEEZE_TIME / 2));
    }

    set_alarm(2.0, 0.0, first_sneeze);
    victim->add_attack_delay(sneeze_time + 1, 1);
    set_alarm(itof(sneeze_time), 0.0, stop_sneezing);
    set_alarm((TIME_BETWEEN_SNEEZES + 2.0), 0.0, sneeze_again);
}
