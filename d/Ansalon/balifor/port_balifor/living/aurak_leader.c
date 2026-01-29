/* created by Aridor 04/19/94 */

#include "/d/Krynn/solamn/splains/local.h"
#include <ss_types.h>

inherit         AURAK;
inherit         AUTO_TEAM

                string color = "blue";

#include "/d/Krynn/solamn/splains/living/arm_me.h"

void
create_aurak()
{
    int             i, j = random(4) + 5;
    /* j is the level of the draconian */
    string          str;

    set_pick_up_team(({"aurak", "sivak", "bozak", "kapak"}));
    set_max_team_size_auto_join(6);

    add_prop(OBJ_I_COLORABLE, 1);

#include "/d/Krynn/solamn/splains/living/level_me.h"

    set_long(BS("This draconian, like all draconians, has a reptilian head. "
	   + "Except that this kind of draconian looks bigger and stronger "
		+ "than any other kind of draconian you have ever seen. "
		+ "You can't help thinking that his face looks like "
		+ "what you'd call an evil face. " + str, SL));


    for (i = 0; i < 6; i++)
	set_base_stat(i, j * 12 + random(14) + 40);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_2H_COMBAT, 100);
    set_skill(SS_WEP_KNIFE, j * 4 + random(4) + 65);
    set_skill(SS_WEP_CLUB, j * 4 + random(4) + 65);
    set_skill(SS_WEP_POLEARM, j * 4 + random(4) + 65);
    set_skill(SS_WEP_JAVELIN, j * 4 + random(4) + 65);
    set_skill(SS_WEP_AXE, j * 4 + random(4) + 65);

    set_all_hitloc_unarmed(20);

    set_act_time(3);
    add_act("emote looks at you suspiciously.");
    add_act("emote snarls: What have we here?");
    add_act("emote hisses: Have you seen anyone with " +
	    "a gemstone embedded in their chest? The Everman?");

    set_cact_time(10);
    add_cact("shout DIE THEN SCUM!");
    add_cact("shout Soldiers! To me!");

    set_alarm(2.0, 0.0, &arm_me(j + 4));

    start_patrol();
    set_patrol_time(30);
set_patrol_path(({"ne","n","n","nw","se","s","s","sw"}));

}


set_color(string new_color)
{
    color = new_color;
}


void
init_living()
{
    init_team_pickup();
    ::init_living();
}
