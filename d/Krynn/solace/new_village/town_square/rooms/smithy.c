/*
* Theros Ironforge's Smithy
*  Created By Leia
*  June 06, 2005
*
** Last Updated By:
** Leia
** July 1, 2005
*
* Updated typos.  Removed no_attack props.
*
* Mortis 06.2006
*
* Updated so that repair codes are now in Theros
* Arman October 2016
*/

/*Smith Code Borrowed From Ashlar*/

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <money.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <language.h>
#include <formulas.h>
#include <ss_types.h>
#include <macros.h>

inherit R_FILE

object theros;

void
reset_krynn_room()
{
    if(!objectp(theros))
    {
        theros = clone_object(THEROS);
        theros->move(TO);
        theros->arm_me();
    }
}

void
create_krynn_room()
{
    set_short("Theros Ironfeld's Smithy");
    set_long("This is Theros Ironfeld's smithy. This smithy has been "
	+ "built inside of a boulder. Everything from the forge, to the shelves, "
	+ "has been crafted directly out of the rock. In fact, the only wooden "
	+ "aspect of this store is the door that hangs at the entrance. Even the "
	+ "sign above it outside has been carved into the boulder. There is a "
	+ "granite plaque hanging on the wall.\n");
    add_item("plaque", "It has words on it. Maybe you should read it.\n");
    add_cmd_item("plaque", "read", "@@sign_long");
    add_item(({"forge"}), "The forge has been crafted off towards the side "
	+ "of the shop. It is amazing what the builder of this shop has done to "
	+ "create such a forge. The opening glows a bright red.\n");
    add_item("door", "The door is most beautifully crafted from oak with a "
	+ "brass knob and a small window.\n");
    add_item("window", "The window is small and displays the surroundings "
	+ "outside the door.\n");
    add_item("knob", "The knob is crafted of the finest brass. Looking "
	+ "closely, you notice that the knob is in the shape of a dragon, and "
	+ "the button to unlatch it an axe, which penetrates the dragons head.\n");
    add_item(({"shelf", "shelves"}), "The shelves are carved into the "
	+ "boulder, and contain all sorts of different smithing supplies.\n");
    
    add_exit(NESMITHY, "northeast", 0);

    reset_krynn_room();
}

int
msg()
{
    write("You wipe your brow as you step out of the warm smithy.\n");
    return 0;
}

void
init()
{
    ::init();

    add_action("hand_beer", "hand");
}

int
hand_beer(string str)
{   
    NF("Hand what to whom?\n");

    if ((str == "beer to human") || (str == "beer to theros") || 
        (str == "beer to smith") || (str == "beer human") ||
        (str == "beer theros") || (str == "beer smith"))
    {    
        if(present(B_NAME, this_player()))
        {
            object beer = present(B_NAME, this_player());
            say(QCTNAME(this_player()) + " gives a small beer to "
			+ QTNAME(theros) + ".\n");
            theros->command("emote roars: Why thanks, good buddy!");
            theros->command("emote downs the small beer in a single gulp!");
            write("Theros gives you a hearty slap on the back!\n");
            say("Theros gives " + QTNAME(TP) + " a hearty slap on the "
			+ "back!\n");
            beer->remove_object();
            return 1;
        }
    
        else
        {
            write("That's not a beer from the Inn!\n");
            return 1;
        }
    }
    
    return 1;
    
}

string
sign_long()
{
    return
      "Theros Ironfeld's Smithy\n\n" +
      "Weapon improvement:\n"
      + "-------------------\n"
      + "   <sharpen> dull weapons\n"
      + "   <wax> corroded weapons\n"
      + "\n"
      + "   All prices depend on the price of the weapon.\n"
      + "   Do <wcost> <weapon> to see the costs.\n\n"+
      "Armour repairs:\n"
      + "---------------\n"
      + "   <fix> damaged armours\n"
      + "   Do <acost> <armour> to see the repair costs.\n\n"+
      "Commission masterwork equipment:\n"
      +"--------------------------------\n"
      +"     <commission> weapon / armour / wand\n"
      +"     <list>\n"
      +"     <list weapons>\n"
      +"     <list armours>\n"
      +"     <list wands>\n\n"
      +"     I take commission in steel coins, but you\n"
      +"     will also need to pay material costs!\n\n";
}