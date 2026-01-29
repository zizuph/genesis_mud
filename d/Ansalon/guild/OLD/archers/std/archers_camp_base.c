
/*   File name: archer_camp_base.c
 *
 *   Archer camp is Qualinesti. This is a base file for the Archers Guild.
 *
 *   Date: 06.11.2003
 *   Blizzard
 */

#include <macros.h>
#include "/d/Krynn/qualinesti/local.h"
#include "../guild.h"

inherit OUT;
inherit HERBSEARCHNEW

int     kick_ash(string str);
int     ext_campfire(string str);
int     gather_ash(string str);
int     number = 5;

string *herbs = HERB_MASTER->query_herbs( ({ "mixedforest", }) );

public void
reset_qualinesti_room()
{
    set_searched(random(2));
    number = 5;
}

public void
create_camp()
{

}

nomask void
create_qualinesti_room()
{
    set_place(ARCHER_CAMP);
    set_long_desc("The area is surrounded by a thick " +
        "wall of plants of all kind, but here and there you notice also " +
        "a few large, grey rocks jutting out in the bushes. This makes " +
        "it excellent environment for setting a camp and that was " +
        "probabaly the main reason why the elves decided to establish " +
        "their training base here. You notice narrow plumes of smoke " +
        "ascending from a few small campfires.");
        
    add_item(({"clearing", "area", "camp"}),
        "A small clearing in the Qualinesti forest. It seems that a " +
        "group of elven archers set their trainig place here.\n");
    add_item(({"wall", "bushes", "bush"}), 
    	"A thick wall of bushes and trees surrounds this place. There must " +
    	"be a path leading outside, otherwise you doubt you can force your " +
    	"way through it.\n");
    add_item(({ "rock", "rocks", "grey rocks", "large rocks", "grey rock",
        "large rock" }),
        "There are several granite rocks jutting out in the bushes. They " +
        "seem to be here for a very long time.\n");
    add_item(({"forest", "trees"}),
        "The forest surrounding this place contains different types of " +
        "trees. Some of them are very old and grow here for many " +
        "generations of humans and perhaps even elves.\n");
    add_item(({"piles", "ashes", "piles of ashes", "pile", "pile of ashes",
        "ash", "remains"}),
        "You see several piles of ashes around. Probably remains of " +
        "campfires, that burned out last night.\n");
    add_item(({"herb growth", "growth"}), "This place seems to be trodden " +
        "down, but you could probably still find a few useful herbs here.\n");
    add_item(({"campfires", "campfire"}),
        "A few campfires are still burning, but someone really care so " +
        "they do not produce too much smoke.\n");
    add_item("smoke",
        "Smoke ascending from the campfires quickly vanishes, but a light " +
        "scent of it is perceptible in the air.\n");
 
    add_search(({ "campfire", "campfires" }), 1, "burn_me", 1);
    add_search(({ "ashes", "piles of ashes", "pile of ashes", "pile", 
        "piles", "ash", "remains" }), 1, "search_pile", 1); 
    
    set_tell_time(350);
    add_tell("You hear a crack of burning wood coming from the nearest " +
    	"campfire.\n");
    add_tell("The branches above your head wave gently, as a " +
        "sudden gust of wind strikes the area.\n");
    add_tell("You hear sound of snapped bowstring and a silent curse " +
        "following it.\n");
    add_tell("The refreshing scent of the forest fills your nostrils.\n");
    add_tell("Suddenly, an eagle flies down from the sky and lands on " +
        "the top of the biggest tent.\n");
    add_tell("The silent sounds of the forest are coming to your ears.\n");
                
    add_prop(ROOM_I_INSIDE, 0);
    
    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs) }) , 
        ({ "growth", "herb growth", }), 3);
           
    create_camp();
    reset_qualinesti_room(); 

}
 
void
init()
{
    ::init();
    
    add_action(kick_ash, "kick");
    add_action(ext_campfire, "extinguish");
    add_action(gather_ash, "gather");
}

int
ext_campfire(string str)
{
    if ( str == "campfire" )
    {
        write("You prefer not to anger the elves here and you decide " +
            "to let it burn.\n");
        tell_room(TO, QCTNAME(TP) + " looks like " + HE(TP) + 
            " is thinking about extinguishing the campfire, but " +
            HE(TP) + " decides not to after all.\n", TP);
        
        return 1;
    }
    
    if ( str == "campfires" )
    {
        write("You cannot extinguish all campfires at once.\n");
        
        return 1;
    }
        
    return 0;
}
    
/*
 * Function name: kick_ash 
 * Description  : This function return the message if someone kicks a pile
 *                of ashes.
 */
int
kick_ash(string str)
{   
    if ( str == "ash" || str == "ashes" || str == "pile of ashes" )
    {
        write("You kick the pile of ashes, sending a cloud of dark dust " +
            "into the air.\n");
        tell_room(TO, QCTNAME(TP) + " kicks the pile of ashes, sending " +
            "a cloud of dark dust into the air.\n", TP);

        return 1;
    }

    if ( str == "campfire" )
    {
        write("The elves would not be happy if you destroy this campfire. " +
            "You decide to abandon that idea.\n");

        return 1;
    }

    if ( str == "campfires" )
    {
        write("Kick all campfires at once? You are crazy.\n");

        return 1;
    }

    return 0;
    
}

int
gather_ash(string str)
{
    object found;
    
    if ( str == "ash" || str == "ashes" )
    {
        if ( number > 0 )
        {
            tell_room(TO, QCTNAME(TP) + " gathers some ashes.\n", TP);
            write("You gather some ashes from one of the piles.\n");
            found = clone_object(OBJ + "ash");
            found->move(TP);
            number--;
            
            return 1;
        }
        
        notify_fail("There is no more ashes to gather here.\n");
                    
        return 0;
    }
    
    notify_fail("You want to gather some ashes maybe?\n");
    
    return 0;        

}

string
search_pile(object searcher, string what)
{
    object found;
    
    if ( number <= 0 )
        return 0;
    
    if ( random(3) )
    {
        tell_room(TO, QCTNAME(searcher) + " finds nothing in the ashes.\n",
            searcher);
        return "There is obviously nothing but ashes in this pile.\n";
    }
    else
    {
        found = clone_object(OBJ + "charcoal");
        found->move(searcher);
        number--;
        tell_room(TO, QCTNAME(searcher) + " finds something in the ashes.\n", 
            searcher);
        return "You find a " + found->short() + " in the pile of ashes.\n";
    }

}    

string 
burn_me(object searcher, string what)
{
    searcher->heal_hp(-10);
    tell_room(TO, QCTNAME(searcher) + " quickly takes " + 
        POSSESSIVE(searcher) + " hand back as the fire burns " +
        OBJECTIVE(searcher) + ".\n", searcher);

    return "Ouch! The fire is hot. You quickly take your hand back.\n";
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
        start_room_tells();
}
       
             