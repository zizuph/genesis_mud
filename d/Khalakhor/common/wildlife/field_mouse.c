/* File         : /d/Khalakhor/common/wildlife/mouse.c
 * Creator      : Khail@Genesis
 * Copyright:   : Mike Henderson
 * Date         : July 15, 1997
 * Purpose      : A mouse npc.
 * Related Files: /d/Khalakhor/std/npc/wildlife.c
 * Comments     : Just a mouse.
 * Modifications: Teth - March 13, 1999 - converted to
 *                inherit Khalakhor's /std/wildlife
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
#define H_RARM 2
#define H_LARM 3
#define H_RLEG 4
#define H_LLEG 5
#define H_TAIL 6

public string terrain_vanish();
public void setup_acts();
public void setup_cacts();

void
create_khalakhor_wildlife()
{
    set_name("mouse");
    set_pname("mice");
    add_name("rodent");
    add_pname("rodents");
    set_race_name("mouse");
    set_adj("brown");
    add_adj("field");
    set_short("brown field mouse");
    set_pshort("brown field mice");
    set_long("Small enough to fit in the palm of your hand, " +
        "the brown field mouse poses no threat to anyone. " +
        "A long tail increases the length of the mouse by half.\n");

    set_stats(({2 + random(2),
                10 + random(5),
                3 + random(3),
                5,
                5,
                3}));

    refresh_living();
    set_stuffed(1200);

    set_skill(SS_DEFENCE, 40);
    set_skill(SS_UNARM_COMBAT, 40);
    set_skill(SS_SNEAK, 30);
    set_skill(SS_HIDE, 30);
                     
    set_attack_unarmed(A_BITE,     /* Attack id, defined in header. */
                      10,          /* 'weapon tohit' of attack. */
                      5,           /* 'weapon pen' of attack. */
                      W_IMPALE,    /* Damage type, defined in wa_types.h */
                      100,         /* Chance of use per attack. */
                      "tiny teeth"); /* Description of attack. */

    set_hitloc_unarmed(H_HEAD,     /* Hitloc id */
                      5,          /* Ac of hitloc */
                      10,          /* % of attacks to hit this hitloc */
                      "head");     /* Hitloc description. */
    set_hitloc_unarmed(H_BODY, 7, 50, "body");
    set_hitloc_unarmed(H_RARM, 3, 10, "right foreleg");
    set_hitloc_unarmed(H_LARM, 3, 10, "left foreleg");
    set_hitloc_unarmed(H_RLEG, 2, 7, "right hindleg");
    set_hitloc_unarmed(H_LLEG, 2, 7, "left hindleg");
    set_hitloc_unarmed(H_TAIL, 1, 6, "tail");

  /* Npc will move every 10 + random(20) seconds in a random */
  /* direction. */
    set_random_move(20);  

    setup_acts();
    setup_cacts();

    set_alignment(0);

    set_m_in("skitters in");
    set_m_out("skitters");

    add_prop(CONT_I_WEIGHT, 50);
    add_prop(CONT_I_VOLUME, 20);
    add_prop(CONT_I_HEIGHT, 2);

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
  /* Add some actions to the npc. Will be performed */
  /* on average every 20 seconds. */
    set_act_time(20);
    
    add_act("hide");
    add_act("reveal myself");
    add_act("@@terrain_vanish");
    add_act("emote pauses and sniffs at the air.");
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
}

/*
 * Function name: oke_to_move (MASK)
 * Description  : Called by the domove routines to actually
 *                make monsters wander in a random direction.
 *                It actually returns the command string to
 *                use, so we'll mask it here to return
 *                "sneak <exit>" instead of just "<exit>".
 * Arguments    : exit - String describing the exit command.
 * Returns      : 0 - In combat, so don't go anywhere.
 *                Otherwise string describing the exit command.
 *                For example "sneak east".
 */
mixed
oke_to_move(string exit)
{
    if (query_attack())
        return 0;

  /* 50% chance the npc will sneak. */
    if (!random(2))
        return "sneak " + exit;

    return exit;
}

public string
terrain_vanish()
{
    int terrain;
    string where, where2;

    terrain = environment(this_object())->query_prop(ROOM_I_TERRAIN_TYPE);

    switch(terrain)
    {

    case(TERRAIN_PLAIN):
    where = "beneath a clump of grass";
    where2 = "from the other side";
    break;

    case(TERRAIN_HILL):
    where = "behind a small rock";
    where2 = "from the other side";
    break;

    case(TERRAIN_THICKET):
    where = "behind a small shrub";
    where2 = "from beneath the branches on the other side";
    break;

    case(TERRAIN_FIELD):
    where = "beneath a clump of grass";
    where2 = "from the other side";
    break;

    case(TERRAIN_GARDEN):
    where = "behind a leafy herb";
    where2 = "from the other side";
    break;

    default:
    where = "behind a small bushy plant";
    where2 = "from the other side";
    break;
    }
   
    return ("emote vanishes " + where + " and emerges " + where2 + "."); 

}