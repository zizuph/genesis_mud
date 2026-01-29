inherit "/std/object";

#include <stdproperties.h>
#include <composite.h>
#include "defs.h"

/* Ideas: Lime (linden), pine, oak, cedar, ash, apple tree,
	  cherry tree, chestnut, maple, sycamore,
	  beech, rowan, birch, larch, spine,
	  spruce, alder. */

/* name, hits, diameter[cm], height[cm], diff */

#define TREE_MAP\
([  0: ({ "oak",    7200, 500, 5000, 500, 200 }),\
    1: ({ "willow", 3400, 300, 2000, 400, 150 }),\
    2: ({ "aspen",  2500,  50, 1000, 600,  80 }),\
    3: ({ "birch",  1250,  40, 1000, 200,  40 }),\
    4: ({ "maple",  2310,  90, 4000, 300, 100 }),\
])

#define TEMP_CHECKED_TREES "_temp_checked_trees"

#define TNAME 0
#define HITS 1
#define DIAM 2
#define HEIGHT 3
#define DIFF 4
#define LIFE 5
#define AGE  5

//   Prototypes
void remove_temp_checked_trees(object who);

int tree_type;
int hp;
int diam;
int height;
int diff;
int age;
int alarm_id;

create_object()
{
    this_object()->create_tree(1,0);
    set_no_show_composite(1);
}

int is_tree() { return 1; }

string
age_string(int age)
{
    switch(age) {
	case 0..10:  return "very young";
	case 11..20: return "young";
	case 21..50: return "mature";
	case 51..75: return "old";
	case 76..90: return "very old";
	default:     return "ancient";
    }
}

string
height_string(int h)
{
    switch(h) {
	case	0.. 100: return "very small";
	case  101.. 400: return "small";
	case  401.. 800: return "normal";
	case  801..1200: return "tall";
	case 1201..2000: return "quite tall";
	case 2001..4000: return "very tall";
	case 4001..6000: return "incredibly tall";
	default:	 return "dazzlingly tall";
    }
}

string
diam_string(int d)
{
    switch(d) {
	case   0.. 10: return "very thin";
	case  11.. 30: return "quite thin";
	case  31.. 50: return "thin";
	case  51..100: return "quite thick";
	case 101..150: return "rather thick";
	case 151..300: return "very thick";
	default      : return "exceptionally thick";
    }
}


create_tree(int type, int seed)
{
    mixed *data=TREE_MAP[type];

    tree_type = type;

    age = (random(1000)+random(1000)+random(1000))/30+1; /*1-100*/
    age = age * data[LIFE] / 100;

    height = age*data[HEIGHT]/100;
    diam   = age*data[DIAM]/100;
    diff   = age*data[DIFF]/100;
    hp	   = age*data[HITS]/100;

    set_name("tree");
    set_pname("trees");

    add_adj(data[TNAME]);
    add_adj(explode(height_string(height)," "));
    add_adj(explode(diam_string(diam)," "));
    add_adj(explode(age_string(age)," "));

    set_short(data[TNAME]+" tree");
    set_pshort(data[TNAME]+" trees");

    add_prop(OBJ_I_WEIGHT, height/10*diam/20*diam/20*3 * 1000);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/3);

    set_long(
	"This is a "+height_string(height)+" "+data[TNAME]+" tree. It seems "+
	age_string(age)+" and "+diam_string(age)+".\n"
    );
}

int
filter_tree(object ob)
{
    return objectp(ob) && ob->is_tree();
}

void
enter_env(object dest, object old)
{
    dest->add_my_desc("@@desc_trees:"+file_name(TO)+"@@ ");
    ::enter_env(dest, old);
}

void
leave_env(object from, object dest)
{
    from->remove_my_desc();
}

string
desc_trees()
{
    object *trees;
    string str;

    if (TP->query_prop(TEMP_CHECKED_TREES))
	return "";

    TP->add_prop(TEMP_CHECKED_TREES, 1);

    trees = all_inventory(ENV(TO));
    trees = filter(trees, "filter_tree", TO);

    alarm_id = set_alarm(2.0,0.0,"remove_temp_checked_trees(TP)");

    if (!sizeof(trees))
	return "You can see that there are some trees here.";

    trees->set_no_show_composite(0);

    str = "There are some interesting trees here. ";

    switch (random(5))
    {
	case 0:
	    str += "You notice " + COMPOSITE_DEAD(trees) + ".";
	    break;
	case 1:
	    str += "You can see " + COMPOSITE_DEAD(trees) +
		   " stretch their bows into the sky.";
	    break;
	case 2:
	    str += CAP(COMPOSITE_DEAD(trees)) + " darkens the sky above.";
	    break;
	case 3:
	    str += "Some of them are easier distinguished from the rest, "
		 + "for instance " + COMPOSITE_DEAD(trees) + ".";
	    break;
	case 4:
	    str += "Of these, " + COMPOSITE_DEAD(trees) + " looks climbable.";
	    break;
    }

    trees->set_no_show_composite(1);

    return str;
}

void
remove_temp_checked_trees(object who)
{
    remove_alarm(alarm_id);
    who->remove_prop(TEMP_CHECKED_TREES);
}
