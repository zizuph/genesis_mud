
/* File name :  joinroom.c
 *
 * Inside the leader's tent. It is possible to join the occupational
 * branch of Elven Archers here.
 *
 * Blizzard, 05.11.2003
 */
 
#include "/d/Krynn/common/defs.h"
#include "../guild.h"

inherit  R_FILE

public string    papers_desc();

object           leader;

void
reset_qualinesti_room()
{
     if ( !leader )
     {
         leader = clone_object(GUILD_NPC + "porthios");
         leader->move(TO, 1);
     }
}

public void
create_krynn_room()
{
    set_short("inside the leader's tent");
    set_long("You are standing inside a spacious tent, which obviously " +
        "belongs to some important person. There are not many decorations " +
        "or much furniture here, however. In fact, the most valuable items " +
        "are probably a map and a pile of papers lying on the small " +
        "wooden table, although there is also a simple " +
        "couch standing next to it.\n");
    
    add_item(({ "furnitures", "furniture" }),
        "The only furniture in this room are a small wooden " +
        "table and a simple couch standing next to it. You are a bit " +
        "surprised, because this tent belongs to the leader of the " +
        "Elven Archers after all.\n");
    add_item( "table",
        "A small wooden table, with a map and a pile of papers lying " +
        "on it, is standing in the middle of the room. Maybe you could " +
        "take a closer look at these them.\n");
    add_item( "map",
        "This looks like a map of Qualinesti. Some locations seem to be " +
        "described, but other places are only marked to draw the reader's " +
        "attention. On the first sight you recognize just simple words... " +
        "Qualinost, Pax Tharkas, Newports.\n");
    add_item( ({ "paper", "papers", "pile", "pile of papers" }), papers_desc);
    add_item( ({ "couch", "simple couch" }),
        "This is a simple couch. Most of his time Porthios spends " +
        "outside, but sometimes he also has to rest.\n");
        
    add_cmd_item( ({ "paper", "papers", "pile of papers" }), "read",
        papers_desc);
             
    INSIDE;
    NO_TIME;
    
    add_exit(GUILD_ROOM + "archer_camp1.c", "out", 0, 1);

    reset_qualinesti_room();    
}

public string
papers_desc()
{
    string ret_str;
       
    ret_str = "These are reports delivered to the leader, as well as the " +
        "instructions for those who wish to join the Elven Archers.";
    
    if ( TP->query_wiz_level() /* or council - add later */ )
    {
        ret_str += " These papers contain also other important informations, " +
            "such as the list of the warriors and the special orders.\n";

     /* add list of council commands here */

    }
    else
    {
        ret_str += " They seem to contain also other informations, but you " +
            "cannot understand them.\n";
    }
            
    return ret_str;
    
    
}
