/*
 * can.c
 *
 * Used in npc/kato.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* A can of paint
* With big help from
* Napture and Gresolle
* Joshua 19950114
*
* Updated: Jakob 950301
*/

#pragma save_binary
#pragma strict_types

inherit "std/object";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <language.h>
#include "defs.h"

int n;

void
create_object()
{
    n = 1;
    set_name("can");
    set_short("can of paint");
    set_long("This is a can of paint. There is some " +
             "black paint left in the can. \n");
    set_adj(({"painted", "black"}));

    add_prop(OBJ_I_VALUE, 293);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_WEIGHT, 750);
}

void
init()
{
    ::init();
    add_action("paint_me", "paint");
}

int
paint_me(string what)
{
    object dragobj;
    object *arr;
    string possesiv;

    notify_fail("Paint what? \n");
    if (!what)
        return 0;

    if (environment(TO) != TP)
    {
        notify_fail("But you have nothing to paint with!\n");
        return 0;
    }

    what = lower_case(what);
    sscanf(what, "%s black", what);  /* Remove `paint dragon black` */
    arr = FIND_STR_IN_OBJECT(what, environment(TP));
    if (!sizeof(arr))
        return 0;
    if (sizeof(arr) > 1)
    {
        notify_fail("You can only paint one thing at a time!\n");
        return 0;
    }

    dragobj = arr[0];

    if (n > 3)
    {
        notify_fail("Damn, There is no paint left...\n");
        TO->set_long("This is can of paint. " +
                     "There is no paint left in it.\n");
        return 0;
    }
    if (present("_the_paint_subloc", dragobj))
    {
        if (TP != dragobj)
            TP->catch_msg(QCTNAME(dragobj) + " is already painted black!\n");
        else
            TP->catch_msg("You are already painted black!\n");
        return 1;
    }

    seteuid(getuid());
    clone_object(ROKEDIR + "obj/paint_subloc")->move(dragobj);
    if (dragobj->id("kaheda_dragon_quest"))
    {
        n++;
        TP->catch_msg("You paint the lovely dragon black!\n");
        say(QCTNAME(TP) + " paints " + LANG_ADDART(dragobj->short ()) +
            "!!\n");
        if (!QDONE(ROKEGROUP, PAINTQUEST) && (TP->query_alignment() < 0))
        {
            seteuid(getuid());
            TP->catch_msg("You feel more experienced!\n");
            TP->add_exp(PAINTQUESTXP);
            QSET(ROKEGROUP, PAINTQUEST);
            QLOG("paint quest");
            return 1;
        }
    }
    else
    {
        n++;

        possesiv = TP->query_objective() + "self";

        if (TP != dragobj)
        {
            if (TP->query_met(dragobj))
                write("He he you paint " + dragobj->short () +
                      " black. Great fun!\n");
            else
                write("He he you paint the " + dragobj->query_race_name() +
                      " black. Great fun!\n");
        }
        else
            write("He he you paint yourself black. Great fun!\n");

        if (TP != dragobj)
        {
            say(QCTNAME(TP) + " paints " + QNAME(dragobj) + " black! \n",
                ({dragobj, TP}));
            dragobj->catch_msg(QCTNAME(TP) + " paints you black!\n");
        }
        else
        {
            say(QCTNAME(TP) + " paints " + possesiv + " black! \n");
        }
        return 1;
    }
    return 1;
}
