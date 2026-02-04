/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/*  Mystic Cloud.c */
/*  janus 921029 */

inherit "/std/object";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#define BS(xx)    break_string((xx), 72)
#define TO        this_object()
#define ETO       environment(TO)
#define MSGS      ({\
       "A bright flash of lightning streaks forth from the storm!",\
       "A light rain falls from the dark storm clouds.",\
       "A sudden crash of thunder errupts from the storm.",\
       "A blast of wind almost knocks you down.",\
       "The dark storm lulls for a moment.",\
       "The storm rumbles and flashes with excitement."\
       })
#define MAX_CALLS 10

public void set_controller(object ob);
public object query_controller();

static int ncalls=0, activated=0;
static object controller;

create_object()
{
    set_name("mystic_cloud");
    add_name("storm");
    add_name("mystic_storm");
    add_name("cloud");
    set_short("dark storm");
    set_long(BS("Dark and tempestuous, this storm hangs in the sky like the"+
              " wrath of nature itself. Its blue-black clouds drift about" 
            + " the sky quickly and with tumultuous effect. Flashes of bright"
            + " lightning pass through the clouds, followed by deep rumbling"
            + " thunder. Shadowy figures seem to dance within the midst of the"
            + " storm, crying out like lost children wailing in despair.\n")); 

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000000);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_GET, "You cannot even touch it!\n");
    add_prop(MAGIC_AM_MAGIC, ({90,"summoning"}));
    set_alarm(20.0, -1.0, "do_stuff");
}

public void
set_controller(object ob)
{
    controller = ob;
}

public object
query_controller()
{
    return controller;
}

public void
remove_object()
{
    if (controller) controller->remove_object();
    ::remove_object();
}

do_stuff()
{
    int i;

    if (ncalls >= MAX_CALLS) {
       remove_object();
       return;
    }
    ncalls++;

    i = random(sizeof(MSGS));
    tell_room(ETO, BS(MSGS[i]) + "\n");
    activated = 1;
    set_alarm(40.0, -1.0, "do_stuff");
}

public int
call_thunder(object who)
{
    int i;
    object *ob;

    if (!activated) return 0;

    ob = all_inventory(ETO);
    tell_room(ETO, "A sudden crash of thunder errupts from the storm.\n");
    for (i=0; i<sizeof(ob); i++) {
        if (!living(ob[i])) continue;
        if (random(ob[i]->query_stat(SS_DIS)) < 30) {
            ob[i]->catch_msg("The crash of thunder scares you.\n");
            ob[i]->add_panic(20);
        }
    }
    activated = 0;
    return 1;
}

public int
call_lightning(object who)
{
    int i;
    object *ob;

    if (!activated) return 0;

    ob = all_inventory(ETO);
    tell_room(ETO, "A bright flash emerges from the cloud.\n");
    for (i=0; i<sizeof(ob); i++) {
        if (!living(ob[i])) continue;
        if (random(ob[i]->query_stat(SS_DEX)) < 30) {
            ob[i]->catch_msg("The flash hurts your eyes.\n");
            ob[i]->reduce_hit_point(2);
        }
    }
    activated = 0;
    return 1;
}

public int
call_wind(object who)
{
    int i;
    object *ob;

    if (!activated) return 0;

    ob = all_inventory(ETO);
    tell_room(ETO, "You are thrown to the ground by a gust of wind.\n");
    for (i=0; i<sizeof(ob); i++) {
        if (!living(ob[i])) continue;
        if (random(ob[i]->query_stat(SS_CON)) < 30) {
            ob[i]->catch_msg("You get dizzy by the fall.\n");
            ob[i]->add_mana(-2);
        }
    }
    activated = 0;
    return 1;
}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (to->query_prop(ROOM_I_IS))
        tell_room(to, "The winds rise up and a storm begins " 
        + "to brew. The skies grow dark and a wind fills the air.\n");
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    if (from->query_prop(ROOM_I_IS))
       tell_room(from, "The storm clouds fade away into the distant sky.\n");        }
