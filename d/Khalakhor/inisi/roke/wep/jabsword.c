/*
 * jabsword.c
 *
 * Used in wild/c5.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 * ::did_hit, Cotillion 2005
 */

#pragma save_binary
#pragma strict_types

/* gresolle -92 */

inherit "/std/weapon";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "defs.h"

/* a sword, effective only against Jabberwocks. It's made of glass and
   breaks against others :) */

#define HEAD (ROKEDIR + "obj/jabhead")

void
create_weapon()
{
    set_short("vorpal sword");
    set_adj("vorpal");
    set_name("sword");
    set_long("Strange... It seems to be made of glass.\n");
/*
    set_long("Strange... It seems to be made of glass. There is a\n" +
             "small picture of a Jabberwock on the handle.\n");
*/

    set_hit(10);
    set_pen(10);

    set_wt(W_SWORD);
    set_dt(W_SLASH | W_BLUDGEON);
    set_hands(W_BOTH);

    set_wf(this_object());
    add_prop(MAGIC_AM_MAGIC, ({38, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO, 
             ({"It has an aura of enchantment.", 10,
               "You think it might be used against only special creatures.", 25,
               "It's a Sword of Slay Jabberwock.", 50}));
    add_prop(OBJ_S_WIZINFO,
             "This sword is effective only against a jabberwock.\n" +
             "It gives 700+random(700) hp damage. If you use it against other\n" +
             "monsters it will break sooner or later. It's made of glass :)\n" +
             "If you have killed the jabberwock with it once, you can't wield\n" +
             "the sword anymore. (QUEST!!!)\n");
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
}

void
init()
{
    ::init();

    add_action("kill", "kill");
}

void
restore_prop(object tp)
{
    tp->remove_prop(NPC_I_NO_FEAR);
}

/* Help the player to dare attack the jabberwock. */
int
kill(string s)
{
    if (s != "jabberwock")
        return 0;

    /* Must wield this sword */
    if (query_wielded() != this_player())
        return 0;

    /* Normally 50 is needed, we only demand 35 */
    if (this_player()->query_stat(SS_DIS) < 35)
        return 0;

    this_player()->add_prop(NPC_I_NO_FEAR, 1);
    
    set_alarm(1.0, 0.0, &restore_prop(this_player()));
    return 0;
}

mixed
wield(object o)
{
    if (o != this_object())
        return 0;

    if (QDONE(ROKEGROUP, JABBERWOCK))
        return "The sword slips out of your hands when you try to wield it.\n";

    write("As you wield the vorpal sword, you feel a strong magic force within it.\n");
    return 1;
}

mixed
unwield(object o)
{
    if (o != this_object())
        return 0;

    write("You unwield the vorpal sword and feel the magic disappear.\n");
    return 1;
}

int
try_hit(object t)
{
    if (t->query_race_name() == "jabberwock")
    {
        wielder->catch_msg("The vorpal sword says 'Snicker-Snack'.\n");
        tell_room(environment(wielder), "You hear " + QTNAME(wielder) +
                  "'s vorpal sword going 'Snicker-Snack'.\n", wielder);
    }
    return 1;
}

varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit,
        int dam)
{
    object head;

    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    
    if (enemy->query_race_name() == "jabberwock")
    {
        wielder->catch_msg("You feel the sword tearing the jabberwock apart.\n");
        enemy->heal_hp(random(-700) - 700);
        tell_room(environment(wielder), 
                  QCTNAME(wielder) + " tears the jabberwock apart with " +
                  wielder->query_possessive() + " vorpal sword.\n",
                  wielder);

        if (enemy->query_hp() <= 0)
        {
            enemy->heal_hp(-10000);
            wielder->catch_msg("As the Jabberwock dies, the vorpal sword " +
                               "glows briefly, and suddenly it makes a " +
                               "move by itself, cutting off the head of " +
                               "the dying Jabberwock.\n");
            tell_room(environment(wielder),
                      QCTNAME(wielder) + 
                      " cuts off the Jabberwock's head.\n", wielder);
            enemy->do_die(wielder);
            seteuid(getuid(TO));

            head = clone_object(HEAD);
            head->move(ENV(wielder));
            remove_object();
        }

        return 0;
    }

    TP->catch_msg("You notice that hitting a " +
                  capitalize(enemy->query_race_name()) +
                  " with your vorpal sword causes severe damage to it.\n" +
                  "It's made of glass, you know.\n");
    set_likely_break(query_likely_break() + 1);
    set_dull(query_dull() + 1);
    return 0;
}

void
remove_object()
{
    environment()->catch_msg(
        "The vorpal sword melts away, leving nothing behind.\n");
    ::remove_object();
}
