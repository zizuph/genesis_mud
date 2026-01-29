//-*-C++-*-
// Entrance to worm lair.
// Last changes by Boriska, Feb 24 96

inherit "/lib/unique";
inherit "/d/Avenir/common/dark/lair/lair_common";

#include "/d/Avenir/common/dark/dark.h"
#include "/d/Avenir/include/worm.h"
#include "/d/Avenir/smis/sys/statserv.h"

#define SLAB_ROOM (DARK + "l4/n26")
#define SLAB_RAISED (SLAB_ROOM->query_slab_raised())
#define SLAB_HELD (SLAB_ROOM->query_slab_held())

int damage_alarm = 0;

void
create_room()
{
    set_short("in the lair");
    set_long("Fire surrounds you. An intense heat makes rock "+
      "melt and molten rock boil. Nothing can stay solid in "+
      "this heat, yet some force, some great magic preserves "+
      "you. Your perspiration dries just as it reaches the "+
      "surface of your skin, leaving a fine salt-film on your "+
      "flesh. The only liquids around here are lava and boiling "+
      "acid, gathered in bubbling pools. High over your head "+
      "you see a black spot.\n");

    add_item ("spot", "It is a part of black rock slab.\n");
    add_item (({"slab", "passage"}), "@@slab_desc@@");
    add_item ("lava", "Red, hot molten rock.\n");
    add_item (({"acid", "pool", "pools"}),
      "The boiling acid is gathered in pools that fill the air "+
      "with poisonous steam.\n");
    add_item(({"flakes", "flake", "words", "blood"}), "@@blood_words@@");

    IN;
    add_prop (OBJ_S_SEARCH_FUN, "search_fun");

    add_exit (LAIR + "l2", "north");
}

string
slab_desc()
{
    if (SLAB_HELD)
	return "The slab seems to be held securely, allowing you to pass.\n";

    if (SLAB_RAISED)
	return "The slab is raised, revealing the passage, but is is "+
	    "too dangerous to pass through right now.\n";

    return "The heavy rock monolith is closing the only passage out of "+
	"here. It emits a low sound in response to your touch. You "+
	"wonder if it can be heard on the other side.\n";
}

string
blood_words()
{
    return "Your eyes fall on faded words written with blood:\n" +
	"I'm trap..d in .ere\n     B..are the W.rm\n   "+
	"K..l it .nd tak. the t...h then d.p them .. ..e acid pool " +
	"IT .. yo.. onl. hop.\nMier.n! My love, farew...\n";
}

int
do_knock(string str)
{
    if (!str || !parse_command(str, ({}), "'on' [the] 'slab' / 'rock'"))
	return notify_fail ("Knock on what?\n");

    if (SLAB_HELD || SLAB_RAISED)
    {
	write("The slab is too high for you to knock at.\n");
	return 1;
    }

    write("You knock on the slab, causing a loud sound. Dark "+
	"dark flakes of something on the slab remains on your fingers.\n");
    say(QCTNAME(this_player()) + " knocks on the slab.\n");
    tell_room(SLAB_ROOM, "You hear a faint sound as if somebody "+
      "is knocking on the slab from beneath.\n");

    return 1;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv (ob, from);

    if (!query_interactive(ob))
	return;

    if (file_name(from) == "/d/Avenir/common/dark/l4/n26")
	STATSERV_LOG_EVENT("Utterdark", "Entered the Worm lair");

    if (!damage_alarm)
	damage_alarm = set_alarm(60.0, 60.0, "do_damage");
}

void
do_damage()
{
    object *ppl;

    if (!sizeof(ppl = FILTER_PLAYERS(all_inventory())))
    {
	remove_alarm(damage_alarm);
	damage_alarm = 0;
	return;
    }
    map(ppl, "hurt", this_object());
}

void
hurt(object tp)
{
    tp->catch_tell("You are burned by molten rock! You'd better leave.\n");
    tp->heal_hp(-random(300));
    // intentionally not checking hps and not calling do_die() here.
    // being close to autoattacking NPC is risky enough :)
}

int
do_enter(string str)
{
    if ((str != "passage") && (str != "hole"))
	return notify_fail("Enter what?\n");

    if (!SLAB_HELD)
	return notify_fail("The slab of rock prevents you from passing.\n");

    write("You leave through the passage under the rock.\n");
    this_player()->move_living("through the passage", SLAB_ROOM, 1);
    return 1;
}

int
do_deep(string str)
{
    string name;
    object item, leftover;

    if (!str)
	return notify_fail("Dip what?\n");

    if (!parse_command(str, all_inventory(TP),
	    "[the] %o 'in' / 'into' [the] 'pool' / 'acid'", leftover) &&
	!leftover->id(WORM_LEFTOVER_ID))
	return notify_fail( "Dip what where?\n");

    name = leftover->query_name();

    write("You dip the "+ name +" in the pool of acid.\n" +
      "Rising clouds of poisonous steam sting your eyes and nose!\n");
    say(QCTNAME(TP) + " dips the " + name + " in the pool.\n");

    // If the object has been dipped too often, too bad.
    if (leftover->query_acid() > 3)
    {
	write("After the air clears you find that you "+
	  "still have the " + leftover->short() +" in your hand "+
	  "a bit the worse for the acid-bath.\n");
	leftover->set_acid(leftover->query_acid() + 1);
	return 1;
    }

    seteuid(getuid());

    if (name == "tooth")
    {
	item = clone_unique(DARK + "obj/tooth_knife", 6,
	    DARK + "obj/worm_leftover", 1, 50);
    }
    else
    {
	item = clone_unique(DARK + "obj/worm_armor", 6,
	    DARK + "obj/worm_leftover", 1, 50);

	item->configure_me(leftover->query_part());
    }

    if (item->id(WORM_LEFTOVER_ID))
    {
	  item->remove_object();
	  leftover->set_acid(leftover->query_acid() + 1);
	return 1;
    }

    if (item->move(TP))
	item->move(this_object());

    write("After the air clears you find a " +
	item->short() +" in your hand.\n");

    leftover->remove_object();

    WRITE_LOG(this_player()->query_cap_name() +" transformed the "+
	name +" in the acid pool.\n");
    return 1;
}

string
search_fun(object tp, string what)
{
    if (what == "slab")
    {
	return "Your eyes fall on faded words written with blood:\n" +
	    "I'm trap..d in .ere\n     B..are the W.rm\n   "+
	    "K..l it .nd tak. the t...h then d.p them .. ..e acid pool " +
	    "IT .. yo.. onl. hop.\nMier.n! My love, farew\n";
    }
    return "Your search reveals nothing.\n";
}

void
init()
{
    ::init();
    add_action (do_knock, "knock");
    add_action (do_knock, "rap");
    add_action (do_knock, "tap");
    add_action (do_knock, "bang");
    add_action (do_enter, "enter");
    add_action (do_deep,  "dip");
    add_action (do_deep,  "plunge");
    add_action (do_deep,  "swirl");
}    
