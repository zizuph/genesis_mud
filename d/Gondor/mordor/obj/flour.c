/*
 * /d/Gondor/mordor/obj/flour.c
 *
 * This is flour. You find it in the 'kitchen' of the orcs at the tower at
 * Cirith Ungol. If you throw it at someone, you will distract him from hitting
 * you for a little time, giving you the advantage of hitting him without
 * being hit yourself.
 *
 * Unfortunately there is no support for a heap-object that isn't countable, so
 * you have to redefine a lot of functions to get the desired result. :-(
 *
 * /Mercade, 27 September 1993
 *
 * Revision history:
 */

/*
 * I will have to see whether it completely works without 'counting' and if
 * not, I will have to recode it, using /std/object and doing it myself.
 * There is no check yet to max the number of 'hands ful' in a player.
 */

inherit "/std/heap" heap_file;

#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <ss_types.h>
#include "/d/Gondor/defs.h"

#define FLOUR_UNIQUE_ID   "_unique_orc_flour_"
#define FLOUR_EFFECT      MORDOR_DIR + "obj/flour_effect"
#define TOTAL_SNEEZE_TIME 40

void
create_heap()
{
    set_name("flour");
    set_pname("flour");
    add_name("pouch");
    add_pname("pouch");
    set_adj("some");
    add_adj("grey");

    set_heap_size(1);

    add_prop(HEAP_S_UNIQUE_ID,   FLOUR_UNIQUE_ID);
    add_prop(HEAP_I_UNIT_WEIGHT, 50);
    add_prop(HEAP_I_UNIT_VOLUME, 50);
    add_prop(HEAP_I_UNIT_VALUE,  0);
    add_prop(OBJ_S_WIZINFO,
        BSN("This is flour, an uncounable heap object that offers the " +
        "bearer a nice feature. If you throw (a handful) of flour at an " +
        "opponent, he will be unable to hit anything for some time. The " +
        "total time is dependant on your dex and the dex of your opponent."));
}

/*
 * In this function init() the call to ::init() is deliberately omitted for I
 * do not want the "count" command that is defined in /std/heap to be added
 * to the player. Furthermore, there are no important calls in ::init() at all.
 */
void
init()
{
    add_action("do_throw", "throw");
}

/*
 * Same short for plural and singular. Unfortunately the adjective 'a' will
 * always be added so I cannot call it "some flour".
 */
varargs string
short()
{
    return "some grey flour";
}

/*
 * The long description is also always the same.
 */
varargs string
long()
{
    return BSN("It is a pouch with some grey flour in it, found in the " +
        "kitchen or what it passes for of the orcs that live at Cirith " +
        "Ungol. It doesn't look like it is suitable for consumption. You " +
        "might consider throwing it at an attacker to distract him from " +
        "molesting you for a moment.");
}

/*
 * Tell all people in the room about the throwing.
 */
tell_spectators(object tp, object victim)
{
    object *inventory = all_inventory(environment(tp));
    int i;
    string str;

    for (i = 0; i < sizeof(inventory); i++)
    {
        if ((inventory[i] != tp) && (inventory[i] != victim) &&
            (living(inventory[i])))
        {
            str = tp->query_The_name(inventory[i]) + " grabs at " +
                POSSESSIVE(tp) + "pouch with flour and gets and handful of " +
                "it. They " + PRONOUN(tp) + "throws it at " +
                victim->query_the_name(inventory[i]) + "'s face.";
            if (num_heap() <= 1)
            {
                inventory[i]->catch_msg(BSN(str + " As " + PRONOUN(TP) +
                    " discovers that " + POSSESSIVE(tp) + " pouch is " +
                    "empty now, " + PRONOUN(tp) + " throws it away."));
            }
            else
            {
                inventory[i]->catch_msg(BSN(str));
            }
        }
    }
}

/*
 * The parser to get the victim.. .Copied from the standard soul and slightly
 * adjusted to my needs.
 */
object
get_victim(string str)
{
    object *oblist, *tmplist;
    int    i;

    tmplist = ({});
    if (!CAN_SEE_IN_ROOM(this_player()))
        return 0;

    if (!parse_command(str, environment(this_player()),
            " [some] [grey] 'flour' [at] %l ", oblist))
        return 0;
 
    oblist = NORMAL_ACCESS(oblist, 0, 0);

    if (!sizeof(oblist))
        return 0;

    for (i = 0; i < sizeof(oblist); i++)
    {
        if (objectp(oblist[i]) && living(oblist[i]) &&
                (this_player() != oblist[i]) &&
                CAN_SEE(this_player(), oblist[i]))
            tmplist = tmplist + ({ oblist[i] });
    }

    return tmplist[0];
}

/*
 * Throw it at someone to distract him for a moment.
 */
int
do_throw(string str)
{
    object tp = TP;
    object victim;
    object cloud;
    string str1, str2;
    int sneeze_time;
    int vdex, pdex;

    if (!strlen(str))
    {
        NFN("Throw what?");
        return 0;
    }

    if (explode(str, " ")[0] == "pouch")
    {
        NFN("You don't have to throw the whole pouch, some flour will do.");
        return 0;
    }

    if (ENV(TO) != tp)
    {
        NFN("You will have to pick up the flour before you can throw it.");
        return 0;
    }

    victim = get_victim(str);

    if (!objectp(victim))
    {
        NFN("Throw what at whom?");
        return 0;
    }

    str1 = "You grab at your pouch with flour and get a handful of it. " +
        "Then you throw it at " + victim->query_the_name(tp) + "'s face.";
    str2 = " grabs at " + POSSESSIVE(tp) + " pouch with flour and gets " +
        "a handful of it. Then " + PRONOUN(tp) + " throws it at your face.";

    if (num_heap() <= 1)
    {
        write(BSN(str1 + " As you discover that the pouch is empty now, you " +
            "decide to throw it away."));
        victim->CATCH_MSG(str2 + " As " + PRONOUN(tp) + " discovers that " +
            POSSESSIVE(tp) + " pouch is empty now, " + PRONOUN(tp) +
            " decides to throw it away.", tp);
        set_alarm(1.0, 0.0, "remove_object");
    }
    else
    {
        write(BSN(str1));
        victim->CATCH_MSG(str2, tp);
        item_count--; /* reduce the number of "flours" by one. */
    }

    tell_spectators(tp, victim);

    vdex = victim->query_stat(SS_DEX);
    pdex = victim->query_stat(SS_DEX);
    sneeze_time = (((TOTAL_SNEEZE_TIME + random(TOTAL_SNEEZE_TIME / 2)) *
        ((vdex > pdex) ? pdex : vdex)) / vdex);

    seteuid(getuid(this_object()));
    cloud = clone_object(FLOUR_EFFECT);
    cloud->move(victim, 1);
    cloud->start_the_sneeze(sneeze_time);    

    return 1;
}

/*
 * Direct call to /std/object
 */
/*
 * This function is currently out of order for multiple inheritance doesn't
 * seem to work properly.
 */
public void
appraise_object(int num)
{
/*    ::::appraise_object(num);*/
}

/*
 * Recovery stuff
 */
string
query_recover()
{
    return MASTER + ":#num_heap#" + num_heap() + "#";
}

void
init_recover(string arg)
{
    string foobar;

    sscanf(arg, "%s#num_heap#%d#%s", foobar, item_count, foobar);
}
