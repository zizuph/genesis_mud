/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TP              this_player
#define TO              this_object

#define HP_TO_HEAL    25 + random(15)


/*
 * Mystic Incense
 *      A mystic who burns this in the holy thurible, and meditates upon
 *      the ancients, shall regenerate mana rapidly.
 * Cedric 3/93
 * Modified by Mortricia 960502
 */

string                  meditate_text;
int                     num_uses=0;

/*
 * Function: do_it(object to_be_affected)
 * Description: Called from the thurible, do_it() takes an object
 *  and performs the incense's function on those objects. In this
 *  case, heals the mana of the person meditating.
 * Arguments: to_be_affected - The living to be affected.
 * Returns: 1 if successful, else 0
 */
public int
do_it(object to_be_affected)
{
   object n = to_be_affected->query_piety();
    if (MEMBER(to_be_affected))
    {
   to_be_affected->heal_hp(3);
   to_be_affected->set_piety(n + 3);
        return 1;
    }
    return 0;
}

/*
 * Function:    query_meditate_text()
 * Description: returns the text the meditating player gets using this incense.
 */
public string
query_meditate_text()
{
    return meditate_text;
}

/*
 * Function:    set_uses
 * Description: How many uses is this incense good for?
 * Arguments:   uses - the number of uses.
 */
public void
set_uses(int uses)
{
    num_uses = uses;
    add_prop(OBJ_I_VALUE, 288);
}

/*
 * Function     query_uses
 * Decription:  obvious (see above)
 */
public int
query_uses()
{
    return num_uses;
}

/*
 * Function:    set_meditate_text(string the_text)
 * Description: sets the text the meditating player gets using this incense.
 */
public void
set_meditate_text(string the_text)
{
    meditate_text = the_text;
}

public void
create_object()
{
    set_name("incense");
   add_name("holy_incense");
    set_short("small amount of golden incense");
    set_pshort("small amounts of golden incense");
    add_adj(({"small", "golden"}));
   set_long("This small amount of incense, golden in color is " +
   "made from from sandalwood, myrrh and mystic herbs. Its scent fills you " +
  "with a sense of devotion, a spiritual desire for another world.\n");
    set_long("This small amount of incense, whitish in color and redolent "
    + "somehow with scents of knowledge and power, fascinates you with "
    + "its heady aroma.\n");
    set_meditate_text("You seat yourself and stare into the holy thurible. "
    + "Inhaling the incense, you gradually drift into a state of higher "
    + "consciousness. Eyes closed, you realize with a shock that you can "
    + "somehow see your surroundings...the incense dies, and you stand up "
    + "again, refreshed and purified.\n");
    set_uses(3);
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 25);
}
