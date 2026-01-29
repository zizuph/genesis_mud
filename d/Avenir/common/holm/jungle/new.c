// file name:        /d/Avenir/common/holm/jungle/lf7.c
// creator(s):       Lilith, Nov 96
// revisions:        Add wolf bone -Sirra
// purpose:
// note:
// bug(s):
// to-do:            add code for jumping off ledge into whirlpool,
//                   resulting in death. Also, add water spirits.

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/holm/jungle/jungle_base";

/* Include the local area defines, etc */
#include "/d/Avenir/common/holm/holm.h"
#include "/d/Avenir/common/holm/wolf.h"

int check_ledge();
int do_search(string str);
int find_bone(object player);

int found;


/*
 * Function name: reset_domain_room
 * Description:   This function should be used for for reseting herbs
 */
void reset_domain_room()
{
	 set_searched(0);
	 found = 1;
	 ::reset_domain_room();
}

/* Now create the room.  */
void
create_jungle_room()
{
	 set_short("in a hollow, overlooking a whirlpool");
	 set_long("Grass grows thickly along the western slope of the "+
		  "hollow, blending gradually into a moss-covered ledge "+
		  "of rock. The ledge juts out over a deep pool, the "+
		  "center of which is caught in a whirl. There are water "+
		  "spirits here, and they permit no rest for the stream, "+
		  "nor for those who visit it.\n");

	 add_exit("lf10", "southwest", 0);

	 add_prop(ROOM_I_TYPE, ROOM_BEACH);
	 add_cliff();
	 add_moss();
	 add_atrack();
	 add_stream();
	 add_grass();

	 add_item(({"pool", "whirl", "whirlpool"}),
		  "It is cloudy and chill. Fingers of water vapour drift "+
		  "in a circular motion above the torrent of water that "+
		  "inexorably pulls everything beneath its surface.\n");

	 add_prop(OBJ_S_SEARCH_FUN,"do_search");
	 //add_prop(OBJ_I_SEARCH_TIME,2);

		 reset_domain_room();
}



string
do_search(string str)
{

	object player = this_player();
	string  place,
			  *herb_names = ({}),
				this_herb;
	 int     i;
	 object bone;

	 if (!places)
		  places = ({"here","ground"});

	 if (sscanf(str,"%s for %s", place, this_herb) == 2
		  && member_array(place,places) >= 0)
	 {
		  if (this_herb == "herbs")
				return this_object()->search_for_herbs(player);

		  for (i = 0; i < sizeof(herbs); i++)
				herb_names += ({ herbs[i]->query_herb_name() });
		  if ((i = member_array(this_herb, herb_names)) > -1)
				return this_object()->search_for_herbs(player, herbs[i]);
	 }

	//notify_fail("Search what?\n");

	if(!str)
	return "";

	if(str == "ledge" && found<1)
	{
		//write("You might slip!\n");
		return "You might slip!\n";
	}

	//If there are any bones here, the following will process.

	if (str == "ledge" && found>0)
	{
		write("Dont slip!\n");
		set_alarm(2.0, 0.0, &find_bone(player) );
		return " ";
	}

	else
	{
		return "";
	}


}


int
find_bone(object player)
{

	object bone;
	int num;

/*
Something you might thing is cute,
because I did, is to have the player
actually slip into the whirlpool.
Here's what you might not know...
a player really can die in the whirlpool.
I never have. The spirits always saved me.
I should have taken the name whirlpool_die_die_die.c
a little more to heart, huh? -Sirra

	num = random(5);

	if(num == 0)
	{
		player->catchmsg("You Slip!!\n"
			+"The shockingly cold water makes you gasp as you come into "
			+"contact with it.\n");
		say(QCTNAME(player)+" slips off the ledge and falls whirlpool below!\n");
		player->move_living("M", "/d/Avenir/common/holm/jungle/whirlpool_die_die_die.c", 1, 0);
		return 1;
	}
*/

	found--;
	bone = clone_object(WOLF_BONE + "pelvic.c");
	bone->move(player, 1);

	player->catch_msg("You found a pelvic bone!\n");

	return 1;
}




void
init()
{
	 ::init();
	 check_ledge();
	 //add_action(do_search, "search");
}

int
check_ledge()
{
	 if(found<1)
	 {

		add_item("ledge", "It is covered in moss and slick with "+
		  "moisture. It juts out over the pool of water with "+
		  "the whirl at its center.\n");

		return 1;
	 }


		add_item("ledge", "It is covered in moss and slick with "+
		  "moisture.  It juts out over the pool of water with "+
		  "the whirl at its center. At the end you see something "+
		  "white and glittering sticking out from the moss at the "+
		  "end of the ledge.\n");

	 return 1;
}

