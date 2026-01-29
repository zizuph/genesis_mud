/*
 * /d/Shire/common/obj/club/fogey_soul.c
 *
 * The shadow for Old Fogeys.
 *
 * Glaurung 8-97
 */

#pragma strict_types
#pragma binary_save

inherit "/std/shadow";

#include "/d/Shire/defs.h"

#define FOGEY_SHADOW ("/d/Shire/common/obj/club/fogey_shadow")
#define FOGEY_SOUL   ("/d/Shire/common/obj/club/fogey_soul")

//** Prototypes **//
void add_soul(object o);
void remove_fogey_shadow();


/*
 * function name : autoload_shadow
 * description   : called by the autoloading routine in /std/player_sec
 *                 to ensure autoloading of the shadow
 * arguments     : mixed arg - possible arguments
 */

public void
autoload_shadow(mixed arg)
{
    object cane;

    ::autoload_shadow(arg);

    // check for the right kind of members, kick them out if bad
    if (QSW->query_gender() != 0 || QSW->query_race() != "human" &&
        QSW->query_race() != "hobbit" && QSW->query_race() != "dwarf")
    {
        write("Hey you're not an old fogey anymore!!\n");
        if (objectp(cane = present("_new_fogey_cane", QSW)))
            cane->remove_object();

        QSW->remove_autoshadow(FOGEY_SHADOW+":");
        remove_fogey_shadow();
    }

    // add the soul to members
    set_alarm(0.0, 0.0, &add_soul(QSW));
}


/*
 * function name : shadow_me
 * description   : called from object to make us shadow it
 * arguments     : mixed to_shadow - string or object. If it is a string
 *                 use find_player to find object to shadow
 * returns       : int - true if shadowed
 */

public varargs int
shadow_me(mixed to_shadow)
{
    ::shadow_me(to_shadow);

    // add autoshadow to player so this shadow will stick
    QSW->add_autoshadow(FOGEY_SHADOW+":");

    // add the soul to player
    set_alarm(0.0, 0.0, &add_soul(QSW));
}


/*
 * function name : add_soul
 * description   : adds the club cmdsoul to the player
 * arguments     : object o - the player to add the soul to
 */

void
add_soul(object o)
{
    object cane;

    o->add_cmdsoul(FOGEY_SOUL);
    o->update_hooks();

    // do we have our cane? Old Fogeys tend to misplace theirs ;)
    if (!objectp(cane = present("_new_fogey_cane", QSW)))
    {
        setuid(); seteuid(getuid());
        cane = clone_object("/d/Shire/common/obj/club/cane2");
        cane->move(QSW, 1);
        o->catch_msg("You get an "+cane->short()+".\n");
    }
}


/*
 * function name : remove_fogey_shadow
 * description   : removes this shadow
 */

void
remove_fogey_shadow()
{
    ::remove_shadow();
}
