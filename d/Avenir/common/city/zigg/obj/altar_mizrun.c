// file name  :  altar_mizrun.c
// creator(s) :  Zielia
// purpose    :  Altar for the Ziggurat
// note       :  Successful worship is intoxicating. 
//               Drinking from altar will cause memory loss - player will randomly forget
//		         names they have remembered.
//               Offering a poppy will allow player to choose another player
//               to forget their name, at the cost of a name.
// revision(s):  Lilith, Dec 2021/Jan 2022: got the targetted name-forget
//                 working, added name-for-a-name functionality and logging.
// bug(s)     :
// to-do      :
#pragma strict_types

#include "zigg.h"
#include "/d/Avenir/include/deities.h"
#include <macros.h>
#include <language.h>
#include <stdproperties.h>

#define DELAY  3600.0
#define FAERIE_ID          "_Avenir_park_faerie"
#define DRANK_FROM_ALTAR   "_live_i_drank_from_mizrun_altar"
#define PRAYER_PROP        "_live_i_prayed_at_mizrun_altar"

inherit (ZIG_LIB + "altar");
inherit RLOG;

private static mapping m_forgetting = ([]);

public void delay_forget();
/*
 * set_id_long(string)      - Identified long desc.
 * set_unid_long(string)    - Unidentifed long desc.
 * set_altar_short(string)  - Short desc.
 * set_god(string *)        - God(s) of altar.
 * set_altar_hour(int)      - Hour of the God.
 * set_offer_max(int)       - Max offerings.
 * set_altar_name(string)   - True name of altar.
 * set_offering_prop(string *)   - Acceptable offerings have these props.
 *
 ****** ADD ACTIONS BELOW *************************************************
 *
 * set_bless_command(string *)     - Accepted commands to bless altar.
 * set_defile_command(string *)    - Accepted commands to defile altar.
 * set_repair_command(string *)    - Accepted commands to repair altar.
 * set_destroy_command(string *)   - Accepted commands to destory altar.
 *
 * set_offer_command(string *)     - Accepted commands to make offerings.
 * set_pray_command(string *)      - Accepted commands to pray at altar.
 */

public void
create_altar(void)
{
    set_god("mizrun");
    set_altar_hour(3);
    set_altar_name("ziggurat::mizrun");
    set_altar_short("low silver font surrounded by a hazy green aura");

    add_name(({"font"}));
    set_adj(({"silver", "green", "hazy", "low"}));

    set_unid_long("An emerald green cushion is placed on the ground before "+
      "a white marble pedestal, presumably to kneel upon. Atop the pedestal "+
      "is a silver basin filled with a glowing, sea green liquid that swirls "+
      "lazily and occassionally dissipates into wisps of hazy green vapor.");
    set_id_long("An emerald green cushion is placed on the ground before "+
      "a white marble pedestal, presumably to kneel upon. Atop the pedestal "+
      "is a silver basin filled with a swirling sea green liquid, which "+
      "glows softly in the dim light: the holy water of Mizrun.");

    set_offering_prop(({MIZRUN_OFFERING}));

    set_offer_command(({"offer", "sacrifice"}));
    set_pray_command(({
	"pray", "petition", "worship", "respect", "revere", "celebrate"
      }));
    set_defile_command(({"defile"}));
    set_destroy_command(({"break", "destroy"}));
    set_offer_max(20);
    set_no_show_composite(1);

    add_item(({"font","bowl","basin","cup","flower"}),
      "The bowl of the font is made of carefully polished silver and "+
      "shaped like the poppy flowers carved into the base. Molded petals "+
      "overlap tightly so none of the green lethean nectar within the "+
      "bowl can escape.\n");
    add_item(({"base","pedestal","flowers","fairies","carvings","carving",
	"fields","marble",}),
      "The base of the font is made a pedestal of carved, white marble. "+
      "Euphoric fairies frollic in fields of delicately carved poppies "+
      "all around the pedestal. Just beneath the flowers, deeply carved "+
      "runes and symbols seem to shimmer through the green haze.\n");
    add_item(({"runes","rune","symbol","symbols"}),
      "The runes and symbols carved around the base shift and shimmer, "+
      "seeming to blur as you try to focus on them, never allowing you "+
      "to quite make them out. Only one is still, glowing softly with "+
      "it's own yellow light: It is a crescent with its tips pointed "+
      "upward.\n");
    add_item(({"cushion",}),
      "It is a velvet covered, emerald green cushion most likely "+
      "placed here for people to kneel upon as they worship and pray.\n");
    add_item(({"liquid","water","holy water","nectar","gas","vapor",
	"lethean nectar","mist","aura"}),
      "Within the font a sea green liquid glows faintly. The liquid "+
      "swirls hypnotically, seeming to shift and move of its own accord, "+
      "occassionally evaporating into the wisps of hazy green gas which "+
      "hang in the air around the altar and give the room a warm, "+
      "cloying sweet smell.\n");
}

/*
 * Function name: pray_text
 * Description	: Here the prayer/worship message is written.
 * Arguments	: string verb - The verb used (pray or worship)
 * 		  string god  - The god invoked.
 */
static void
pray_text(string verb, string god)
{
    if (verb == "pray")
	verb += "ing";

    write("You assume the proper posture for "+ verb +" to "+ god +
	".\n\nYou kneel upon the emerald cushion, pressing "+
	"your forehead against the ground and stretching your "+
	"arms out toward the "+ real_short() +".\n");

    say(QCTNAME(TP) +" kneels before the "+ real_short() +
        ", supplicating "+ HIM(TP) +"self on the emerald cushion.\n");
}

public void
hook_smelled(string what)
{
    write("The haze around the font has a warm, saccharine smell "+
      "that is almost too sweet yet makes you feel relaxed and "+
      "lethargic.\n");
}

private int
random_name(string name, object tp)
{
    if (!random(10))
	tp->remove_remembered(name);

    return 0;
}

private void
f_lethe(object tp, int count)
{
    object room = environment(TO);
    string name;

    switch(++count)
    {
    case 1:
	if (!present(tp, room))
	{
	    m_delkey(m_forgetting, tp);
	    return;
	}
	tp->catch_tell("The green liquid seems to vaporize as soon as you "+
	  "cup it in your hand, leaving a cool tingle in its wake. You "+
	  "quickly raise your hand to your mouth, capturing a tiny sip "+
	  "before it escapes.\n");
	tell_room(room, QCTNAME(tp) +" takes a tiny sip of the sea green "+
	  "nectar.\n", tp, tp);
	break;
    case 2:
	tp->catch_tell("The sweet taste rolls over your tongue, becoming "+
	  "insubstantial until you aren't sure if you swallow or breathe "+
	  "it into you.\n");

	if (!present(tp, room))
	    return;

	tell_room(room, QCTNAME(tp) +" draws a deep breath and swallows, "+
	  HIS(TP) +" eyes taking on a euphoric glaze.\n", tp, tp);
	break;
    case 3:
	tp->catch_tell("Suddenly the world seems more vibrant, colors seem, "+
	  "brighter and the air almost shimmers.\n");
	break;
    case 4:
	if (!m_sizeof(tp->query_remembered()))
	{
	    tp->catch_tell("You feel wonderfully intoxicated, jubilant "+
	      "and carefree.\n");
	    m_delkey(m_forgetting, tp);
	    break;
	}
	
	if (!tp->query_prop(DRANK_FROM_ALTAR))
	{   tp->catch_tell("You fill your cupped hand with a scoopful "+
		"of the green liquid and watch as it turns to vapor at "+
		"your touch, elusive as a forgotten memory, forever "+
		"beyond your grasp.\n");
		
	    tp->catch_tell("You wonder if it's safe to drink this "+
	        "strange liquid and if it would be wiser not to try "+
	        "again.\n");	
	        	
	    tell_room(room, QCTNAME(tp) +" scoops up a handful of the "+
	    	"strange green liquid from the altar and watches as it "+
	    	"evaporates in "+ HIS(tp) +" hand.\n", tp, tp);
	    tp->add_prop(DRANK_FROM_ALTAR, 1);
	}
	else if (tp->query_prop(DRANK_FROM_ALTAR) == 1)
	{   name = capitalize(one_of_list(m_indexes(tp->query_remembered())));
	    tp->remove_remembered(name);
	    tp->catch_tell("Flitting memories of "+ name +" pass through "+
	      "your mind quickly, then are gone.\n");
	    tp->add_prop(DRANK_FROM_ALTAR, 2);
	}
	else if (tp->query_prop(DRANK_FROM_ALTAR) == 2)
	{
	    filter(m_indexes(tp->query_remembered()), &random_name( , tp ));
	    tp->catch_tell("A wonderful cloudy feeling fills your mind "+
	      "and thoughts of the past become blissfully hazy and "+
	      "elusive.\n");
	    tp->add_prop(DRANK_FROM_ALTAR, 3);
	}
	else
	{
	    filter(m_indexes(tp->query_remembered()), tp->remove_remembered);
	    tp->catch_tell("Joyous ignorance descends upon you, letting "+
	      "you forget the pains of the past and begin anew.\n");
	    ALTER_PROP(tp, DRANK_FROM_ALTAR, 1);
	}
	m_delkey(m_forgetting, tp);
	break;
    default:
	count = -1;
	break;
    }

    if (count > 0)
    {
	set_alarm(3.0, 0.0, &f_lethe(tp, count));
    }
}

public mixed
query_forgetting(void)
{
    return m_forgetting;
}

public int
do_drink(string str)
{
    object tp = TP;

    if (!strlen(str))
    {
	notify_fail("Drink from what?\n");
	return 0;
    }

    if (!parse_command(str, ({ }),
	"[nectar] / [liquid] / [water} 'from' [the] 'font' / 'altar' / "+
	"'bowl' / 'basin' / 'cup' / 'flower' / 'bowl'"))
    {
	return 0;
    }

    if (m_forgetting[TP])
    {
	notify_fail("You are still savouring your last sip.\n");
	return 0;
    }

    write("You kneel upon the green velvet cushion edge and "+
	"scoop up a handful of the green liquid.\n");
    say(QCTNAME(TP) + " kneels upon the green velvet cushion edge "+
	"and scoops up a handful of the green liquid.\n");

    m_forgetting[TP] = set_alarm(3.0, 0.0, &f_lethe(tp, 0));
    TP->drink_soft(20, 0);
    if (!TP->drink_alco(TP->intoxicated_max()/3, 0))
    {
	TP->set_intoxicated(TP->intoxicated_max());
    }

    return 1;
}

public void
altar_result_pos(string verb, string god)
{
    string str;
    int num;
    int num2;
    object tp = TP;

    // increment the prayer prop to increase the chance of failure
    // for continual attempts.
    TP->add_prop(PRAYER_PROP, TP->query_prop(PRAYER_PROP) + 1);

    if(random((2 + TP->query_prop(PRAYER_PROP))/3))
    {
	TP->catch_tell("Your prayers go unheard.\n");
	return;
    }

    num = TP->query_intoxicated() + (TP->intoxicated_max() / 10);

    TP->set_intoxicated(num, 0);

    num2 = ftoi((itof(TP->query_intoxicated()) /
	(itof(TP->intoxicated_max()))) * 100.0);

    switch(num2)
    {
    case 81..100:
	str = "It suddenly dawns on you that you love "+
	    "everyone and everything.\n";
	break;
    case 61..80:
	str = "You feel strong and invigorated and maybe "+
	    "a bit invincible.\n";
	break;
    case 41..60:
	str = "The world around you seems more vibrant and exciting.\n";
	break;
    case 21..40:
	str = "You feel giddy and intoxicated.\n";
	break;
    default:
	str = "An effervescent feeling of elation bubbles through you.\n";
	break;
    }

    write("A feeling of ecstasy uplifts you, as though you can feel "+
      LANG_POSS(god) +" pleasure in your actions.\n");

    say(QCTNAME(TP) +" appears to be momentarily over"+
      "come with ecstacy.\n");

    set_alarm(2.0, 0.0, &tell_object(tp, str));
}


public void remove_faerie(object faerie)
{
    faerie->remove_object();
}

public void
faerie_blessing(object player)
{
    object room = ENV(TO);
    object faerie = clone_object(ZIG_MON +"gfaerie.c");
    faerie->move(room);
    faerie->faerie_blessing(player, 0);
    set_alarm(100.0, 0.0, &remove_faerie(faerie));
}

public void
altar_result_neg(string verb, string god)
{
    object room = ENV(TO);
    object fairy;

    ::altar_result_neg(verb, god);

    clone_object(ZIG_MON +"gfaerie.c")->move(room);
    clone_object(ZIG_MON +"gfaerie.c")->move(room);
    clone_object(ZIG_MON +"gfaerie.c")->move(room);
    clone_object(ZIG_MON +"gfaerie.c")->move(room);
    clone_object(ZIG_MON +"gfaerie.c")->move(room);
    clone_object(ZIG_MON +"gfaerie.c")->move(room);
    clone_object(ZIG_MON +"gfaerie.c")->move(room);
    clone_object(ZIG_MON +"gfaerie.c")->move(room);
    clone_object(ZIG_MON +"gfaerie.c")->move(room);
    clone_object(ZIG_MON +"gfaerie.c")->move(room);
    clone_object(ZIG_MON +"gfaerie.c")->move(room);
    clone_object(ZIG_MON +"gfaerie.c")->move(room);

    filter(all_inventory(ENV(TO)),
	&->id(FAERIE_ID))->defend_altar(TP);

}

public void
init()
{
    ::init();

    add_action(do_drink, "drink");
}

/*
 * Below called by the Green Faerie for letting players remove names
 * from someone else.
 */

public int forget_name(object who, string forgotten)
{
    who->catch_msg("Your memory becomes foggy for a moment.\n");
    
    logrotate(ZIG_LOGS + "mizrun_forgets",
    time2format(time(), "dd mmm yyyy tt: ") +
    who->query_real_name() + " forgot " + forgotten + "\n",
        200000, 3);
	return who->remove_remembered(forgotten);
}


private static int alarm;
private static mapping m_forget = ([]);

public void
delay_forget()
{
    alarm = 0;

    /* Looking for these people to remove names from. */
    foreach(string who, string *arr : m_forget)
    {
	    object tmp = find_player(who);

	    /* Player not awake? */
	    if (!objectp(tmp))
    	    continue;

    	/* Remove this list of names. */
    	foreach(string me : arr)
        {
            forget_name(tmp, me);
        }

	    /* Remove our entry. */
	    m_delkey(m_forget, who);
    }

    /* Still some left, restart alarm. */
    if (m_sizeof(m_forget))
    {
	    alarm = set_alarm(DELAY, 0.0, delay_forget);
    }
}

public int
gf_forget(string forgetter, string forgotten)
{
    object tmp;

    /* No input == no ouput */
    if (!forgotten || !forgetter || !strlen(forgetter) 
            || !strlen(forgotten))
	return 0;

    /* Player in the realms already? */
    if (objectp(tmp = find_player(forgetter)))
    {
        return forget_name(tmp, forgotten);
    }

    /* Add to delayed removal list. */
    if (m_forget[forgetter])
    {
	if (!IN_ARRAY(forgotten, m_forget[forgetter]))
	    m_forget[forgetter] += ({ forgotten});
    }
    else
    {
	m_forget[forgetter] = ({ forgotten });
    }

    /* Start delayed removal. */
    if (!alarm)
	alarm = set_alarm(3.0, 0.0, delay_forget);

    return 1;
}
