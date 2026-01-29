/* Goblin, a small and stupid evil creature
 * modified by Teth, Feb.07,96
 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit M_FILE
#include <macros.h>
#include <ss_types.h>

void
create_krynn_monster()
{
    int i;

    set_name("goblin");
    set_long("Snarling and stupid, this goblin smells of filth and " +
             "caves. It's fairly large, but it also doesn't look like " +
             "it would pose much of a challenge in a fight.\n");
    set_race_name("goblin");
    set_adj("wretched");

    add_act("say I wants to be a Seeker guard! Me train long and hard!");
    add_act("emote snarls viciously.");
    add_act("emote sighs wistfully and utters: Me wants to patrol " +
            "Solace one day like da biggah gobbos! Me hopes the " +
            "Fewmasta picks me after training!");
    add_act("say I wants to be paid more for what me does!");
    set_act_time(10);
    set_gender(2); /* male = 0, female = 1, other = 2 */
    add_prop(NPC_I_NO_LOOKS,1);

    set_alignment(-130);
    set_knight_prestige(200);

    for (i = 0; i < 6; i++)
        set_base_stat(i, 15 + random(5));

    set_skill(SS_WEP_KNIFE, 14);
    set_skill(SS_WEP_CLUB, 15);
    set_skill(SS_WEP_SWORD, 13);

    set_all_hitloc_unarmed(({ 6, 7, 5 }));

}

int
arm_me() 
{
    object wep;
    int temp;
    
    seteuid(getuid(TO));
    temp = random(3);
    if (temp == 0)
	wep = clone_object(OBJ + "wooden_club");
    if (temp == 1)
	wep = clone_object(OBJ + "knife");
    if (temp == 2)
	wep = clone_object(OBJ + "short_sword");
    wep->move(TO);
    command("wield all");
    return temp;
}

