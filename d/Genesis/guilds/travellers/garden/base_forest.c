/* 
 * Base Room for the Forest in the
 * Sparkle Area on Genesis
 * 
 * Includes: 
 * Weather Descriptions
 * Time of day and year
 * Special Herbsearch functions
 * Diffrent forest types
 * Special location sense function
 *
 * Created by Raist (2000-11-19)
 */
inherit "/d/Pegana/common/room";

#include <herbsearch.h>

object clock;
string temp_desc;
string time_day;
int    weather;
int    forest_type;
int    no_herbs_here;

void create_forest();

void
set_forest_type(int type)
{
    forest_type = type;
}

int
query_forest_type()
{
    return forest_type;
}

void
set_no_herbs(int arg)
{
    no_herbs_here = arg;
}

int
query_no_herbs()
{
    return no_herbs_here;
}

void
make_messages()
{
	switch(forest_type)
	{
	case 0:
		add_prop(ROOM_AS_MESSAGE_TEXT, ({
			"A bird flies past you quickly disappearing between the " +
			"trees.\n",
			"A gust of wind ruffles your hair.\n",
			"Some animal call can be heard far away.\n",
			"The air is really fresh in the forest.\n",
			"A small mouse skitters around between the trees.\n"
		}));
	break;
	case 1:
		add_prop(ROOM_AS_MESSAGE_TEXT, ({
			"You hear a bird call within the dense forest.\n",
		    "You hear something rummaging around between the " +
		    "trees nearby.\n",
		    "A shrill animal call makes your heart stand still for a"+
		    " few seconds.\n",
		    "The air here inside the dense forest is still and "+
		    "oppressive.\n",
		    "Suddenly a rush of leaves can be"+
		    " heard but no winds ever reach the ground.\n"
		}));
	break;
	case 2:
	    add_prop(ROOM_AS_MESSAGE_TEXT, ({
			"You see a large bird far away.\n",
		    "You notice how clean and fresh the wind is here " +
		    "in the open.\n",
		    "You see a couple of deer grazing far away.\n",
		    "A gust of wind ruffles your hair.\n",
		    "The tall grass waves in the wind.\n"
		}));
    }
}

string
sky_item()
{
    switch(time_day)
    {
	case "night":
	    return "It is dark with only the stars shining.\n";
	    break;
	case "early morning":
	    return "It is dark but in the east you can spot the beginning"+
		" light of day.\n";
	    break;
	case "late evening":
	    return "It is darkening with only a little light in the west.\n";
	    break;
	default:
	    if (weather > 0)
			return "It is light at this time of day.\n";
	    else
			return "It is very dark and clouded even at this time of day.\n";
	    break;
    }
}

string
vegitation()
{
    if ((forest_type==0) || (forest_type==1))
	{
	    if ((time_year<3) || (time_year>10))
			return "It is almost impossible to spot any vegetation save "+
				"the trees and bushes.\n";
		if ((time_year==3) || (time_year==4))
			return "Everywhere in the forest green grass and other new "+
				"plants are appearing.\n";
		if ((time_year==5) || (time_year==6) || (time_year==7))
			return "Colorful flowers and green plants are visible "+
				"everywhere.\n";
		if ((time_year==8) || (time_year==9))
			return "At this time of year the leaves on the trees are "+
				"reddening and the grass is getting a darker green hue.\n";
		if (time_year==10)
		    return "the leaves are falling from the trees while the only "+
				"small growths to be found are mushrooms and the like.\n";
    }

    if (forest_type==2)
	{
		if ((time_year<3) || (time_year>10))
			return "It consists mostly of dried moss and grass.\n";
		if ((time_year==3) || (time_year==4))
		    return "It consists of dried moss but you see that fresh green "+
				"weeds and grasses are growing here and there.\n";
		if ((time_year==5) || (time_year==6) || (time_year==7))
			return "It is tall weeds and grasses on small tussocks of moss, "+
				"mostly.\n";
		if ((time_year==8) || (time_year==9))
			return "The vegetation consists is tall weeds and grasses on "+
				"large tussocks of soft green moss.\n";
		if (time_year==10)
			return "The vegetation consists of dried or drying weeds and "+
				"grasses on tussocks of moss.\n";
    }

    if (forest_type==3)
	{
		return "There is too little light here between the trees to allow"+
			"the growth of any undergrowth, the only vegetation is the"+
			"trees.\n";
    }

    if (forest_type==4) {
		if ((time_year<5) || (time_year>9))
			return "The tall grass is dry and brown.\n";
		if (time_year==5)
		    return "Here and there fresh green grass is growing.\n";
		if ((time_year==6) || (time_year==7))
			return "The vegetation consists of tall green grass.\n";
		if ((time_year==8) || (time_year==9))
			return "The tall green grass growing here has a golden color.\n";
    }
}

string
long_maker()
{
    string desc;

    switch(query_forest_type())
    {
        case 0:
	if ((time_year<3) || (time_year>10))
	    desc = "This is an area in Darkleaf Forest where tall deciduous"+
		" trees"+
		" grow, not that there are any leaves on the trees at this"+
		" time of year where the tall oaks and birches are bare.";
	if ((time_year>2) && (time_year<5))
	    desc = "This is an area in Darkleaf Forest where tall deciduous"+
		" trees"+
		" grow, and fresh new leaves will soon make the forest a light"+
		" and cheerful place.";
	if ((time_year>4) && (time_year<8))
	    desc = "This is an area in Darkleaf Forest where tall deciduous"+
		" trees"+
		" grow. The leaves of the trees are coloring the forest a"+
		" cheerful green.";
	if ((time_year>7) && (time_year<10))
	    desc = "This is an area in Darkleaf Forest where tall deciduous"+
		" trees"+
		" grow. The leaves of the trees are getting a darker green"+
		" color and some are reddening at this time of year.";
	if (time_year==10)
	    desc = "This is an area in Darkleaf Forest where tall deciduous"+
		" trees"+
		" grow. The leaves are falling from the trees, covering the"+
		" ground in a soft layer of red leaves.";
	if ((time_day=="night") || (time_day=="late evening") ||
	    (time_day=="early morning")) {
	    desc += " There is not much light between the trees at this time"+
		" of day. ";
	}
	else {
	    desc += " The light is shining down through the branches of the"+
		" trees. ";
	}
        break;
        case 1:
	if ((time_year<3) || (time_year>10))
	    desc = "This is an area in Darkleaf Forest where the Tarrinian"+
		" elves live. At this time of year whisps of smoke can be seen"+
		" rising from the small houses that are built in the trees.";
	if ((time_year>2) && (time_year<5))
	    desc = "This is an area in Darkleaf Forest where the Tarrinian"+
		" elves live. Many elves are working on planting new plants"+
		" and tending the fresh new growths at this time of year.";
	if ((time_year>4) && (time_year<10))
	    desc = "This is an area in Darkleaf Forest where the Tarrinian"+
		" elves live. At this time of year elves are wandering around"+
		" in the forest all day, some singing, some meditating, and"+
		" some just enjoying the forest.";
	if (time_year==10)
	    desc = "This is an area in Darkleaf Forest where the Tarrinian"+
		" elves live. At this time of year the elves are busy fishing"+
		" and hunting and gathering supplies for the winter that will"+
		" come soon.";
	if ((time_day=="night") || (time_day=="late evening") ||
	    (time_day=="early morning")) {
	    desc += " The light from many houses in the trees and magical"+
		" light sources spread a golden glow between the elven"+
		" dwellings. ";
	}
	else {
	    desc += " The light is shining down through the branches of the"+
		" trees. ";
	}
        break;
        case 2:
	if ((time_year<3) || (time_year>10))
	    desc = "This is an area in Darkleaf Forest where tall deciduous"+
		" trees"+
		" grow, not even at this time of the year does much light"+
		" reach the ground in this dense part of the forest.";
	if ((time_year>2) && (time_year<5))
	    desc = "This is an area in Darkleaf Forest where tall deciduous"+
		" trees"+
		" grow, and fresh new leaves will soon cover the ground in"+
		" the dense forest in darkness once more.";
	if ((time_year>4) && (time_year<8))
	    desc = "This is an area in Darkleaf Forest where tall deciduous"+
		" trees"+
		" grow. By looking up into the dense forest roof you spot"+
		" fresh green leaves.";
	if ((time_year>7) && (time_year<10))
	    desc = "This is an area in Darkleaf Forest where tall deciduous"+
		" trees"+
		" grow. At this time of year almost no light reach the ground"+
		" in this dense part of the forest.";
	if (time_year==10)
	    desc = "This is an area in Darkleaf Forest where tall deciduous"+
		" trees"+
		" grow. The leaves are falling from the trees allowing a little"+
		" light to reach the ground in the dense forest.";
	if ((time_day=="night") || (time_day=="late evening") ||
	    (time_day=="early morning")) {
	    desc += " There is almost total darkness between the trees at this"+
		" time of day. ";
	}
	else {
	    desc += " You guess it is daytime even though almost no light reach"+
		" the ground. ";
	}
        break;
    }

    desc += temp_long;
    return desc;
}

/*
 * Function name: check_exit
 * Description  : This is a function to check
 *                players location sense skill
 *                and if its below LOC_SKILL
 *                the exit will be randomized
 *                from all exits in the room.
 */
int
check_exit()
{
    string *exit_rooms, *exit_cmds;
    int selected;
    
    if(!interactive(this_player())) return 0;

    if(this_player()->query_skill(SS_LOC_SENSE) < LOC_SKILL)
	{
	    write("You are not really sure that you are heading in the right"+
		  " direction.\n");
	    
	    exit_cmds = query_exit_cmds();
	    exit_rooms = query_exit_rooms();
	    selected = random((sizeof(exit_rooms)));
	    this_player()->move_living(exit_cmds[selected], exit_rooms[selected]);
	    
	    return 1;
	}

    return 0;
}

/*
 * Function name: add_forest_exit
 * Description  : A short way of adding the special exit
 *                that checks the players location sense
 *                and if its lower then LOC_SKILL that
 *                is defined in base_forest.h they will
 *                lost in the forest.
 * Dependings   : check_exit
 */
void
add_forest_exit(string path, string exit, int hard)
{
    add_exit(path, exit, "@@check_exit@@", hard, 1);
}

void
add_herbs()
{
    int amount;
    int i;

	amount = random(5);

	for(i = 0; i < amount; i++)
    {
		add_herb_file(HERBDIR + "herb"+(1+random(4)));
    }

    set_search_places(({"bushes","bush","shrubs","shrub",
		"flowers","forest","ground","plants","here"}));

    add_prop(OBJ_I_SEARCH_TIME, 5);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
}

void
add_animals()
{
    if((forest_type == DENSE) || (forest_type == LIGHT) || (forest_type == OPEN))
	{
	    if(!present("npc_animal"))
		{
		    if(random(2)>0)
			add_npcs(NPCDIR+"animal", random(3));
		}
	}
}

void
reset_room()
{
    set_searched(0);

    add_animals();
}

nomask void
create_room()
{
    int *all_time;

    clock = find_object("/d/Pegana/common/weathclock");
    if (!objectp(clock)) clock = clone_object("/d/Pegana/common/weathclock");

    all_time  = clock->query_exact_time();
    weather   = clock->query_exact_weather();
    time_day  = clock->query_time_string();
    time_year = all_time[3];

    create_forest();

    if(!query_no_herbs())
        add_herbs();

    switch (forest_type) {
    case 0:

	add_item("trees", "Most of them are tall birches and oaks.\n");
	add_item(({"oaks", "birches"}),
		 "They are tall and slender, growing between the"+
		 " other trees.\n");
	add_item(({"tree", "birch", "oak"}),
		 "Just one of hundreds of trees.\n");
	add_item("ground","It is covered with leaves.\n");
	add_item("leaves","They must come from the trees.\n");
	add_item(({"branch", "bough", "root"}),
		 "Others like that one are visible everywhere.\n");
	add_item(({"branches", "boughs", "roots"}),
		 "Everywhere you look they are visible.\n");
	add_item("forest", "It is all around you consisting of birches"+
		 " and oaks mostly.\n");
	add_item("sky",   "@@sky_item@@");
	add_item(({"vegetation","growth","herbs","plants"}),
		 "@@vegitation@@");
	break;
    case 1:

	add_item("moss", "It is shaped as large tussocks between and in"+
		 " the water pools.\n");
	add_item("pools", "They are pools of stagnant water that doesn't"+
		 " smell very good.\n");
	add_item("pool", "It is a water pool.\n");
	add_item(({"weeds", "grasses"}), "They are tall, blocking off"+
		 " much of the view.\n");
	add_item(({"weed", "grass"}), "Any particular plant, or?\n");
	add_item("ground","Where there IS a ground it is in the shape"+
		 " of tussocks of mosses.\n");
	add_item("forest", "There is not much forest right here.\n");
	add_item("trees", "There are not too many trees right here.\n");
	add_item("sky",   "@@sky_item@@");
	add_item(({"vegetation","growth","herbs","plants"}),
		 "@@vegitation@@");
	break;
    case 2:

	add_item("trees", "Most of them are tall birches and oaks.\n");
	add_item(({"oaks", "birches"}),
		 "They are tall and wild they block out almost all light.\n");
	add_item(({"tree", "birch", "oak"}),
		 "Just one of hundreds of trees.\n");
	add_item("ground","It is covered with leaves but you find it hard"+
		 " to distinguish any details in the faint light.\n");
	add_item("leaves","They must come from the trees.\n");
	add_item(({"branch", "bough", "root"}),
		 "Others like that one are visible everywhere.\n");
	add_item(({"branches", "boughs", "roots"}),
		 "Everywhere you look they are visible.\n");
	add_item("forest", "It is all around you consisting of birches"+
		 " and oaks mostly.\n");
	add_item("sky",   "@@sky_item@@");
	add_item(({"vegetation","growth","herbs","plants"}),
		 "@@vegitation@@");
	break;
    }

    set_short("an area in the forest");
    set_long("@@long_maker@@");

    reset_room();

    make_messages();
}

void
create_forest()
{

}
