/*
  /d/Shire/common/obj/club/huntsclub/huntsclub_shadow.c

  Taken from the:  Shadow for Equestrian Society of Bree
  Tomas, November 2017
  
  Stolen for the Allies of Rohan club
  Raymundo, Summer 2021
*/

#pragma strict_types
#pragma binary_save

inherit "/std/shadow";

#include "/d/Gondor/defs.h"
#include "ally_rohan.h"
#include "macros.h"

//** Prototypes **//
void add_soul(object o);
void remove_ally_shadow();


/*
 * function name : autoload_shadow
 * description   : called by the autoloading routine in /std/player_sec
 *                 to ensure autoloading of the shadow
 * arguments     : mixed arg - possible arguments
 */

public void
autoload_shadow(mixed arg)
{
    
   
    ::autoload_shadow(arg);


    // add the soul to members
    set_alarm(0.0, 0.0, &add_soul(query_shadow_who()));
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
    query_shadow_who()->add_autoshadow(ALLY_SOUL);

    // add the soul to player
   set_alarm(0.0, 0.0, &add_soul(query_shadow_who()));
}

/*
 * function name : add_soul
 * description   : adds the club cmdsoul to the player
 * arguments     : object o - the player to add the soul to
 */

void
add_soul(object o)
{
     object signet;

    o->add_cmdsoul(ALLY_SOUL);
    o->update_hooks();
    o->catch_msg("Shadow Loaded!\n");
    // do we have our signet? _rohan_signet
    if (!objectp(signet = present("_rohan_signet_", o)))
    {
        setuid(); seteuid(getuid());
        signet = clone_object(SIGNET);
        signet->move(o, 1);
        o->catch_msg("You get a "+signet->short()+".\n");
    }
}

void
remove_ally_shadow()
{
    ::remove_shadow();

}
