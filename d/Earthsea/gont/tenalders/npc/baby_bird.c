/* A quest npc. The idea is to put the baby bird back in
 * the nest.  Bird is located at:
 * /d/Earthsea/gont/tenalders/village/witch_garden_8.c
 * The bird is replaced into a nest at:
 * /d/Earthsea/gont/tenalders/villlage/limb.c.
 * In order to pick it up, you first need to feed it a worm.
 * Then you need to put straw into a basket and carry it
 * in the basket.
*/

#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";

#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <language.h>
#include "defs.h"

#define A_WING 0
#define A_BEAK 1
#define A_FOOT 2
#define H_HEAD 0
#define H_BODY 1

public void
create_creature()
{
    set_name("bird");
    set_adj("baby");
    set_living_name("_baby_bird_");
    set_short("baby bird");
    set_long("A tiny baby bird. It looks too small "+
        "to be away from its nest. It has blue and yellow "+
        "feathers.\n");
    default_config_creature(5);
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
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(OBJ_M_NO_GET, VBFC_ME("worm_check"));
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(OBJ_M_NO_GIVE, "You don't want to give the baby "+
        "bird into someone else's keeping.\n");
    add_prop(OBJ_M_NO_SELL, "You can't sell a baby bird!\n");
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(CONT_I_WEIGHT, 1000);
    add_prop(CONT_I_VOLUME, 1000);
}

public void
worm_given(object player)
{
    command("eat worm");
    command("emote chirps happily.");
    player->add_prop(WORM_GIVEN, 1);
}

public void
drop_it(object ob)
{
    command("drop " + ob->query_name());
    command("emote pecks at " + LANG_THESHORT(ob));
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(ob->query_the_worm())
    {
        if(interactive(from))
        {
            set_alarm(1.0, 0.0, &worm_given(from));
        }
    } else {
        set_alarm(2.0, 0.0, &drop_it(ob));
    }
}

public void
jump_down(object tp)
{
    if((environment()->query_name() != "_basket_") &&
        (present(this_object(), tp)))
    {
        move(environment(tp));
        tell_room(environment(tp), "The little bird wriggles free "+
            "and jumps down.\n");
    }
}

public mixed
worm_check()
{
    object tp = this_player(), to = this_object(), *basket;

    if(tp->query_prop(WORM_GIVEN))
    {
        basket = FIND_STR_IN_OBJECT("_basket_", tp);

        if(sizeof(basket))
        {
            if(basket[0]->query_straw_in())
            {
                tell_room(environment(tp), QCTNAME(tp) + " gently picks up "+
                    "the baby bird.\n", ({ tp }));
                set_alarm(10.0, 0.0, &jump_down(tp));
                write("The baby bird allows you to gently pick " +
                    "it up.\n");
                return 0;
            }

            return "You need something softer inside the basket, "+
                "so the bird will feel more at home.\n";
        }

        return "You can't carry the bird in your bare hands!\n";
    }

    return "The baby bird does not trust you.\n";
}

public int
query_knight_prestige()
{
    return -20;
}
