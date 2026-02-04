/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * house4c.c
 * Calathin external house.
 * 09/30/1999 -- TOMAS
 */

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>

inherit STDROOM;
#include <stdproperties.h>
object guard;
object guard2;

string ext_lamps();
string light_lamps();
string butler_light();

public void
create_room()
{
    ::create_room();
    INSIDE;
    set_short("trophy room");
    set_long("This room is clearly the trophy room. " +
       "The walls are scattered with various hunting trophies. " +
       "A large mural has been painted on the far wall depicting " +
       "men on horseback being lead through the forest by a large pack of dogs. " +
       "The team appears to be hunting an elusive silver colored " +
       "fox that can be seen hiding below a fallen tree in one of the " +
       "corners of the mural. In the center of the floor is a round " +
       "table which rests upon the skin of an enormous black bear. " +
       "A large fireplace is placed against the northern wall.\n");


    add_item(({"round table","table"}),
       "In the center of the table sits a small statue of a armoured figure riding a " +
                "charging horse. The figure holds a sword held thrust forward..\n");


    add_item(({"figure","statue"}),"The small statue was cast from pewter forming " +
       "a man in armour wielding a sword thrust " +
       "forward while riding a charging horse.\n");

    add_item(({"large fireplace","fireplace","mantle"}),
       "The large fireplace is placed into the northern wall. The fireplace mantle " +
       "was crafted from a single piece of dark red wood. A mural has been carved " +
       "into the mantle depicting a battle between a dragon and a knight upon " +
       "horseback. Upon the mural sits a silver-colored fox.\n");


    add_item(({"large mural","painting","mural"}),
       "A large mural has been painted on the far wall depicting " +
       "men on horseback being lead through the forest by a large pack of dogs. " +
       "The team appears to be hunting an elusive silver-colored " +
       "fox that can be seen hiding below a fallen tree in one of the " +
       "corners of the mural.\n");
    
    add_item(({"silver fox","silver-colored fox","fox"}),
       "The silver-colored fox is quite astounding. Unfortunately for the " +
       "fox, someone decided it would look better stuffed and on their " +
       "mantlepiece than roaming free.\n");

    add_item(("dogs"),"The dogs are almost lifelike. They appear " +
       "to be quite determined in finding their prey.\n");

    add_item(("team"),"The team of humans with their hunting dogs " +
       "are attempting to find their prey.\n");

    add_item(("floor"),"The hardwood floor has been waxed and polished " +
       "to a high sheen. A round table resting upon a large bear skin " +
       "can be seen in the middle of the floor.\n");

    add_item(({"bear skin","skin"}),
       "It must have been some challenge to make this bear give up his coat. " +
       "Connected to the far end of the skin is the huge head of its previous " +
       "owner. The head of the beast bares its giant gleaming teeth. " +
       "At the ends of the skin are the paws. Each paw displays large " +
       "and seemingly sharp claws.\n");

    add_item(({"paws","claws"}),
       "The paws are huge! Several sharp claws protrude from the paws.\n");

    add_item(({"trophy","trophies"}),
       "The heads of various animals set into various positions upon the walls " +
       "and along corners of the room stare back at you.\n");

    add_item(({"walls", "paneling"}),
       "The walls have been covered with a dark walnut wood stained " +
       "with a slight reddish tint. The trim at the floor and ceiling " +
       "are stained darker to be almost black and have been carved " +
       "with elaborate patterns. A piece of trim also circles around the " +
       "room at waist level it too is stained a darked color. Crystal " +
       "lamps, two to a wall are evenly spaced around the room provide " +
       "ample light. Several various hunting trophies are hung about " +
       "the room. The northern wall is dominated by a large fireplace.\n");

    add_exit(CALATHIN_DIR + "houses/house4a","west",0,1);


   add_cmd_item(({"crystal lamps"}),
                 ("extinguish"),
                 ("@@ext_lamps"));
      
    add_cmd_item(({"crystal lamps"}),
                 ("light"),
                 ("@@light_lamps"));
                 

    reset_room();

}

void
reset_room()
{    
  
    if(!guard)
    {
       guard = clone_object(CALATHIN_DIR + "houses/npc/house4_guard");
       guard->move(TO);

       guard2 = clone_object(CALATHIN_DIR + "houses/npc/house4_guard");
       guard2->move(TO);
       guard2->team_join(guard);
   
    }
}



string
ext_lamps()
{
    add_prop(ROOM_I_LIGHT, 0);
    write ("You extinguish the lamps.\n");
    say(QCTNAME(TP) + " extinguishes the crystal lamps.\n");
    set_alarm(10.0, -1.0, "butler_light");
  return "";
}


string
light_lamps()
{
    add_prop(ROOM_I_LIGHT, 1);
    write ("You light the crystal lamps.\n");
    say(QCTNAME(TP) +" lights the crystal lamps.\n");
   
  return "";
}


string
butler_light()
{
    add_prop(ROOM_I_LIGHT, 1);
    say("The butler enters the room relights the lamps then leaves.\n", 
       ({TP}));
         TP->catch_msg("The butler enters the room relights the lamps then leaves.\n");
  return "";
}


