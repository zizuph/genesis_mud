/*
 * Master for the whodunnit in Minas Tirith
 *
 * Password quest to the 5th gate
 *
 * Olorin, 11-jan-1995
 *
 * How does it work:
 *     A player asks Hunthor for a task.
 *     Hunthor calls set_murderer(player) in this master.
 *     All other objects should only call query_murderer() and
 *     query_murderer_name() to see if there has been a murder
 *     and who the murderer is.
 *
 *     Before Hunthor is asked for the task, no murder has been
 *     committed yet. If a second player asks for the task, the
 *     murderer is the same as for the first player.
 *
 */
#include <math.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/minas/quest/pw5_defs.h"

#define NO_OF_SUSPECTS	8
#define SUSPECT_SEED	27239071

#define NO_OF_HIDING	5
#define HIDING_SEED	44411171

int     murderer = -1,
        pw5_status = 0;		// is set when someone asks for the quest from Hunthor
object *suspects = allocate(NO_OF_SUSPECTS);

int
query_pw5_status()
{
    return pw5_status;
}

void
reset_pw5_status()
{
    pw5_status = 0;
    murderer = -1;
}

static varargs int
query_suspect(string name)
{
    if (murderer >= 0)
        return murderer;

    if (!strlen(name))
    {
        if (objectp(TP))
            name = TP->query_real_name();
        else
            return -1;
    }
    return NAME_TO_RANDOM(name, SUSPECT_SEED, NO_OF_SUSPECTS);
}

varargs int
query_hiding_place(string name)
{
    if (!strlen(name))
    {
        if (objectp(TP))
            name = TP->query_real_name();
        else
            return -1;
    }
    return NAME_TO_RANDOM(name, HIDING_SEED, NO_OF_HIDING);
}

varargs int
set_murderer(object detective)
{
    if (murderer >= 0)
        return murderer;

    if (!objectp(detective))
        detective = TP;

    if (!objectp(detective) || !interactive(detective))
        return -1;

    murderer = query_suspect(detective->query_real_name());
    pw5_status = 1;
    if (objectp(suspects[murderer]))
        suspects[murderer]->set_is_murderer();

    FIX_EUID

    MT_PW5_GIMILZOR_START->load_me();
    MT_PW5_GIMILZOR_START->start_investigation();

    return murderer;
}

int     query_murderer() { return murderer; }

object
query_murderer_obj()
{
    if (murderer < 0)
        return 0;

    return suspects[murderer];
}

string
query_murderer_name()
{
    if (murderer < 0)
        return 0;

    seteuid(getuid());
    MT_PW5_SUSPECT->load_me();
    return MT_PW5_SUSPECT->query_suspect_name(murderer);
}

int
add_suspect(int i, object ob)
{
    int     j;

    if ((i < 0) || (i >= sizeof(suspects)))
        return 0;
    if (objectp(suspects[i]))
        return 0;

    // remove other entries of this suspect
    for (j = 0; j < sizeof(suspects); j++)
    {
        if (suspects[j] == ob)
            suspects[j] = 0;
    }

    suspects[i] = ob;
    return 1;
}

object *
query_suspects()
{
    return suspects;
}

