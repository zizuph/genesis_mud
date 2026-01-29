
/* 
   Potion for Gelan alchemist quest, will have one of a range of 
   strange side-effects when drunk. 

   Coded by Maniac

   Amended, Maniac, 19/2/96, 16/5/98
*/

inherit "/std/drink";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <language.h>
#include "object.h"
#include ALCHEMIST_QUEST


int effect = -1;

void
set_effect(int e)
{
    effect = e;
}


int
has_side_effect(object tp)
{
    if (present(STUTTER_NAME, tp) ||
        tp->has_weaken_stat_shadow() ||
        tp->has_g_change_shadow())
        return 1;
    else
        return 0;
}



void
remove_object()
{
    if (environment(this_object())->query_prop(ROOM_I_IS))
        tell_room(environment(this_object()), 
        capitalize(LANG_THESHORT(this_object())) + 
                  " breaks as it hits the ground.\n");
    ::remove_object();
}


/* Break potion if it's dropped */ 
void
leave_env(object old, object dest)
{
    ::leave_env(old, dest);
    if (!living(dest))
        set_alarm(1.0, 0.0, "remove_object");
}


void
special_effect(int n)
{
    int sw;
    object tp = this_player();
    object a, s;


    if ((tp->query_stat(SS_CON) < AQ_MIN_CON) ||
        (tp->query_stuffed() > AQ_MAX_STUFFED)  ||
        (tp->query_soaked() > (query_soft_amount() + AQ_MAX_SOAKED)) ||
        has_side_effect(tp)) {
        tp->set_hp(1);
        tp->catch_msg("You feel absolutely terrible after " +
             "drinking the potion! Your health has dropped " +
             "nigh to death!\n"); 
        tell_room(environment(tp), QCTNAME(tp) + " looks deathly " +
             "ill.\n", tp);
        return;
    }

    if (effect == -1)
        sw = random(3);
    else
        sw = effect;

    seteuid(getuid());
    switch (sw) {
        case 0: clone_object(GELAN_OBJECTS + "stutter")->move(tp);
                tp->add_prop(AQ_EXPERIMENT_FAILURE, "stutter");
                if (a = present(ALCHEMIST_NAME, environment(tp)))
                    a->react(tp);
                break;
        case 1: s = clone_object(GELAN_SPECIALS + "weaken_shadow");
                s->shadow_me(tp);
                s->weaken_stat();
                tp->add_prop(AQ_EXPERIMENT_FAILURE, "weaken");
                if (a = present(ALCHEMIST_NAME, environment(tp))) 
                    a->react(tp);
                break;
        default: s = clone_object(GELAN_SPECIALS + "g_change_shadow");
                s->shadow_me(tp);
                s->trans_to();
                tp->add_prop(AQ_EXPERIMENT_FAILURE, "g_change");
                if (a = present(ALCHEMIST_NAME, environment(tp)))
                    a->react(tp);
                break;
    }
}


void
create_drink()
{
    set_name("potion");
    add_name(AQ_GREEN_POTION);
    set_adj(({"green", "bubbling"}));
    set_short("green bubbling potion");
    set_long("A green bubbling potion. You get the feeling that if " +
             "you're going to drink it you'd better be prepared for " +
             "something strange to happen!\n");
    set_soft_amount(40);
    set_alco_amount(1);
    add_prop(OBJ_I_WEIGHT, 330);
    add_prop(OBJ_I_VOLUME, 330);
}

