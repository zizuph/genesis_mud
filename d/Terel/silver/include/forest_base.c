/* File         : /d/Terel/silver/include/forest_base.c
 * Creator      : Tomas
 * Date         : August 2000
 * Purpose      : Base file for Silver Forest.
 * Related Files:
 * Comments     : Taken from Elderwood forest.c file.
 * Modifications:
 * Modified by Pasqua - unq_no_move
 *     - Fixed random hag, added roaming bandits, random animals..
 * Cotillion - 2020-09-07
 * - Fixed cloning to not fill the area over time.
 * - Updated to show the same exits as obvious each time for the same player
 * Lucius - 2021-03
 * - Exclude 'up','down' from custom unq_no_move.
 */

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <filter_funs.h>
#include "/d/Terel/include/herb_arrs.h"
#include "defs.h"
#include "math.h"

inherit INCLUDE + "cold_room.c";
inherit "/d/Terel/std/room_tell.c";
inherit "/d/Terel/std/herbsearch.c";

#define  ONE_OF_LIST(array) ((array)[random(sizeof(array) -1)])
#define  HAS_HOVEL is_hovel()
#define  NO_HOVEL_DESC  if(!HAS_HOVEL) return 0

string *birds   = ({"bird","falcon"}),
       *small   = ({"rodent","squirrel","rabbit","pfox","hare","ferret"}),
       *large   = ({"deer","caribou","moose","mbear"});

int long, short, exits, roomCount;
int hovel_flag = 0;

int
is_hovel()
{
    return hovel_flag;
}

int
set_this_hovel()
{
    SEND(file_name(TO));
    (HOVEL)->set_exit(TO);
    add_exit(HOVEL, "enter", 0, 1, 0);
    hovel_flag = 1;
    return hovel_flag;
}

int
set_long_desc(int i)
{
    long = i;
}

int
set_short_desc(int i)
{
    short = i;
}

int
am_first()
{
    if((HOVEL)->block())
	return 0;
    for(int i = 0; i < sizeof(HAG_LOCATIONS); ++i)
    {
	if(HAG_LOCATIONS[i]->is_hovel())
	    return 0;
    }
    return 1;
}

void
set_hovel()
{
    if(!am_first())
	return;
    int hag_index = random(sizeof(HAG_LOCATIONS));
    (HAG_LOCATIONS[hag_index])->set_this_hovel();
    write_file(HOVEL_LOC_LOG, "Hovel location: " + HAG_LOCATIONS[hag_index] +
      ". Timestamp: " + ctime(time()) + "\n");
}

void
init()
{
    ::init();
    start_room_tells();
}

public void
reset_terel_room()
{
}

public void
create_room()
{
    ::create_room();
    set_short("@@short_desc@@");
    set_long("The massive Silver forest surrounds you. Its many " +
      "varieties of trees densely populate the area. Heavy snowfall " +
      "and the dense scrub brush makes it difficult for you to travel " +
      "swiftly through the forest. " +
      "@@long_desc@@");


    add_prop("_room_m_da_dragonsteed_no_land","The forest " +
      "is too thick for your dragon to land here.");

    add_item(({"rocks", "pebbles"}),
      "Various sized rocks and pebbles litter the forest " +
      "floor.\n");
    add_item(({"plants", "woodland plants"}),
      "Besides trees, a diverse number of plants grow in the " +
      "forest. Bushes grow everywhere, somewhat " +
      "impeding your travel and blocking your view.\n");
    add_item("bushes",
      "Bushes of different color and sizes grow everywhere. " +
      "Some are thick and block your view while others are " +
      "thin and spindly.\n");
    add_item(({"snow", "drift","snowdrift","snow drifts","snowsdrift",
	"patches of snow"}),
      "The forest, plants, shrubs and ground are covered in " +
      "a thick blanket of snow.\n");
    add_item(({"hollow logs", "hollow log"}),
      "The logs are rotting and hollowed out. Most of them " +
      "are partially buried in the snow.\n");
    add_item(({"tree","trees"}),
      "Several varieties of trees such as evergreens and inhabit the " +
      "forest. However, " +
      "the forest was named after a particular common tree which " +
      "has a roundish leaf that is greenish bronze in color " +
      "and streaked with silver. The silver trees provide " +
      "a soft silverish tint to the forest.\n");
    add_item(({"evergreen trees", "conifer trees", "evergreen",
	"evergreens", "conifers", "conifer"}),
      "The dominate evergreen trees here are tall pines. Also " +
      "growing here are hemlocks and some cedars. The trees reach " +
      "to the sky and block out much of the light.\n");
    add_item(({"silver tree","silver trees"}),
      "The silver trees scatter about the forest. Their greenish bronze leaves " +
      "are streaked with silver, providing a soft silver glow about the forest.\n");
    add_item(({"pine trees", "pine tree", "hemlock", "hemlocks",
	"cedar", "cedars", "pines", "hemlock trees", "hemlock tree",
	"cedar trees", "cedar tree"}),
      "These evergreens dominate the forest. Some grow along the rocks " +
      "showing exposed roots.\n");
    add_item(({"ground", "path", "forest debris", "debris",
	"forest's floor", "floor", "down"}),
      "The ground is mostly covered in deep snow with the exception of various " +
      "dry spots around rock outcroppings, underneath " +
      "bushes and along the edges of fallen trees. Twigs, branches " +
      "and other various forest debris can be seen mixed with " +
      "snow.\n");
    add_item(({"leaves", "leaf"}),
      "You see a mat of both fresh and dead leaves covering the " +
      "ground. Poking out of them are dead branches, some " +
      "plants, stones, and other signs of a living forest.\n");
    add_item(({"fallen branches", "dead branches", "dead branch",
	"branches", "branch"}),
      "Broken branches can be seen scattered about the snow drifts. " +
      "Some look like they just fell from the trees, " +
      "splintered and twisted. They lay on the ground in " +
      "various stages of decomposition.\n");
    add_item(({"twig", "twigs"}),
      "They are small branches, laying scattered across the " +
      "forest's floor.\n");
    add_item(({"needles", "pine needles"}),
      "Some fresh and dead pine needles litter the ground.\n");
    add_item(({"fallen trees", "fallen tree", "dead trees",
	"dead tree"}),
      "Some fallen trees lay rotting under a blanket of fallen " +
      "pine needles and forest debris.\n");
    add_item(({"log", "logs", "rotting log", "rotting logs"}),
      "The rotting logs are in various forms of decomposition. " +
      "Some are hollowed out and look to be homes for " +
      "woodland animals.\n");
    add_item(({"forest","silver forest"}),
      "@@set_long");
    add_item(({"ravine"}),"The ravine is covered in undergrowth.\n");
    add_item(({"undergrowth", "underbrush"}),
      "Dense bushes grow under the trees, making travel " +
      "through the forest difficult and obscuring your way.\n");
    add_item(({"outcroppings", "rock outcroppings",
	"rock outcropping", "outcropping"}),
      "These bits of rock protrude from the ground. They are " +
      "weather beaten with a few trees clinging to them, " +
      "trying to grow in the dense forest.\n");
    add_item(({"rays","rays of light","light","ray"}),
      "Rays of light rain down from the canopy of tree " +
      "limbs above.\n");
    add_item(({"hovel", "black hovel"}), "@@hovel_desc");
    add_item(({"roof", "hovel roof"}), "@@hovel_roof_desc");
    add_item(({"chimney", "hovel chimney"}), "@@hovel_chimney_desc");
    add_item(({"smoke"}), "@@hovel_smoke_desc");

    set_up_herbs( ({ ONE_OF_LIST(FOREST_HERBS),
	ONE_OF_LIST(FROST_HERBS),
	ONE_OF_LIST(FOREST_HERBS),
      }),
      ({"trees","bushes","undergrowth",
	"plants","shrub","tree","shrubs","here"}) , random(3) );


    set_tell_time(300 + random(200));
    add_tell("You hear birds chirping off in the distance.\n");
    add_tell("The wind whips through the trees, creating " +
      "an erie howling sound.\n");
    add_tell("Something scurries past in the brush next to you.\n");
    add_tell("The leaves from the trees sway in the icy cold " +
      "breeze.\n");
    add_tell("You catch something furry run from one bush " +
      "to another in the corner of your eye.\n");

    add_cmd_item(({"rocks","rock","pebble","pebbles"}),
      ({"collect","gather","get"}),"@@get_pebble");

    add_cmd_item(({"air","forest","trees","plants"}),
      "smell","@@smell_air");

    add_cmd_item(({"tree"}),({"climb"}),"The tree limbs are too " +
      "high for you to grab making climbing them " +
      "impossible.\n");
    add_cmd_item(({"silver leaves","silver leaf"}),({"pick"}),"You pick one of the " +
      "silver streaked leaves off of one of the trees.\n " +
      "The leaf blows away in the wind.\n");

    add_prop(ROOM_I_INSIDE, 0); // This is an outdoor room

    set_hovel();

    reset_room();

    if (!random(3))
	add_npc(MONSTER + birds[random(sizeof(birds))], 1);

    if (!random(4))
	add_npc(MONSTER + small[random(sizeof(small))], 1);

    if (!random(5))
	add_npc(MONSTER + large[random(sizeof(large))], 1);

    if (!random(10))
	add_npc(NPC + "bandit", 4);
}

int seed = 0;

public string *
query_obvious_exits()
{
    if (objectp(this_player()))
	seed = atoi(OB_NUM(this_player())) + atoi(OB_NUM(this_object()));
    return ::query_obvious_exits();
}

int
exits()
{
    seed++;

    if ((TP->query_skill(SS_LOC_SENSE) + random(20, seed) > 70))
    {
	return 0;
    }
    return 1;
}

// Smell the air, forest, plants
public string
smell_desc()
{
    return "The air smells pine fresh.\n";
}

public int
do_smell(string str)
{
    write(smell_desc());
    return 1;
}

//Forest Objects
public int
get_pebble()
{
    object pebble;

    seteuid(getuid(TO));
    pebble = clone_object(CALATHIN_DIR + "houses/obj/pebble");
    pebble->move(TP);
    write("You sift through the snow finding a pebble, then pick it up.\n");
    say(QCTNAME(TP) + " reaches into the snow and picks up a pebble.\n");
    return 1;
}

public string *
query_moving_object_list()
{
    seteuid(getuid(this_object()));

    switch(random(15))
    {
    case 0 :
	return ({MONSTER + birds[random(sizeof(birds))]});
	break;
    case 1 :
	return ({MONSTER + small[random(sizeof(small))]});
	break;
    case 2 :
	return ({MONSTER + large[random(sizeof(large))]});
	break;
    case 3 :
	return 0;
	break;
    }
}

//added "camp" with a short description

string
short_desc()
{
    if(HAS_HOVEL)
    {
	return "Outside a hovel in the Silver forest";
    }

    switch(short)
    {
    case "middle":
	return "You are in the middle of the Silver forest";
	break;

    case "east":
	return "You are in the eastern area of the Silver forest";
	break;

    case "south":
	return "Southern reaches of the Silver forest";
	break;

    case "north":
	return "Northern reaches of the Silver forest";
	break;

    case "west":
	return "Western area of the Silver forest";
	break;

    case "camp":
	return "A Camp somewhere in the Silver forest";
	break;

    default:
	return "Somewhere within the Silver forest";
	break;
    }
}

string
long_desc()
{
    if(HAS_HOVEL)
    {
	return "There is a black hovel here covered by a deep layer of snow. " +
	"A thick plume of smoke is rising from the chimney, indicating that " +
	"the hovel is occupied.\n";
    }

    switch(long)
    {
    case 0:
	return "Several patches of rocky granite dot the snowfilled " +
	"ground here.\n";
	break;

    case 1:
	return "The snow is very deep here.\n";
	break;

    case 2:
	return "Patches of yellow grass protrude the surface " +
	"of the snowy ground.\n";
	break;

    case 3:
	return "You descend into a sandstone ravine filled with " +
	"frozen scrub brush.\n";
	break;

    case 4:
	return "The trees open up into a small snowy meadow.\n";
	break;

    case 5:
	return "The dense scrub brush claws at your clothing as " +
	"you travel through the forest.\n";
	break;

    case 6:
	return "The forest floor slopes downward here.\n";
	break;

    case 7:
	return "The snow drifts collect at the the tree basin " +
	"looking similiar to waves upon a vast " +
	"ocean of white.\n";
	break;

    case 8:
	return "The silvery leaves from the trees " +
	"provides a soft, silky glow about the " +
	"forest.\n";
	break;

    case 9:
	return "Rocky formations dot the area around " +
	"tree basin.\n";
	break;

    default:
	return "default case long description.\n";
	break;
    }
}

public string
hovel_desc()
{
    NO_HOVEL_DESC;
    return "The hovel has been painted black.\n";
}

public string
hovel_roof_desc()
{
    NO_HOVEL_DESC;
    return "You cannot see it because of all the snow.\n";
}

public string
hovel_chimney_desc()
{
    NO_HOVEL_DESC;
    return "It's an ordinary chimney, but the smoke coming from it " +
    "forms a strange pattern.\n";
}

public string
hovel_smoke_desc()
{
    NO_HOVEL_DESC;

    return "The cloud of smoke forms something that resembles a toad. " +
    "Very strange, indeed!\n";
}

public int
unq_no_move(string str)
{
    string verb = query_verb();
    if (verb == "up" || verb == "down")
        return ::unq_no_move(str);

    notify_fail("The forest is too dense to enter in that direction.\n");
    return 0;
}
