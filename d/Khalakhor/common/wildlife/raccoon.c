/* File         : /d/Khalakhor/common/wildlife/raccoon.c
 * Creator      : Khail@Genesis
 * Copyright:   : Mike Henderson
 * Date         : July 15, 1997
 * Purpose      : A raccoon npc.
 * Related Files: /d/Khalakhor/std/npc/wildlife.c
 * Comments     : Just a raccoon.
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

public string terrain_search();
public void setup_acts();
public void setup_cacts();

public void
create_khalakhor_wildlife()
{
    set_name("raccoon");
    set_pname("raccoons");
    set_race_name("raccoon");
    set_adj("fat");
    add_adj("mischievous");
    set_short("fat mischievous raccoon");
    set_pshort("fat mischievous raccoons");
    set_long("With its fur a mixture of shiny brown and grey, this " +
        "raccoon appears healthy. Black rings encircle its thick " +
        "brown tail, while a mask of black fur crosses it face.\n");

    set_stats(({10 + random(5),
                10 + random(5),
                10 + random(5),
                10 + random(5),
                10 + random(5),
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

  /* Npc will move every 10 + random(20) seconds in a random */
  /* direction. */
    set_random_move(20);

    add_prop(CONT_I_WEIGHT, 6000);
    add_prop(CONT_I_VOLUME, 5000);
    add_prop(CONT_I_HEIGHT, 30);

    set_m_in("waddles in");
    set_m_out("waddles");

    setup_acts();
    setup_cacts();

    set_alignment(0);

    add_leftover(SKIN, "fur", 1, "", 0, 1);
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
  /* Add some actions to the npc. Will be performed */
  /* on average every 20 seconds. */
    set_act_time(20);
    
    add_act("emote stares at you intently.");
    add_act("emote pokes around on the ground at something " +
        "momentarily.");
    add_act("emote starts chittering at you.");
    add_act("@@terrain_search");
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
    add_cact("emote flashes its razor sharp teeth " +
        "at you while snarling viciously.");
}

public string
terrain_search()
{
    int terrain;
    string food, where;

    terrain = environment(this_object())->query_prop(ROOM_I_TERRAIN_TYPE);

    switch(terrain)
    {

    case(TERRAIN_PLAIN):
    food = "seeds on";
    where = "ground";
    break;

    case(TERRAIN_HILL):
    food = "insects on";
    where = "ground";
    break;

    case(TERRAIN_LAKESHORE):
    food = "insects near";
    where = "lakeshore";
    break;

    case(TERRAIN_RIVERBANK):
    food = "crayfish near";
    where = "riverbank";
    break;

    case(TERRAIN_FRESHBEACH):
    food = "insects on";
    where = "beach";
    break;

    case(TERRAIN_MARSH):
    food = "bugs in";
    where = "reeds";
    break;

    case(TERRAIN_THICKET):
    food = "insects on";
    where = "shrubs";
    break;

    case(TERRAIN_BUSH):
    food = "insects on";
    where = "trees";
    break;

    case(TERRAIN_MIXEDWOOD):
    food = "grubs behind";
    where = "bark of some trees";
    break;

    case(TERRAIN_CONIFEROUS):
    food = "grubs behind";
    where = "bark of some coniferous trees";
    break;

    case(TERRAIN_DECIDUOUS):
    food = "caterpillars on";
    where = "bark of some deciduous trees";
    break;

    case(TERRAIN_GARDEN):
    food = "juicy vegetables in";
    where = "garden";
    break;

    default:
    food = "food on";
    where = "ground";
    break;
    }
    
    return ("emote searches for " + food + " the " + where + "."); 

}
