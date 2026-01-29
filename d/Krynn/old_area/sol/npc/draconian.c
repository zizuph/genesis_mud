/* disquised draconian looking for staff - coded by ashbless */
/* turned into a Baaz by Aridor, 05/10/94*/


inherit "/d/Krynn/common/monster/baaz_base";

#include "/d/Krynn/common/defs.h"
#define ACT1 "emote hisses: Have you seen a blue crystal staff?"
#define ACT2 "emote hisses: It was stolen from our temple!"
#define ACT3 "emote hisses: The staff has healing properties..."
#define ACT4 "emote hisses: One of our brothers is very ill."
#define TALK ACT1, ACT2, ACT3, ACT4
#define STARE "emote stares at you suspiciously."
#define FEEL  "emote gives you an eerie feeling."
#define STOP FEEL, STARE, TALK
#include <money.h>
#include <ss_types.h>
#include <macros.h>

create_baaz()
{
    int i;
    if (!IS_CLONE)
	return;
    set_name("figure");
    set_race_name("humanoid");
    remove_adj("narrowfaced");
    set_short("tall hooded figure");
    set_pshort("tall hooded figures");
    set_long("This humanoid is extremely tall and is completely " +
	     "wrapped in cloth. Even its hands and feet are covered " +
	     "and its face is concealed under its hood. Its robes " +
	     "resemble those of a priest but you have never seen a " +
	     "priest this large and there is an odd bulge next to its " +
	     "belt.\n");
	
    set_adj("tall");
    add_adj("hooded");

    set_skill(SS_DEFENCE, 30);
    default_config_mobile(30);
    set_all_hitloc_unarmed(28);
    set_all_attack_unarmed(22, 12);

    add_item(({"clothes","cloth","clothing","robe","robes"}),
        "The figure is bundled up in many layers of cloth, " +
        "each of a different material. All its features are " +
        "completely concealed. It is slightly chilly for this " +
        "time of year, but this is ridiculous.\n");
    add_item(({"face","head", "hood"}),
        "Its hood is pulled far over its head and all " +
        "you can make out are two glowing eyes, staring " +
        "coldly back at you.\n");
    add_item(({"hand","hands","feet","foot"}),
        "Its hands and feet are wrapped in cloth and " +
        "are extremely large. It is clenching and unclenching " +
        "its hands under the robes, unnerving you.\n");
    add_item(({"buldge","belt","waist"}),
        "You think you can make out the familiar buldge " +
        "of a weapon at its side, but you aren't sure.\n");
    set_act_time(10);
    add_act(({ STOP, "east", "east", STOP, "east", "east", STOP,
        "east","east",STOP,"east","east",STOP,"west","west",STOP,
        "west","west",STOP,"west","west",STOP,"west","west",STOP,
        "south",STOP,"south",STOP,"north",STOP,"west",STOP,
        "east",STOP,"north"}));


    seteuid(getuid(TO));
    MONEY_MAKE_SC(30)->move(this_object());

}
