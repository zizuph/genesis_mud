#pragma strict_types
#pragma save_binary

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove"; /* Include this if you want the creature to move */
inherit "/std/act/action"; /* Include this if you want your creature to act */

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>

#include <stdproperties.h>

#include "defs.h"

void move_home();

#define A_BITE  0
#define H_HEAD 0
#define H_BODY 1

void
create_creature()
{
    set_name("ant");
    set_race_name("ant");
    set_short("black ant");
    set_adj("black");

    set_stats(({7,4,5,2,2,10}));

    set_gender(2);

    set_attack_unarmed(A_BITE,  5, 3, W_IMPALE, 40, "jaws");

    set_hitloc_unarmed(H_HEAD, ({ 1, 2, 2, 2 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 1, 1, 3, 2 }), 80, "body");

    set_random_move(3);
    set_act_time(3);

    add_act("emote touches you with its tiny antennas.");

    add_prop(OBJ_I_WEIGHT,3);
    add_prop(OBJ_I_VOLUME,5);
    add_prop(CONT_I_WEIGHT,3);
    add_prop(CONT_I_VOLUME,5);
    add_prop(LIVE_I_NEVERKNOWN, 1);
}

void
enter_inv(object from,object to)
{
    ::enter_inv(from,to);

    set_alarm(1.0, 0.0, move_home);
}

void
do_die(object who)
{
    (ANTHANDLER)->remove_ant();

    ::do_die(who);
}

void
enter_env(object dest,object old)
{
    set_alarm(1.0, 0.0, &command("take all"));

    if(!old)
        return;

    if(!dest->query_prop(ANTSCENT))
        dest->add_prop(ANTSCENT,old);
}

void
move_home()
{
    object whereto;
    int alarm_id;

    whereto=E(TO)->query_prop(ANTSCENT);

    if(whereto)
    {
        tell_room(E(TO),"The black ant leaves.\n");
        move_living("M",whereto);
        tell_room(E(TO),"A small black ant arrives.\n");

        set_alarm(10.0, 0.0, move_home);
    }

    whereto = present("hill",E(TO));

    if(whereto)
    {
        tell_room(E(TO),"The tiny ant enters the ant hill, but returns almost immediately.\n");

        move_living("M",whereto);
        command("drop all");
        move(query_prop(LIVE_O_LAST_ROOM));

        remove_alarm(alarm_id);
    }
}

