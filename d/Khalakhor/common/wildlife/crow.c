/* File         : /d/Khalakhor/common/wildlife/crow.c
 * Creator      : Khail@Genesis
 * Copyright:   : Mike Henderson
 * Date         : July 15, 1997
 * Purpose      : A crow npc.
 * Related Files: /d/Khalakhor/std/npc/bird.c
 * Comments     : 
 * Modifications: Teth - March 14, 1999 - converted to
 *                inherit Khalakhor's /std/bird
 *                Cotillion - 2005-06-18
 *                - Made it tear stuff from nearby corpses.
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Khalakhor/std/npc/bird";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <language.h>
#include <files.h>
#include <filter_funs.h>
#include <stdproperties.h>

#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include "/d/Khalakhor/sys/properties.h"
#include "/d/Khalakhor/sys/terrains.h"

#define A_BEAK 0

#define H_HEAD  0
#define H_BODY  1
#define H_RWING 2
#define H_LWING 3
#define H_RLEG  4
#define H_LLEG  5

public void setup_acts();
public void setup_cacts();

static string fly;
static object corpse;
static int eat_alarm;

public void
create_khalakhor_bird()
{
    set_name("crow");
    set_pname("crows");
    set_race_name("crow");
    set_adj("large");
    add_adj("black");
    set_short("large black crow");
    set_pshort("large black crows");
    set_long("@@my_long");
    set_stats(({2 + random(2),
                10 + random(5),
                3 + random(3),
                5,
                5,
                3}));

    set_m_in("hops in");
    set_m_out("hops");

    refresh_living();
    set_stuffed(1000);

    set_skill(SS_DEFENCE, 40);
    set_skill(SS_UNARM_COMBAT, 40);
                     
    set_attack_unarmed(A_BEAK,     /* Attack id, defined in header. */
        10,          /* 'weapon tohit' of attack. */
        5,           /* 'weapon pen' of attack. */
        W_IMPALE,    /* Damage type, defined in wa_types.h */
        100,         /* Chance of use per attack. */
        "beak"); /* Description of attack. */

    set_hitloc_unarmed(H_HEAD,     /* Hitloc id */
        5,          /* Ac of hitloc */
        10,          /* % of attacks to hit this hitloc */
        "head");     /* Hitloc description. */
    set_hitloc_unarmed(H_BODY, 7, 50, "body");
    set_hitloc_unarmed(H_RWING, 3, 10, "right wing");
    set_hitloc_unarmed(H_LWING, 3, 10, "left wing");
    set_hitloc_unarmed(H_RLEG, 2, 7, "right hindleg");
    set_hitloc_unarmed(H_LLEG, 2, 7, "left hindleg");

    /* Npc will move every 10 + random(20) seconds in a random */
    /* direction. */
    set_random_move(20);

    setup_acts();
    setup_cacts();

    set_alignment(0);

    add_prop(CONT_I_WEIGHT, 1200);
    add_prop(CONT_I_VOLUME, 1300);
    add_prop(CONT_I_HEIGHT, 35);

    add_leftover(FEATHER, "feather", random(30)+1, "", 0, 0);

    fly = "";
}

public string
my_long()
{
    return "A scavenger, the crow is a medium-sized bird which " +
        "enjoys a variety of food, both living and dead. Covered in " +
        "black feathers, it also has a black beak and dark eyes." +
        fly + "\n";
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
    
    add_act("@@do_fly@@");
    add_act("@@do_land@@");
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

public int
do_fly()
{
    if ((this_object()->query_attack()) ||
        (this_object()->query_prop(LIVE_I_FLYING)))
    {
        return 0;
    }
    command("emote hops into the air, quickly flapping its wings.");
    command("emote emits a cry: CAW! CAW!");
    add_prop(LIVE_I_FLYING, 1);
    add_prop(OBJ_M_NO_ATTACK, "The crow is flying too far overhead " +
        "for you to attack.\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, "The crow is flying too far " +
        "overhead for you to attack.\n");
    set_m_in("flies in");
    set_m_out("flies");
    fly = " It is flying overhead.";
    set_short("large black crow, flying overhead");
    set_pshort("large black crows, flying overhead");
    return 1;
}

public varargs int
do_land(object ob)
{
    int terrain;

    if (!(this_object()->query_prop(LIVE_I_FLYING)))
    {
        return 0;
    }
    
    set_short("large black crow");
    set_pshort("large black crows");

    if (!objectp(ob)) {
        command("emote glides down, then hops as it lands.");
        command("emote tucks its wings against its body.");
    } else {
        tell_room(environment(),
            QCTNAME(this_object()) + " glides down and lands on the "
            + QSHORT(corpse) + ".\n");
    }
    
    remove_prop(LIVE_I_FLYING);
    remove_prop(OBJ_M_NO_ATTACK);
    remove_prop(OBJ_M_NO_MAGIC_ATTACK);
    set_m_in("hops in");
    set_m_out("hops");

    terrain = environment(this_object())->query_prop(ROOM_I_TERRAIN_TYPE);

    switch (terrain)
    {
    case(TERRAIN_FIELD):
        fly = " It is hopping around the field.";
        break;

    default:
        fly = " It is hopping around on the ground.";
        break;
    }

    return 1;
}

void
eat_corpse()
{
    mixed leftover;
    object lobj;
    
    if (!objectp(corpse) && !objectp(corpse = present("corpse", environment())))
    {
        do_fly();
        remove_alarm(eat_alarm);
        return;
    }

    if (this_object()->query_prop(LIVE_I_FLYING))
    {
        do_land(corpse);
        return;
    }
    
    if (IS_LEFTOVER_OBJECT(corpse))
    {
        tell_room(environment(this_object()),
            QCTNAME(this_object()) + " hacks away at the " +
            QSHORT(corpse) + ".\n");
        corpse->move(this_object());
        command("eat all");
        corpse->remove_object();
        return;
    }

    if (!IS_CORPSE_OBJECT(corpse))
    {
        corpse = 0;
        return;
    }

    
    setuid();
    seteuid(getuid());

    switch (random(2))
    {
    case 0:
        if (leftover = corpse->query_leftover())
        {
            leftover = leftover[random(sizeof(leftover)-1)];
            
            if (random(2))
            {
                lobj = clone_object(leftover[0]);
                lobj->leftover_init(leftover[1],
                    corpse->query_prop(CORPSE_S_RACE));
                if (!lobj->move(environment(this_object())))
                {
                    corpse->remove_leftover(leftover[1]);
                    tell_room(environment(this_object()),
                        QCTNAME(this_object()) + " tears " +
                        LANG_ART(leftover[1]) + " " + leftover[1] + " from the " +
                        QSHORT(corpse) + ".\n");
                    corpse = lobj;
                }
                else
                    lobj->remove_object();

            }
            else
            {
                tell_room(environment(this_object()),
                    QCTNAME(this_object()) + " tries to tear " +
                    LANG_ADDART(leftover[1]) + " from the " +
                    QSHORT(corpse) + ".\n");
            }
        }
        else
        {
            say(QCTNAME(this_object()) + " seems to be searching for something.\n");
        }
        
    case 1:
        say(QCTNAME(this_object()) + " tries to tear a piece of skin from the " +
            QSHORT(corpse)  + ".\n");
        break;
        
    }
}

void
enter_env(object dest, object from)
{
    ::enter_env(dest, from);
    
    if (!get_alarm(eat_alarm))
        eat_alarm = set_alarm(30.0 * rnd(), 15.0 + 30.0 * rnd(), &eat_corpse());    
}

mixed 
oke_to_move(string exit)
{
    if (objectp(corpse) && environment(corpse) == environment())
        return 0;
    
    return ::oke_to_move(exit);
}
