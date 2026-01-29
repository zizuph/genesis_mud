/*
 *  /d/Sparkle/area/orc_temple/obj/priest_journal.c
 *
 *  This is the journal of the High Priest which players can find
 *  and read in his personal chambers. Reading the journal is
 *  required to complete one of the quests involved in the
 *  Sparkle Enchanter's saga.
 *
 *  Created November 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit "/d/Sparkle/std/obj/journal";

#include <stdproperties.h>
#include <time.h>
#include "../defs.h"


/* Definitions */
#define            JOURNAL_NOTIFY  "_imbue_journal_player_notified"

/* prototypes */
public void        create_journal();
public void        quest_entry();


/*
 * Function name:        create_journal
 * Description  :        set up the object
 */
public void
create_journal()
{
    set_journal_name("tome");
    set_journal_adj("gem-encrusted");
    set_journal_desc("The tome lies on the oak desk,"
      + " apparently having been used regularly to record the"
      + " thoughts and accomplishments of the High Priest.");
    set_journal_path(TEXT_DIR + "priest_journal/");

    add_item( ({ "gem", "gems" }),
        "Many crudly-cut gems have been inlaid along the binding"
      + " of this journal.\n");

    add_prop( OBJ_M_NO_GET, "As you move to take the tome with"
      + " you, your mind is struck by a sharp and stifling pain! It"
      + " appears this object is enchanted such that it cannot be"
      + " stolen by the likes of you.\n");

    /* This sits on a desk, and does not appear in the room
     * description.
     */
    set_no_show_composite(1);

    setuid();
    seteuid(getuid());
} /* create_journal */


/*
 * Function name:        quest_entry
 * Description  :        Provide the journal entry for the player
 *                       reading the tome, but also set a prop in
 *                       the player to show that they have read this
 *                       page, and know what reagent the Priest is
 *                       using to craft enchantments.
 */
public void
quest_entry()
{
    mixed     reagent = this_player()->query_prop(JOURNAL_REAGENT_PROP);
    string   *reagents = ({ "sandalwood",
                            "redcorn",
                            "dustwing",
                            "swallowfelt",
                            "firecone",
                            "skyshade",
                            "bluebark",
                            "icemoss",
                            "whitewood",
                            "marblecone",
                            "blackbark",
                         });

    if (!strlen(reagent))
    {
        reagent = one_of_list(reagents);
    }

    this_player()->catch_tell("210th Year of the Fifth Cycle, December 25\n\n"
      + "The waiting is over. Today I took blade to my brother's throat"
      + " and forced him on pain of immediate death to reveal to me the"
      + " substance required to produce lasting enchantments with the ghost"
      + " tears. Pathetic creature that he is, he quickly revealed to me"
      + " that " + reagent + " is the reagent required to bind the"
      + " enchantment to the material. And it does indeed work! I will"
      + " create an unholy arsenal so powerful that the feeding will"
      + " never again be threatened, and Yog-Sothoth will bless me for"
      + " all time! The formula is simple:\n\n"
      + "    - Play the bone flute in each prison cell.\n"
      + "    - Kill the spirits and take their tears.\n"
      + "    - Place the 8 tears in the Enchanter's forge.\n"
      + "    - Fuel the forge's furnace with " + reagent + ".\n"
      + "    - Insert the nullstone dagger into the opening of the"
      + " forge.\n\n"
      + "It works perfectly! The power of Imbuement is mine to"
      + " command!\n\n");

    this_player()->add_prop(JOURNAL_REAGENT_PROP, reagent);

    if (this_player()->query_prop(ORC_TEMPLE_QUEST_PROP) == "journal"
        && !this_player()->query_prop(JOURNAL_NOTIFY))
    {
        set_alarm(5.0, 0.0, &write("You could probably return and"
          + " make a <report> to the Enchanter about what you have"
          + " read here. There are, however, further entries to read"
          + " if you wish to learn more.\n"));
        this_player()->add_prop(JOURNAL_NOTIFY, 1);
    }

#if LOG_ACTIVITY
        write_file(LOG_DIR + "journal", 
            TIME2FORMAT(time(), "mm/dd/yyyy")
          + " (" + ctime(time())[11..18] + ") "
          + capitalize(this_player()->query_name())
          + " reads the journal entry.\n");
#endif
} /* quest_entry */