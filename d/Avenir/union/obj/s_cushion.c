// -*-C++-*-
// file name: 	  /d/Avenir/union/obj/cushion
// creator(s):	  Lilith Feb 2004
/*
 * Revisions:
 *   Lucius, Jun 2016:  Code cleanup and refactored.
 *                      Added seating shadow from Ziggurat.
 *   Lilith, May 2022: removed 'relax' as an option because of issue 
 *                     with 's' v 'es'. Added more verb options.
 *
 */
#pragma strict_types
#include "../defs.h"

#include <macros.h>
#include <language.h>
#include <composite.h>
#include <stdproperties.h>

inherit "/std/object";
inherit "/lib/keep";

#define SS_SHADOW    (ZIGG + "lib/seat_shadow")

private int no_deny;
private string style, colour;

private mapping style_desc = ([
  "samite"   : ({ "samite", "This samite cloth is com"+
    "posed of very heavy silk fibers interwov"+
    "en with strands of silver." }),
  "satin"    : ({ "satin", "This is an example of perfect, "+
    "glossy satin made with painstakingly-woven "+
    "silken threads." }),
  "silk"     : ({ "silk", "The luxury of silk is unsurpas"+
    "sed by any other fabric. This particular "+
    "cloth is of the highest-quality weave, making "+
    "it both lustrous and durable." }),
  "suede"    : ({ "suede", "The suede is made from kid "+
    "leather of the highest quality that has "+
    "been carefully abraded so as to raise a "+
    "fine, soft nap on the material." }),
  "velvet"   : ({ "velvet", "This velvet is very plush, "+
    "and so carefully woven that you are unable "+
    "to see the individual loops of silk which "+
    "form the soft, slightly napped surface." }),
  "webcloth" : ({ "webcloth", "The webcloth material has "+
    "the appearance and lightness of silk, but "+
    "is very strong and resistant to tearing. "+
    "It is known to be an extremely rare and "+
    "thus rather expensive material." }),
]);

private string *styles  = ({
    "samite", "satin", "silk", "suede", "velvet", "webcloth",
});

private string *colours = ({
    "black", "ebony", "charcoal", "gray",
    "silvery",  "white", "cream", "ivory",
    "beige", "ecru", "golden", "yellow", "tawny", "saffron",
    "amber", "chartreuse", "green", "emerald", "viridian", "olive",
    "khaki", "jade", "aquamarine", "teal", "blue", "azure",
    "cerulean", "sapphire", "turquoise", "indigo", "orange",
    "apricot", "coral", "peach", "pink", "fuschia", "scarlet",
    "rose", "red", "blood-red", "burgundy", "cerise", "crimson", "ruby",
    "magenta", "maroon", "russet", "vermillion", "purple", "amethyst",
    "lavender", "lilac", "mauve", "plum", "violet", "brown",
    "coppery", "chocolate", "fawn", "mahogany", "ochre",
    "sable", "sepia", "tan", "umbre",
});

private mapping cmds = ([
     "balance" : "balanced",
    "daydream" : "daydreaming",
        "doze" : "dozing",
      "drowse" : "drowsing",
        "flop" : "flopped",
       "kneel" : "kneeling",
        "lean" : "leaning",
      "lounge" : "lounging",
        "loll" : "lolling",
    "meditate" : "meditating",
         "nap" : "napping",
        "plop" : "plopped",
        "pray" : "praying",
        "pose" : "posed",
//     "relax" : "relaxing",  plural show as 'relaxs'
     "recline" : "reclining",
        "rest" : "resting",
         "sag" : "sagged",
      "settle" : "settled",
         "sit" : "sitting",
       "slump" : "slumped",
      "sprawl" : "sprawling",
      "squat"  : "squatting",
]);


public void set_style(string str)    { style = str;   }
public string query_style(void)      { return style;  }
public void set_colour(string str)   { colour = str;  }
public string query_colour(void)     { return colour; }


public string
f_help(void)
{
    string str = "You can '<verb> on cushion', where the verbs are:\n"+
	"   "+ COMPOSITE_WORDS_WITH(sort_array(m_indexes(cmds)), ",") + "\n";

    if (environment() == TP)
	return str;

    return "You must get this cushion before you can do "+
	"anything with it.\n"+ str;
}

public string
short_desc(void)
{
    return query_colour() +" "+ query_style() +" cushion";
}

public string
long_desc(void)
{
    return "This "+ short() +" is designed for seating. It is the "+
	"perfect combination of firmness and softness. For "+
	"instructions on how to use this cushion, try "+
	"<help cushion>.\n";
}

public void
create_custom(void)
{
    set_colour(colour);
    set_style(style);
    set_adj(({ colour, style, "union" }));

    set_short(short_desc);
    set_long(long_desc);

    add_item(style, style_desc[style][1] +"\n");
}

public void
create_object(void)
{
    reset_euid();
    set_keep(1);

    set_name(({"cushion", "pillow", "_union_cushion"}));
    set_pname(({"pile of cushions", "pile of pillows"}));

    add_prop(OBJ_I_WEIGHT, 200 + random(200));
    add_prop(OBJ_I_VOLUME, 400 + random(100));
    add_prop(OBJ_I_VALUE,  200 + random(50));
    add_prop(OBJ_M_NO_SELL, "It is of purely sentimental value.\n");

    add_item(({"stitching", "stitches"}),
	"They are good, regular stitches.\n");

    add_cmd_item("cushion", "help", f_help);
}

public void
make_random(void)
{
    colour = one_of_list(colours);
    style = one_of_list(styles);
    create_custom();
}

public string
show_subloc(string subloc, object me, object for_obj)
{
    string str = "";

    if (me->query_prop("_temp_subloc_show_only_things"))
	return "";

    if (subloc != "av_cushion_subloc")
	return me->show_subloc(subloc, me, for_obj);

    if (me->query_prop(LIVE_S_EXTRA_SHORT))
    {
	if (for_obj == me)
	    str = "You are very comfortable on your "+ short() +".\n";
    }

    return str;
}

public void
leave_env(object from, object to)
{
    if (living(from))
    {
	from->remove_subloc("av_cushion_subloc");
	from->remove_prop(LIVE_S_EXTRA_SHORT);
	from->remove_prop("i_am_sitting_on_a_bench");
    }

    ::leave_env(from, to);
}

public void
enter_env(object to, object from)
{
    if (living(to))
	set_no_show_composite(0);

    ::enter_env(to, from);
}

static void
add_seat_shadow(object who)
{
    object ob = clone_object(SS_SHADOW);
    ob->set_seating_ob(TO);
    if (!ob->shadow_me(who))
        ob->remove_object();
}

static void
rem_seat_shadow(object who)
{
    who->remove_seating_shadow();
}

public int
do_sit(string str)
{
    string verb = query_verb();

    if (environment(TO) != TP)
    {
	notify_fail("You should get it, first.\n", 0);
	return 0;
    }

    if (!strlen(str))
    {
	notify_fail(capitalize(verb) + " on what?\n", 0);
	return 0;
    }

    if (!parse_command(str, ({ }), "'on' [the] %s", str))
    {
	notify_fail(capitalize(verb) + " on what?\n", 0);
	return 0;
    }

    write("You "+ verb +" on the "+ short() +", "+
      "finding it very comfortable indeed.\n");
    say(QCTNAME(TP) +" "+ verb +"s on "+ HIS(TP) +
	" "+ short() +".\n");

    TP->add_prop("i_am_sitting_on_a_bench", 1);
    TP->add_prop(LIVE_S_EXTRA_SHORT, " is "+ cmds[verb] +
      " on "+ HIS(TP) +" "+ short());
    TP->add_subloc("av_cushion_subloc", TO);

    add_seat_shadow(TP);
    return 1;
}

public nomask void
do_not_deny(void)
{
    if (no_deny)
	no_deny = 0;
    else
	no_deny = set_alarm(0.5, 0.0, do_not_deny);
}

public int
deny_stand(void)
{
    return 0;
}

public int
do_stand(string str)
{
    if (environment(TO) != TP)
    {
	notify_fail("You should get it, first.\n");
	return 0;
    }

    if (!TP->query_prop("i_am_sitting_on_a_bench"))
    {
	write("You are not seated.\n");
	return 1;
    }

    /* Possibly deny the stand attempt. */
    if (!no_deny && deny_stand())
	return 2;

    TP->remove_prop(LIVE_S_EXTRA_SHORT);
    TP->remove_prop("i_am_sitting_on_a_bench");
    TP->remove_subloc("av_cushion_subloc");

    write("You stand up from the "+ short() +
      ", feeling quite rested.\n");
    say(QCTNAME(TP) +" gets up from "+ HIS(TP) +
	" "+ short() +".\n");

    /* If called by the shadow, let it remove itself safely. */
    if (TP->query_seating_shadow() != calling_object(0))
	rem_seat_shadow(TP);

    return 1;
}

public void
init_arg(string arg)
{
    sscanf(arg, "#STYLE#%s#COLOUR#%s#NONE#", style, colour);
    create_custom();
}

public mixed
query_auto_load(void)
{
    if (random(4) == 3)
	return 0;

    /* if it is going to auto-load, don't drop it when quitting */
    add_prop(OBJ_M_NO_DROP, 1);
    set_alarm(1.0, 0.0, &remove_prop(OBJ_M_NO_DROP));

    return MASTER + ":#STYLE#"  + style +
	"#COLOUR#" + colour + "#NONE#";
}

public int
do_nothing(string str)
{
    if (environment() != TP)
	return 0;

    if (!TP->query_prop("i_am_sitting_on_a_bench"))
	return 0;

    write("You must stand up from the cushion before you can do that.\n");
    return 1;
}

public void
init(void)
{
    ::init();

    foreach(string cmd: m_indexes(cmds))
	add_action(do_sit, cmd);

    add_action(do_stand, "rise");
    add_action(do_stand, "stand");
}

public void
remove_object(void)
{
    object whom = environment();

    no_deny = 1;
    whom->catch_tell("As the "+ short() +" disappears, you stand up.\n");
    rem_seat_shadow(whom);
    ::remove_object();
}

