/* Maen, the dwarven smith of Kendermore, Gwyneth, June 1999 */

#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit "/std/act/action.c";
inherit AM_FILE

public void
create_krynn_monster()
{
    if (!IS_CLONE)
        return;

    set_name("maen");
    set_living_name("maen");
    set_race_name("dwarf");
    set_title("Stoneblood, the Blacksmith of Kendermore");
    set_long("This dwarf looks a bit out of place in this city, but she " + 
        "doesn't seem to mind the odd ways of the inhabitants. In fact, " + 
        "she seems rather fond of them. Muscles bulge from her powerful " + 
        "arms as she hammers a piece of metal. She seems very friendly, " + 
        "but you might not want to anger her.\n");
    add_name("smith");
    add_name("blacksmith");
    set_adj("stout");
    add_adj("bright-eyed");
    set_gender(G_FEMALE);
    set_introduce(1);
    set_stats(({95,80,95,82,82,90}));
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_AWARENESS, 50);
    set_alignment(400);
    set_knight_prestige(-40);

    set_default_answer("The noise of metal clanging drowns out your words.\n");
    add_ask(" [about] 'sharpen'", "emote points to the sign.", 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    set_alarm(1.0,0.0,"arm_me");
}

/* Function name : Arm me
 * Description : Clones, wears and wields armours and weapons.
 * Returns : Null
*/

void
arm_me()
{
    seteuid(getuid(TO));
    clone_object(KOBJ + "dwarfboots")->move(TO);
    clone_object(KOBJ + "dwarfleather")->move(TO);
    clone_object(KOBJ + "dwarfpants")->move(TO);
    clone_object(KOBJ + "dwarfhammer")->move(TO);

    command("wear all");
    command("wield all");
}

