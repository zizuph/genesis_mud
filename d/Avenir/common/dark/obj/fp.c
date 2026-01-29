//-*-C++-*-
// file name:   ~Avenir/common/dark/obj/fp.c
// creator(s):  Boriska, nasty descriptions by Tepisch.
// last update: Jan 15 1995
// 		Lucius 2008: Minor cleanups, adjusted the damage type
// 			     to stop the runtime errors.
//      Lilith Apr 2022: to add Avenir privvies.
// purpose:     food poisoning object
// note:        Poisoning occurs upon eating one or more pieces of
//              rotten meat, obj/r_meat.c .
//              See ~Avenir/QUESTS/food_poisoning.
// bug(s):
// to-do:     

inherit "/std/poison_effect";
inherit "/d/Avenir/inherit/quest";

#include <poison_types.h>
#include <macros.h>

// contains poison ID for Gelan lavatories to recongize us.
#include "/d/Avenir/include/food_poison.h"

#define TR(x) tell_room(environment(poisonee), (x), poisonee);

// rooms where poison can be healed.. yes, yes, my workroom is like
// toilet...
#define TOILETS ({ "/d/Calia/gelan/rooms/lavatory_male", \
		    "/d/Calia/gelan/rooms/lavatory_female", \
		    "/d/Calia/gelan/rooms/lavatory_neutral", \
            "/d/Avenir/common/outpost/tower_privvy"	})

// NEW_ID and OLD_ID are used for altering damage for existing poison
//object and destructing new one when more than one poison is consumed.
#define NEW_ID "_avenir_food_poison_new"
#define OLD_ID "_avenir_food_poison_old"

// damage messages range when no hp damage
#define STANDARD_DAMAGE 10

// full damage messages range
#define FULL_DAMAGE 15

#define LOG_FILE "/d/Avenir/log/quest/food_poisoning"

#define WRITE_LOG(x) (write_file(LOG_FILE, ctime(time()) + " " + \
	     this_player()->query_name() + "(" + \
	     this_player()->query_wiz_level() + "," + \
	     this_player()->query_average_stat() + ")" + (x)))

// these are written to the player first.
static string *prologue = ({
  "You feel an ominous twitch in your stomach.\n",
  "You feel a twitching in your stomach.\n",
  "Your tummy is a bit upset.\n",
  "Your stomach seems to be doing somersaults.\n",
  "You wish you had left your stomach at home.\n",
  "You feel really sick.\n",
  "You feel a bad cramping in your gut.\n",
  "Your bowels feel like they are turning to liquid.\n",
});

private void start_me(void);

static int prologue_len = sizeof(prologue);
static int dams = STANDARD_DAMAGE;
static int step = 0;

public void
create_poison_effect(void)
{
    setuid();
    seteuid(getuid());

    set_name("food_poisoning");
    set_short("food_poisoning");
    remove_name("poison");  // I do not like people doing 'drop poisons'
    add_name(NEW_ID);
    add_name(AVENIR_FOOD_POISON_ID);

    set_interval(60);
    set_time(20000);  
    set_damage( ({ POISON_USER_DEF, 0, POISON_MANA, 20, POISON_FATIGUE, 10 }));
    set_strength(60);  // strength is increased when more poisons consumed.

    set_poison_type("food");
    set_silent(2); // no puking, shivering, messages about poisoning

    if (IS_CLONE)
	set_alarm(2.0, 0.0, start_me);
}  

private void
start_me(void)
{
    object op;
    int *old_damage;

    if (environment()) 
	op = present(OLD_ID, environment());

    if (!op)  // no poisons encountered. Just start me.
    {
	start_poison();

	remove_name(NEW_ID);
	add_name(OLD_ID);

	if (!query_recovery())  // write log entry only upon first poisoning
	{
	    step = 0;
	    WRITE_LOG(" was poisoned.\n");
	}
	else
	{
	    poisonee->catch_tell(
	      "You are still having problems with your stomach.\n");
	    step = prologue_len; // no prologue when recovering
	}
	return;
    }

    // player already poisoned. Change the strength of existing
    // poison and self-destruct.
    old_damage = op->query_damage();

    // each additional poison adds 20 to the strength of existing one
    // till strength of 100 is reached.
    if (op->query_strength() < 100) // upper limit not reached yet
    {
	op->set_strength(op->query_strength() + 20);
	// increase mana and fatigue damage
	old_damage[3] += 20;
	old_damage[5] += 20;
    }

    // strength at max already, meaning more than 2 poisons consumed.
    if (op->query_strength() >= 100)
    {
	if (sizeof(old_damage) == 6) // hp damage has not been added yet
	{
	    op->add_damage(({ POISON_HP, 150 }));
	    op->set_dams(FULL_DAMAGE); // add more funny messages to chose from
	}
	else
	{
	    old_damage[7] += 50; // increase hp damage by 50
	    op->set_damage(old_damage);
	}
    }
    remove_object();
}

// this function is called in lavatories
void
heal()
{
    // can be healed in Calia and Avenir.
    if (poisonee &&
	member_array(file_name(environment(poisonee)), TOILETS) > -1)
    {
	WRITE_LOG (" was healed in lavatory.\n");

	if (!poisonee->test_bit("avenir", GROUP, BIT)) { // give them some XP
	    reward_quest("Food Poisioning", poisonee, GROUP, BIT, XP);
	    WRITE_LOG(" " + XP + " XP handed out.\n");
	}
	set_alarm(1.0, 0.0, remove_object);
    }
}

// lots of nasty stuff.
void
special_damage (int damage)
{
    if (step < prologue_len)
    {
	poisonee->catch_tell(prologue[step]);
	step++;
	return;
    }

    switch (random(dams))
    {
    case 0:
	poisonee->catch_tell("Your face turns greenish-blue.\n");
	TR(QCTPNAME(poisonee) + " face turns greenish-blue.\n");
	break;
    case 1:
	poisonee->catch_tell("A rumble emanates from deep within you.\n");
	TR("A nauseous sound emanates from " + QTNAME(poisonee) + ".\n");
	break;

    case 2:
	poisonee->catch_tell("You feel uncomfortable.\n");
	TR(QCTNAME(poisonee) + " starts to walk kinda funny.\n");
	break;

    case 3:
	poisonee->catch_tell("You cradle your stomach.\n");
	TR(QCTNAME(poisonee) + " rubs " + poisonee->query_possessive() +
	  " stomach.\n");
	poisonee->command ("fart");
	break;

    case 4:
	poisonee->catch_tell("Something you ate does not agree with you.\n");
	TR(QCTNAME(poisonee) + " looks as if something "
	  + poisonee->query_pronoun() + " ate does not agree with " +
	  poisonee->query_objective() + ".\n");
	break;

    case 5:
	poisonee->catch_tell("You'd better go somewhere to relieve yourself.\n");
	TR(QCTNAME(poisonee) + " looks like " + poisonee->query_pronoun() +
	  " has to go.\n");
	break;

    case 6:
	poisonee->catch_tell("You get a bad headache trying to think about " +
	  "anything but your rebelling stomach.\n");
	break;
    case 7:
	poisonee->catch_tell("You really could use a toilet.\n");
	TR(QCTNAME(poisonee) + " gets an expression on " +
	  poisonee->query_possessive() +
	  " face showing " + poisonee->query_pronoun() +
	  " really could use a toilet.\n");
	break;
    case 8:
	poisonee->catch_tell(
	  "You discover that walking is really hard work.\n");
	TR(QCTNAME(poisonee) + " barely lifts " + poisonee->query_possessive() +
	  " legs while walking.\n");
	break;

    case 9:
	poisonee->catch_tell(
	  "You barely find the strength to make your next step.\n");
	TR(QCTNAME(poisonee) + " hardly stays on " +
	  poisonee->query_possessive() + " feet.\n");
	break;
    default:
	poisonee->catch_tell(
	  "You feel that your sickness might turn to something more serious.\n");
	TR(QCTNAME(poisonee) + " looks really ill.\n");
	break;
    }
}  

// called when poison is removed.
void
timeout()
{
    poisonee->catch_tell("You feel healthy again.\n");
    ::timeout();
}

// called from new-arriving poison to change a set of possible
// damage messages in the old (and remaining) one
void
set_dams(int d) { dams = d; }

// save and recover dams variable storing the range of damage messages
void
init_poison_recover(string args) {sscanf (args, "%d", dams);}

string
query_poison_recover() { return sprintf("%d", dams); }

