/*
 * A normal house in Solace
 *
 * By Rastlin
 * Add_items and descrip changes by Teth
 * Jan 2006 - Bug fixed for new Faerie portal
 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit  SOLINROOM;

object gDoor;

public void
create_solace_room()
{
    seteuid(getuid());

    set_short("A house with an air of enchantment");
    set_long("@@my_desc@@");

    add_item("rug", "Now that you examine it closer, you feel certain " +
             "that the rug does 'complain' when you step on it. " +
             "However, no amount of whining from the rug can change " +
             "your mind about the fact that it is a marvellous rug, " +
             "magnificent to behold. It is rumoured that such fine " +
             "weavery is only done by Ergothians, though you certainly " +
             "can't be certain with your untrained eye.\n");

    add_item("bed", "This place of rest fades in and out of existence. " +
             "It is not a good idea to lie down on it, as there is a " +
             "good chance it will not be there when you make your " +
             "attempt. The linen on the bed has a faint aura of blue " +
             "about it.\n");

    add_item(({"linen", "aura"}), "The aura surrounding the linen has " +
             "a faint blue colour, but it is hard to tell if it is " +
             "merely a reflection from the deep blues radiated from " +
             "the portal.\n");

    add_item("dresser", "The dresser is bathed in a flickering light, " +
             "that reflects and dances off the varnish. It has several " +
             "drawers, the handles of which are exquisitely carved.\n");

    add_item("handles", "Each handle is carved into a likeness of " +
             "a fantastic creature, but none are readily identifiable.\n");

    add_item(({"drawer", "drawers"}), "Taking a closer inspection " +
             "of the drawers reveals little. They appear to be empty, " +
             "which isn't unlikely, as what sane person would live " +
             "in a house with a shimmering portal??\n");

    add_item(({"stove", "wood stove"}), "As much as you'd like to " +
             "examine the wood stove with greater care, it always seems " +
             "to skirt itself away from you looking at it directly. If " +
             "you try to approach it, you feel like you've walked " +
             "forever, and have gone nowhere. Best to let it be.\n");

    add_item("kitchen", "Everytime you try to examine the kitchen, " +
             "it seems to dance away from your inspection, undoubtedly " +
             "an effect of the magical nature of the house. You have " +
             "no luck approaching it either, as it retreats as you " +
             "attempt to near it. Some things weren't meant for your " +
             "eyes, it seems.\n");

    room_add_object(C_ELF);

    gDoor = clone_object(OBJ + "d_house7");
    gDoor->move(TO);

    /*
    add_item("portal", "This portal is a swirling maelstrom of " +
             "colours. Raging reds battle brilliant blues in a contest " +
             "of hues. A slight hum is emitted from the shimmering " +
             "portal, attesting to its enchanted quality.\n");
    add_cmd_item(({"through the portal","through portal","portal"}),
		 ({"enter","go","walk"}),
		 "@@go_portal");
         */

}

/*
portal() 
{ 
  write("You enter the shimmering portal.\n"); 
  return 0; 
}

go_portal()
{ 
  write("You enter the shimmering portal.\n");
  this_player()->move_living("through the shimmering portal", C_ELF, 1, 0); 
  return ""; 
}
*/

public string
my_desc()
{
    string str;

    str = "This house has a mystical atmosphere, most likely due to the " +
	  "presence of the shimmering portal that replaces the west wall. " +
	  "The mundane green door set in the east wall rests ";

    if (gDoor->query_open())
        str += "open";
    else
        str += "closed";

    str += ". Everything else in the room has an air of enchantment. " +
           "The bed and dresser seem to fade in and out of existence, " +
           "while the kitchen and wood stove never appear to be quite " +
           "in the same place as when you glanced at them before. The " +
           "rug that occupies the floor seems to utter groans as you " +
           "step on it, but that is probably your imagination.\n";

    return str;
}
