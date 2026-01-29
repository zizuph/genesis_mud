#pragma strict_types
// file name:   rods.c
// creator(s):  Zielia & Lucius
// last update:
// purpose:
// note: Should there be a gender check for bosom etc?
//	Should all the risque omes be part of the random places or
//	would it be better to just have one place be default?
//	How about a trace/caress emote?  
// bug(s):
// to-do:
/*
 * http://www.smartspanking.com/implements.html
 * http://spankingartwiki.animeotk.com/wiki/Implement
 * http://en.wikipedia.org/wiki/Birching
 * http://en.wikipedia.org/wiki/Switch_%28rod%29
 * http://en.wikipedia.org/wiki/Flagellation
 * http://en.wikipedia.org/wiki/Erotic_spanking
 * http://en.wikipedia.org/wiki/Impact_play
 */
inherit "/std/weapon";
inherit "/lib/commands";
inherit "/lib/keep";

#include "zigg.h"

#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <adverbs.h>
#include <macros.h>

#define HIT 15
#define PEN 15

/* Various ways to invoke us. */
private static string *cmds = sort_array(({
	"rflail", "rflog", "rswat", "rspank", "rsmack",
	"rpaddle", "rswitch",
}));
/* "ing" form of each invokable verb. */
private static mapping cmding = ([
	"flail" : "flailing", "swat" : "swatting",
	"flog" : "flogging", "spank" : "spanking",
	"smack" : "smacking", "paddle" : "paddling",
	"switch" : "switching",
]);
/* Different types of rods. */
private static mapping descs = ([
    "switch" : ([    /* Class / Name */
	"wooden": ({ /* Sub-class */
	    ({ "rod" }),  /* Other names. */
	    ({ "hazel", "hickory", "birch", "willow", }), /* 2nd adj */
	    ({ "long", "thin", "flexible", "supple", }),  /* 1st adj */
	    "This switch is a straight, slender rod cut from a tree. "+
	    "It differs from a stick in the respect that it is thinner "+
	    "and more flexible. Leaves and branches have been trimmed, "+
	    "the bark peeled and the entire length sanded smooth. Supple "+
	    "strength is achieved from being soaked in brine for a few "+
	    "hours then having a sealant applied. This makes the switch "+
	    "useful for both heavy and light usage.",   /* Long desc. */
	}),
	"leather": ({
	    ({ "rod" }),
	    ({ "leather", }),
	    ({ "black", "red", "violet", }),
	    "This switch is a straight, slender steel rod sheathed "+
	    "in leather. The spring steel core is lightweight and flexible "+
	    "with several layers of soft leather tightly wrapped "+
	    "around it then then capped and sewn closed. A thicker hide "+
	    "is wrapped around one end to form a handle. This careful "+
	    "construction allows for vigorous usage without causing undo "+
	    "damage, either to itself or to the recipient.",
	}),
    ]),
    "crop" : ([
	"leather": ({
	    ({ "rod", }),
	    ({ "leather", }),
	    ({ "flexible", "supple", }),
	    "This crop is a straight, slender steel rod sheathed "+
	    "in leather. The spring steel core is lightweight and flexible "+
	    "with several layers of soft leather tightly wrapped "+
	    "around it then then capped and sewn closed. A thicker hide "+
	    "is wrapped around one end to form a handle. At the other is "+
	    "a rectangular tongue of stiffer rawhide. Crops are short, "+
	    "giving them greater control than a switch, and when used "+
	    "upon humanoids, the tongue is often used for precision "+
	    "targetting of sensitive areas. Its larger surface allows "+
	    "for greater coverage and also a spreading out of the blow "+
	    "so as to reduce the overall effect from being too painful.",
	}),
    ]),
    "rod" : ([
	"wooden": ({
	    ({ "switch" }),
	    ({ "hazel", "birch", "willow", }),
	    ({ "thick", "strong", }),
	    "This rod is a collection of twigs bound together at one "+
	    "end with string, cloth or both to produce a grippable "+
	    "whipping instrument. The twigs are first dried out and then "+
	    "soaked in a brine solution before being gathered together. "+
	    "This gives them longevity and strength while remaining "+
	    "lightweight.",
	}),
    ]),
    "martinet" : ([
	"leather": ({
	    ({ "flogger" }),
	    ({ "leather", "suede", }),
	    ({ "short", }),
	    "This is a short, multi-tailed whip also known as a flogger. "+
	    "The thongs, or falls, are composed of many thin strips of "+
	    "soft leather or suede which are enclosed on one end by a "+
	    "wooden handle. The handle is designed to be held by a single "+
	    "hand and is round and smooth, often with a protuberance at "+
	    "both ends to keep slippage during use to a minimum. This "+
	    "design excells at producing minimum damage no matter how "+
	    "rough the usage.",
	}),
    ]),
]);

#define ADJ1	descs[which][type][2]
#define ADJ2	descs[which][type][1]
#define LONG	descs[which][type][3]
#define NAMES	descs[which][type][0]

private static string adj1, adj2, which, type;

private void
config_rod(string w, string t, string a1, string a2)
{
    if (strlen(which))
    {
	remove_adj(ADJ1);
	remove_adj(ADJ2);
	remove_name(which);
	remove_name(NAMES);
    }

    type = t;
    which = w;

    set_name(which);
    add_name(NAMES);
    set_long(LONG +" You get a sense that the word \"rhelp\" "+
	"would be invaluable to you.\n");

    adj1 = (strlen(a1) ? a1 : one_of_list(ADJ1));
    adj2 = (strlen(a2) ? a2 : one_of_list(ADJ2));

    set_adj(({ adj1, adj2 }));
    set_short(adj1 +" "+ adj2 +" "+ which);
    set_pshort(adj1 +" "+ adj2 +" "+ LANG_PWORD(which));
}

/* Bypass update_prop_settings */
private void
my_props(void)
{
    add_prop(OBJ_I_VALUE,
	F_VALUE_WEAPON(random(HIT * 3), random(PEN * 3)) * 3);

    add_prop(OBJ_I_WEIGHT,
	F_WEIGHT_DEFAULT_WEAPON(random(PEN + HIT), W_CLUB) / 3);

    add_prop(OBJ_I_VOLUME,
	query_prop(OBJ_I_WEIGHT) / 2);
}

public void
create_weapon(void)
{
    if (!IS_CLONE)
	return;

    setuid();
    seteuid(getuid());

    set_keep(1);
    set_hit(HIT);
    set_pen(PEN);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);
    set_wf(this_object());

    string w = one_of_list(m_indexes(descs));
    string t = one_of_list(m_indexes(descs[w]));

    set_alarm(0.1, 0.0, my_props);
    config_rod(w, t, "", "");
}

public int
wield(object what)
{
    write("You grip the "+ short() +" firmly.\n");
    say(QCTNAME(TP) +" firmly grips "+ HIS(TP) +" "+ short() +".\n");

    return 1;
}

public int
unwield(object what)
{
    if (wielder != this_player())
	return 1;

    write("You release your "+ short() +".\n");
    say(QCTNAME(TP) +" releases "+ HIS(TP) +" "+ short() +".\n");

    return 1;
}

public int
f_rhelp(void)
{
    string *tmp = cmds - ({"rsmack"});
    write("With this "+ short() +" you may:\n\n"+
	"   rthreaten <whom> [how] : Let someone know they are about\n"+
	"                            to get spanked. Also: rthreat.\n\n"+
	"   rsmack <whom> [where] [how] : Smack someone's [where] [how].\n"+
	"           Also: "+ implode(tmp, ", ") +".\n\n"); 
    return 1;
}

public int
f_threat(string str)
{
    if (!strlen(str))
	return NF("Threaten <whom> [how]?\n");

    string *how = parse_adverb_with_space(str, "meaningfully", 1);
    object *oblist = parse_this(how[0], "[the] %l",
	ACTION_VISUAL | ACTION_THREATENING);

    if (!sizeof(oblist))
	return NF("Threaten <whom> [how]?\n");

    actor("You tap your "+ short() +" against your palm while eyeing",
	oblist, how[1] +".");
    all2act(" taps "+ HIS(TP) +" "+ short() +" against "+ HIS(TP) +" palm "+
	"while eyeing", oblist, how[1] +".", how[1],
	ACTION_VISUAL | ACTION_THREATENING);
    target(" taps "+ HIS(TP) +" "+ short() +" against "+ HIS(TP) +" palm "+
	"while eyeing you"+ how[1] +".", oblist, how[1],
	ACTION_VISUAL | ACTION_THREATENING);

    return 1;
}

/* Repeating verbs. */
private string *r_verbs = ({ " repeatedly",  " excessively",
	" continuously", " relentlessly", " rhythmically",
	" thoroughly", " tirelessly", " unceasingly", });

/* Violent verbs. */
private string *v_verbs = ({ " aggressively", " fiercely", " forcefully",
	" furiously", " harder", " heartlessly", " harshly", " horribly",
	" maliciously", " mercilessly", " painfully", " roughly",
	" ruthlessly", " sadistically", " savagely", " severely",
	" viciously", " violently", });

/* Quiet verbs. */
private string *q_verbs = ({ " gently", " softly", " lightly", " lazily",
	" affectionately", " amicably", " barely", " benignly", " feebly",
	" fondly", " gingerly", " halfheartedly", " harmlessly",
	" hesitantly", " languidly", " pathetically", " soundlessly", });

#define FIRM_IMPACT  ({ "impacting", "striking", "walloping" })
#define SOFT_IMPACT  ({ "hitting", "swatting", "smacking" })
#define STD_IMPACT   (FIRM_IMPACT | SOFT_IMPACT)
#define VIO_IMPACT   ({ "beating", "pounding", "bludgeoning", \
			"smacking", "walloping" })

#define FIRM_SOUND   ({ "SMACK", "WHAP", "THUD", "THWACK", "WHACK" })
#define SOFT_SOUND   ({ "THUMP", "WHOP", "WHUMP" })
#define STD_SOUND    (FIRM_SOUND | SOFT_SOUND)

#define FIRM_FEEL    ({ "resounding", "loud" })
#define SOFT_FEEL    ({ "soft", "fleshy" })
#define STD_FEEL     (FIRM_FEEL | SOFT_FEEL)
#define VIO_FEEL     ({ "painful", "stinging", "blistering", \
			"breath stealing", "bruising" })

private mapping places = ([
            "arm": ({ STD_IMPACT,  STD_SOUND,  FIRM_FEEL }),
        "forearm": ({ STD_IMPACT,  FIRM_SOUND, FIRM_FEEL }),
      "upper arm": ({ STD_IMPACT,  FIRM_SOUND, FIRM_FEEL }),
       "shoulder": ({ STD_IMPACT,  FIRM_SOUND, FIRM_FEEL }),
           "back": ({ STD_IMPACT,  FIRM_SOUND, FIRM_FEEL }),
          "chest": ({ SOFT_IMPACT, STD_SOUND,  FIRM_FEEL }),
          "tummy": ({ STD_IMPACT,  STD_SOUND,  STD_FEEL  }),
          "bosom": ({ STD_IMPACT,  STD_SOUND,  SOFT_FEEL, 1, "chest" }),
       "cleavage": ({ SOFT_IMPACT, SOFT_SOUND, SOFT_FEEL, 1, "chest" }),
         "bottom": ({ SOFT_IMPACT, SOFT_SOUND, SOFT_FEEL }),
           "calf": ({ STD_IMPACT,  STD_SOUND,  FIRM_FEEL }),
          "thigh": ({ STD_IMPACT,  STD_SOUND,  STD_FEEL  }),
    "upper thigh": ({ STD_IMPACT,  SOFT_SOUND, STD_FEEL  }),
    "lower thigh": ({ STD_IMPACT,  SOFT_SOUND, STD_FEEL  }),
    "inner thigh": ({ STD_IMPACT,  SOFT_SOUND, STD_FEEL  }),
]);

private mapping gender = ([
]);


private mapping subst = ([
	" cheekily" : "cheek",
]);

public int
f_spank(string str)
{
    object ob;
    string verb = query_verb();
    int attr = ACTION_CONTACT | ACTION_MACTIVITY |
		ACTION_INTIMATE | ACTION_OFFENSIVE;
    
    if (!strlen(str))
	return NF(CAP(verb) +" what?\n");

    if (!wielder)
	return NF("You should wield it first.\n");

    object *oblist = filter(all_inventory(ENV(TP)) - ({ TP }), living);
    if (!parse_command(str, oblist,
	    "[the] %o [on] [the] / [his] / [her] / [its] %s", ob, str))
    {
	return NF(CAP(verb) +" <whom> [on] [the] <where> "+
	    "[how] with your "+ short() +"?\n");
    }

    string *how = parse_adverb_with_space(str, "firmly", 1);
    if (!strlen(how[0]))
    {
	if (strlen(subst[how[1]]))
	{
	    how[0] = subst[how[1]];
	    how[1] = " ";
	}
	else
	{
	    how[0] = one_of_list(m_indexes(places));
	}
    }

    if (!IN_ARRAY(how[0], m_indexes(places)))
    {
	write("The location \""+ how[0] +"\" is not valid.\n");
	return 1;
    }

    if (sizeof(places[how[0]]) == 5)
    {
	if (TP->query_gender() != places[how[0]])
	    how[0] = places[how[0]][4];
    }

    verb = verb[1..];
    oblist = ({ ob });
    how += places[how[0]];

    /* Impact */
    how[2] = one_of_list(how[2]);
    /* Sound */
    how[3] = one_of_list(how[3]);
    /* Feel */
    how[4] = one_of_list(how[4]);

    if (IN_ARRAY(how[1], r_verbs))
	how[3] = how[3] +"! "+ how[3] +"! "+ how[3];

    if (IN_ARRAY(how[1], v_verbs) && random(4))
    {
	how[2] = one_of_list(VIO_IMPACT);
	how[4] = one_of_list(VIO_FEEL);

	actor("You "+ verb, oblist, "'s "+ how[0] +" with your "+ short() +
	    ","+ how[1] +" "+ how[2] +" "+ HIM(ob) +" with "+
	    how[4] +" "+ "force.");
	all2act(" "+ verb +"s", oblist, "'s "+ how[0] +" with "+ HIS(TP) +" "+
	    short() +","+ how[1] +" "+ how[2] +" "+ HIM(ob) +
	    " with "+ how[4] +" force.", how[1], attr);
	target(" "+ verb +"s your "+ how[0] +" with "+ HIS(TP) +" "+ short() +
	    ","+ how[1] +" "+ how[2] +" you with "+ how[4] +" force.",
	    oblist, how[1], attr);
    }
    else if (IN_ARRAY(how[1], q_verbs) && random(4))
    {
	verb = cmding[verb];
	actor("You pat", oblist, "'s "+ how[0] +" with your "+ short() +
	    ","+ how[1] +" "+ verb +" "+ HIM(ob) +".");
	all2act(" pats", oblist, "'s "+ how[0] +" with "+ HIS(TP) +" "+
	    short() +","+ how[1] +" "+ verb +" "+ HIM(ob) +".",
	    how[1], attr);
	target(" pats your "+ how[0] +" with "+ HIS(TP) +" "+ short() +","+
	    how[1] +" "+ verb +" you.", oblist, how[1], attr);
    }
    else
    {
	actor("You "+ verb, oblist, how[1] +" with your "+ short() +
	    ", "+ how[2] +" "+ HIS(ob) +" "+ how[0] +" with a "+ how[4] +
	    " "+ how[3] +"!");
	all2act(" "+ verb +"s", oblist, how[1] +" with "+ HIS(TP) +
	    " "+ short() +", "+ how[2] +" "+ HIS(ob) +
	    " "+ how[0] +" with a "+ how[4] +" "+ how[3] +"!", how[1], attr);
	target(" "+ verb +"s you" + how[1] +" with "+ HIS(TP) +" "+
	    short() +", "+ how[2] +" your "+ how[0] +" with a "+
	    how[4] +" "+ how[3] +"!", oblist, how[1], attr);
    }

    return 1;
}

public void
init()
{
    ::init();

    if (TP != environment())
	return;

    add_action( f_rhelp, "rhelp"     );
    add_action(f_threat, "rthreat", 1);

    foreach(string cmd : cmds)
	add_action( f_spank, cmd );
}

public string
query_recover(void)
{
    return MASTER + ":" +
	query_keep_recover() + query_wep_recover() +
	"#!"+ which +"!"+ type +"!"+ adj1 +"!"+ adj2 +"!#";
}

public void
init_recover(string arg)
{
    string w, t, a1, a2;

    init_wep_recover(arg);
    init_keep_recover(arg);

    sscanf(arg, "%s#!%s!%s!%s!%s!#", arg, w, t, a1, a2);
    config_rod(w, t, a1, a2);
}
