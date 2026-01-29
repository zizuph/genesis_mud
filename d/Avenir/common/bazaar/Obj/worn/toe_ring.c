// -*-C++-*-
// file name:	/d/Avenir/common/bazaar/Obj/worn/toe_ring.c
// creator(s):  	Sirra	
// last update:	Febuary 1998(created)
// purpose:       ring to be worn on the toe with added emotes
// to-do:     	-limit number of time armour will reboot.
#pragma strict_types

inherit "/lib/keep";
inherit "/std/object";
inherit "/lib/commands";
inherit "/lib/wearable_item";

#include <composite.h>
#include <wa_types.h>		//weapon types
#include <stdproperties.h>	//properties
#include <macros.h>
#include <adverbs.h>		//parse_adverb_with_space

int load;

int do_toewig(string str);
int do_toehelp();

void
create_object()
{
    set_name("toe-ring");
    add_name("ring");
    add_name("TOE_RING");
    add_adj(({"oval", "onyx", "toe"}));
    add_pname(({"clothes", "clothing"}));

    set_short("oval onyx toe-ring");
    set_long("A black oval onyx toe-ring with an intricate "
      + "ivory band, made to wear around "
      + "your big toe. The band is ornately "
      + "decorated with symbols, representing "
      + "a life of leisure and luxury.\n"
      + "An inscription on the inside of the band "
      + "reads: type 'toehelp'.\n");

    config_wearable_item(A_R_FOOT, 1, 1, this_object());
    set_keep(1);

    add_prop(OBJ_I_VALUE, 75);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_WEIGHT, 300);

    add_item(({"onyx", "stone"}),
      ("A deep black stone shaped like an "
	+ "owl's eye. It's shiny luster "
	+ "seems to speak of unknown mysteries "
	+ "and forgotten dreams.\n"));

    add_item("band", "An ornate ivory band "
      + "with a black oval onyx inset. Someone "
      + "has taken alot of time to craft this. "
      + "You recognize the symbols for leisure and "
      + "luxury expertly designed along the sides.\n");
	  
   if (IS_CLONE)
      set_item_expiration();  	  
}

int
init()
{
    ::init();
    add_action(do_toewig, "toewig");
    add_action(do_toehelp, "toehelp");
}

//Modeled after the bow() emote in cmd/std/soul
//Player can wiggle their toes spontaneously
int
do_toewig(string str)
{
    object *oblist;
    string *how, *wow;

    //Defaults if player doesnt specify an adverb.
    how = parse_adverb_with_space(str, "spontaneously", 0);
    wow = parse_adverb_with_space(str, "defiantly", 0);

    if (!query_worn())
    {   
	write("You must be wearing the toe-ring.\n");
	return 1;
    }


    //player types "toewig", or "toewig <adverb>"
    if (!stringp(how[0]))
    {
	write("You wiggle your beautifully clad toes" 
	  + how[1] + ".\n");
	allbb(" wiggles " + this_player() -> query_possessive()
	  + " beautifully clad toes" + how[1] + ".", how[1]);
	return 1;
    }

    oblist = parse_this(wow[0], "[in] %l");

    if (!sizeof(oblist))
    {
	notify_fail("Toewig [how] in whose face?\n");
	return 0;
    }

    //player types "toewig <player>", or "toewig <adverb> <player>"

    actor("You wiggle your beautifully clad toes" + wow[1] + " in",
      oblist, "'s face.");
    all2actbb(" wiggles " + this_player() -> query_possessive()
      + " beautifully clad toes" + how[1] + " in", oblist, 
      "'s face.", wow[1]);
    targetbb(" wiggles "+ this_player() -> query_possessive()
      + " beautifully clad toes" + wow[1] + " in your face.", 
      oblist, wow[1]);

    return 1;
}


//player types "toehelp" and gets help on syntax.
int
do_toehelp()
{
    write("For some fancy footwork, try the following:\n"
      + "toewig\n"
      + " -wiggle your toes spontaneously.\n\n"

      + "toewig <adverb>\n"
      + " -personalize the wiggle.\n\n"

      + "toewig <player>\n"
      + " -wiggle your toes defiantly in someone's face!\n\n"

      + "toewig <adverb> <player>\n"
      + " -wiggle your own way in someone's face!\n");

    return 1;
}

//Modeled after /d/Avenir/common/bazaar/Obj/worn/mencloaks.c"
mixed
wear(object ob)
{
    object tp = environment(this_object());

    if ( (tp != this_player()) || (ob != this_object()) )
	return -1;

    /* Successful wear */
    this_player() -> catch_msg("You slip the onyx toe-ring "
      + "over your right big toe, and wiggle it appreciatively.\n");

    tell_room(environment(tp), QCTNAME(this_player()) 
      + " slips an onyx toe-ring over "+ this_player()-> query_possessive()
      + " right toe, and wiggles it appreciatively.\n", tp);

    return 1;
}

//Modeled after /d/Avenir/common/bazaar/Obj/worn/mencloaks.c
mixed
remove(object ob)
{
    object tp = query_worn();

    if ( (ob != this_object() ) && (tp != query_worn()))
	return -1;

    /* Successful remove */
    if (!living(tp) )
	return 0;

    tp->catch_tell("You slip your onyx toe-ring "
      + "off your right big toe and wiggle it.\n");

    tell_room(environment(tp), 
      QCTNAME(tp) + " slips " + tp -> query_possessive()
      + " onyx toe-ring off " + tp -> query_possessive()
      + " right big toe and wiggles it.\n", tp);

    return 1;
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    wearable_item_leave_env(from, to);
}

public void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}


public string
query_recover()
{
    return MASTER + ":" + query_item_expiration_recover();  
}

/*
 * Function name: init_recover
 * Description  : When the object recovers, this function is called to set
 *                the necessary variables. 
 * Arguments    : string argument - the arguments to parse
 */
public void
init_recover(string arg)
{
    init_item_expiration_recover(arg);
}
