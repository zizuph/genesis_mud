/* Witch outside the forests of Kendermore, Gwyneth June 11, 1999 */

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit "/std/act/action.c";
inherit AM_FILE

create_krynn_monster()
{
    if (!IS_CLONE)
        return;

    set_name("sateela");
    add_name("sorceress");
    set_living_name("sateela");
    set_race_name("human");
    set_adj("willowy");
    add_adj("cold-hearted");
    set_gender(G_FEMALE);
    set_title("Adept of Magic");
    set_introduce(1);
    set_short("willowy cold-hearted sorceress");
    set_long("This woman looks back at you with a fire in her hard eyes. " + 
        "You can detect an air of magic about her. Perhaps it's best to " + 
        "leave this servant of Takhisis alone.\n");
    set_stats(({100,100,100,100,100,100}));
    set_hp(query_max_hp());

    set_skill(SS_AWARENESS, 50);
    set_skill(SS_UNARM_COMBAT, 80);

    set_alignment(-500);
    set_knight_prestige(200);
    set_act_time(10);
    add_act("scowl");
    add_act("emote mixes a handful of flowers into her pot.");
    add_act("emote brushes a lock of fire red hair from her face.");
    add_act("smile wickedly");
    set_alarm(0.0,0.0, "arm_me");
}

/* Function name : Arm me
 * Description : Clones, and wears armours
 * Returns : Null
*/
 
void
arm_me()
{
    setuid();
    seteuid(getuid(TO));
    clone_object(KOBJ + "wrobe")->move(TO);
    clone_object(KOBJ + "wcirclet")->move(TO);
    clone_object(KOBJ + "wshoes")->move(TO);
    command("wear all");
}

public void
do_die(object killer)
{
    command("remove robe");
    ::do_die(killer);
}
