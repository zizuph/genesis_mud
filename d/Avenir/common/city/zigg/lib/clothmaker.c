/*
 *  file name:   clothmaker.c
 *  creator:     Zielia & Lucius
 *  last update:
 *  purpose:	 Object to generate random clothing for npc's.
 *  note(s):
 *  bug(s):
 *  to-do:
 */
#pragma no_clone
#pragma no_shadow
#pragma no_inherit
#pragma strict_types


/* Village clothing objects. */
#define VCLOTH(X)  ("/d/Avenir/common/village/obj/custom_" + (X))
/* Bazaar clothing objects.  */
#define BCLOTH(X)  ("/d/Avenir/common/bazaar/Obj/worn/men" + (X))


/*  Female Items.  item[0] = styles; item[1] = fabrics;  */

/* cambric chamois flannel homespun lace linen leather muslin
 * samite satin silk suede tartan tweed velvet webcloth 
 * wooden wool    */

private static string *f_wrap = ({
    ({ "shawl", "wrap", }),
    ({ "lace", "muslin", "samite", "satin", "silk", "tartan",
	"velvet", "webcloth", }),
});

private static string *f_furs = ({
    ({ "boa", "stole", }),
    ({ "ermine", "fox", "lynx", "mink", "sable", "wolf", }),
});

private static string *f_gloves = ({
    ({ "gloves", }),
    ({ "lace", "leather", "satin" ,"silk", "webcloth" }),
    ({ "short", "long", "none", }),
});

private static string *f_dress = ({
    ({ "caftan", "chemise", "dress", "frock", "shift", }),
    ({ "cambric", "linen", "muslin", "samite", "satin", "silk",
	"velvet", "webcloth", }),
});

private static string *f_slippers = ({
    ({ "slippers", "heels", }),
    ({ "chamois", "satin", "silk", "suede", "velvet", }),
});

private static string *f_shirt = ({
    ({ "blouse", "bodice", "cholie", "shirt", }),
    ({ "cambric", "linen", "lace", "muslin", "samite", "satin", "silk",
	"velvet", "webcloth", }),
});

private static string *f_pants = ({
    ({ "harem", "pants", "slacks", "trousers", }),
    ({ "cambric", "chamois", "linen", "leather", "muslin", "silk", "suede",
	"tweed", "velvet", "webcloth", }),
});

private static string *f_shoes = ({
    ({ "sandals", "shoes", }),
    ({ "chamois", "leather", "suede", }),
});

/*  Male Items.  item[0] = styles; item[1] = fabrics;  */

#if 0
/* No village shirts for men. */
private static string *m_shirt = ({
    ({ "tunic", "shirt", }),
    ({ "cambric", "flannel", "homespun", "linen", "muslin", "samite", "silk",
	"tartan", "webcloth", }),
});
#else
/* Bazaar shirts for men. */
private static string *m_shirt = ({
    ({ "blouse", "shirt", }),
    ({ "chamois", "linen", "samite", "satin", "silk", "velvet",
	"webcloth", "wool", }),
});
#endif

private static string *m_pants = ({
    ({ "pants", "slacks", "trousers", }),
    ({ "cambric", "chamois", "flannel", "homespun", "leather", "muslin",
	"samite", "silk", "suede", "tartan", "tweed", "webcloth", }),
});

private static string *m_shoes = ({
    ({ "shoes", "boots", "loafers", }),
    ({ "leather", "suede", }),
});

private static string *m_vest = ({
    ({ "vest", "singlet", "waist-coat", }),
    ({ "cambric", "chamois", "flannel", "homespun", "muslin",
	"samite", "silk", "tartan", "webcloth", }),
});

private static string *m_jacket = ({
    ({ "jacket", "coat", }),
    ({ "beaver", "ermine", "fox", "lamb", "lynx", "mink", "rabbit",
	"sable", "weasel", "wolf", }),
});

private static string *m_gloves = ({
    ({ "gloves", }),
    ({ "leather", "satin" ,"silk", "suede", "webcloth" }),
    ({ "none", }),
});

private static string *m_tie = ({
    ({ "ascot", "scarf", }),
    ({ "samite", "satin", "silk", "tartan", "webcloth", }),
});

/*  Colour Sets.  colours["set"] = ({ "colours" });  */
/*
 * ({ "black", "charcoal", "gray", "silvery",  "white",
 *    "cream", "ivory", "beige", "golden", "yellow", "saffron", 
 *    "amber", "chartreuse", "green", "emerald", "viridian",
 *    "olive", "khaki", "jade", "aquamarine", "teal", "blue",
 *    "azure", "cerulean", "sapphire", "turquoise", "indigo",
 *    "orange", "apricot", "coral", "peach", "pink", "fuschia",
 *    "scarlet", "rose", "red", "blood-red", "burgundy", "cerise",
 *    "crimson", "ruby", "magenta", "maroon", "russet", "vermillion",
 *    "purple", "amethyst", "lavender", "lilac", "mauve", "plum",
 *    "violet", "brown", "coppery", "chocolate", "mahogany", "ochre", 
 *    "tan", "umbre" });
 */
private static mapping colours = ([
    "warm"   : ({
	"yellow", "amber", "saffron", "tan", "brown", "ochre", "cream",
	"beige", "umbre",
    }),
    "cool"   : ({
	"blue", "violet", "plum", "amethyst", "azure", "teal", "turquoise",
	"indigo", "aquamarine",
    }),
    "fire"   : ({
	"coral", "crimson", "cerise", "burgundy", "vermillion", "scarlet",
	"red", "maroon", "black",
    }),
    "nature" : ({
	"jade", "chartreuse", "olive", "emerald", "green", "white", "ivory",
    }),
    "flesh"  : ({
	"cream", "beige", "tan", "apricot", "peach", "russet", "ochre",
	"coppery",
    }),
    "girly"   : ({
	"cream", "apricot", "peach", "pink", "fuschia", "rose", "purple",
	"amethyst", "lavender", "lilac", "white",
    }),
    "bright"  : ({
	"cream", "ivory", "golden", "yellow", "saffron", "amber", "orange",
	"silvery",
    }),
    "dark"    : ({
	"ebony", "silvery", "grey",
    }),
]);

private static string *csets = m_indexes(colours), cset;

/*
 * Assign a named or random colour-set to be the current
 * choice for colour selections.
 */
public void
set_cset(string str)
{
    if (pointerp(colours[str]))
	cset = str;
    else
	cset = one_of_list(csets);
}

/* Returns the currently assigned colour-set. */
public string
query_cset(void)	{ return cset; }

/*
 * Make a clothing item.
 *
 * string what  ==  article of clothing to make.
 *    int girl  ==  what gender to make it for.
 */
public object
make_item(string what, int girl)
{
    object item;

    if (!strlen(what))
	return 0;

    what = lower_case(what);
    girl = (girl == 1 ?: 0);

    switch(what)
    {
    /* girl only items */
    case "dress":
	item = clone_object(VCLOTH("dress"));
	item->set_style(one_of_list(f_dress[0]));
	item->set_fabric(one_of_list(f_dress[1]));
	break;
    case "wrap":
	item = clone_object(VCLOTH("shawl"));
	item->set_style(one_of_list(f_wrap[0]));
	item->set_fabric(one_of_list(f_wrap[1]));
	break;
    case "fur":
	item = clone_object(VCLOTH("fur"));
	item->set_fur(one_of_list(f_furs[1]));
	item->set_style(one_of_list(f_furs[0]));
	break;
    case "slippers":
	item = clone_object(VCLOTH("shoes"));
	item->set_style(one_of_list(f_slippers[0]));
	item->set_fabric(one_of_list(f_slippers[1]));
	break;
    /* boy only items */
    case "tie":
	item = clone_object(VCLOTH("neck"));
	item->set_style(one_of_list(m_tie[0]));
	item->set_fabric(one_of_list(m_tie[1]));
	break;
    case "vest":
	item = clone_object(VCLOTH("vest"));
	item->set_style(one_of_list(m_vest[0]));
	item->set_fabric(one_of_list(m_vest[1]));
	break;
    case "jacket":
	item = clone_object(VCLOTH("fur"));
	item->set_fur(one_of_list(m_jacket[1]));
	item->set_style(one_of_list(m_jacket[0]));
	break;
    /* mixed gender items */
    case "shirt":
	if (girl)
	{
	    item = clone_object(VCLOTH("cholie"));
	    item->set_style(one_of_list(f_shirt[0]));
	    item->set_fabric(one_of_list(f_shirt[1]));
	}
	else
	{
	    item = clone_object(BCLOTH("shirts"));
	    item->set_style("shirts");
	    item->set_substyle(one_of_list(m_shirt[0]));
	    item->set_type(one_of_list(m_shirt[1]));
	}
	break;
    case "pants":
	item = clone_object(VCLOTH("pants"));
	if (girl)
	{
	    item->set_style(one_of_list(f_pants[0]));
	    item->set_fabric(one_of_list(f_pants[1]));
	}
	else
	{
	    item->set_style(one_of_list(m_pants[0]));
	    item->set_fabric(one_of_list(m_pants[1]));
	}
	break;
    case "shoes":
	item = clone_object(VCLOTH("shoes"));
	if (girl)
	{
	    item->set_style(one_of_list(f_shoes[0]));
	    item->set_fabric(one_of_list(f_shoes[1]));
	}
	else
	{
	    item->set_style(one_of_list(m_shoes[0]));
	    item->set_fabric(one_of_list(m_shoes[1]));
	}
	break;
    case "gloves":
	item = clone_object(VCLOTH("gloves"));
	if (girl)
	{
	    item->set_size(one_of_list(f_gloves[2]));
	    item->set_style(one_of_list(f_gloves[0]));
	    item->set_fabric(one_of_list(f_gloves[1]));
	}
	else
	{
	    item->set_size(one_of_list(m_gloves[2]));
	    item->set_style(one_of_list(m_gloves[0]));
	    item->set_fabric(one_of_list(m_gloves[1]));
	}
	break;
    default:
	return 0;
	break;
    }

    if (!strlen(cset))
	set_cset("random");

    item->set_desc("none");
    item->set_colour(one_of_list(colours[cset]));

    /* Finalize item. */
    item->create_tailored();

    return item;
}

/* Boys only have one option, so ignore 'flag' */
public varargs void
make_boy(object who, int flag)
{
    if (!objectp(who))
	return;

    if (!strlen(cset))
	set_cset("random");

    make_item("shoes", 0)->move(who);
    make_item("pants", 0)->move(who);
    make_item("shirt", 0)->move(who);

    if (!random(3))
	make_item("vest", 0)->move(who);

    if (!random(3))
    {
	make_item("jacket", 0)->move(who);

	if (random(2))
	    make_item("gloves", 0)->move(who);
    }

    cset = 0;
}

/* Use flag to choose between plain & dress */
public varargs void
make_girl(object who, int flag)
{
    if (!objectp(who))
	return;

    if (!strlen(cset))
	set_cset("random");

    if (flag == -1)
	flag = random(2);

    if (flag)
    {
	make_item("dress", 1)->move(who);
	make_item("slippers", 1)->move(who);

	if (!random(3))
	    make_item("gloves", 1)->move(who);

	if (!random(3))
	    make_item("wrap", 1)->move(who);
	else if (!random(3))
	    make_item("fur", 1)->move(who);
    }
    else
    {
	make_item("shoes", 1)->move(who);
	make_item("pants", 1)->move(who);
	make_item("shirt", 1)->move(who);

	if (!random(3))
	    make_item("wrap", 1)->move(who);
    }

    cset = 0;
}

public object
get_this_object(void)	{ return this_object(); }

static void
create(void)
{
    setuid();
    seteuid(getuid());
}
