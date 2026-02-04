/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/* 
 * angelicus.c
 */

#include <ss_types.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <macros.h>
#include "spells.h"

/* 
 * Function name: angelicus
 * Description:   summons an angelic spirit to do casters bidding
 */
nomask mixed
angelicus()
{
    object angel, ob;

    if (this_player()->query_stat(SS_WIS) < ANGELICUS_MIN_WIS)
   return "You are not of high enough stature to attempt this yet.\n";

    if (this_player()->query_mana() < ANGELICUS_MANA_COST)
   return "You do not have the strength.\n";

  ob = present("incense", this_player());
  if(!ob) return "You will need some incense.\n";
    this_player()->add_mana(-ANGELICUS_MANA_COST);

    if (random(this_player()->query_skill(SS_FORM_CONJURATION) +
        this_player()->query_skill(SS_ELEMENT_LIFE)) < random(ANGELICUS_CAST_LIMIT))
    {
        write("Your call of summons to the heavens has failed.\n");
        return 1;
    }

    write("You kneel upon the ground and invoke the heavenly choirs.\n");
    say(QCTNAME(this_player()) + " kneels upon the ground and sings out.\n");
    tell_room(environment(this_player()),
    "A light appears from above, from which a winged spirit descends.\n" +
    "The angelic spirit says: Hail " + QCTNAME(this_player()) + "\n");

    seteuid(getuid(this_object()));

    angel = clone_object(SPELL_DIR + "angel");
    angel->set_duration(DURATION(this_player()->query_stat(SS_INT),
        this_player()->query_skill(SS_SPELLCRAFT),
        ANGELICUS_MIN_DURATION));

    angel->add_prop("owner", this_player()->query_name());
    angel->move_living("M", environment(this_player()));
    ob->remove_object();

    return 1;
}
