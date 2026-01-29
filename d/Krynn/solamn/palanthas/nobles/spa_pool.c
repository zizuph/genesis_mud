/* 
 * Laethorian Spa and Body, swimming pool
 * Swimming trained here to L30, Superior Layman
 *
 * Mortis 02.2006
 *
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>
#include <cmdparse.h>
#include <ss_types.h>

#define SWIMMING		"_i_am_swimming_at_the_laethorian"
#define POOP			"_there_is_a_floater_in_the_pool"
#define POOPER			"_i_pooped_in_the_laethorian_pool"
#define URINATOR		"_i_pissed_in_the_laethorian_pool"
#define WET_SUBLOC		"wet_subloc"
#define WET				"i_am_wet"

inherit NOBLE_ROOMBASE;
inherit "/lib/guild_support";
inherit "/lib/skill_raise";

/* Prototypes */

int towel_thief();
int read_sign();
int dive(string str);
int climb(string str);
int swim();
string skylight_time();
public void set_up_skills();

int pee = 0, wettime;
string poop;
object lifeguard;

string
query_to_jail()
{
  return "east";
}

void
reset_palan_room()
{
    if (!lifeguard)
    {
        lifeguard = clone_object(NOBLE + "living/lifeguard");
        lifeguard->move(TO);
    }
	
	pee = 0;
	
	if (query_prop(POOP) != 0)
	{
		remove_prop(POOP);
		remove_item("pool");
		remove_item("spot");
		add_item(({"pool", "water"}), "The pool is thirty feet wide, sixty "
		+ "long, and eight feet deep.  Clear, blue water rests in a white "
		+ "marble basin rectangular in shape with a dark grainy stone "
		+ "walkway surrounding it.\n");
	}
}

void
create_palan_room()
{
    SHORT("Large swimming pool at a dayspa");
    LONG("This large pool room stretches north and south and is almost "
	+ "completely pool except for a stone walkway encircling the rectangular "
	+ "pool.  A shaft of " + "@@skylight_time@@" + " streams down "
	+ "from the ceiling into the center of the pool and sparkling off the "
	+ "clear, blue water.  Hooks for towels and clothing line the walls, and "
	+ "a tall, wooden chair sits just south of the entrance from where the "
	+ "lifeguard keeps an eye on the pool and offers lessons.  A large, marble "
	+ "sign is hung in the center of the west wall.\n");

	ITEM(({"water", "pool"}), "The pool is thirty feet wide, sixty long, and "
	+ "eight feet deep.  Clear, blue water rests in a white marble basin "
	+ "rectangular in shape with a dark grainy stone walkway surrounding "
	+ "it.  You can <enter> or <exit> the pool.\n");
	ITEM("entrance", "The entrance is an arched hallway leading back into "
	+ "the spa.\n");
	ITEM(({"brazier", "braziers", "silver brazier", "silver braziers", "fire",
		"fires"}), "Tall, silver braziers stand in the four corners of this "
	+ "room.  Small fires burn in each, their light reflecting off the "
	+ "polished marble of the ceiling and shedding even light across the "
	+ "floor and walls.\n");
	ITEM(({"corner", "corners"}), "Standing in each of the corners and "
	+ "providing light are tall, silver braziers.\n");
	ITEM(({"wall", "walls"}), "The walls are of translucent white marble "
	+ "polished to a gleaming shine.  They are lined with hooks for towels "
	+ "and clothing.\n");
	ITEM("ceiling", "In the center of the marble ceiling is a shaft leading "
	+ "to a skylight through which " + "@@skylight_time@@" + " streams "
	+ "down sparkling off the clear, blue water of the pool.\n");
	ITEM(({"floor", "walkway"}), "A walkway of rough grained, dark stone "
	+ "surrounds the pool.  It is only a few feet wide, but is not slick "
	+ "when wet.\n");
	ITEM("chair", "There is a tall, wooden chair south of the entrance "
	+ "where the lifeguard sits, keeps an eye on the pool, and occasionally "
	+ "teaches swimming.\n");
	ITEM(({"sign", "marble sign"}), "A large, marble sign is hung on the "
	+ "west wall.  It clearly reads, \"N O   D I V I N G!\" in the old "
	+ "style.\n");


    add_smell("vampire", "The air here is cool and moist with the smells of "
	+ "an indoor pool that is well-kept, clean, and devoid of blood.");
    add_smell("morgul", "The air here is cool and moist.  It smells of an "
	+ "indoor pool that is well-kept and clean.  With a sufficient fire lit "
	+ "beneath, you estimate several hundred hobbits could be boiled alive "
	+ "in this pool.");
    
	add_smell("human", "The air here is cool and moist.  It smells of an "
	+ "indoor pool that is well-kept and clean.");
	add_smell("elf", "The air here is cool and moist.  It smells of an "
	+ "indoor pool that is well-kept and clean.");
	add_smell("goblin", "The air here is cool and moist.  It smells of an "
	+ "indoor pool that is well-kept and clean.  Why these humans clean "
	+ "their water confuses you.");
	add_smell("dwarf", "The air here is cool and moist.  It smells of an "
	+ "indoor pool that is well-kept and clean.  Why it is here is beyond "
	+ "you.");
	add_smell("hobbit", "The air here is cool and moist.  It smells of an "
	+ "indoor pool that is well-kept, clean, and nice for a refreshing "
	+ "swim.");
	add_smell("gnome", "The air here is cool and moist.  It smells of an "
	+ "indoor pool that is properly sterilized and cleaned.");
	add_smell("minotaur", "The air here is cool and moist.  It smells of an "
	+ "indoor pool that is well-kept and clean enough to drink from.  What "
	+ "else it's here for is beyond you.");
	add_smell("halfhuman", "The air here is cool and moist.  It smells of an "
	+ "indoor pool that is well-kept and clean.");
	add_smell("halfelf", "The air here is cool and moist.  It smells of an "
	+ "indoor pool that is well-kept and clean.");
	add_smell("orc", "The air here is cool and moist.  It smells of an "
	+ "indoor pool that is well-kept and clean.  You wonder why these "
	+ "humans would keep their water pool so clean except to boil "
	+ "hobbits in.");
	add_smell("hobgoblin", "The air here is cool and moist.  It smells of an "
	+ "indoor pool that is well-kept and clean.");
	add_smell("kender", "Ahh!  A swimming pool that is well-kept and clean.  "
	+ "It smells refreshing already.");
	add_smell("drow", "The air here is cool and moist.  It smells of an "
	+ "indoor pool that is well-kept and clean.");
	add_smell("noldor", "The air here is cool and moist.  It smells of an "
	+ "indoor pool that is well-kept and clean though you question the "
	+ "human source of the cleaning solutions.");

	CMD(({"sign", "marble sign"}), "read", "@@read_sign");

	EXIT(NOBLE + "spa2", "east", "@@towel_thief", 0);
	
    create_skill_raise();
    set_up_skills();

	reset_palan_room();
}

int
towel_thief()
{
	object *towels = FIND_STR_IN_OBJECT("pal_spa_towel", TP);

	if (sizeof(towels) != 0)
	{
		if (lifeguard)
		{
			command("say Hey, " + QTNAME(TP) + " no running off with the "
			+ "Laethorian's towels!");
			write("The lifeguard stops you short from leaving.\n");
			say(QCTNAME(TP) + " is stopped short from leaving by the "
			+ "lifeguard.\n");
			return 1;
		}
		write("An attendant stops you from running away with the Laethorian's "
		+ "towel.\n");
		say(QCTNAME(TP) + " is stopped from leaving by an attendant.\n");
		return 1;
	}
	return 0;
}

string
skylight_time()
{
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
		return one_of_list(({"pale purple", "soft yellow", "soft orange",
		"pink"})) + " morning light";
		break;
    case TOD_DAY:
		return one_of_list(({"golden yellow", "golden", "bright yellow"}))
		+ " daylight";
		break;
    case TOD_TWILIGHT:
		return one_of_list(({"fading yellow", "pale yellow", "fading",
		"pale"})) + " evening light";
		break;
	case TOD_NIGHT:
		return one_of_list(({"silvery star", "silvery moon", "pale moon",
		"shimmering star", "star", "moon"})) + "light";
		break;
	default:
		return "light";
		break;
	}
}

int
read_sign()
{
	write("It reads:  N O   D I V I N G!\n");
	say(QCTNAME(TP) + " reads the marble sign on the west wall.\n");
	return 1;
}

void 
init()
{
    init_skill_raise();

    ::init();
	ADA("dive");
	ADD("dive", "jump");
	ADD("dive", "enter");
	ADA("climb");
	ADD("climb", "exit");
	ADD("climb", "leave");
	ADA("swim");
	ADA("drink");
	ADA("poop");
	ADD("poop", "defecate");
	ADD("poop", "shit");
	ADD("poop", "crap");
	ADA("pee");
	ADD("pee", "urinate");
	ADD("pee", "piss");
	ADA("fart");
}

int
dive(string str)
{
	object wettowel;

	if (TP->query_prop(SWIMMING) == 1)
	{
		write("You cannot " + query_verb() + " from within the pool.  Climb "
		+ "out and try again?\n");
		return 1;
	}

	if (query_verb() == "dive")
	{
		if (lifeguard)
		{
			lifeguard->command("shout N O   D I V I N G!  Can't you read?");
			lifeguard->command("point sign");
		}
			
		write("You leap off the walkway and dive headfirst into the pool.\n"
		+ "Sploosh!\n");
		say(QCTNAME(TP) + " leaps off the walkway and dives headfirst into "
		+ "the pool.\nSploosh!\n");
	}

	if (query_verb() == "jump")
	{
		if (!str)
			return 0;

		write("You attempt a " + one_of_list(({"fancy", "convoluted",
		"simple"})) + " jump and land in the pool.\nKersploosh!\n");
		say(QCTNAME(TP) + " attempts a " + one_of_list(({"fancy",
		"convoluted", "simple"})) + " jump and lands in the pool.\n"
		+ "Kersploosh!\n");
	}

	if (query_verb() == "enter")
	{
		if (!str)
			return 0;

		if (!parse_command(str, ({}), "[the] 'pool'"))
			return 0;

		write("You slip into the pool, the water rippling before you.\n");
		say(QCTNAME(TP) + " slips into the pool, the water rippling before "
		+ HIM(TP) + ".\n");
	}

	TP->add_prop(SWIMMING, 1);
	TP->add_prop(WET, time());
	TP->add_subloc(WET_SUBLOC, TO);
	TP->add_prop(LIVE_S_EXTRA_SHORT," is swimming in the pool");

	if (wettowel = present("_laethorian_pool_towel", TP))
		wettowel->get_wet();

	return 1;
}

int 
climb(string str)
{
	string verb, verbs;

	if (query_verb() == "climb")
		verb = "climb out of";
		verbs = "climbs out of";
	if (query_verb() == "exit")
		verb = "exit";
		verbs = "exits";
	if (query_verb() == "leave")
		verb = "leave";
		verbs = "leaves";

	if (!str && query_verb() == "exit")
	{
		write("Exit the pool?\n");
		return 1;
	}

	if (!str && query_verb() == "climb")
	{
		write("Climb out of the pool?\n");
		return 1;
	}

	if (!str)
		return 0;

	if (parse_command(str, ({}), "[out] [of] [the] 'pool'"))
	{
		if (TP->query_prop(SWIMMING) == 1)
		{
			write("You " + verb + " the pool dripping wet.\n");
			say(QCTNAME(TP) + " " + verbs + " the pool dripping wet.\n");
			TP->remove_prop(TSIT);
			TP->remove_prop(LIVE_S_EXTRA_SHORT);
			TP->remove_prop(SWIMMING);
			TP->add_prop(WET, time());
			TP->add_subloc(WET_SUBLOC, TO);
			return 1;
		}
		write("But you're not in the pool.\n");
		say(QCTNAME(TP) + " contemplates the improbable.\n");
		return 1;
	}
}

int
swim()
{
	NF("You need to be in the pool to swim.  The lifeguard doesn't teach "
	+ "air swimming.\n");

	if (TP->query_prop(SWIMMING) != 1)
		return 0;

	write("You swim around in the pool.  The water is cool and refreshing.\n"
	+ "Ahhhhh!\n");
	say(QCTNAME(TP) + " swims around in the pool.\n");
	return 1;
}

int
drink(string str)
{
	if (!str)
		return 0;

	if (!parse_command(str, ({}), "[from] [the] 'pool' / 'water'"))
		return 0;

	if (TP->drink_soft(TP->drink_max() / 20, 0))
	{
		write("For some reason you decide to take a gulp of pool water.\n"
		+ "Hmm, not bad, but you can taste some of the solution they use "
		+ "to keep it sterile.");

		switch (pee)
		{
			case 0:
				write("");
				say(QCTNAME(TP) + " has a blank expression as " + HE(TP)
				+ " takes a gulp of water from the pool.");
				break;
			case 1:
				write("  You detect another flavour in the water, too, but "
				+ "you can't quite place it.");
				say(QCTNAME(TP) + "");
				break;
			case 2:
				write("  Eww, what else is that you taste in the water?  "
				+ "It reminds you of " + one_of_list(({"asparagus",
				"stale noodles", "ammonia", "something unpleasant"}))
				+ ".");
				say(QCTNAME(TP) + " turns up " + HIS(TP) + " nose as "
				+ HE(TP) + " takes a gulp of water from the pool.");
				break;
			default:
				write("  This pool is filled with urine!  Oh gods, no!!!  "
				+ "Why?!?");
				say(QCTNAME(TP) + " gags as " + HE(TP) + " spits out:  "
				+ "Urine?!?  Nooooo, gods!  Why?!?");
				break;
		}
		
		if (poop = query_prop(POOP))
		{
			write("  There is a " + poop + " floating in the pool!  And you "
			+ "just drank from it!\nYou gag.");
			say(QCTNAME(TP) + " cries out, \"I feel unclean!\" as a " + poop
			+ " goes floating by in the pool water " + HE(TP) + " just "
			+ "drank.\n" + QCTNAME(TP) + " gags.");
		}

		write("\n");
		say("\n");
		
		return 1;
	}
	else
		write("Tempting as the pool water may look, you are too full to "
		+ "drink anymore.\n");
	
	return 1;
}

int
poop()
{
	if (TP->query_prop(SWIMMING) == 0)
	{
		write(C(query_verb()) + "?  What, right here out in the open?  Are "
		+ "you some kind of madman?\n");
		say(QCTNAME(TP) + " purses " + HIS(TP) + " lips as " + HE(TP)
		+ " peers around conspicuously.\n");
		return 1;
	}

	if (poop = TP->query_prop(POOPER))
	{
		write("You already dropped " + poop + " in the pool.  Geesh, "
		+ "how much turd do you think you can crap in a day?  If "
		+ "pooping's your game, go to Gelan.\n");
		return 1;
	}

	poop = one_of_list(({"an enormous greenish-brown turd", "a corn "
	+ "speckled brown turd", "a blackish-green turd log", "a messy "
	+ "puddle of lumpy brown crap", "a sesame seed speckled crap log",
	  "a sickly black turd"}));

	write("You pause for a moment while swimming and " + query_verb()
	+ " out " + poop + " with a splurty grunt.\n");
	say(QCTNAME(TP) + " pauses for a moment while swimming to " + query_verb()
	+ " out " + poop + " with a splurty grunt.\n");

	if (lifeguard)
	{
		lifeguard->command("gag");
		lifeguard->command("shout I'm not cleaning that!");
	}

	TP->add_prop(POOPER, poop);
	add_prop(POOP, poop);
	remove_item("pool");
	add_item(({"pool", "water"}), "The pool is thirty feet wide, sixty long, "
	+ "and eight feet deep.  Clear, blue water rests in a white marble basin "
	+ "rectangular in shape with a dark grainy stone walkway surrounding "
	+ "it.  You may <enter> or <exit> the pool.  There is a dark spot "
	+ "floating in the water.\n");
	add_item("spot", "Oh no!  Someone has deposited " + poop + " in the "
	+ "pool!\n");
	return 1;
}

int
pee()
{
	int howmuchpee = TP->query_prop(URINATOR);

	if (TP->query_prop(SWIMMING) == 0)
	{
		write(C(query_verb()) + "?  What, right here on the floor?  Are "
		+ "you some kind of madman?\n");
		say(QCTNAME(TP) + " squeezes " + HIS(TP) + " legs together as "
		+ HE(TP) + "peers around conspicuously.\n");
		return 1;
	}

	if (howmuchpee >= 5)
	{
		write("You already filled the pool with urine.  Geesh, "
		+ "how much do you think you can piss in a day?  If "
		+ "peeing's your game, go to Gelan.\n");
		return 1;
	}

	write("You pause for a moment while swimming and " + query_verb()
	+ " in the pool.\nThe water around you grows warmer.\n");
	say(QCTNAME(TP) + " pauses for a moment while swimming, " + HIS(TP)
	+ " eyes almost rolling up in his eyelids as " + HE(TP) + " smiles "
	+ "and sighs.\n");

	if (lifeguard)
	{
		lifeguard->command("gag");
		lifeguard->command("shout " + TP->short() + " and peeing!  "
		+ "That is sick!");
	}

	howmuchpee++;
	pee++;

	TP->add_prop(URINATOR, howmuchpee);

	remove_item("pool");
	return 1;
}

int
fart()
{
	if (TP->query_prop(SWIMMING) == 0)
		return 0;

	string fart = one_of_list(({"horrid brown bubbles", "rotten peach "
	+ "smelling bubbles", "dead rat smelling bubbles", "tiny bubbles",
	"suspicious bubbles", "nose-burning green bubbles"}));

	write("A stream of " + fart + " gurbles up around you.\n");
	say("A stream of " + fart + " gurbles up around " + QTNAME(TP) + ".\n");

	if (lifeguard)
	{
		lifeguard->command("say Oh man, what have you been eating?  "
		+ one_of_list(({"Rotten corn", "Sancrist prunes", "Crap burgers",
		"Rotten eggs", "Dead things"})) + "?");
		lifeguard->command("shout Hey, " + TP->query_adj() + " "
		+ TP->query_race_name() + ", stop trying to carbonate the pool!");
	}
	return 0;
}



/* ----------------------  Skill Functions  ---------------------- */
public void
set_up_skills()
{
	sk_add_train(SS_SWIM,"swim",0,0,30);
}

public int
sk_improve(string sk)
{
    if (!(present("lifeguard", TO)))    
    {
        write("You need the lifeguard to give you swimming lessons.\n");
        return 1;
    }
	if (TP->query_prop(SWIMMING) != 1)
	{
		lifeguard->command("say You'll need to be swimming in the pool first, "
		+ QTNAME(TP) + ", before I can give you swimming lessons.");
		return 1;
	}
    return ::sk_improve(sk);
}

public int
sk_query_max(int snum)
{
    int *skills_available_here;
    mixed skval;
   
    skills_available_here = sk_query_train();
   
    if(member_array(snum, skills_available_here) == -1)
        return 0;
   
    if (!mappingp(sk_default))
        return 0;
    skval = sk_trains[snum];
    if (sizeof(skval)>2)
        return skval[2];
    else return 0;
}

public int
sk_hook_improved_max(string skill)
{
    NF("The lifeguard is unable to teach you anymore about swimming.  "
	+ "Why, you're probably as good a swimmer as he is now.\n");
    return 0;
}

void leave_inv(object ob, object to)
{
        ::leave_inv(ob, to);    
        
        if(!objectp(to) || !objectp(ob))
                return;
                
        if(TP->query_prop(SWIMMING) == 1)
        {
                TP->catch_msg("You climb out of the pool dripping wet before "
				+ "leaving.\n");
                say(QCTNAME(TP) + " climbs out of the pool dripping wet as " 
				+ HE(TP) +" leaves.\n");
                TP->remove_prop(LIVE_S_EXTRA_SHORT);
                TP->remove_prop(SWIMMING);
				TP->add_prop(WET, time());
				TP->add_subloc(WET_SUBLOC, TO);
        }
}


/* ----------------------  Wet Subloc Functions  ---------------------- */

public string
show_subloc(string subloc, object pl, object for_obj)
{
	int subtime = time() + 36000; // Stay wet for 10 minutes w/out drying.
	string name;

	if (TP->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	{
		return "";
	}

	if (subloc != WET_SUBLOC)
	{
		return pl->show_subloc(subloc, pl, for_obj);
	}

	if (pl->query_prop(SWIMMING))
    {
		if (for_obj != pl)
		{
			return C(HE(pl)) +
			" is swimming in the pool.\n";
			
		}
		return "You are swimming in the pool.\n";
	}

	if (pl->query_prop(WET))
	{
		wettime = pl->query_prop(WET);

		if (wettime > subtime)
		{
			pl->remove_prop(WET);
			pl->remove_prop(WET_SUBLOC);
			return "";
		}

		if (for_obj != pl)
		{
			return C(HE(pl)) + " is dripping wet.\n";
			
		}
		return "You are dripping wet.\n";
	}

	return "";
}
