/* File         : /d/Khalakhor/common/wildlife/gull.c
 * Creator      : Teth@Genesis
 * Copyright:   : Daniel Mosquin
 * Date         : December 8, 1997
 * Purpose      : A gull npc - it is used for a quest item
 * Related Files: /d/Khalakhor/std/npc/bird.c
 * Comments     : 
 * Modifications: Zima - March 10, 1998 - converted to accept "feed
 *                <fish> to seagull, causing the gull to relieve himself
 *                of droppings used to make saltpeter for the kirk
 *                incense tour
 *                Teth - March 14, 1999 - converted to
 *                inherit Khalakhor's /std/bird
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Khalakhor/std/npc/bird";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <language.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include "/d/Khalakhor/sys/properties.h"
#include "/d/Khalakhor/sys/terrains.h"

#define  BIRDOO        "/d/Khalakhor/guilds/sean-rhian/objects/birdoo"
#define  ANI_HANDL_REQ 10
#define  DOO_DELAY     30.0

#define A_PECK 0

#define H_HEAD 0
#define H_BODY 1
#define H_LWING 2
#define H_RWING 3

public void setup_acts();
public void setup_cacts();

string fly;

public void
create_khalakhor_bird()
{
    set_name("gull");
    add_name(({"seabird","seagull"}));
    set_pname("gulls");
    add_pname(({"seabirds","seagulls"}));
    set_adj("sea");
    set_short("sea gull");
    set_pshort("sea gulls");
    set_race_name("gull");
    set_long("@@my_long");

    set_m_in("cockily waddles in");
    set_m_out("cockily waddles");

    set_stats(({5 + random(2),
                10 + random(5),
                2 + random(3),
                4,
                4,
                6}));

    set_alignment(0);

    refresh_living();
    set_stuffed(1000);

    set_skill(SS_UNARM_COMBAT, 40);
    set_skill(SS_DEFENCE, 40);

    add_prop(CONT_I_VOLUME,2210);
    add_prop(CONT_I_WEIGHT,2235);
    add_prop(CONT_I_HEIGHT, 40);

    add_leftover(FEATHER, "feather", random(30) + 1, "", 0, 0);

    set_attack_unarmed(A_PECK, 3, 4, W_IMPALE, 100, "beak");

    set_hitloc_unarmed(H_HEAD, 2, 20, "head");
    set_hitloc_unarmed(H_BODY, 2, 40, "body");
    set_hitloc_unarmed(H_LWING, 2, 20, "left wing");
    set_hitloc_unarmed(H_RWING, 2, 20, "right wing");

    fly = "";

    set_random_move(100);

    setup_acts();
    setup_cacts();
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

    add_act("@@do_fly");
    add_act("@@do_land");
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

public string
my_long()
{
    return "Commonly found near piers and seashores, the gull " +
      "is a ravenous scavenger. It can occasionally be found in other " +
      "environments. Its body is white, while its wings and back are a " +
      "slate grey. A red ring of colour encircles the tip of its yellow " +
      "beak." + fly + "\n";
}

public string
do_fly()
{
    if ((this_object()->query_attack()) ||
      (this_object()->query_prop(LIVE_I_FLYING)))
    {
        return "";
    }
    command("emote launches into the air, after a few awkward flaps.");
    command("emote emits a cry: SCRAWK!!");
    add_prop(LIVE_I_FLYING, 1);
    add_prop(OBJ_M_NO_ATTACK, "The gull is flying too far overhead " +
      "for you to attack.\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, "The gull is flying too far " +
      "overhead for you to attack.\n");
    set_m_in("glides in");
    set_m_out("glides");
    fly = " It is flying overhead.";
    set_short("sea gull, flying overhead");
    set_pshort("sea gulls, flying overhead");
    return "";
}

public string
do_land()
{
    int terrain;

    if (!(this_object()->query_prop(LIVE_I_FLYING)))
    {
        return "";
    }
    set_short("sea gull");
    set_pshort("sea gulls");
    command("emote glides down, flares briefly, then lands.");
    command("emote settles its wings against its body.");
    remove_prop(LIVE_I_FLYING);
    remove_prop(OBJ_M_NO_ATTACK);
    remove_prop(OBJ_M_NO_MAGIC_ATTACK);
    set_m_in("cockily waddles in");
    set_m_out("cockily waddles");

    terrain = environment(this_object())->query_prop(ROOM_I_TERRAIN_TYPE);

    switch (terrain)
        {
        case(TERRAIN_PIER):
        fly = " It is waddling on the pier.";
        break;

        default:
        fly = " It is waddling on the ground.";
        break;
        }

    return "";
}

/*
 * Function name: do_doo
 * Description  : seagull drops his droppings
 */
public void
do_doo()
{
    object doo=clone_object(BIRDOO);
    if (this_object()->query_prop(LIVE_I_FLYING))
    {
        command("emote squawks loudly and lets loose some droppings!");
        tell_room(environment(this_object()),"The droppings hit the " +
          "ground right next to your feet!\n");
    }
    else
    {
        command("emote squawks and raises its rear tail feathers up.");
        command("emote relieves itself on the ground and waddles around.");
    }
    doo->move(environment(this_object()));
}

/*
 * Function name: do_feed
 * Description  : added action allows player to feed gull, though
 *                he only eats fish. A while after eating, he'll
 *                "drop" his saltpeter-laden treasure ;)
 * Arguments    : cmd - string player entered with command "feed"
 * Returns      : 0 - command didn't match - 1 command matches
 */
public int
do_feed(string cmd)
{
    int rc;
    object food;
    string fshort;

    // check if command given correctly
    notify_fail("Feed what to the seagull?\n");
    if (!stringp(cmd)) return 0;
    rc = parse_command(cmd,all_inventory(TP),
      "%o 'to' [the] 'gull' / 'seagull' / 'bird'", food);
    if (!rc) return 0;

    // check that food is fish
    fshort = food->query_short();
    if (!(food->id("fish")))
        write("The seagull doesn't seem interested in what you offer.\n");

    // check that the gull isn't afraid of the player
    else if ((TP->query_skill(SS_ANI_HANDL)) < ANI_HANDL_REQ)
    {
        if (TO->query_prop(LIVE_I_FLYING))
        {
            write("The seagull swoops over you nervously and flies back up.\n");
            tell_room(environment(TO),"A seagull swoops over "+QTNAME(TP)+
              "nervously and flies back up.\n",TP);
        }
        else
        {
            command("emote squawks alarmedly.");
            do_fly();
        }
    }

    // OK, player is offering fish and gull isn't afraid, so do feeding
    else
    {
        if (TO->query_prop(LIVE_I_FLYING))
        {
            write("The seagull swoops down and snatches the "+ fshort+
              " from your hand.\n");
            tell_room(ENV(TO),"A seagull swoops down and snatches a "+
              fshort+" from the hand of "+QTNAME(TP)+".\n",TP);
        }
        else
        {
            write("You feed the "+fshort+" to the seagull.\n");
            tell_room(ENV(TO),QCTNAME(TP)+" feeds the seagull "+ fshort+".\n",TP);
            command("emote gulps the "+fshort+" down greedily.");
        }
        if (food->query_prop(HEAP_I_IS))
            food->set_heap_size((food->num_heap())-1);
        else
            food->remove_object();
        set_alarm(DOO_DELAY,0.0,&do_doo());
    }
    return 1;
}

/*
 * init_living - MASK to add_action
 */
public void
init_living()
{
    ::init_living();
    add_action(&do_feed(),"feed");
}
