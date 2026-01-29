// file name:   paddle.c
// creator(s):  Zielia
// last update:
// purpose:
// note:
// bug(s):
// to-do:

inherit "/std/weapon";
inherit "/lib/keep";
inherit "/lib/commands";

#include "zigg.h"
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <adverbs.h>
#include <macros.h>

#define HIT 30
#define PEN 10

#define SHORT 		paddle[which][0]
#define ADJS  		paddle[which][1]
#define LONG  		paddle[which][2]
#define HANDLE 		paddle[which][3]
#define MATERIAL  	paddle[which][4]
#define MATERIAL_DESC  	paddle[which][5]
#define EXTRA	  	paddle[which][6]

#define ESHORT	  	EXTRA[ornament][0]
#define EADJ	  	EXTRA[ornament][1]
#define ELONG	  	EXTRA[ornament][2]
#define EITEMS	  	EXTRA[ornament][3]
#define EIDESC	  	EXTRA[ornament][4]
#define EBLOWS	  	EXTRA[ornament][5]


private static mapping paddle = ([
"leather" : ({
	"black leather paddle",
	({"black", "leather", "stiff", "rounded", "round"}),
	"Three layers of stiff, yet flexible leather are sewn "+
	    "together with red stitching to form the rounded face "+
	    "of this paddle. A piece of heavy hide is bonded into the "+
	    "handle to give a more comfortable grip. Another strip of "+
	    "leather passes through a hole at the end of the handle to "+
	    "serve as a wrist strap or means by which to hang it. ",
	"A piece of heavy hide is bonded into the "+
	    "handle to give a more comfortable grip. Another strip of "+
	    "leather passes through a hole at the end of the handle to "+
	    "serve as a wrist strap or means by which to hang it. ",
	({"leather", "stiff leather", "flexible leather",
	    "black leather",}),
	"This leather is thick, heavy and stiff, but still has "+
	    "some give. It is like the leather often used for boot "+
	    "soles, but dyed black and with a fine, pebbly grain.\n",
    ([
	"holes" : ({
	    "perforated",
	    ({"perforated", "holey"}),
	    "Twelve round holes have been punched in the layers of stiff "+
		"leather to reduce air resistance when the paddle is swung "+
		"and produce a sharper sting on impact.\n",
	    ({"holes", "hole"}),
	    "Twelve round holes have been punched in the layers of stiff "+
		"leather to reduce air resistance when the paddle is swung "+
		"and produce a sharper sting on impact.\n",
	    1,
		}),
	"studs" : ({
	    "studded",
	    ({"studded", "knobby"}),
	    "Raised metal knobs stud the leather, creating focused points of "+
		"impact across the surface of the paddle.",
	    ({"studs", "knobs", "stud", "knob"}),
	    "The studs are made of a silvery metal. They rise slightly from "+
		"the surrounding leather, creating texture and many focused "+
		"impact points, but they are well rounded without any sharp "+
		"edges to cut the skin. The slight flexability of the leather "+
		"and even spacing of the studs also slow bruising.",
	    2,
		}),
	"fur" : ({
	    "fuzzy",
	    ({"fuzzy", "furry"}),
	    "Soft black rabbit fur has been stitched to the back of the paddle.",
	    ({"fur",}),
	    "The fur is soft and silky: Perfect for a soothing caress on "+
		"tender skin.\n",
	    0,
		}),
    ]),
  }),

"bloodwood" : ({
    "bloodwood paddle",
    ({"scarlet", "bloodwood", "wood", "heavy", "rectangular",
	"glossy",}),
    "The paddle is long, rectangular, and made of heavy, scarlet "+
	"bloodwood. The edges have been rounded and some kind of "+
	"lacquer applied to give the wood a nice gloss. The short handle "+
	"is carved to allow an optimal grip. A leather strap "+
	"passes through a small hole drilled into the handle to allow "+
	"the paddle to be hung up or for use as a wrist strap. ",
    "The short handle is carved to allow an optimal grip. A leather strap "+
	"passes through a small hole drilled into the handle to allow "+
	"the paddle to be hung up or for use as a wrist strap. ",
    ({"wood", "bloodwood", "dense", "heavy", "grain",
	"scarlet wood",}),
    "The wood is very dense, with a tight fine, mostly linear "+
	"grain and beautiful deep rose colour.\n",
    ([
	"holes" : ({
	    "perforated",
	    ({"perforated", "holey"}),
	    "Twelve round holes have been drilled into wood at "+
		"even intervals in order to reduce air resistance when "+
		"the paddle is swung and produce a sharper sting in impact. "+
		"The edges of the holes are bevelled to reduce the chance "+
		"of blistering.\n",
	    ({"holes", "hole"}),
	    "Twelve round holes have been drilled into wood at even intervals "+
		"in order to reduce air resistance when the paddle is swung "+
		"and produce a sharper sting in impact. The edges of the "+
		"holes are bevelled to reduce the chance of blistering.\n",
	    1,
		}),
	"studs" : ({
	    "studded",
	    ({"studded", "knobby"}),
	    "Raised metal studs have been drilled into the wood, creating "+
		"vicious points of impact across the surface of the paddle.",
	    ({"studs", "knobs", "stud", "knob"}),
	    "The studs are made of a silvery metal. They rise slightly from "+
		"the wood. They are well rounded without any sharp "+
		"edges to cut the skin, but with the rigid, heavy wood behind "+
		"them, they are are likely to have a bruising bite.\n",
	    2,
		}),
	"fur" : ({
	    "fuzzy",
	    ({"fuzzy", "furry"}),
	    "Soft red fox fur has been tacked to the back of the paddle.",
	    ({"fur",}),
	    "The fur is soft and silky: Perfect for a soothing caress on "+
		"tender skin.\n",
	    0,
		}),
    ]),
  }),
]);

private static string ornament, which = one_of_list(m_indexes(paddle));

public void
create_weapon(void)
{
    setuid();
    seteuid(getuid());

    set_name("paddle");
    set_adj(ADJS);
    add_adj(({"sybarun", "ziggurat"}));

    if (random(3))
    {
	ornament = one_of_list(m_indexes(EXTRA));

	add_adj(EADJ);
	set_short(ESHORT +" "+ SHORT);
	set_long(LONG + ELONG + "\n");
	add_item(EITEMS, EIDESC);
    }
    else
    {
	set_short(SHORT);
	set_long(LONG +"\n");
    }

    set_wt(W_CLUB);
    set_hit(HIT);
    set_pen(PEN);
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);
    set_wf(this_object());

    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN) + 100 + random(50));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_CLUB) +
        random(50) - 25);

    add_item(MATERIAL, MATERIAL_DESC);
    add_item(({"handle"}), HANDLE +"A small stamp says <phelp>.\n");
    add_cmd_item("paddle", "help", "@@f_phelp");
}

public string
f_phelp(void)
{
    write(
	"    With this paddle you may:\n\n"+
	"    phelp                : This text. Also 'help paddle'.\n"+
	"\n"+
	"    pthreaten [how]      : Let someone know they are about to get\n"+
	"                           paddled.\n"+
	"\n"+
	"    pspank <whom> [how]  : Paddle someone's bottom. Also 'ppaddle'\n"+
	"                           and 'psmack'.\n"+
	"\n");

    if (ornament == "fur")
    {
	write(
	"    pcaress <whom> [how] : Caress someone with the furry side\n"+
	"                           of your paddle.\n"+
	"\n");
    }

    return "";
}

public int
wield(object what)
{
    write("You grip the handle of your "+ short() +".\n");
    say(QCTNAME(TP) +" grips the handle of "+ HIS(TP) +" "+ short() +".\n");

    return 1;
}

public int
unwield(object what)
{
    write("You release the handle of your "+ short() +".\n");
    say(QCTNAME(TP) +" releases the handle of "+
	HIS(TP) +" "+ short() +".\n");

    return 1;
}

public int
f_threaten(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "meaningfully", 1);

    oblist = parse_this(how[0], "[the] %l",
	ACTION_VISUAL | ACTION_THREATENING);

    if (!sizeof(oblist))
    {
	notify_fail("Threaten whom [how]?\n");
	return 0;
    }

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

public int
f_caress(string str)
{
    object *oblist;
    string *how;
    int attr = ACTION_CONTACT | ACTION_MACTIVITY | ACTION_INTIMATE;

    if (ornament != "fur")
	return 0;

   if (!this_object()->query_wielded())
   {
	notify_fail("You should wield it first.\n");
	return 0;
   }

    how = parse_adverb_with_space(str, "soothingly", 1);
    oblist = parse_this(how[0], "[the] %l", attr);

    if (!sizeof(oblist))
    {
	notify_fail("Caress whom [how] with your paddle?\n");
	return 0;
    }

    actor("You caress", oblist, how[1] +" with the soft fur of your "+
	short() +".");
    all2act(" caresses", oblist, how[1] +" with the soft fur of "+ HIS(TP) +
	" "+ short() +".", how[1], attr);
    target(" caresses you"+ how[1] +" with the soft fur of "+ HIS(TP) +" "+
	short() +".", oblist, how[1], attr);

    return 1;
}

private string *impacts = ({ "impacting", "striking", "hitting",
	"slapping", "swatting", "walloping", });
private string *sounds = ({ "SMACK", "WHAP", "THUD", "THUMP",
	"THWACK", "WHACK", "WHOP"});
private string *feels = ({ "resounding", "loud", });

private string *verbs1 = ({ " repeatedly",  " excessively",
	" continuously", " relentlessly", " rhythmically",
	" thoroughly", " tirelessly", " unceasingly", });

private string *verbs2 = ({ " aggressively", " fiercely", " forcefully",
	"furiously", " harder", " heartlessly", " harshly", " horribly",
	" maliciously", " mercilessly", " painfully", " roughly",
	" ruthlessly", " sadistically", " savagely", " severely",
	" viciously", " violently", });

private string *verbs3 = ({ " gently", " softly", " lightly",
	" affectionately", " amicably", " barely", " benignly", " feebly",
	" fondly", " gingerly", " halfheartedly", " harmlessly",
	" hesitantly", " languidly", " pathetically", " soundlessly", });

public int
f_spank(string str)
{
    int blows = 1;
    object mark, *oblist;
    string *how, alt, verb = query_verb();
    string impact = one_of_list(impacts);
    string sound  = one_of_list(sounds);
    string feel   = one_of_list(feels);
    int attr = ACTION_CONTACT | ACTION_MACTIVITY |
		ACTION_INTIMATE | ACTION_OFFENSIVE;
    
    if (!this_object()->query_wielded())
    {
	notify_fail("You should wield it first.\n");
	return 0;
    }

    verb   = verb[1..];
    how    = parse_adverb_with_space(str, "sharply", 1);
    oblist = parse_live(how[0], "[the] %o", attr);

    if (sizeof(oblist) != 1)
    {
	return notify_fail(capitalize(verb) +" <whom> [how] "+
	    "with your "+ short() +"?\n");
    }

    if (strlen(ornament))
	blows += EBLOWS;

    if (IN_ARRAY(how[1], verbs1))
    {
	blows *= 3;
	sound = sound +"! "+ sound +"! "+ sound;
    }

    if (IN_ARRAY(how[1], verbs2) && random(4))
    {
	impact = one_of_list(({"beating", "pounding", "bludgeoning",
	    "smacking", "walloping", }));

	feel  = one_of_list(({"painful", "stinging", "blistering",
	    "breath stealing", "bruising"}));

	actor("You "+ verb, oblist, "'s bottom with your "+ short() +
	    ","+ how[1] +" "+ impact +" "+ HIM(oblist[0]) +" with "+
	    feel +" "+ "force.");
	all2act(" "+ verb +"s", oblist, "'s bottom with "+ HIS(TP) +" "+
	    short() +","+ how[1] +" "+ impact +" "+ HIM(oblist[0]) +
	    " with "+ feel +" force.", how[1], attr);
	target(" "+ verb +"s your bottom with "+ HIS(TP) +" "+ short() +
	    ","+ how[1] +" "+ impact +" you with "+ feel +" force.",
	    oblist, how[1], attr);
    }
    else if (IN_ARRAY(how[1], verbs3) && random(4))
    {
	actor("You pat", oblist, "'s bottom with your "+ short() +
	    ","+ how[1] +" spanking "+ HIM(oblist[0]) +".");
	all2act(" pats", oblist, "'s bottom with "+ HIS(TP) +" "+
	    short() +","+ how[1] +" spanking "+ HIM(oblist[0]) +".",
	    how[1], attr);
	target(" pats your bottom with "+ HIS(TP) +" "+ short() +","+
	    how[1] +" spanking you.", oblist, how[1], attr);
    }
    else if (ornament == "holes")
    {
	actor("You "+ verb, oblist, "'s bottom"+ how[1] +
	    ", your "+ short() +" whistling through the air before "+
	    "landing with a "+ feel +" "+ sound +"!");
	all2act(" "+ verb +"s", oblist, "'s bottom"+ how[1] +
	    ", the "+ short() +" whistling through the air before "+
	    "landing with a "+ feel +" "+ sound +"!", how[1], attr);
	target(" "+ verb +"s your bottom"+ how[1] +", "+ HIS(TP) +" "+
	    short() +" whistling through the air before, it lands "+
	    " with a "+ feel +" "+ sound +"!", oblist, how[1], attr);
    }
    else if (ornament == "studs")
    {
	actor("You "+ verb, oblist, "'s bottom"+ how[1] +
	    " with your "+ short() +", the metal studs biting deeply as "+
	    "it lands with a "+ feel +" "+ sound +"!");
	all2act(" "+ verb +"s", oblist, "'s bottom"+ how[1] +
	    " with the "+ short() +", the metal studs biting deeply as "+
	    "it lands with a "+ feel +" "+ sound +"!", how[1], attr);
	target(" "+ verb +"s your bottom"+ how[1] +" with "+ HIS(TP) +" "+
	    short() +", the metal studs biting deeply as "+
	    "it lands with a "+ feel +" "+ sound +"!",
	    oblist, how[1], attr);
    }
    else
    {
	actor("You "+ verb, oblist, how[1] +" with your "+ short() +
	    ", "+ impact +" "+ HIS(oblist[0]) +" bottom with a "+ feel +
	    " "+ sound +"!");
	all2act(" "+ verb +"s", oblist, how[1] +" with "+ HIS(TP) +
	    " "+ short() +", "+ impact +" "+ HIS(oblist[0]) +
	    " bottom with a "+ feel +" "+ sound +"!", how[1], attr);
	target(" "+ verb +"s you" + how[1] +" with "+ HIS(TP) +" "+
	    short() +", "+ impact +" your bottom with a "+
	    feel +" "+ sound +"!", oblist, how[1], attr);
    }

    if (!objectp(mark = present("Zig::PMark", oblist)))
    {
	mark = clone_object(ZIG_OBJ +"paddle_marks");
	mark->move(oblist[0]);
    }

    while(blows--)
	mark->set_blows();

    return 1;
}

public void
init()
{
    ::init();

    add_action(   f_spank, "pspank"   );
    add_action(   f_spank, "psmack"   );
    add_action(   f_spank, "ppaddle"  );
    add_action(f_threaten, "pthreaten");
    add_action(  f_caress, "pcaress"  );
    add_action(   f_phelp, "phelp"    );
}

public string
query_recover(void)
{
    return MASTER + ":" + query_keep_recover() +
	query_wep_recover() + "#!"+ which +"!"+ ornament +"!#";
}

public void
init_recover(string arg)
{
    string index, extra;

    init_wep_recover(arg);
    init_keep_recover(arg);

    sscanf(arg, "%s#!%s!%s!#", arg, index, extra);

    /* Remove current attributes. */
    remove_adj(ADJS);
    remove_item(MATERIAL[0]);

    if (strlen(ornament))
    {
	remove_adj(EADJ);
	remove_item(EITEMS[0]);
    }

    /* Add recovered attributes. */
    which = index;
    ornament = extra;

    set_adj(ADJS);
    add_item(MATERIAL, MATERIAL_DESC);

    if (EXTRA[ornament])
    {
	set_short(ESHORT +" "+ SHORT);
	set_long(LONG + ELONG + "\n");
	add_adj(EADJ);
	add_item(EITEMS, EIDESC);
    }
    else
    {
	set_short(SHORT);
	set_long(LONG +"\n");
    }
}

