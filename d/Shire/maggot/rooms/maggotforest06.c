
/* 
	*Small forest area near Maggot's field
	*Altrus, March 2005
*/
#include "/d/Shire/sys/defs.h"
#include "defs.h"
#define MUSHROOM_PROP "_already_picked_mushrooms"

inherit BASE_FOREST;
inherit AREA_ROOM;

void create_area_room()
{
	areadesc = "dense thicket";
	area = "in";
	areaname = "the Marish";
	land = "Eriador";
	areatype = 0;
	extraline = "Through the breaks in the trees you can see " +
	"a field to the north. The undergrowth here is suprisingly " +
	"sparse, with most of the ground given to fungal growth.\n";
	
	add_item(({"breaks", "field", "fields"}), "The fields seen through " +
	"the breaks in the trees appear to be filled with turnips.\n");
	add_item(({"turnip", "turnips"}), "From this distance it is hard " +
	"to tell, but the turnips look quite large.\n");
	add_item(({"trees", "tree"}), "The trees are deciduous, the " +
	"foliage a healthy green.\n");
	add_item(({"foliage", "leaves"}), "The leaves range in size, " +
	"from smaller than a length of a finger to twice the size of a " +
	"hand.\n");
	add_item(({"undergrowth", "bushes"}), "There is not much to " +
	"speak of, just a few bushes growing near the bases of the trees.\n") +
	add_item(({"growth", "lichen", "fungal growth"}), "Lichen grows " +
	"on the trees in abundance; mushrooms litter the forest floor.\n");
	add_item(({"mushroom", "mushrooms"}), "Most of the mushrooms " +
	"here look fairly small, but there is a group of them that appear " +
	"to be quite large.\n");
	add_item(({"ground", "floor", "forest floor", "soil"}), "The ground is " +
	"soft, and pleasantly cool. The soil is dark, nearly black, and " +
	"appears quite fertile.\n");
	add_item(({"large mushrooms", "large mushroom", "group"}), "These " +
	"large mushrooms look ready to pick!\n");
	
	set_add_rtells_forest();
	
	add_std_herbs("forest");
	
	add_exit(ROOM_DIR + "maggotforest02", "north");
	add_exit(ROOM_DIR + "maggotforest07", "west");
	add_exit(ROOM_DIR + "maggotforest05", "east");
}

void init()
{
	::init();
	add_action("pick_large_mushrooms", "pick");
}

int pick_large_mushrooms(string str)
{
if (this_player()->query_prop(MUSHROOM_PROP))
{
	this_player()->catch_msg("You have already picked mushrooms. " +
	"There is no need to be greedy.\n");
	return 1;
}

else
{	
	if(str == "large mushrooms")
        {
		this_player()->catch_msg("You kneel down in the soft, loamy " +
		"soil, searching for just the right sized mushrooms. Eventually " +
		"you stand back up, having picked a small bunch of fairly large " +
		"sized mushrooms.\n");
		say(QCTNAME(this_player()) + " kneels down for a moment, " + 
		"searching the immediate area for something. Eventually " + 
		HE_SHE(this_player()) + " stands back up with what looks like " +
		"a modest amount of largish mushrooms in " + HIS_HER(this_player()) + " hand.\n");
		
		setuid();
		seteuid(getuid());
		
		clone_object("/d/Shire/maggot/obj/maggot_shrooms.c")->move(this_player());
		
		this_player()->add_prop(MUSHROOM_PROP,1);
		
		return 1;
        }
        
	else if(str == "mushrooms")
	{
		write("Pick which mushrooms?\n");
		return 1;
	}
	
	else 
        {
		write("Pick what?\n");
		return 1;
        }
}	
}
