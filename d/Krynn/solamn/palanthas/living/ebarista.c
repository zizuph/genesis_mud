/* 
 * Lady who serves food and drink at the cafe in the
 * northeast of the palatial plaza.  Schumann, anyone?
 * Mortis 09.2005
 */

#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include "/d/Krynn/common/defs.h"


inherit CITIZEN;

#define MONEY 11 + random(1500)

void
create_krynn_monster()
{
    set_name("clara");
	set_living_name("clara");
    set_race_name("human");
    set_adj("stately");
    add_adj("long-dressed");
	add_name(({"clara", "wieck", "schumann", "barista", "proprietor","lady"}));
	set_title("Wieck, Lady of the Light Hart");
    set_long("Stately and of average height and build is the lady of the "
	+ "Light Hart Cafe.  Her hair is pulled back into a bun with a pair of "
	+ "braids wrapped around it.  Though still a shiny, light brown, there "
	+ "is a thin streak of grey in her hair by her left temple.  She wears "
	+ "a long, tight-waisted grey and brown dress with a collar bound by a "
	+ "black ribbon about her neck.  The dress hovers just above the floor.  "
	+ "She is serving patrons from behind the counter along the south wall. "
	+ "\n");
	set_gender(G_FEMALE);
    set_stats(({20,60,45,75,60,55}));
    set_skill(SS_AWARENESS, 55);
    set_size_descs("short", "skinny");
	set_appearance(4);
	
	add_prop(OBJ_M_HAS_MONEY, MONEY);
	set_introduce(1);
    set_act_time(12);
    add_act("say Welcome, patrons.");
    add_act("say How may I accommodate?");
    add_act("emote nods as she smiles charmingly.");
    add_act("emote smells the air, as the door opens and a patron leaves, "
	+ "smiling to herself in pleasant reverie.");
	add_act("smell");
	add_act("emote hums a tune beneath her breath as she prepares an order.");
    add_act("time");
    
    add_ask(({"coffee", "food", "price", "list"}), "Clara replies:  "
    + "The Light Hart prepares its food and drink properly.  Your "
	+ "satisfaction is paramount.\n");

	add_ask(({"light hart cafe", "light hart", "cafe"}), "Clara replies:  "
    + "This is my cafe, and I am its proprietor.  Yes, the name is my own "
	+ "clever design.\n");

	add_ask(({"city", "palanthas"}), "Clara replies:  The city of Palanthas is "
	+ "magnificent and regal.  Its pristine marble, well architected streets, "
	+ "and beautifully designed buildings exude an old world charm you'll not "
	+ "find elsewhere.\n");

	add_armour(OBJ + "ecof_dress");
	set_alarm(2.0,0.0,"arm_me");

}

void
arm_me()
{
    seteuid(getuid(TO));
	MONEY_MAKE_GC(random(13))->move(TO);
	MONEY_MAKE_SC(40 + random(15))->move(TO);
}