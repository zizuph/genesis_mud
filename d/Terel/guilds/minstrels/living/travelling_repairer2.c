/* A repairer base for the minstrel guild. 
 *
 * Arman Dec 2019
 */

#pragma save_binary

inherit "/d/Terel/guilds/minstrels/living/minstrel_repairer";

#include <state_desc.h>
#include <stdproperties.h>

public void
set_up_repairer()
{
    set_name("minstrel");
    add_name("repairer");
    set_adj("travelling");
    set_short("travelling minstrel");
    set_race_name("human");

    add_prop(CONT_I_WEIGHT, 60000 + random(15000));
    add_prop(CONT_I_HEIGHT, 160 + random(40));

    set_long("Before you stands a human minstrel, travelling "
       + "the realms and performing in welcoming inns and taverns. "
       + "For fellow performers, he is happy to sell some of the "
       + "tools of his trade, <fix> "
       + "or <repair> a damaged instrument, or <assess> the "
       + "cost to repair damaged instruments.\n");
    default_config_npc(SD_AV_EXPERT);
    set_alignment(500);
}