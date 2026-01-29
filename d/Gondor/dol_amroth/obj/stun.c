/* -*- Mode: C -*-
 *
 * Stun object
 */
inherit "/std/object";

#include <stdproperties.h>

static object victim;
static int    delay = 1;

void set_victim(object o) { victim = o; }
void set_delay(int i) { delay = i; }

void
do_remove()
{
  //  tell_room(environment(environment(this_object())), "Stun Removed.\n",0,0);
    victim->remove_stun();
    remove_object();
}

void
remove_stun()
{
    set_alarm(itof(2+delay), 0.0, &do_remove());
}

void
create_object()
{
    set_short("__stun_object_");
    set_no_show();
    set_alarm(4.0,0.0,&remove_stun());
}

