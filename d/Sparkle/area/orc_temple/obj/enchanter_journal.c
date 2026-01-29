/*
 *  /d/Sparkle/area/orc_temple/obj/enchanter_journal.c
 *
 *  This is the Karkadelt's personal journal that he keeps in his bed
 *  chambers.
 *
 *  Created February 2011, by Cooper Sherry (Gorboth)
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
    set_journal_name("diary");
    add_name(DIARY_ID);
    set_journal_adj("small");
    set_journal_desc("This diary rests on the dresser beside the bed.");
    set_journal_path(TEXT_DIR + "enchanter_journal/");
    set_entry_word(1);
    set_no_show_composite(1);

    add_item( ({ "dresser" }),
        "The dresser sits near to the bed. A small diary rests upon"
      + " it.\n");

    add_prop(OBJ_M_NO_GET, "As your hands move to take the diary, they"
      + " seem to slow down the closer they get, until they have frozen"
      + " in place. It appears this object is enchanted such that it"
      + " cannot be stolen by the likes of you. You might be able to"
      + " <read> it, however.\n");

    setuid();
    seteuid(getuid());
} /* create_journal */
