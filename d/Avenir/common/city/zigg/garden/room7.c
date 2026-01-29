// Ziggurat galleria (room7.c)
// creator(s):   Zielia 2006
// last update:  Lilith, 2021: added poppies, they were missing
//                 from the garden.
// purpose:
// note:
// bug(s):
// to-do:
#pragma strict_types

#include <language.h>
#include <macros.h>
#include "zigg.h"

inherit ZIG_GARDEN;

private static int hour;

public void
zig_room(void)
{
    /* Avtime events. */
    AVTIME->add_event(this_object());
    hour = AVTIME->get_avenir_hour();

    set_long("The air is filled with the joyful twittering and plaintive "+
      "music of songbirds perching in silver cages suspended from "+
      "special ashwood poles set amongst the well pruned raspberry and "+
      "blackberry bushes in this section. The white flagstone path winds "+
      "its way between a grey marble bird bath and a matching stone "+
      "bench. Behind the bench, a backdrop of pale, sweet smelling "+
      "honeysuckle vines climb an ashwood trellis set against the black "+
      "stone wall of the Ziggurat. Alongside the bench, a mound of "+
	  "poppies grows, the feathery foliage and long stems moving "+
      "gracefully in the breeze. Beyond the aqueduct railing to the "+
      "north sprawls a dream-like view of the Forbidden City.\n");

    add_exit("room8", "east", "@@exit_string");
    add_exit("room6", "west", "@@exit_string");

}

static void
garden_items(void)
{
    ::garden_items();

    add_views("From this side of the "+
      "Ziggurat you can see some of the High Lord Executioner's enclave "+
      "to the northeast, opulent noble houses circle the High Lord's "+
      "palace on the central hill.", "enclave, giving it");

    add_rock("a picture of a hammer, painted all in blue.",
      ", the symbol of Plalgus");

    add_item(({"raspberry","raspberries","raspberry bush",
	"raspberry bushes",}),
      "The raspberry bushes are formed of a scrambling habit of dense "+
      "arching stems with sparse thorns and toothed leaves with "+
      "silver-white undersides. The branches root from the node tip "+
      "when they reach the ground forming thick tangled hedgerows all "+
      "around this section of the garden. Many of the bushes have "+
      "little, red, cup-like berries.\n");

    add_item(({"bushes","bush","blackberry","blackberries","blackberry bush",
	"blackberry bushes",}),
      "The blackberry bushes are formed of a scrambling habit of dense "+
      "arching stems carrying short, curved, very sharp spines and large "+
      "toothed leaves. The branches root from the node tip when they reach "+
      "the ground forming thick tangled hedgerows all around this section "+
      "of the garden. Many of the bushes have plump, glossy black berries "+
      "formed of clusters of many smaller round berries.\n");

    add_item(({"bird bath","bath","basin","grey bird bath","marble bird bath",}),
      "A grey marble bird bath is placed in the garden here as though "+
      "to attract birds. Normally it would help provide water to the "+
      "thirsty and overheated birds and be used both for drinking and "+
      "bathing. The bird bath is intricately carved with striking "+
      "patterns and made of lustrous polished marble. It stands at a "+
      "natural height and the base is weighted to prevent tipping. The "+
      "marble bath surface is textured to allow sure footing of birds "+
      "while water depth would accommodate both large and small birds. "+
      "The water in the basin looks stagnant, however, and is covered "+
      "with a fine film. The caged birds must never be allowed to use "+
      "it.\n");

    add_item(({"trellis","ash trellis","ash grey trellis","grey trellis",}),
      "Long thin pieces of ashwood criss cross in front of the black stone "+
      "of the ziggurat wall. Honeysuckle vines twist and cling to the wood "+
      "while pale blossoms emit a sweet fragrance.\n");

    add_item(({"pole","ash pole","ashwood pole","poles","ash poles",
	"ashwood poles",}),
      "Tall thick poles planted deep in the ground keep silver cages "+
      "hanging high out of reach.\n");

    add_item(({"cage","cages","silver cage","silver cages","bell cage",
	"bell cages","bell-shaped cage","bell-shaped cages"}),
      "Bell-shaped cages of shining silver hang high over head from ashwood "+
      "poles. Inside, songbirds of all sizes and colors perch and twitter.\n");

    add_item(({"bird","songbird","song bird","birds","songbirds","song birds",}),
      "Songbirds of every color and hue perch in silver cages, twittering "+
      "joyfully and singing mellifluously.\n");
	  
    add_item(({"mound", "mound of poppies", "feathery foliage"}),
	  "A mound of poppies with feathery foliage and long fuzzy stems "+
	  "moves gracefully in the breeze.\n"); 	

    add_fruit("blackberry");
    add_fruit("raspberry");


    add_object(ZIG_RLG + "bench_r7", 1, 0 );

}

static void
garden_flowers(void)
{
    add_flower("honeysuckle");
    add_flower("poppy", ({ "yellow"}));

    ::garden_flowers();
}

private int
birds_sing(int time, int count)
{
    string gods;

    switch(time)
    {
    case 1:
	gods = "Salilus and Sair";
	break;
    case 2:
	gods = "Tabris-Zeffar";
	break;
    case 3:
	gods = "Hahabi";
	break;
    case 4:
	gods = "Plalgus";
	break;
    case 5:
	gods = "Nantur and Thagrinus";
	break;
    case 6:
	gods = "Nitikas and Zahun";
	break;
    case 7:
	gods = "Cahor and Tarob";
	break;
    case 8:
	gods = "Tacritan and Zizuph";
	break;
    case 9:
	gods = "Zaren";
	break;
    case 10:
	gods = "Sabrus";
	break;
    case 11:
	gods = "Hizarbin and Sachluph";
	break;
    case 12:
	gods = "Jazur and Sisera";
	break;
    }

    switch(++count)
    {
    case 1:
	tell_room(TO, "Suddenly all the song birds begin to sing in "+
	    "mellifluous, well-trained tones.\n", 0, TO);
	break;
    case 2:
	tell_room(TO, "Somehow, each bird seems to know its part of the song, "+
	    "some singing melodically while others harmonize according to "+
	    "their natural tones.\n", 0, TO);
	break;
    case 3:
	tell_room(TO, "Some birds fall silent, allowing other birds to "+
	    "pick up the music before they all come back together in a "+
	    "glorious symphony.\n", 0, TO);

	break;
    case 4:
	foreach(object who : filter(all_inventory(), query_interactive))
	{
	     if (IS_SYBARITE(who))
	    {
		who->catch_tell("Listening carefully you pick out "+
		    "the base melody of the birds' song, recognizing it as a "+
		    "traditional song to praise "+ gods +" and to welcome "+
		    "the "+ LANG_ORD2WORD(hour) +" hour.\n");
	    }
	}
	break;
    default:
	count = -1;
	break;
    }
    if (count > 0)
	set_alarm(2.0, 0.0, &birds_sing(time, count));
}

public int
climb_trellis(string str)
{
    string god;
    string verb = query_verb();
    string *what;
    int size;

    if (!stringp(str))
	return NF(CAP(verb) + " what?\n");

    what = explode(str, " ");
    size = sizeof(what);

    if (what[(size - 1)] == "trellis")
    {
	write("You decide it would be a bad idea to risk harming "+
	    "the vines here without good reason.\n");
	return 1;
    }

    return 0;
}

int
drink_water(string str)
{
    if(!parse_command(str, ({ }), "[the] [water] [from] [the] %s", str))
	return 0;
    
    if (str == "bath" || str == "bird bath")
    {	
	if (TP->drink_soft(TP->drink_max() / 16 , 0))
        {
            TP->catch_msg("You cup your hands in the stagnant water of "+
	 	"the bird bath and lift them to your lips, taking " +
		"a big drink of the warm, dirty water.\nThe water tastes "+
		"foul and leaves your tongue coated with an unpleasant "+
		"film.\n");
            say(QCTNAME(TP)+" dips "+ HIS(TP) +" cupped hands into the "+
              "stagnant water of the bird bath and raises them to "+
		HIS(TP) +" lips, taking a big drink.\n");
        }
        else
	{
            write("You aren't thirsty at the moment.\n");
	}
    
        return 1;
    }
    if (str == "aqueduct")
    {
        if (TP->drink_soft(TP->drink_max() / 16 , 0))
        {
            TP->catch_msg("You cup your hands in the flowing water of the "+
	 	"aqueduct and lift them to your lips, taking a mouthful " +
		"of the cold, refreshing water.\n");
            say(QCTNAME(TP)+" dips "+ HIS(TP) +" cupped hands into the "+
              "flowing water of the aqueduct and raises them to "+
		HIS(TP) +" lips, drinking deeply.\n");
        }
        else
	{
            write("You aren't thirsty at the moment.\n");
	}

        return 1;
    }

}

public void
init(void)
{
    ::init();

    add_action(climb_trellis, "climb");
    add_action(drink_water, "drink");    
}

public int
avenir_event(int av_year, int av_week, int av_day, int av_hour)
{
    ::avenir_event(av_year, av_week, av_day, av_hour);
    birds_sing(hour = av_hour, 0);
    return 1;
}
