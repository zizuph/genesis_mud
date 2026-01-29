inherit "/std/monster";

#include <ss_types.h>
#include <defs.h>
#include <macros.h>
#include <stdproperties.h>
#include <money.h>

void
create_monster()
{

    set_name("fisherman");
    add_adj("tanned");
    add_name("man");
    set_race_name("human");
    set_short("tanned fisherman");
    set_long("He looks to be about thirty years of age and is very tanned" +
	     " from working out in the sun all day. He is tall and slim" +
	     " with dark curly hair, dressed in a pair of grey linen" +
	     " trousers and wearing sandals on his feet. He is kneeling" +
	     " down on the beach, working on some fishing nets with quick" +
	 " agile fingers, seemingly knowing very well what he is doing.\n");
    set_stats(({35, 40, 40, 25, 35, 30}));
    set_skill(SS_PARRY, 25);
    set_skill(SS_WEP_KNIFE, 25);
    set_skill(SS_DEFENCE, 25);
    set_skill(SS_AWARENESS, 50);

    set_act_time(10);
    add_act("emote stands up briefly stretching his back.");
    add_act("emote peers out over the ocean.");
    add_act("emote sighs wearily.");
    set_default_answer("The fisherman says: I'm busy working right now!\n");
}

dress_me()
{
    object          wep, arm1, arm2;
    seteuid(geteuid(TO));
    wep =clone_object(CIR_OBJ + "fisher_knife.c");
    wep->move(TO);
    arm1 = clone_object(CIR_OBJ + "sandals.c");
    arm1->move(TO);
    arm2 = clone_object(CIR_OBJ + "trousers.c");
    arm2->move(TO);
    command("wear all");
    command("wield all");
    command("emote gives you a cautious look.");
    MONEY_MAKE_SC(5)->move(TO);
}
