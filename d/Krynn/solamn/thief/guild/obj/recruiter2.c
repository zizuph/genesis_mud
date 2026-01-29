/* the recruiter of the thieves, by Aridor 12/13/95
 * this one is stationary in Solace, active at night
 * when the shop is closed.
 */

inherit "/d/Krynn/solamn/thief/guild/obj/recruiter";

#include "../guild.h"
#include <ss_types.h>

void
create_merchant()
{
    set_name("golinias");
    set_living_name("golinias");
    add_name("recruiter");
    set_adj("short-legged");
    add_adj("black-skinned");
    set_title("the Merchant");
    set_gender(0);
    set_long("This is a short-legged, black-skinned man in his best years. " +
	     "He looks very agile. He seems to be selling and buying " +
	     "things. Actually he seems to carry an entire shop around with him. " +
	     "Use the commands 'list', 'buy', 'value', 'show' and 'sell' just like " +
	     "in any normal shop.\n");
    set_race_name("human");
    default_config_mobile(110);
    set_all_attack_unarmed(90, 90);
    set_all_hitloc_unarmed(90);
    set_skill(SS_BACKSTAB, 80);
    set_skill(SS_WEP_KNIFE, 80);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_PICK_POCKET, 80);
    set_skill(SS_FR_TRAP, 80);
    set_skill(SS_HIDE, 80);
    set_skill(SS_SNEAK, 80);
    set_skill(SS_OPEN_LOCK, 80);
    set_skill(SS_ACROBAT, 80);
    set_skill(SS_TRADING, 100);
    set_skill(SS_APPR_OBJ, 90);
    set_skill(SS_APPR_VAL, 90);

    set_alignment(-100);
    set_knight_prestige(-1);
    set_whimpy_dir("north");
    set_whimpy(50);

    set_introduce(1);
    
    set_alarm(1.0,0.0,"equip_me");

    set_pick_up(10);
    set_act_time(10);
    add_act("say Torches, torches, cheap torches!");
    add_act("say Would you like to buy some torches?");
}

