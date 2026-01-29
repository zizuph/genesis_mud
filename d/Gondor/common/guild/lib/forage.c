/*
 *      /d/Gondor/common/guild/lib/forage.c
 *
 *      This is included into the ranger soul.
 * 
 *      the Gondorian Rangers Guild's function that allows the
 *      Rangers to forage for food in the open.
 *      The command requires that the player is in an outside-room, and will
 *      drain 5 mana and 5 fatigue for small game, 10 mana and 10 fatigue
 *      for big game hunting. Mayhem, April 1994
 *
 *      Modification log:
 *      March 1997, Olorin:     Revision.
 *                              combined two separate functions into forage_animal().
 */
#define SMALL_COST 5
#define LARGE_COST 10
#define GONDOR_I_HUNTING  "_gondor_i_hunting"
#define GONDOR_I_HUNTED   "_gondor_i_hunted"
#define MAX_HUNT 2

private int 
query_been_hunted(object player)
{
    if (ENV(player)->query_prop(GONDOR_I_HUNTED) >= MAX_HUNT)
    {
	player->catch_msg("You notice this area has already been hunted "+
	    "in a few times, and decide not to over-hunt the area.\n");
	tell_room(ENV(player), QCTNAME(player)+" returns "+
		  "empty-handed from hunting.\n",player);
	return 1;
    }
    return 0;
}

public int
forage_animal(object player, string size)
{
    int     food_amount,
            cost,
            task;
    object  animal, 
            room;
    string  animal_type;

    if (!objectp(player)) 
	return 0;

    room = ENV(player);
    player->remove_prop(GONDOR_I_HUNTING);
    if (room->query_prop(ROOM_I_INSIDE))
    {
	NFN("You cannot forage for food indoors!");
	return 0;
    }
    if ((room->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER) ||
	(room->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER))
    {
	NFN("If you want to catch animals in water, go fishing!");
	return 0;
    }
    switch (size)
    {
    default:
    case "small":
	cost = SMALL_COST;
	task = TASK_ROUTINE;
	break;
    case "large":
	cost = LARGE_COST;
	task = TASK_DIFFICULT;
	break;
    }

    if (player->query_mana() < cost)
    {
	write("The strain is too great for you to concentrate "
	    + "on foraging.\n");
	return 1;
    }
    if (player->query_fatigue() < cost)
    {
	write("Your weary bones refuse to forage for food.\n");
	return 1;
    }

    if (query_been_hunted(player)) 
	return 1; 

    player->add_mana(cost);
    player->add_fatigue(cost);

    if (player->resolve_task(task, ({ TS_WIS, SS_HUNTING })) <= 0)
    {
	write("You search all around for " + size + " game animals, "+
	      "but are unable to find any.\n");
	say(QCTNAME(player)+ " searches all around but can not "+
	    "seem to catch anything to eat.\n",player);
	return 1;
    }

    switch (size)
    {
    default:
    case "small":
	switch (random(6))
	{
	case 0:
	    animal_type = "coney";
	    food_amount = 70;
	    break;
	case 1:
	    animal_type = "pheasant";
	    food_amount = 60;
	    break;
	case 2:
	    animal_type = "squirrel";
	    food_amount = 50;
	    break;
	case 3:
	    animal_type = "quail";
	    food_amount = 55;
	    break;
	case 4:
	    animal_type = "duck";
	    food_amount = 65;
	    break;
	case 5:
	    animal_type = "pig";
	    food_amount = 100;
	    break;
	}
	break;
    case "large":
	switch (random(6))
	{
	case 0:
	    animal_type = "deer";
	    food_amount = 180;
	    break;
	case 1:
	    animal_type = "moose";
	    food_amount = 210;
	    break;
	case 2:
	    animal_type = "boar";
	    food_amount = 150;
	    break;
	case 3:
	    animal_type = "elk";
	    food_amount = 195;
	    break;
	case 4:
	    animal_type = "goat";
	    food_amount = 145;
	    break;
	case 5:
	    animal_type = "yak";
	    food_amount = 155;
	    break;
	}
	break;
    }
    room->add_prop(GONDOR_I_HUNTED, 
		   room->query_prop(GONDOR_I_HUNTED) + 1);
    write("You successfully catch and prepare " + 
	  LANG_ADDART(animal_type) + " for cooking.\n");
    say(QCTNAME(player)+" catches " + 
	LANG_ADDART(animal_type)+" for dinner.\n");

    FIX_EUID;

    animal = clone_object(RANGER_DIR + "obj/animal_corpse");
    animal->set_name(animal_type);
    animal->set_animal_type(animal_type);
    animal->set_food_amount(food_amount);
    animal->move(room);

    return 1;
}

public int
try_forage(string str)
{
    int     speed;
    object  tp = TP,
            room;

    if (!strlen(str))
	return 0;

    if (objectp(tp->query_attack()))
    {
	NFN("You cannot hunt for food while fighting!");
	return 0;
    }
    if (tp->query_prop(GONDOR_I_HUNTING))
    {
	NFN("You are already foraging for food!");
	return 0;
    }
    if ((room = ENV(tp))->query_prop(ROOM_I_INSIDE))
    {
	NFN("You can only hunt for game out in the open.");
	return 0;
    }

    if ((room->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER) ||
	(room->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER))
    {
	NFN("If you want to catch animals in water, go fishing!");
	return 0;
    }

    if (parse_command(str, tp, 
	" [for] [small] 'game' / 'animals' "))
    {
	speed = ((100 - tp->query_skill(SS_HUNTING)) / 2 + 10);
	write("You start foraging for some small animals to eat.\n");
	say(QCTNAME(tp)+" starts foraging for food.\n");
	tp->add_prop(GONDOR_I_HUNTING, 1);
	set_alarm(itof(speed), 0.0, &forage_animal(tp, "small"));
	return 1;
    }
    if (parse_command(str, tp, 
        " [for] [big] [large] 'game' / 'animals' "))
    {
	speed = ((100 - tp->query_skill(SS_HUNTING)) / 2 + 30);
	write("You start foraging for some large animals to eat.\n");
	say(QCTNAME(tp)+" starts foraging for food.\n");
	tp->add_prop(GONDOR_I_HUNTING, 1);
	set_alarm(itof(speed) ,0.0, &forage_animal(tp, "large"));
	return 1;
    }
    return 0;
}
