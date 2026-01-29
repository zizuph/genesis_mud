/*
 * woodpecker.c
 *
 * Used in wild/f3.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/monster";

#include <stdproperties.h>
#include <macros.h>

void gract();
void tenk(object tp);

void
create_monster()
{
    set_name("woodpecker");
    add_name("bird");
    add_name("hacke");

    set_race_name("woodpecker");
    set_gender(2);
    set_short("woodpecker");
    set_long("This is the woodpecker that lives in the hut on the tree. " +
             "It looks like it is very wise.\n");
    default_config_npc(50);

    add_prop(OBJ_I_NO_ATTACK, "The woodpecker flies too high up.\n");
    add_prop(OBJ_I_NO_MAGIC_ATTACK,
             "A forcefield protects the woodpecker.\n");

    add_ask(({"blue dragon", "dragon"}),
            "Woodpecker says: I've heard that the dragon was a wizard before.\n");
    add_ask("wizard", "Woodpecker says: Refnas zapped a wand at him.\n");
    add_ask("wand", "Woodpecker says: Wands are usually zapped.\n");
    add_ask("ogion", "Woodpecker says: Ogion lives in the forest.\n");
    add_ask("jhonlee",
            "Woodpecker says: Jhonlee meditates beyond the Stairs to the Sky.\n");
    add_ask("healer",
            "Woodpecker says: Jhonlee meditates beyond the Stairs to the Sky.\n");

}

void
attack_object(object o)
{
    return;
}

void
init_living()
{
    add_action("grovel", "grovel");
    add_action("ask", "ask");
}

int
ask(string s)
{

    if (!(TP->query_prop(MQ4PROP)))
    {
        notify_fail("The woodpecker stares at you with disgust and asks you " +
                    "if you don't have better things to do than disturb him " +
                    "with unimportant matters.\n");
        return 0;
    }

    TP->catch_msg("You ask the woodpecker what should be done with the " +
                  "nasty warriors that roam the countryside.\n");
    command("ponder");
    set_alarm(5.0, 0.0, &tenk(TP));
    return 1;
}

void
tenk(object tp)
{
    tp->catch_msg("I think I have found the solution to your problems.\n\n" +
                  "The only thing to do is to find the long-lost Stick " +
                  "of Powerful Wood, and bring it to the Mayor so he can " +
                  "have it converted into a Wand of Destruction.\n" +
                  "Rumors say that it can be found on the volcano island\n" +
                  "Carisca, which is told to be somewhere south of Cadu.\n\n" +
                  "The ancient legend says that if you want to release the " +
                  "powers that hold the Stick you must go to places close to " +
                  "the four elements water, earth, fire and air.\n");
}

int
grovel()
{
    say(QCTNAME(TP) + " grovels in front of the woodpecker.\n");
    TP->catch_msg("You fall to the ground, groveling, as the bird peers " +
                  "intently at you.\n");
    set_alarm(4.0, 0.0, gract);
    TP->add_prop(MQ1PROP, 1);
    return 1;
}

void
gract()
{
    command("say All you frightened fools that come here to please me!");
    command("laugh");
}
