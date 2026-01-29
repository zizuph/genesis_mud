/*
 * Lorfela the Aide of Wayreth
*/

#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <money.h>
#include "/d/Krynn/common/defs.h";
inherit M_FILE

inherit "/std/act/domove";     /* Allows Lenz to move */
inherit "/std/act/action";     /* Allows Lenz to act  */

public void
create_krynn_monster()
{
    string str;

    set_name("lorfela");
    set_living_name("lorfela");
    set_race_name("aide");
    set_title("the Aide of Wayreth");
    set_long("This magical creature is more of a presence than a physical " +
	"being. Created and sustained for the purpose of aiding Wizards " +
	"in the management of their equipment, this aide will " +
	"monitor items given and taken from storage at the Tower of " +
        "Wayreth.\n"); 
    add_name(({"ethereal","creature","being"}));
    set_adj("ethereal");
    set_gender(G_NEUTER);
    add_prop(NPC_I_NO_LOOKS,1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(CONT_I_HEIGHT, 190);
    add_prop(CONT_I_WEIGHT, 70100);

    set_stats(({100,120,100,100,200,100}));
    set_skill(SS_DEFENCE,        100);
    set_skill(SS_BLIND_COMBAT,   100);
    set_skill(SS_AWARENESS,      150);
    set_skill(SS_UNARM_COMBAT,   100);
  
    set_default_answer("The aide says: I'm sorry, but that is beyond " +
        "my knowledge and duties.\n");
   
    add_ask(" [about] 'quest' / 'task'",
	"say I thank you for your offer, but I am but " +
	"a lowly servant here and have no needs.", 1);

    set_act_time(85);
    add_act("emote patiently waits to help you where possible.");
    add_act("emote floats about, tidying the racks and chests.");
    
    set_cact_time(4);
    add_cact("say Odd, you shouldn't be able to attack me, please " +
	"make a bug report about this to the Immortal Wizards of " +
	"the Tower.\n");
}  

