/*
 * /d/Gondor/common/guild/north/obj/towel.c
 *
 * Modification history:
 *
 * 28-Feb-98, Gnadnar: general cleanup, conform to domain.rules
 */
inherit "/std/object";

#include "/d/Gondor/defs.h"
#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#define BODY_PARTS  ({"thigh","buttock","arm","back","leg","waist", \
                     "tummy","shoulder","chest"})

#define WET         "i_am_wet"
#define TOWEL_ID    "_northern_baths_towel"


static int Wet, Dry_alarm_id;

public void     create_object();
public string   long_desc();
public void     init();
public int      do_dry(string str);
public void     dry_towel();
public int      do_snap(string str);
public int      query_wet();


/*
 * Function name: create_object
 * Description  : set up the towel
 */
public void
create_object()
{
    set_name("towel");
    add_name(TOWEL_ID);
    add_adj( ({ "plush", "blue", "bath" }) );
    set_long(long_desc);
    add_prop(OBJ_I_WEIGHT, 125 + random(100));
    add_prop(OBJ_I_VOLUME, 100 + random(50));
    add_prop(OBJ_I_VALUE, 0);
}


/*
 * Function name: long_desc
 * Description  : VBFC for towel desc
 * Returns      : string -- the desc
 */
public string
long_desc()
{
    if (Wet)
    {
        return "The plush towel is soft and comfortable, quite " +
            "absorbent, and right now rather wet. It has been dyed " +
            "a deep shade of royal blue.\n";
    }

    return "The plush towel is soft and comfortable, and quite " +
        "absorbent. It has been dyed a deep shade of royal blue. " +
        "It feels dry and pleasant.\n";
}


/*
 * Function name: init
 * Description  : add player verbs
 */
public void
init()
{
    ::init();
    add_action(do_dry,  "dry");
    add_action(do_snap, "snap");
    add_action(do_snap, "whip");
}


/*
 * Function name: do_dry
 * Description  : handle attempts to dry off
 * Arguments    : string str -- whatever the player typed
 * Returns      : 1 on success, 0 on failure
 */
public int
do_dry(string str)
{
    object tp = TP;

    if (!strlen(str) ||
      (str != "me" && str != "myself" && str != "off" &&
      LOW(str) != tp->query_real_name()))
    {
        NF("Dry whom? Yourself?\n");
        return 0;
    }

    if (!tp->query_prop(WET))
    {
        write("You are not wet.\n");
        return 1;
    }

    if (Wet)
    {
        NF("This towel is too wet to be useful.\n");
        return 0;
    }

    tp->remove_prop(WET);
    write("You dry yourself off with the plush blue towel.\n");
    say(QCTNAME(TP) + " dries " + OBJECTIVE(TP) + "self off with the " +
        "plush blue towel.\n");
    Wet = 1;

    if (!Dry_alarm_id)
        Dry_alarm_id = set_alarm(150.0, 0.0, "dry_towel");

    return 1;
}


/*
 * Function name: dry_towel
 * Description  : reset towel state to dry
 */
public void
dry_towel()
{
    Wet = 0;
    Dry_alarm_id = 0;
}


/*
 * Function name: do_snap
 * Description  : handle attempts to snap towel
 * Arguments    : string str -- whatever the player typed
 * Returns      : 1 on success, 0 on failure
 */
public int
do_snap(string str)
{
    object *who, tp = TP, ob;
    string where, tmpstr, vb = QVB;

    /* make two calls to parse_command to avoid bug */
    if (!strlen(str) ||
      (!parse_command(LOW(str), ({ TO }), "%o 'at'  %s", ob, tmpstr) &&
      !parse_command(LOW(str), ({ TO }), "%s 'with'  %o", tmpstr, ob)))
    {
        NF(CAP(vb)+" towel at whom?\n");
        return 0;
    }

    if (!parse_command(tmpstr, all_inventory(ENV(tp)), "%l", who) ||
      !sizeof(who = NORMAL_ACCESS(who, 0, 0)))
    {
        NF(CAP(vb)+" towel at whom?\n");
        return 0;
    }

    if (!Wet)
    {
        write("Nah, this towel isn't wet enough.\n");
        return 1;
    }

    if (random(tp->query_stat(SS_DEX)) >
      (random(who[0]->query_stat(SS_DEX) + who[0]->query_skill(SS_ACROBAT))))
    {
        where = one_of_list(BODY_PARTS);
        write("You " + vb + " your wet towel at " +
            who[0]->query_the_name(tp) + ". The end of the towel " + vb +
            "s at " + POSSESSIVE(who[0]) + " " + where + "!\n");
        who[0]->catch_tell("You scream as " + tp->query_the_name(who[0]) +
            " " + vb + "s " + POSSESSIVE(tp) + " wet towel at your " +
            where + "!\n");
        say(QCTNAME(tp) + " " + vb + "s " + POSSESSIVE(tp) + " wet towel " +
            "at " + QTPNAME(who[0]) + " " + where + "!\n", ({ tp, who[0] }));
        who[0]->command("$scream");
        who[0]->reduce_hit_point(random(5) + 5);
        return 1;
    }

    who[0]->catch_tell("You hear a snapping sound and realize that " +
        tp->query_the_name(who[0]) + " tried to " + vb + " you with " +
        POSSESSIVE(tp) + " wet towel!\n");
    write("You try to " + vb + " your wet towel at " +
        who[0]->query_the_name(tp) + ", but miss!\n");
    say(QCTNAME(tp) + " " + vb + "s " + POSSESSIVE(tp) + " wet towel at " +
        QTNAME(who[0]) + ", but misses.\n", ({ tp, who[0] }));
    return 1;
}

public int
query_wet()
{
    return Wet;
}
