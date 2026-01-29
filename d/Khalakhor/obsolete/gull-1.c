/* File:          /d/Khalakhor/ship/macdunn/gull.c
 * Creator:       Teth
 * Date:          December 8, 1997
 * Modifications:
 *                Zima (3/10/98): player can "feed <fish> to seagull";
 *                bird will "relieve himself" of droppings from which
 *                saltpeter is extracted for the kirk incense tour.
 *
 *
 * Purpose:       This bird is an npc on the Khalakhor piers.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/open/SHIPLINES
 * Comments:
 */

#pragma save_binary
#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include "local.h"
#include "/d/Khalakhor/sys/properties.h"
#include "/d/Khalakhor/sys/defs.h"
#define  BIRDOO "/d/Khalakhor/guilds/sean-rhian/objects/birdoo"
#define  ANI_HANDL_REQ 10
#define  DOO_DELAY     30.0

#define A_PECK 0
#define A_CLAW 1

#define H_HEAD 0
#define H_BODY 1
#define H_WING 2

string fly;

public void
create_creature()
{
    int i;

    set_name("gull");
    add_name("testgull");
    add_name(({"bird","seabird","seagull"}));
    set_pname("gulls");
    add_pname(({"birds","seabirds","seagulls"}));
    set_adj("sea");
    set_short("sea gull");
    set_pshort("sea gulls");
    set_race_name("bird");
    set_long("@@my_long");
    set_gender(G_NEUTER);

    set_m_in("cockily waddles in");
    set_m_out("cockily waddles");

    for (i=0;i<6;i++)
        set_base_stat(i, 14+random(2));

    set_alignment(0);

    refresh_living();

    set_act_time(7);
    add_act("@@do_fly");
    add_act("@@do_land");

    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(CONT_I_VOLUME,2210);
    add_prop(CONT_I_WEIGHT,2235);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE,1);

    add_leftover("/std/leftover","feather",(random(40)) + 1,0,0,0);
    add_leftover("/std/leftover","beak",1,0,0,0);

    set_attack_unarmed(A_PECK, 3, 4, W_IMPALE, 60, "beak");
    set_attack_unarmed(A_CLAW, 4, 3, W_IMPALE, 40, "claw");

    set_hitloc_unarmed(H_HEAD, 2, 20, "head");
    set_hitloc_unarmed(H_BODY, 2, 40, "body");
    set_hitloc_unarmed(H_WING, 2, 40, "wing");

    fly = "It is waddling on the pier.";

    set_random_move(100);
    set_restrain_path(MACDUNN_DIR);
    set_monster_home(MACDUNN_DIR + "pier7");
}

public string
my_long()
{
    return "This bird is a gull, a common bird found " +
    "near piers and seashores. Its body is white, while " +
    "its wings and back are slate grey. A red ring of colour " +
    "encircles the tip of its yellow beak. " + fly + "\n";
}

public int
do_fly()
{
    if ((this_object()->query_attack()) ||
      (this_object()->query_prop(LIVE_I_FLYING)))
    {
        return 0;
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
    fly = "It is flying overhead.";
    set_short("sea gull, flying overhead");
    set_pshort("sea gulls, flying overhead");
    return 1;
}

public int
do_land()
{
    if (!(this_object()->query_prop(LIVE_I_FLYING)))
    {
        return 0;
    }
    set_short("sea gull");
    set_pshort("sea gulls");
    command("emote glides to the pier, flares briefly, then lands.");
    command("emote settles its wings against its body.");
    remove_prop(LIVE_I_FLYING);
    remove_prop(OBJ_M_NO_ATTACK);
    remove_prop(OBJ_M_NO_MAGIC_ATTACK);
    set_m_in("cockily waddles in");
    set_m_out("cockily waddles");
    fly = "It is waddling on the pier.";
    return 1;
}

/*
 * Function name: do_doo
 * Description  : seagull drops his droppings
 */
void do_doo()
{
    object doo=clone_object(BIRDOO);
    if (TO->query_prop(LIVE_I_FLYING))
    {
        command("emote squawks loudly and drops a bomb!");
        tell_room(ENV(TO),"The droppings hit the ground right next to "+
          "your feet!\n");
    }
    else
    {
        command("emote squawks and raises his rear tail feathers up.");
        command("emote relieves itself on the ground and waddles around.");
    }
    doo->move(ENV(TO));
}

/*
 * Function name: do_feed
 * Description  : added action allows player to feed gull, though
 *                he only eats fish. A while after eating, he'll
 *                "drop" his saltpeter-laden treasure ;)
 * Arguments    : cmd - string player entered with command "feed"
 * Returns      : 0 - command didn't match - 1 command matches
 */
int do_feed(string cmd)
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
    else if ((TP->query_skill(SS_ANI_HANDL))<ANI_HANDL_REQ)
    {
        if (TO->query_prop(LIVE_I_FLYING))
        {
            write("The seagull swoops over you nervously and flies back up.\n");
            tell_room(ENV(TO),"A seagull swoops over "+QTNAME(TP)+
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
void init_living() {
    ::init_living();
    add_action(&do_feed(),"feed");
}
