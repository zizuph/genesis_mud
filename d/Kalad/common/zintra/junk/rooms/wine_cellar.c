inherit "/std/room.c";
#include <stdproperties.h>
#include <macros.h>
#include "../defs.h"

int passage;     /*  1 if secret passage is open.
                     0 if secret passage is closed.            */
int puddle;      /*  1 if puddle is on the floor.
                     0 if puddle is gone.                      */  
int turned;      /*  1 if the iron spigot has been turned..
                     0 if the iron spigot has not been turned  */  
void
reset_me()
{
    if (passage == 1 || puddle == 1 || turned == 1)
        tell_room(TO, BS("You feel dizzy for a moment.  When you " +
            "recover, things look a little different.\n"));
    passage = 0;
    puddle = 0;
    turned = 0;
}

void
create_room()
{
    set_short("Wine Cellar");
    set_long( BS(
"This room is in very good condition.  It seems that the bartender of the " +
"Bloody Raven is hoarding a fairly decent supply of wine.  There are " +
"several wine casks here, as well as a huge winerack on the north wall.  " +
"The lanterns in this room provide an almost warm, if not bright, " +
"glow.\n" + "@@extra_long@@"));

    add_exit(G_ROOMS + "pub", "up", 0);

    add_item(({"cask", "casks"}), BS(
"These are large wine casks, produced to hold large quantities.  From the " +
"markings, you can see that this is the last shipment from the old golden " +
"days of the city.  The value of this treasue is uncalculable, for the " +
"Kalidians of old were renowned for their winemaking abilities.  There are " +
"casks made of oak, walnut, and teakwood, all designed to provide " +
"different flavors to the wine encased within.\n"));

    add_item ("oak cask", BS(
"A huge oak cask with an oak spigot protrouding from the bottom of one end " +
"of the cask.\n"));

    add_item ("walnut cask", BS(
"A huge walnut cask with a walnut spigot protrouding from the bottom of one " +
"end of the cask.\n"));

    add_item (({"teakwood cask", "teak cask"}), BS(
"A huge teakwood cask with an iron spigot protrouding from the bottom of one" +
" end of the cask.  This cask is flush to the west wall.\n"));

    add_item (({"oak spigot", "walnut spigot", "iron spigot", "spigot"}),
        "'Tis your standard spigot.\n");

    add_item(({"winerack", "rack"}), break_string(
"This winerack contains bottles from other realms and provinces.  There " +
"are some labels you don't even recognize.  This is quite a collection!  " +
"It must have taken some time to put together.  You wonder briefly how " +
"something like this could have been amassed in these surroundings.\n", 78));

    add_item(({"lanterns", "lantern"}), break_string(
"Thes lanterns, unlike the rest in this area, are clean.  You can actually " +
"tell that they are made of brass, and quite beautiful.  Unfortunately for " +
"you, they are firmly attached to the wall.\n", 78));

    add_item("puddle", "@@puddle_desc");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
}

string
extra_long()
{
    if (passage)  
    {
       if (puddle) return
         "The teakwood cask is open, revelaing a dark passage to the west.\n" +
         "There is a small puddle of wine on the floor.\n";
       return "A teakwood cask is open, revealing a passage to the west.\n";
    }
    if (puddle) return "There is a small puddle of wine on the floor.\n";
    return "";
}

string
puddle_desc()
{
    if (puddle)
    return BS("There is a small puddle of wine on the floor.  Someone " +
        "must have left one of the spigots open.\n");
    return "You find no puddle.\n";
}

void
init()
{
    ::init();
    add_action("turn_spigot", "turn");
    add_action("pull_spigot", "pull");
    add_action("close_cask", "close");
    add_action("move_west", "west");
    add_action("move_west", "w");
}

int
turn_spigot(string str)
{
    NF("Turn what?\n");
    if (!str) return 0;
    if (str == "spigot")
    {
        write ("Which spigot do you wish to turn?\n");
        return 1;
    }
    if (str == "walnut spigot" || str == "oak spigot")
    {
        write( BS("You turn the spigot and wine starts pouring out of the " +
          "walnut.  Not wishing to waste such delicious stuff (not " +
          "to mention that you don't have a cup), you quickly shut it " +
          "off, but not before a small puddle of wine forms on the floor.\n"));
        say(BS(QCTNAME(TP) + " fiddles with one of the casks, and wine starts" +
        " to pour out all over the floor, forming a small puddle.  " +
        capitalize(TP->query_pronoun()) + " quickly shuts off the flow.\n"));
        puddle = 1;
        call_out ("puddle_evap", 30);
        return 1;
    }
    if (str == "iron spigot")
    {
        if (passage)
        {
             write ("Nothing happens.\n");
             return 1;
	}
        write( BS("You turn the iron spigot and you hear a soft 'click' " +
            "behind the teakwood cask.\n"));
        say (QCTNAME(TP) + " fiddles with one of the casks.\n");
        if (turned) 
        {
            turned = 0;
            return 1;
	}
        turned = 1;
        return 1;
    }
    return 0;
}

int
pull_spigot(string str)
{
    NF("Pull What?\n");
    if (!str) return 0;
    if (str == "spigot")
    {
        write ("Which spigot do you wish to pull?\n");
        return 1;
    }
    if (str == "oak spigot" || str == "walnut spigot")
    {
        write ("Nothing happens.\n");
        return 1;
    }
    if (str == "iron spigot")
    {
        write("You grasp the iron spigot firmly and give it a good yank.\n");
        if (passage)
	{
            write ("Someone has already done that.\n");
            return 1;
	}
        if (turned) 
	{
            write ( BS("The front of the teakwood cask swings outward, " +
                "revealing a dark passage leading west.  Who ever heard of " +
                "a teakwood winecask anyhow.\n"));
            say (QCTNAME(TP) + " pulls open the teakwood winecask, revealing" +
            " a dark passage leading west.\n");  
            passage = 1;
            call_other(G_ROOMS + "passage2", "east_open");
            return 1;
        }
        write ("However, nothing seems to happen.  Perhaps its stuck?\n");
        return 1;
      }
    return 0;
}

int
close_cask(string str)
{
    NF("Close what?  Do you mean the teakwood cask?\n");
    if (!str) return 0;
    if (str != "cask" && str != "teakwood cask") return 0;
        write ("You close the teakwood cask.\n");
        say (QCTNAME(TP) + " closes the teakwood cask.\n");
        passage = 0;
        call_other(G_ROOMS + "passage2", "east_open");
        return 1;
        }

int
move_west(string str)
{
    NF("Move where?\n");
    if (str) return 0;
    if (!passage) return 0;
    TP->move_living("into the dark passage leading west", 
         G_ROOMS + "passage2");
    return 1;
}

void
puddle_evap()
{
    puddle = 0;
    tell_room(TO, "The puddle on the floor evaporates.\n");
}

void
open_wall()
{
    if (passage)
    {
    tell_room(TO, BS("The cask can be open from inside, but not shut.  If " +
"you are seeing this message, it is a logic error with the rooms concerned." +
"  Please report this with as many details as you can, and I'll try to " +
"fix it.  Hopefully, it will reset itself within this function.  " +
"Thank you.\n"));
    return;
    }
    passage = 1;
    tell_room(TO, BS("The front of the teakwood cask swings outward, " +
        "revelaing a passage to the west.\n"));
}
