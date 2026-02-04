/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
/*
 * A speed increasin/decreasing object
 * it uses the prop LIVE_I_QUICKNESS in the player/npc
 * Used in the mystic order spell:
 */
inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

#define TO         this_object()
#define TP         this_player()
#define ETO        environment(TO)
#define MIN_DUR    10
#define MAX_DUR    1000

public int query_time_left();
public void set_duration(int t);
public int query_quickness();
public void set_quickness(int q);

int speed_set_by_me = 0;
int duration=0, quickness=0;
int delta_q, aid=0;

public void
create_object()
{
    set_name("mystic energy");
    set_no_show();
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
}

public void
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
            dest->catch_msg("Mystic energy flows through your entire body.\n");
	} else if (delta_q < 0) {
            dest->catch_msg("Energy is leaving your body.\n");
	}
	if (old_q == 0) {
	    dest->add_prop(LIVE_I_QUICKNESS, new_q);
	} else {
	    dest->change_prop(LIVE_I_QUICKNESS, new_q);
	}
	aid = set_alarm(itof(duration), -1.0, remove_object);
        speed_set_by_me = 1;
    } else {
	remove_object();
    }
}

public void
leave_env(object from, object to)
{
    int q;

    ::leave_env(from, to);
    
    if (aid) aid = 0;
    
    if (living(from) && speed_set_by_me) {
        speed_set_by_me = 0;
	q = from->query_prop(LIVE_I_QUICKNESS) - delta_q;
	if (delta_q < 0) {
            from->catch_msg("Energy flows back into your body.\n");
	} else if (delta_q > 0) {
            from->catch_msg("Some of the mystic energy seems to vanish.\n");
	}
	if (q == 0) {
	    from->remove_prop(LIVE_I_QUICKNESS);
	} else {
	    from->change_prop(LIVE_I_QUICKNESS, q);
	}
    }
}

public void
set_duration(int t)
{
    duration = t;
    if (duration < MIN_DUR) duration = MIN_DUR;
    if (duration > MAX_DUR) duration = MAX_DUR;
}

public int
query_time_left()
{
    mixed *call;
    
    if (!aid) return -1;
    call = get_alarm(aid);
    return ftoi(call[2]);
}

public void
set_quickness(int q)
{
    quickness = q;
}

public int
query_quickness()
{
    return quickness;
}
