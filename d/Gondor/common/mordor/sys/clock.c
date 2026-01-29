#pragma  strict_types
#pragma  save_binary
#pragma  no_inherit
#pragma  no_clone
#pragma  resident

#include <stdproperties.h>
#include <macros.h>
#include "clock.h"
#include "defs.h"


// Moon Reference: http://www.treasure-troves.com/astro/Moon.html.
private static mapping _moon_phase_times = ([
    MOON_NEW                 : 0x00015180, // +1 day (full)
    MOON_WAXING_CRESCENT     : 0x0009BBA5, // +0x00086A25
    MOON_WAXING_HALF         : 0x000B0D25, // +1 day (half)
    MOON_WAXING_GIBBOUS      : 0x0013774A, // +0x00086A25
    MOON_FULL                : 0x0014C8CA, // +1 day (full)
    MOON_WANING_GIBBOUS      : 0x001D32EF, // +0x00086A25
    MOON_WANING_HALF         : 0x001E846F, // +1 day (half)
    MOON_WANING_CRESCENT     : 0x0026EE93, // +0x00086A24
]);

#define  MOON_SYNODIC_PERIOD   0x0026EE93
// MOON_TIME_RISE -> (DAY + (DAY / MOON_SYNODIC_PERIOD))
#define  MOON_TIME_RISE        0x00015CEE

private static mapping _rq_stages = ([ 
    RQ_GANDALF_IN_BAGEND     : 0x0107AC00, // midnight, Apr 12, 3018 TA
    RQ_OSGILIATH_ATTACK      : 0x01615200, // midnight, Jun 20, 3018 TA
    RQ_LEFT_HOBBITON         : 0x01DBED80, // midnight, Sep 23, 3018 TA
    RQ_ARRIVED_IN_RIVENDELL  : 0x01F25700, // midnight, Oct 10, 3018 TA
    RQ_LEFT_RIVENDELL        : 0x02553780, // midnight, Dec 25, 3018 TA
    RQ_ARRIVED_IN_LOTHLORIEN : 0x0270E700, // midnight, Jan 16, 3019 TA
    RQ_LEFT_LOTHLORIEN       : 0x02987400, // midnight, Feb 16, 3019 TA
    RQ_LEFT_HENNETH_ANNUN    : 0x02B57500, // midnight, Mar  8, 3019 TA
    RQ_ENTERED_MORDOR        : 0x02BEAF80, // midnight, Mar 15, 3019 TA
    RQ_QUEST_ENDED           : 0x02CBDE80, // midnight, Mar 25, 3019 TA
]);

private static int _stage;

private static function *_dawn_notifications       = ({ }),
                        *_dusk_notifications       = ({ }),
                        *_moon_rise_notifications  = ({ }),
                        *_moon_set_notifications   = ({ }),
                        *_moon_phase_notifications = ({ });

private static mapping _rq_notifications = ([
    RQ_GANDALF_IN_BAGEND     : ({ }),
    RQ_OSGILIATH_ATTACK      : ({ }),
    RQ_LEFT_HOBBITON         : ({ }),
    RQ_ARRIVED_IN_RIVENDELL  : ({ }),
    RQ_LEFT_RIVENDELL        : ({ }),
    RQ_ARRIVED_IN_LOTHLORIEN : ({ }),
    RQ_LEFT_LOTHLORIEN       : ({ }),
    RQ_LEFT_HENNETH_ANNUN    : ({ }),
    RQ_ENTERED_MORDOR        : ({ }),
    RQ_QUEST_ENDED           : ({ }),
]);

private int _zero_time; // system-time clock started, translates
                        // to midnight, September 22nd, 3017 TA,
                        // the date of Frodo's 50th birthday.


public nomask void
log(string text) {

    write_file(MORDOR_LOG + "clock", ctime(time()) + " :: " + text + "\n");

} // clock::log()


// Method  : time
// Remarks : Returns the time in real seconds elapsed since midnight on
//           September 22nd, 3017 TA.

public nomask int
time() {

    return (efun::time() - _zero_time);

} // clock::time()


// Method  : game_time
// Remarks : Returns the time in game seconds elapsed since midnight on
//           September 22nd, 3017 TA.

public nomask int
game_time() {

    return ((efun::time() - _zero_time) * 10);

} // clock::game_time()


public nomask int
game_time_24(int t = game_time()) {

    return (t % DAY);

} // clock::game_time_24()


public nomask int
game_second(int t = game_time()) {

    return (t % MINUTE);

} // clock::game_second()


public nomask int
game_minute(int t = game_time()) {

    return ((t % HOUR) / MINUTE);

} // clock::game_minute()


public nomask int
game_hour(int t = game_time()) {

    return (((t % DAY) / HOUR));

} // clock::game_hour()


public nomask int
game_day(int t = game_time()) {

    int days = ((t % MONTH) / DAY);

    if (days <= 8)
        return (days + 22);

    return (days - 8);

} // clock::game_day()


public nomask int
game_month(int t = game_time()) {

    int months = (t % YEAR);

    if (months < (DAY * 9))
        return (9);

    months = (((months - (DAY * 9)) / MONTH) + 1);
    if (months <= 3)
        return (months + 9);

    return (months - 3);

} // clock::game_month()


public nomask int
game_year(int t = game_time()) {

    int year_end_offset = ((MONTH * 3) + (DAY * 9));
    
    if (t < year_end_offset)
        return (3017);

    return (((t - year_end_offset) / YEAR) + 3018);

} // clock::game_year()


public nomask int
game_time_from_date(int month = game_month(),
                    int day = game_day(),
                    int year = (game_year() - 3017)) {

    if (year >= 3017)
        year -= 3017;

    if (month > 9)
        return ((year * YEAR) + ((month - 9) * MONTH) + (day * DAY));

    if ((month == 9) && (day >= 22))
        return ((year * YEAR) + ((day - 22) * DAY));

    if (year > 0)
        return (((year - 1) * YEAR) +
                ((month + 3) * MONTH) + ((day + 9) * DAY));

    return (((month + 3) * MONTH) + ((day + 9) * DAY));

} // clock::game_time_from_date()


public nomask string
month_string(int month = game_month()) {

    switch (month) {

        case 1 :
            return ("January");   // Narvinye
        case 2 :
            return ("February");  // Nenime
        case 3 :
            return ("March");     // Sulime
        case 4 :
            return ("April");     // Viresse
        case 5 :
            return ("May");       // Lotesse
        case 6 :
            return ("June");      // Narie
        case 7 :
            return ("July");      // Cermie
        case 8 :
            return ("August");    // Urime
        case 9 :
            return ("September"); // Yavannie
        case 10 :
            return ("October");   // Narquelie
        case 11 :
            return ("November");  // Hisime
        case 12 :
            return ("December");  // Ringare

    } // switch (month)

    return ("");

} // clock::month_string()


public nomask int
calculate_rq_stage(int t = game_time()) {

    int x, s;

    for (x = RQ_NONE; x <= RQ_QUEST_ENDED; x++)
        if (t >= _rq_stages[x])
            s = x;

    return (s);

} // clock:calculate_rq_stage()


public nomask string
rq_stage_string(int s = calculate_rq_stage(game_time())) {

    switch (s) {

        case RQ_NONE :
            return ("RQ_NONE");
        case RQ_GANDALF_IN_BAGEND :
            return ("RQ_GANDALF_IN_BAGEND");
        case RQ_OSGILIATH_ATTACK :
            return ("RQ_OSGILIATH_ATTACK");
        case RQ_LEFT_HOBBITON :
            return ("RQ_LEFT_HOBBITON");
        case RQ_ARRIVED_IN_RIVENDELL :
            return ("RQ_ARRIVED_IN_RIVENDELL");
        case RQ_LEFT_RIVENDELL :
            return ("RQ_LEFT_RIVENDELL");
        case RQ_ARRIVED_IN_LOTHLORIEN :
            return ("RQ_ARRIVED_IN_LOTHLORIEN");
        case RQ_LEFT_LOTHLORIEN :
            return ("RQ_LEFT_LOTHLORIEN");
        case RQ_LEFT_HENNETH_ANNUN :
            return ("RQ_LEFT_HENNETH_ANNUN");
        case RQ_ENTERED_MORDOR :
            return ("RQ_ENTERED_MORDOR");
        case RQ_QUEST_ENDED :
            return ("RQ_QUEST_ENDED");

    } // switch (s)

    return ("");

} // clock::rq_stage_string()


public nomask string
date_string(int t = game_time()) {

    return (month_string(game_month(t))[0..2] + " " + game_day(t) +
            ", " + game_year(t) + " TA");

} // clock::date_string()


public nomask string
time_string(int t = game_time()) {
    
    return (sprintf("%02d:%02d:%02d", game_hour(t),
                    game_minute(t), game_second(t)));

} // clock::time_string()


public nomask status
see_sky(object player) {

    object room;

    return (objectp(player) &&
//            (player == find_player("curumo")) &&
            (player == find_player("finwe")) &&
            objectp(room = environment(player)) &&
            (member_array(room->query_domain(), ME_DOMAINS) >= 0) &&
            !room->query_prop(ROOM_I_INSIDE) &&
            !room->query_prop(ROOM_M_NO_SUN));

} // clock::see_sky()


private nomask int
_dawn(int days) {

    if (days < 90) {

        // Between autumn equinox (6am) -> winter solstice (5am).
        return ((6 * HOUR) - ftoi((itof(days) / 90.0) * itof(HOUR)));

    }

    if ((days >= 90) && (days < 270)) {

        // It's between winter solstice (5am) -> summer solstice (7am).
        return ((5 * HOUR) + ftoi((itof(days - 90) / 180.0) * itof(2 * HOUR)));

    }

    // It's between summer solstice (7am) -> winter solstice (5am).
    return ((7 * HOUR) - ftoi((itof(days - 270) / 90.0) * itof(HOUR)));

} // clock::_dawn()


public nomask int
dawn(int t = game_time()) {

    int days, dawn_time;

    if ((t % YEAR) < 0)
        return (6 * HOUR); // Clock starts at autumn equinox.

    days = ((t % YEAR) / DAY);
    dawn_time = _dawn(days);
    
    if (game_time_24(t) > dawn_time) {

        // It's already past dawn for the given time, so calculate for
        // the next day's dawn.
        dawn_time = _dawn(++days);

    }

    // Truncate the time to midnight, and add the dawn time.
    return (((t / YEAR) * YEAR) + (days * DAY) + dawn_time);

} // clock::dawn()


public nomask void
announce_dawn(int time) {

    int x, d, sz;

    // Make sure this was called as a result of the clock alarm.
    if (previous_object() != this_object())
        return;

    filter(users(), see_sky)->catch_msg("The darkness seems to creep " +
                                        "back east, and day begins.\n");

    for (x = 0, sz = sizeof(_dawn_notifications); x < sz; x++)
        set_alarm(0.0, 0.0, _dawn_notifications[x]);

    _dawn_notifications = ({ });

    d = dawn(time + 1);
    set_alarm(itof((d - time) / 10), 0.0, &announce_dawn(d));

} // clock::announce_dawn()


private nomask int
_dusk(int days) {

    if (days < 90) {

        // Between autumn equinox (8pm) -> winter solstice (9pm).
        return ((20 * HOUR) - ftoi((itof(days) / 90.0) * itof(HOUR)));

    }

    if ((days >= 90) && (days < 270)) {

        // It's between winter solstice (7pm) -> summer solstice (9pm).
        return ((19 * HOUR) + ftoi((itof(days - 90) / 180.0) * itof(2 * HOUR)));

    }

    // It's between summer solstice (8pm) -> winter solstice (7pm).
    return ((21 * HOUR) - ftoi((itof(days - 270) / 90.0) * itof(HOUR)));

} // clock::_dusk()


public nomask int
dusk(int t = game_time()) {

    int days, dusk_time;

    if ((t % YEAR) < 0)
        return (6 * HOUR); // Clock starts at autumn equinox.

    days = ((t % YEAR) / DAY);
    dusk_time = _dusk(days);
    
    if (game_time_24(t) > dusk_time) {

        // It's already past dusk for the given time, so calculate for
        // the next day's dusk.
        dusk_time = _dusk(++days);

    }

    // Truncate the time to midnight, and add the dusk time.
    return (((t / YEAR) * YEAR) + (days * DAY) + dusk_time);

} // clock::dusk()


public nomask void
announce_dusk(int time) {

    int x, d, sz;

    // Make sure this was called as a result of the clock alarm.
    if (previous_object() != this_object())
        return;

    filter(users(), see_sky)->catch_msg("Darkness rolls in over the land " +
                                        "of Middle-earth from the east.\n");

    for (x = 0, sz = sizeof(_dusk_notifications); x < sz; x++)
        set_alarm(0.0, 0.0, _dusk_notifications[x]);

    _dusk_notifications = ({ });

    d = dusk(time + 1);
    set_alarm(itof((d - time) / 10), 0.0, &announce_dusk(d));

} // clock::announce_dusk()


public nomask string
position_string(int position) {

    switch (position) {

        case POSITION_NOT_VISIBLE :
            return ("POSITION_NOT_VISIBLE");
        case POSITION_EASTERN_HORIZON :
            return ("POSITION_EASTERN_HORIZON");
        case POSITION_EASTERN_RISING :
            return ("POSITION_EASTERN_RISING");
        case POSITION_OVERHEAD :
            return ("POSITION_OVERHEAD");
        case POSITION_WESTERN_SINKING :
            return ("POSITION_WESTERN_SINKING");
        case POSITION_WESTERN_HORIZON :
            return ("POSITION_WESTERN_HORIZON");
    
    } // switch (position)

    return ("");

} // clock::position_string()


public nomask int
sun_position(int t = game_time()) {

    int t_24, dusk_t, dawn_t, day = game_day(t);

    dawn_t = dawn(t);
    if (game_day(dawn_t) != day)
        dawn_t = dawn(t - DAY); // It's already past dawn for today.

    dusk_t = dusk(t);
    if (game_day(dusk_t) != day)
        dusk_t = dusk(t - DAY); // It's already past dusk for today.

    if ((t < dawn_t) || (t > dusk_t))
        return (POSITION_NOT_VISIBLE);

    if (t < (dawn_t + HOUR))
        return (POSITION_EASTERN_HORIZON);

    t_24 = game_time_24(t);
    
    if (t_24 < ((11 * HOUR) + (30 * MINUTE)))
        return (POSITION_EASTERN_RISING);

    if (t_24 < ((13 * HOUR) + (30 * MINUTE)))
        return (POSITION_OVERHEAD);

    if (t < (dusk_t - HOUR))
        return (POSITION_WESTERN_SINKING);

    if (t < dusk_t)
        return (POSITION_WESTERN_HORIZON);
    
    return (POSITION_NOT_VISIBLE);

} // clock::sun_position()


public nomask int
moon_phase(int t = game_time()) {

    int x;

    t = (t % MOON_SYNODIC_PERIOD);
    for (x = MOON_NEW; x <= MOON_WANING_CRESCENT; x++)
        if (t < _moon_phase_times[x])
            return (x);

} // clock::moon_phase()


public nomask string
moon_phase_string(int t = game_time()) {
  
    switch (moon_phase(t)) {

        case MOON_NEW :
            return ("new");
        case MOON_WAXING_CRESCENT :
            return ("waxing crescent");
        case MOON_WAXING_HALF :
            return ("waxing half");
        case MOON_WAXING_GIBBOUS :
            return ("waxing gibbous");
        case MOON_FULL :
            return ("full");
        case MOON_WANING_GIBBOUS :
            return ("waning gibbous");
        case MOON_WANING_HALF :
            return ("waning half");
        case MOON_WANING_CRESCENT :
            return ("waning crescent");

    } // switch (moon_phase(t))

} // clock::moon_phase_string()


private nomask string
moon_phase_macro_string(int phase = moon_phase(game_time())) {

    switch (phase) {

        case MOON_NEW :
            return ("MOON_NEW");
        case MOON_WAXING_CRESCENT :
            return ("MOON_WAXING_CRESCENT");
        case MOON_WAXING_HALF :
            return ("MOON_WAXING_HALF");
        case MOON_WAXING_GIBBOUS :
            return ("MOON_WAXING_GIBBOUS");
        case MOON_FULL :
            return ("MOON_FULL");
        case MOON_WANING_GIBBOUS :
            return ("MOON_WANING_GIBBOUS");
        case MOON_WANING_HALF :
            return ("MOON_WANING_HALF");
        case MOON_WANING_CRESCENT :
            return ("MOON_WANING_CRESCENT");

    } // switch (phase)

    return ("");

} // clock::moon_phase_macro_string()


public nomask int
moon_phase_time(int phase) {

    int t, x;

    if ((phase < MOON_NEW) || (phase > MOON_WANING_CRESCENT))
        return (0);

    t = game_time();
    x = (game_time() % MOON_SYNODIC_PERIOD);
    if (x <= _moon_phase_times[phase - 1])
        return (t + (_moon_phase_times[phase - 1] - x));

    return (t + _moon_phase_times[phase - 1] + (MOON_SYNODIC_PERIOD - x));

} // clock::moon_phase_time()


public nomask int
moon_rise(int t = game_time()) {

    return (t + (MOON_TIME_RISE - (t % MOON_TIME_RISE)));

} // clock::moon_rise()


public nomask int
moon_set(int t = game_time()) {

    return (moon_rise(t) + (12 * HOUR));

} // clock::moon_set()


public nomask int
moon_position(int t = game_time()) {

    int rise_t, set_t, day = game_day(t);

    rise_t = moon_rise(t);
    if (game_day(rise_t) != day)
        rise_t = moon_rise(t - DAY); // It's already past moon rise for today.

    set_t  = moon_set(t);
    if (game_day(set_t) != day)
        set_t = moon_set(t - DAY); // It's already past moon set for today.

    if ((t < rise_t) || (t > set_t))
        return (POSITION_NOT_VISIBLE);

    if (t < (rise_t + HOUR))
        return (POSITION_EASTERN_HORIZON);

    if (t < (rise_t + (5 * HOUR) + (30 * MINUTE)))
        return (POSITION_EASTERN_RISING);

    if (t < (rise_t + (6 * HOUR) + (30 * MINUTE)))
        return (POSITION_OVERHEAD);

    if (t < (set_t - HOUR))
        return (POSITION_WESTERN_SINKING);

    if (t < set_t)
        return (POSITION_WESTERN_HORIZON);

    return (POSITION_NOT_VISIBLE);

} // clock::moon_position()


public nomask void
announce_moon_rise(int time) {

    int x, r, sun, sz;

    // Make sure this was called as a result of the clock alarm.
    if (previous_object() != this_object())
        return;

    sun = sun_position(time);
    if ((sun < POSITION_EASTERN_RISING) ||
        (sun > POSITION_WESTERN_SINKING)) {

        if (moon_phase(time) == MOON_NEW)
            filter(users(), see_sky)->catch_msg("Ithil appears from behind " +
                                                "the eastern horizon, but " +
                                                "sheds no light as he is " +
                                                "new.\n");
        else
            filter(users(), see_sky)->catch_msg("Ithil's silvery light " +
                                                "appears as he rises from " +
                                                "behind the eastern " +
                                                "horizon.\n");

    } // if (sun < POSITION_EASTERN_RISING) || ...

    for (x = 0, sz = sizeof(_moon_rise_notifications); x < sz; x++)
        set_alarm(0.0, 0.0, _moon_rise_notifications[x]);

    _moon_rise_notifications = ({ });

    r = moon_rise(time + 1);
    set_alarm(itof((r - time) / 10), 0.0, &announce_moon_rise(r));

} // clock::announce_moon_rise()


public nomask void
announce_moon_set(int time) {

    int x, s, sun, sz;

    // Make sure this was called as a result of the clock alarm.
    if (previous_object() != this_object())
        return;

    sun = sun_position(time);
    sun = sun_position(time);
    if ((sun < POSITION_EASTERN_RISING) ||
        (sun > POSITION_WESTERN_SINKING)) {

        if (moon_phase(time) == MOON_NEW)
            filter(users(), see_sky)->catch_msg("Ithil disappears behind " +
                                                "the western horizon.\n");
        else
            filter(users(), see_sky)->catch_msg("Ithil's silvery light " +
                                                "disappears as he sinks " +
                                                "below the western " +
                                                "horizon.\n");

    } // if (sun < POSITION_EASTERN_RISING) || ...

    for (x = 0, sz = sizeof(_moon_set_notifications); x < sz; x++)
        set_alarm(0.0, 0.0, _moon_set_notifications[x]);

    _moon_set_notifications = ({ });

    s = moon_set(time + 1);
    set_alarm(itof((s - time) / 10), 0.0, &announce_moon_set(s));

} // clock::announce_moon_set()


public nomask void
announce_moon_phase(int time) {

    int x, sz, position, sun, phase;

    // Make sure this was called as a result of the clock alarm.
    if (previous_object() != this_object())
        return;

    sun = sun_position(time);
    phase = moon_phase(time);

    if ((sun < POSITION_EASTERN_RISING) || (sun > POSITION_WESTERN_SINKING)) {
    
        if (moon_position(time) != POSITION_NOT_VISIBLE) {

            switch (phase) {

                case MOON_NEW :
                    filter(users(), see_sky)->catch_msg("Ithil's silvery " +
                        "light winks out as he becomes new.\n");
                    break;

                case MOON_WAXING_CRESCENT :
                    filter(users(), see_sky)->catch_msg("Ithil's silvery " +
                        "light appears as he waxes into his crescent " +
                        "phase.\n");
                    break;

                case MOON_WAXING_HALF :
                case MOON_WANING_HALF :
                    filter(users(), see_sky)->catch_msg("Ithil is now " +
                        "half-full.\n");
                    break;

                case MOON_WAXING_GIBBOUS :
                    filter(users(), see_sky)->catch_msg("Ithil's silvery " +
                        "light grows as he waxes into his gibbous phase.\n");
                    break;

                case MOON_FULL :
                    if (sun == POSITION_NOT_VISIBLE)
                        filter(users(), see_sky)->catch_msg("Ithil's silvery " +
                            "light illuminates the land as he becomes full, " +
                            "casting shadows in the darkness.\n");
                    else
                        filter(users(), see_sky)->catch_msg("Ithil's is now " +
                            "full.\n");
                    break;

                case MOON_WANING_GIBBOUS :
                    filter(users(), see_sky)->catch_msg("Ithil's silvery light " +
                         "diminishes as he wanes into his gibbous phase.\n");
                    break;

                case MOON_WANING_CRESCENT :
                    filter(users(), see_sky)->catch_msg("Ithil's silvery light " +
                         "diminishes as he wanes into his crescent phase.\n");
                    break;

            } // switch (phase)

        } // if (moon_position(time) != POSITION_NOT_VISIBLE)

    } // if ((sun < POSITION_EASTERN_RISING) || ...

    for (x = 0, sz = sizeof(_moon_phase_notifications); x < sz; x++) {
        function f = _moon_phase_notifications[x];
        set_alarm(0.0, 0.0, &f(phase));
    }

    _moon_phase_notifications = ({ });

    x = moon_phase_time((phase == MOON_WANING_CRESCENT) ?
                        MOON_NEW : (phase + 1));
    set_alarm(itof((x - time) / 10), 0.0, &announce_moon_phase(x));

} // clock::announce_moon_phase()


public nomask int
query_rq_stage() {

    return (_stage);

} // clock::query_rq_stage()


public nomask void
increment_rq_stage() {

    function *funcs;
    int x, sz;

    // Make sure this was called as a result of the clock alarm.
    if ((previous_object() != this_object()) &&
        (calling_object() != this_object()))
        return;

    if (((_stage = calculate_rq_stage()) > RQ_NONE) &&
        (calling_function() != "create")) {

        for (x = _stage; x <= RQ_QUEST_ENDED; x++)
            _rq_notifications[x] -= ({ 0 });

        funcs = _rq_notifications[_stage];
        _rq_notifications[_stage] = ({ });

        for (x = 0, sz = sizeof(funcs); x < sz; x++) {
            function f = funcs[x];
            set_alarm(0.0, 0.0, &f(_stage));
        }

    } // if (((_stage = calculate_rq_stage()) > RQ_NONE) && ...

    if (_stage < RQ_QUEST_ENDED)
        set_alarm(itof((_rq_stages[_stage + 1] - game_time()) / 10),
                  0.0, increment_rq_stage);

} // clock::increment_rq_stage()


public nomask void
notify_dawn(function callback) {

    if (!functionp(callback))
        throw ("Illegal function passed to clock::notify_dawn().\n");

    _dawn_notifications -= ({ 0 });
    _dawn_notifications += ({ callback });

} // clock::notify_dawn()


public nomask void
notify_dusk(function callback) {

    if (!functionp(callback))
        throw ("Illegal function passed to clock::notify_dusk().\n");

    _dusk_notifications -= ({ 0 });
    _dusk_notifications += ({ callback });

} // clock::notify_dusk()


public nomask void
notify_moon_rise(function callback) {

    if (!functionp(callback))
        throw ("Illegal function passed to clock::notify_moon_rise().\n");

    _moon_rise_notifications -= ({ 0 });
    _moon_rise_notifications += ({ callback });

} // clock::notify_moon_rise()


public nomask void
notify_moon_set(function callback) {

    if (!functionp(callback))
        throw ("Illegal function passed to clock::notify_moon_set().\n");

    _moon_set_notifications -= ({ 0 });
    _moon_set_notifications += ({ callback });

} // clock::notify_moon_set()


public nomask void
notify_moon_phase(function callback) {

    if (!functionp(callback))
        throw ("Illegal function passed to clock::notify_moon_phase().\n");

    _moon_phase_notifications -= ({ 0 });
    _moon_phase_notifications += ({ callback });

} // clock::notify_moon_phase()


public nomask void
notify_rq_stage(function callback, int stage) {

    int x;

    if (!functionp(callback))
        throw ("Illegal function passed to clock::notify_rq_stage().\n");

    if ((stage <= _stage) || (stage > RQ_QUEST_ENDED))
        throw ("Illegal ring-quest stage passed to " +
               "clock::notify_rq_stage().\n");

/*  Not relevant for non-objectpointers and gives runtime error.
    for (x = _stage; x <= RQ_QUEST_ENDED; x++)
        _rq_notifications[x] -= ({ 0 });
*/

    _rq_notifications[stage] += ({ callback });

} // clock::notify_rq_stage()


public nomask string
stat_object() {

    mixed *alarms = get_all_alarms();
    int x, sz, t = game_time(), dawn_t = dawn(t), dusk_t = dusk(t),
        moon_rise_t = moon_rise(t), moon_set_t = moon_set(t),
        phase = moon_phase(t),
        phase_t = moon_phase_time((phase == MOON_WANING_CRESCENT) ?
                                  MOON_NEW : (phase + 1)),
        rqt = _rq_stages[_stage + 1];
    string s =
        "Middle-Earth Clock :" +
        "\n-----------------------------------------------------" +
        "\n   Start time              | " +
        ctime(_zero_time) +
        "\n   Game time               | " +
        time_string(t) + " " + date_string(t) +
        "\n   Sun                     |" +
        "\n      Dawn                 | " +
        time_string(dawn_t) + " " + date_string(dawn_t) +
        "\n      Dusk                 | " +
        time_string(dusk_t) + " " + date_string(dusk_t) +
        "\n      Position             | " +
        position_string(sun_position(t)) +
        "\n   Moon                    |" +
        "\n      Rise                 | " +
        time_string(moon_rise_t) + " " + date_string(moon_rise_t) +
        "\n      Set                  | " +
        time_string(moon_set_t) + " " + date_string(moon_set_t) +
        "\n      Phase                | " +
        moon_phase_macro_string(phase) +
        "\n      Next phase time      | " +
        time_string(phase_t) + " " + date_string(phase_t) +
        "\n      Position             | " +
        position_string(moon_position(t)) +
        "\n   Ring quest              |" +
        "\n      Stage                | " +
        rq_stage_string(calculate_rq_stage(t)) +
        "\n      Next stage           | " +
        rq_stage_string(_stage + 1) +
        "\n      Next stage time      | " +
        time_string(rqt) + " " + date_string(rqt);

    if (sz = sizeof(alarms)) {

        s += "\n   Alarms                  |\n";

        for (x = 0; x < sz; x++)
            s += sprintf("      %-19s  | %O seconds.\n", alarms[x][1],
                         alarms[x][2]);

    } // if (sz = sizeof(alarms))

    return (s);

} // clock::stat_object()


// Method  : create
// Remarks : Constructor.

public nomask void
create() {

    int t, x;

    seteuid(getuid(this_object()));

    if (!restore_object(MASTER)) {

        log("restore_object() failed, reinitializing clock.");
        _zero_time = efun::time();
        save_object(MASTER);

    } // if (!restore_object(MASTER))

    increment_rq_stage();
    if (_stage >= RQ_QUEST_ENDED) {

        log("the quest has ended, reinitializing clock.");
        _zero_time = efun::time();
        save_object(MASTER);
        increment_rq_stage();

    } // if (_stage >= RQ_QUEST_ENDED)

    t = game_time();

    x = dawn(t);
    set_alarm(itof((x - t) / 10), 0.0, &announce_dawn(x));

    x = dusk(t);
    set_alarm(itof((x - t) / 10), 0.0, &announce_dusk(x));

    x = moon_rise(t);
    set_alarm(itof((x - t) / 10), 0.0, &announce_moon_rise(x));

    x = moon_set(t);
    set_alarm(itof((x - t) / 10), 0.0, &announce_moon_set(x));

    x = moon_phase(t);
    x = moon_phase_time((x == MOON_WANING_CRESCENT) ? MOON_NEW : (x + 1));
    set_alarm(itof((x - t) / 10), 0.0, &announce_moon_phase(x));

    log("clock initialized.");

} // clock::create()
