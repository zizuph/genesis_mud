/*
 * BASEFOREST.c
 * This room serves as the master room for all of the rooms in the 
 * forest of Coramar. This forest is designed specifically to give the 
 * players the impression that the forest is alive, and actively protecting
 * its interior, which also houses the Druid Keep of Cirdaan.
 *
 * Players will be able to search for herbs here.
 * Also, as defense mechanisms, the forest instills a sleep spell
 * on the player which grows the more they move, and at seemingly
 * random points, the vines will reach out to a player and steal attempt
 * to steal a weapon.
 *
 * Begun November 28, 1997 - Alaron
 *
 * If you're reading this on-line and hate the format, thats because at the time
 * of modification, my only choice was notepad on a huge monitor, so its formatted
 * for hi-res wide-screen. - Alaron Feb 1998
 */

#include "/d/Emerald/defs.h"

#include "dirheader.h"
#include "coramar.h"

#define DEBUG_MODE 1


inherit "/std/room";

static string *noise_messages =
			 ({ "A cool breeze blows through the forest, bringing with it "+
			  "the unmistakable smell of wet pine.\n",
			  "The sound of leaves rustling and branches shifting echos "+
			  "through the forest as a strong gust of wind howls between "+
	                  "the trees.\n",
			  "As a gust blowing through the forest canopy above shakes the "+
			  "leaves and branches, thousands of little beads of water "+
			  "rain down from above. The drops feel very cold as they "+
			  "drip onto your face.\n",
			  "You hear a quick rustling noise from nearby bushes as an "+
			  "animal darts from its hiding place.\n",
		          "The faint echo of the call of a large bird fills the area "+
			  "and slowly fades away.\n",
			  "The scent of fresh rain against the bark of the forest trees "+
			  "suddenly wafts into the area, hinting at a storm on the "+
			  "outskirts of the woods.\n",
                          "A small, lizard-like animal scurries along the forest floor "+
			  "and then dashes into a protective cover of green foliage.\n",
                          "The sound of wings flapping and leaves rustling echos "+
			  "through the area as a flock of birds takes off high above "+
			  "in the canopy.\n" });
                          
/*
 * FUNCTION PROTOTYPES
 */

int climb_trees(string str);
int echo_shout(string str);
void return_shout(string str);

// Function to handle sleep counting through exits
public mixed do_fexit();

// Rooms inheriting this one will define this function.
public void create_forest();

// Function called to make all default add_item calls to this room.
nomask public void create_default_items();

// Function to use for all forest exits to make sleep counter work.
function add_fexit = &add_exit(,,VBFC_ME("do_fexit"),1,);


/*
 * Room 'tell' / 'noise' variables and prototypes
 */

public void make_noise(); /* this is mask-able */
public void quiet();

private int num_interactives;
private int noise_alarmid;
private int no_noise = 0;


void
create_room()
{
    create_default_items(); // Called to add the default item descriptions to the room.  

    add_prop(ROOM_I_HIDE, 1);
    add_prop(ROOM_M_NO_TELEPORT, "You sense an almost otherworldly presence "+
             "restraining you.\n");
    create_forest();
}

public mixed
do_fexit()
{
/*
 * In this code is where additional drowsyness levels will be
 * added to the player's sleeb object in their inventory. If they
 * do not have a sleep object in their inventory, they will get
 * one when they go through an exit.
 */
#ifdef DEBUG_MODE
    this_player()->catch_msg("You went through the exit.\n\n");
#endif

    return 0;
}

nomask public void
create_default_items()
{
    // This function adds all of the default items to this room
    // that are a part of the 'basic' Coramar forest.
    set_short("A misty forest path");

    add_item( ({"vine", "vines"}),
	"The vines in this forest are of all shapes and sizes, though most are of "+
	"a thick, dark green variety. Some of the larger vines have large, cup-shaped "+
	"leaves hanging down loosely, trapping water as it drips from the forest "+
	"canopy above. They seem to be growing everywhere; wrapped around the trunks "+
	"of the massive trees or slithering along the forest floor like snakes awaiting "+
	"their prey. Many of the vines near the forest floor have large, painful-"+
	"looking thorns sprouting from them.\n");

    add_item( ({"thorns", "spikes", "brambles", "prickles"}),
	"There are thorns jutting out from nearly every bush along the forest floor. Not "+
	"only do the bushes have large, dark brown thorns jutting out from beneath "+
	"their seemingly innocent green foliage, but some of the vines on the ground and "+
	"near the base of the trees also sport enormous, dagger-like thorns. Crouching "+
	"down to get a closer look, you notice a thick purple liquid dripping from the "+
	"hollow tips of some of the thorns. Could they be poisonous?\n");

    add_item( ({"mist", "fog", "shroud", "cloud", "haze"}),
	"The mist covering the forest fills you with a sense of confusion and fear. It "+
	"is so thick that you cannot even see daylight through the haze. The visibility "+
	"on the forest floor is so limited that you can barely make out the trees "+
	"a few meters in front of you. The cool breeze drifting through the woods and "+
	"the dampness of the mist occasionally causes water to condense onto your "+
	"clothing. As you peer around into the mist, the ancient woods gradually "+
	"dissolve behind the floating, gray curtain.\n");

    add_item( ({"trees", "tree"}),
	"The trees in this forest are astonishing. Some of them are so large that "+
	"it would take ten paces just to walk around the base of the trunk. The bottom "+
	"halves of the trees are absolutely covered in damp moss fed by the tremendous "+
	"amount of moisture in the air. The trunks are dark and slick with moisture and "+
	"decaying moss. As you tilt your head back to get a better look at the tops "+
	"of the trees, you see only the dark shadows of the upper limbs hidden by "+
	"the mist. It is impossible to tell how high the trees really are. It looks "+
	"as though they would be nearly impossible to climb without a lot of equipment "+
	"to avoid slipping on the moss and water.\n");

    add_item( ({"trunk" ,"trunks", "tree trunk", "tree trunks"}),
	"The trunks of the trees are staggering. You struggle to imagine how old they "+
	"are, but cannot imagine the age of trees that have trunks thicker than "+
	"most houses! The trunks are covered with a mixture of water, moss and a "+
	"dark, slimy substance which seems to be oozing from the damp moss.\n");

    add_item( ({"leaves", "leaf", "limbs", "upper limbs", "limb", "upper limb",
	        "branch", "branches"}),
	"You tilt your head back to try and get a better look at the tree limbs "+
	"high above, but are disappointed when you can see mothing more than dark, "+
	"shadowy outlines barely visible through the barrier of mist.\n");

    add_item( ({"up", "sky", "daylight", "day", "sun"}),
	"Craning your neck to look up, you can see nothing but the bleak, forboding "+
	"grayness of the all-encompassing mist. A few shadowy outlines of tree limbs "+
	"can be seen shifting in the cool breeze, but nothing more. The experience "+
	"leaves you feeling confined and wary of your surroundings.\n");

    add_item( ({"down", "ground", "floor", "dirt", "forest floor"}),
	"Looking down at the ground beneath you, you are startled by the amount of "+
	"growth on the forest floor. Bushes, ferns and vines flourish wildly on the "+
	"rich soil and damp air, creating a tangled web of leaves, thorn-riddled "+
	"bushes and dangerous-looking vines. You don't seem to notice any insects or "+
	"animal life scurrying about in the underbrush, though.\n");

} // END OF CREATE_DEFAULT_ITEMS    


public void
create_forest()
{
 // This function intentionally left blank. Rooms which inherit
 // this master room will define this function in their local
 // scope.
}


void
init()
{
    ::init();
    add_action(climb_trees, "climb");
    add_action(echo_shout, "shout");
}

int
echo_shout(string str)
{
    set_alarm(2.5, 0.0, &return_shout(str));
    return 0;
}

void
return_shout(string str)
{
    tell_room(this_object(), "A strong wind blows through the forest, carrying "+
	"with it a faint, eerily shrill echo, \""+
	str +
	"\"\n");
}

int
climb_trees(string str)
{
    if ((str == "trees") || (str == "tree") || (str == "trunk") )
    {
        write("You think about it for a moment, and then look at the slippery surface "+
		"and the tremendous thickness of the trees and decide against "+
		"attempting a climb.\n");
	return 1;
    }
    else if ((str == "vines") || (str == "vine") )
    {
        write("You look up at the vines hanging down from the impressive branches and "+
		"limbs above. They look sturdy enough, but something about those vines "+
		"makes you wary. When you realize that you can't even see the tops "+
		"of the vines because they're hidden by mist and fog, you decide "+
		"against attempting a climb.\n");
	return 1;
    }
    else 
	return 0;
}

public void
enter_inv(object ob, object from)
{
    if (interactive(ob))
      num_interactives++;

    if ( (num_interactives == 1) && (!no_noise))
      noise_alarmid = set_alarm(9.0,35.0+itof(random(10)),make_noise);
}

public void
leave_inv(object ob, object to)
{
    if (to != this_object())
       num_interactives--;

    if ((!num_interactives) && (!no_noise))
       remove_alarm(noise_alarmid);
}

public void
quiet()
{
    no_noise = 1;  
}

public void
make_noise()
{
     int i;

    /*
     * This function displays messages to players that remain in a room for a longer
     * period of time, perhaps while they're examining the items or something. Adds
     * senses to description like smell, touch, and sound.
     */

    i = random(sizeof(noise_messages));

    tell_room(this_object(), noise_messages[i]);
   

}
