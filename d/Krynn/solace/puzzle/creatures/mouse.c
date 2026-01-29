/* A cute mousy wowsey. ~solace/puzzle/creatures/mouse */

inherit "/std/monster";
inherit "/std/creature";
inherit "/std/combat/unarmed";

#include "../defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

#define ATT_TEETH       0
#define ATT_LFRONT      1
#define ATT_RFRONT      2

#define HIT_BODY        3
#define HIT_HEAD        4
#define HIT_TAIL        5
#define HIT_LFRONT      6
#define HIT_RFRONT      7
#define HIT_LBACK       8
#define HIT_RBACK       9

#define COLOUR ({"black", "brown", "white", "grey", "speckled"})

int killme_alarm, return_alarm;

void start_mouse()
{
    if(!pointerp(get_alarm(return_alarm)))
        return_alarm = set_alarm(itof(60 + random(61)), 0.0, "scamper_back");
}

void create_creature()
{
    set_name("mouse");
    set_pname("mice");
    set_adj("little");
    set_race_name("mouse");
    add_adj(COLOUR[random(sizeof(COLOUR))]);
    set_long("A cute little mouse scampering around on the ground. It "+
       "doesn't look very strong - in fact you'd be surprised if it put "+
       "up much of a fight at all.\n");

                       /* Att_id  Hit Pen  Dam_type     %  Att_string */
    set_attack_unarmed(ATT_TEETH,  3,  3,  W_IMPALE,   60, "teeth");
    set_attack_unarmed(ATT_LFRONT, 2,  1,  W_BLUDGEON, 20, "left front paw");
    set_attack_unarmed(ATT_RFRONT, 2,  1,  W_BLUDGEON, 20, "right front paw");

                    /* Hit_id     Ac   %  Hit_string */
    set_hitloc_unarmed(HIT_BODY,   2, 40, "body");
    set_hitloc_unarmed(HIT_HEAD,   2, 14, "head");
    set_hitloc_unarmed(HIT_TAIL,   1, 14, "tail");
    set_hitloc_unarmed(HIT_LBACK,  2,  8, "left back paw");
    set_hitloc_unarmed(HIT_LFRONT, 1,  8, "left front paw");
    set_hitloc_unarmed(HIT_RBACK,  2,  8, "right back paw");
    set_hitloc_unarmed(HIT_RFRONT, 1,  8, "right front paw");

    set_stats(({ (2 + random(3)),     /* str */
                 (2 + random(3)),     /* dex */
                 (2 + random(3)),     /* con */
                 (2 + random(3)),     /* int */
                 (2 + random(3)),     /* wis */
                 (2 + random(3))}));  /* dis */

    set_hp(10000);

    add_prop(CONT_I_WEIGHT, 500);
    add_prop(CONT_I_HEIGHT, 400);

    add_prop(LIVE_I_NEVERKNOWN, 1);

    change_prop(NPC_M_NO_ACCEPT_GIVE, 1);

    set_act_time(1);
    add_act("emote squeaks cutely.");
    add_act("emote scampers around.");
    add_act("emote cleans its paws.");
    add_act("emote twitches its nose.");
    add_act("emote @@floor_or_trap@@.");
    add_act("emote sniffs at your feet.");

    start_mouse();
}

string floor_or_trap()
{
    object trap = present("mouse-trap", E(TO));

    if(objectp(trap))
    {
        if(trap->query_ready())
            if(!pointerp(get_alarm(killme_alarm)))
                killme_alarm = set_alarm(1.0, 0.0, "kill_me", trap);

        return "looks inquisitively at the mouse-trap";
    }
    else
        return "sniffs at the floor";
}

void enter_env(object dest, object old)
{
    object cheese,  trap = present("mouse-trap", dest);

    if(objectp(trap))
    {
        if(trap->query_ready())
            if(!pointerp(get_alarm(killme_alarm)))
                killme_alarm = set_alarm(1.0, 0.0, "kill_me", trap);
    }

    if(objectp(cheese = present("cheese", dest)))
    {
        tell_room(E(TO), QCTNAME(TO)+" scampers over to the cheese and "+
            "drags it back into the mouse-hole.\n", TO);

        TO->remove_object();
        E(TO)->start_mouse();
        cheese->remove_object();
    }

    ::enter_env(dest, old);
}

void kill_me(object trap)
{
    tell_room(E(TO), QCTNAME(TO)+" scampers over to the mouse-trap and takes "+
        "a bite from the cheese.\n", TO);

    tell_room(E(TO), "All of a sudden, there is an almighty CRACK and the "+
        "trap snaps shut, killing "+QTNAME(TO)+"!\n", TO);

    trap->reset_trap();
    heal_hp(-10000);
    do_die(trap);
}

void scamper_back()
{
    E(TO)->start_mouse();

    tell_room(E(TO), QCTNAME(TO)+" scampers back into the mouse-hole.\n", TO);

    TO->remove_object();
}

void attacked_by(object obj)
{
    obj->stop_fight(TO);
    TO->stop_fight(obj);
    E(TO)->start_mouse();

    obj->catch_msg("Before you even reach "+QTNAME(TO)+", "+PRONOUN(TO)+
        " scampers back into the mouse-hole!\n");

    tell_room(E(TO), QCTNAME(obj)+" tries to attack "+QTNAME(TO)+", but "+
        PRONOUN(TO)+" scampers back into the mouse-hole before a blow is "+
        "thrown.\n", ({ obj, TO }));

    TO->remove_object();
}
