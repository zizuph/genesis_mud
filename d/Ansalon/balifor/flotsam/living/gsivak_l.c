/* created by Aridor 04/19/94 */
/* Modified by Gorr 13/12/96 */

#include "/d/Krynn/solamn/splains/local.h"
#include <ss_types.h>

inherit SIVAK;
inherit AUTO_TEAM

void
create_sivak()
{
    int i, j = 8;
    /* j is the level of the draconian */
    string str;

    set_pick_up_team(({"ogre","baaz","kapak","sivak"}));       

    for(i=0; i<6; i++)
	set_base_stat(i, j * 10 + random(10) + 30);
    set_skill(SS_DEFENCE,     j * 5 + random(4) + 65);
    set_skill(SS_PARRY,       j * 4 + random(4) + 65);
    set_skill(SS_WEP_SWORD,   j * 4 + random(4) + 65);
    set_skill(SS_2H_COMBAT,   j * 4 + random(4) + 65);
    set_skill(SS_WEP_KNIFE,   j * 4 + random(4) + 65);
    set_skill(SS_WEP_CLUB,    j * 4 + random(4) + 65);
    set_skill(SS_WEP_POLEARM, j * 4 + random(4) + 65);
    set_skill(SS_WEP_JAVELIN, j * 4 + random(4) + 65);
    set_skill(SS_WEP_AXE,     j * 4 + random(4) + 65);

    set_act_time(3);
    add_act("peer nervous");
    add_act("tap");           
    add_act("emote hisses: I wish I could kill something, my weapon is " +               
      "getting rusty ...");
    add_act("emote hisses: If only we could get some money for that.");
    add_act("emote hisses: If we don't find that amulet stolen from her lair, Emerald will " +
      "eat us quicker than a dwarf throws down ale.");
    add_act("emote hisses: I doubt Kitiara will be pleased if she catches us in Flotsam... " +
      "So be quiet!");
    set_cact_time(2);
    add_cact("grin");
    add_cact("emote moves back to protect one of the boxes.");
    add_cact("emote laughs maniacaly.");
    add_cact("emote licks his weapon.");
    add_cact("emote jumps forth and back to avoid the hits.");

    set_color("green");

    add_prop(NPC_I_NO_RUN_AWAY,1);
}

void
init_living()
{
    init_team_pickup();
    ::init_living();
}
