
/*
 * Corpse Cleaner
 *
 * This object will place all the leftovers from a corpse
 * and items from the corpse on the ground in one shot.
 *
 * Jaacar, September 12, 2003
 *
 * Changelog:
 *      May 2008, Fixed bug with leftovers that aren't really
 *                leftovers. Causing duplicates and was being
 *                abused to get more dragon teeth. - Petros
 *      Feb 2009, Fixed the text so that if the corpse doesn't have
 *                a race, it won't print out silly 0's.
 *      April 2009, Removed no steal prop - Cotillion
 *      August 2009, Fixed runtime with bad leftover definitions - Petros
 *      October 2009, moved messages to hooks to allow inheriting - Petros
 * 2021-01-21 - Cotillion
 * - Added setting of OBJ_O_LOOTED_IN_ROOM prop
 */
 
inherit "/std/object";

#include <macros.h>
#include <files.h>
#include <stdproperties.h>
#include <cmdparse.h>

#include "/d/Calia/domain.h"

// Prototypes
public void     hook_no_corpse_found(string str);
public void     hook_clean_corpse(object corpse);

void create_object() 
{
    set_name( ({ "pentacled silver ingot", "pentacled ingot", "silver ingot",
                 "ingot"}));
    set_adj("silver");
    add_adj("pentacled");
    set_short("pentacled silver ingot");
    set_long("This silver ingot is a thin rod delicately carved with "+
        "tiny pentacles in a repetitive pattern around the shaft. It softly "+
        "vibrates with a mystical energy.\n");
    add_prop(MAGIC_AM_ID_INFO,({"This ingot has been magically infused with the "+
        "power of the elements. It can be passed over a corpse for a ritual "+
        "cleansing that will hasten the decay of physical remains, quickening "+
        "its return to the elemental cycle. The corpse's contents will be "+
        "left behind, as will particularly dense body matter. To use "+
        "the ingot, you need only <clean corpse>.\n", 10}));

    add_prop(OBJ_I_WEIGHT, 80);
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_VALUE, 4000);
    add_prop(OBJ_M_NO_SELL, 1);
}

int
do_clean(string str)
{
    mixed *stuff;
    object corpse, theorgan;
    string racename;
    int i;

    if (!strlen(str))
    {
        hook_no_corpse_found(str);
        return 0;
    }
    
    corpse = PARSE_COMMAND_ONE(str, 0, "[the] %i");
    if (!objectp(corpse) || !IS_CORPSE_OBJECT(corpse))
    {
        hook_no_corpse_found(str);
        return 0;
    }

    stuff = corpse->query_leftover();
    racename = corpse->query_race();

    setuid();
    seteuid(getuid());
    for (i=0; i < sizeof(stuff);i++)
    {
        if (stuff[i][2] == 0
            || (stuff[i][3] != "" && stuff[i][3] != 0))
        {
            // Don't clone the object if there are
            // none left available, or if there is VBFC
            continue;
        }
        theorgan = clone_object(stuff[i][0]);
        if (IS_LEFTOVER_OBJECT(theorgan))
        {
            // Wizards can place non-leftovers as parts of the
            // corpse. In this case, these objects should not
            // have these leftover/heap specific functions
            // called.
            if (!stringp(stuff[i][1]) || !intp(stuff[i][2]))
            {
                continue;
            }
            // Sometimes leftover objects are just not set up correctly
            // we check the types to make sure that we don't throw
            // runtimes.
            theorgan->leftover_init(stuff[i][1], racename);
            theorgan->set_heap_size(stuff[i][2]);
        }

        object room = environment(TP);
        theorgan->add_prop(OBJ_O_LOOTED_IN_ROOM, room);
        theorgan->move(room);
    }

    hook_clean_corpse(corpse);
    this_player()->remove_prop(TEMP_STDCORPSE_CHECKED);
    corpse->remove_object();
    return 1;
}

void
init()
{
    ::init();
    add_action(do_clean,"clean");
}

// HOOKS DEFINED BELOW

/* 
 * Function:    hook_no_corpse_found
 * Description: Should call notify_fail with your specific error
 *              message to display to users when corpse is not found.
 * Arguments:   str - the argument they passed in
 */
public void
hook_no_corpse_found(string str)
{
    NF("Clean which corpse?\n");    
}

/*
 * Function:    hook_clean_corpse
 * Description: Displays the messages when someone successfully cleans
 *              the corpse. The corpse is passed in so one can do
 *              queries on it before it gets destroyed.
 */
public void
hook_clean_corpse(object corpse)
{
    write("You extend your arm and pass the pentacled silver ingot slowly "
        + "over the " + corpse->short() + ". It glows softly with a faint "
        + "silver light before slowly fading into dust, leaving its "
        + "contents and a few remnants behind.\n");
    say(QCTNAME(TP) + " extends " + TP->query_possessive() + " arm and "
        + "passes " + TP->query_possessive() + " " + short() + " slowly "
        + "over the " + corpse->short() + ". It glows softly with a "
        + "faint silver light before slowly fading into dust, leaving "
        + "its contents and a few remnants behind.\n");    
}
