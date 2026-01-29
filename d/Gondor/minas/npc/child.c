/* 
 * /d/Gondor/minas/npc/child.c  
 *
 * A child roaming the streets of Minas Tirith
 *
 * Originally coded by Elessar (?)
 *
 * Modified by Alto, 12 June 2001
 *   Revised character to fit a city bracing for war
 *   Altered description for varied NPCs
 *
 */

#pragma strict_types

inherit "/d/Gondor/minas/npc/mtirith_monster";
#include <ss_types.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

string  alignlook();
string  alignlook2();
void    arm_me();

private int armed = 0;

void
create_monster()
{
    set_adj(alignlook());
    add_adj(alignlook2());
    set_pname("children");
    set_name("child");
    add_name("boy");
    set_race_name("human"); 
    set_long("This is a young child roaming the streets of Minas Tirith. "
        + "Although in days past the children of Gondor laughed and played "
        + "in the streets, now they quietly help their mothers and fathers "
        + "prepare for an uncertain future. This boy is probably on an "
        + "errand of some sort.\n");
    default_config_npc(5 + random(10));
    set_alignment(50 + random(100));
    set_hp(350);
    set_skill(SS_WEP_KNIFE,10 + random(10));
    set_whimpy(1);
    set_gender(0);

    set_chat_time(30);

    add_chat("I am on my way to pick up Papa's armours. I hope "
        + "Master Calmacil has them ready.");
    add_chat("Greetings stranger! What brings you to the city?");
    add_chat("I wish I could play games with my friends. Alas we are "
        + "all too busy preparing for war.");
    add_chat("We used to live on a farm, but Papa said we would be "
        + "safer here in the city.");
    add_chat("How do you like my tunic? My mother made it for me on my "
        + "last birthday.");
    add_chat("My Papa is the bravest warrior in the world! If those orcs "
        + "are smart, they will stay away from here.");
    add_chat("When I grow up, I am going to be a Captain of the Guard "
        + "and protect the city from danger!");
    add_chat("I once saw the Steward ride by on his great horse. He looked "
        + "very sad.");
    add_chat("Have you news of Captain Boromir? Papa says he is much "
        + "needed in the coming war.");

    set_act_time(7);

    add_act("emote looks nervously at the eastern sky.");
    add_act("sigh");
    add_act("worry");
    add_act("emote shuffles his feet.");
    add_act("scratch head");
    add_act("smile sadly");
    add_act("emote looks about for his friends.");
    add_act("emote peers suspiciously at you.");

    set_cact_time(2);

    add_cact("say Craven! I am only a child!");
    add_cact("say Wait until my Papa gets ahold of you!");
    add_cact("emote looks for a way to escape.");
    add_cact("cry");
    add_cact("sob");

    arm_me();
}

void
arm_me()
{
    if (armed)
	return;

    seteuid(getuid(TO));

    clone_object(WEP_DIR + "knife")->move(TO);
    command("wield knife");
    clone_object(MINAS_DIR + "obj/ltunic")->move(TO);
    command("wear tunic");

    armed = 1;
}

string
alignlook() 
{
    string *alignlooks =
                 ({"short", "clever", "timid", "grim",
                   "tall", "thin", "friendly", "mischievous", "talented", 
                   "skinny","tough","shy","bold", "eager", 
                   "impatient"});
    return ONE_OF_LIST(alignlooks);
}


string
alignlook2() 
{
    string *alignlooks2 =
                 ({"adolescent", "juvenile",
                   "young"});
    return ONE_OF_LIST(alignlooks2);
}


/* solemnian prestige */
int query_knight_prestige() {return (-3);}
