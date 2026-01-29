/* File         : /d/Khalakhor/common/wildlife/red_deer.c
 * Creator      : Khail@Genesis
 * Copyright:   : Mike Henderson
 * Date         : July 15, 1997
 * Purpose      : A deer npc.
 * Related Files: /d/Khalakhor/std/npc/wildlife.c
 * Comments     : Just a deer.
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

#define A_ANTLER 0
#define A_RHOOF  1
#define A_LHOOF  2

#define H_HEAD 0
#define H_BODY 1
#define H_RARM 2
#define H_LARM 3
#define H_RLEG 4
#define H_LLEG 5

public string terrain_nuzzle();
public string terrain_paw();
public void setup_acts();
public void setup_cacts();

public void
create_khalakhor_wildlife()
{
    set_name("deer");
    set_pname("deer");
    set_race_name("deer");
    set_adj("lean");
    add_adj("red");
    set_short("lean red deer");
    set_pshort("lean red deer");
    set_long("Muscled and sinewy, the lean red deer is a large " +
        "animal. Its hide is a deep reddish-brown. Two stocky antlers " +
        "covered in sharp points cap its head.\n");

    set_stats(({50 + random(20),
                40 + random(5),
                40 + random(10),
                10 + random(5),
                10 + random(5),
                5 + random(10)}));

    refresh_living();
    set_stuffed(1200);

    set_skill(SS_DEFENCE, 40);
    set_skill(SS_UNARM_COMBAT, 40);

                     
    set_attack_unarmed(A_ANTLER,   /* Attack id, defined in header. */
                      20,          /* 'weapon tohit' of attack. */
                      30,          /* 'weapon pen' of attack. */
                      W_IMPALE,    /* Damage type, defined in wa_types.h */
                      40,          /* Chance of use per attack. */
                      "antlers");  /* Description of attack. */
    set_attack_unarmed(A_RHOOF, 25, 20, W_BLUDGEON, 30, "right hoof");
    set_attack_unarmed(A_LHOOF, 25, 20, W_BLUDGEON, 30, "left hoof");

    set_hitloc_unarmed(H_HEAD,     /* Hitloc id */
                      35,          /* Ac of hitloc (25 to all dt's) */
                      10,          /* % of attacks to hit this hitloc */
                      "head");     /* Hitloc description. */
    set_hitloc_unarmed(H_BODY, 30, 50, "body");
    set_hitloc_unarmed(H_RARM, 15, 10, "right foreleg");
    set_hitloc_unarmed(H_LARM, 15, 10, "left foreleg");
    set_hitloc_unarmed(H_RLEG, 15, 7, "right hindleg");
    set_hitloc_unarmed(H_LLEG, 15, 7, "left hindleg");

  /* Npc will move every 10 + random(20) seconds in a random */
  /* direction. */
    set_random_move(20);

    setup_acts();
    setup_cacts();

    set_alignment(0);

    set_m_in("stalks in");
    set_m_out("stalks");

    add_prop(CONT_I_WEIGHT, 140000);
    add_prop(CONT_I_VOLUME, 100000);
    add_prop(CONT_I_HEIGHT, 200);

    add_leftover(SKIN, "hide", 1, "", 0, 1);
    add_leftover(HORN, "antler", 2, "", 1, 1);
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
    
    add_act("emote glances at you briefly, then seems " +
        "to ignore your presence entirely.");
    add_act("@@terrain_nuzzle");
    add_act("@@terrain_paw");
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

    add_cact("emote rears back, flailing the hooves on its " +
        "forelegs.");
    add_cact("emote flicks its head, its antlers whistling " +
        "through the air.");
}

public string
terrain_nuzzle()
{
    int terrain;
    string loc, plant;

    terrain = environment(this_object())->query_prop(ROOM_I_TERRAIN_TYPE);

    switch(terrain)
    {
    case(TERRAIN_PLAIN):
    loc = "plains";
    plant = "grass on";
    break;

    case(TERRAIN_MOOR):
    loc = "moor";
    plant = "lichens on";
    break;

    case(TERRAIN_HILL):
    loc = "hillside";
    plant = "herbs on";
    break;

    case(TERRAIN_RIVERBANK):
    loc = "riverbank";
    plant = "plants on";
    break;

    case(TERRAIN_THICKET):
    loc = "thicket";
    plant = "herbs in";
    break;

    case(TERRAIN_CONIFEROUS):
    loc = "coniferous forest";
    plant = "herbs in";
    break;

    case(TERRAIN_MIXEDWOOD):
    loc = "mixed woods forest";
    plant = "herbs in";
    break;

    case(TERRAIN_DECIDUOUS):
    loc = "deciduous forest";
    plant = "herbs in";
    break;

    case(TERRAIN_BUSH):
    loc = "bush";
    plant = "herbs in";
    break;

    case(TERRAIN_FIELD):
    loc = "field";
    plant = "plants in";
    break;

    case(TERRAIN_GARDEN):
    loc = "garden";
    plant = "herbs in";
    break;

    default:
    loc = "ground";
    plant = "plants on";
    break;
    }

    return("emote nuzzles the " + plant + " the " + loc +
           ", in search of something edible.");
}

public string
terrain_paw()
{
    int terrain;
    string loc;

    terrain = environment(this_object())->query_prop(ROOM_I_TERRAIN_TYPE);

    switch(terrain)
    {
    case(TERRAIN_PLAIN):
    loc = "rich soil of the plains";
    break;

    case(TERRAIN_MOOR):
    loc = "hard rock of the moors";
    break;

    case(TERRAIN_RIVERBANK):
    loc = "soft soil of the riverbank";
    break;

    case(TERRAIN_THICKET):
    loc = "hard soil of the thicket";
    break;

    case(TERRAIN_CONIFEROUS):
    loc = "hard soil of the coniferous forest";
    break;

    case(TERRAIN_MIXEDWOOD):
    loc = "rich soil of the mixed woods forest";
    break;

    case(TERRAIN_DECIDUOUS):
    loc = "rich soil of the deciduous forest";
    break;

    case(TERRAIN_BUSH):
    loc = "soft soil of the bush";
    break;

    case(TERRAIN_FIELD):
    loc = "loose soil of the field";
    break;

    case(TERRAIN_GARDEN):
    loc = "rich soil of the garden";
    break;

    default:
    loc = "ground";
    break;
    }

    return("emote paws at the " + loc + " with a hoof.");
}

