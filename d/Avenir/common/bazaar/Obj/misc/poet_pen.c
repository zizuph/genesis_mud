/*
 * A pen for poets
 *
 * Revisions:
 * 	Lucius, Mar 2018: Convert to /lib/commands + cleanups.
 */
#pragma strict_types

inherit "/std/object";
inherit "/lib/commands";

#include <macros.h>
#include <cmdparse.h>
#include <stdproperties.h>

#define TP  this_player()
#define TO  this_object()

#define SOULDESC(x)  TP->add_prop(LIVE_S_SOULEXTRA, (x))
#define HIS          TP->query_possessive()

#define PEN_ID       "_Avenir_poets_pen"

string colour = "blue";
int type, capacity, break_chance;

void create_object()
{
    set_name(({"pen",PEN_ID}));

    add_prop(OBJ_I_WEIGHT, 25);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 425);
    add_prop(OBJ_M_NO_SELL, "You wouldn't want to sell it.\n");
    add_prop(OBJ_M_NO_GET, VBFC_ME("check_get"));
    add_prop(OBJ_M_NO_BUY, VBFC_ME("check_get"));
}

mixed check_get()
{
    if (present(PEN_ID, TP))
	return "You do not need more than one.\n";

    return 0;
}

void set_colour(string what)
{
    colour = what;
}

string query_colour()
{
    return colour;
}

void set_break_chance(int what)
{
    break_chance = what;
}

int query_break_chance()
{
    return break_chance;
}

void set_capacity(int num)
{
    capacity = num;
}

int query_capacity()
{
    return capacity;
}

void set_type(int which)
{
    type = which;
}

void init_pen()
{
    add_adj(colour);

    switch(type)
    {
    case 0:
	add_name("pen");
	set_short("simple " + colour + " pen");
	add_adj(({"simple", colour}));
	set_long("It is a simple " + colour + "-coloured "
	  + "pen with a small nib at the end that "
	  + "can hold some ink.\n");
	set_break_chance(8);
	set_capacity(2);
	add_prop(OBJ_I_VALUE, 148 + random(20));
	add_prop(OBJ_I_WEIGHT, 100);
	add_prop(OBJ_I_VOLUME, 500);
	break;
    case 1:
	add_name("pen");
	set_short("ornate " + colour + "-feathered pen");
	add_adj(({"ornate", colour, colour + "-feathered", "feathered"}));
	set_long("It is an ornate pen with a tiny steel nip, "
	  + "and expanding into a wide " + colour + " feather.\n");
	set_break_chance(6);
	set_capacity(4);
	add_prop(OBJ_I_VALUE, 280 + random(20));
	add_prop(OBJ_I_WEIGHT, 100);
	add_prop(OBJ_I_VOLUME, 500);
	break;
    case 2:
	add_name("quill");
	set_short("magnificant " + colour + "-plumed quill");
	add_adj(({"magnificant", colour, colour + "-plumed", "plumed"}));
	set_long("It is beautiful piece of craftsmanship, with "
	  + "an elegant tip. The body of the pen turns into "
	  + "an enormous " + colour + " plume at the end, the "
	  + "feather's fine threads shivering with every movement.\n");
	set_break_chance(9);
	set_capacity(10);
	add_prop(OBJ_I_VALUE, 800 + random(100));
	add_prop(OBJ_I_WEIGHT, 200);
	add_prop(OBJ_I_VOLUME, 500);
	break;
    default:
	add_name("stylus");
	set_short("long " + colour + "-steel stylus");
	add_adj(({"long", colour, colour + "-steel", "steel"}));
	set_long("Elegant and simple, this long stylus is constructed "
	  + "from beaten steel dyed " + colour + ". The base curves "
	  + "inwards to form a strong nib.\n");
	set_break_chance(1);
	set_capacity(4);
	add_prop(OBJ_I_VALUE, 1200 + random(100));
	add_prop(OBJ_I_WEIGHT, 600);
	add_prop(OBJ_I_VOLUME, 300);
	break;
    }
}

varargs string short(object for_obj)
{
    return (query_prop(OBJ_I_BROKEN) ? "broken " : "") + ::short(for_obj);
}


void randomize()
{
    string *cols = ({ "red","crimson","purple","white","black",
      "green","blue","golden","cinamon","grey",
      "turquoise","indigo","azure","maroon","brown","violet" });

    set_colour(one_of_list(cols));
    set_type(random(4));
    init_pen();
}

/*
 * Pen emotions
 * To be honest, most of these are just copied straight from
 * /cmd/std/soul_cmd.c
 */
void init()
{
    ::init();
    add_action("phelp",     "help");

    add_action("ppoke",     "ppoke");
    add_action("ppoint",    "ppoint");
    add_action("pscratch",  "pscratch");
    add_action("pstroke",   "pstroke");
    add_action("pswing",    "pswing");
    add_action("pwave",     "pwave");
}

int phelp(string str)
{
    if (!present(TO, TP))
	return 0;

    if (str != "pen")
	return 0;

    write("You can do the following with your " + short() + ":\n"
      + " ppoke            - Poke someone with your pen\n"
      + " ppoint           - Point at someone/something with your pen\n"
      + " pscratch         - Scratch with your pen\n"
      + " pstroke          - Stroke your pen thoghtfully\n"
      + " pswing           - Swing your pen to fend of enemies\n"
      + " pwave            - Wave your pen around threatiningly\n\n");
    return 1;
}


int pwave(string str)
{
    object *oblist;
    string *how;

    if (!present(TO, TP))
	return 0;

    how = parse_adverb_with_space(str, "threatiningly", 0);

    if (!strlen(how[0]))
    {
	write("You wave your " + short() + how[1] + " around in the air.\n");
	allbb(" waves " + HIS + " " + short() + how[1] + " around in the air.");
	SOULDESC("waving " + LANG_ADDART(short()) + " around");
	return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail("Wave your pen [how] at whom?\n");
	return 0;
    }

    actor("You wave your " + short() + how[1] + " at", oblist);
    targetbb(" waves " + HIS + " " + short() + how[1] + " at you.", oblist);
    all2actbb(" waves " + HIS + " " + short() + how[1] + " at", oblist);
    SOULDESC("waving " + LANG_ADDART(short()) + " around");
    return 1;
}

int pswing(string str)
{
    object *oblist;
    string *how;

    if (!present(TO, TP))
	return 0;

    how = parse_adverb_with_space(str, "dangerousley", 0);

    if (!strlen(how[0]))
    {
	write("You swing your " + short() + how[1] + " before you.\n");
	allbb(" waves " + HIS + " " + short() + how[1]
	  + " before " + TP->query_objective() + ".");
	SOULDESC("swinging " + LANG_ADDART(short()) + " around");
	return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail("Swing your pen [how] before who?\n");
	return 0;
    }

    actor("You swing your " + short() + how[1] + " in front of", oblist);
    targetbb(" swings " + HIS + " " + short() + how[1] + " in front of you.", oblist);
    all2actbb(" swings " + HIS + " " + short() + how[1] + " in front of", oblist);
    SOULDESC("swinging " + LANG_ADDART(short()) + " around");
    return 1;
}

int pstroke(string str)
{
    object *oblist;
    string *how;

    if (!present(TO, TP))
	return 0;

    how = parse_adverb_with_space(str, "thoughtfully", 0);

    if (!strlen(how[0]))
    {
	write("You stroke your " + short() + how[1] + ".\n");
	allbb(" strokes " + HIS + " " + short() + how[1] + ".");
	SOULDESC("stroking " + LANG_ADDART(short()) + how[1]);
	return 1;
    }

    notify_fail("Stroke your pen [how]?\n");
    return 0;
}

string *ind_dirs = ({ "up", "down", "north", "south", "west", "east",
    "northwest", "southwest", "northeast", "southeast" });

int ppoint(string str)
{
    object *oblist, knife;
    string *tmp;

    if (!present(TO, TP))
	return 0;

    notify_fail("Where do you want to point with your "+
	short()+"?\n");

    if (!strlen(str))
    {
	write("You wave your "+short()+" in a general direction.\n");
	allbb(" waves "+HIS+" "+short()+" in a general direction.");
	return 1;
    }

    str = lower_case(str);
    if (member_array(str, ind_dirs) >= 0)
    {
	write("You point " + str + " with your "+short()+".\n");
	allbb(" point " + str + " with "+HIS+" "+short()+".");
	return 1;
    }

    if (str == (string) TP->query_real_name() ||
	str == "me" || str == "myself")
    {
	write("You point your "+short()+" at yourself.\n");
	allbb(" points "+HIS+" "+short()+" at "
	  + TP->query_objective() + "self.");
	return 1;
    }

    oblist = parse_this(str, "[at] [the] %l");

    if (!sizeof(oblist))
    {
	tmp = explode(str, " ");
	if (sizeof(tmp) > 1 && tmp[0] == "at")
	    str = implode(tmp[1 .. sizeof(tmp) - 1], " ");

	oblist = FIND_STR_IN_OBJECT(str, environment(TP));
	if (!sizeof(oblist))
	{
	    if (environment(TP)->item_id(str))
	    {
		write("You point at the " + str
		  +" with your "+short()+".\n");
		allbb(" points at " + LANG_ADDART(str) + " with "
		  +HIS+" "+short()+".");
		return 1;
	    }
	    return 0;
	}
	write("You point at " + LANG_THESHORT(oblist[0])
	  +" with your "+short()+".\n");
	allbb(" points at " + LANG_THESHORT(oblist[0])
	  +" with "+HIS+" "+short() + ".");
	return 1;
    }

    targetbb(" points at you with "+HIS+" "+short()+".", oblist);
    actor("You point at", oblist," with your "+short()+".");
    all2actbb(" points at", oblist, " with "+HIS+" "+short()+".");

    return 1;
}

string *p_zones = ({ "eye", "ear", "nose", "thorax", "abdomen",
    "shoulder", "ribs" });

int ppoke(string str)
{
    object *oblist;
    string location;
    string *words;

    if (!present(TO, TP))
	return 0;

    if (!stringp(str))
    {
	notify_fail("Poke whom [where] with your pen?\n");
	return 0;
    }

    oblist = parse_this(str, "[the] %l [in] [the] [eye] [ear] [nose] " +
      "[thorax] [abdomen] [shoulder] [ribs]");

    if (!sizeof(oblist))
    {
	notify_fail("Poke whom [where] with your pen?\n");
	return 0;
    }

    words = explode(str, " ");
    if (member_array(words[sizeof(words) - 1], p_zones) != -1)
	location = words[sizeof(words) - 1];
    else
	location = "abdomen";

    actor("You poke", oblist, " in the " + location
      + " with your " + short() + ".");
    all2act(" pokes", oblist, " in the " + location
      + " with " + HIS + " " + short() + ".");
    target(" pokes you in the " + location
      + " with " + HIS + " " + short() + ".", oblist);

    return 1;
}

string *s_zones = ({ "head", "chin", "back", "behind", "nose" });

int pscratch(string str)
{
    object *oblist;
    string one, two;

    if (!present(TO, TP))
	return 0;


    if (!stringp(str))
	str = "head";

    if (member_array(str, s_zones) != -1)
    {
	write("You scratch your " + str + " thoughtfully with your " + short() + ".\n");
	allbb(" scratches " + this_player()->query_possessive() +
	  " " + str + " thoughtfully with " + HIS + " " + short() + ".");
	return 1;
    }

    notify_fail("Scratch [whom] where with your pen?\n");
    if (sscanf(str, "%s %s", one, two) == 2)
    {
	if (member_array(two, s_zones) == -1)
	    return 0;
    }

    if (!stringp(two))
	two = "head";

    oblist = parse_this(one, "[the] %l [at] [the]");

    if (!sizeof(oblist))
	return 0;

    actor("You scratch", oblist, "'s " + two + " with your " + short() + ".");
    all2act(" scratches", oblist, "'s " + two + " with " + HIS + " " + short() + ".");
    target(" scratches your " + two + " with " + HIS + " " + short() + ".", oblist);
    return 1;
}
