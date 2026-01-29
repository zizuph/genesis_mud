/*
 * Some library functions for Gnomehome.
 *
 */

#pragma save_binary

#include "../gnome.h"

object *guards;
mixed  *guard_settings;

void
reset_guards() {
    int i;
    if (!guards) {
	guards = allocate(guard_settings[0]);
    }
    for (i = 0; i < guard_settings[0]; i ++) {
	call_out("queue_make_guard", 0, i);
    }
}

void
queue_make_guard(int index) {
    object guard;

    if (!guards[index]) {
	guard = (object) GUARD_POOL->fetch_guard(guard_settings[1]);
	if (guard) {
	    if (guard_settings[2]) {
		filter(guard_settings[2], "equip_guard", this_object(), guard);
	    }
	    guard->queue_setup(guard_settings[3], guard_settings[4]);
	    guards[index] = guard;
	}
    }
}

void
equip_guard(string file, object guard) {
    object ob;
    ob = clone_object(file);
    if (ob) {
	ob->move(guard);
    }
}

varargs mixed *
relay(object *arr, string func, object ob, mixed extra) {
    if (!ob) {
        ob = this_object();
    }
    return map(arr, "do_relay", ob, ({ func, extra }));
}

mixed
do_relay(object ob, mixed *extra) {
    return (mixed) call_other(ob, extra[0], extra[1]);
}

void
room_shout(string str, mixed *exits) {
    int i;

    for (i = 0; i < sizeof(exits); i += 3) {
	tell_room(exits[i], str);
    }
}

object
living_environment(object ob) {
    while (ob && !living(ob)) {
	ob = environment(ob);
    }
    return ob;
}
