/*
 *  file name:   Ivory brush ~brush.c
 *  creator(s):  Zielia + Lucius 2006
 *  purpose:     Object mortals can buy to brush their hair.
 *  note:        Works with hair from /d/Calia/gelan if the mortal has it.
 *
 *  Revisions:
 *     Lucius, Jul 2016: Added recovery code to preserve state.
 */
#pragma strict_types

inherit "/std/object";
inherit "/lib/holdable_item";
inherit "/lib/commands";
inherit "/lib/keep";

#include <cmdparse.h>
#include <wa_types.h>
#include <macros.h>
#include "zigg.h"
#include "hair.h"

public static string which = "";
public static int carved, locked;


private static mapping brush = ([
  "ivory" : ({
    "ivory brush",
    ({ "smooth", "ivory" }),
    "This is a lady's hairbrush carved from ivory. Its shape "+
    "is reminiscent of a slightly elongated oval that thins and "+
    "tapers down into the handle, which begins to bulge then "+
    "rounds off at the tip. The back of the brush is flat and "+
    "smooth%s. The bristle "+
    "plate is made from wood and glued to the ivory backing. The "+
    "bristles themselves are quite full and comprised of boar "+
    "bristles. They are long and flexible, meant to bend over the "+
    "hair rather than penetrate as you brush.\n",
    ({ "ebony", "carved ebony" }),
    "The ivory is exceptionally smooth, even where it is engraved. "+
    "The brush and handle are a single unit, all carved as one piece. "+
    "It's cool to the touch and the palest of white in colour with the "+
    "edges slightly rounded so as not to feel too sharp as you hold it.\n",
    ([
      1 : ({
	({ "engraving", "engravings", "carvings", "intricate engravings" }),
	"The intricate engraving on the back of this brush is "+
	"a portrait done in relief of a womans face tilted slightly "+
	"to the side. Her hair flutters as though blown by a subtle "+
	"breeze and frames her face. The carving is detailed enough "+
	"that you can nearly count each windblown strand and eyelash. "+
	"The carving of the face shows the woman with eyes closed and "+
	"refined features such as high cheekbones and elegantly tapered "+
	"nose leading to thin but well-formed lips. Her chin narrows "+
	"to a soft point and the weaving of her hair occupies the "+
	"rest of the back, ending at the neck to leave the "+
	"handle unadorned.\n",
      }),
    ]),
  }),
  "ebony" : ({
    "ebony brush",
    ({ "smooth", "ebony" }),
    "This is a hairbrush carved from ebony. Its shape "+
    "is reminiscent of a slightly elongated oval that thins and "+
    "tapers down into the handle, which begins to bulge then "+
    "rounds off at the tip. The back of the brush is flat and "+
    "smooth%s. The ebony is smooth, cool, heavy and "+
    "very black. The bristle plate is made from wood as well and "+
    "glued to the ebony backing. The bristles themselves are "+
    "quite full and comprised of boar bristles. They are long "+
    "and flexible, meant to bend over the hair rather than "+
    "penetrate as you brush.\n",
    ({ "ebony", "ebony back", "back" }),
    "The ebony is a very hard and heavy wood and feels exceptionally "+
    "smooth. The brush and handle are a single unit, all carved "+
    "as one piece and elegant in their simplicity. The ebony is "+
    "cool to the touch and the darkest black in colour with the "+
    "edges slightly rounded so as not to feel too sharp as you "+
    "hold it.\n",
    ([
      1 : ({
	({ "engraving", "engravings", "carvings", "intricate engravings" }),
	"The intricate engraving on the back of this brush is "+
	"a portrait done in relief of a womans face tilted slightly "+
	"to the side. Her hair flutters as though blown by a subtle "+
	"breeze and frames her face. The carving is detailed enough "+
	"that you can nearly count each windblown strand and eyelash. "+
	"The carving of the face shows the woman with eyes closed and "+
	"refined features such as high cheekbones and elegantly tapered "+
	"nose leading to thin but well-formed lips. Her chin narrows "+
	"to a soft point and the weaving of her hair occupies the "+
	"rest of the back, ending at the neck to leave the "+
	"handle unadorned.\n",
      }),
    ]),
  }),
]);

public void
create_brush(void)
{
    if (locked)
	return;

    locked = 1;
    which = one_of_list(m_indexes(brush));

    string extra, *adjs = brush[which][1];

    if (carved = random(2))
    {
	extra = "intricately-engraved";
	adjs += ({ "engraved" });

	add_item(brush[which][5][carved][0],
	    brush[which][5][carved][1]);
    }
    else
    {
	extra = "elegant";
	adjs += ({ "elegant" });
    }

    set_adj(adjs);
    set_short(extra + " " + brush[which][0]);
    set_long(sprintf(brush[which][2],
	    ({ "", ", though engraved rather intricately", })[carved]));

    add_item(brush[which][3], brush[which][4]);
}

public void
create_object(void)
{
    set_name("brush");
    set_pname("brushes");

    add_adj(({"sybarun", "ziggurat"}));

    add_item( ({ "bristles", "boar bristles", "full bristles" }),
      "The bristles of this brush are a darkish yellow-brown in colour. "+
      "They are rather flexible, meant to distribute the oils of ones hair "+
      "evenly from end to end, resulting in smooth shiny strands.\n");
    add_item( ({ "wood", "plate", "bristle plate" }),
      "The bristle plate is a thin, shaped cut of light-coloured "+
      "wood. It is glued directly to the ivory and has precisely drilled "+
      "holes that the bunches of bristles are set within.\n");
    add_item( ({ "handle", "ivory handle" }),
      "The handle is seemless from the brush itself, all of it carved as "+
      "one piece. Unlike the brush, however, the handle is plain and "+
      "unadorned. Its shape is one of a simple bulging design starting at "+
      "the neck of the brush then tapering into a wide, rounded tip.\n");
    add_item( ({ "backing", "ivory backing" }),
      "This is simply the underside of the brush. The wood bristle plate "+
      "is glued directly to it so you can't really see it except at the "+
      "edges where it is rounded and plain.\n");

    add_prop(OBJ_I_VALUE,  500);
    add_prop(OBJ_I_WEIGHT, 75);
    add_prop(OBJ_I_VOLUME, 75);

    set_keep(1);
    set_slots(W_ANYH);

    set_alarm(1.0, 0.0, create_brush);
	
    if (IS_CLONE)
      set_item_expiration();  	
	
}

public mixed
hold(void)
{
    if (this_player() != environment())
	return "";

    return 0;
}

public mixed
release(void)
{
    if (this_player() != environment())
	return 1;

    return 0;
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    holdable_item_leave_env(from, to);
}

public void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_holdable_item();
}

public int
do_brush(string str)
{
    object *oblist;
    string *how;
    int num = random(10);

    how = parse_adverb_with_space(str, "tenderly", 1);

    if (!stringp(how[0]) || how[0] == "hair")
    {
	if (IN_ARRAY("bald", TP->query_adjs()))
	{
	    notify_fail("You don't have any hair to brush!\n");

	    return 0;
	}

	if (IN_ARRAY(STYLE(TP), tangled))
	{
	    write("You try to brush your"+ HAIR(TP) +
	      " with your "+ short() +" but as the brush is quickly "+
	      "snared by your many tangles, you realize it is futile. "+
	      "With a painful jerk, you pull the brush free.\n");

	    allbb(" tries to brush "+ HIS(TP) + HAIR(TP) +
	      " with "+ HIS(TP) +" "+ short() +
	      " but seems to reconsider as the brush is caught by a tangle. "+
	      "With a rough tug, "+ HE(TP) +" pulls the brush free.",
	      how[1], ACTION_VISUAL);

	    return 1;
	}

	if (IN_ARRAY(STYLE(TP), curled))
	{
	    write("You carefully brush your"+ LENGTH(TP) + COLOR(TP) +
	      " locks with your "+ short() +", delicately seperating each "+
	      "curl with your fingers and using the brush to smooth and "+
	      "shape it.\n");

	    allbb(" carefully brushes "+ HIS(TP) + LENGTH(TP) +
	      COLOR(TP) +" locks with "+ HIS(TP) +" "+ short() +
	      ", delicately seperating each curl with "+ HIS(TP) +
	      " fingers and using the brush to smooth and shape them.",
	      how[1], ACTION_VISUAL);

	    return 1;
	}

	if (IN_ARRAY(STYLE(TP), missing))
	{
	    write("You gently brush the sparse remains of your "+
	      HAIR(TP) +" with your "+ short() +".\n");

	    allbb(" gently brushes the sparse remains of "+
	      HIS(TP) + HAIR(TP) +" with "+ HIS(TP) +" "+
	      short() +".", how[1], ACTION_VISUAL);

	    return 1;
	}

	if (IN_ARRAY(STYLE(TP), back))
	{
	    write("You lightly brush back the loose strands of your "+
	      HAIR(TP) +", smoothing them back "+
	      "into place with your "+ short() +".\n");

	    allbb(" lightly brushes back the loose strands of "+
	      HIS(TP) + HAIR(TP) +", "+
	      "smoothing them back into place with "+ HIS(TP) +" "+
	      short() +".", how[1], ACTION_VISUAL);

	    return 1;
	}

	if (IN_ARRAY(STYLE(TP), up))
	{
	    write("You brush your"+ HAIR(TP) +
	      " with small flicks of your wrist, using your "+
	      short() +" to coax the strands up to their maximum "+
	      "height.\n");

	    allbb(" brushes "+ HIS(TP) + HAIR(TP) +
	      " with small flicks of "+ HIS(TP)
	      +" wrist, using "+ HIS(TP) +" "+ short() +
	      " to coax the strands up to their maximum height.",
	      how[1], ACTION_VISUAL);

	    return 1;
	}

	if (STYLE(TP) == "vermin-infested")
	{
	    write("You whip your "+ short() +" through your"+ HAIR(TP) +
	      ", vermin flying out every which "+
	      "way and scrurrying off as you brush.\n");

	    allbb(" whips "+ HIS(TP) +" "+ short() +" through "+
	      HIS(TP) + HAIR(TP) +", vermin "+
	      "flying out every which way and scrurrying off as "+
	      HE(TP) +" brushes.", how[1], ACTION_VISUAL);

	    return 1;
	}

	if (STYLE(TP) == "lice-infested")
	{
	    write("You whip your "+ short() +" through your"+ HAIR(TP) +
	      ", lice flying everywhere as you brush.\n");

	    allbb(" whips "+ HIS(TP) +" "+ short() +" through "+
	      HIS(TP) + HAIR(TP) +", lice "+
	      "flying everywhere as "+ HE(TP) +" brushes.",
	      how[1], ACTION_VISUAL);

	    return 1;
	}
	else
	{
	    switch(num)
	    {
	    case 1 :

		write("You brush your"+ HAIR(TP) +
		  " vigorously with your "+ short() +" feeling it "+
		  "crackle with static electricity.\n");

		all(" brushes "+ HIS(TP) + HAIR(TP) +
		  " vigorously with "+ HIS(TP) +" "+ short() +
		  " as tiny sparks of electricity crackling through it.",
		  how[1], ACTION_VISUAL);

		break;

	    case 2 :

		write("You carefully brush your"+ HAIR(TP) +" with your "+
		  short() +" working out the tangles with small, "+
		  "tender tugs.\n");

		allbb(" carefully brushes "+ HIS(TP) +
		  HAIR(TP) +", working out the tangles with "+
		  HIS(TP) +" "+ short() +".", how[1], ACTION_VISUAL);

		break;

	    case 3 :

		write("You brush your"+ HAIR(TP) +" repeatedly with "+
		  "your "+ short() +" distributing the oils and giving "+
		  "it a lustrous gloss.\n");

		allbb(" brushes "+ HIS(TP) + HAIR(TP) +
		  " repeatedly with "+ HIS(TP) +" "+ short() +
		  " distributing the oils and giving it a lustrous gloss.",
		  how[1], ACTION_VISUAL);

		break;

	    case 4 :

		write("You fluff your"+ HAIR(TP) +" with your "+
		  short() +" making the strands look silky and voluminous.\n");

		allbb(" fluffs "+ HIS(TP) + HAIR(TP) +" with "+
		  HIS(TP) +" "+ short() +" making the strands look "+
		  "silky and voluminous.", how[1], ACTION_VISUAL);

		break;

	    default :

		write("You gently brush your"+ HAIR(TP) +" with "+
		  "luxurious, smooth strokes of your "+ short() +".\n");

		allbb(" gently brushes "+ HIS(TP) + HAIR(TP) +
		  " with smooth strokes of "+ HIS(TP) +" "+ short() +".",
		  how[1], ACTION_VISUAL);

		break;

	    }

	    return 1;
	}

    }

    oblist = parse_this(how[0], "[the] %l [hair]",
      ACTION_CONTACT | ACTION_INTIMATE);

    if (sizeof(oblist) != 1)
    {
	notify_fail("Brush who?\n");
	return 0;
    }
    else
    {
	actor("You"+ how[1] +" brush the"+ LENGTH(oblist[0]) +
	  " strands of", oblist, "'s"+ COLOR(oblist[0]) +" hair "+
	  "with your "+ short() +".");

	all2actbb(how[1] +" brushes the"+ LENGTH(oblist[0]) +
	  " strands of", oblist, "'s"+ COLOR(oblist[0]) +" hair "+
	  "with "+ HIS(TP) +" "+ short() +".",
	  how[1], ACTION_CONTACT | ACTION_INTIMATE);

	target(how[1]+ " brushes the"+ LENGTH(oblist[0]) +" strands "+
	  "of your"+ COLOR(oblist[0]) +" hair with "+ HIS(TP) +
	  " "+ short() +".", oblist, how[1], ACTION_CONTACT |
	  ACTION_INTIMATE);

	return 1;
    }

    notify_fail("Brush what?\n");
    return 0;
}

public int
f_spank(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "playfully", 1);

    oblist = parse_this(how[0], "[the] %l [with] [the] 'brush'",
      ACTION_CONTACT | ACTION_INTIMATE);

    if (!sizeof(oblist))
    {
	notify_fail("Spank whom/what [how]?\n");
	return 0;
    }

    actor("You "+ query_verb(), oblist, how[1] +" with the flat backside "+
      "of your "+ short() +".");
    all2act(" "+ query_verb() +"s", oblist, how[1] +" with the flat backside "+
      "of "+ HIS(TP) +" "+ short() +".", how[1], ACTION_CONTACT
      | ACTION_INTIMATE);
    target(" "+ query_verb() +"s you" + how[1] +" with the flat backside of "+
      HIS(TP) +" "+ short() +".", oblist, how[1], ACTION_CONTACT
      | ACTION_INTIMATE);

    return 1;
}

public string
query_recover(void)
{
    return MASTER + ":" + carved + "@" + which + "$" +
	query_item_expiration_recover(); 
}

public void
init_recover(string arg)
{
    sscanf(arg, "%d@%s$%s", carved, which, arg);
    init_item_expiration_recover(arg);
    create_brush();
}

public void
init()
{
    ::init();

    add_action( do_brush, "brush"  );
    add_action(  f_spank, "spank"  );
    add_action(  f_spank, "paddle" );
}
