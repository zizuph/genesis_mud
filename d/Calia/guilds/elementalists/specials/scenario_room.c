
/*
 * scenario_room.c
 *
 * This is the scenario room. After becoming a Master
 * Cleric, players will venture to this scenario room
 * to experience some Calian history and see the unique 
 * spells of each branch before chosing which branch 
 * they want to join. Only one player is allowed
 * in here at a time (as to not break the immersion). 
 * 
 * Jaacar (Mike Phipps), April 2017
 *
 */
 
#pragma strict_types
#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

#include "defs.h"

int occupied = 0;
int phase = 0;

object scenario_player = 0;

string scenario = "";
string scenario_short_desc = "A void";
string scenario_long_desc = "You are floating in some place you don't recognize. "+
                            "It is neither light, nor dark. It isn't warm, nor "+
                            "cold. You sense nothing, feel nothing. You seem to "+
                            "be nowhere.\n";

public void start_scenario(string element, object player);
public void scenario_phase_two(object player);
public void scenario_phase_three(object player);
public void scenario_phase_four(object player);
public void scenario_phase_five(object player);
public void scenario_phase_six(object player);
public void scenario_phase_seven(object player);
public void scenario_end(object player);
public void return_player(object player);
public void clear_scenario();

void
create_room()
{
    set_short("@@short_desc");
    set_long("@@long_desc");
    
    add_item(({"road"}),"@@road_desc");
    add_item(({"corpse"}),"@@corpse_desc");
    add_item(({"lethos", "Lethos"}),"@@lethos_desc");
    add_item(({"kaikos", "Kaikos"}),"@@kaikos_desc");
    add_item(({"mountain"}),"@@mountain_desc");
    add_item(({"trees"}),"@@trees_desc");
    add_item(({"stronghold"}),"@@stronghold_desc");
    add_item(({"people"}),"@@people_desc");
    add_item(({"barbarians"}),"@@barbarians_desc");
    add_item(({"barbarian"}),"@@barbarian_desc");
    add_item(({"shaman"}),"@@shaman_desc");
    add_item(({"alleyway"}),"@@alleyway_desc");
    add_item(({"flames"}),"@@flames_desc");
    add_item(({"fire"}),"@@fire_desc");
    add_item(({"wall"}),"@@wall_desc");
    add_item(({"wall of fire"}),"@@wall_of_fire_desc");
    add_item(({"wall of flames"}),"@@wall_of_flames_desc");
    add_item(({"firewall"}),"@@firewall_desc");
    add_item(({"beach"}),"@@beach_desc");
    add_item(({"cilla", "Cilla"}),"@@cilla_desc");
    add_item(({"forest"}),"@@forest_desc");
    add_item(({"buckets"}),"@@buckets_desc");
    add_item(({"bucket"}),"@@bucket_desc");
    add_item(({"encampment"}),"@@encampment_desc");
    add_item(({"leda","Leda"}),"@@leda_desc");
    add_item(({"town"}),"@@town_desc");
    add_item(({"greensea","Greensea"}),"@@greensea_desc");
    add_item(({"creatures"}),"@@creatures_desc");
    add_item(({"creature"}),"@@creature_desc");
    add_item(({"krougs"}),"@@krougs_desc");
    add_item(({"kroug"}),"@@kroug_desc");
    add_item(({"island"}),"@@island_desc");
    add_item(({"city"}),"@@city_desc");
    add_item(({"Menisca","menisca"}),"@@menisca_desc");
    add_item(({"Conchoida","conchoida"}),"@@conchoida_desc");
    add_item(({"boat"}),"@@boat_desc");
    add_item(({"boats"}),"@@boats_desc");
    add_item(({"dock"}),"@@dock_desc");
    add_item(({"docks"}),"@@docks_desc");
    add_item(({"sea"}),"@@sea_desc");
    add_item(({"water"}),"@@water_desc");
    add_item(({"waters"}),"@@waters_desc");
    add_item(({"body"}),"@@body_desc");
    add_item(({"bodies"}),"@@bodies_desc");
    add_item(({"sword"}),"@@sword_desc");
    add_item(({"Steerax","steerax"}),"@@steerax_desc");
    add_item(({"pelias","Pelias"}),"@@pelias_desc");
    add_item(({"kyrullian","Kyrullian"}),"@@kyrullian_desc");
    add_item(({"kyrullians","Kyrullians"}),"@@kyrullians_desc");
    add_item(({"man"}),"@@man_desc");
    add_item(({"cot"}),"@@cot_desc");
    add_item(({"cots"}),"@@cots_desc");
    add_item(({"blanket"}),"@@blanket_desc");
    add_item(({"blankets"}),"@@blankets_desc");
    add_item(({"temple","Temple"}),"@@temple_desc");
    add_item(({"statue"}),"@@statue_desc");
    add_item(({"basin"}),"@@basin_desc");
    add_item(({"harbour"}),"@@harbour_desc");
    add_item(({"guard"}),"@@guard_desc");
    add_item(({"guards"}),"@@guards_desc");
    add_item(({"gate"}),"@@gate_desc");
    add_item(({"gates"}),"@@gates_desc");
	add_item(({"roundabout"}),"@@roundabout_desc");
	add_item(({"rocks"}),"@@rocks_desc");
	add_item(({"pile"}),"@@pile_desc");
	add_item(({"Sehis","sehis"}),"@@sehis_desc");
	add_item(({"garden"}),"@@garden_desc");
	add_item(({"plants"}),"@@plants_desc");
	add_item(({"rubble"}),"@@rubble_desc");
	add_item(({"tapestry"}),"@@tapestry_desc");
	add_item(({"tapestries"}),"@@tapestries_desc");
	add_item(({"ashes"}),"@@ashes_desc");
	add_item(({"mosaic"}),"@@mosaic_desc");
	add_item(({"wight"}),"@@wight_desc");
	add_item(({"stairs"}),"@@stairs_desc");
	add_item(({"stairwell"}),"@@stairwell_desc");
	add_item(({"ghoul"}),"@@ghoul_desc");
	add_item(({"ghouls"}),"@@ghouls_desc");
	add_item(({"Jardeth","jardeth"}),"@@jardeth_desc");
	add_item(({"Tahla","tahla"}),"@@tahla_desc");
	add_item(({"hall"}),"@@hall_desc");
	add_item(({"hallway"}),"@@hallway_desc");
	add_item(({"corpses"}),"@@corpses_desc");
	add_item(({"Conduit","conduit"}),"@@conduit_desc");
	add_item(({"shadowy wall"}),"@@shadowy_wall_desc");   

    add_prop(ROOM_M_NO_ATTACK,"You cannot attack in here, you are in a "+
        "sacred place!\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK,"You cannot attack in here, you are in "+
        "a sacred place!\n");

}

public string
short_desc()
{
	return scenario_short_desc;
}

public string
long_desc()
{
	return scenario_long_desc;
}

public string
road_desc()
{
	switch(scenario)
	{
		case "fire":
			switch(phase)
			{
				case 1:
					return "It is a dirt road that meanders through the moorlands.\n";
					break;
			    case 2:
			    	return "It is a dirt road at the base of a mountain.\n";
			    	break;
				default:
					return "You find no road.\n";
					break;
			}
			break;
	}
}

public string
corpse_desc()
{
	switch(scenario)
	{
		case "fire":
			switch(phase)
			{
				case 1:
					return "It is the corpse of a human located on the road.\n";
					break;
				case 4:
					return "It is the corpse of a large barbarian with a smouldering "+
					    "crater-like wound in its chest.\n";
					break;
				default:
					return "You find no corpse.\n";
					break;
			}
			break;
		case "life":
			switch(phase)
			{
				case 5:
					return "They are the corpses of Jardeth and Tahla.\n";
					break;
				default:
					return "You find no corpse.\n";
					break;
			}
			break;
	}
}

public string
corpses_desc()
{
	switch(scenario)
	{
		case "life":
			switch(phase)
			{
				case 5:
					return "They are the corpses of Jardeth and Tahla.\n";
					break;
				default:
					return "You find no corpses.\n";
					break;
			}
			break;
	}
}

public string
lethos_desc()
{
	switch(scenario)
	{
		case "fire":
			switch(phase)
			{
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
			    case 6:
			    case 7:
					return "Lethos is a Kyrullian Fire Cleric.\n"+
						   "He is tall and lean for an elf.\n"+
						   "He looks like the image of perfection.\n"+
						   "He has a Kyrullian aurua surrounding him.\n"+
						   "He seems to be feeling very well.\n";
					break;
				default:
					return "You find no lethos.\n";
					break;
			}
			break;
	}
}

public string
kaikos_desc()
{
	switch(scenario)
	{
		case "fire":
			switch(phase)
			{
				case 1:
				case 2:
				case 3:
					return "Kaikos is a Kyrullian Fire Cleric.\n"+
						   "He is tall and lean for an elf.\n"+
						   "He looks like the image of perfection.\n"+
						   "He has a Kyrullian aurua surrounding him.\n"+
						   "He seems to be feeling very well.\n";
					break;
				default:
					return "You find no kaikos.\n";
					break;
			}
			break;
	}
}

public string
mountain_desc()
{
	switch(scenario)
	{
		case "fire":
			switch(phase)
			{
				case 2:
			    case 3:
			    case 4:
			    case 5:
					return "It is a tall, rocky mountain.\n";
					break;
				default:
					return "You find no mountain.\n";
					break;
			}
			break;
	}
}

public string
trees_desc()
{
	switch(scenario)
	{
		case "fire":
			switch(phase)
			{
				case 2:
					return "They are trees at the base of the mountain.\n";
					break;
				default:
					return "You find no trees.\n";
					break;
			}
			break;
		case "earth":
			switch(phase)
			{
				case 2:
				case 3:
			    case 4:
					return "There are hundreds of trees around you in the "+
					    "forest, all reaching high into the air.\n";
					break;
				default:
					return "You find no trees.\n";
					break;
			}
	}
}

public string
stronghold_desc()
{
	switch(scenario)
	{
		case "fire":
			switch(phase)
			{
				case 3:
				case 4:
				case 5:
					return "It is a mighty stronghold situated on the top of a mountain.\n";
					break;
				default:
					return "You find no stronghold.\n";
					break;
			}
			break;
	}
}

public string
people_desc()
{
	switch(scenario)
	{
		case "fire":
			switch(phase)
			{
				case 3:
				case 4:
				case 5:
				case 6:
					return "These people all have the same energy or aura that Lethos and "+
					    "Kaikos have.\n";
					break;
				default:
					return "You find no people.\n";
					break;
			}
			break;
		case "earth":
			switch(phase)
			{
				case 3:
			    case 4:
			    case 5:
			    case 6:
					return "These people all have the same energy or aura that Cilla has.\n";
					break;
				default:
					return "You find no people.\n";
					break;
			}
		case "air":
			switch(phase)
			{
				case 1:
				case 2:
				case 3:
				case 4:
					return "These people seem impoverished and none of them seem to have the "+
					    "same energy or aura that Leda has.\n";
					break;
				case 5:
				case 6:
				case 7:
					return "These people seem well off and all of them seem to have the "+
					    "same energy or aura that Leda has.\n";
					break;
				default:
					return "You find no people.\n";
					break;
			}
		case "water":
			switch(phase)
			{
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:    
					return "These people seem well off and all of them seem to have the "+
					    "same energy or aura as other Kyrullians you have seen.\n";
					break;
				default:
					return "You find no people.\n";
					break;
			}
	}
}

public string
barbarians_desc()
{
	switch(scenario)
	{
		case "fire":
			switch(phase)
			{
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
					return "The barbarians are terrifying looking creatures.\n";
					break;
				default:
					return "You find no barbarians.\n";
					break;
			}
			break;
		case "earth":
			switch(phase)
			{
				case 3:
				case 4:
					return "The barbarians are terrifying looking creatures.\n";
					break;
				default:
					return "You find no barbarians.\n";
					break;
			}
			break;
	}
}

public string
barbarian_desc()
{
	switch(scenario)
	{
		case "fire":
			switch(phase)
			{
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
					return "The barbarians are terrifying looking creatures.\n";
					break;
				default:
					return "You find no barbarian.\n";
					break;
			}
			break;
		case "earth":
			switch(phase)
			{
				case 3:
				case 4:
					return "The barbarians are terrifying looking creatures.\n";
					break;
				default:
					return "You find no barbarian.\n";
					break;
			}
			break;
	}
}

public string
shaman_desc()
{
	switch(scenario)
	{
		case "fire":
			switch(phase)
			{
				case 5:
					return "The shaman is like the other barbarians except he seems to use "+
					    "magic rather than weapons.\n";
					break;
				default:
					return "You find no shaman.\n";
					break;
			}
			break;
	}
}

public string
alleyway_desc()
{
	switch(scenario)
	{
		case "fire":
			switch(phase)
			{
				case 6:
				case 7:
					return "The alleyway runs beside the stronghold.\n";
					break;
				default:
					return "You find no alleyway.\n";
					break;
			}
			break;
	}
}

public string
flames_desc()
{
	switch(scenario)
	{
		case "fire":
			switch(phase)
			{
				case 6:
					return "The flames form a wall spreading from one side of the alleyway to "+
					    "the other, towering high above Lethos.\n";
					break;
				default:
					return "You find no flames.\n";
					break;
			}
			break;
	}
}

public string
fire_desc()
{
	switch(scenario)
	{
		case "fire":
			switch(phase)
			{
				case 6:
					return "The fire forms a wall spreading from one side of the alleyway to "+
					    "the other, towering high above Lethos.\n";
					break;
				default:
					return "You find no fire.\n";
					break;
			}
			break;
	}
}

public string
wall_desc()
{
	switch(scenario)
	{
		case "fire":
			switch(phase)
			{
				case 6:
					return "The flames form a wall spreading from one side of the alleyway to "+
					    "the other, towering high above Lethos.\n";
					break;
				default:
					return "You find no wall.\n";
					break;
			}
			break;
		case "life":
			switch(phase)
			{
				case 6:
				case 7:
					return "It is a large shadowy wall blocking the entrance to the Conduit chamber.\n";
					break;
				default:
					return "You find no wall.\n";
					break;
			}
			break;
	}
}

public string
shadowy_wall_desc()
{
	switch(scenario)
	{
		case "life":
			switch(phase)
			{
				case 6:
				case 7:
					return "It is a large shadowy wall blocking the entrance to the Conduit chamber.\n";
					break;
				default:
					return "You find no shadowy wall.\n";
					break;
			}
			break;
	}
}

public string
wall_of_fire_desc()
{
	switch(scenario)
	{
		case "fire":
			switch(phase)
			{
				case 6:
					return "The fire forms a wall spreading from one side of the alleyway to "+
					    "the other, towering high above Lethos.\n";
					break;
				default:
					return "You find no wall of fire.\n";
					break;
			}
			break;
	}
}

public string
wall_of_flames_desc()
{
	switch(scenario)
	{
		case "fire":
			switch(phase)
			{
				case 6:
					return "The flames form a wall spreading from one side of the alleyway to "+
					    "the other, towering high above Lethos.\n";
					break;
				default:
					return "You find no wall of flames.\n";
					break;
			}
			break;
	}
}

public string
firewall_desc()
{
	switch(scenario)
	{
		case "fire":
			switch(phase)
			{
				case 6:
					return "The fire forms a wall spreading from one side of the alleyway to "+
					    "the other, towering high above Lethos.\n";
					break;
				default:
					return "You find no firewall.\n";
					break;
			}
			break;
	}
}

public string
beach_desc()
{
	switch(scenario)
	{
		case "earth":
			switch(phase)
			{
				case 1:
					return "It is a sandy beach on the shores of Calia.\n";
					break;
				default:
					return "You find no beach.\n";
					break;
			}
			break;
		case "air":
			switch(phase)
			{
				case 1:
				case 2:
				case 3:
				case 4:
					return "It is a sandy beach on the shores of Calia.\n";
					break;
				default:
					return "You find no beach.\n";
					break;
			}
	}
}

public string
cilla_desc()
{
	switch(scenario)
	{
		case "earth":
			switch(phase)
			{
				case 1:
			    case 2:
			    case 3:
			    case 4:
			    case 5:
			    case 6:
			    case 7:
					return "Cilla is a Kyrullian Earth Cleric.\n"+
						   "She is tall and lean for a human.\n"+
						   "She looks like the image of perfection.\n"+
						   "She has a Kyrullian aurua surrounding her.\n"+
						   "She seems to be feeling very well.\n";
					break;
				default:
					return "You find no cilla.\n";
					break;
			}
			break;
	}
}

public string
buckets_desc()
{
	switch(scenario)
	{
		case "earth":
			switch(phase)
			{
				case 1:
					return "They are large buckets filled with water. They look "+
					    "very heavy.\n";
					break;
				default:
					return "You find no buckets.\n";
					break;
			}
			break;
	}
}

public string
bucket_desc()
{
	switch(scenario)
	{
		case "earth":
			switch(phase)
			{
				case 1:
					return "They are large buckets filled with water. They look "+
					    "very heavy.\n";
					break;
				default:
					return "You find no bucket.\n";
					break;
			}
			break;
	}
}

public string
forest_desc()
{
	switch(scenario)
	{
		case "earth":
			switch(phase)
			{
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
					return "It is a dense forest in Calia with hundreds of trees in it.\n";
					break;
				default:
					return "You find no bucket.\n";
					break;
			}
			break;
	}
}

public string
encampment_desc()
{
	switch(scenario)
	{
		case "earth":
			switch(phase)
			{
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
					return "It is a small encampment of people in the forest.\n";
					break;
				default:
					return "You find no encampment.\n";
					break;
			}
			break;
	}
}

public string
leda_desc()
{
	switch(scenario)
	{
		case "air":
			switch(phase)
			{
				case 1:
			    case 2:
			    case 3:
			    case 4:
			    case 5:
			    case 6:
			    case 7:
					return "Leda is a Kyrullian Air Cleric.\n"+
						   "She is tall and lean for a gnome.\n"+
						   "She looks like the image of perfection.\n"+
						   "She has a Kyrullian aurua surrounding her.\n"+
						   "She seems to be feeling very well.\n";
					break;
				default:
					return "You find no leda.\n";
					break;
			}
			break;
	}
}

public string
pelias_desc()
{
	switch(scenario)
	{
		case "water":
			switch(phase)
			{
				case 1:
			    case 2:
			    case 3:
			    case 4:
			    case 5:
			    case 6:
			    case 7:
					return "Pelias is a Kyrullian Water Cleric.\n"+
						   "He is very tall and lean for a elf.\n"+
						   "He looks like the image of perfection.\n"+
						   "He has a Kyrullian aurua surrounding him.\n"+
						   "He seems to be feeling very well.\n";
					break;
				default:
					return "You find no pelias.\n";
					break;
			}
			break;
	}
}

public string
town_desc()
{
	switch(scenario)
	{
		case "air":
			switch(phase)
			{
				case 1:
				case 2:
				case 3:
				case 4:
					return "It is the small beach town of Greensea, located on the shores "+
					    "of Calia.\n";
					break;
				default:
					return "You find no town.\n";
					break;
			}
			break;
	}
}

public string
greensea_desc()
{
	switch(scenario)
	{
		case "air":
			switch(phase)
			{
				case 1:
				case 2:
				case 3:
				case 4:
					return "It is the small beach town of Greensea, located on the shores "+
					    "of Calia.\n";
					break;
				default:
					return "You find no greensea.\n";
					break;
			}
			break;
	}
}

public string
creatures_desc()
{
	switch(scenario)
	{
		case "air":
			switch(phase)
			{
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:					
					return "It is a large group of monstrous looking creatures. Upon closer "+
					    "examination, you realize these are krougs!\n";
					break;
				default:
					return "You find no creatures.\n";
					break;
			}
			break;
	}
}

public string
creature_desc()
{
	switch(scenario)
	{
		case "air":
			switch(phase)
			{
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
					return "It is a large group of monstrous looking creatures. Upon closer "+
					    "examination, you realize these are krougs!\n";
					break;
				default:
					return "You find no creature.\n";
					break;
			}
			break;
	}
}

public string
krougs_desc()
{
	switch(scenario)
	{
		case "air":
			switch(phase)
			{
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
					return "It is a large group of monstrous looking creatures. Upon closer "+
					    "examination, you realize these are krougs!\n";
					break;
				default:
					return "You find no krougs.\n";
					break;
			}
			break;
		case "water":
			switch(phase)
			{
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
					return "It is a large group of monstrous looking creatures. Upon closer "+
					    "examination, you realize these are krougs!\n";
					break;
				default:
					return "You find no krougs.\n";
					break;
			}
			break;
	}
}

public string
kroug_desc()
{
	switch(scenario)
	{
		case "air":
			switch(phase)
			{
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
					return "It is a large group of monstrous looking creatures. Upon closer "+
					    "examination, you realize these are krougs!\n";
					break;
				default:
					return "You find no kroug.\n";
					break;
			}
			break;
		case "water":
			switch(phase)
			{
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
					return "It is a large group of monstrous looking creatures. Upon closer "+
					    "examination, you realize these are krougs!\n";
					break;
				default:
					return "You find no kroug.\n";
					break;
			}
			break;
	}
}

public string
island_desc()
{
	switch(scenario)
	{
		case "air":
			switch(phase)
			{
				case 5:
					return "It is the island city of Menisca.\n";
					break;
				case 6:
					return "It is the island city of Conchoida.\n";
					break;
				case 7:
					return "It is the island city of Menisca.\n";
					break;
				default:
					return "You find no island.\n";
					break;
			}
			break;
		case "water":
			switch(phase)
			{
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
					return "It is the island city of Conchoida.\n";
					break;
				default:
					return "You find no island.\n";
					break;
			}
			break;
	}
}

public string
city_desc()
{
	switch(scenario)
	{
		case "air":
			switch(phase)
			{
				case 5:
					return "It is the island city of Menisca.\n";
					break;
				case 6:
					return "It is the island city of Conchoida.\n";
					break;
				case 7:
					return "It is the island city of Menisca.\n";
					break;
				default:
					return "You find no city.\n";
					break;
			}
			break;
		case "water":
			switch(phase)
			{
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
					return "It is the island city of Conchoida.\n";
					break;
				default:
					return "You find no city.\n";
					break;
			}
			break;
	}
}

public string
menisca_desc()
{
	switch(scenario)
	{
		case "air":
			switch(phase)
			{
				case 5:
					return "It is the island city of Menisca.\n";
					break;
				case 7:
					return "It is the island city of Menisca.\n";
					break;
				default:
					return "You find no menisca.\n";
					break;
			}
			break;
	}
}

public string
conchoida_desc()
{
	switch(scenario)
	{
		case "air":
			switch(phase)
			{
				case 6:
					return "It is the island city of Conchoida.\n";
					break;
				default:
					return "You find no conchoida.\n";
					break;
			}
			break;
		case "water":
			switch(phase)
			{
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
					return "It is the island city of Conchoida.\n";
					break;
				default:
					return "You find no conchoida.\n";
					break;
			}
			break;			
	}
}

public string
boat_desc()
{
	switch(scenario)
	{
		case "air":
			switch(phase)
			{
				case 5:
					return "These boats are the ones that were stolen from the "+
					    "town of Greensea.\n";
					break;
				case 7:
					return "These boats are the ones that were stolen from the "+
					    "town of Greensea.\n";
					break;
				default:
					return "You find no boat.\n";
					break;
			}
			break;
		case "water":
			switch(phase)
			{
			    case 3:
			    case 4:
				case 5:
				case 6:
				case 7:
					return "These boats are the ones that were stolen from the "+
					    "town of Greensea.\n";
					break;
				default:
					return "You find no dock.\n";
					break;
			}
			break;
	}
}

public string
boats_desc()
{
	switch(scenario)
	{
		case "air":
			switch(phase)
			{
				case 5:
					return "These boats are the ones that were stolen from the "+
					    "town of Greensea.\n";
					break;
				case 7:
					return "These boats are the ones that were stolen from the "+
					    "town of Greensea.\n";
					break;
				default:
					return "You find no boats.\n";
					break;
			}
			break;
		case "water":
			switch(phase)
			{
			    case 3:
			    case 4:
				case 5:
				case 6:
				case 7:
					return "These boats are the ones that were stolen from the "+
					    "town of Greensea.\n";
					break;
				default:
					return "You find no dock.\n";
					break;
			}
			break;
	}
}

public string
dock_desc()
{
	switch(scenario)
	{
		case "air":
			switch(phase)
			{
				case 5:
					return "These are the docks in the island city of Menisca. There "+
					    "are many boats here.\n";
					break;
				case 7:
					return "These are the docks in the island city of Menisca. There "+
					    "are many boats here.\n";
					break;
				default:
					return "You find no dock.\n";
					break;
			}
			break;
			
		case "water":
			switch(phase)
			{
			    case 3:
			    case 4:
				case 5:
				case 6:
				case 7:
					return "These are the docks in the island city of Conchoida. There "+
					    "are many boats here.\n";
					break;
				default:
					return "You find no dock.\n";
					break;
			}
			break;
	}
}

public string
docks_desc()
{
	switch(scenario)
	{
		case "air":
			switch(phase)
			{
				case 5:
					return "These are the docks in the island city of Menisca. There "+
					    "are many boats here.\n";
					break;
				case 7:
					return "These are the docks in the island city of Menisca. There "+
					    "are many boats here.\n";
					break;
				default:
					return "You find no docks.\n";
					break;
			}
			break;
		case "water":
			switch(phase)
			{
			    case 3:
			    case 4:
				case 5:
				case 6:
				case 7:
					return "These are the docks in the island city of Conchoida. There "+
					    "are many boats here.\n";
					break;
				default:
					return "You find no docks.\n";
					break;
			}
			break;
	}
}

public string
sea_desc()
{
	switch(scenario)
	{
		case "air":
			switch(phase)
			{
				case 5:
                case 6:
				case 7:
					return "It is the Thalassian sea which borders Calia.\n";
					break;
				default:
					return "You find no sea.\n";
					break;
			}
			break;
		case "water":
			switch(phase)
			{
			    case 3:
			    case 4:
				case 5:
                case 6:
				case 7:
					return "It is the Thalassian sea which borders Calia.\n";
					break;
				default:
					return "You find no sea.\n";
					break;
			}
			break;
	}
}

public string
water_desc()
{
	switch(scenario)
	{
		case "air":
			switch(phase)
			{
				case 5:
                case 6:
				case 7:
					return "They are the waters of the Thalassian sea which borders Calia.\n";
					break;
				default:
					return "You find no water.\n";
					break;
			}
			break;
		case "water":
			switch(phase)
			{
			    case 3:
			    case 4:
				case 5:
                case 6:
				case 7:
					return "They are the waters of the Thalassian sea which borders Calia.\n";
					break;
				default:
					return "You find no water.\n";
					break;
			}
			break;
	}
}

public string
waters_desc()
{
	switch(scenario)
	{
		case "air":
			switch(phase)
			{
				case 5:
                case 6:
				case 7:
					return "They are the waters of the Thalassian sea which borders Calia.\n";
					break;
				default:
					return "You find no waters.\n";
					break;
			}
			break;
		case "water":
			switch(phase)
			{
			    case 3:
			    case 4:
				case 5:
                case 6:
				case 7:
					return "They are the waters of the Thalassian sea which borders Calia.\n";
					break;
				default:
					return "You find no water.\n";
					break;
			}
			break;
	}
}

public string
body_desc()
{
	switch(scenario)
	{
		case "air":
			switch(phase)
			{
				case 7:
					return "There are many bodies strewn around, both Kyrullian and kroug.\n";
					break;
				default:
					return "You find no body.\n";
					break;
			}
			break;
		case "life":
			switch(phase)
			{
				case 5:
					return "They are the bodies of Jardeth and Tahla.\n";
					break;
				default:
					return "You find no body.\n";
					break;
			}
			break;
	}
}

public string
bodies_desc()
{
	switch(scenario)
	{
		case "air":
			switch(phase)
			{
				case 7:
					return "There are many bodies strewn around, both Kyrullian and kroug.\n";
					break;
				default:
					return "You find no bodies.\n";
					break;
			}
			break;
		case "life":
			switch(phase)
			{
				case 5:
					return "They are the bodies of Jardeth and Tahla.\n";
					break;
				default:
					return "You find no body.\n";
					break;
			}
			break;
	}
}

public string
sword_desc()
{
	switch(scenario)
	{
		case "air":
			switch(phase)
			{
				case 7:
					return "It is a large silver two-handed sword.\n";
					break;
				default:
					return "You find no sword.\n";
					break;
			}
			break;
	    case "water":
			switch(phase)
			{
				case 7:
					return "It is a large silver two-handed sword.\n";
					break;
				default:
					return "You find no sword.\n";
					break;
			}
			break;
	}
}

public string
steerax_desc()
{
	switch(scenario)
	{
		case "air":
			switch(phase)
			{
				case 7:
					return "Steerax is a very dominating kroug. He is much larger "+
					    "than the other krougs and wields a large two-handed sword "+
					    "with just one hand.\n";
					break;
				default:
					return "You find no steerax.\n";
					break;
			}
			break;
		case "water":
			switch(phase)
			{
				case 7:
					return "Steerax is a very dominating kroug. He is much larger "+
					    "than the other krougs and wields a large two-handed sword "+
					    "with just one hand. There are what appear to be burn marks "+
					    "on his chest armour.\n";
					break;
				default:
					return "You find no steerax.\n";
					break;
			}
			break;
	}
}

public string
kyrullian_desc()
{
	switch(scenario)
	{
	    case "air":
			switch(phase)
			{
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:    
					return "These people seem well off and all of them seem to have the "+
					    "same energy or aura as other Kyrullians you have seen.\n";
					break;
				default:
					return "You find no kyrullian.\n";
					break;
			}
		case "water":
			switch(phase)
			{
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:    
					return "These people seem well off and all of them seem to have the "+
					    "same energy or aura as other Kyrullians you have seen.\n";
					break;
				default:
					return "You find no kyrullian.\n";
					break;
			}
	}
}

public string
kyrullians_desc()
{
	switch(scenario)
	{
	    case "air":
			switch(phase)
			{
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:    
					return "These people seem well off and all of them seem to have the "+
					    "same energy or aura as other Kyrullians you have seen.\n";
					break;
				default:
					return "You find no kyrullian.\n";
					break;
			}
		case "water":
			switch(phase)
			{
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:    
					return "These people seem well off and all of them seem to have the "+
					    "same energy or aura as other Kyrullians you have seen.\n";
					break;
				default:
					return "You find no kyrullians.\n";
					break;
			}
	}
}

public string
man_desc()
{
	switch(scenario)
	{
		case "water":
			switch(phase)
			{
				case 1:
					return "This man appears to have sustained injuries in some type "+
					    "of battle.\n";
					break;
				default:
					return "You find no man.\n";
					break;
			}
			break;
	}
}

public string
cot_desc()
{
	switch(scenario)
	{
		case "water":
			switch(phase)
			{
				case 1:
					return "They are cots on the ground next to a building.\n";
					break;
				default:
					return "You find no cot.\n";
					break;
			}
			break;
	}
}

public string
cots_desc()
{
	switch(scenario)
	{
		case "water":
			switch(phase)
			{
				case 1:
					return "They are cots on the ground next to a building.\n";
					break;
				default:
					return "You find no cots.\n";
					break;
			}
			break;
	}
}

public string
blanket_desc()
{
	switch(scenario)
	{
		case "water":
			switch(phase)
			{
				case 1:
					return "They are blankets on the ground next to a building.\n";
					break;
				default:
					return "You find no blanket.\n";
					break;
			}
			break;
	}
}

public string
blankets_desc()
{
	switch(scenario)
	{
		case "water":
			switch(phase)
			{
				case 1:
					return "They are blankets on the ground next to a building.\n";
					break;
				default:
					return "You find no blankets.\n";
					break;
			}
			break;
	}
}

public string
temple_desc()
{
	switch(scenario)
	{
		case "water":
			switch(phase)
			{
				case 2:
					return "It is a temple in honor of Lord Diabrecho. There is a "+
					    "statue at the front of the temple.\n";
					break;
				default:
					return "You find no temple.\n";
					break;
			}
			break;
		case "life":
			switch(phase)
			{
			    case 3:
			    case 4:
			    case 5:
			    case 6:
			    case 7:
					return "This Temple was once the home of the Elementalists "+
					    "of Calia. It it now a crumbling ruins, destroyed by the "+
					    "hordes of Undead.\n";
					break;
				default:
					return "You find no temple.\n";
					break;
			}
			break;
	}
}

public string
statue_desc()
{
	switch(scenario)
	{
		case "water":
			switch(phase)
			{
				case 2:
					return "It is a large statue of Lord Diabrecho.\n";
					break;
				default:
					return "You find no statue.\n";
					break;
			}
			break;
	}
}

public string
basin_desc()
{
	switch(scenario)
	{
		case "water":
			switch(phase)
			{
				case 2:
					return "It is a basin of purified water in the temple of Lord "+
					    "Diabrecho.\n";
					break;
				default:
					return "You find no basin.\n";
					break;
			}
			break;
	}
}

public string
guard_desc()
{
	switch(scenario)
	{
		case "water":
			switch(phase)
			{
				case 5:
				case 6:
				case 7:
					return "They are the city guards of Conchoida.\n";
					break;
				default:
					return "You find no guard.\n";
					break;
			}
			break;
	}
}

public string
guards_desc()
{
	switch(scenario)
	{
		case "water":
			switch(phase)
			{
				case 5:
				case 6:
				case 7:
					return "They are the city guards of Conchoida.\n";
					break;
				default:
					return "You find no guards.\n";
					break;
			}
			break;
	}
}

public string
harbour_desc()
{
	switch(scenario)
	{
		case "water":
			switch(phase)
			{
			    case 3:
			    case 4:
				case 5:
				case 6:
				case 7:
					return "It is the harbour of Conchoida.\n";
					break;
				default:
					return "You find no harbour.\n";
					break;
			}
			break;
	}
}

public string
gate_desc()
{
	switch(scenario)
	{
		case "water":
			switch(phase)
			{
			    case 3:
			    case 4:
				case 5:
				case 6:
				case 7:
					return "They are the city gates of Conchoida.\n";
					break;
				default:
					return "You find no gate.\n";
					break;
			}
			break;
	}
}

public string
gates_desc()
{
	switch(scenario)
	{
		case "water":
			switch(phase)
			{
			    case 3:
			    case 4:
				case 5:
				case 6:
				case 7:
					return "They are the city gates of Conchoida.\n";
					break;
				default:
					return "You find no gates.\n";
					break;
			}
			break;
	}
}

public string
roundabout_desc()
{
	switch(scenario)
	{
		case "life":
			switch(phase)
			{
			    case 2:
					return "A wide circular road around a large pile of rocks, with branches "+
						"running off it to the north, south, east and west.\n";
					break;
				default:
					return "You find no roundabout.\n";
					break;
			}
			break;
	}
}

public string
rocks_desc()
{
	switch(scenario)
	{
		case "life":
			switch(phase)
			{
			    case 2:
					return "A large pile of rocks that used to be one massive boulder "+
					    "in the middle of the roundabout.\n";
					break;
				default:
					return "You find no rocks.\n";
					break;
			}
			break;
	}
}

public string
pile_desc()
{
	switch(scenario)
	{
		case "life":
			switch(phase)
			{
			    case 2:
					return "A large pile of rocks that used to be one massive boulder "+
					    "in the middle of the roundabout.\n";
					break;
				default:
					return "You find no pile.\n";
					break;
			}
			break;
	}
}

public string
sehis_desc()
{
	switch(scenario)
	{
		case "life":
			switch(phase)
			{
			    case 2:
			    case 3:
			    case 4:
			    case 5:
			    case 6:
			    case 7:
					return "She is a white-robed elf.\n"+
						   "She is short and lean for a elf.\n"+
						   "She looks like the image of perfection.\n"+
						   "She has a Kyrullian aurua surrounding her.\n"+
						   "She seems to be feeling very well.\n";
					break;
				default:
					return "You find no sehis.\n";
					break;
			}
			break;
	}
}

public string
garden_desc()
{
	switch(scenario)
	{
		case "life":
			switch(phase)
			{
			    case 3:
					return "This once lush and beautiful garden now lies in ruin. "+
					    "Plants are crushed or burned everywhere you look.\n";
					break;
				default:
					return "You find no garden.\n";
					break;
			}
			break;
	}
}

public string
plants_desc()
{
	switch(scenario)
	{
		case "life":
			switch(phase)
			{
			    case 3:
					return "This once lush and beautiful garden now lies in ruin. "+
					    "Plants are crushed or burned everywhere you look.\n";
					break;
				default:
					return "You find no plants.\n";
					break;
			}
			break;
	}
}

public string
rubble_desc()
{
	switch(scenario)
	{
		case "life":
			switch(phase)
			{
			    case 4:
					return "Large blocks of rock and stone creating rubble in front "+
					    "of the exits.\n";
					break;
				default:
					return "You find no rubble.\n";
					break;
			}
			break;
	}
}

public string
tapestry_desc()
{
	switch(scenario)
	{
		case "life":
			switch(phase)
			{
			    case 4:
					return "These once beautiful tapestries are now destroyed leaving not much "+
					    "more than a pile of ashes below where they used to hang.\n";
					break;
				default:
					return "You find no tapestry.\n";
					break;
			}
			break;
	}
}

public string
tapestries_desc()
{
	switch(scenario)
	{
		case "life":
			switch(phase)
			{
			    case 4:
					return "These once beautiful tapestries are now destroyed leaving not much "+
					    "more than a pile of ashes below where they used to hang.\n";
					break;
				default:
					return "You find no tapestries.\n";
					break;
			}
			break;
	}
}

public string
ashes_desc()
{
	switch(scenario)
	{
		case "life":
			switch(phase)
			{
			    case 4:
					return "The once beautiful tapestries are now destroyed leaving not much "+
					    "more than a pile of ashes below where they used to hang.\n";
					break;
				default:
					return "You find no ashes.\n";
					break;
			}
			break;
	}
}

public string
mosaic_desc()
{
	switch(scenario)
	{
		case "life":
			switch(phase)
			{
			    case 4:
					return "The once beautiful golden mosaic on the floor is now destroyed.\n";
					break;
				default:
					return "You find no mosaic.\n";
					break;
			}
			break;
	}
}

public string
wight_desc()
{
	switch(scenario)
	{
		case "life":
			switch(phase)
			{
			    case 4:
			    case 5:
			    case 6:
			    case 7:
					return "It is a a weird and twisted reflection of the life "+
					    "it once had formed through sheer violence and hatred.\n";
					break;
				default:
					return "You find no wight.\n";
					break;
			}
			break;
	}
}

public string
stairs_desc()
{
	switch(scenario)
	{
		case "life":
			switch(phase)
			{
			    case 5:
					return "A set of black stairs leading up and down inside "+
					    "the Temple.\n";
					break;
				default:
					return "You find no stairs.\n";
					break;
			}
			break;
	}
}

public string
stairwell_desc()
{
	switch(scenario)
	{
		case "life":
			switch(phase)
			{
			    case 5:
					return "A set of black stairs leading up and down inside "+
					    "the Temple.\n";
					break;
				default:
					return "You find no stairwell.\n";
					break;
			}
			break;
	}
}

public string
ghoul_desc()
{
	switch(scenario)
	{
		case "life":
			switch(phase)
			{
			    case 5:
			    case 6:
			    case 7:
					return "These hideous creatures have large claws and enjoy "+
					    "eating the flesh and bones of their victims.\n";
					break;
				default:
					return "You find no ghoul.\n";
					break;
			}
			break;
	}
}

public string
ghouls_desc()
{
	switch(scenario)
	{
		case "life":
			switch(phase)
			{
			    case 5:
			    case 6:
			    case 7:
					return "These hideous creatures have large claws and enjoy "+
					    "eating the flesh and bones of their victims.\n";
					break;
				default:
					return "You find no ghouls.\n";
					break;
			}
			break;
	}
}

public string
jardeth_desc()
{
	switch(scenario)
	{
		case "life":
			switch(phase)
			{
			    case 5:
			    	return "The body of Jardeth lies here being desecrated by a ghoul.\n";
					break;
			    case 7:
					return "It is the body of Jardeth re-animated by the Soulless.\n";
					break;
				default:
					return "You find no jardeth.\n";
					break;
			}
			break;
	}
}

public string
tahla_desc()
{
	switch(scenario)
	{
		case "life":
			switch(phase)
			{
			    case 5:
			    	return "The body of Tahla lies here being desecrated by a ghoul.\n";
					break;
			    case 7:
					return "It is the body of Tahla re-animated by the Soulless.\n";
					break;
				default:
					return "You find no tahla.\n";
					break;
			}
			break;
	}
}

public string
hall_desc()
{
	switch(scenario)
	{
		case "life":
			switch(phase)
			{
			    case 5:
			    	return "It is a hallway leading from the stairwell to the Conduit "+
			    	    "chamber.\n";
					break;
				default:
					return "You find no hall.\n";
					break;
			}
			break;
	}
}

public string
hallway_desc()
{
	switch(scenario)
	{
		case "life":
			switch(phase)
			{
			    case 5:
			    	return "It is a hallway leading from the stairwell to the Conduit "+
			    	    "chamber.\n";
					break;
				default:
					return "You find no hallway.\n";
					break;
			}
			break;
	}
}

public string
conduit_desc()
{
	switch(scenario)
	{
		case "life":
			switch(phase)
			{
			    case 6:
			    	return "This large cylindrical tube known only as the conduit "+
			    	    "appears to stretch from inside the floor and goes right up "+
			    	    "into the ceiling. It is made from some sort of clear material "+
			    	    "like glass yet it is flexible as you see it pulsing inwards "+
			    	    "and outwards, almost like a heartbeat. Inside of the tube you see "+
			    	    "energy flowing upwards very slowly.\n";
					break;
				case 7:
			    	return "This large cylindrical tube known only as the conduit "+
			    	    "appears to stretch from inside the floor and goes right up "+
			    	    "into the ceiling. It is made from some sort of clear material "+
			    	    "like glass yet it is flexible as you see it pulsing inwards "+
			    	    "and outwards, almost like a heartbeat. There are many cracks "+
			    	    "in it material. Inside of the tube you see energy flowing "+
			    	    "upwards very slowly.\n";
					break;
				default:
					return "You find no conduit.\n";
					break;
			}
			break;
	}
}

public void
set_occupied(int i)
{
	occupied = i;
}

public int
query_occupied()
{
	return occupied;
}

public void
set_phase(int i)
{
	phase = i;
}

public int
query_phase()
{
	return phase;
}

public void
set_scenario(string str)
{
	scenario = str;
}

public string
query_scenario()
{
	return scenario;
}

public void
start_scenario(string element, object player)
{
	scenario = element;
	occupied = 1;
	phase = 1;
	scenario_player = player;
	
	switch(scenario)
	{
		case "fire": // Corpse and Seria
			scenario_short_desc = "On a road in the moorlands";
			scenario_long_desc = "You are floating above a road in the moorlands. "+
				"On the road you see a corpse. Next to the "+
			    "corpse you see two Kyrullians; Lethos and Kaikos.\n";
			string *fire_one_messages = ({"\n\nYour vision fades away temporarily. "+
				"Once you regain it, you find yourself hovering above a road in the "+
				"moorlands of Calia. It is a rough dirt road meandering through the "+
				"moorlands.\n\n",
				"You notice two people standing on the road next to a human corpse. "+
				"These people don't look like anyone you have ever seen before. It is "+
				"almost as if there is some type of energy or aura radiating from "+
				"them.\n\n",
				"'Lethos, this looks like the work of the barbarians! You should see "+
				"if that is the case so that we might warn the others that they have "+
				"become brazen and are attacking on the open road!', says one of "+
				"them.\n\n",
				"The other leans down towards the corpse and gestures mysteriously while "+
				"praying. 'Yes Kaikos, this was the work of the barbarians, we must warn "+
				"the Elders!'\n\n",
				"\n\nYour vision fades away again. After a moment you begin to see a "+
				"light. You could probably <focus> on it.\n\n"});
				
			for (int i=0; i < sizeof(fire_one_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(player, fire_one_messages[i]));    			
			break;
			
		case "earth": // Beach and Diakopi
		    scenario_short_desc = "On a beach";
			scenario_long_desc = "You are floating above a beach. On the beach you "+
				"see a lone Kyrullian; Cilla.\n";
		    string *earth_one_messages = ({"\n\nYour vision fades away temporarily. Once "+
		    	"you regain it, you find yourself hovering above a beach.\n\n",
			    "You notice one person standing on the beach. This person "+
			    "has the same type of energy or aura radiating from them as you saw on "+
			    "Lethos and Kaikos. 'Her name is Cilla', you hear the voice of Nysa say "+
			    "in your mind.\n\n",
			    "You see Cilla place a handful of brightly colored gems down "+
			    "onto the ground in front of her and stretch her hand out towards them.\n\n",
			    "A brilliant burst of light temporarily blinds you and you hear a loud "+
			    "shattering sound. As the light fades you see the gems have been broken "+
			    "into many shards.\n\n",
			    "She reaches down and picks up the shards, putting them into a small pouch.\n\n",
			    "\n\nYour vision fades away again. After a moment you "+
			    "begin to see a light. You could probably <focus> on it.\n\n"});
			for (int i=0; i < sizeof(earth_one_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(player, earth_one_messages[i])); 
			break;
			
		case "air": // Greensea and Trefo
		    scenario_short_desc = "In a small beach town";
			scenario_long_desc = "You are floating above a small beach town. There are many "+
			    "people here in the town.\n";
		    string *air_one_messages = ({"\n\nYour vision fades away temporarily. Once "+
		    	"you regain it, you find yourself hovering above a small beach town. "+
		    	"There are many people here in the town.\n\n",
			    "One of them stands out from the others. She is dressed quite "+
			    "differently and appears to have an aura surrounding her.\n\n",
			    "'This is the town of Greensea.', you hear the voice of Nysa say in your "+
			    "mind, 'And that is Leda. She is one of the Kyrullian Air Clerics.\n\n",
			    "Leda closes her eyes and concentrates for a moment. As she opens her eyes, "+
			    "a large wicker basket appears in her hand.\n\n",
			    "Leda reaches into the basket and pulls out various fruits and a flagon of "+
			    "water. As she pulls the last item out of the basket, it disappears.\n\n",
			    "She hands out the fruits to the people around her and offers up some "+
			    "water to those who want some.\n\n",
			    "\n\nYour vision fades away again. After a moment you "+
			    "begin to see a light. You could probably <focus> on it.\n\n"});
			for (int i=0; i < sizeof(air_one_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(player, air_one_messages[i]));
			break;
			
		case "water": // Conchoida, Aleipso and Pano
			scenario_short_desc = "In a large island city";
			scenario_long_desc = "You are floating above a large island city. There are many "+
			    "people here in the city.\n";
			string *water_one_messages = ({"\n\nYour vision fades away temporarily. Once "+
		    	"you regain it, you find yourself hovering above a large island city. "+
		    	"There are many people here wandering around here.\n\n",
		    	"'This is the island city of Conchoida. It too was once perched atop "+
		    	"a mountain on the mainland of Calia before the Elementals saved it "+
		    	"and it's sister city, Menisca.', you hear the voice of Nysa say in "+
		    	"your mind.\n\n",
		    	"Standing next to a building you see a very tall robed person next to "+
		    	"many other people who are all lying down on blankets and cots. 'That is "+
		    	"Pelias.', you hear Nysa say in your mind, 'He is a very powerful Kyrullian "+
		    	"Water Cleric.\n\n",
		    	"Pelias bends down over one of the people on a cot and closes his eyes "+
		    	"in concentration. He opens his eyes and places his hand over the person's "+
		    	"chest. Thin streams of water move between Pelias' hand and the person's "+
		    	"chest.\n\n",
		    	"The person opens his eyes and after a moment, stands up and he thanks Pelias "+
		    	"for healing him. Pelias asks him to wait for another moment and holds out his "+
		    	"hands in prayer. A dazzling array of lights appears around Pelias' hands for "+
		    	"a moment then move out to surround the man, expanding around him completely. "+
		    	"The lights flash for a second then blink out of existance.\n\n",
		    	"'That will help you resist the magic from those beasts.', says Pelias to "+
		    	"the man.\n\n",
			    "\n\nYour vision fades away again. After a moment you "+
			    "begin to see a light. You could probably <focus> on it.\n\n"});
			for (int i=0; i < sizeof(water_one_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(player, water_one_messages[i]));
			break;
			
		case "life":
			scenario_short_desc = "A void";  // Overview
			scenario_long_desc = "You are floating in some place you don't recognize. "+
                "It is neither light, nor dark. It isn't warm, nor "+
                "cold. You sense nothing, feel nothing. You seem to "+
                "be nowhere.\n";
            string *life_one_messages=({"\n\nYour vision fades away temporarily. Once "+
		    	"you regain it, you find yourself in the void. It is neither light, nor "+
                "dark. It isn't warm, nor cold. You sense nothing, feel nothing. You "+
                "seem to be nowhere.\n\n",
				"You hear the voice of Nysa say 'You experienced a brief "+
			    "time in the life of a Kyrullian named Lethos. He used the aggressive gifts "+
			    "of flame to save his friends and destruct his enemies. Although he may "+
			    "have died, his sacrifice was not in vain. The Elementals had time to "+
			    "save his kind by moving the mountain tops into the sea.'\n\n",
				"'You witnessed the barbarians press the attack against "+
			    "the Kyrullian named Cilla and her companions. Her protective gifts of "+
			    "earth perservered and even though she fell, our Ways were kept secret.'\n\n",
				"'You witnessed Steerax and the krougs rise up and attack "+
			    "the island of Menisca through the eyes of the Kyrullian named Leda. Her "+
			    "supportive gifts of air helped rescue many before she succumbed to the "+
			    "evil forces.'\n\n",
				"'You then experienced the battle in Conchoida leading up to the Elementals "+
				"intervening once again; Mt. Pyros erupting and the sinking of "+
				"the islands. Through the experiences of Pelias, you saw the healing "+
				"gifts of water and his sacrifice in order to maintain the bonds of "+
				"Family for everyone else.'\n\n",
				"'Now I take you to a time, just before the end of all time as "+
			    "you know it. It is one possible future if we do not continue the fight "+
			    "against the Soulless, to once and for all stop Theos, the Voidbringer, on "+
			    "his dreaded crusade to make everyone into Undead. Experience now why we "+
			    "oppose the Soulless and why we of Spirit are gifted to do so.'\n\n",
				"\n\nYour vision fades away again. After a moment you "+
				"begin to see a light. You could probably <focus> on it.\n\n"});
			for (int i=0; i < sizeof(life_one_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(player, life_one_messages[i]));    
			break;
	}

}

public void
scenario_phase_two(object player)
{
	phase = 2;
	switch(scenario)
	{
		case "fire": // Mountain road and Tromazo
			scenario_short_desc = "On a road at the base of a mountain";
			scenario_long_desc = "You are floating above a road at the base of "+
			    "a mountain. Walking down the road you see Lethos and Kaikos.\n";
			string *fire_two_messages=({"\n\nYou refocus your vision and "+
			    "you find yourself hovering above a road at the base of a mountain. "+
			    "The road emerges from some trees and gently slopes upwards from here, "+
			    "spiralling around the mountain as it does so. Walking down the road "+
			    "you see Lethos and Kaikos.\n\n",
				"You hear a noise and notice some rustling in the trees. "+
			    "Both Lethos and Kaikos notice the noise as well. Lethos stops, closes "+
			    "his eyes and concentrates. You notice a small flame appear on the road "+
			    "in front of him then it quickly disappears.\n\n",
				"'Good idea, that alarm will warn you if they decide to "+
			    "follow us up the mountain.', says Kaikos. Both Lethos and Kaikos start "+
			    "running up the mountain road.\n\n",
				"\n\nYour vision fades away again. After a moment you "+
				"begin to see a light. You could probably <focus> on it.\n\n"});
			for (int i=0; i < sizeof(fire_two_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(player, fire_two_messages[i])); 
			break;
			
		case "earth": // Forest and Kourasi
			scenario_short_desc = "In a forest";
			scenario_long_desc = "You are floating above the ground in a forest. "+
			    "Below you, you see Cilla.\n";
			string *earth_two_messages=({"\n\nYou refocus your vision and "+
			    "you find yourself hovering above the ground in a forest, surrounded "+
			    "by trees that reach high up into the air above you. You see Cilla "+
			    "walking through the forest below you, carrying two very large buckets "+
				"of water.\n\n",
				"She stops and puts the buckets down, obviously very fatigued from "+
				"carrying them. She gestures towards herself with her hands briefly.\n\n",
				"Energy flows from her hands into her own body, surrounding her for "+
				"a split second before disappearing.\n\n",
				"She looks much more refreshed than she did just a moment ago, "+
				"reaches down and grabs the buckets again and continues on her "+
				"journey.\n\n",
				"\n\nYour vision fades away again. After a moment you "+
				"begin to see a light. You could probably <focus> on it.\n\n"});
			for (int i=0; i < sizeof(earth_two_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(player, earth_two_messages[i]));
			break;
			
		case "air": // Greensea and Apofevgo
		    scenario_short_desc = "In a small beach town";
			scenario_long_desc = "You are floating above a small beach town. There are many "+
			    "people here in the town.\n";
			string *air_two_messages=({"\n\nYou refocus your vision and "+
			    "you find yourself hovering above the beach town of Greensea again. "+
			    "Below you, you see Leda with a look of horror on her face.\n\n",
				"Glancing in the direction you see she is facing, you see a massive "+
				"group of creatures heading towards her.\n\n",
				"As the group gets closer to her, you recognize these creatures; they're "+
				"krougs!\n\n",
				"Leda concentrates for a moment and you see a thin layer of air moving "+
				"around her body.\n\n",
				"A kroug decends upon Leda and tries to strike her with his hammer but it "+
				"is deflected by the layer of air.\n\n"});
			for (int i=0; i < sizeof(air_two_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(player, air_two_messages[i]));
		    set_alarm(50.0,0.0,&scenario_phase_three(player));
			break;
			
		case "water": // Conchoida and Kinisi
		    scenario_short_desc = "In a large temple";
			scenario_long_desc = "You are hovering inside of a large temple located "+
			    "in Conchoida.\n";
			string *water_two_messages = ({"\n\nYour vision fades away temporarily. Once "+
		    	"you regain it, you find yourself hovering inside a large temple located in "+
		    	"Conchoida. Below you, you see Pelias kneeling before a statue of Lord "+
		    	"Diabrecho in prayer.\n\n",
		    	"He finishes praying and stands up. He walks over to a basin containing "+
		    	"some purified water and fills up some vials he had in his pack with the "+
		    	"water.\n\n",
		    	"Pelias whispers a prayer to Lord Diabrecho. When he has finished his prayer, "+
		    	"a ball of water in the shape of a globe appears in his hands. He plunges the "+
		    	"his hand with the vials in it into the water globe and pulls his hand out. "+
		    	"The vials are gone and his hand is dry. He grabs a few loaves of bread from "+
		    	"his pack and puts them inside of the water globe as well and then closes his eyes, "+
		    	"whispering another prayer to Lord Diabrecho. The water globe disappears into "+
		    	"thin air!\n\n",
		    	"'Hopefully that will help feed the wounded for a bit.', you hear him say.\n\n",
			    "\n\nYour vision fades away again. After a moment you "+
			    "begin to see a light. You could probably <focus> on it.\n\n"});
			for (int i=0; i < sizeof(water_two_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(player, water_two_messages[i]));
			break;
			
		case "life": // Roundabout and Thesi
		    scenario_short_desc = "A larger roundabout";
			scenario_long_desc = "You find yourself at a large roundabout, at the centre " +
      			"of which is a large pile of rocks.\n";
			string *life_two_messages = ({"\n\nYour vision fades away temporarily. Once "+
		    	"you regain it, you find yourself hovering above a large roundabout, at "+
		    	"the centre of which is a large pile of rocks. Standing next to the pile "+
		    	"of rocks, you see Sehis.\n\n",
		    	"She doesn't seem like the same Sehis you know from the Elemental Temple, "+
		    	"instead she seems very disheveled and almost panicky.\n\n",
		    	"You quickly realize that the pile of rocks is actually the remains of the "+
		    	"large boulder that used to sit there. This is the roundabout in Calia!\n\n",
		    	"The voice of Nysa echoes in your mind, 'These are dark times. Calia and "+
		    	"much of the world has been overrun by undead.'\n\n",
		    	"You see Sehis close her eyes in concentration. After a moment a look of "+
		    	"shock falls over her face. She closes her eyes again in concentration. "+
		    	"The shocked look grows, her face begins to turn white, her hands trembling "+
		    	"with fear.\n\n",
		    	"'Sehis is attempting to scry the location of the other Temple Elders, but "+
		    	"she won't find them. They are already dead.'\n\n",
		    	"You see Sehis try again and again, each time unsuccessful, each time she "+
		    	"gets more and more afraid.\n\n",
			    "\n\nYour vision fades away again. After a moment you "+
			    "begin to see a light. You could probably <focus> on it.\n\n"});
			for (int i=0; i < sizeof(life_two_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(player, life_two_messages[i]));
			break;
			break;
	}

}

public void
scenario_phase_three(object player)
{
	phase = 3;
	switch(scenario)
	{
		case "fire": // Stronghold and Enkav
			scenario_short_desc = "Outside of a stronghold";
			scenario_long_desc = "You are floating above a stronghold.\n";
			string *fire_three_messages=({"\n\nYou refocus your vision and "+
			    "you find yourself hovering above the entrance to a stronghold that is "+
			    "situated on the top of the mountain. There are many people here, including "+
			    "Lethos and Kaikos.\n\n",
				"Lethos gets a concerned look on his face. 'You run ahead "+
			    "and warn the Elders Kaikos. The barbarians just triggered my alarm and are "+
			    "on their way up.' he says to Kaikos, who immediately enters the stronghold "+
			    "and disappears from sight.\n\n",
				"Suddenly a large group of barbarians comes running up the "+
			    "road, yelling and screaming. The group of people all brandish their weapons "+
			    "and begin to attack them. Lethos closes his eyes and concentrates briefly. "+
			    "Fire forms around his hands as he points towards one of the barbarians. "+
				"Tendrils of fire leap from his hands, burning the barbarian badly.\n\n"});
			for (int i=0; i < sizeof(fire_three_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(player, fire_three_messages[i]));
			set_alarm(30.0,0.0,&scenario_phase_four(player));
			break;
			
		case "earth": // Encampment and Oxy
			scenario_short_desc = "Hovering above an encampent";
			scenario_long_desc = "You are hovering above an encampment in the forest. "+
			    "You see many people here, including Cilla.\n";
			string *earth_three_messages=({"\n\nYou refocus your vision and "+
			    "you find yourself hovering above an encampment in the forest. You see "+
			    "many people here, including Cilla.\n\n",
				"You hear someone shouting 'They're coming! They're coming!' from somewhere "+
				"up in the trees. Glacing around you see a large group of barbarians "+
				"approaching the encampment.\n\n",
				"Cilla closes her eyes briefly in concentration. She holds out her arm, "+
				"pointing towards one of the barbarians. Shards of earth spray "+
				"forth from her fingertips towards the barbarian.\n\n",
				"As the shards imbed themselves in the barbarian, he drops to the ground writhing "+
				"in pain.\n\n"});
			for (int i=0; i < sizeof(earth_three_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(player, earth_three_messages[i]));
			set_alarm(40.0,0.0,&scenario_phase_four(player));
			break;
			
		case "air": // Greensea and Afoplizo
			scenario_short_desc = "In a small beach town";
			scenario_long_desc = "You are floating above a small beach town. There are many "+
			    "people here in the town.\n";
			string *air_three_messages=({"Angered by what happened the kroug tries again, "+
				"swinging at Leda with all his might. The blow is again deflected away.\n\n",
				"Leda whispers an ancient prayer while looking at the kroug attacking her.\n\n",
				"The kroug winces and drops his weapon, grabbing his hand with the "+
				"other trying to stop the pain in his hand.\n\n"});
			for (int i=0; i < sizeof(air_three_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(player, air_three_messages[i]));
		    set_alarm(30.0,0.0,&scenario_phase_four(player));
			break;
			
		case "water": // Conchoida Docks and Antistasi
		    scenario_short_desc = "At the Conchoida docks";
			scenario_long_desc = "You are floating above the Conchoida docks.\n";
			string *water_three_messages = ({"\n\nYour vision fades away temporarily. Once "+
		    	"you regain it, you find yourself hovering above the Conchoida docks.\n\n",
		    	"There are many boats already docked in the harbour and many more filled "+
		    	"with krougs sailing in from the sea.\n\n",
		    	"You see Pelias below you concentrating while staring at one of the krougs "+
		    	"on the docks. After a moment you hear him say, 'They're immune to all magic "+
		    	"except water! Get everyone inside the gates that doesn't have water magic!'\n\n",
		    	"You see many people turn and run towards a massive set of gates.\n\n"});
			for (int i=0; i < sizeof(water_three_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(player, water_three_messages[i]));
			set_alarm(40.0,0.0,&scenario_phase_four(player));
			break;
			
		case "life": // Elemental Temple Garden and Aorato
		    scenario_short_desc = "Inside a walled garden";
			scenario_long_desc = "You are floating above part of the walled garden surrounding "+
			    "the crystalline Elemental Temple of Calia. Below you is a path "+
				"winding through what is left of the temple garden.\n";
			string *life_three_messages = ({"\n\nYour vision fades away temporarily. Once "+
		    	"you regain it, you find yourself hovering above part of the walled garden "+
		    	"surrounding the crystalline Elemental Temple of Calia. Below you is a path "+
		    	"winding through what is left of the temple garden. The plants have all been "+
		    	"crushed or burned.\n\n",
		    	"You see Sehis crouching beside some of the plants, her face showing she is "+
		    	"pained by all the destruction.\n\n",
		    	"Sehis stands up and quietly whispers a prayer to Psuchae. Suddenly Sehis "+
		    	"disappears from sight!\n\n",
		    	"You hear the voice of Nysa say in your mind, 'Invisibility. It will do her "+
		    	"little good I'm afraid after what has happened here, but it will allow her "+
		    	"to witness the damage for herself.'\n\n",
			    "\n\nYour vision fades away again. After a moment you "+
			    "begin to see a light. You could probably <focus> on it.\n\n"});
			for (int i=0; i < sizeof(life_three_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(player, life_three_messages[i]));
			break;
			break;
	}

}

public void
scenario_phase_four(object player)
{
	phase = 4;
	switch(scenario)
	{
		case "fire": // Stronghold and Viloda
			scenario_short_desc = "Outside of a stronghold";
			scenario_long_desc = "You are floating above a stronghold.\n";
			string *fire_four_messages=({"A large barbarian runs towards Lethos. Seeing "+
				"this, he concentrates intensely and pulls his hands towards his chest, "+
				"one on top of the other, his hands forming a ball shape. A large ball "+
				"of fire forms between his hands and he pushes it outwards. The fireball "+
				"streaks towards the large barbarian, striking him in the chest and "+
				"exploding.\n\n",
				"When the light from the explosion clears, you see the large "+
				"barbarian lying on the ground with a smouldering crater-like wound in "+
				"its chest.\n\n"});
			for (int i=0; i < sizeof(fire_four_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(player, fire_four_messages[i]));
			set_alarm(20.0,0.0,&scenario_phase_five(player));
			break;
			
		case "earth": // Encampment and Aspida
			scenario_short_desc = "Hovering above an encampent";
			scenario_long_desc = "You are hovering above an encampment in the forest. "+
			    "You see many people here, including Cilla.\n";
			string *earth_four_messages=({"Seeing one of his companions drop to the "+
				"ground in pain, one of the barbarians charges at Cilla.\n\n",
				"Seeing the approaching barbarian, Cilla closes her eyes and begins "+
				"to concentrate. As she opens them, her body transforms into what "+
				"appears to be a golem, her skin made of rock, her hands as big as "+
				"boulders!\n\n",
				"Cilla closes her eyes briefly again in concentration. As she opens them, "+
				"her rocky skin flashes for a split second.\n\n",
				"The barbarian closes on her and smashes his club into her body. The club "+
				"bounces back at the barbarian, hitting him squarely in the face.\n\n"});
			for (int i=0; i < sizeof(earth_four_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(player, earth_four_messages[i]));
			set_alarm(40.0,0.0,&scenario_phase_five(player));
			break;
			
		case "air": // Greensea and Paradido
			scenario_short_desc = "In a small beach town";
			scenario_long_desc = "You are floating above a small beach town. There are many "+
			    "people here in the town.\n";
			string *air_four_messages=({"Leda glances towards the edge of town. More and more "+
				"krougs are coming.\n\n",
				"She sees a large group of krougs at the docks. They climb into a ship and cast "+
				"off, heading out towards the islands.\n\n",
				"A look of remorse washes over Leda's face. 'All hope is lost for the town "+
				"of Greensea.', you hear Nysa's voice say in your mind, 'She knows there is "+
				"nothing else she can do here and she must warn the others.'\n\n",
				"She closes her eyes in concentration. You see a single tear fall from the "+
				"corner of her eye, running down her cheek. Suddenly she disappears.\n\n",
				"\n\nYour vision fades away again. After a moment you "+
				"begin to see a light. You could probably <focus> on it.\n\n"});
			for (int i=0; i < sizeof(air_four_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(player, air_four_messages[i]));
			break;
			
		case "water": // Conchoida Docks and Kryo
		    scenario_short_desc = "At the Conchoida docks";
			scenario_long_desc = "You are floating above the Conchoida docks.\n";
			string *water_four_messages = ({"Pelias closes his eyes in concentration and "+
			    "points towards the kroug on the dock. His fingers begin to turn white and "+
			    "frost forms on his finger tips. A blast of air flies out from his hand as "+
			    "he opens his eyes, hitting the kroug in the face. The krougs face turns "+
			    "white and frost forms on his nose.\n\n",
		    	"The kroug stops his attack, obviously shaken from the attack and he seems "+
		    	"to be shivering.\n\n",
			    "\n\nYour vision fades away again. After a moment you "+
			    "begin to see a light. You could probably <focus> on it.\n\n"});
			for (int i=0; i < sizeof(water_four_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(player, water_four_messages[i]));
			break;
			
		case "life": // Elemental Temple Greathall and Kato/Ousia
		    scenario_short_desc = "In a greathall";
			scenario_long_desc = "You are floating above the greathall of the Elemental "+
			    "Temple.\n";
			string *life_four_messages = ({"\n\nYour vision fades away temporarily. Once "+
		    	"you regain it, you find yourself hovering above the greathall of the "+
		    	"Elemental Temple. All passageways out of here are now destroyed or have "+
		    	"rubble lying in front of them save the north and the south ones. The "+
		    	"tapestries that used to hang here are both gone, ashes lie on the ground "+
		    	"below where they used to be. Much of the mosaic on the floor has been "+
		    	"scorched, burned or destroyed.\n\n",
		    	"You once again hear the voice of Nysa in your mind, 'Sehis is here now, "+
		    	"examining the damage to this once great place that she spent so much "+
		    	"time in.'\n\n",
		    	"You hear sobbing from a darkened corner of the room.\n\n",
		    	"Slowly you see Sehis fade into view as the gift of invisibility wears off "+
		    	"of her. Tears are rolling down her cheeks.\n\n"+
		    	"You see something moving into the greathall. Sehis notices too and stands "+
		    	"up immediately. It's a wight!\n\n",
		    	"Sehis points her hand towards the wight and concentrates on it. A flash of "+
		    	"light erupts from her hand, surrounding the wight for a brief moment.\n\n",
		    	"'That will make you much weaker.', she says as she raises her hand towards "+
		    	"it again and begins to concentrate.\n\n",
		    	"A bolt of dark energy flies from Sehis' fingertips at the wight, striking "+
		    	"it. The bolt is absorbed into the creature and you hear it wail in pain.\n\n"+
		    	"Sehis runs for the north exit quickly, disappearing from sight into the next "+
		    	"room, the wight following behind her.\n\n",
			    "\n\nYour vision fades away again. After a moment you "+
			    "begin to see a light. You could probably <focus> on it.\n\n"});
			for (int i=0; i < sizeof(life_four_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(player, life_four_messages[i]));
			break;
			break;
	}

}			

public void
scenario_phase_five(object player)
{
	phase = 5;
	switch(scenario)
	{
		case "fire": // Stronghold and Anavo
			scenario_short_desc = "Outside of a stronghold";
			scenario_long_desc = "You are floating above a stronghold.\n";
			string *fire_five_messages=({"In the group of barbarians you see one "+
				"of them that seems to have no weapons and is instead using magic. "+
				"Lethos also notices this barbarian, points towards him and yells "+
				"out, 'Shaman!'\n\n",
				"Lethos closes his eyes and concentrates. The shaman "+
			    "suddenly grasps his head and screams out in pain loudly. 'Hopefully "+
			    "that will weaken his mental strength.', says Lethos to one of the "+
			    "other people fighting the barbarians.\n\n",
				"\n\nYour vision fades away again. After a moment you "+
				"begin to see a light. You could probably <focus> on it.\n\n"});
			for (int i=0; i < sizeof(fire_five_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(player, fire_five_messages[i]));
			break;
			
		case "earth": // Encampment and Diasosi
			scenario_short_desc = "Hovering above an encampent";
			scenario_long_desc = "You are hovering above an encampment in the forest. "+
			    "You see many people here, including Cilla.\n";
			string *earth_five_messages=({"Cilla sees another of the barbarians "+
				"attacking one of her friends. She quickly begins to pray to Lady Gu.\n\n",
				"She runs towards her friend and just as the barbarian's club is about "+
				"to make contact with her friend, Cilla blinks into existance in front "+
				"of her, taking the hit from the club.\n\n",
				"Cilla staggers back briefly in pain from the attack.\n\n"});
			for (int i=0; i < sizeof(earth_five_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(player, earth_five_messages[i]));
			set_alarm(30.0,0.0,&scenario_phase_six(player));
			break;
			
		case "air": // Menisca and Ripi
			scenario_short_desc = "In a large island city";
			scenario_long_desc = "You are floating above a large island city. There are many "+
			    "people here in the city.\n";
			string *air_five_messages=({"\n\nYou refocus your vision and "+
			    "you find yourself hovering above a large island city. You see many "+
			    "people here.\n\n",
			    "The voice of Nysa echoes in your mind once again, 'This is the island "+
			    "city of Menisca. It has been many years since this land mass was moved "+
			    "from the top of the mountain on the mainland by the Elementals.'\n\n",
				"You see Leda appear out of nowhere next to one of the people below you. "+
				"'They're coming! Krougs are coming by boat. We must warn everyone!', "+
				"she yells. Looks of horror and panic invade the faces of everyone around "+
				"her.\n\n",
				"Several people run away notifying others of the impending invasion coming "+
				"their way.\n\n",
				"You hear a bell tolling loudly from towards the docks. You see several "+
				"ships approaching from the sea.\n\n",
				"Leda runs towards the docks with several others. Just as they arrive, a "+
				"group of krougs jumps off of one of the ships and onto the docks.\n\n",
				"Leda whispers a prayer to Lady Aeria quietly and points her hand out "+
				"towards one of the krougs near the edge of the dock. A gust of wind "+
				"flies out from her hand and strikes the kroug, causing him to stagger "+
				"backwards and fall into the water.\n\n",
				"\n\nYour vision fades away again. After a moment you "+
				"begin to see a light. You could probably <focus> on it.\n\n"});
			for (int i=0; i < sizeof(air_five_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(player, air_five_messages[i]));
			break;
			
		case "water": // Conchoida Gates and Treximo
		    scenario_short_desc = "At the gates of Conchoida";
			scenario_long_desc = "You are floating above the massive gates of Conchoida.\n";
			string *water_five_messages = ({"\n\nYour vision fades away temporarily. Once "+
		    	"you regain it, you find yourself hovering above the massive gates "+
		    	"surrounding the island city of Conchoida.\n\n",
		    	"Many people are fleeing from the docks and through the safety of the "+
		    	"gates.\n\n",
		    	"Pelias is standing below you next to some of the city guards. Many "+
		    	"krougs are rushing towards the gates, trying to attack those that "+
		    	"are fleeing. Pelias and the guards rush out to meet them head on.\n\n",
		    	"Pelias pauses and begins to concentrate. Just as he is about to use "+
		    	"one of his gifts, a kroug hits him with its hammer in the leg, breaking "+
		    	"his concentration.\n\n",
		    	"Pelias ducks behind one of the guards and asks him to shield him for a "+
		    	"moment. The guard nods and Pelias once again concentrates for a moment. "+
		    	"Pelias suddenly disappears and then reappears behind a different guard!\n\n"});
			for (int i=0; i < sizeof(water_five_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(player, water_five_messages[i]));
			set_alarm(50.0,0.0,&scenario_phase_six(player));
			break;
			
		case "life": // Elemental Temple Stairwell and Diochetevo
		    scenario_short_desc = "Basement Central Stairwell";
			scenario_long_desc = "You are floating above the basement stairwell in the "+
			    "Elemental Temple.\n";
			string *life_five_messages = ({"\n\nYour vision fades away temporarily. Once "+
		    	"you regain it, you find yourself hovering above the basement stairwell in "+
		    	"the Elemental Temple.\n\n",
		    	"Sehis has just reached the bottom of the stairs and has come across two "+
		    	"bodies being desecrated by two ghouls.\n\n",
		    	"'The Soulless are so strong that they have found a way to have our "+
		    	"corpses stay in this material plane when we pass. They are in the process "+
		    	"of trying to re-animate those two corpses.', says the voice of Nysa disgustedly "+
		    	"in your mind.\n\n"+
		    	"Looking at the bodies, you recognize them! It is the bodies of Jardeth and Tahla!\n\n",
		    	"You see the wight making its way down the stairwell behind Sehis.\n\n",
		    	"Sehis runs to the hallway leading south, turns around and begins whispering "+
		    	"a prayer to Psuchae. She pushes her hands towards one of the ghouls and a large "+
		    	"wave of shadowy energy flies out of them and into the ghoul, stopping it from "+
		    	"ravaging the corpse and hurting it greatly.\n\n",
		    	"It slumps down onto the floor and the other ghoul takes notice, charging towards "+
		    	"Sehis. She whispers another prayer to Psuchae and pushes her hands towards that "+
		    	"ghoul. Another large wave of shadowy energy flies out of her hands and into the "+
		    	"ghoul, hurting it and causing it to slump to the floor as well.\n\n",
		    	"Sehis turns to the now closing wight and whispers a prayer to Psuchae. She pushes "+
		    	"her hands towards the wight and another large wall of shadowy energy flies out of "+
		    	"them and into the wight. The wight staggers backwards, allowing Sehis to escape "+
		    	"to the south.\n\n",
			    "\n\nYour vision fades away again. After a moment you "+
			    "begin to see a light. You could probably <focus> on it.\n\n"});
			for (int i=0; i < sizeof(life_five_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(player, life_five_messages[i]));
			break;
			break;
	}

}

public void
scenario_phase_six(object player)
{
	phase = 6;
	switch(scenario)
	{
		case "fire": // Alleyway and Teichos
			scenario_short_desc = "Alleyway beside a stronghold";
			scenario_long_desc = "You are floating above a stronghold.\n";
			string *fire_six_messages=({"\n\nYou refocus your vision and "+
			    "you find yourself hovering above an alleyway beside the stronghold. "+
			    "There are only a three people here, including Lethos. They seem to have "+
			    "been forced into this area and are fighting for their very lives!\n\n",
				"A big group of barbarians is approaching them and you "+
			    "can tell they don't have much energy to continue the fight. The "+
			    "others begin to panic. Lethos notices, realizes that they won't "+
			    "last much longer, stops what he is doing, stands very still and closes "+
			    "his eyes, deep in concentration.\n\n",
				"There is an explosion of energy around Lethos as his "+
			    "entire body is engulfed by flames. He reaches down, touching the ground. "+
			    "Flames leap from his body and jump down onto the alleyway, quickly forming "+
			    "a wall of flames spreading across the entire alleyway and towering high "+
			    "above him. He grabs the other two by the arms, somehow not burning them, "+
			    "and steps through the wall of flames with them, all of them reaching the "+
			    "other side unharmed.\n\n",
				"The barbarians attempt to cross the wall of flames but are "+
			    "burned and quickly turn away in pain. Many of them attempt to cross the wall "+
				"but all are blocked from doing so by the fire.\n\n"});
			for (int i=0; i < sizeof(fire_six_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(player, fire_six_messages[i]));
			set_alarm(40.0,0.0,&scenario_phase_seven(player));
			break;
			
		case "earth": // Encampment and Livra
			scenario_short_desc = "Hovering above an encampent";
			scenario_long_desc = "You are hovering above an encampment in the forest. "+
			    "You see many people here, including Cilla.\n";
			string *earth_six_messages=({"Cilla regains her focus and prepares to "+
				"strike out at the barbarian.\n\n",
				"She pounds her rocklike fist into the chest of the barbarian soundly. "+
				"The barbarian cries out in great pain as her fist drives his "+
				"breastplate into his chest. As Cilla pulls her fist back, the breastplate "+
				"falls to the ground, broken.\n\n",
				"She yells at the others to retreat and they begin to do so, disappearing "+
				"into the forest.\n\n"});
			for (int i=0; i < sizeof(earth_six_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(player, earth_six_messages[i]));
			set_alarm(40.0,0.0,&scenario_phase_seven(player));
			break;
			
		case "air": // Menisca (briefly), Conchoida and Metafora
			scenario_short_desc = "In a large island city";
			scenario_long_desc = "You are floating above a large island city. There are many "+
			    "people here in the city.\n";
			string *air_six_messages=({"\n\nYou refocus your vision and "+
			    "you find yourself hovering above a large island city. You see many "+
			    "people here.\n\n",
			    "Many other boats arrive at the docks, all full of krougs, all of them "+
			    "hell-bent on the destruction of this city.\n\n",
			    "Seeing this, Leda runs back towards the city, shouting to people "+
			    "and telling them to follow her as she goes.\n\n",
			    "She gathers around a dozen or so people up, gathers then all to one "+
			    "small area and closes her eyes in concentration.\n\n",
			    "As she opens her eyes, her entire body begins to become vaporous, almost "+
			    "as if clouds and wind were trapped in a human form.\n\n",			
			    "Her vaporous body expands to envelop the entire party and then suddenly "+
			    "disappears.\n\n",
			    "Your vision becomes blurry, you can't make out anything.\n\n",
			    "Your vision returns and you find yourself hovering above a different island "+
			    "city! Leda and her group are all here, she's instructing them to find safety.\n\n",
			    "'Are you sure they aren't going to attack Conchoida?' you hear one of the "+
			    "people say. 'No but you are safer here than you were a moment ago.', says Leda "+
			    "back to him.\n\n",
			    "Leda closes her eyes in concentration and after a moment, the vaporous form "+
			    "disappears, leaving her back in human form. After a brief moment, she disappears "+
			    "again.\n\n", 
				"\n\nYour vision fades away again. After a moment you "+
				"begin to see a light. You could probably <focus> on it.\n\n"});
			for (int i=0; i < sizeof(air_six_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(player, air_six_messages[i]));
			break;
			
		case "water": // Conchoida Gates and Krystallos
		    scenario_short_desc = "At the gates of Conchoida";
			scenario_long_desc = "You are floating above the massive gates of Conchoida.\n";
			string *water_six_messages = ({"Pelias and the guards continue their attack "+
			    "on the krougs and appear to be pushing them back towards the docks.\n\n",
		    	"Pelias continues his attacks on the krougs as he blinks around behind "+
		    	"the other guards.\n\n",
		    	"He closes his eyes in concentration. As he opens his eyes a ball of ice "+
		    	"forms just above his hand, hovering and spinning slowly. He pushes his "+
		    	"hand out towards a kroug and the ball is hurled at him quickly. The "+
		    	"frost bolt hits the kroug in the shoulder, causing much damage to him.\n\n",
			    "\n\nYour vision fades away again. After a moment you "+
			    "begin to see a light. You could probably <focus> on it.\n\n"});
			for (int i=0; i < sizeof(water_six_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(player, water_six_messages[i]));
			break;
			
		case "life": // Elemental Temple Conduit Chamber and Tihosskias
		    scenario_short_desc = "In the Conduit Chamber";
			scenario_long_desc = "You are floating above the Conduit Chamber in the "+
			    "Elemental Temple.\n";
			string *life_six_messages = ({"\n\nYour vision fades away temporarily. Once "+
		    	"you regain it, you find yourself hovering above the Conduit Chamber in "+
		    	"the Elemental Temple. In the centre of the room you see the conduit "+
		    	"leading from the floor up into the ceiling.\n\n",
		    	"Sehis runs into the chamber from the north and begins to whisper a "+
		    	"a prayer to Psuchae. A large shadowy wall forms over the north entrance "+
		    	"into the room.\n\n",
		    	"Through the wall you can see the ghouls and wight attempting to get in "+
		    	"to the chamber but they are being repelled by the wall.\n\n",
		    	"You see Sehis examine the Conduit. The light inside of it is so dull and "+
		    	"barely moving. There are cracks on the outside of it.\n\n",
		    	"'The end is almost upon us.', you hear the voice of Nysa say in your "+
		    	"mind, 'It won't be long now.'\n\n"});
			for (int i=0; i < sizeof(life_six_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(player, life_six_messages[i]));
			set_alarm(50.0,0.0,&scenario_phase_seven(player));
			break;
	}

}

public void
scenario_phase_seven(object player)
{
	phase = 7;
	switch(scenario)
	{
		case "fire": // Alleyway and Panikos
			scenario_short_desc = "Alleyway beside a stronghold";
			scenario_long_desc = "You are floating above a stronghold.\n";
			string *fire_seven_messages=({"The flames surrounding Lethos disappear and "+
				"he returns to his normal form. He then closes his eyes and grasps the "+
				"shoulder of one of the other people. The person calms down almost "+
				"immediately as Lethos releases his shoulder, that look of wild panic "+
				"gone from their eyes.\n\n",
				"Lethos grabs the shoulder of the other person, and once "+
			    "again closes his eyes. As soon as he releases their shoulder, that person "+
			    "also calms down almost immediately.\n\n",
				"Sensing that his wall of flames was about to expire, Lethos "+
			    "commands the other two to run, pointing down the alleyway away from the wall. "+
			    "They run away and you lose sight of them as they round a corner at the end "+
			    "of the stronghold.\n\n",
			    "The wall of flames ceases to exist, the barbarians push "+
			    "forward immediately, charging directly at Lethos. He does his best to hold "+
			    "them off for as long as he possibly can using anything he can.\n\n",
				"Knowing that there is nothing he can do to hold them off "+
			    "any longer, you see him kneel down and begin to pray. You hear him say "+
			    "'May the flames of Lord Pyros ever guide me in my travels.' as the "+
			    "barbarians surround and engulf him.\n\n",
				"\n\nYour vision fades away again. After a moment you "+
				"begin to see a light. You could probably <focus> on it.\n\n"});
			for (int i=0; i < sizeof(fire_seven_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(player, fire_seven_messages[i]));
			break;
			
		case "earth": // Encampment and Onkolithos
			scenario_short_desc = "Hovering above an encampent";
			scenario_long_desc = "You are hovering above an encampment in the forest. "+
			    "You see many people here, including Cilla.\n";
			string *earth_seven_messages=({"It is just her and the "+
				"barbarians now. Cilla, visibly mentally and physically "+
				"drained, reverts back to her human form.\n\n",
				"She closes her eyes and concentrates once again on the barbarian "+
				"in front of her.\n\n",
				"A pebble forms in her hand, floats up above it and begins to turn "+
				"rapidly, gaining mass as it does so. When it is about the size of "+
				"a small boulder, she pushes her hands towards the barbarian and the "+
				"boulder hurls into his face. The barbarian falls to the ground in "+
				"agony.\n\n",
				"A large group of barbarians charge towards her. Knowing there is nothing "+
				"more she can do to hold them off, Cilla kneels down and begins to pray. "+
				"You hear her say 'May the mountains of Lady Gu ever guide me in my "+
				"travels.' as the barbarians reach her and smash her with their clubs.\n\n",
				"\n\nYour vision fades away again. After a moment you "+
				"begin to see a light. You could probably <focus> on it.\n\n"});
			for (int i=0; i < sizeof(earth_seven_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(player, earth_seven_messages[i]));
			break;
			
		case "air": // Menisca and Astrapi
			scenario_short_desc = "In a large island city";
			scenario_long_desc = "You are floating above a large island city. There are many "+
			    "people here in the city.\n";
			string *air_seven_messages=({"\n\nYou refocus your vision and "+
			    "you find yourself hovering above Menisca again.\n\n",
			    "Much of the city is now burning, there are bodies everywhere you "+
			    "look.\n\n",
			    "Leda appears out of nowhere again and witnesses the devastation that has "+
			    "taken place. Her saddness is visible as she looks around her.\n\n",
			    "'This battle is lost! Take everyone you can and go to Conchoida!', she "+
			    "yells out. Other people fighting around her stop what they are doing and "+
			    "run back into the city, grabbing whomever they can on the way.\n\n",
			    "'NO! I WILL NOT HAVE THIS! YOU WILL NOT ESCAPE!', you hear being yelled "+
			    "from the docks. As you and Leda both turn towards the noise, you both see a "+
			    "very large and dominating looking kroug.\n\n",
			    "The voice of Nysa echoes in your mind saying only one word in disgust, "+
			    "'Steerax.'\n\n",
			    "Leda glances back and sees large groups of people disappearing into thin air. "+
			    "She holds her arms out in front of her, pointing them towards Steerax. "+
			    "She utters a quiet prayer to Lady Aeria and suddenly a bolt of lightning "+
			    "rips forth from her arms and hits Steerax directly in the chest.\n\n",
			    "Steerax charges at Leda, sword drawn and held out in front of him like a giant "+
			    "skewer. It plunges straight through Leda's torso, her stomach pressed against "+
			    "the hilt of Steerax's sword, the blade protruding from her back.\n\n",
			    "'You and your kind will never win!' says Leda to Steerax, 'The Elementals will "+
			    "save us all and destroy you, or worse!'\n\n",
			    "As you see the life force in her fade away, you hear her whisper under her "+
			    "breath, 'May the winds of Lady Aeria ever guide me in my travels.'\n\n",
				"\n\nYour vision fades away again. After a moment you "+
				"begin to see a light. You could probably <focus> on it.\n\n"});
			for (int i=0; i < sizeof(air_seven_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(player, air_seven_messages[i]));
			break;
			
		case "water": // Conchoida and Zalisma
		    scenario_short_desc = "At the Conchoida docks";
			scenario_long_desc = "You are floating above the Conchoida docks.\n";
			string *water_seven_messages = ({"\n\nYour vision fades away temporarily. Once "+
		    	"you regain it, you find yourself hovering above the Conchoida docks again.\n\n",
		    	"Pelias and a group of guards have beaten the krougs back to the docks. "+
		    	"Out in the sea you see many more boats filled with krougs approaching.\n\n",
		    	"One boat has just docked and a large and dominating kroug steps out from it "+
		    	"and onto the dock.\n\n",
		    	"The voice of Nysa echoes in your mind saying only one word in hatred, "+
			    "'Steerax.'\n\n",
			    "Steerax pulls out his sword and begins to attack one of the guards. He "+
			    "swings his sword and it easily connects with the guard, fatally slashing "+
			    "across his chest and dropping him to the ground.\n\n",
			    "Pelias whispers a prayer to Lord Diabrecho and points his hand out towards "+
			    "Steerax. Steerax's face darkens with anger and he glares at his arms "+
			    "in shock and disbelief - they are frozen solid!\n\n",
			    "Steerax wanders around aimlessly for a moment, frantically trying to "+
			    "regain the use of his arms. When they finally thaw, he peers around angrily "+
			    "to see where this attack came from and after a few moments, he spies "+
			    "Pelias.\n\n",
			    "Rage overcomes his face and he charges directly at Pelias. Just as he "+
			    "is about to reach him, Pelias blinks behind a guard and away from "+
			    "Steerax.\n\n",
			    "Steerax sees Pelias again and charges at the guard standing in front "+
			    "of him.\n\n",
			    "Steerax's sword connects with the flesh of the guard, piercing his chest "+
			    "and causing the guard to collapse to the ground.\n\n",
			    "Pelias blinks behind another guard, the rage on Steerax's face grows and "+
			    "he begins to yell and scream.\n\n",
			    "Steerax continues to attack the guards that are standing in front of "+
			    "Pelias, dropping every one of them to the ground as he does so. More krougs "+
			    "continue to pile forth onto the docks from the boats.\n\n",
			    "You see Pelias look back at the gates. They are being closed now, everyone "+
			    "from the docks has made it inside to safety. It's just him and the few "+
			    "remaining guards now against a huge army of krougs.\n\n",
			    "Pelias does his best to heal the guards as they press their attack but "+
			    "their numbers are dwindling as both the army of krougs and Steerax continue "+
			    "to attack.\n\n",
			    "A group of krougs rush towards Pelias but stop when they hear "+
			    "Steerax yell out, 'THAT ONE IS MINE!'\n\n",
			    "Pelias glances back at the gates once again. They are completely shut now. "+
			    "He turns to the remaining guards and yells, 'Press the attack! Take as many "+
			    "as you can with you!', as he charges towards Steerax.\n\n",
			    "With a mighty swing, Steerax slices his sword across Pelias' face and neck, "+
			    "dropping him to the ground.\n\n",
			    "You see Pelias looking around, all of the guards are dead or on the ground "+
			    "dying. He himself is bleeding out, the life barely clinging to his body.\n\n",
			    "Steerax and his army charge towards the gates with nobody left to stand "+
			    "in their way.\n\n",
			    "As you see the life force in Pelias fade away, you hear him whisper under "+
			    "his breath, 'May the waters of Lord Diabrecho ever guide me in my travels.'\n\n",
			    "You heard a loud rumbling noise which draws your eyes out towards the sea. In "+
			    "the distance you see a large volcano - Mt. Pyros! Fire and ash are spewing out "+
			    "of the top of it, it is erupting!\n\n",
			    "\n\nYour vision fades away again. After a moment you "+
			    "begin to see a light. You could probably <focus> on it.\n\n"});
			for (int i=0; i < sizeof(water_seven_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(player, water_seven_messages[i]));
			break;
			
		case "life": // Elemental Temple Conduit and Vekpos
		    scenario_short_desc = "In the Conduit Chamber";
			scenario_long_desc = "You are floating above the Conduit Chamber in the "+
			    "Elemental Temple.\n";
			string *life_seven_messages = ({"The shadowy wall begins to fade away.\n\n",
		    	"As it disappears fully, the undead that were waiting outside rush into "+
		    	"the room.\n\n",
		    	"The ghouls charge directly at Sehis while the wight heads right for "+
		    	"the Conduit.\n\n",
		    	"Sehis whispers a prayer to Psuchae and pushes her hands towards one of "+
		    	"the ghouls. The ghoul turns and flees in terror from the room.\n\n",
		    	"The second ghoul lands an attack on Sehis, scraping her face badly with its "+
		    	"claw-like hand.\n\n",
		    	"The wight begins to beat on the Conduit with it's arms. Each time it lands "+
		    	"a blow with one of it's arms, the Conduit grows darker and the outside "+
		    	"cracks a bit more.\n\n",
		    	"Two more figures enter the room from the north. As they get closer you see "+
		    	"that they are the re-animated bodies of Jardeth and Tahla!\n\n",
		    	"The wight hits the Conduit again and the energy inside goes dark and stops "+
		    	"moving.\n\n",
		    	"Jardeth and Tahla join the wight and continue to bash the ouside of the "+
		    	"Conduit with their arms and bodies, each time the cracks grown larger.\n\n",
		    	"Sehis is fighting the ghoul back with a large hammer. Everytime she hits "+
		    	"it, the light inside the Conduit very dully pulses grey.\n\n",
		    	"Seeing the Conduit pulse back to life, Sehis seems to get renewed energy "+
		    	"and begins to fight with more vigor. She smashes her hammer into the skull "+
		    	"of the ghoul, crushing it completely; the ghoul collapsing to the ground. "+
		    	"The Conduit flashes bright white for a brief second.\n\n",
		    	"She races towards the wight and smashes her hammer into the back of the "+
		    	"foul creature and pulls it away from the Conduit. The energy inside of "+
		    	"the Conduit turns into a dull grey color and begins flowing slowly towards "+
		    	"the ceiling.\n\n",
		    	"Sehis bashes her hammer into the head of the wight until it no longer moves. "+
		    	"Each time she lands a blow, the conduit pulses with energy.\n\n",
		    	"She turns her attention now to Tahla. She raises her hammer and smashes it "+
		    	"into the back of her skull.\n\n",
		    	"Tahla turns around to face Sehis. Her face is twisted, her eyes pure white, "+
		    	"her mouth gaping open. She screams a horrible scream at Sehis and attacks "+
		    	"her with her arms, bashing them into Sehis wildly.\n\n",
		    	"Jardeth begins punching the Conduit in the area with the largest cracks. Each "+
		    	"time he lands a blow, the cracks grow larger, the energy inside grows darker "+
		    	"and moves slower.\n\n",
		    	"Tahla swings wildly and connects with her hand on Sehis' face, knocking her "+
		    	"down to the ground. Tahla leaps onto Sehis and begins to bite her savagely "+
		    	"on the face and neck.\n\n",
		    	"Jardeth punches the Conduit again, this time though his fist breaks through "+
		    	"the outside and as his hand touches the energy inside, it turns pitch black "+
		    	"and stops moving.\n\n",
		    	"The Conduit begins to shake, then the floor begins to shake, then the walls, "+
		    	"then the ceiling!\n\n",
		    	"The energy inside of the Conduit begins to flow downwards, into Jardeth's "+
		    	"hand!\n\n",
		    	"Sehis cries out in agony as Tahla continues to ravage her face with her "+
		    	"teeth. You see Sehis look over at Jardeth and the Conduit and all expression "+
		    	"of hope is gone.\n\n",
		    	"Knowing everything is lost, you hear Sehis whisper, 'May the spirit of Psuchae "+
		    	"ever guide me in my travels.', as she stops fighting.\n\n",
		    	"The black energy from the Conduit visibly flows through Jardeth, turning "+
		    	"his skin black as it moves through him. Once his body has been turned "+
		    	"completely, he pulls his hand out of the Conduit and turns around "+
		    	"to face Sehis. His eyes are glowing red, his body seems to be growing "+
		    	"larger.\n\n",
		    	"'With your Conduit destroyed I am able to inhabit one of your pitiful "+
		    	"cleric's bodies to deliver you a message directly.', you hear him say "+
		    	"while laughing.\n\n",
		    	"He reaches down and grabs Tahla, throwing her across the room violently. "+
		    	"He then reaches down and grabs Sehis by the throat, lifting "+
		    	"her up off the ground and looking directly at her saying mockingly, 'When "+
		    	"you see them in a moment, tell your gods that Theos has returned!'.\n\n",
		    	"He wraps his other hand completely around Sehis' head and squeezes, "+
		    	"crushing her head completely.\n\n",
			    "\n\nThe very fabric of reality around you begins to crumble. "+
			    "It looks like what you are seeing with your eyes is being torn "+
			    "up like a picture and falling into nothingness below you!\n\n",
			    "Everything goes blurry and your vision fades away again. After a moment you "+
			    "begin to see a light. You could probably <focus> on it.\n\n"});
			for (int i=0; i < sizeof(life_seven_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(player, life_seven_messages[i]));
			break;
	}

}

public void
scenario_end(object player)
{
	string name = player->query_real_name();
	phase = 8;
	switch(scenario)
	{
		case "fire": 
			scenario_short_desc = "A void";
			scenario_long_desc = "You are floating in some place you don't recognize. "+
            	"It is neither light, nor dark. It isn't warm, nor "+
                "cold. You sense nothing, feel nothing. You seem to "+
                "be nowhere.\n";
			string *fire_end_messages=({"\n\nYou refocus your vision and "+
			    "you find yourself in some place you don't recognize. It is neither "+
			    "light, nor dark. It isn't warm, nor cold. You sense nothing, feel "+
			    "nothing. You seem to be nowhere.\n\n",
				"You hear the voice of Nysa say 'You have witnessed "+
			    "enough for now. The gifts of fire are powerful and destructive. Should you "+
			    "choose to follow Lord Pyros and become one of his Fire Clerics, "+
			    "that is an example of the gifts that will be bestowed upon you.'\n\n",
				"Your vision fades away again and once you regain it, "+
				"you find yourself back where this all began.\n\n"});
			for (int i=0; i < sizeof(fire_end_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(player, fire_end_messages[i])); 
			set_alarm(25.0,0.0, &return_player(player));
			if (GUILD_MANAGER->query_has_completed_scenarios(player) != 5)
				GUILD_MANAGER->set_has_completed_scenarios(name, 1);
			break;
			
		case "earth":
			scenario_short_desc = "A void";
			scenario_long_desc = "You are floating in some place you don't recognize. "+
            	"It is neither light, nor dark. It isn't warm, nor "+
                "cold. You sense nothing, feel nothing. You seem to "+
                "be nowhere.\n";
			string *earth_end_messages=({"\n\nYou refocus your vision and "+
			    "you find yourself in some place you don't recognize. It is neither "+
			    "light, nor dark. It isn't warm, nor cold. You sense nothing, feel "+
			    "nothing. You seem to be nowhere.\n\n",
				"You hear the voice of Nysa say 'You have witnessed "+
			    "enough for now. The gifts of earth are both powerful and protective. "+
			    "Should you choose to follow Lady Gu and become one of her Earth Clerics, "+
			    "that is an example of the gifts that will be bestowed upon you.'\n\n",
				"Your vision fades away again and once you regain it, "+
				"you find yourself back where this all began.\n\n"});
			for (int i=0; i < sizeof(earth_end_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(player, earth_end_messages[i])); 
			set_alarm(25.0,0.0, &return_player(player));
			if (GUILD_MANAGER->query_has_completed_scenarios(player) != 5)
				GUILD_MANAGER->set_has_completed_scenarios(name, 2);
			break;
			
		case "air":
			scenario_short_desc = "A void";
			scenario_long_desc = "You are floating in some place you don't recognize. "+
            	"It is neither light, nor dark. It isn't warm, nor "+
                "cold. You sense nothing, feel nothing. You seem to "+
                "be nowhere.\n";
			string *air_end_messages=({"\n\nYou refocus your vision and "+
			    "you find yourself in some place you don't recognize. It is neither "+
			    "light, nor dark. It isn't warm, nor cold. You sense nothing, feel "+
			    "nothing. You seem to be nowhere.\n\n",
				"You hear the voice of Nysa say 'You have witnessed "+
			    "enough for now. The gifts of air are both powerful and supportive. "+
			    "Should you choose to follow Lady Aeria and become one of her Air Clerics, "+
			    "that is an example of the gifts that will be bestowed upon you.'\n\n",
				"Your vision fades away again and once you regain it, "+
				"you find yourself back where this all began.\n\n"});
			for (int i=0; i < sizeof(air_end_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(player, air_end_messages[i])); 
			set_alarm(25.0,0.0, &return_player(player));
			if (GUILD_MANAGER->query_has_completed_scenarios(player) != 5)
				GUILD_MANAGER->set_has_completed_scenarios(name, 3);
			break;
			
		case "water":
		    string *water_end_messages=({"\n\nYou refocus your vision and "+
			    "you find yourself in some place you don't recognize. It is neither "+
			    "light, nor dark. It isn't warm, nor cold. You sense nothing, feel "+
			    "nothing. You seem to be nowhere.\n\n",
				"You hear the voice of Nysa say 'You have witnessed "+
			    "enough for now. The gifts of water are both powerful and healing. "+
			    "Should you choose to follow Lord Diabrecho and become one of his "+
			    "Water Clerics, that is an example of the gifts that will be bestowed "+
			    "upon you.'\n\n",
				"Your vision fades away again and once you regain it, "+
				"you find yourself back where this all began.\n\n"});
			for (int i=0; i < sizeof(water_end_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(player, water_end_messages[i])); 
			set_alarm(25.0,0.0, &return_player(player));
			if (GUILD_MANAGER->query_has_completed_scenarios(player) != 5)
				GUILD_MANAGER->set_has_completed_scenarios(name, 4);
			break;
			
		case "life":
			string *life_end_messages=({"\n\nYou refocus your vision and "+
			    "you find yourself in some place you don't recognize. It is neither "+
			    "light, nor dark. It isn't warm, nor cold. You sense nothing, feel "+
			    "nothing. You seem to be nowhere.\n\n",
				"You hear the voice of Nysa say 'There is nothing else left "+
				"to show you. The gifts of spirit are both powerful and damaging to "+
				"the Soulless. Should you choose to follow Psuchae and become one of the "+
			    "Spirit Clerics, that is an example of the gifts that will be bestowed "+
			    "upon you.'\n\n",
			    "'If you do not stop the Soulless on their rampage, THAT will be the future "+
			    "that you can expect. Regardless of which you choose, all will grant you "+
			    "the power to push back the Undead and to stop this from every happening.'\n\n",
			    "'When you are ready, visit the statue of the Diety you wish to follow in "+
			    "the Temple and worship them. This will set you forward on your chosen path.'\n",
			    "'Go now and choose wisely.'\n\n",
				"Your vision fades away again and once you regain it, "+
				"you find yourself back where this all began.\n\n"});
			for (int i=0; i < sizeof(life_end_messages); i++)
				set_alarm((10.0*itof(i)), 0.0, &tell_object(player, life_end_messages[i])); 
			set_alarm(35.0,0.0, &return_player(player));
			if (GUILD_MANAGER->query_has_completed_scenarios(player) != 5)
				GUILD_MANAGER->set_has_completed_scenarios(name, 5);
			break;
	}
}

public void
return_player(object player)
{
	player->move_living("X",ELEMENTALIST_TEMPLE+"conduit",1,0);
	tell_room(player, QCTNAME(player)+" suddenly appears out of nowhere!\n",player);
	set_alarm(1.0, 0.0, &clear_scenario());
}	

public int
do_focus()
{
    switch(phase)
    {
        case 1:
            scenario_phase_two(scenario_player);
            break;
        case 2:
            scenario_phase_three(scenario_player);
            break;
        case 3:
            scenario_phase_four(scenario_player);
            break;
        case 4:
            scenario_phase_five(scenario_player);
            break;
        case 5:
            scenario_phase_six(scenario_player);
            break;
        case 6:
            scenario_phase_seven(scenario_player);
            break;
        default:
            scenario_end(scenario_player);
            break;
    }
    return 1;
}

public void
init()
{
    ::init();
    add_action(do_focus,"focus");
}

public void
clear_scenario()
{
	scenario = "";
	occupied = 0;
	phase = 0;
	scenario_player = 0;
	
	mixed *alarms_running = get_all_alarms();
	for(int i = 0; i <sizeof(alarms_running); i++)
	{
	   remove_alarm(alarms_running[i][0]);
	} 
	scenario_short_desc = "A void";
	scenario_long_desc = "You are floating in some place you don't recognize. "+
                         "It is neither light, nor dark. It isn't warm, nor "+
                         "cold. You sense nothing, feel nothing. You seem to "+
                         "be nowhere.\n";
}

/*
 * Function name: prevent_leave
 * Description:   Called when an object is trying to leave this container
 *                to see if we allow it to leave.
 * Arguments:     object ob - the object trying to leave
 * Returns:       1 - The object is not allowed to leave
 *                0 - The object is allowed to leave
 */
public int
prevent_leave(object ob)
{
    // We don't actually want to prevent them from leaving but we want to 
    // reset the room so that others can use it
    
    clear_scenario();
    return 0;
}