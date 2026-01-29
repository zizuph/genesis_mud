/*
 * spellp.c
 *
 * Used in carisca/x1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include "defs.h"
#include <macros.h>

string
query_recover()
{
    return MASTER;
}

void
create_object()
{
    set_short("old elf skeleton");
    set_name("skeleton");
    set_adj("old");
    add_adj("elf");
    add_name("elf");
    set_long("The skeleton looks as if it has been away from its owner for " +
             "a while.\n");
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_S_SEARCH_FUN, "lookforstuff");
}

string
lookforstuff(string s)
{
    object apa;

    seteuid(getuid(TO));

    if (QDONE(ROKEGROUP, SKELETON) && !present("sppapp", TP))
    {
        write("Strange... You find the paper you ate again.\n" +
              "It must be something special about it, if it " +
              "is able to find its way back to you like this.\n");

        apa = clone_object(ROKEDIR + "obj/spellpaper");
        apa->transform_me();
        apa->move(TP);
        return " ";
    }

    if (!QDONE(ROKEGROUP, SKELETON))
    {
        write("As you search the skeleton it crumbles to dust and " +
              "you find an old paper.\n");
        clone_object(ROKEDIR + "obj/spellpaper")->move(TP);
        say(QCTNAME(TP) + " finds something in the skeleton.\n");

        write("You have performed well!\nYou feel more experienced!\n");
        TP->add_exp(SKELETONXP);

        QSET(ROKEGROUP, SKELETON);
        QLOG("skeletonquest");

        remove_object();
        return " ";
    }
    return 0;
}
