// OBJECT:  cat fur

    /* Calia Domain

    HISTORY

    [99/10/24] Created by Sheytansha.

    PURPOSE

    To be used in conjunction with the black_cat.c, for Hallowe'en.
    This object will dispense a bad luck timer to players as they
    "look at" or "examine" the cat.

    */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>

// GLOBAL VARIABLES

/* The Player_Luck_Value works very simply:  as the number increases the
player's luck gets worse. The Luck_Sequence is used to control the worst
effects only. */

int Player_Luck_Value = 0;
int Luck_Sequence = 0;

// FUNCTIONS

// Function:  see_a_flea()

/*

Purpose:  make a flea (not a real object) jump from the victim.  He doesn't see
it, but his comrades do.

Arguments:  none

Returns:  nothing

*/

void
see_a_flea()

{

    object victim = environment();

    tell_room(environment(victim),
	"A tiny black flea jumps off " + QTNAME(victim) +
	" and disappears into the distance.\n",
	({victim}));

}

// Function:  get_very_bad_luck()

/*

Purpose:  inflict the worst level of bad luck.  The function calls itself
repeatedly, relentlessly, mercilessly!  Well, at least for a little while.
Once this function is invoked, Luck_Sequence takes over as the controlling
variable; Player_Luck_Value is simply used as a selector to determine whether
the victim gets fleas or a hairball.

Arguments:  none

Returns:  nothing

*/

void
get_very_bad_luck()

{

    object victim = environment();      /*  whom are we doing it to?  */
    object room = environment(victim);  /*  where is he now?  */
    string v_pronoun = victim->query_pronoun();
    string v_objective = victim->query_objective();
    string v_possessive = victim->query_possessive();
    int n = Player_Luck_Value % 2;     /*  must match number of cases  */

    switch (n)

    {

	/*
	 *  Fleas    
	 */

	case 0:

	write(
	    ({
	    "You feel an itch at the back of your neck.\n",
	    "You find a tiny flea crawling on your arm! You flick" +
	    " it off, and it quickly jumps out of sight.\n",
	    "Several fleas start biting your legs, and you have" +
	    " to bend over and inspect yourself carefully to" +
	    " pick them all off.\n",
	    "Fleas start crawling all over your body" +
	    " and biting you mercilessly! You squat on the" +
	    " the ground, remove everything you're wearing," +
	    " and scratch all over, picking and shaking the fleas" +
	    " off one by one.\n",
	    "A virtual army of fleas covers your body - where" +
	    " could they have been hiding? They bite the areas" +
	    " that are already numb from being" +
	    " thoroughly bitten, and apparently satisfied" +
	    " that they've drained everything that they can get" +
	    " from you, they hop off in a steady stream in" +
	    " search of more succulent fare.\n"
	    })[Luck_Sequence]);

	tell_room(room,
	    QCTNAME(victim) + " " +
	    ({
	    "cranes " + v_possessive + " head back and rocks it" +
	    " from side to side as if " + v_pronoun + " felt a" +
	    " slight tickle at the back of " + v_possessive + " neck.\n",
	    "finds a tiny flea crawling on " + v_possessive +
	    " arm! " + capitalize(v_pronoun) + " flicks" +
	    " it off, and it quickly jumps out of sight.\n",
	    "bends over to ispect the backs of " + v_possessive +
	    " legs and finds several fleas" +
	    " feasting there! " + capitalize(v_pronoun) +
	    " takes a few minutes to pick them all off.\n",
	    "suddenly seems to be covered with fleas, and" +
	    " they are obviously biting " + v_objective +
	    " mercilessly! " + capitalize(v_pronoun) +
	    " is forced to squat on the ground and pick over" +
	    " every inch of " + v_possessive +
	    " body to get rid of them.\n",
	    "is buried under a virtual army of fleas - where" +
	    " could they have come from? They crawl over every part" +
	    " of " + v_possessive + " body, covered or not," +
	    " and when they've had their fill, they take off in" +
	    " a steady stream and disappear in search of other prey.\n"
	    })[Luck_Sequence],
	    ({victim}));

	/*
	 *  The following operation is just an extra effect timed to conicide 
	 *  with the fourth text string above.    
	 */

	if (Luck_Sequence == 3)

	{

	    victim->command("$remove all");

	}

	/*
	 *  The following function is just a trivial addition to make the flea 
	 *  curse a little more annoying.    
	 */

	set_alarm(35.0, 0.0, see_a_flea);

	break;

	/*
	 *  Hairball    
	 */

	case 1:

	write(
	    ({
	    "Your stomach seems to be a little upset.\n",
	    "Wow... What did you eat? Your stomach is protesting greatly" +
	    " and making strange gurgling noises.\n",
	    "Your stomach continues to churn and twist horribly, and you" +
	    " think you're going to be sick!\n",
	    "You feel all the gears in your stomach reverse, and you start" +
	    " making a sick half-coughing, half-gagging noise. Whatever it" +
	    " is, it's making a major production of coming back up.\n",
	    "Finally with a great amount of effort, you lean over and puke" +
	    " out whatever was on your stomach. Turns out it wasn't" +
	    " something you ate after all, it was a big ol' hairball.\n"
	    })[Luck_Sequence],);

	tell_room(room,
	    QCTNAME(victim) + " " +
	    ({
	    "puts a hand on " + v_possessive + 
	    " stomach and groans quietly.\n",
	    "'s stomach is grumbling and gurgling and making all sorts of" +
	    " interesting noises. It's loud enough you can hear it from" +
	    " a few feet away!\n",
	    "blanches noticably as " + v_pronoun + " puts a hand over " +
	    v_possessive + " stomach. " + capitalize(v_pronoun) + " looks" +
	    " like " + v_pronoun + "'s going to be sick.\n",
	    "'s eyes bug out of " + v_possessive + " head, as " + v_pronoun +
	    " quickly clamps a hand over " + v_possessive + " mouth. Seconds" +
	    " later " + v_pronoun + " starts making a truly obnoxious" +
	    " half-coughing, half-gagging noise. You start thinking you" +
	    " might want to back up, just in case...\n",
	    "continues the obscene action until finally, " + v_pronoun + 
	    " doubles over and pukes up a great big hairball! All this" +
	    " time you thought only cats did that!\n"
	    })[Luck_Sequence],
	    ({victim}));


    }

    /*
     *  Continue the sequence at 90-second intervals.  If the sequence is 
     *  finished, schedule it to start all over again in 20 minutes.    
     */

    Luck_Sequence += 1;

    if (Luck_Sequence < 5)

    {

	set_alarm(90.0, 0.0, get_very_bad_luck);

    }

    else

    {

	Luck_Sequence = 0;
	set_alarm(1200.0, 0.0, get_very_bad_luck);
      Player_Luck_Value += 1;

    }

}

// Function:  get_bad_luck()

/*

Purpose:  generate the bad luck effect.

Arguments:  none

Returns:  nothing

*/

void
get_bad_luck()

{

    object caramel;
    object victim = environment();      /*  whom are we doing it to?  */
    object room = environment(victim);  /*  where is he now?  */
    string v_pronoun = victim->query_pronoun();
    string v_objective = victim->query_objective();
    string v_possessive = victim->query_possessive();
    int n;                              /*  general-purpose counter  */

    switch (Player_Luck_Value)

    {
	/*
	 *  The lowest levels simply invoke a trivial standard emote.  The 
	 *  vargument to 'random' must match the number of entries in the text
	 *  array.    
	 */

      case -1000..0:
	
      caramel = clone_object("/d/Calia/weenware/caramel.c");
      caramel->move(victim);
      write ("In front of your eyes, an apparition of an old lady" +
          " holding a jack'o'lantern appears. She silently motions" +
          " for you to come closer, and as you do, she reaches into" +
          " the jack'o'lantern and pulls out a candy! She drops it" +
          " into your outstretched hand, and vanishes from sight.\n");
  
      tell_room(room, "Suddenly, an apparition of an old" +
          " woman holding a jack'o'lantern appears before " + 
          QTNAME(victim)+ "! She motions for " + v_objective +
          " to come closer, and as " + v_pronoun + " does," +
          " the old lady reaches into the jack'o'lantern and" +
          " pulls out a candy! She drops it into " + v_possessive +
          " hand and vanishes from sight.\n", ({victim}));

      remove_object();

      break;

	case 1..4:

	victim->command(
	  ({
	  "sneeze",
	  "hiccup",
	  "drool",
	  "fart",
	  "burp",
	  })[random(5)]);

      remove_object();

	break;

	/*
	 *  The next level inflicts an original effect.  To keep the 'write' 
	 *  and 'tell_room' effects in synch, they both use variable 'n', whose
	 *  random range must match the number of elements in the text arrays
	 *  in this section.    
	 */

	case 5..8:

	n = random(2);

	write(
	    ({
	    "You suddenly trip over apparently nothing at all and" +
	    " fall flat on your face! You sheepishly get back on" +
	    " your feet and briefly dust yourself off," +
	    " hoping that nobody noticed.\n",
	    "You sneeze abruptly and unexpectedly! Your" +
	    " head feels much clearer, but a moment later you" +
	    " notice the slimy trail leading down from your nose" +
	    " to your chin. You wipe it away as casually as" +
	    " you can manage.\n"
	    })[n]);

	tell_room(room,
	    QCTNAME(victim) + " " +
	    ({
	    "suddenly trips over " + v_possessive + " own feet" +
	    " and falls flat on " + v_possessive +
	    " face! " + capitalize(v_pronoun) +
	    " gets back on " + v_possessive +
	    " feet, briefly dusts " + v_objective + "self off, and" +
	    " tries to act as if nothing at all had happened.\n",
	    "lets loose a forceful sneeze, then stands" +
	    " around looking dimwitted for a" +
	    " moment before " + v_pronoun +
	    " notices the slimy trail leading from " + v_possessive +
	    " nose to " + v_possessive +
	    " chin. " + capitalize(v_pronoun) +
	    " does " + v_possessive +
	    " best to look casual as " + v_pronoun +
	    " wipes it away.\n",
	    })[n],
	    ({victim}));

      remove_object();

	break;

	/*
	 *  The section below invokes the worst level of bad luck through a 
	 *  separate function.    
	 */

	default:

	Luck_Sequence = 0;
	set_alarm(90.0, 0.0, get_very_bad_luck);

    }

}

// Function:  add_luck_level(amount)

/*

Purpose:  adjust the bad luck level of this object (and of the player
possessing it); the value may be specified as positive to increase the effect
or negative to decrease it.

Arguments:  integer indicating the luck adjustment amount.

Returns:  nothing

*/

void
add_luck_level(int amount)

{

    Player_Luck_Value += amount;

}

// Function:  set_luck_level(amount)

/*

Purpose:  set the luck level of this object (and of the player possessing it).

Arguments:  integer indicating the desired luck value.

Returns:  nothing

*/

void
set_luck_level(int amount)

{

    Player_Luck_Value = amount;

}

// Function:  query_luck_level()

/*

Purpose:  allow an external object to query the current luck level.

Arguments:  none.

Returns:  integer, higher numbers indicate worse luck.

*/

int
query_luck_level()

{

    return Player_Luck_Value;

}

// Function:  enter_env(inv, from)

/*

Purpose:  this function is automatically called when this object enters an
environment.  It is used here to start the timer for the bad luck effect.

Arguments:  none

Returns:  nothing

*/

void
enter_env(object env, object from)

{

    ::enter_env(env, from);

    if (interactive(env))

    {

	set_alarm(250.0, 0.0, get_bad_luck);

    }

}

// Function:  query_recover()

/*

Purpose:  returns a zero to prevent this object from ever recovering.

Arguments:  none

Returns:  0

*/

int
query_recover()

{

    return 0;

}

// OBJECT DEFINITION

void
create_object()

{

    set_name("cat fur");
    add_name("fur");
    set_short("small clump of black cat fur");
    set_long("You've got dozens of short black cat hairs all over you.\n");

    /*
     *  PROPERTIES    
     */

    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_M_NO_DROP, "You obviously never owned a cat, have you?\n");


    setuid();
    seteuid(getuid());


}
