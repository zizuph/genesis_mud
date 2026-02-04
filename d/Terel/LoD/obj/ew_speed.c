/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * ew_speed.c
 *
 * A speed increasing/decreasing object
 * it uses the prop LIVE_I_QUICKNESS in the player/npc
 * Tailored for the evil warlord
 */

#include "/d/Terel/include/Terel.h"
inherit STDOBJECT;

int query_time_left();
void set_duration(int t);
int query_quickness();
void set_quickness(int q);

int speed_set_by_me = 0;
int id_dur, quickness=0;
int delta_q;
int duration;

create_object()
{
    set_name("_evil_slowness");
    add_prop(OBJ_M_NO_DROP, 1);
    set_no_show(1);
}

void
enter_env(object dest, object old)
{
    int old_q, new_q;

    ::enter_env(dest, old);
    if (living(dest)) {
	old_q = dest->query_prop(LIVE_I_QUICKNESS);
	new_q = old_q + query_quickness();
	if (new_q > 100) new_q = 100;
	if (new_q < -100) new_q = -100;
	delta_q = new_q - old_q;
	if (delta_q > 0) {
            dest->catch_msg("Energy flows through your entire body.\n");
	} else if (delta_q < 0) {
            dest->catch_msg("Energy is leaving your body. " +
			    "You suddenly feel very tired.\n");
	}
	if (old_q == 0) {
	    dest->add_prop(LIVE_I_QUICKNESS, new_q);
	} else {
	    dest->change_prop(LIVE_I_QUICKNESS, new_q);
	}
        if (duration < 10) duration = 10;
	id_dur = set_alarm(itof(duration), -1.0, "remove_object");
        speed_set_by_me = 1;
    } else {
	remove_object();
    }
}

void
leave_env(object from, object to)
{
    int q;

    ::leave_env(from, to);
    if (living(from) && speed_set_by_me) {
        speed_set_by_me = 0;
	q = from->query_prop(LIVE_I_QUICKNESS) - delta_q;
	if (delta_q < 0) {
            from->catch_msg("Energy flows back into your body.\n");
	} else if (delta_q > 0) {
            from->catch_msg("Some of the evil energy seems to vanish.\n");
	}
	if (q == 0) {
	    from->remove_prop(LIVE_I_QUICKNESS);
	} else {
	    from->change_prop(LIVE_I_QUICKNESS, q);
	}
    }
}

void
set_duration(int t)
{
    duration = t;
}

int
query_time_left()
{
    if (!id_dur) return -1;
    
    return ftoi(get_alarm(id_dur)[2]);
}

void
set_quickness(int q)
{
    quickness = q;
}

int
query_quickness()
{
    return quickness;
}
