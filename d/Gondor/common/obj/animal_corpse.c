/*
 * /d/Gondor/common/obj/animal_corpse.c
 *
 * Modified from
 * /d/Gondor/common/obj/rabbit_corpse.c by Olorin, Apr 1993,
 * for foraging to accomodate differing types of creatures.
 * Mayhem, April 1994
 *
 * Modification log:
 * Rewritten following the occurence of runtime errors.
 * Olorin, 26-may-1995
 * Updated Gwyneth/Tigerlily for use with new ranger code
 *    January 2004
 *
 * Inherited by:
 * /d/Gondor/common/obj/rabbit_corpse.c
 * /d/Gondor/common/guild/obj/animal_corpse.c
 */
#pragma strict_types

inherit "/std/object.c";

#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/rangers/rangers.h"

// definitions
#define INTERVAL     6.0
#define ROAST_DONE  20
#define COOK_DONE   40
#define FRY_DONE    30
#define STEW_NO_REM "You cannot take the stew out of the pot!\n" +\
                    "Why don't you try to eat it right out of the pot?\n"
#define DECAY_TIME 30
#define FOOD_POISONED	"_poisoned"

/*
 *	Prototypes:
 */
public int     check_fire(object player);
public int     prepare_meal(string verb, object tp, object pot);
public void    decay_fun();

/*
 *	Global variables:
 */
static int     Decay     = DECAY_TIME,	// how many minutes until the corpse decays?
               Prep_Time = 0,		// how long to prepare a meal (step size INTERVAL)
	       Alarm_Id  = 0,		// id of the prepare_meal alarm
	       Food_Am;			// how much food is the meal
static string  Animal_Type = "animal",	// what kind of animal do we prepare
               Preparing   = 0,		// are we stewing, cooking, roasting, or frying?
	       Meal_File = (RANGER_DIR + "obj/prep_animal");  // file for the meal

public void
create_object()
{
    set_name( ({ "animal", "corpse", }) );
    set_adj("dead");
    set_long("This is the dead body of an animal.\n");
    set_alarm(60.0, 60.0, decay_fun);
}

public int
set_animal_type(string what)
{
    if (!strlen(what))
        return 0;
    Animal_Type = what;
    set_name( ({ Animal_Type, "corpse of " + Animal_Type, }) );
    set_long("This is the dead body of "+LANG_ADDART(Animal_Type)+". " +
	     "Properly prepared it might make a tasty, filling meal.\n");
    // We have to do this to update the obj_short variable:
    set_short(0);
    short();

    return 1;
}

public int
set_meal_file(string filename)
{
    if (file_size(filename+".c") > 0 ||
        file_size(filename) > 0)
    {
        Meal_File = filename;
        return 1;
    }
    return 0;
}

public void
set_food_amount(int amount)
{
    Food_Am = amount;
    add_prop(OBJ_I_VOLUME, Food_Am *  8);
    add_prop(OBJ_I_WEIGHT, Food_Am * 10);
}

public int    query_prep_time()   { return Prep_Time; }

public int
do_eat(string str)
{
    NF("Eat what?\n");
    if (!strlen(str) || 
	((str != Animal_Type) && (str != "corpse of "+Animal_Type)))
        return 0;

    write(BSN("You do not want to eat the "+Animal_Type+" raw. "
      + "You could try to roast it over a fire, or if you "
      + "have the proper utensils, you might fry it in a pan or cook "
      + "it in a pot with water."));
    return 1;
}

public int
hook_query_prepared(string verb)
{
    return 1;
}

public int
do_prepare(string str)
{
    string  verb = LOW(query_verb());
    object  tp = TP,
            pot,
            *animals,
            oc;
    int     flag;

    NFN(CAP(verb) + " what?");
    if (!strlen(str) || ((str != Animal_Type) && (str != "corpse of "+Animal_Type)))
        return 0;

    if (!hook_query_prepared(verb))
        return 0;

    NFN("You do not find any fire to "+verb+" the "+Animal_Type+".");
    if (!check_fire(tp))
        return 0;

    NFN("You are already "+Preparing+" the "+Animal_Type+".");
    if (strlen(Preparing))
        return 0;

    switch(verb)
    {
    case "prepare":
	write(BSN("How do you want to prepare the "+Animal_Type
           + "? You could try to roast it over a fire, or if you "
           + "have the proper utensils, you might fry it in a pan "
           + "or cook it in a pot with water.\n"));
	return 1;
	break;

    case "stew":
    case "cook":
	NFN("You need a larger fire to "+verb+" the "+Animal_Type+".");
	if (check_fire(tp) == 1)
	    return 0;
	NF(BSN("You need a pot to "+verb+" the "+Animal_Type
	       + ". Why do you not try to roast it instead?"));
	pot = present("pot",tp);
	if (!objectp(pot) || !pot->query_prop(CONT_I_IN))
	    return 0;
	NF(BSN("You need to have water in your pot to "+verb+" the "+Animal_Type+"."));
	if (!pot->query_prop(OBJ_I_CONTAIN_WATER))
	    return 0;
	if (oc = present("corpse", pot))
	{
	    write("There is already "+LANG_ADDART(oc->short())+" in the pot.\n");
	    NFN("If you want to cook the "+TO->short()+", the pot should be empty!");
	    return 0;
	}

	if (flag = TO->move(pot))
	{
	    NFN("The "+Animal_Type+" does not fit into the pot.");
	    return 0;
	}
	Preparing = "cooking";
	Prep_Time = COOK_DONE;
	write("You put the "+Animal_Type+" into the pot and start "+verb+"ing it.\n");
	say(QCTNAME(tp)+" puts "+LANG_ADDART(Animal_Type)
	    + " into a pot and starts "+verb+"ing it.\n");

        pot->set_meal(TO);
        if (pot->query_dirty())
            TO->add_prop(FOOD_POISONED, 1);
        break;

    case "roast":
        if ((TP->query_prop(RANGER_I_TASK) == COOK_TASK) &&
            present("taskmaster", environment(TP)))
        {
            if (member_array(TO, TP->query_prop(RANGER_O_COOK_TASK)) == -1)
            {
                write("The only game you can cook is that which you have " +
                    "hunted yourself.\n");
                return 1;
            }

            animals = TP->query_prop(RANGER_O_ROASTED);
            if (member_array(TO, TP->query_prop(RANGER_O_ROASTED)) == -1)
            { 
                if (sizeof(animals))
                    TP->add_prop(RANGER_O_ROASTED, animals + ({ TO }) );
                else
                    TP->add_prop(RANGER_O_ROASTED, ({ TO }));
            }
        }

	Preparing = "roasting";
	Prep_Time = ROAST_DONE;
	pot = 0;
	write("You start roasting the "+Animal_Type+".\n");
	say(QCTNAME(tp)+" starts roasting "+LANG_ADDART(Animal_Type)+".\n");
	break;

    case "fry":
	NFN("You need a larger fire to fry the "+Animal_Type+".");
	if (check_fire(tp) == 1)
	    return 0;
	NF(BSN("You need a pan to fry the "+Animal_Type
	       + ". Why do you not try to roast it instead?"));
	if (!objectp(pot = present("pan", tp)) || 
	    !(pot->query_prop(CONT_I_IN)))
	    return 0;
	
	if (TO->move(pot))
	{
	    NFN("The "+Animal_Type+" does not fit into the pan.");
	    return 0;
	}
	Preparing = "frying";
	Prep_Time = FRY_DONE;
	write("You put the "+Animal_Type+" into the pan and start frying it.\n");
	say(QCTNAME(tp) + " puts "+LANG_ADDART(Animal_Type)
	    + " into a pan and starts frying it.\n");
	break;
    }
    
    if (Prep_Time <= 0)
        Prep_Time = COOK_DONE;
    if (Alarm_Id)
        remove_alarm(Alarm_Id);
    Alarm_Id = set_alarm(INTERVAL, INTERVAL, &prepare_meal(verb, tp, pot));
    return 1;
}

public void
stop_preparation(object pot)
{
    Preparing = 0;
    Prep_Time = 0;
    remove_alarm(Alarm_Id);
    Alarm_Id = 0;
    if (objectp(pot))
        pot->set_meal(0);
}

public string
query_prep_adj(string verb)
{
    string  adj;

    switch(verb)
    {
    case "cook":
    case "stew":
	adj = "stewed"; 
	break;
    case "fry":
	adj = "fried";  
	break;
    case "roast":
	adj = "roast";
	break;
    }
    return adj;
}

public int
hook_setup_meal(string verb, object meal)
{
    return 0;
}

public int
prepare_meal(string verb, object tp, object pot)
{
    int     i;
    mixed  *exits;
    object  meal,
            room = ENV(TO),
            spice;
    string  adj,
            this_room_msg;

    if (!strlen(Preparing))
    {
        set_alarm(0.0, 0.0, &stop_preparation(pot));
        return 0;
    }
        
    while (!room->query_prop(ROOM_I_IS))
        room = ENV(room);

    if (Prep_Time--)
    {
        if (!check_fire(tp))
        {
            if (objectp(tp) && present(tp, room))
            {
                tp->catch_msg("Without fire you cannot continue to "
                  + verb+" the "+Animal_Type+".\n");

                switch(verb)
                {
		case "roast": 
		    break;
		case "cook":
		case "stew":
		    tp->catch_msg("You get a dead "+Animal_Type+" from the pot.\n");
		    tell_room(room, QCTNAME(tp)+"takes the "+Animal_Type
			+ " from the pot since "+HE(tp)+"cannot continue "
                        + "to cook it without fire.\n", ({ tp }));
		    if (TO->move(tp))
			TO->move(tp, 1);
		    break;
		case "fry":
		    tp->catch_msg("You get a dead "+Animal_Type+" from the pan.\n");
		    tell_room(room, QCTNAME(tp)+"takes the "+Animal_Type
                        + " from the pan since "+HE(tp)+"cannot continue "
                        + "to cook it without fire.\n", ({ tp }));
		    if (TO->move(tp))
			TO->move(tp, 1);
		    break;
                }
            }
            set_alarm(0.0, 0.0, &stop_preparation(pot));
            return 0;
        }
        if (!random(5))
        {
            exits = room->query_exit_rooms();
            switch(verb)
            {
	    case "roast":
		this_room_msg = "The "+Animal_Type+" sizzles over the fire.";
		break;
	    case "cook":
	    case "stew":
		this_room_msg = "The "+Animal_Type+" stews in the water "
		    + "in the pot over the fire.";
		break;
	    case "fry":
		this_room_msg = "The "+Animal_Type+" sizzles in the pan over the fire.";
		break;
            }
            tell_room(room, BSN(this_room_msg+" The smell of "
              + query_prep_adj(verb)+" "+Animal_Type+" rises to your nose."));
	    map(exits, &tell_room( , "Suddenly the smell of " +
				  query_prep_adj(verb) + " " +
				  Animal_Type + " is carried to your nose.\n"));
	}
	return 1;
    }

    stop_preparation(pot);
    tell_room(room, "The tender meat of the "+Animal_Type+" is done now.\n");
    if (objectp(tp) && present(tp, room))
    {
        switch(verb)
        {
	case "roast":
	    tp->catch_msg("You take the "+Animal_Type+" from the fire.\n");
	    tell_room(room, QCTNAME(tp)+" takes the "+Animal_Type
		      + " from the fire.\n", ({ tp }));
	    break;
	case "cook":
	case "stew":
	    tp->catch_msg("You take the pot from the fire.\n");
	    tell_room(room, QCTNAME(tp)+" takes the pot from the fire.\n", ({ tp }));
	    break;
	case "fry":
	    tp->catch_msg("You take the pan from the fire.\n");
	    tell_room(room, QCTNAME(tp)+" takes the pan from the fire.\n", ({ tp }));
	    break;
        }
    }

    FIX_EUID

    meal = clone_object(Meal_File);
    meal->set_name(Animal_Type);
    meal->set_animal_type(Animal_Type);
    meal->set_amount(Food_Am);
    meal->set_short(query_prep_adj(verb)+" "+Animal_Type);
    meal->set_adj(query_prep_adj(verb));
    hook_setup_meal(verb, meal);

    if (member_array(this_object(), tp->query_prop(RANGER_O_ROASTED)) != -1)
        meal->add_prop("_ranger_s_roasted", tp->query_real_name());

    switch(verb)
    {
    case "cook":
    case "stew":
	meal->add_name("stew");
	pot->remove_water();
	pot->set_meal(0);
	meal->add_prop("_salt_added_to_stew", TO->query_prop("_salt_added_to_stew"));
	meal->add_prop("_herb_added_to_stew", TO->query_prop("_herb_added_to_stew"));
	meal->add_prop("_rabbit_herb_added_to_stew",
		       TO->query_prop("_rabbit_herb_added_to_stew"));
	meal->add_prop("_stew_herb_added_to_stew",
		       TO->query_prop("_stew_herb_added_to_stew"));
	meal->add_prop("_extra_herb_added_to_stew",
		       TO->query_prop("_extra_herb_added_to_stew"));
	meal->add_prop(FOOD_POISONED,
		       TO->query_prop(FOOD_POISONED));
	meal->add_prop(OBJ_I_VOLUME,
		       pot->query_prop(CONT_I_MAX_VOLUME) - 
		       pot->query_prop(CONT_I_VOLUME));
	pot->add_prop(CONT_M_NO_REM, STEW_NO_REM);
	meal->start_cooling();

	while(spice = present("spice",pot))
	    spice->remove_object();

	break;
    }
    if (meal->move(ENV(TO)))
	meal->move(ENV(TO), 1);
    stop_preparation(pot); 
    set_alarm(0.0, 0.0, remove_object);
    return 1;
}

int
check_fire(object player)
{
    object room = ENV(TO),
           torch,
           lamp;

    while (!room->query_prop(ROOM_I_IS))
        room = ENV(room);

    if (room->query_prop("_room_has_fire") || room->query_prop(OBJ_I_HAS_FIRE))
        return 2;
    if (!objectp(player))
        return 0;
    if (ENV(player) != room)
       return 0;

    if ( (objectp(torch=present("torch", player)) &&
        torch->query_prop(OBJ_I_LIGHT)) ||
       (objectp(lamp=present("lamp", player)) &&
        lamp->query_prop(OBJ_I_LIGHT)))
        return 1;

    return 0;
}

public void
leave_env(object old, object dest)
{
    ::leave_env(old, dest);

    if (Alarm_Id && sizeof(get_alarm(Alarm_Id)))
    {
        write("You stop "+Preparing+" the "+Animal_Type+".\n");
        say(QCTNAME(TP) + " stops "+Preparing+" the "+Animal_Type+".\n");
        stop_preparation(old);
    }
}

int
query_cooking()
{
    return (Preparing == "cooking");
}

public void
decay_fun()
{
    if(!strlen(Preparing) &&
        ENV(TO)->query_prop(ROOM_I_IS))
    {
        if (!(Decay--))
        {
            tell_room(ENV(TO), "The "+QSHORT(TO)+" rapidly decays.\n");
            set_alarm(0.0, 0.0, remove_object);
            return;
        }
    }
}

public void
init()
{
    ::init();
    add_action(do_eat,     "eat");
    add_action(do_prepare, "prepare");
    add_action(do_prepare, "stew");
    add_action(do_prepare, "cook");
    add_action(do_prepare, "roast");
    add_action(do_prepare, "fry");
}
