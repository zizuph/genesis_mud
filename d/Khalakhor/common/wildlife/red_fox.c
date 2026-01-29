/* File         : /d/Khalakhor/common/wildlife/red_fox.c
 * Creator      : Khail@Genesis
 * Copyright:   : Mike Henderson
 * Date         : July 14, 1997
 * Purpose      : A fox npc.
 * Related Files: /d/Khalakhor/std/npc/wildlife.c
 * Comments     : Just a little fox.
 * Modifications: Teth - March 13, 1999 - converted to
 *                inherit Khalakhor's /std/wildlife, added
 *                skin leftover
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Khalakhor/std/npc/wildlife";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <language.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include "/d/Khalakhor/sys/terrains.h"

#define A_BITE 0

#define H_HEAD 0
#define H_BODY 1
#define H_TAIL 2
#define H_RARM 3
#define H_LARM 4
#define H_RLEG 5
#define H_LLEG 6

public string terrain_dash();
public void setup_acts();
public void setup_cacts();

public void
create_khalakhor_wildlife()
{
    set_name("fox");
    set_pname("foxes");
    set_race_name("fox");
    set_adj("sleek");
    add_adj("red");
    set_short("sleek red fox");
    set_pshort("sleek red foxes");
    set_long("Red-furred and sleek, this fox appears to be " +
        "an intelligent and curious animal. It is very similar " +
        "to a dog in appearance, but with a narrow snout, better " +
        "agility, and a thick bushy tail capped in white.\n");

    set_stats(({5 + random(5),
                10 + random(10),
                10 + random(5),
                10 + random(10),
                10 + random(10),
                5 + random(10)}));

    refresh_living();
    set_stuffed(1200);

    set_skill(SS_DEFENCE, 40);
    set_skill(SS_UNARM_COMBAT, 40);

                     
    set_attack_unarmed(A_BITE,     /* Attack id, defined in header. */
                      15,          /* 'weapon tohit' of attack. */
                      15,          /* 'weapon pen' of attack. */
                      W_IMPALE,    /* Damage type, defined in wa_types.h */
                      100,         /* Chance of use per attack. */
                      "jaws");     /* Description of attack. */

    set_hitloc_unarmed(H_HEAD,     /* Hitloc id */
                      25,          /* Ac of hitloc (25 to all dt's) */
                      10,          /* % of attacks to hit this hitloc */
                      "head");     /* Hitloc description. */
    set_hitloc_unarmed(H_BODY, 20, 50, "body");
    set_hitloc_unarmed(H_TAIL, 5,  6, "tail");
    set_hitloc_unarmed(H_RARM, 15, 10, "right foreleg");
    set_hitloc_unarmed(H_LARM, 15, 10, "left foreleg");
    set_hitloc_unarmed(H_RLEG, 15, 7, "right hindleg");
    set_hitloc_unarmed(H_LLEG, 15, 7, "left hindleg");

  /* Fox will move every 10 + random(20) seconds in a random */
  /* direction. */
    set_random_move(20);

    add_prop(CONT_I_WEIGHT, 10000);
    add_prop(CONT_I_VOLUME, 8000);
    add_prop(CONT_I_HEIGHT, 30);

    set_m_in("pounces in");
    set_m_out("pounces");

    setup_acts();
    setup_cacts();

    set_alignment(0);

    add_leftover(SKIN, "pelt", 1, "", 0, 1);
    add_leftover("/std/leftover", "tail", 1, "", 0, 1);
}

/*
 * Function name: setup_acts
 * Description  : Fairly straightforward, just executes a 
 *                series of add_acts to add to the monster.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
setup_acts()
{
  /* Add some actions to the fox. Will be performed */
  /* on average every 20 seconds. */
    set_act_time(20);
    
    add_act("emote stalks around you in a circle, eyeing " +
        "you curiously.");
    add_act("emote yaps playfully at you.");
    add_act("emote looks down suddenly, its rather short " +
        "attention span now focused intently on a small " +
        "bug on the ground.");
    add_act("emote jumps backwards suddenly, startled as " +
        "the bug it was watching started to crawl over its paw.");
    add_act("@@terrain_dash");
}

/*
 * Function name: setup_cacts
 * Description  : Again, quite straightforward, just sets up
 *                the monster's combat actions.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
setup_cacts()
{
    set_cact_time(10);

    add_cact("emote growls at you savagely.");
    add_cact("emote leaps backward and charges in at a " +
        "different angle of attack.");
    add_cact("emote glances around briefly, as if gauging " +
        "its chances of escape.");
}

public string
terrain_dash()
{
    int terrain;
    string how, what;

    terrain = environment(this_object())->query_prop(ROOM_I_TERRAIN_TYPE);

    switch(terrain)
    {

    case(TERRAIN_PLAIN):
    how = "over";
    what = "tuft of grass";
    break;

    case(TERRAIN_MOOR):
    how = "over";
    what = "low rock";
    break;

    case(TERRAIN_RIVERBANK):
    how = "around";
    what = "riverside plant";
    break;

    case(TERRAIN_THICKET):
    how = "around";
    what = "shrub";
    break;

    case(TERRAIN_CONIFEROUS):
    how = "around";
    what = "coniferous tree";
    break;

    case(TERRAIN_MIXEDWOOD):
    how = "around";
    what = "tree";
    break;

    case(TERRAIN_DECIDUOUS):
    how = "around";
    what = "deciduous tree";
    break;

    case(TERRAIN_BUSH):
    how = "around";
    what = "tree";
    break;

    case(TERRAIN_FIELD):
    how = "over";
    what = "small plant";
    break;

    case(TERRAIN_GARDEN):
    how = "over";
    what = "small plant";
    break;

    default:
    how = "over";
    what = "small rock";
    break;
    }

    return("emote dashes behind a " + what + " and peers " +
        "out " + how + " it at you playfully.");
}
