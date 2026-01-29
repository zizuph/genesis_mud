/* creatures for Galaith inisi
 * Created by Damaris 12/Y2K
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

#define A_RCLAW  1
#define A_LCLAW  2

#define H_HEAD 0
#define H_BODY 1
#define H_RARM 2
#define H_LARM 3

private string query_creature_one();
private string query_creature_two();
private string query_creature_three();
private string query_creature_name();

string _ADJ = query_creature_one();
string __ADJ = query_creature_two();
string ___ADJ = query_creature_three();
string CREATURE = query_creature_name();

public string terrain_nuzzle();
public string terrain_claw();
public void setup_acts();
public void setup_cacts();

public void
create_khalakhor_wildlife()
{
    set_name( CREATURE );
    set_race_name( CREATURE );
    set_short(""+_ADJ+" "+ __ADJ+" "+ CREATURE+"");
    set_adj( _ADJ  );
    add_adj( __ADJ );
    add_adj(___ADJ);
    set_gender(G_MALE);
    set_long("This is a " + short() + ".\n"+
      "He has piercing "+ ___ADJ+" eyes.\n"+
      "He has large sharp claws.\n"+
      "He looks vicious.\n");    
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

                     
    set_attack_unarmed(A_RCLAW, 25, 20, W_BLUDGEON, 30, "right claw");
    set_attack_unarmed(A_LCLAW, 25, 20, W_BLUDGEON, 30, "left claw");

    set_hitloc_unarmed(H_HEAD,     /* Hitloc id */
                      35,          /* Ac of hitloc (25 to all dt's) */
                      10,          /* % of attacks to hit this hitloc */
                      "head");     /* Hitloc description. */
    set_hitloc_unarmed(H_BODY, 30, 50, "body");
    set_hitloc_unarmed(H_RARM, 15, 10, "right foreleg");
    set_hitloc_unarmed(H_LARM, 15, 10, "left foreleg");

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

    add_leftover(SKIN, "hide", 2, "", 0, 1);
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
    add_act("@@terrain_claw");
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

    add_cact("emote rears back, flailing his paws wildly.");

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
terrain_claw()
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

    return("emote paws at the " + loc + " with a claw.");
}

private string
query_creature_one()
{
  string *adjectives = ({
        "sleek", "powerful", "sturdy", "muscular", "brawny", "formidable",
        "ferocious", "mighty", "fierce", "strong", "forceful", "intense",
        "vigorous", "savage"
                        });

  return adjectives[random(sizeof(adjectives))];
}

private string
query_creature_two()
{
  string *adjectives = ({
        "black", "gold", "white", "red", "tan",
                        });

  return adjectives[random(sizeof(adjectives))];
}

private string
query_creature_three()
{
  string *adjectives = ({
        "black", "gold", "red",
                        });

  return adjectives[random(sizeof(adjectives))];
}

private string
query_creature_name()
{
  string *names = ({
        "panther", "bear", "cougar", "tiger", 
                   });

  return names[random(sizeof(names))];
}
