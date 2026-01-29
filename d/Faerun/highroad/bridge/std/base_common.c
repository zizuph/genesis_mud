#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit "/cmd/std/command_driver";
inherit "/std/room";
inherit "/d/Faerun/std/room_tell";


void add_features(string *features)
{
	int i,s;
	
	s=sizeof(features);
	for (i=0; i<s; i++) {
		switch(features[i]) {
			case "bridge":
				add_item(({"bridge", "old bridge", "stone bridge"}), 
					"This is an old stone bridge, standing over the rapid current " +
					"of Neverwinter River.\n");	
				break;
			
			case "river":
				add_item(({"river", "neverwinter river"}),
					"The river flows westwards toward the far away sea. It is wide " +
					"and its current is very strong.\n");
				break;			
			
			case "barricade":
			    add_item(({"barricade"}),
					"Made of wooden bales clearily indicates you are not supposed " +
					"to go north.\n");			
				break;
			
			case "nw_city_n_far":
				add_item(({"city", "neverwinter", "neverwinter city"}), 
					"It is a large, walled city far to the north. There is a slight mist " +
					"clouding the city.\n");
				break;
				
			case "nw_city_n_close":
			    add_item(({"city", "neverwinter", "neverwinter city"}), 
					"It is a large, walled city. " +
					"Large towers and beautiful buildings rise above the walls. They " +
					"look exquisite and glow in the light. Some large gardens can " +
					"be seen on the tops of the tallest buildings.\n");
				break;

			case "nw_walls":
				add_item(({"wall", "walls", "city walls", "neverwinter walls"}),
		        	"The walls are tall and solid looking. They surround the city, " +
				    "blocking enemies and protecting all behind them.\n");
				break;
			
			case "neverwinterf":
				add_item(({"woods", "forest", "neverwinter wood", "neverwinter woods"}),
			        "Tall trees make it up the forest. It stand in the distance to " +
			        "the east and spreads in that direction.\n");
			    break;
			
			case "grasslands":
				add_item(({"grasslands"}),
				    "They are a large, rolling area covered in tall grass. A few " +
				    "trees dot the land. The grass is tall and waves in the breeze.\n");
				add_item(({"grass"}),
				    "The grass covers the grasslands. It is " +
				    "green with slender leaves and waves in the breeze.\n");
				add_item(({"birds"}),
				    "They are various sizes and colors. Some fly around, chirping " +
				    "and singing in the grasslands.\n");
				add_item(({"trees"}),
				    "They grow in groups around the grasslands. They look strong and healthy.\n");
				add_item(({"bushes"}),
				    "They are all sizes and shapes, and grow scattered everywhere. They are low plants with many branches that spread outward.\n");
				break;
			
			case "highroad":
			    add_item(({"road", "highway", "high road", "highroad"}),
			        "The highway is wide and old looking. It is covered with large " +
			        "cobbles and looks well used. Bushes and grass have been cleared " +
			        "from the side of the road.\n");
			    add_item(({"cobbles", "cobblestones"}),
			        "They are rectangular shaped paving stones with curved tops. They " +
			        "are laid into the road and look worn.\n");
				break;														

			case "travellers":
			    add_room_tell("Some travellers push past you.");
			    break;
			    
			case "wagon":
			    add_room_tell("A wagon rumbles past along the road.");			
			    break;
			    
			case "mere":
			    add_item(({"marsh", "swamp"}),
			        "It is a large swamp full of low lying water and floating hillocks. " +
			        "It smells awful and dangerous. It's known as the Mere of Dead Men.\n");
			    add_item(({"mere", "mere of dead men"}),
			        "It is an ancient battle field where wars were waged and countless " +
			        "warriors died. Since that time, it has flooded and become haunted. " +
			        "Rumors say it is full of undiscovered treasure where only " +
			        "the strongest and bravest go, but few return, and unspeakable " +
			        "horrors live.\n");
			    add_item(({"water", "low lying water", "brackish water"}),
			        "The water is brackish but reeks of death and sickness. It " +
			        "looks diseased and has hillocks floating in it.\n");
			    add_item(({"hillocks", "hillock"}),
			        "They are islands of matted grass amd debris floating in the " +
			        "brackish water. The hillocks look large enough to barely support " +
			        "a traveller but still dangerous.\n");
			
			    add_room_tell("A cold mist drifts across the highway.");
			    add_room_tell("The smell of stench drifts past you from the west.");
			    add_room_tell("Gruff noises echo from the mere.");
				break;
												
			case "hills":
			    add_item(({"hills"}),
			        "They are brown and rocky looking. The hills are rolling and " +
			        "covered with grass and windblown.\n");
				break;			

			case "sword_mts":
			    add_item(({"mountains", "sword mountains"}),
			        "The mountains are tall and rough looking. They run roughly " +
			        "northeast and southwest. The range isn't very large, but " +
			        "towers in the distance. The mountains are known by the locals " +
			        "as the Sword Mountains.\n");
				break;			

			case "sword_mts1":
			    add_item(({"mountains", "sword mountains"}),
			        "The mountains are tall and rugged looking. They run roughly " +
			        "northeast and southwest. The sides are steep and higher than " +
			        "the surrounding land. A rocky trail winds through it, past " +
			        "large rocks and boulders.\n");
			    add_item(({"large rocks", "rocks", "stone", "stones"}),
			        "They are large and scattered around the mountain. Many are " +
			        "dark and various sizes, and rolled down from higher up on the " +
			        "mountain.\n");
			    add_item(({"boulders"}),
			        "They are large, round rocks laying around the mountainside. " +
			        "Most of them are taller than a man. Some are cracked and " +
			        "splintered. Some are partially buried in the ground.\n");
			    add_item(({"dirt", "ground", "soil"}),
			        "The dirt is dark brown and rocky. It is made up of rocks that " +
			        "have been ground down to grit and pebbles.\n");
			    add_item(({"grit"}),
			        "It is brown, red, and other earth colors. It is composed of " +
			        "rocks that have been ground down to small bits. Rocks and " +
			        "pebbles are mixed into it.\n");
				break;			
				
			case "bandit_path":
			    add_item(({"trail", "path"}),
			        "The trail is little more than a line in the hills. It is hidden from everyone but the most observant eyes.\n");
			    add_item(({"grass"}),
			        "It is thin and gray looking. It grows in clumps scattered across the hills.\n");
			    add_item(({"bushes"}),
			        "They grow in clumps on the hills. The bushes look windblown and stunted.\n");
			    add_item(({"rocks", "gravel"}),
			        "They are broken and jagged, and of various sizes. The rocks and gravel are different colors and lay scattered across the hills.\n");
				break;							
			default:
				write_file("/d/Faerun/log/features", 
					"Unsupported feature '" + features[i] + "' in " + file_name(this_object()) + "\n");
		}
	}
}


// BACKWARD COMPATIBILITY

void add_neverwinterf()
{
    add_features(({"neverwinterf", "fixme"}));
}

void add_grasslands()
{
    add_features(({"grasslands", "fixme"}));
}

void add_highroad()
{
	add_features(({"highroad", "travellers", "wagon", "fixme"}));
}


void add_mere()
{
	add_features(({"mere", "fixme"}));
}


void add_hills()
{
	add_features(({"hills", "fixme"}));
}

void add_sword_mts()
{
	add_features(({"sword_mts", "fixme"}));
}

// Up on the mountain
void add_sword_mts1()
{
    add_features(({"sword_mts1", "fixme"}));
}

void add_bandit_path()
{
    add_features(({"bandit_path", "hills", "fixme"}));
}

