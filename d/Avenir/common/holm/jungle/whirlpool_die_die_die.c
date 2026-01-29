// file name:        /d/Avenir/common/holm/jungle/whirlpool_die_die_die.c
// creator(s):       Lilith, Nov 96
// purpose:          Drowning room: they took liberites with the water.
// note:             Thanks to Fysix for help with removing the alarms.
/*
 * Revisions:
 * 	Lucius, Dec 2017: Check for water breathing post-entry as well.
 */
/* Inherit the smis room*/
inherit "/d/Avenir/inherit/room";

/* Include the local area defines, etc */
#include "../holm.h"
#include <stdproperties.h>

// Added: a prop in the player that remembers the alarm running for him
#define TELLTIME   "_drown_tell_"
#define ALARM_ID   "_live_i_drown_alarm_id"
#define VOICE(x)   tell_object(ob, "The water spirit sings to you: " + x)
#define SCARE(x)   tell_object(ob, x)

#define MOUTH_PROP	"Your mouth is full of water!\n"

#define DROWN_LOG	"/d/Avenir/log/deaths/drown_log"
#define HIZ_POOL	(SHORE + "pool")
#define OUTSIDE		(JUNG + "lf7")

void tell_before_drown(object ob);

// Start the drown alarm for a player
void
start_drown_alarm(object ob)
{
    // Create an alarm, and store the id in the prop in the player
    int alarm_id = set_alarm(5.0, 10.0, &tell_before_drown(ob));
    ob->add_prop(ALARM_ID, alarm_id);
}

// Remove the drown alarm for a player
void
remove_drown_alarm(object ob)
{
    // Find the alarm_id in the player and remove the alarm
    int alarm_id = ob->query_prop(ALARM_ID);
    ob->remove_prop(ALARM_ID);
    remove_alarm(alarm_id);
}

/* Now create the room.  */
void
create_domain_room()
{
    set_short("in a whirlpool");
    set_long("The water is cold and murky. It swirls everything "+
      "caught in it downward, toward the bottom of the pool. "+
      "White streamers of vapour cloud your vision. There are water "+
      "spirits here, and they permit no rest for the water, "+
      "nor for those who are caught it.\nSeveral water spirits.\n");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
    add_prop(OBJ_S_WIZINFO,
      "     Yes, this room is a death trap. All who enter it "+
      "should DIE if they cannot discover the way out. DO NOT "+
      "trans mortals from this room. They are supposed to drown "+
      "in this whirlpool.\n");

    add_item(({"track", "ancient track"}),
      "It is little more than an animal track, mostly obscured "+
      "by the prolific growth of vegetation along the forest "+
      "floor.\n");
    add_item(({"cliff", "high cliff"}),
      "From this angle, the cliff looks like a dark wave "+
      "topped with pale green foam, eternally frozen in "+
      "stone.\n");
    add_item(({"moss"}),
      "Spongy and green, moss grows on every possible "+
      "surface here, relishing the moist environment.\n");

    add_item(({"pool", "whirl", "whirlpool", "water", "center"}),
      "It is cloudy and chill. Fingers of water vapour drift "+
      "in a circular motion above the torrent of water that "+
      "inexorably pulls everything beneath its surface.\n");
    add_item("ledge", "It is covered in moss and slick with "+
      "moisture.  It juts out over the water, just beyond reach.\n");
    add_item(({"spirit", "water spirit", "spirits", "water spirits"}),
      "There "+
      "appears to be several water spirits here. They all "+
      "look very much the same.\n");
    add_item(({"first water spirit", "first spirit",
	"angry spirit"}), "She "+
      "is translucent, the colour of milky quartz, and seems "+
      "to glow with an inner light. Her hair is long and "+
      "oddly green, it looks like tangled seaweed. She appears "+
      "to be angry.\nShe is feeling very well.\n");
    add_item(({"second water spirit", "second spirit"}), "She "+
      "is translucent, the colour of milky quartz, and seems "+
      "to glow with an inner light. Her hair is long and "+
      "pale green, it looks like the water weeds growing "+
      "along the streambed. Her face is sensitive and her "+
      "expression kind.\nShe is feeling very well.\n");
}

public int
cleanup_drowning(object who)
{
    remove_drown_alarm(who);
    who->remove_prop(TELLTIME);

    if (who->query_prop(LIVE_M_MOUTH_BLOCKED) == MOUTH_PROP)
	who->remove_prop(LIVE_M_MOUTH_BLOCKED);
}

private void
delayed_exit(object who)
{
    if (environment(who) != this_object())
	return;

    tell_object(who, "A water spirit swims up to you.\n");
    tell_object(who, "The water spirit says: "+
	"Father Hizarbin has blessed you, "+
	"mortal. You will survive the day.\n");
    tell_object(who, "The water spirit waves it hands and "+
	"a surge of water sweeps you back onto land.\n");

    who->move_living("M", OUTSIDE, 1, 1);
}

public int
check_drown(object who)
{
    if (who->query_prop(MAGIC_I_BREATH_WATER) ||
	who->query_magic_protection(MAGIC_I_BREATH_WATER, who))
    {
	set_alarm(2.5, 0.0, &delayed_exit(who));
	return 0;
    }
    /* 1 == start drowning */
    return 1;
}

/*
 * Function name: tell_before_drown
 * Description:   Messages for people who're going to drown
 */
public void
tell_before_drown(object ob)
{
    if (!check_drown(ob))
	return;

    /* The following code increments the player's time-tell counter */
    int ttime = ob->query_prop(TELLTIME) + 1;
    ob->add_prop(TELLTIME, ttime);

    switch (ttime)
    {
    case 1:
	SCARE("You begin a slow spiralling toward the center of "+
	  "the whirlpool.\n");
	break;
    case 2:
	SCARE("A water spirit swims up to you, her beautiful face "+
	  "twisted with anger.\n");
	break;
    case 3:
	VOICE("This is my demesne, mortal!\n");
	break;
    case 4:
	VOICE("You thought to sample the water. Now it shall "+
	  "sample you!\n");
	break;
    case 5:
	SCARE("The water spirit smiles maliciously at you.\n");
	break;
    case 6:
	SCARE("You are half-way to the center of the water-funnel.\n"+
	  "You are becoming dizzy from the endless circling.\n");
	break;
    case 7:
	SCARE("You are growing so cold that you cannot feel your "+
	  "fingers and toes.\n");
	break;
    case 8:
	SCARE("   Circling, circling... \n");
	break;
    case 9:
	SCARE("You have reached the center of the whirlpool!\n"+
	  "There is a tugging at your feet and your head is "+
	  "sucked below the water's surface!\n");
	ob->add_prop(LIVE_M_MOUTH_BLOCKED, MOUTH_PROP);
	break;
    case 10:
	SCARE("Water fills your lungs, making you choke! You thrash "+
	  "around, trying to reach the surface of the water.\n");
	break;
    case 11:
	SCARE("The blood is pounding in your head...you feel "+
	  "dizzy.\n");
	VOICE("Stop struggling so. Accept your impending death "+
	  "with dignity and grace.\n");
	break;
    case 12:
	SCARE("Another water spirit swims over to you.\n");
	SCARE("The second water spirit sings to the first: "+
	  "You torment it. If you think doing so will "+
	  "attract our father's favour, you are wrong.\n");
	break;
    case 13:
	SCARE("You feel like vomiting, but cannot.\nYour eye"+
	  "sight seems to dim.\n");
	break;
    case 14:
	SCARE("The first water spirit sings: "+
	  "I hate it here. I long for the sea!\n");
	SCARE("The second water spirit sings to the first: "+
	  "Then learn to behave. It is your duty to drown "+
	  "those who sample the waters without leave. You "+
	  "are not supposed to delight in it.\n");
	break;
    case 15:
	SCARE("You flail about with less energy.\nInarticulate "+
	  "cries come from your throat.\n");
	break;
    case 16:
	SCARE("The first water spirit pouts, then sends you a "+
	  "malicious glare.\n");
	SCARE("The second water spirit looks at you with sympathy "+
	  "in her eyes.\n");
	break;
    case 17:
	SCARE("The second water spirit sings to you: Poor mortal. "+
	  "Let me ease your suffering.\n");
	break;
    case 18:
	SCARE("You feel a blow at the back of your head.\n"+
	    "You know only a brief moment of whirling darkness "+
	    "before your view tilts and you slide into unconscious"+
	    "ness.\n");

	cleanup_drowning(ob);
	write_file(DROWN_LOG, ob->query_real_name() +" drowned in "+
	    "the Holm whirlpool at "+ ctime(time())+".\n");
	ob->heal_hp(-90000);
	ob->do_die(this_object());
	if (ob->query_wiz_level())
	    ob->move_living("M", OUTSIDE, 1, 1);
	break;
    }
}

int
swim_fail(string str)
{
    if (!str || (parse_command(str, ({ }),
		"[to] [the] 'shore' / 'beach' / 'rock'")))
    {
	write("You struggle valiantly against the circular under-pull "+
	  "of the water, but find yourself no closer to shore.\n");
	return 1;
    }

    notify_fail(capitalize(query_verb()) +" where?\n");
    return 0;
}

int
do_pray(string str)
{
    if (!strlen(str))
    {
	notify_fail("Pray to whom?\n");
	return 0;
    }

    if (str != "hizarbin" && str != "to hizarbin" &&
	str != "Hizarbin" && str != "to Hizarbin")
	return 0;

    if (random(10))
    {
	write("A feeling of joy suffuses you as the water about you "+
	  "surges and carries you toward land.\nHizarbin has heard "+
	  "your prayer!\n");
	say(QCTNAME(this_player()) +" is carried away by a sudden "+
	  "surge in the water!\n");
	this_player()->move_living("M", OUTSIDE, 1, 1);
	return 1;
    }

    write("Something has changed. You feel as though the water has "+
      "become sentient, and is evaluating the sincerity of your "+
      "prayer.\n");
    return 1;
}

int
do_beg(string str)
{
    if (!str)
	str = "pardon";

    if (str != "for forgiveness" && str != "forgiveness" &&
	str != "pardon" && str != "hizarbin" && str != "Hizarbin")
	return 0;

    write("Hizarbin is pleased by your abasement, and decides to "+
      "spare your life!\nA feeling of joy suffuses you as the water "+
      "about you surges and carries you toward land.\n");
    say(QCTNAME(this_player()) +" is carried away by a sudden "+
      "surge in the water!\n");
    this_player()->move_living("M", OUTSIDE, 1, 1);
    return 1;
}

void
init()
{
    ::init();
    add_action(swim_fail, "swim");
    add_action(do_pray,   "pray");
    add_action(do_beg,    "beg");
}

/*
 * Function name: enter_inv
 * Description:
 */
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!interactive(ob))
	ob->move(HIZ_POOL);
    else if (check_drown(ob))
	start_drown_alarm(ob);
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    cleanup_drowning(ob);
}
