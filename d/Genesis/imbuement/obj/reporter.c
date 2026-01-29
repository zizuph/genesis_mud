/*
 *  /d/Genesis/imbuement/obj/reporter.c
 *
 *  Gives players a command so they can report bugs/typos/issues with imbuement
 *  related things, rather than the reports going to unrelated domain logs.
 *
 *  2011/02/16 Lavellan
 */
#pragma strict_types
#include "../imbuement.h"
#include "macros.h"
#include "files.h"

inherit "/std/object";

/* Definitions */
//#define ROOM "/d/Genesis/start/human/town/pier4"

/* Global Variables */

/* Prototypes */
void                    create_object();
public void             init();
public int              report(string arg);

/*
 * Set up parameters
 */
void
create_object()
{
    set_name("_imbuement_reporter");
    set_long("This invisible object gives players the \"imbuement\" command " +
        "with which they can report imbuement related issues.\n");

    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    
    set_no_show();

    seteuid(getuid());
} /* create_object */


/*
 * Function name: init
 * Description:   Add command to player
 */
public void
init()
{
    if (!interactive(this_player()))
        return;

    //if (environment() == find_object(ROOM))
    if (IS_ROOM_OBJECT(environment()))
    {
        if (this_player()->query_wiz_level())
            return;
        if (present("_imbuement_reporter", this_player()))
            return;
        if (present(LAPID_NAME, this_player()))
            return;
        clone_object(MASTER)->move(this_player());
    }
    else
        add_action(report, "imbuement");
} /* init */


/*
 * Function name: report
 * Description:   Allow players to report bugs etc.
 */
public int
report(string arg)
{
    IMBUE_LOGGER->report(arg);
    return 1;
} /* report */
    