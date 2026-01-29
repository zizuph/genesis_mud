/*
 * grimoire.c
 *
 * Used in nyreese/cas_c7.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object.c";

#include "defs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

void explodeall();
void warning(object tp);

/* Motorhead -92  This is the evil wizard Refnas ancient grimoire
 * Couldn't you have made it right the first time?
 * Changed several times by multiple wizards and Arches.
 *
 * Last changed by Lord Ged and so mote it be !!!
 * Ha ha Gresolle poked in it a little too... *grin*
 * actually, gresolle added an enter_inv, leave_inv to take care
 * of teleporting and such things.
 *
 * Seems like we had to change the grimoire a little bit more.
 * The grimoire got its powers from the evil wizard Refnas
 * If the grimoire is too far away from Refnas it will loose all its powers
 * It will also loose its powers if it is teleported because the magic
 * spell cast upon the book can't survive teleportations.
 *
 * If any Arch or reviewer has a problem with this please send us
 * (Ged, Gresolle and Glindor) a mail with a better idea.
 *
 * The story goes on... Gresolle is working on some kind of ranged
 * effect. Must admit that I liked it best in its first version though.
 *
 * /Lord Ged 930707
 */

/*  A bomb shouldn't be recoverable....
    /Lord Ged 930707

query_recover()
{
  return MASTER;
}
*/

object current_env;
mixed oldprop;

string
wizardstuff()
{
    if (!this_player()->query_wiz_level())
        return "";

    return
        "Since you are a wizard, you immediately recognize the language " +
        "the grimoire is written in, and after a while you decide that it " +
        "must be a Swedish Songbook. It is filled with awful songs which " +
        "were written by some of the most evil Swedish authors, " +
        "to terrorize the Swedish schoolchildren and destroy their " +
        "youth. Fortunately Refnas has cast a spell upon it to " +
        "make it self-destruct when someone tries to read it. " +
        "Surprisingly enough, the damage made by the explosion " +
        "is far less than the songs would do.\n";
}

string
mylong()
{
    return
        "This is what you think is Refnas personal grimoire. You see " +
        "several texts written in a strange language. You reckon it must " +
        "be Refnas' evil spells and formulae. They are the fruits of " +
        "centuries of hard work.\n" +
        wizardstuff();
}

void
create_object()
{
    set_short("ancient grimoire");
    set_long("@@mylong");

    set_adj("ancient");
    set_name("grimoire");
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_name("book");
    add_name("refnasgrim");
    add_prop(OBJ_M_NO_TELEPORT, 1);
    add_prop(OBJ_S_WIZINFO, "This grimoire will explode of you examine it. " +
             "It wont hurt Npcs and you cant bring it out of the domain.\n");
}

void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    if (interactive(dest))
    {
        if (!oldprop)
            oldprop = dest->query_prop(OBJ_I_NO_TELEPORT);
        dest->add_prop(OBJ_I_NO_TELEPORT, VBFC_ME("steals"));
    }
    current_env = dest;
}

object
find_holder(object apa)
{
    while (apa && !interactive(apa))
        apa = environment(apa);
    return apa;
}

void
leave_env(object a, object b)
{
    ::leave_env(a, b);

    if (!find_holder(current_env))
    {
        a->add_prop(OBJ_I_NO_TELEPORT, oldprop);
        oldprop = 0;
    }
}

int
steals()
{
    object ob;
    if (!(ob = find_holder(current_env)))
        return 0;

    if (ob == TP)
        return 1;
    else
        return 0;
}

string
long(mixed s)
{
    add_prop(OBJ_I_NO_DROP,
             "The grimoire seems to be stuck on your fingers.\n");
    add_prop(OBJ_I_NO_GIVE, "That is not a very nice thing to do.\n");
    set_alarm(25.0, 0.0, explodeall);
    set_alarm(1.0, 0.0, &warning(TP));
    return ::long(s);
}

int
check_living(object obj)
{
    if (living(obj))
        return 1;
    return 0;
}

void
explodeall()
{
    object *objs, room;
    int i;

    room = TO;
    while (!(room = ENV(room))->query_prop(ROOM_I_IS)) ;

    tell_room(room, "The grimoire disintegrates in a huge ball of fire!!\n" +
              "You are severely burnt!\n");

    objs = all_inventory(room);
    objs = filter(objs, &check_living());

    for (i = 0; i < sizeof(objs); i++)
    {
        if (objs[i]->query_npc())
            break;

        objs[i]->heal_hp(-(objs[i]->query_hp() / 5));
        if (objs[i]->query_hp() <= 0)
            objs[i]->do_die(TO);
    }

    remove_object();
}

void
warning(object tp)
{
    if (tp->query_skill(SS_AWARENESS) >= 15)
    {
        tp->catch_msg("You shouldn't have looked in the grimoire...\n" +
                      "It doesn't like to be handled by anyone else than " +
                      "Refnas. It will probably explode any minute!!!\n");
    }
}
