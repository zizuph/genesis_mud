/* The long awaited Grunts pub. Based on the Telberin Pub & Inn.       */
/* The items on the menu were suggested by Grunts (see for yourself!). */
/* Grunts do not get any special deals here, for tax reasons.          */
/* Coded 27/12/95 by Tulix III.                                        */


inherit "/std/room";
inherit "/lib/pub";

#include <stdproperties.h>
#include "default.h"
#include "../guild.h"

/* Prototype functions */
public void reset_room();
public int not_now(string dummy);

/*
 * Function name:   create_room
 * Description:     define the basics of the room  
 */
public void
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    
    set_short("Grunts bar");
    set_long("   You have entered the Grunts bar. A more deeply depraved den "
	+ "of drunken debauchery would be difficult to describe. The unique "
	+ "atmosphere of the place arises from a blend of illicitly "
	+ "distilled alcoholic drinks and the deliberately obnoxious "
	+ "behaviour of the regular customers. Not forgetting the similar "
	+ "behaviour of the bar staff too, of course!\n"
        + "There is a menu on the wall for those sober enough to read.\n\n");
    
    add_item(({"walls","wall"}),
	"There are torches fixed on two walls of the bar. " +
	"The walls are cold, and damp to touch. It seems to be made " +
	"of the usual volcanic rock like the rest of the caves. There is " +
	"a menu scratched onto one of the walls.\n");
    
    add_item(({"roof","ceiling"}),
	"The roof is made of the same rock as the walls, the familiar " +
	"volcanic rock. At least you can " +
	"be fairly sure the roof won't be falling down, as volcanic rock " +
	"is pretty tough stuff.\n");

    add_item(({"floor","ground"}),
	"The floor on which you are standing seems very firm, and is made " +
	"of volcanic rock.\n");

    add_item(({"torch","torches"}),
	"The torches are fixed firmly to the wall, and cannot be taken.\n");

    /* Set up the drinks which we want to sell. */
    
    add_drink( ({ "lager", "light lager", "lagers", "light lagers" }), 
	"lager", "light", 540, 4, 12, 0, 0, 
	"A weak and watery drink for wimps.\n", 0);
    
    add_drink( ({ "ale", "dodgy ale", "ale", "dodgy ale" }), 
	"ale", "dodgy", 540, 16, 36, 0, 0, 
	"A dodgy ale of somewhat dubious origins.\n", 0);

    add_drink( ({ "stout", "harsh stout", "stouts", "harsh stouts" }), 
        "stout", "harsh", 270, 25, 75, 0, 0,
	"A harsh stout that is probably better sold as shoe-polish.\n", 0);
    
    add_drink( ({ "wine", "ropy wine", "wines", "ropy wines" }), 
	"wine", "ropy", 300, 35, 135, 0, 0, 
	"A small bottle of generic plonk. Strong, but " +
	"not the connoisseur's choice.\n", 0);
    
    add_drink( ({ "moonshine", "strong moonshine", "moonshines", 
	"strong moonshines" }), 
	"moonshine", "strong", 52, 50, 260, 0, 0, 
	"It looks like rather powerful (and illegal) stuff.\n", 0);

    /* Set up the foods which we want to sell. */
    
    add_food( ({ "gnome soup", "soup", "gnome soups", "soups" }),
	"soup", ({ "gnome", "brain" }), 30, 25, "bowl of gnome brain soup",
	"bowls of gnome brain soup",
	"It is a soup of gnome brains. It doesn't look very filling.\n" , 0);

    add_food( ({ "hobbit stew", "stew", "hobbit stews", "stews" }), 
	"stew", "hobbit", 65, 80, "bowl of hobbit stew", 
	"bowls of hobbit stew",
	"Hmmm. Considered a delicacy by some. You're not so sure....\n" , 0);

    add_food( ({ "dwarf casserole", "casserole", "dwarf casseroles", 
	"casseroles" }), 
	"casserole", "dwarf", 80, 115, "dwarf casserole",
	"dwarf casseroles",
	"The bits of dwarf are well cooked, but still a bit tough.\n", 0);

    add_food( ({ "spicy human rib", "rib", "spicy human ribs", "ribs" }),
	"rib", ({ "spicy", "human" }), 110, 220, "spicy human rib",
	"spicy human ribs",
	"This is probably the safest item on the Grunts bar menu, as it " +
	"looks well cooked, and is quite tender.\n", 0);
    
    add_food( ({ "elf steak", "steak", "elf steaks", "steaks" }),
	"steak", ({ "large", "elf" }), 150, 380, "elf steak",
	"elf steaks",
	"Yeah, this is a _large_ elf steak: lets hope you can eat it.\n", 0);
    
    add_item("menu", "The menu is carved into the wall and reads:\n\n" +
	"@@menu_items_desc");

    add_cmd_item("menu", "read", "The menu carved into the wall reads:\n\n" +
	"@@menu_items_desc");
   
    add_exit(THIS_DIR + "bank", "west", 0, 1);
    add_exit(THIS_DIR + "train", "south", 0, 1);

    reset_room();
}


/*
 * Function name:   reset_room
 * Description:     populate the bar with appropriate npcs  
 */
public void
reset_room()
{
    object drunk_goblin, barmaid;
    
/*    
    if (!present("jorwarq"))
    {
	drunk_goblin=clone_object(GRUNTS_DIR + "npc/drunk_goblin1");
	drunk_goblin->move(TO);
    }
*/

/*
    if (!present("chorgur"))
    {
	drunk_goblin=clone_object(GRUNTS_DIR + "npc/drunk_goblin2");
	drunk_goblin->move(TO);
    }
*/

/*
    if (!present("klurfy"))
    {
	drunk_goblin=clone_object(GRUNTS_DIR + "npc/drunk_goblin3");
	drunk_goblin->move(TO);
    }
*/
    
    if (!present("luptord"))
    {
	barmaid=clone_object(GRUNTS_DIR + "npc/barmaid");
	barmaid->move(TO);
    }

}

/*
 * Function name:   init
 * Description:     add buy command to players who enter the room
 */
public void
init()
{
    ::init();
    
    if (present("luptord"))
    {    
	/* Only allow players to buy stuff if the barmaid is here */
	init_pub();
    }
    else
    {    
	/* Make sure we explain why players cannot buy stuff */
	add_action(not_now, "buy");
    }
}

/*
 * Function name:   not_now
 * Description:     Give player the reason for not being able to buy stuff
 * Arguments:       dummy: the stuff the player wishes to buy
 */
public int
not_now(string dummy)
{
    write("Alas, the barmiad is not here to serve you.\n");
    return 1;
}

/*
 * Function name:   menu_items_desc
 * Description:     set up a menu describing what you can buy here
 * Returns:         a string showing the full list of stuff we sell
 */
public string
menu_items_desc()
{
    return "  Booze available here:          Grub available here:\n\n"
	+  "    Lager         -   12 cc        Gnome Brain Soup  -  25 cc\n"
	+  "    Ale           -   36 cc        Hobbit Stew       -  80 cc\n"
	+  "    Stout         -   75 cc        Dwarf Casserole   - 115 cc\n"
	+  "    Wine          -  135 cc        Spicy Human Rib   - 220 cc\n"
	+  "    Moonshine     -  260 cc        Elf Steak         - 380 cc\n\n"
	+  "  Cash only or get lost. (Especially Grunts).\n";
}

