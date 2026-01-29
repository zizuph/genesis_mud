/* 
 * Hero of the Lance - Tasslehoff
 * by Teth, March 28, 1996
 *
 * Quest stuff by Rastlin
 */

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include "hero_tasslehoff.h"
#include TIME_FLOW

inherit M_FILE
inherit CMD_MODULE;

public void
create_krynn_monster()
{
    set_name("tasslehoff");
    set_living_name("tasslehoff");
    set_title("Burrfoot");
    set_long("This kender, like all others, has a glint in his eye and " +
             "a curiousity in his voice.\n");
    set_race_name("kender");
    set_adj("mischievous");
    add_adj("happy");
    set_gender(G_MALE);
    add_prop(NPC_I_NO_LOOKS, 1);
    set_introduce(1);

    set_alignment(900);
}

/*
 * Function name: solace_forest
 * Description:   Here the actual talking will take place
 */
public void
solace_forest(float time)
{
    mixed talk = SOLACE_FOREST;

    if (sizeof(talk) > gCmd_counter)
        set_alarm(time, 0.0, &do_command(talk[gCmd_counter],
					 "solace_forest"));
}

/*
 * Function name: solace_forest_start
 * Description:   This starts the actions of Tas in the Solace forest.
 */
public void
solace_forest_start()
{
    gCmd_counter = 0;
}

public void
remove_object()
{
    INTERRUPT_PERIOD("tasslehoff", "Tasslehoff died");
    ::remove_object();
}
