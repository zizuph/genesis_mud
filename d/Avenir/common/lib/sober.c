/*
 * - sober.c  ~*~ Lucius Kane.
 *
 * This is just a routine to increase sobriety.
 */
#pragma strict_types

#include <formulas.h>
#include <state_desc.h>
#include <stdproperties.h>

#define LIVE_I_DRANK_COFFEE  "__live_i_drank_coffee"

#undef DEBUG
#ifdef DEBUG
#  define D(x) write((x) + "\n");
#else
#  define D(x)
#endif

private string *intox = SD_HEADACHE, *denom = SD_STAT_DENOM;

public varargs void
make_sober(object who = this_player(), int silent = 0)
{
    int value = who->query_intoxicated();
D("VALUE: "+ value);
    /*
     * Not currently drunk
     */
    if (value < 1)
	return;
    /*
     * Normalize max intox levels.
     */
    int prop = who->query_prop(LIVE_I_MAX_INTOX);
    if (prop < 1) prop = 1;
D("PROP: "+ prop);
    /*
     * Determine personal increment between headache levels.
     */
    value = minmax(value, 0, prop - 1);
    int incr = (value * sizeof(intox) * sizeof(denom)) / prop;
D("INCR0: "+ incr +" -- "+ (sizeof(denom) + 1));
    incr /= (sizeof(denom) + 1);
D("INCR1: "+ incr);
    /*
     * Simulate normal rate of sobriety, effectively doubling it.
     */
    int rate = (incr / F_SOBER_RATE) * F_INTERVAL_BETWEEN_INTOX_HEALING;
D("RATE: "+ rate);
    /*
     * Not enough to reduce.
     */
    if (!incr || !rate)
	return;

    prop = who->query_prop(LIVE_I_DRANK_COFFEE);
    /*
     * Not enough time has passed to increase sobriety.
     */
    if ((time() - prop) < rate)
	return;
    /*
     * "heal" one headeache level.
     */
D("INTOX: "+ value +" - "+ incr +" == "+ (value - incr));
    who->set_intoxicated(value - incr);
    who->add_prop(LIVE_I_DRANK_COFFEE, time());
    /*
     * Print a message if desired.
     */
    if (!silent) {
	who->catch_tell("Your headache subsides somewhat.\n");
    }
}

