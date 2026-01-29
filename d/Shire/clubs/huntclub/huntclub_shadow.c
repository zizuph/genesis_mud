/*
  /d/Shire/common/obj/club/huntsclub/huntsclub_shadow.c

  Taken from the:  Shadow for Equestrian Society of Bree
  Tomas, November 2017
*/

#pragma strict_types
#pragma binary_save

inherit "/std/shadow";

#include "/d/Shire/sys/defs.h"
#include "huntclub.h"
#include "macros.h"

//** Prototypes **//
void add_soul(object o);
void remove_huntclub_shadow();

/*
 * function name : autoload_shadow
 * description   : called by the autoloading routine in /std/player_sec
 *                 to ensure autoloading of the shadow
 * arguments     : mixed arg - possible arguments
 */

public void
autoload_shadow(mixed arg)
{
    object tallystick;

    ::autoload_shadow(arg);


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
    QSW->add_autoshadow(HUNTCLUB_SHADOW+":");

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
    object tallystick;

    o->add_cmdsoul(HUNTCLUB_SOUL);
    o->update_hooks();
    
    // do we have our tallystick? _huntclub_tallystick_
    if (!objectp(tallystick = present("_huntclub_tallystick_", QSW)))
    {
        setuid(); seteuid(getuid());
        tallystick = clone_object(TALLYSTICK);
        tallystick->move(QSW, 1);
        o->catch_msg("You get a "+tallystick->short()+".\n");
    }
}


/*
 * Function name: notify_you_killed_me
 * Description  : This function is called in a living when they kill
 *                something. It has been masked to add to the hunter
 *                kill counter.
 * Arguments    : object killed - the killed living
 * Returns      : 1/0
 */
public int
notify_you_killed_me(object killed)
{
	setuid(); seteuid(getuid());
    HUNTCLUB_MANAGER_FILE->add_hunter_kills(shadow_who, killed);
    
    return shadow_who->notify_you_killed_me(killed);
    
} /* notify_you_killed_me */


/*
 * function name : remove_huntclub_shadow
 * description   : removes this shadow
 */

void
remove_huntclub_shadow()
{
    ::remove_shadow();

}
