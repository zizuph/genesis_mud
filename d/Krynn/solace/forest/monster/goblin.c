/* Goblin, a small and stupid evil creature
 * updated by Teth, Feb.07/96
 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"

#include <money.h>

inherit M_FILE

void
create_krynn_monster()
{
    int i;

    set_name("goblin");
    set_long("A disgusting little creature, this goblin has warty green " +
             "skin and reeks of filth. It appears to be a pathetic " +
             "beast, untrained in the art of combat.\n");
    set_race_name("goblin");
    set_adj("stinking");

    add_act("say I hope da Fewmaster Toede likes da message me broughts " +
            "fo him.");
    add_act("say I wants to plunda Solace!");
    add_act("emote flaps his feet noisily as he skitters about nervously.");
    set_act_time(10);

    set_alignment(-100);
    set_knight_prestige(100);

    set_gender(2); /* male = 0, female = 1, other = 2 */
    add_prop(NPC_I_NO_LOOKS,1);

    for (i = 0; i < 6; i++)
        set_base_stat(i, 7 + random(5));

    set_all_attack_unarmed(7, 6);
    set_all_hitloc_unarmed(2);

    seteuid(getuid(TO));
    MONEY_MAKE_CC(5 + random(11))->move(TO);

}
