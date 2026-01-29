/* The center of the city of Palanthas.
   This room contains a donation column (/d/Genesis/obj/donation/column)
   Mortis 07.2005 */

#pragma strict_types

#include "../local.h"
#include CLOCKH
#include <macros.h>

inherit CITY_BASE;

string
query_to_jail()
{
  return "north";
}
string plazasmell = "Misty air blowing south off the bay mingles here with the "
	+ "rich smells of coffee and cooking coming from the doorways of a "
	+ "cafe in the northwest of the plaza and one in the northeast along "
	+ "with the smells of a plaza busy with the human merchants and citizens "
	+ "frequenting it.  ";

object column = 0;

int moves = 0;

nomask public string
get_time_desc()
{
    string desc = "";
	string plaza = "  To the north is the Palanthas palace, its great white "
	+ "tower rising high above the plaza, and the city jail is to the "
	+ "south.  Cafes and street vendors ring the plaza between the "
	+ "administrative buildings.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of the streets and buildings of the Palatial "
	+ "Plaza glows in pale purple hues as the sun peeks above the mountains. "
	+ "The air is rich with the smells of morning cooking and coffee borne "
	+ "on a cool, misty breeze from the bay." + plaza;
	break;

    case TOD_DAY:
	desc += "The pristine marble of the streets and buildings of the Palatial "
	+ "Plaza gleams in the midday sun as merchants, bureaucrats, "
	+ "and shoppers crowd the plaza with the noisy murmurings of their "
	+ "daily business." + plaza;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of the streets and buildings of the Palatial "
	+ "Plaza catches the last rays of the sun appearing to glow of its own accord "
	+ "as the evening crowd comes out to walk and dine mingling with the "
	+ "remaining shoppers and merchants." + plaza;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of the streets and buildings of the Palatial Plaza amplifying the "
	+ "yellow glow of the street lamps.  Merchants and revelers still make "
	+ "their way about at this hour." + plaza;
    break;

    default:
	break;
    }
    return desc;
}

void create_palan_room()
{
    SHORT("In line in the Palatial Plaza of Palanthas");
    LONG("@@get_time_desc@@");

	ITEM("palace", "The palace of the Palanthas family dominates the entire "
	+ "north side of the plaza, its balconied windows gazing down upon the "
	+ "plaza from the many city offices it houses. Great white-enameled "
	+ "iron doors grant access to those who have waited in line for an "
	+ "audience.  Formidably plated knights guard the entrance, their "
	+ "oiled and polished halberds held crossed barring intruders and line "
	+ "jumpers.\n");

    ITEM("tower", "The Tower of Lord Amothus Palanthas rises a hundred feet "
	+ "if not more above the palace.  Polished white marble finishes the walls "
	+ "and crenellations of the tower.  The view from the top is said to be "
	+ "the most splendid in the city.\n");

	ITEM(({"line", "queue"}), "The line of citizens waiting for an audience "
	+ "at the doors to the palace is long at any hour and seems to be moving "
	+ "steadily forward at an unhurried pace.  You are waiting in the line.  "
	+ "If you'd like to get out, you can <leave line>.\n");

    ITEM(({"vendor", "vendors", "merchant", "merchants", "salesman", "salesmen"}),
		"Street vendors and merchants wander the plaza looking for business "
	+ "as well as ring the plaza catering to the fancies of the officials, "
	+ "nobles, and citizens of the city regardless of hour.\n");

	ITEM(({"hue", "hues", "purple hues", "sunrise"}), "@@get_dawn_hue@@" + "\n");
    ITEM(({"smells", "cooking", "coffee", "breeze"}), 
		"You would get more from that if you used your nose.\n");

    ITEM(({"crowd", "crowds", "people", "shoppers", "citizens"}),
		"@@get_day_crowd@@" + "\n");

    ITEM(({"reveler", "revelers", "reveller", "revellers"}),
		"@@get_night_revel@@" + "\n");

	EXIT(PALACE + "palace1", "north", "@@why_wait", 0);

	set_tell_time(150);

	add_tell("@@get_tell_time@@" + "\n");

	add_smell("vampire", plazasmell + "Your heightened sense of smell "
	+ "picks up the scent of coffee, biscuits, and fruit coming from the "
	+ "northwest cafe and from the northeast the scent of vanilla, coffee, "
	+ "turkey, and spices all subdued by the scent of human blood insipidly "
	+ "underlying it all.");
    add_smell("morgul", plazasmell + "Through the strong presence of "
	+ "human odours in this plaza you detect something you seek... no, it's "
	+ "just hobbit.  You smell food and coffee being served in the cafes "
	+ "to the northwest and northeast.");
    
	add_smell("human", plazasmell + "The smell of human food, wine, "
	+ "coffee, and people at their business in the city is familiar.");
	add_smell("elf", plazasmell + "The scents of food and drink on the "
	+ "air are distinctly human.  Though simple to your elven palate, the "
	+ "hint of spices from the northeast cafe is intriguing.");
	add_smell("goblin", plazasmell + "The scent of human flesh and offings "
	+ "is strong here with a hint of food and alcohol.");
	add_smell("dwarf", plazasmell + "The air though strong with human smells "
	+ "is clean enough to breathe.  Your dwarven nose picks up the smell of "
	+ "wine coming from the northeast cafe.");
	add_smell("hobbit", plazasmell + "There is a pleasant smelling mix of "
	+ "coffee and biscuits and lemon and tart fruits coming from the "
	+ "doorway of the northwest cafe and the hints of vanilla, spices, "
	+ "turkey, and wine from the northeast cafe.");
	add_smell("gnome", plazasmell + "The air is good enough to breathe at "
	+ "the moment and strong with many inviting human smells from the "
	+ "surrounding cafes and buildings.");
	add_smell("minotaur", plazasmell + "The smell of human flesh floods "
	+ "your senses in this great human plaza beneath which is the scent of "
	+ "cooked meat and wine coming from the northeast cafe.");
	add_smell("halfhuman", plazasmell + "The smell of human food, wine, "
	+ "coffee, and people at their business in the city is not "
	+ "unfamiliar.");
	add_smell("halfelf", plazasmell + "The scents of the plaza are not "
	+ "unfamiliar to your senses nor the smell of coffee and cooking in "
	+ "the nearby cafes unpleasant.");
	add_smell("orc", plazasmell + "The smell of manflesh is strong here in "
	+ "the center of their large city along with, what's that... a hint of "
	+ "hobbit?  The scents of food and drink come to your nose from the "
	+ "northwest and northeast cafes.");
	add_smell("hobgoblin", plazasmell + "The scents of human flesh, offings, "
	+ "and all the smells of a fortified human city abound here.");
	add_smell("kender", plazasmell + "Oh my!  You are almost overwhelmed "
	+ "by the multitude of amazing people and things to smell!  Human "
    + "cities must be very rich with things to discover and places to "
	+ "explore.");
	add_smell("drow", plazasmell + "Jiv'elgg!  All your composure is "
	+ "needed to keep from retching at the overwhelming stink of humans "
	+ "and overdwellers in this crowded plaza.  Still you can pick out the "
	+ "scents of food and drink, reminiscent of the strongest drow poisons, "
	+ "coming from a cafe in the northwest and less offensive scents from "
	+ "the cafe in the northeast.");
	add_smell("noldor", plazasmell + "The scent of humans is strong in the "
	+ "air along with the smells that accompany so many of their dwellings.");

}

/* The following large strings are the room emotes that vary depending
   on what time of day you're in the plaza. */

string
get_tell_time()
{
    string ttell = "";
	
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	ttell += one_of_list(({"The aroma of strong, fresh-brewed coffee wafts "
	+ "on a cool breeze under your nose from somewhere in the plaza.",
	  "A pair of aesthetics in quiet discussion munch on biscuits as they "
	+ "make their way south across the plaza.",
	  "The plaza streetwashers put the finishing touches on the plaza as "
	+ "they sweep and scrub efficiently.",
	  "A gathering of merchants walks past you arguing the details "
	+ "of a shipment.",
	  "A flock of pigeons flutters into the air from atop a nearby "
	+ "building.",
	  "A cool breeze off the bay ruffles banners and sways signs.",
	  "A page walks hurriedly past you."}));

	break;

    case TOD_DAY:
	ttell += one_of_list(({"A path clears before a merchant leading his draft "
	+ "horses and wagon west out of the plaza.",
	  "A knight, his squire marching behind him carrying several packs, makes "
	+ "his way through the crowd on foot to the noble quarter in the east.",
	  "A trio of aesthetics in vigorous discussion make their way south "
	+ "across the plaza.",
	  "A cloud passes across the sun for a moment.",
	  "The clouds drift gently across the sky spreading their bulbous "
	+ "shadows across the plaza.",
	  "A page walks hurriedly past you.",
	  "A messenger jogs swiftly past you."}));

	break;

    case TOD_TWILIGHT:
	ttell += one_of_list(({"An official walks past you, his elegantly dressed "
	+ "lady at his arm.  She nods at you as she fans herself with a small "
	+ "foldout fan.",
	  "A grey cloaked female human bumps into your side and then is gone, just "
	+ "another face in the crowd",
	  "The aroma of coffee with a hint of vanilla wafts on a breeze under "
	+ "your nose from somewhere in the plaza.",
	  "A squire of Solamnia clips along slowly across the plaza atop his "
	+ "steed.",
	  "A cloaked noble accompanied by a pair of knights and a "
	+ "retinue of courtesans push past the line to the palace and are "
	+ "ushered within by the guards.",
	  "A cool breeze off the bay ruffles banners and sways signs.",
	  "A page walks hurriedly past you.",
	  "A messenger jogs swiftly past you."}));

    break;

    case TOD_NIGHT:
	ttell += one_of_list(({"A grey cloaked male human bumps into your side "
	+ "and then is gone, just another face in the crowd.",
	  "A constable looks you over slowly before nodding his head and continuing "
	+ "on across the plaza.",
	  "A reveler sings a tavern ditty about a girl, too much sweets, lost her "
	+ "teeth, and something you can't clearly make out as his voice trails off "
	+ "in the distance.",
	  "A young woman helps a reveler leaning on her shoulder cut a crooked path "
	+ "across the plaza steering clear of constables.",
	  "A squire of Solamnia clips along slowly across the plaza atop his "
	+ "steed, a skin of wine in his hand.",
	  "A bearded merchant and a sailor walk through the plaza sharing a "
	+ "bottle of wine.",
	  "Clouds pass briefly across the sky overhead leaving only yellow lamp "
	+ "light on the translucent white streets.",
	  "A shadow passes over the roof of a nearby building.",
	  "A messenger jogs swiftly past you.",
	  "The lamp atop a tall, grey lamp post nearby flickers briefly."}));

	break;

    default:
	break;
    }
    return ttell;
}

string
get_dawn_hue()
{
	string dhue = "";
 
    switch(GET_TIMEOFDAY)
    {
	case TOD_DAWN:
    dhue += one_of_list(({"The sun rising above the eastern peaks spreads soft "
	+ "hues of purple fading to orange in the long, wispy clouds sailing slowly "
	+ "across the morning sky.", "The sun rising above the eastern peaks "
	+ "spreads tendrils of pink and orange fading to purple in the long, wispy "
	+ "clouds sailing slowly across the morning sky."}));
	break;

	case TOD_DAY:
	dhue += "Sunrise has passed.  You will have to wait another day.";
	break;

	case TOD_TWILIGHT:
    dhue += "Sunrise has passed.  You will have to wait another day.";
	break;

	case TOD_NIGHT:
	dhue += "You'll have to wait a little while longer for the sunrise.";
	break;
	default:
	break;
	}
	return dhue;
}

string
get_day_crowd()
{
	string dcrowd = "";
	string dline = "Among them to the north is a slow moving line of people "
	+ "at the entrance to the palace.";
 
    switch(GET_TIMEOFDAY)
    {
	case TOD_DAWN:
    dcrowd += "The crowds have not yet filled the plaza though the early "
	+ "shoppers, deliverers, and messengers are already going about their "
	+ "business.  " + dline;
	break;

	case TOD_DAY:
	dcrowd += "Crowds of people throng the plaza in the midday sun eating, "
	+ "drinking, looking for the best deals to be found in the various quarters "
	+ "and districts.  " + dline;
	break;

	case TOD_TWILIGHT:
    dcrowd += "The crowds of people milling about the plaza have thinned since "
	+ "afternoon leaving it easier to make your way across the plaza.  The "
	+ "strolling, relaxed evening crowd now mixes with the hustling, bustling "
	+ "afternoon shoppers.  " + dline;
	break;

	case TOD_NIGHT:
	dcrowd += "Though most people have retired for the night, constables, "
	+ "merchants selling wares, and revelers heading for the next tavern "
	+ "still make their way through the plaza.  " + dline;
	break;
	default:
	break;
	}
	return dcrowd;
}

string
get_night_revel()
{
	string drevel = "";
 
    switch(GET_TIMEOFDAY)
    {
	case TOD_DAWN:
    drevel += "There aren't any revelers left.";
	break;

	case TOD_DAY:
	drevel += "There aren't any revelers left.";
	break;

	case TOD_TWILIGHT:
    drevel += "There won't be anymore revelers out this early";
	break;

	case TOD_NIGHT:
	drevel += "Having drinks and socializing is a common pasttime in the "
	+ "palatial plaza, and nobles, merchants, officials, and common citizens "
	+ "alike are all passing through the plaza on their way to various inns "
	+ "and taverns as well as stopping for a drink at the cafes here.";
	break;
	default:
	break;
	}
	return drevel;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}

void
init()
{
    int i;
    ::init();
    add_action("leave_line","exit");
    add_action("leave_line","leave");
    for(i = moves; i < 20; i++)
      set_alarm(itof(i * 20),0.0,"little_move",TP);
    moves = 20;
    set_alarm(220.0,0.0,"my_move", TP);
}


int
leave_line(string str)
{
    int i;
    if (str == "line")
    {
        write("You leave the line.\n");
        say(QCTNAME(TP) + " leaves the line.\n");

        TP->move_living(0,ROOM + "plaza");
        return 1;
    }
    else
    {
        NF("Exit what?\n");
        return 0;
    }


}


void 
little_move(object player)
{   
    seteuid(getuid(TO));
    if (player && E(player) == TO)
      player->catch_msg("The line moves a little further.\n");
    /*tell_room(TO,"The line moves a little further.\n");*/
    moves--;
}


void
my_move(object player)
{
    seteuid(getuid(TO));
    if (present(player, TO))
    {
        write("Finally you reach the palace. The line ends here.\n");
        player->move_living("north", PALACE + "palace1", 0);
    }
}

int
leave_line_first()
{
    write("You still stand in line, remember? This means you " +
	  "have to exit the line first before wandering off!\n");
    return 1;
}

int
why_wait()
{
    write("What do you think you are waiting in line for?\n");
    return 1;
}
