/*
 * /d/Gondor/anorien/pelennor/citygate.c
 *
 * Modification history:
 *	29-Oct-98, Gnadnar: add "undead" shout, conform
 *			    to code standards
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/friend_or_foe";
inherit "/d/Gondor/common/lib/binbit";
// inherit "/d/Gondor/minas/lib/archery";


#include <composite.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/rangers/rangers.h"

#define KNIGHT_S_GUILD_NAME "Solamnian Knights"
#define DID_ATTACK_MT_GATES   "_attacked_mt_gate"
#define	LIVE_I_KNOCKED	"_live_i_knocked"
#define DID_VISIT_PELENNOR "_ranger_visited_pelennor"

object  patrol,
    gate,
    other_gate,
    officer,
    *guards;
int     officer_count,  /* how many officers cloned this reset */
        cg_aid,
        ga_aid;

/* prototypes */
public void         create_gondor();
public void         init();
public string       long_func();
public void         reset_room();
public int          filter_enemy(object enemy);
public object       *check_enemies();
public varargs void get_guards_ready(object *enemy);
public string       ranger_title(object pl);
public void         suspicious_to_entry(object pl);
public int          do_knock(string str);
public void         close_gate();
public void         close_gate_to_stop_invaders(object one_enemy);
public void         set_officer_count(int i);
public int          clone_officer();
public void         prepare_guard_attack(object *enemy);
public void         prepare_archer_attack(object *enemy);
public void         guard_attack(object *enemy);
public void         leave_inv(object ob, object to);
public varargs int  query_friend_or_foe(mixed pl);
public void         hook_wagon_depart(object wagon, string where);
public void         hook_wagon_arrive(object wagon, string from);



/* 
 * Function name:   create_gondor
 * Description  :   set up the room
 */
public void 
create_gondor()
{
    FIX_EUID;
    set_name("Minas Tirith Gate");
    set_short("before the Great Gate of Minas Tirith");
    set_long(long_func);

    add_exit((MINAS_DIR + "ingate1"),         "west", 1);
    add_exit((ANO_DIR + "pelennor/nroad1"),  "north", 0);
    add_exit((ANO_DIR + "pelennor/sroad1"),  "south", 0);
    add_exit((ANO_DIR + "pelennor/neroad1"), "northeast", 0);

    gate = clone_object(MINAS_DIR + "obj/tirithgate1");
    gate->move(TO);
    other_gate = gate->query_other_door();

    add_item("battlements",
	BSN("The battlements upon the gatehouse have crenelated walls " +
	    "in front, so that the guards are protected from arrows " +
	    "and other missiles. "));
    add_item("gatehouse",
	BSN("The gatehouse of the Great Gate is a strong stone building " +
	    "protecting this only entrance to the City. On the top are " +
	    "crenelated battlements, and probably a number of guards " +
	    "as well."));
    add_item("guards",
	BSN("None are visible from here; they probably are behind " +
	    "the battlements."));
    add_item( ({ "doors", "door" }),
	BSN("The two doors of the gate are made of strong iron, each " +
	    "held up by a steel post."));
    add_item( ({ "road", "ground" }),
	BSN("Roads lead north, northeast and south from here, "+
    	    "crossing the green fields of Pelennor. "));
    add_item( ({ "post", "posts" }), 
	BSN("These steel posts hold the gates open to allow entry into " +
	    "Minas Tirith. They are very sturdy and can hold the gate " +
	    "easily."));

    reset_room();
    (MINAS_DIR + "wall/sinwall1")->load_me();
    (MINAS_DIR + "wall/ninwall1")->load_me();

} /* create_gondor */


/*
 * Function name:   init
 * Description  :   add the knock verbs
 */
public void
init()
{
    ::init();
    add_action(do_knock, "knock");
    add_action(do_knock, "pound");
} /* init */


/*
 * Function name:   long_func
 * Description  :   VBFC for the room long
 * Returns      :   string -- the description
 */
public string
long_func()
{
    if (gate->query_open())
    {
        return BSN("The Great Gate of Minas Tirith looms to the west. " +
        "Roads lead up to the Gate, crossing the green fields of " +
        "Pelennor from the north, northeast and south. The gate " +
        "is wide open, swung back on posts of steel, seemingly " +
        "allowing entry to the City of Guard to the west.");
    }
    return BSN("The Great Gate of Minas Tirith looms to the west. " +
    "The gate is closed now, blocking the only entry to the " +
    "City of Guard. Roads lead away across the green fields of " +
    "Pelennor, north, northeast and south.");
} /* long_func */


/*
 * Function name:  reset_room
 * Description  :  replenish the patrol if needed,
 *                 move any non-fighting guards back inside
 */
public void
reset_room()
{
    int s;

    if (!patrol) 
    {
	patrol = clone_object(MINAS_DIR + "npc/gondor_leader");
	patrol->set_monster_home(ANO_DIR + "pelennor/citygate");
	patrol->set_restrain_path(({ANO_DIR + "pelennor"}));
	patrol->set_patrol_size(4);
	patrol->arm_me();
	patrol->move_living("away", TO);
    }
    officer_count = 0;
    if (objectp(officer) &&
	ENV(officer) == TO &&
	!officer->query_attack())
    {
	officer->move_living("west through the gate",
	    (MINAS_DIR + "wall/sinwall1"));
    }
    s = sizeof(guards);
    while (s-- > 0)
    {
	if (objectp(guards[s]) &&
	    ENV(guards[s]) == TO &&
	    !guards[s]->query_attack())
	{
	    guards[s]->move_living("west through the gate",
		(MINAS_DIR + "wall/sinwall1"));
	}
    }
} /* reset_room */


/*
 * Function name:	filter_enemy
 * Description	:	filter for MT enemies
 * Arguments	:	object enemy -- the person being considered
 * Returns	:	1 if is an enemy, 0 if not
 */
public int
filter_enemy(object enemy)
{
    return (interactive(enemy) &&
        query_friend_or_foe(enemy) == -1);
} /* filter_enemy */


/*
 * Function name:	check_enemies
 * Description	:	check whether are any enemies in room
 * Returns	:	object * -- an array of enemies
 */
public object *
check_enemies()
{
    return filter(all_inventory(TO), filter_enemy);
} /* check_enemies */


/*
 * Function name:	get_guards_ready
 * Description	:	do the initial prep for guards
 * Arguments	:	object *enemey -- an array of enemies
 */
public varargs void
get_guards_ready(object *enemy)
{
    object	other_room = gate->query_other_room();
    string	undeadstr = "";

    if(!sizeof(enemy))
    {
        enemy = ({ TP });
    }
    if (sizeof(filter(enemy, &->query_prop(LIVE_I_UNDEAD))))
    {
	undeadstr = " It is one of the undead!";
    }
    tell_room(TO,
	BSN("From the top of the walls, someone shouts: Alarm! " +
	    "Enemies at the gate!" + undeadstr));
    tell_room(other_room,
	BSN("From the top of the walls, someone shouts: Alarm! " +
	    "Enemies at the gate!" + undeadstr));
    tell_room(TO,
	BSN("You hear more loud shouts from the top of the walls " +
	    "and on the other side of the gate!"));
    tell_room(other_room,
        BSN("You hear more loud shouts from the top of the walls " +
	    "and on the other side of the gate!"));

    set_alarm((rnd() * 4.0), 0.0, &prepare_guard_attack(enemy));
} /* get_guards_ready */


/*
 * Function name:	ranger_title
 * Description	:	return a ranger's title
 * Arguments	:	object pl -- the ranger
 * Returns	:	string -- the title
 */
public string
ranger_title(object pl)
{
#ifndef NEW_RANGERS_OPEN
    if (pl->query_company() == "the Ranger pupils")
    {
    return "a fresh Ranger";
    }
    if (query_bin_bits(1,18,2,pl) == 2)
    {
    return "the Captain of the Rangers of " + pl->query_company();
    }
    return "a Ranger of " + pl->query_company();
#endif

#ifdef NEW_RANGERS_OPEN
    if (RANGERS_MEMBER(pl))
        return (LANG_ADDART(MANAGER->query_title_name(pl->query_real_name())));
#endif
} /* ranger_title */


/*
 * Function name:	suspicious_to_entry
 * Description	:	handle the msgs for strangers
 * Arguments	:	object pl -- the stranger
 */
public void
suspicious_to_entry(object pl)
{
    tell_room(TO,
	BSN("From the top of the wall, someone shouts: Turn away, " +
	    "stranger! Gondor is at War, and no strangers are welcome " +
	    "in the City now!"));
    tell_room(gate->query_other_room(),
	    BSN("You hear someone shouting someplace above you."));
} /* suspicious_to_entry */


/*
 * Function name:	do_knock
 * Description	:	respond to people knocking on the gate
 * Arguments	:	string str -- whatever the player typed
 * Returns	:	1 if we understand the arg, 0 if not
 */
public int
do_knock(string str)
{
    object	*enemy,
		token;
    string	fname;
    string	vb = QVB;
    int		fof;
  
    if (!strlen(str) ||
	!parse_command(LOW(str), ({ }),
	    "[on] [the] [great] [iron] [city] "+
	    "'gate' / 'gates' / 'citygate' / 'citygates'"))
    {
	NF0(CAP(vb)+" on what?\n");
    }

    TP->reveal_me(1);

    if (gate->query_open())
    {
	write("You " + vb + " on the open gate.\n");
	say(QCTNAME(TP) + " " + vb + "s on the open gate.\n");
	return 1;
    }

    write("You " + vb + " on the great iron gate.\n");
    say(QCTNAME(TP) + " " + vb + "s on the great iron gate.\n");

    enemy = check_enemies();
    fof = query_friend_or_foe(TP);

    if (fof == -1)
    {
        get_guards_ready(enemy);
    }
    else if (fof == 0 &&
	     find_object(CLOCK)->query_war())
    {
	suspicious_to_entry(TP);
    }
    else if (sizeof(enemy))
    {
	tell_room(TO,
	    BSN("From the top of the gatehouse, someone shouts: " +
		"Get away from there, " + TP->query_nonmet_name() + "! " +
		"Enemies are near!"));
	get_guards_ready(enemy);
    }
    else
    {
#ifndef NEW_RANGERS_OPEN
	if (IS_RANGER(TP) &&
        objectp(token = present("ranger_guild_object", TP)) &&
        token->query_worn())
	{
	    fname = ranger_title(TP);
	}
#endif
#ifdef NEW_RANGERS_OPEN
    if (RANGERS_MEMBER(TP) &&
        objectp(token = present("ranger_guild_object", TP)) &&
        token->query_worn())
    {
        fname = ranger_title(TP);
    }
#endif
	else if (IS_DUNADAN(TP))
	{
	    fname = "a Dunadan";
	}
	else if (TP->query_guild_name_occ() == KNIGHT_S_GUILD_NAME)
	{
	    fname = "some knight";
	}
	else
	{
	    fname = "some " + TP->query_race_name();
	}

	tell_room(TO,
	    BSN("From the top of the gatehouse, someone shouts: " +
		"Open the gate, " + fname + " wants to enter!"));
	tell_room(gate->query_other_room(),
	    BSN("From the top of the gatehouse, someone shouts: " +
		"Open the gate, " + fname + " wants to enter!"));

	gate->do_unlock_door("You hear something heavy moving " +
	    "on the other side of the Great Gate.\n");
	other_gate->do_unlock_door("Suddenly, the wooden beam " +
	    "blocking the door starts moving.\n");
	gate->do_open_door("The Great Gate of Minas Tirith opens " +
	    "as the iron doors swing inwards.\n");
	other_gate->do_open_door("The Great Gate of Minas Tirith " +
	    "opens as the iron doors swing inwards.\n");

	cg_aid = set_alarm(10.0, 0.0, close_gate);
	TP->add_prop(LIVE_I_KNOCKED, 1);
    }
    return 1;
} /* do_knock */


/*
 * Function name:	close_gate
 * Description	:	close the gate
 */
public void
close_gate()
{
    remove_alarm(cg_aid);
    cg_aid = 0;
    gate->query_other_room()->close_gate();
} /* close_gate */


/*
 * Function name:	close_gate_to_stop_invaders
 * Description	:	close gate on an enemy
 * Argument	:	object one_enemy -- the person trying to enter
 */
public void
close_gate_to_stop_invaders(object one_enemy)
{
    object *enemy;
    one_enemy->catch_msg("When you try to enter the gate, " +
	"you hear a shout from inside the City.\n");
    tell_room(TO,
	BSN("When " + QTNAME(one_enemy) + " tries to enter the gate, " +
        "you hear a shout from inside the City."), one_enemy);
    tell_room(TO,
	"Someone shouts: Close the gate! Invaders!\n");
    close_gate();
    enemy = ({ one_enemy });
    get_guards_ready(enemy);
} /* close_gate_to_stop_invaders */


public void	set_officer_count(int i)	{ officer_count = i; }

/* 
 * Function name:	clone_officer
 * Description	:	start up a gondor officer
 * Returns	:	int --	1 if officer moved to sinwall1,
 *				0 otherwise (reach limit of officers
 *				  per reset, or officer is busy
 *				  fighting)
 */
int clone_officer()
{
    int    s;

    if (!objectp(officer))
    {
	if (officer_count > 2 ||
	    !random(3))
	{
            return 0;
	}
	else
	{
	    officer = clone_object(MINAS_DIR + "npc/gondor_officer");
	    officer->arm_me();
	    (MINAS_DIR + "wall/sinwall1")->reset_room();
	    officer_count++;
	}
    }
    else
    {
	if (officer->query_attack())
	{
	    return 0;
	}
	tell_room(ENV(officer), QCTNAME(officer) + " leaves.\n");
    }

    officer->move_living("M", (MINAS_DIR + "wall/sinwall1"));
    tell_room((MINAS_DIR + "wall/sinwall1"),
	CAP(LANG_ADDART(officer->query_nonmet_name())) +
	" arrives running!\n");
    officer->command("shout Alarm! Enemies at the gates!");
    officer->command("shout All guards follow me!");
    guards = ENV(officer)->query_guards();
    s = sizeof(guards);
    while (s-- > 0)
    {
	if (objectp(guards[s]))
	{
	    officer->team_join(guards[s]);
	}
    }
    return 1;
} /* clone_officer */


/* 
 * Function name:	prepare_guard_attack
 * Description	:	set alarm to start an attack
 * Arguments	:	object *enemy -- the enemies
 */
public void
prepare_guard_attack(object *enemy)
{
    tell_room(TO,
	"You hear people running and shouting on the other side " +
	"of the gate!\n");
    
    if (clone_officer() && !ga_aid)
    {
	ga_aid = set_alarm((2.0 + (rnd() * 5.0)), 0.0, &guard_attack(enemy));
    }
    
    prepare_archer_attack(enemy);
} /* prepare_guard_attack */


/* 
 * Function name:	prepare_guard_attack
 * Description	:	set alarm to start an attack
 * Arguments	:	object *enemy -- the enemies
 */
public void
prepare_archer_attack(object *enemy)
{
    object *archers;
    
    seteuid(getuid(TO));
    (MINAS_DIR + "wall/battlement1")->load_me();
    archers = (MINAS_DIR + "wall/battlement1")->query_guards();
    archers->attack_ranged_enemies(enemy, TO, "before the gate");
}

/* 
 * Function name:	guard_attack
 * Description	:	attack our enemies
 * Arguments	:	object *enemy -- the enemies
 */
public void
guard_attack(object *enemy)
{
    int		s;
    string	ename;

    remove_alarm(ga_aid);
    ga_aid = 0;

    if (!officer ||
	!(s = sizeof(enemy)))
    {
	return;
    }

    while (s-- > 0)
    {
	if (objectp(enemy[s]) &&
	    ENV(enemy[s]) == TO &&
	    query_friend_or_foe(enemy[s]) == -1) 
	{
      	    break;	/* we have an enemy */
	}
    }

    if (s < 0)
    {
	return;
    }

    officer->command("west");
    officer->command("north");
    officer->command("east");
    officer->command("shout Open the gate!");

    tell_room(TO,
	"The iron doors of the Great Gate swing open. \n");
    tell_room(ENV(officer),
	"The iron doors of the Great Gate swing open. \n");

    officer->move_living("east through the Great Gate", TO);
    officer->command("shout For Gondor and the City!");
    ename = enemy[0]->query_real_name();
    officer->command("kill " + ename);

    s = sizeof(guards);
    while (s-- > 0)
    {
	if (objectp(guards[s]))
	{
	    guards[s]->move_living("east through the gate",TO);
	    guards[s]->command("shout For Gondor!");
	    guards[s]->command("kill " + ename);
	}
    }

    tell_room(TO, "The Great Gate closes again. \n");
    tell_room(gate->query_other_room(), "The Great Gate closes again. \n");

} /* guard_attack */


/*
 * Function name:	leave_inv
 * Description	:	mask parent to close gate after departures
 * Arguments	:	object ob -- the departing object
 *			object to - its destination
 */
public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (living(ob) &&
        gate->query_open())
    {
	remove_alarm(cg_aid);
	cg_aid = set_alarm(1.0, 0.0, close_gate);
    }
} /* leave_inv */

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
#ifndef NEW_RANGERS_OPEN
    if (IS_RANGER(ob))
        ob->add_prop(DID_VISIT_PELENNOR, 1);
#endif
#ifdef NEW_RANGERS_OPEN
    if (RANGERS_MEMBER(ob))
        ob->add_prop(DID_VISIT_PELENNOR, 1);
#endif
}


/*
 * Function name:	query_friend_or_foe
 * Description	:	decide wheter pl is a friend
 * Arguments	:	object pl -- the person of interest
 * Returns	:	-1 = goblins, morgul mages, angmarim,
 *				undead, align < -250
 *           		1 = elves, rangers, paladines, align > 750
 *           		0 = others
 */
public varargs int
query_friend_or_foe(mixed pl)
{
    if (stringp(pl))
    {
        pl = find_living(LOW(pl));
    }
    else if (!objectp(pl))
    {
        pl = TP;
    }

    if (!objectp(pl))
    {
        return 0;
    }

    if (M_TIRITH_MASTER->query_enemy(pl->query_real_name(),
        pl->query_race()))
    {
        return -1;
    }

    if (pl->query_prop(DID_ATTACK_MT_GATES))
    {
        return -1;
    }
  
    int fof = ::query_friend_or_foe(pl);
    // We make this extra check to permit dunedain to enter the city
    // during war time even if they do not have an alignment in excess
    // of 750:
    if ( (pl->query_guild_name_race() == DUNEDAIN_S_GUILD_NAME) &&
	 (fof >= 0) && (pl->query_alignment() > 250)) 
	return 1;

    return fof;
} /* query_friend_or_foe */


/*
 * Function name:	hook_wagon_depart
 * Description	:	do msgs for wagon
 * Arguments	:	object wagon -- the transport
 *			string where -- direction of travel
 */
public void
hook_wagon_depart(object wagon, string where)
{
    if (where != "west" ||
        gate->query_open())
    {
	return;
    }

    tell_room(gate->query_other_room(), 
	BSN("From the east, someone shouts: Open the gate, " +
	    "the transport from Edoras is outside!"));

    tell_room(TO,
	"You hear a muffled shout from the other side of the Great Gate.\n");

    gate->do_unlock_door("You hear something heavy moving on the other " +
	"side of the Great Gate.\n");
    other_gate->do_unlock_door("Suddenly, the wooden beam blocking the " +
	"door starts moving.\n");
    gate->do_open_door("The Great Gate of Minas Tirith opens as the iron " +
	"doors swing inwards.\n");
    other_gate->do_open_door("The Great Gate of Minas Tirith opens as the " +
	"iron doors swing inwards.\n");
} /* hook_wagon_depart */


/*
 * Function name:	hook_wagon_arrive
 * Description	:	close gate behind wagon
 * Arguments	:	object wagon -- the transport
 *			string where -- direction of travel
 */
public void
hook_wagon_arrive(object wagon, string from)
{
    if (from == "east")
    {
    close_gate();
    }
} /* hook_wagon_arrive */










