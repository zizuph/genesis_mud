/*
 * h_scare_him.c
 *
 * Used in obj/h_crucifix.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/*  A small gift to all the nice vampires out there. */
/*  coded by Calonderiel 930906                      */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include "defs.h"

#define TIME 100.0
object owner;

void scare_1();
void scare_2();
void scare_3();
void scare_4();

void
create_object()
{
    set_name("crucifix");
    set_adj("holy");
    set_short("holy crucifix");
    set_long("This is an even more holy crucifix.\n");

    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_I_INVIS, 1);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_VALUE, 0);
}

void
saj(string str)
{
    tell_room(environment(owner), str, owner);
}

void
activate()
{
    set_alarm(TIME, 0.0, scare_1);
    owner = environment(TO);
}

void
scare_1()
{
    owner->catch_msg("Someone says : Dont think you can escape me, evil one!\n");
    saj(QCTNAME(owner) + " anxiously looks behind " +
        owner->query_possessive() +
        " back.\n");
    owner->add_prop(LIVE_S_SOULEXTRA, "desperate");
    owner->add_panic(250);
    set_alarm(TIME, 0.0, scare_2);
}

void
scare_2()
{
    owner->catch_msg("Someone says : I'll hunt you all the way to your lair," +
                     " damned one!\n");
    saj("As " + QCTNAME(owner) + " anxiously looks behind " +
        owner->query_possessive() + " back,\n" +
        owner->query_possessive() + " knees starts to wobble.\n");
    owner->add_prop(LIVE_S_SOULEXTRA, "wobbly-kneed with fright");
    owner->add_panic(250);
    set_alarm(TIME, 0.0, scare_3);
}

void
scare_3()
{
    owner->catch_msg("Someone says : Come dawn I'll seek you out, vampire!\n");
    saj("With a face suddenly gone grey with fright, " + QCTNAME(owner) +
        "\n" +
        "desperately looks behind " + owner->query_possessive() + " back.\n");
    owner->add_prop(LIVE_S_SOULEXTRA, "grey-faced with fright");
    owner->add_panic(250);
    set_alarm(TIME, 0.0, scare_4);
}

void
scare_4()
{
    owner->catch_msg("Someone says : I'll relish the moment when I drive" +
                     " my ash pole\n" +
                     "               through your black heart!\n" +
                     "Someone cackles gleefully.\n");
    saj(QCTNAME(owner) + " suddenly jumps high into the air.\n" +
        "As sweat breaks out on " + owner->query_possessive() +
        " forehead,\n" +
        owner->query_pronoun() + " starts to shake with fright.\n");
    owner->add_prop(LIVE_S_SOULEXTRA, "shaking with fright");
    owner->add_panic(250);
    set_alarm(1.0, 0.0, remove_object);
}
