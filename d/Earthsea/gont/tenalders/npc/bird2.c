/*  A quest npc. The idea is to put the baby bird back in
*  the nest.  Bird is located at:
*  /d/Earthsea/gont/tenalders/village/witch_garden_8.c
*  The bird is replaced into a nest at:
*  /d/Earthsea/gont/tenalders/villlage/limb.c.
*  In order to pick it up, you first need to feed it a worm.
*/
inherit "/std/monster";
inherit "/std/combat/unarmed";

inherit "/std/act/domove";
inherit "/std/act/action";

#include "/sys/wa_types.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/filter_funs.h"
#include "/sys/stdproperties.h"
#include "/sys/cmdparse.h"

#include "defs.h"

#define A_WING 0
#define A_BEAK 1
#define A_FOOT 2


#define H_HEAD 0
#define H_BODY 1

// prototypes of functions:

int worm_given(object player);
string worm_check();
int right_worm = 0;
int drop_it(object ob);

void
create_monster()
{
    set_name("bird");
    set_adj("baby");
    set_living_name("_baby_bird_");
    set_short("baby bird");
    set_long(break_string("A tiny baby bird. It looks too small "+
	"to be away from its nest. It has blue and yellow "+
	"feathers.\n", 70));

    /* str, con, dex, int, wis, dis
    */
    set_stats(({5, 5, 5, 5, 5, 5}));

    set_hp(query_max_hp());

    set_skill(SS_UNARM_COMBAT, 5);
    set_skill(SS_DEFENCE, 5);

    set_attack_unarmed(A_WING, 10, 20, W_BLUDGEON, 30, "tiny wing");
    set_attack_unarmed(A_FOOT, 10, 20, W_BLUDGEON, 30, "tiny foot");
    set_attack_unarmed(A_BEAK, 10, 20, W_IMPALE, 30, "little beak");
    set_hitloc_unarmed(H_HEAD, ({15, 25, 20, 20 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 10, 5, 30, 20 }), 80, "body");

    set_act_time(35);
    add_act("emote cheeps hungrily.");
    add_act("emote flaps its tiny wings, trying to fly.");
    set_m_in("hops in");
    set_m_out("hops away");
    add_prop(OBJ_M_NO_GET, VBFC_ME("worm_check"));
    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
    add_prop(OBJ_M_NO_GIVE, "You don't want to give the baby "+
      "bird into someone else's keeping.\n");
    add_prop(OBJ_M_NO_SELL, "You can't sell a baby bird!\n");
    add_prop(CONT_I_WEIGHT, 1000);
    add_prop(CONT_I_VOLUME, 1000);
}

int
worm_given(object player)
{
    object to = this_object();

    to->command("eat worm");
    to->command("emote chirps happily.");
    player->add_prop(WORM_GIVEN, 1);
    return 1;
}

mixed
worm_check()
{
    object tp = this_player();
    object to = this_object();
    object basket;

    if (tp->query_prop(WORM_GIVEN))
    {



	basket = present("basket", tp);

	if (!objectp(basket))
	{
return "You can't carry a baby bird in your rough hands!\n";
	}


	return 0;
    }
    tp->catch_msg("The baby bird does not trust you.\n");
}

int
drop_it(object ob)
{
    object to = this_object();


    to->command("drop "+ ob->query_name());
    to->command("emote pecks at the "+ob->query_name());
    return 1;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(from) && ob->query_the_worm())
    {
	set_alarm(3.0, -1.0, &worm_given(from));
	return;
    }
    if (!ob->query_the_worm())
	set_alarm(2.0, -1.0, &drop_it(ob));
    return;
}

int
query_knight_prestige()
{
    return -20;
}

