#include <stdproperties.h>
#include "defs.h"

inherit "/d/Shire/common/lib/rom";

static object clock;
static int life;
static mixed *things;

create_rom() {
    clock = find_object("/d/Gondor/common/obj/clock");
    add_prop(ROOM_I_INSIDE, 0);

    /* add_prop(ROOM_I_LIGHT, "@@my_light@@"); */
    add_prop(ROOM_I_LIGHT, 1);

    add_item(({"sky","moon","sun","stars","heaven"}),"@@do_sky@@\n");
    add_item(({"forest"}), "@@exa_forest@@\n");
    add_item(({"trees","tree"}), "@@exa_trees@@\n");
    add_item(({"ground", "soil", "vegetation"}), "@@exa_ground@@\n");
    this_object()->create_forest();
    my_exit_desc_mode = 1;
    create_things();
}

reset_rom() {
    this_object()->reset_forest();
}

/*-----------------------------------------------------------------
 *
 * Special things to happen in the forest.
 *
 */

mixed
pos()
{
    string s1,s2;
    int n,e;

    if (sscanf(file_name(this_object()), "%s/hollin/f%s", s1, s2)==2)
    {
	s1 = s2[0..1];
	s2 = s2[2..3];
	sscanf(s1, "%d", n);
	sscanf(s1, "%d", e);
	return ({ n, e });
    }
    else
	return ({ 100, 100 });
}

int
idno()
{
    mixed r = pos();
    return (r[1]*13+r[0]*17)%27;
}

int
rnd(int s)
{
    return random(s, TO->idno());
}

/*
 * I want to have:
 *   - 1 to 4 climbable trees.
 *   - 1 to 10 other trees.
 *   - 1 to 3 different mushrooms and mosses.
 *   - Bugs and insects.
 *   - Birds singing in the trees/pressing into the soil.
 *   - Stones and pebbles on the ground.
 *   . Sand and possibility to dig in it.
 *   - Special things:
 *       Walking animals.
 *
 * For efficiency, I will not clone anything until referred to.
 * Therefore I will build up an array of strings.
 *
 * Codes:
 *   T <type>   - Tree
 *   H <type>   - Herbs
 *   b <type>   - Bugs
 *   B <type>   - Birds
 *   S <type>   - Stones
 *   G <type>   - Ground
 */

#define MAX_TREES   6
#define NT_TREES    5

#define BUGS_FILES  ({ "ant", "butterfly", "bark_bug", "cockroach" })
#define MAX_BUGS    12
#define NT_BUGS     sizeof(BUGS_FILES)

#define BIRD_FILES  ({ "woodpecker", "owl", "craw", "jay", "nutcracker" })
#define MAX_BIRDS   3
#define NT_BIRDS    sizeof(BIRD_FILES)

#define MAX_HERBS   2
#define NT_HERBS    0

#define MAX_STONES  1
#define NT_STONES   0

#define MAX_GROUND  1
#define NT_GROUND   0

#define STD_TREE    STAND_OBJ + "tree"
#define STD_BUGS    STAND_MONSTER + "bugs"
#define STD_BIRDS   STAND_MONSTER + "birds"

int
type_filter(mixed *what, string type)
{
    return what[0]==type;
}

create_things()
{
    int i,r;

    things = ({});

    r=rnd(MAX_TREES)+1;
    for(i=0;i<r;i++)
	things += ({ ({ "T",rnd(NT_TREES) }) });

/*
    r=rnd(MAX_HERBS)+1;
    for(i=0;i<r;i++)
	things += ({ ({ "H",rnd(NT_HERBS) }) });

    r=rnd(MAX_BUGS)+1;
    for(i=0;i<r;i++)
	things += ({ ({ "b",rnd(NT_BUGS) }) });

    r=rnd(MAX_BIRDS)+1;
    for(i=0;i<r;i++)
	things += ({ ({ "B",rnd(NT_BIRDS) }) });

    r=rnd(MAX_STONES)+1;
    for(i=0;i<r;i++)
	things += ({ ({ "S",rnd(NT_STONES) }) });

    r=rnd(MAX_GROUND)+1;
    for(i=0;i<r;i++)
	things += ({ ({ "G",rnd(NT_GROUND) }) });
*/
}

object
create_tree(int type)
{
    object tree;

    FIXEUID;

    tree = clone_object(STD_TREE);
    if(!tree) return 0;

    tree->create_tree(type, 0);
    tree->move(this_object(),1);
    
    return tree;
}

object
create_bugs(int type)
{
    object bug;

    bug = clone_object(STD_BUGS+BUGS_FILES[type]);
    if(bug) bug->move(this_object());

    return bug;
}

object
create_bird(int type)
{
    object bird;

    bird=clone_object(STD_BIRDS+BIRD_FILES[type]);
    if(bird) bird->move(this_object());

    return bird;
}

object
create_stone(int type)
{
    object stone;

    stone=clone_object(D_OBJ+"stone");
    stone->set_type(type);
    stone->move(this_object());
    return stone;
}

object this_ground;

object
create_ground(int type)
{
    if(!this_ground) {
	this_ground = clone_object(D_OBJ+"ground");
	this_ground ->set_type(type);
	this_ground ->move(this_object());
    }
    return this_ground;
}


string
exa_ground()
{
    return break_string("The ground is right under your feet.",75);
}

string
exa_forest()
{
    return break_string(
	"You are in a gloomy forest in Hollin. Several trees surround you, "+
	"most of them are large while some are smaller and could not be "+
	"climbed except light animals. Birds sing in the trees here usually "+
	"and on the ground you notice that you could find some plants. "+
	"Actually, it looks like it is possible to climb some of "+
	"these trees, well of course, if you know how to climb at "+
	"all that is.. ", 75)+"\n";
}

mixed
exa_trees()
{
    mixed t;
    int i;
    object tree;

    t = filter(things, "type_filter", this_object(), "T");

    if (sizeof(t)==1)
    {
	tree = create_tree(t[0][1]);
	if (tree)
	{
	    remove_item("trees");
	    return tree->long();
	}
	else
	    return "A funny little tree you couldn't know the name of.";
    }
    else if(sizeof(t))
    {
	for(i=0;i<sizeof(t);i++)
	    create_tree(t[i][1]);
	return present("tree")->desc_trees()+"\n";
    }
}

#define EARLY_NIGHT     22..24
#define LATE_NIGHT      0..3
#define EARLY_MORNING   4..7
#define MORNING         8..10
#define NOON            11..13
#define AFTERNOON       14..17
#define EVENING         18..21

do_sky()
{
  int time = clock -> query_hour();
  switch(time) 
  {
    case LATE_NIGHT:
    case EARLY_NIGHT:
      return "It is very dark around you as the leaves of the trees prevent "+
	     "any penetration of light. ";
    case EARLY_MORNING:
      return "It is now starting to get brighter "+
	     "in the east as the day comes. ";
    case MORNING:
      return "The sun rises above the top of the trees, "+
	     "though little light escapes down here. ";
    case NOON:
      return "The sun is now due south now, as it is around noon. ";
    case AFTERNOON:
      return "The sun is lower now than at its zenith, emerging slowly "+
	     "to the east. ";
    case EVENING:
      return "The sun is setting below the horizon, "+
	     "and forest is darker than before. ";
  }
}

int
my_light()
{
    int time = clock->query_hour();
    switch(time) {
	case EARLY_MORNING:
	case MORNING:
	case AFTERNOON:
	    return 1;
	case NOON:
	    return 2;
	default:
	    return 0;
    }
}
