/*
  /d/Shire/common/obj/club/equestrian_shadow.c

  Shadow for Equestrian Society of Bree
  Palmer, January 2003

  Snarfed from:
  The shadow for Old Fogeys.

  Glaurung 8-97
 */

#pragma strict_types
#pragma binary_save

inherit "/std/shadow";

#include "/d/Shire/defs.h"

#define EQUESTRIAN_SHADOW ("/d/Shire/bree/rooms/town/stable/club/equestrian_shadow")
#define EQUESTRIAN_SOUL   ("/d/Shire/bree/rooms/town/stable/club/equestrian_soul")
#define CROP "/d/Shire/bree/rooms/town/stable/club/crop"

//** Prototypes **//
void add_soul(object o);
void remove_equestrian_shadow();


/*
 * function name : autoload_shadow
 * description   : called by the autoloading routine in /std/player_sec
 *                 to ensure autoloading of the shadow
 * arguments     : mixed arg - possible arguments
 */

public void
autoload_shadow(mixed arg)
{
    object crop;

    ::autoload_shadow(arg);

    /*
    // check for the right kind of members, kick them out if bad
    if (QSW->query_I_killed_a_steed)
    {
        write("Hey you're not an equestrian anymore!!\n");
        if (objectp(crop = present("_new_equestrian_crop", QSW)))
            crop->remove_object();

        QSW->remove_autoshadow(EQUESTRIAN_SHADOW+":");
        remove_equestrian_shadow();
    }
    */

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
    QSW->add_autoshadow(EQUESTRIAN_SHADOW+":");

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
    object crop;

    o->add_cmdsoul(EQUESTRIAN_SOUL);
    o->update_hooks();

    // do we have our crop?
    if (!objectp(crop = present("_equestrian_crop", QSW)))
    {
        setuid(); seteuid(getuid());
        crop = clone_object(CROP);
        crop->move(QSW, 1);
        o->catch_msg("You get a "+crop->short()+".\n");
    }
}


/*
 * function name : remove_equestrian_shadow
 * description   : removes this shadow
 */

void
remove_equestrian_shadow()
{
    ::remove_shadow();
}
