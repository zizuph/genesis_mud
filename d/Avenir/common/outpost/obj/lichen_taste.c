// file name:   ~Avenir/common/outpost/obj/lichen_taste.c
// creator:	Kazz, poisoning structure is a thinned version of Boriska's
//		food poisoning.
// last update: Feb 1995
//              Nov 1995: raised msg-between-time from 60 to 180
//                        decreased taste-life from 10000 to 5000
//              Denis, Mar'2001 Fixed run-time error in before special_damage
//                              was called.
// purpose:     lichen 'fun' poisoning
// note:        lichen gives bad breath and reminds player that they had
//		something nasty in their mouth.
// bug(s):
// to-do:     	* other ways to get rid of it besides timing out?
//		* When the outpost guard-water quest (future) is
//		  finished, guard can give cancel food.

inherit "/std/poison_effect";

#include <poison_types.h>
#include <macros.h>


#define TR(x) tell_room(environment(poisonee), (x), poisonee);

// NEW_ID and OLD_ID are used for altering damage for existing poison
//object and destructing new one when more than one poison is consumed.
#define NEW_ID "_avenir_lichen_taste_new"
#define OLD_ID "_avenir_lichen_taste_old"

#define LOG_FILE "/d/Avenir/log/outpost/lichen_taste"

#define WRITE_LOG(x) (write_file(LOG_FILE, ctime(time()) + " " + \
	     this_player()->query_name() + "(" + \
	     this_player()->query_wiz_level() + "," + \
	     this_player()->query_average_stat() + ")" + (x)))

// #define DEBUG will cause dump_array messages written to player
// including mortals.. do it on the copy..
#undef DEBUG

void start_me();

void
create_poison_effect()
{
    if (!IS_CLONE)
	return;

    set_name ("lichen_taste");
    set_short ("lichen_taste");
    remove_name ("poison");  	// prevent people from doing 'drop poisons'
    add_name (NEW_ID);

    set_interval(180);
    set_time(5000);			// duration of 'taste' poison
    set_damage( ({ POISON_USER_DEF, 0 }));

    set_poison_type("food");
    set_silent(2);	 // no puking, shivering, messages about poisoning
    seteuid(getuid());
    set_alarm(2.0, 0.0, start_me);
}  

void
start_me()
{
    object op;

    if (environment()) 
	op = present(OLD_ID, environment());
    seteuid(getuid());

    if (!op)  // no poisons encountered. Just start me.
    {
	::start_poison();

	remove_name(NEW_ID);
	add_name(OLD_ID);

	if (!query_recovery())  // write log entry only upon first poisoning
	{
	    WRITE_LOG(" ate tunnel lichen.\n");
	}
	else
	{
	    poisonee->catch_msg (
	      "Your mouth is still recovering from something you ate.\n");
	}
	return;
    }

    // player has already eaten some lichen.
    poisonee->catch_msg("You add more lichen to the surfaces of your mouth.\n");

    remove_object();
    return ;
}

// lots of smelly, nasty tasting things.
void
special_damage(int damage)
{
    int msg_num = random( 7 );

    // player and room tells
    switch (msg_num)
    {
    case 0:
	poisonee->catch_msg("You smell something horrible.\n");
	TR(QCTNAME(poisonee) + "'s breath smells disgusting.\n");
	break;
    case 1:
    	poisonee->catch_msg(
	    "Your tongue feels like something is crawling on it.\n" );
	TR(QCTNAME(poisonee) + "'s mouth twitches.\n");
	break;
    case 2:
	poisonee->catch_msg("Your tongue goes numb momentarily.\n" );
	break;
    case 3:
	poisonee->catch_msg("Your entire mouth feels oily and slimy.\n");
	TR(QCTNAME(poisonee) + "'s breath smells like pond scum.\n");
	break;
    case 4:
	poisonee->catch_msg("Your tongue spasms briefly.\n");
	TR(QCTNAME(poisonee) +
	  " starts to say something and then stops.\n");
	break;
    case 5:
	poisonee->catch_msg("You taste ... a putrid dead rat.\n");
	TR(QCTNAME(poisonee) + " looks like he might puke.\n");
	break;
    case 6:
	poisonee->catch_msg("You taste ... moldy leather on your tongue.\n");
	TR(QCTNAME(poisonee) +
	  "'s mouth smacks like he's tasting something.\n");
	break;
    case 7:
	poisonee->catch_msg("You taste ... urine.\n");
	TR(QCTNAME(poisonee) + " grimaces and shudders.\n");
	break;

    default:
	poisonee->catch_msg("Your mouth tastes like slimy feet.\n");
	break;
    }
}  // special_damage()

// called when poison is removed.
void
timeout()
{
    poisonee->catch_msg("Your mouth and tongue feel normal again.\n");
    ::timeout();
}
