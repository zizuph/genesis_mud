/* 
 * Mortis 03.2006
 *
 * Merchant house Trusq office manager.
 *
 * Call constable when attacked?
 */

#include "../../local.h"
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <language.h>

inherit M_FILE
inherit AUTO_TEAM

int attacked;

/*prototype*/
void arm_me();

void
create_krynn_monster()
{
    seteuid(getuid(TO));

	set_name("varnga");
	set_living_name("varnga");
	add_name("manager");
	set_adj("brown-skinned");
	add_adj(({"thick-robed", "office"}));
	set_gender(G_MALE);
	set_short("brown-skinned thick-robed male manager");
	set_long("Nicely robed in blue, this business manager is busy "
	+ "at work keeping the affairs of merchant house Trusq in order.  "
	+ "On the swarthy side for an office worker, he has a rough edge "
	+ "about him that hints of a vigorous life outdoors.  He is certified "
	+ "by the bureaumancy to perform managerial duties.\n");
	set_race_name("human");
	set_title("Naci, Business Manager of Merchant House Trusq");
	
	set_size_descs("tall", "of normal width");
	set_appearance(3);
	set_introduce(1);

	set_skill(SS_DEFENCE,      50);
	set_skill(SS_UNARM_COMBAT, 45);
	set_skill(SS_WEP_SWORD,    50);
	set_skill(SS_AWARENESS,    35);

	set_stats((({35, 40, 35, 50, 45, 40})), 10);

    set_pick_up_team("guard");
    set_max_team_size_auto_join(3);

	set_alignment(300);
	set_knight_prestige(-20);

	add_ask(({"work", "accounting", "merchant", "house", "trusq"}), "say "
	+ "Merchant house Trusq is one of the oldest, most successful merchant "
	+ "houses in Palanthas.  I manage their affairs.", 1);
	add_ask("palanthas", "say Palanthas is the busiest trade city in the "
	+ "realms.  Anyone with a nose for business is assured of wealth here.",
	1);

    set_default_answer("@@def_answer");

	set_alarm(1.0,0.0,"arm_me");
}

string
def_answer()
{
    command("say I am much too busy keeping the affairs of merchant house "
	+ "Trusq in order to attend to that.  Who let you in here?");
    return "";
}

void
arm_me()
{
	MONEY_MAKE_GC(6 + random(11))->move(TO);
	MONEY_MAKE_SC(18 + random(19))->move(TO);
}

void
attacked_by(object ob)
{
	ob->add_prop(LIVE_I_ATTACKED_TRUSQ, 1);

	if (attacked == 0)
	{
		command("emote draws a blade from beneath his thick, blue robes.");
		object cutlass = clone_object(MERCH + "arms/smith_sword");
		cutlass->set_weapon_data("short" + "&&" + "polished" + "&&"
								 + "cutlass");
		cutlass->move(TO);
		command("wield cutlass");
		attacked = 1;
	}

    ::attacked_by(ob);
}
