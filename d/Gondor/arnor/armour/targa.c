/*  Shield
 *  Coded by Tigerlily, April 10, 2005
 *
 *  Modifications:
 *     Toby, 2006-12-05:
 *         Fixed runtime error. Removed QTNAME from tp->catch_tell
 *         and put query_the_name in its place as it should be.
 * 
 *     Toby, 2007-02-13:
 *         Removed hit_loc legs. Its a round shield!
 *         And alos now it complies to the rules... ^^
 *
 *     Toby, 2007-02-13:
 *         Fixed with set_am and the weight.
 *         Upped volume to 1500 since its bulky.
 */

inherit "/std/armour";
inherit "/lib/keep.c";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#include "/d/Gondor/defs.h"

int ac = 45;

void
create_armour()
{
    set_name("shield");
    add_name("targa");
    set_pname(({"shields", "targas"}));
    set_adj(({"round", "spiked" }));
    set_short("silver spiked targa");
    set_long("The targa is a large round shield that can be worn on " +
        "either arm. Tooled silver covers the convex side, and it is " +
        "decorated with swirling shapes that remind you of " +
        "cold mountain winds in frozen fog. The inner side is " +
        "covered in leather, and soft doeskin makes a comfortable " +
        "cushion for the arm. The spike that protrudes outward from " +
        "its center is sharp and quite deadly.\n");

    set_default_armour(ac, A_SHIELD, ({ -2, 1, 1 }), 0);
    set_keep(1);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(ac-5, A_SHIELD)); 
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ac));
}

int *
query_shield_slots()
{
    return (::query_shield_slots() + ({ A_BODY }) );
}

varargs int
got_hit(int hid, int ph, object att, int dt, int dam)
{
    object tp = query_worn();
    string * locations = ({"face", "right arm", "left arm",
        "groin", "head", "chest", "guts", "left armpit", 
        "right thigh", "left thigh", "neck", });
    string location = locations[random(sizeof(locations))];
    string * attacks = ({"impales", "stabs", "slashes",
        "cuts", "jabs", "skewers", });
    string attack = attacks[random(sizeof(attacks))];

    int points = 50 + random(100);

    if (random(100) > 80 && objectp(tp))
    {
        tp->catch_msg("The spike in the targa " + attack + " " +
            att->query_the_name(tp) + " in the " + location + " as you fend " +
            "off " + att->query_possessive() + " attack!\n");
        tell_room(environment(tp), "The spike in the targa " + attack +
            " " + QTNAME(att) + " in the " + location + " as " +
            QTNAME(tp) + " fends off " + att->query_possessive()+
            " attack!\n", ({tp, att}));
        att->heal_hp(-random(points));
        att->catch_msg("You are wounded in the " + location + 
            " by the spike on " + QTNAME(tp) + "'s targa as " + 
            tp->query_pronoun() + " fends off " + 
            "your attack!\n");
    }
    return (::got_hit(hid, ph, att, dt, dam));
}

/*

    Commented out this section as it masks out item expiration.
    Not sure why this was included in the first place? A.K (April 2020)

public string
query_recover()
{
    return MASTER + ":" + query_keep_recover();
}

public void
init_recover(string arg)
{
    init_keep_recover(arg);
}
*/
