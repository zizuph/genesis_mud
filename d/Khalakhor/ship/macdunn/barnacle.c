/* File:          /d/Khalakhor/ship/macdunn/barnacle.c
 * Creator:       Teth / Daniel Mosquin
 * Date:          September 27, 1997
 * Modifications: July 27, 1998 - bug repair caused by change in /std code. 
 * Purpose:       This object can be cloned in under_pier.c in this dir.
 *                It can be used as a spell component, or to make another
 *                spell component, a tooth, by biting it or chewing it.
 * Related Files: /d/Khalakhor/ship/macdunn/under_pier.c
 * Comments:
 */

#pragma save_binary
#pragma strict_types

inherit "/std/food";

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <language.h>
#include "/d/Khalakhor/sys/defs.h"

object tooth;

public void
create_food()
{
    set_name("barnacle");
    add_name(({"crustacean","invertebrate","seashell","shell"}));
    set_pname("barnacles");
    add_pname(({"crustaceans","invertebrates","seashells","shells"}));
    set_adj("gooseneck");
    add_adj("white");
    set_short("gooseneck barnacle");
    set_pshort("gooseneck barnacles");
    set_long("This is a gooseneck barnacle, of the genus Pollicipes. " +
      "It is white in colour, and has a long neck. A mushroom without " +
      "its cap winged out would look similar to this creature. " +
      "Barnacles attach themselves to hard surfaces in salt water " +
      "areas. It does not look edible.\n");
    set_amount(40);

    seteuid(getuid());
}

public void
special_effect(int amnt)
{

    write("CRACK! You feel an intense pain inside your mouth!\n");
    say("CRACK! Something breaks inside " + HIS + " mouth!\n");
    tooth = clone_object("/std/leftover");
    tooth->leftover_init("tooth",(TP->query_race_name()));
    tooth->set_heap_size(amnt);
    tooth->move(TP, 1);
    TP->heal_hp(amnt * -20); /* Not going to call do_die(). It is
				messy with the way food is coded,
				and it seems silly to have someone
				die from a barnacle they ate, too. */
}
