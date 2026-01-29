/* This file has been modified with text suggestons for Dust from
 * Azireon.  */
/*

    Modified: 11 June 2003, by Bleys
        - Updated to use modern inherit and includes.
        - Now logs to the correct log file.

    Modified: 1 Sept 2008 by Novo
        - Updated to use correct zodiac.h inherit.
*/

#include "/d/Terel/include/Terel.h"

inherit STDROOM;

#include "/d/Terel/include/zodiac.h"
#include "/d/Terel/include/quest_bits.h"
#include <poison_types.h>
#include <stdproperties.h>
#include <ss_types.h>

#define COLDIR MANSION + "colors/"
/*
 * It contains a hint for teh secret door
 * There are several hints spread, this is
 * hint number HINT_INDEX
 */
#define HINT_INDEX 0

/*
 * The following macros are intended to prevent lines from wrapping
 * around the screen, and avoid the wizard from having to put in explicit 
 * \n's.
 */


/*
 * this_hint is the hint stored inthis room
 */
#define this_hint (calc_hint(0))
int death_present;
object death;
object book;


create_room()
{
    death_present = 0;	/* We must call him first */

    set_long("@@long_desc");
    set_short("a black room with red windows");

    add_item(({"wall","walls","ceiling","floor","velvet"}),
	BS("The walls, the floor and the ceiling are covered " +
		"with heavy, black velvet.\n"));
    add_item("pentagram",
	BS("This pentagram on the book appears in scarlet-red color. " +
	   "It reminds you of the legend about the Red Death: " +
           "Centuries ago, Red Death ruled over this area. " +
           "Some wealthy people had retired to this place to " +
           "protect themselves from the Red Death's power.  Their " +
           "attempt turned out to be in vain and they too lost their " +
           "lives to it.  Somehow, you think he may still linger here " +
           "because you have heard that many dark cults still hold " +
           "their rites here to this day.\n"));

    add_item(({"window","glass","glasses"}),
	BS("The scarlet red glass of the window makes the " +
		"room seem to be filled with blood.\n"));
    add_cmd_item(({"death","red death"}),
		 "please",
		 BS("Yes, but HOW you want to please the Red Death? " +
                "He surely expects you to sacrifice " +
                "everything to him...\n"));

    add_prop(ROOM_I_NO_MAGIC, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
    add_prop(ROOM_I_NO_TELEPORT, 1);
    add_prop(ROOM_I_NO_STEAL, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);

    add_exit(COLDIR + "col_23", "east", "@@check_death");
    book = clone_object(DUST_DIR + "black_book");
    book->move(this_object());
}

init()
{
    ::init();
    add_action("praise_death","praise");
    add_action("praise_death","worship");
    add_action("sacrifice","sacrifice");
    add_action("sacrifice","offer");
}

void
reset_room()
{
    if (death_present)
	death->remove_object();
    death_present = 0;
}

int
check_death()
{
    if (death_present)
    {
   write(BS("You find yourself unable to move in the presence " +
             "of the Red Death.\n"));
	return 1;
    }
    return 0;
}

call_death()
{
    object	poison;
    int		damage;

    seteuid(getuid()); /* Otherwise we can't clone in a vbfc */
    if (death_present)
    {
	write(BS("But the Red Death is already present.\n"));
	return;
    }
    death_present++;

    write(BS("The whole room trembles as a shape suddenly seems to " +
     "appear from behind the scarlet window.  You know it must be " +
     "the Red Death.\n"));
    say(BS("The whole room trembles as a shape suddenly seems to " +
     "appear from behind the scarlet window.  You know it must be " +
     "the Red Death.\n"));
    death = clone_object(DUST_DIR + "red_death");
    death->move(this_object());
    poison = clone_object("/std/poison_effect");
    poison->move(this_player());
    poison->set_time(300);
    /* slow poison, so the player can get the antidote in times */
    poison->set_interval(30);
    poison->set_strength(100);
    /* if all hits hit, then nearly kill the player... but
     * damage is at least 100
     */
    damage = this_player()->query_max_hp() / 6;
    if (damage < 200) damage = 200;
    poison->set_damage(({POISON_HP,damage}));
    poison->set_poison_type("red death");
    poison->start_poison();
    write(BS(
    "As the Red Death enters the room, a foul pestilent odor slowly " +
    "fills your nostrils.  As the Red Death infiltrates your body, " +
    "you know you will soon die.  Your only hope is to plead with " +
    "the Red Death himself.\n"));
    return;
}

string
quest_solved()
{
    int	exp_to_give;

    seteuid(getuid());
    if (this_player()->test_bit("Terel",QUEST_DEATH_GROUP,QUEST_DEATH_BIT))
	return(" ");
    this_player()->set_bit(QUEST_DEATH_GROUP,QUEST_DEATH_BIT);
    exp_to_give = this_player()->query_exp();
    if (exp_to_give > QUEST_DEATH_EXP)
	exp_to_give = QUEST_DEATH_EXP;
    this_player()->add_exp(exp_to_give,0);
    /*
    write_file(QUEST_LOG,this_player()->query_name() +
	" solved death-quest (" + ctime(time()) + ")\n");
    */
    write_file(QUEST_LOG, TP->query_name() + " solved " +
        "the Zodiac red component (death-quest) (" +
        ctime(time()) + ")\n");
    return(" Suddenly you feel much more experienced and " +
	"enlightened than before...\n");
}



int
praise_death(string str)
{
    object antidote;
    object doorroom;
    int hint;

    notify_fail("Good idea, but who you want to praise?\n");
    if (str != "death" && str != "red death") return 0;

    hint = this_hint;

    if (death_present) {
	seteuid(getuid());
	death->remove_object();
	antidote = clone_object(DUST_DIR + "antidote");
	antidote->move(this_object());
	death_present--;
	say("Suddenly, the Red Death magically disappears...\n");
	write(BS("The Red seems to transform into " +
		"the shape of " + SIGPR[hint] + SIGEQ[hint] +
		", but it lasts for such a short moment that you aren't " +
		"sure if it wasn't just an illusion. Finally he vanishes " +
		"more and more and finally disappears into the red " +
		"window as quickly as he appeared. " + quest_solved() + "You " +
		"notice that he left something for his worshipper.\n"));
	return 1;
    }
    notify_fail(BS("There's no Death in this room, but you feel his " +
		"presence. Maybe you better leave before he arrives!\n"));
    return 0;
}

int
sacrifice(string str)
{
    object *inv;
    int i;

    notify_fail("Good idea, but that's not enough... He wants all of you!\n");
    if (str != "all") return 0;
    if (death_present)
    {
	inv = deep_inventory(environment(this_player()));
	for (i=0; i<sizeof(inv); i++)
	    if ((!living(inv[i])) &&
		inv[i] != death &&
		inv[i] != book)
		(inv[i])->remove_object();
	say("The Red Death laughs and takes everything in this room " +
		"as sacrifice.\n");
	write("The Red Death takes everything in this room as a sacrifice.\n");
	write(BS("He laughs, as if he'd like to say: why didn't you just " +
		"praise me...?\n"));
	return(praise_death("death"));
    }
    notify_fail("There's nobody to sacrifice anything to.\n");
    return 0;
}


string
long_desc()
{
    return (BS("Heavy, black velvet covers the walls, floor, and " +
           "ceiling of this room, except for a large window, made of " +
           "scarlet glass, on one wall.  The light shining through it " +
           "gives you a strange impression:  the room seems to " +
           "be filled with blood.\n") +
	   "In the middle of the room, a black book is floating.\n" +
		  ( death_present ?
		    "The Red Death is here and watches you suspiciously.\n"
		    : ""));

}

