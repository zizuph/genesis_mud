/*Created by Stevenson and Macker*/
/*Idea by Stevenson*/
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;

/* change this to reflect the # of paintings mentioned below in the
add_items */

#define NUM_PAINTINGS "nine"

init() {
    ADA("worship");
    ::init();
}

int 
worship(string str) 
{
    if ((str == "statues") || (str == "the statues")) 
    {
	write("The statues of Stevenson and Macker suddenly come to life and "
	  + "smile at you. As one, they both raise their hands, mouth a few "
	  + "magical words and you find yourself in another place.\n");
	say("The statues come to life and cause " + QTNAME(TP) + " to vanish. "
	  + "\n");
	tell_room(CAVERNS+"cavern12",QCTNAME(TP)+" suddenly appears beside you.\n");
	TP->move_living("M",CAVERNS+"cavern12",1,1); /* don't follow, don't look */
	return 1;
    }
    NF("Worship what?  The statues?\n");
    return 0;
}

void
create_icewall_room()
{
    set_short("Stevenson & Macker's Brag Room");
    set_long(
      "You are in a very regal room as is befitting the station of the two "
      + "Krynn wizards who created Icewall out of much mortal blood and "
      + "wizard sweat. Large paintings cover the walls depicting the various "
      + "stages of creation for Icewall. In the center of the room are two "
      + "statues. If you choose to leave just worship the statues. "
      +"\n");

    add_item("statues","There are two of them: one is labeled Stevenson "
      + "and the other is labeled Macker.\n");
    add_item("paintings","There are " + NUM_PAINTINGS + " to examine as "
      + "'first', 'second', 'third', etc.\n");

    /* stevenson's statue */
    add_item(({"stevenson","Stevenson", "statue of stevenson",
	"statue of Stevenson"}),"You gaze upon the statue of the "
      + "mischievous kender wizard named Stevenson. If you see something in "
      + "Icewall which seems odd and maybe even a bit of a joke it was  "
      + "probably made by him.\n");

    /* macker's statue */
    add_item(({"macker","Macker", "statue of macker",
	"satue of Macker"}),"Here you see a statue of " +
      "Macker. He's the guy who created all the violent, brutal " +
      "stuff here in Icewall. He appreciates ideas and praises " +
      "from mortal friends. He can't spell worth a hoot, though, " +
      "so it'd be nice if you could report typos too.\n");

    /* paintings */
    add_item("first","You look at the first painting and see Stevenson and "
      + "Macker high in the mountains. They are overlooking a "
      + "deserted mansion and are planning what to do with it.\n");
    add_item("second", "In the second painting, " +
      "you see Macker raising a baby griffon " +
      "from the egg, teaching it a few of his favorite riddles.\n");
    add_item("third","Here you see Stevenson spreading his hands wide and "
      + "mouthing the words of magic to cause the Icy Forests to spring from "
      + "the frozen earth.\n");
    add_item("fourth", "Here you see Macker teaching Raggart Knug how to " +
      "forge powerful weapons from pure ice.\n");
    add_item("fifth", "This painting depicts Macker training the ice folk " +
      "warriors for their future battles with the ruthless " +
      "thanoi and minotaurs.\n");
    add_item("sixth","This painting shows Stevenson standing waist deep "
      + "in frozen water figuring out where and how to cause the caverns "
      + "you are in to appear.\n");
    add_item("seventh", "This shadowy picture shows Macker's darker side as he " +
      "summons thanoi, minotaurs, and draconians to icewall, " +
      "forming the white dragonarmy!\n");
    add_item("eighth","You see Stevenson feeding " + QRACE(TP)
      + " flesh to a large white dragon.\n");
    add_item("ninth","In this last painting you see Macker and Stevenson " +
      "proudly watching their mortal friends explore and enjoy " +
      "icewall. They'll soon be back to work though, so " +
      "by the time you've seen everything there is to see " +
      "here, there will be more.\n");

}
