/*
 * - gift_box.c  -=-  Lucius
 *
 * Box sold by porters to use as gift boxes.
 */
#pragma strict_types

inherit "/std/receptacle";

#include <macros.h>
#include <cmdparse.h>
#include <language.h>
#include <stdproperties.h>

public static string size, type, shape, colour, extra;

public static mapping m_types  = ([
      "felt" : ({ 150, "felt, which is a stiff matted fabric made from "+
	  	"local sybarun wool and plant fibres. It is soft-textured "+
	  	"and yet hard to the touch at the same time." }),
     "straw" : ({ 150, "straw fiber, thick bands of which have "+
	 	"been meticulously woven together to form a textured, "+
	 	"checkered surface." }),
    "bamboo" : ({ 300, "flexible bamboo strips, which have been "+
		"painstakingly interwoven into attractive "+
		"diagonal patterns." }),
    "kesoit" : ({ 600, "kesoit wood, which has been thinly planed "+
		"to keep the box light, yet still durable. It has "+
		"eye-fetching random patterns along its surface left "+
		"behind by dried and hardened sap residue." }),
    "banana" : ({ 800, "banana bark covered in dried lily leaves. "+
		"These are imported into sybarus, but the bark provides a"+
		"firm yet light and durable structure while the lily "+
		"leaves are pasted to the surface to give it a unique "+
		"look and feel." }),
]);

public void set_size(string str)	{ size = str;	}
public void set_type(string str)	{ type = str;	}
public void set_shape(string str)	{ shape = str;	}
public void set_colour(string str)	{ colour = str;	}
public void set_extra(string str)	{ extra = str;	}

public void
config_box(void)
{
    int value = 1000;

    switch(size)
    {
    case "small":
	value += 200;
	add_prop(CONT_I_WEIGHT, 100);
	add_prop(CONT_I_VOLUME, 100);
	add_prop(CONT_I_MAX_WEIGHT, 600);
	add_prop(CONT_I_MAX_VOLUME, 600);
	break;
    case "medium":
	value += 400;
	add_prop(CONT_I_WEIGHT, 300);
	add_prop(CONT_I_VOLUME, 300);
	add_prop(CONT_I_MAX_WEIGHT, 2500);
	add_prop(CONT_I_MAX_VOLUME, 2500);
	break;
    case "large":
	value += 600;
	add_prop(CONT_I_WEIGHT, 500);
	add_prop(CONT_I_VOLUME, 500);
	add_prop(CONT_I_MAX_WEIGHT, 3500);
	add_prop(CONT_I_MAX_VOLUME, 3500);
	break;
    }

    value += m_types[type][0];
    add_prop(OBJ_I_VALUE, value);

    set_adj(({ type, colour, shape, size }));
    set_short(colour +" "+ shape +" box");
    set_pshort(colour +" "+ shape +" boxes");

    set_long("This is a "+ size +" "+ shape +" box intended for "+
	"the holding and transport of gifts. This box is "+ 
	(random(2) ? "composed of " : "constructed from ") +
	colour +" coloured "+ m_types[type][1] +
	" The inside is stuffed with a thin, translucent crinkly "+
	"paper to act as padding for whatever gifts might lie "+
	"inside. You may \"discard\" it when no longer wanted. ");
}
  
public void
create_receptacle(void)
{
    set_name("box");
    add_adj(({ "sybarun", "gift" }));

    set_no_pick();

    /* Boxes are rigid. */
    add_prop(CONT_I_RIGID, 1);
    /* These boxes don't reduce volume/weight. */
    add_prop(CONT_I_REDUCE_VOLUME, 100);
    add_prop(CONT_I_REDUCE_WEIGHT, 100);
    /* Not for resale. */
    add_prop(OBJ_M_NO_SELL,
	"There is no market for second-hand gift boxes.\n");

    size = type = shape = colour = extra = "";
}

public varargs string
short(object for_obj)
{
    return container::short(for_obj);
}

public varargs string
plural_short(object for_obj)
{
    return container::plural_short(for_obj);
}

public varargs string
long(string str, object viewer)
{
    string desc = container::long(str, viewer);

    if (strlen(str))
	return desc;

    desc += (query_prop(CONT_I_CLOSED) ?
       	"It is currently lidded." :
	"It is currently unlidded.");

    if (strlen(extra))
    {
	desc += " Attached is a foil embossed card, "+
	    "which reads:\n"+ extra;
    } else {
	desc += "\n";
    }

    return desc;
}

public nomask int
avenir_gift_box(void)		{ return 1; }

public mixed
discard_box(void)
{
    if (sizeof(all_inventory(this_object())))
	return "You should empty the "+ short() +" first!\n";
    
    write("You smoosh and scrunch your "+ short() +
	", collapsing it into a mangled wad " +
	"and jettisoning it.\n");
    say(QCTNAME(this_player()) +" smooshes and scrunches "+
	LANG_ASHORT(this_object()) +" collapsing it into "+
	"a mangled wad and jetisoning it.\n");

    set_alarm(0.0, 0.0, remove_object);
    return 1;
}

public int
parse_me(string str)
{
    if (!strlen(str))
    {
	notify_fail(capitalize(query_verb()) +" what?\n");
	return 0;
    }

    object *obs = filter(all_inventory(this_player()),
	    &->avenir_gift_box());

    if (!sizeof(obs = FIND_STR_IN_ARR(lower_case(str), obs)))
    {
	notify_fail(capitalize(query_verb()) +" what?\n");
	return 0;
    }

    mixed *res = map(obs, &->discard_box());
    string *fail = filter(res, strlen);

    /* Only print failures if all failed. */
    if (sizeof(fail) == sizeof(res))
	write(implode(fail, ""));

    return 1;
}

public void
init(void)
{
    ::init();

    if (this_player() != environment())
	return;

    add_action(parse_me, "discard");
}
