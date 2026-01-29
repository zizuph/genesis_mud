/*
 *  /d/Sparkle/area/orc_temple/obj/enchanter_codex.c
 *
 *  This is the Enchanter's Codex which players can read to understand
 *  how to craft enchantments in the Enchanter's Forge.
 *
 *  Created November 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit "/d/Sparkle/std/obj/journal";

#include <stdproperties.h>
#include "../defs.h"


/* prototypes */
public void        create_journal();


/*
 * Function name:        create_journal
 * Description  :        set up the object
 */
public void
create_journal()
{
    set_journal_name("codex");
    set_journal_adj("leather-bound");
    set_journal_desc("The codex stands atop a pedestal in the front of"
      + " the chamber.");
    set_journal_path(TEXT_DIR + "codex/");
    set_entry_word(0);

    set_no_show_composite(1);

    add_item( ({ "leather", "binding", "leather binding" }),
        "The leather of the binding has been stained a deep purple"
      + " colour.\n");
    add_item( ({ "pedestal" }),
        "The pedestal supports a leather-bound codex.\n");

    add_prop(OBJ_M_NO_GET, "As your hands move to take the codex, they"
      + " seem to slow down the closer they get, until they have frozen"
      + " in place. It appears this object is enchanted such that it"
      + " cannot be stolen by the likes of you.\n");

    setuid();
    seteuid(getuid());
} /* create_journal */
