 
 /*
       The Leaping Dolphin Tavern. 

       coder(s):    Jaacar & Maniac 13/9/96

       Revised, Maniac, 2/7/98
 */

#pragma save_binary

inherit "/d/Calia/std/room_tell_room";
inherit "/lib/pub";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"


object keeper;

void
reset_room()
{
     if (!objectp(keeper)) { 
         keeper = clone_object(SEA_CREATURES+"rein_sake"); 
         keeper->move_living("into the bar", this_object()); 
     } 
}

void
create_room()
{
    set_short("The Leaping Dolphin Tavern");
    set_long("This is the Leaping Dolphin Tavern, the most "+
        "spacious hut in the village. " +
        "That rhyme about drunken sailors applies equally to " +
        "their fisherman brethren - you can read it on the wall " +
        "behind the bar. Quite a few of the locals are " +
        "sitting around and having a laugh with their friends or just " + 
        "passing out on the floor. The furniture consists of a number " +
        "of deck chairs. " + 
        "On the near wall is hung a large and interesting painting. " +
        "There's a pricelist on the counter.\n"); 

     add_item(({"hut", "tavern"}), 
            "You're inside it.\n"); 

     add_item(({"wall", "walls"}), "The wall behind the bar " + 
                "has a rhyme written on it, whicn you can read. On " +
                "another wall is mounted an interesting painting.\n"); 

     add_item(({"chairs", "deck chairs"}), 
               "Canvas deck chairs. Very seaside resortish!\n"); 
     add_item("rhyme", "You can read it if you want.\n"); 

     add_cmd_item("rhyme", "read",     
             "What do we do with a drunken whaler?\n" +
             "What do we do with a drunken whaler?\n" +
             "What do we do with a drunken whaler?\n" +
             "Early in the morning?\n" + 
             "Feed him to a shark or hit him with a sardine?\n" + 
             "Slap him with a squid or threaten him with a penguin?\n" +  
             "Poke him with a crab or pester him for hours\n" + 
             "with the captain's parrot?\n"); 


    add_item(({"painting", "large painting", "interesting painting"}), 
        "It is an immaculate oil painting of a great sea storm. " +  
        "Lightning straddles a black sky as the sea rages " +
        "with gigantic waves. They crash on the shore of " +
        "a small, stricken island, which, strangely, is beginning to " + 
        "tilt slightly like a sinking vessel.\n"); 
     
    add_item(({"villager","villagers"}),
        "These sun-bronzed natives are living it up while they can. "+
        "They don't appear to have a care in the world, " +
        "which is quite natural after a few shots of moonshine in " +
        "a pleasant quasi-tropical location.\n");

    add_item("counter","The counter seems to be the most sturdy "+
        "thing in this place, constructed of polished wood. It "+
        "almost seems out of place. There is a small golden "+
        "plaque on the side which appears to have something "+
        "engraved in it.\n");

    add_item("plaque","It reads:  Constructed by Bubba.\n");

    add_item(({"pricelist","menu"}),"It appears to have the prices of "+
        "all of the things you can order here. Perhaps you should "+
        "read it.\n");

    add_cmd_item("pricelist","read","@@read");
    add_cmd_item("menu","read","@@read");

    add_drink(({"beer","beers","dark beer","dark beers"}),
        "beer","dark",100,4,12,0,0,
        "It's a refreshing beer.\n",0);

    add_drink(({"cocktail","cocktails","fancy cocktail","fancy cocktails"}),
        "cocktail","fancy",200,20,72,0,0,
        "It smells very good and probably tastes better!\n",0);

    add_drink(({"wine","wines","red wine","red wines"}),
        "wine","red", 250, 25, 100, 0, 0,
        "It has a deep red colour and smells wonderful.\n",0);

    add_drink(({"grog","grogs","dark grog","dark grogs"}),
        "grog","dark", 300, 30, 120, 0, 0,
        "Its very dark, almost black, and doesn't smell very "+
        "good at all.\n",0);

    add_drink(({"moonshine","moonshines","pale moonshine","pale moonshines"}),
        "moonshine","pale", 70, 50, 210, 0, 0,
        "This home-brewed alcohol smells very strong.\n",0);

    add_food(({"meat","fish","fish meat"}),
        "meat","fish", 65, 80, "strip of fish meat",
        "strips of fish meat",
        "It's a small strip of fish meat.  It looks edible.\n",0);

    add_food(({"scallop","scallops","small scallop","small scallops"}),
        "scallop","small",  30, 25, "small scallop","small scallops",
        "It is a small scallop.\n",0);

    add_food(({"crab","leg","crab leg","crab legs","legs"}),
        "leg","crab", 100,100,0,0,
        "It is a fairly large pink crab leg.\n",0);

    add_food(({"tail","lobster","tails","lobster tail","lobster tails"}),
        "tail","lobster",150,150,0,0,
        "It is a large cooked lobster tail.  It looks very delicious.\n",0);

    add_prop(ROOM_I_LIGHT,1);
    add_prop(ROOM_I_INSIDE,1);

    add_exit(BEACH+"village1","west",0,0);
    add_exit(BEACH+"village5","south",0,0);

    reset_room(); 
}


int
order(string str)
{
    if (!objectp(keeper) || !objectp(present(keeper, this_object())))  { 
        notify_fail("The bartender isn't here!\n"); 
        return 0;
    }

    return ::order(str); 
}


void
init()
{
    ::init();
    init_pub();
}

int
read(string str)
{
    write("\n"+
        "    Dark beer                     12 cc\n"+
        "    Fancy Cocktail                72 cc\n"+
        "    Red Wine                     100 cc\n"+
        "    Dark Grog                    120 cc\n"+
        "    Pale Moonshine               210 cc\n"+
        "\n"+
        "    Small Scallop                 25 cc\n"+
        "    Fish Meat                     80 cc\n"+
        "    Crab Leg                     100 cc\n"+
        "    Lobster Tail                 150 cc\n"+
        "\n"+
        "Try 'buy beer with gold' if you want to specify what\n"+
        "coin type to pay with, or 'buy 10 beer' would get\n"+
        "you ten beers from the bar.\n\n");
    return 1;
}
