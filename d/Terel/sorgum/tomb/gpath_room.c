/*
 * Modifications
 *   November 8, 2010 - Added reset room to allow missing sandal quest to
 *                      reset properly, Petros.
 */

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Terel/common/terel_defs.h"     
#include "tomb.h"

string *names = ({"Gimlie","Gorboth","Gandit","Ralphus","Rasta","Chumley",
		  "Lazarus","Louis","Lapis","Grimjerk","Mac","Lewis",
		  "Festoon","Jumbalaya","Gherghern","Wapporo"});

string occupant;
int sandal_present = 1;
int skeleton_present = 1;

void set_occupant() { occupant = names[random(sizeof(names))]; }
string get_occupant() { return occupant; }

init()
{
     ::init();
     add_action("do_dig", "dig");
}

create_room()
{
    set_short("graveyard path");
    set_long(
	"You are standing on a path in the graveyard.  A cold breeze " +
	"rustles the leaves of the trees above you.\n"
    );

    add_prop(ROOM_I_INSIDE, 0);
     
    add_item(({"tree", "trees", "elm", "elm tree"}),
       "The grotesque vine-encumbered tree silently waves its knotted " +
       "branches far aloft.\n"
    );

    set_occupant();
    add_item(({"grave", "graves", "gravestone", "tombstone"}), "@@grave_desc");
    
    reset_room();
}

string grave_desc()
{
     if (TP->query_skill(SS_LANGUAGE)) 
	  return "The smooth black grave stone has a name inscribed in it " +
	         "but you can't make it out... it's a strange alphabet.\n";
     else
	  return "The smooth black grave stone bears the name " + occupant+".\n";
}

int do_dig(string how)
{
     object sandal;
     object skeleton;
     
     if (!present("shovel", TP)) {
	  write("You'd better get a shovel if you want to dig here!\n");
	  return 1;
     }
	 
     if (how != "here") {
	  write("You want to 'dig here' ?\n");
	  return 1;
     }

     if (query_prop("_sandal_present")){
	  if (sandal_present) {
	       sandal_present = 0;  
	       write("You dig up the grave and find a sandal.\n");
	       sandal = clone_object(TOMBDIR + "sandal");
	       sandal->move(environment(TP));
	       sandal->add_prop("_sandal_finder", TP->query_name());
	       return 1; 
	  }
     }
     else {
	    if (skeleton_present) {
		 skeleton_present = 0;
		 write("You dig up the grave and disturb something that was " +
		       "peacefully at rest, but which now awakens!\n");
		 skeleton = clone_object(TOMBDIR + "skeleton");
		 skeleton->set_follow(TP->query_name());
		 skeleton->move(environment(TP));
		 return 1;
	    }
       }

     write("Someone has already been digging here, the grave is empty.\n");
     return 1;
}

/* 
 * Function:    reset_room
 * Description: This reset_room call resets the dug up state so that one
 *              can repeat this quest.
 */
public void
reset_room()
{
    ::reset_room();
        
    skeleton_present = 1;
    sandal_present = 1;    
}
