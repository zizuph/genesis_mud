/*
 * Hero of the Lance - Flint
 * by Teth, March 28, 1996
 *
 * Quest stuff added by Rastlin April 10, 1996
 */

/*
 * TODO:
 *   Better desc?
 *   Equip Flint (weapons (esp. his axe) and armours (esp. 'griffon' helmet)
 *   Have him react on asks etc.
 *   Special attacks (a lot of them, he is a good fighter)
 *   He hates goblins. Make them aware of that (those who attacks atleast)
 *   Fix his stats.
 *   Give him his knife and a piece of wood.
 *   Quest stuff:
 */

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include TIME_FLOW
#include "hero_flint.h"

inherit M_FILE
inherit CMD_MODULE;

/* Prototypes */
static void flint_interrupt(string thread, string period);

public void
create_krynn_monster()
{
    set_name("flint");
    add_name(FLINT_NAME);
    set_living_name("flint");
    set_title("Fireforge");
    set_long("This dwarf, though outwardly appearing harsh, often slips " +
             "and shows his sentimental side, if you catch his eyes at " +
             "the right time. However, he often just grumbles.\n");
    set_race_name("dwarf");
    set_adj("gruff");
    add_adj("old");
    set_gender(G_MALE);
    add_prop(NPC_I_NO_LOOKS, 1);
    set_introduce(1);

    set_alignment(900);
}

static void
flint_interrupt(string thread, string period)
{
    INTERRUPT_PERIOD(thread, period);
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
 * Description:   This starts the actions of Flint in the Solace forest.
 */
public void
solace_forest_start()
{
    gCmd_counter = 0;
    solace_forest(3.0);
}

public void
remove_object()
{
    INTERRUPT_PERIOD("flint", "Flint died");
    ::remove_object();
}



