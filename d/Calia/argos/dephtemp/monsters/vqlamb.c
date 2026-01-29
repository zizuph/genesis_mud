/* A lamb in the fold
**
** This lamb is part of the Vision of Delphia Quest. It must be killed
** and its corpse (objects/lambbody) is needed for the quest.
** The lamb can only be attacked if the player is properly equipped
**     (see check attack)
** When the lamb dies, no real corpse is left, instead the lambbody
**     object is moved to the room (see do_die)
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           1/10/95    Created
*/
inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
#include <stdproperties.h>
#include <cmdparse.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include "defs.h"

#include "/d/Genesis/specials/debugger/debugger_tell.h"

#define A_FHOOVES 0
#define A_RHOOVES 1
#define A_BITE    2

#define H_HEAD 0
#define H_BODY 1

int check_attack();

void
create_creature()
{
    set_adj("snow-white");
    set_name("lamb");
    set_race_name("lamb");
    set_long(break_string(
        "He is one of the most innocent and defenseless creatures you "+
        "have ever seen. He has a pink face and is covered in a fleece "+
        "as white as snow.\n",70));

    set_stats(({ 5, 5, 5, 5, 5, 5}));
    set_hp(1000);
    set_skill(SS_DEFENCE,5);

    set_attack_unarmed(A_FHOOVES,  5,  5, W_BLUDGEON, 10, "front hooves");
    set_attack_unarmed(A_RHOOVES,  5,  5, W_BLUDGEON, 10, "rear hooves");
    set_attack_unarmed(A_BITE,     5,  5, W_SLASH,    80, "sharp teeth");

    set_hitloc_unarmed(H_HEAD, ({5, 5, 5, 5 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({5, 5, 5, 5 }), 80, "body");

    set_alignment(50);
    set_act_time(10);
    add_act("emote baaaahs squeakily.");
    add_prop(OBJ_I_NO_ATTACK, check_attack);
    add_prop(LIVE_I_NO_CORPSE,1);
    add_prop(CONT_I_WEIGHT, 10000);
    add_prop(CONT_I_VOLUME, 10000);
}

mixed
check_attack() {
   object TPlay=this_player();
   object WearsRobe   =(TPlay->query_armour(A_BODY))->id(VDQ_ROBE);
   object WearsMedal  =(TPlay->query_armour(A_NECK))->id(VDQ_MEDAL);
   object WieldsDagger=((TPlay->query_weapon(W_RIGHT))->id(VDQ_DAGGER) ||
                        (TPlay->query_weapon(W_LEFT))->id(VDQ_DAGGER));

    if ((WearsRobe) && (WearsMedal) && (WieldsDagger))
    {
        this_object()->command("emote screams in terror!");
        return 0;
    }
    else
    {
        return "You feel a divine force protecting "
            + this_object()->query_the_name(TPlay) + " "
            + "and you sense you are not adequately prepared "
            + "to slaughter this innocent animal.\n";
    }
}

void do_die(object attacker) {
   object body=clone_object(DEPHTEMP_DIR+"objects/lambbody");
   object TRoom=environment(this_object());
   body->move(TRoom);
   ::do_die(attacker);
}
