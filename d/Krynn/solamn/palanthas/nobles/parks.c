/* Mortis 12.2005 */

#include "../local.h"
#include CLOCKH
#include <cmdparse.h>
#include <macros.h>

inherit NOBLE_BASE;

string
query_to_jail()
{
  return "north";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "Fields of low, firm grass spread out across the nobles "
	+ "park of Palanthas stretching to the north surrounding small oases "
	+ "of artfully arranged, exotic flowers, bushes, and short trees.  "
	+ "A hedge of tall bushes forms a wall around the park except north "
	+ "where the park fountain spouts arcs of water.  In front of the center "
	+ "of the south hedge is a curved flower patch of artfully arranged "
	+ "flowers.  ";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += road + "A cool, misty breeze blows south from the bay as rays of "
	+ one_of_list(({"pale purple ", "soft pink ", "pale orange ",
	  "grey and pink "})) + "from the sun rising above the hedge in the east "
	+ "catch the tops of the trees setting a sparkle the dewy leaves in "
	+ "bands of green and silver.\n";
	break;
	
    case TOD_DAY:
	desc += road + "A cool breeze blows south from the bay as the midday sun "
	+ "shines down its golden rays upon the leaves of the trees and petals "
	+ "of the flowers.\n";
	break;

    case TOD_TWILIGHT:
	desc += road + "A cool, misty breeze blows south from the bay as the "
	+ "last rays of the sun setting behind the western hedge catch the tops "
	+ "of the trees lighting them in shades of emerald green.\n";
    break;

    case TOD_NIGHT:
	desc += road + "The moon and stars shed pale light across the firm grass "
	+ "of the nobles park as a cool, night breeze blows south from the bay.  "
	+ "Moonlight catches silver streams from the fountain to the north as "
	+ "they arc back down with tinkling bloops into the stone pool below.\n";
    break;

    default:
	break;
    }
    return desc;
}

void
reset_palan_room()
{

}

void create_palan_room()
{
    SHORT("The south end of the nobles park of Palanthas");
    LONG("@@get_time_desc@@");

	ITEM(({"hedge", "hedges", "bush", "bushes"}), "A tall hedge of well "
	+ "tended and cultured bushes trimmed and squared off on all sides "
	+ "rises over ten feet to all sides except the north.  It is "
	+ "too dense to peer all the way through.  The base of the bushes "
	+ "reveals their roots are thick as small trees.\n");
	ITEM(({"base", "roots"}), "Thick roots as wide as small trees rise from "
	+ "the ground up to the heights of the hedge.  These bushes must be old "
	+ "and very well tended.\n");
	ITEM("fountain", "The fountain to your north is a small scale replica of "
	+ "Arms in the Merchants district.  Rising from a white, marble pool, "
	+ "the Tower of it stands nearly eight feet.  Streams of water arc high "
	+ "into the air from the tops of its four corners before falling with "
	+ "tinkling bloops into the stone pool below.\n");
	ITEM(({"flower", "flowers", "oasis", "oases", "tree", "trees"}),
	  "Small oases of artfully arranged, exotic flowers, bushes, and "
	+ "short trees dot the park amidst its lush green fields of grass.  "
	+ "The flowers especially must have been planted by a skilled gardener "
	+ "as their naturally growing beauty and arrangement is quite striking."
	+ "\n");
	ITEM(({"patch", "flower patch"}), "An arc of artfully arranged, exotic "
	+ "flowers sits in front of the south hedge of bushes.  To its north "
	+ "it curves around a circle of especially thick grass raised a half "
	+ "foot higher around its rim like a grassy bench.\n");
	ITEM(({"bench", "grassy bench", "circle", "thick grass", "grass circle",
		   "circle of grass"}), "North of the flower patch by the south "
	+ "hedge is a circle of especially thick grass raised a half foot "
	+ "higher around its rim like a grassy bench.  If it could support "
	+ "your weight it might prove a comfortable seat.\n");
	ITEM(({"field", "fields", "grass"}), "Fields of low, firm grass cover "
	+ "the park.  The grass itself is over half a foot high and so lush and "
	+ "thick that you hardly sink into it while on it.  It's like walking "
	+ "on carpet.\n");
	ITEM(({"hanging lamp", "short lamppost"}), "A lamp suspended from a "
	+ "chain on the long, curved arm of a short lamppost sheds light upon "
	+ "the flower patch from which the post rises.\n");

	set_tell_time(140);
	add_tell("There is a rustling from the hedge to the south.  A "
	+ "sparrow flaps vigorously as it flies out from the top.\n");
	add_tell("There is a slight rustling from an oasis of flowers and "
	+ "bushes in the east.\n");
	add_tell("The hedges in the east rustle briefly as the breeze picks "
	+ "up momentarily.\n");
	add_tell("The hedges in the west rustle briefly as the breeze picks "
	+ "up momentarily.\n");
	add_tell("As the wind picks up, leaves are blown from the hedges and "
	+ "trees.\n");
	add_tell("A humming bird hovers before an exotic, drooping red flower to "
	+ "the southeast.\n");
	add_tell("A white rabbit pops its head out of the hedges to the "
	+ "south, and then is gone in a flash.\n");
	add_tell("A nearby bird trills sweetly, but you did not see from "
	+ "where it sang.\n");
	add_tell("Puffy clouds float lazily by overhead.\n");
	add_tell("A large white cloud drifts slowly by overhead.\n");
	add_tell("A page hurries by looking for someone.\n");
	add_tell("A lamp hanging from a short lamppost by a flower patch "
	+ "flickers briefly.\n");
	add_tell("Water streams out of the four corners atop the south fountain "
	+ "before arcing into the stone pool below with tinkling bloops.\n");
	add_tell("Water streams out of the four corners atop the south fountain "
	+ "before arcing into the stone pool below with tinkling bloops.\n");
	add_tell("Water streams out of the four corners atop the south fountain "
	+ "before arcing into the stone pool below with tinkling bloops.\n");

	add_smell("vampire", "Cool air blowing south off the bay mingles here "
	+ "with the smells of lush, wet greenery.  The scent of blood is weak "
	+ "here.");
    add_smell("morgul", "Misty air blowing south off the bay mingles here "
	+ "with the smell of greenery.");
	add_smell("human", "Misty air blowing south off the bay mingles here with "
	+ "the smell of lush greenery and fresh air.");
	add_smell("elf", "Misty air blowing south off the bay mingles here with "
	+ "the scent of lush greenery, flowers, and water from the park.");
	add_smell("goblin", "The fresh smells of dirt and green things mix here "
	+ "with cool air blowing south off the bay.");
	add_smell("dwarf", "Misty air blowing south off the bay mingles here "
	+ "with the smells of greenery.");
	add_smell("hobbit", "Misty air blowing south off the bay mingles here "
	+ "with the fresh smells of a lush green park with fragrant flowers and "
	+ "hopefully a piece of fruit or two on some of the trees.");
	add_smell("gnome", "There's moisture in the air blowing south off the "
	+ "bay.  Adding to its salty flavor are the smells of plant life and "
	+ "flowing water.");
	add_smell("minotaur", "Misty air blowing south off the bay mingles here "
	+ "with the lush, wet scents of green growing things.");
	add_smell("halfhuman", "Misty air blowing south off the bay mingles here "
	+ "with the smell of lush greenery.");
	add_smell("halfelf", "Misty air blowing south off the bay mingles here "
	+ "with the smells of lush, wet greenery with a hint of flowers.");
	add_smell("orc", "Misty air blowing south off the bay mingles here with "
	+ "the smells of water, dirt, and plants.");
	add_smell("hobgoblin", "Misty air blowing south off the bay mingles here "
	+ "with the smells of a lush park.");
	add_smell("kender", "Misty air blowing south off the bay mingles here "
	+ "with the bright smells of plants and bushes and trees and no doubt "
	+ "pretty flowers all over.  Are there fruits or berries around?  You "
	+ "don't know yet!");
	add_smell("noldor", "Misty air blowing south off the bay mingles here "
	+ "with the smells of a human cultured park with halfway decently "
	+ "tended flowers.");
	add_smell("drow", "Moist air blowing south off the saltwater bay mingles "
	+ "here with the bizarre and foreign smells of a human cultured flowers, "
	+ "plants, and grasses.\n");
	add_smell("unknown", "You smell the park, but your race is unknown to "
	+ "the immortals!  Please mail Krynn with your race.");

	EXIT(NOBLE + "park", "north", 0, 0);

	reset_palan_room();

}

void
init()
{
  ::init();
  add_action("action_sit", "sit");
  add_action("action_stand", "stand");
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}

int 
action_sit(string str)
{
        if(TP->query_prop(TSIT))
        {
                write("But you are already sitting on a bench! How do you "
				+ "expect to sit in two places at once?\n");
                return 1;
        }
          
        if(str == "around bench" | str == "around a bench" | 
		   str == "at bench" | str == "at a bench" | str == "by bench" |
		   str == "by a bench" | str == "bench" |
		   str == "on a bench" | str == "on the bench" |
		   str == "on one of the benches" | str == "grass" |
		   str == "in grass" | str == "in circle" |
		   str == "circle" | str == "on circle" |
	       str == "on grass" | str == "on the grass" | str == "in the grass") 
        {
                TP->catch_msg("You sit down on the high, thick grass around "
				+ "the rim of the grassy circle by the flower patch.  The "
				+ "thick green grass gives at little as you rest your weight "
				+ "upon it.  It is surprisingly lush and comfortable.\n");
                say(QCTNAME(TP) + " sits down on the high, thick grass "
				+ "around the rim of the grassy circle by the flower "
				+ ".\n");
                TP->add_prop(TSIT, 1);
                TP->add_prop(LIVE_S_EXTRA_SHORT," is sitting on the high, "
				+ "thick grass inside the flower patch");
                return 1;
        }
	
        else
        {
			TP->catch_msg("Where would you like to sit?  In the grass?\n");
			return 1;
        }
        
        return 1;
}

int 
action_stand(string str)
{
        if(str == "up" || str != "up")
        {
                if(TP->query_prop(TSIT))
                {
                        
                        TP->catch_msg("You stand up from the grass.  It "
						+ "slowly springs back up as if no one had ever "
						+ "sat upon it.\n");
                        say(QCTNAME(TP)+" stands up from high, thick grass "
						+ "within the flower patch.\n");
                        TP->remove_prop(TSIT);
                        TP->remove_prop(LIVE_S_EXTRA_SHORT);
                        return 1;
                }

        }
        
        else
        {
                TP->catch_msg("Stand?  Stand up?\n");
                return 1;
        }
        
        return 1;
}

void leave_inv(object ob, object to)
{
        ::leave_inv(ob, to);    
        
        if(!objectp(to) || !objectp(ob))
                return;
                
        if(TP->query_prop(TSIT))
        {
                TP->catch_msg("You stand up from the grassy bench before "
				+ "leaving.\n");
                say(QCTNAME(TP) + " stands up from the grassy bench as "
				+ HE(TP) + " leaves.\n");
                TP->remove_prop(LIVE_S_EXTRA_SHORT);
                TP->remove_prop(TSIT);
        }

}
