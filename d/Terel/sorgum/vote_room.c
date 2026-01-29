inherit "/std/room";
     
#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"
#include "tomb/tomb.h" /* fix this later */

#define PORDIR TOWNDIR + "mansion/porcia/"

string *TerelWiz = ({"Cedric", "Mecien", "Vader", "Azireon", "Janus",
		     "Redhawk", "Mortricia", "Dust", "Sorgum"});

string *voters = ({"", "", "", "", ""});

int *taken = ({0, 0, 0, 0, 0, 0, 0, 0, 0});
int *sol_done = ({0, 0, 0, 0, 0});
int current = 0;
int solved = 0;

string *sol = ({"nay", "aye", "aye", "aye", "nay",
		"nay", "aye", "aye", "aye", "nay",
		"aye", "nay", "aye", "aye", "nay",
		"nay", "nay", "aye", "aye", "nay",
		"nay", "aye", "nay", "aye", "nay"});

int ask_next();

init()
{
     ::init();
     add_action("answer_func", "answer");
     add_action("solve_func", "solve");
     add_action("read_func", "read");
}

void reset_room()
{
     int i, x;
     for (i = 0; i < sizeof(taken); i++)
	  taken[i] = 0;

     for (i = 0; i < sizeof(sol_done); i++)
	  sol_done[i] = 0;

     current = 0;
     
     for (i = 0; i < 5; i++) {
	  do {
	       x = random(sizeof(TerelWiz));
	  } while (taken[x] == 1);
	  taken[x] = 1;
	  voters[i] = TerelWiz[x];
     }
     write("There is a blinding flash of light and the sign is " +
	   "magically altered.\n");

     tell_room("There is a blinding flash of light and the sign is " +
	       "magically altered.\n");     
}
     
void
create_room()
{
    object door, key;
    
    set_short("Vote room");
    set_long(BSN(
        "This is the council chamber.  There is a sign on " +
	"the wall.  There is a column in the center of the room with " +
	"an oracle set into it."
    ));

    reset_room();
    
    add_item(({"sign", "wall"}), "@@desc_sign");
    add_item(({"oracle", "column"}), BSN(
       "The oracle accepts solutions to the puzzle.  Make sure you read " +
       "the sign first though."
    ));				   

    add_prop(ROOM_I_INSIDE, 1);
}

string
desc_sign()
{
return(BSN(
      "A council of five Terel wizards recently voted on on five proposals " +
      "concerning the domain of Terel.  Each of the five council members-- " +
      implode(voters[0..3],", ") + " and " + voters[4] + "-- cast an aye or " +
      "a nay vote for each of the five proposals, with no abstentions.  " +
      "You must deduce how each council member voted on each proposal, " +
      "given the following clues:") +
	   
      "\n1. Each proposal got a different number of aye votes." +

      "\n2. All in all, there was one more aye vote than nay vote cast." +
	   
      "\n3. At no point in time did " + voters[2] + " vote nay on two " +
	  "consecutive proposals." +
	   
      "\n4. " + voters[0] + ", " + voters[1] + ", " + voters[4] +
	   " voted the same way on the second proposal." +
	   
      "\n5. " + voters[3] + " voted aye on the fourth proposal." +
	   
     "\n6. " + voters[2] + " and " + voters[4] + " voted differently on " +
       "each of the first three proposals." + 
	   
      "\n7. The third proposal received one more aye vote than the second " +
         "proposal did.\n\n" +

       BSN("When you think you have solved the puzzle you can use 'solve' " +
	   "to give you answer to the oracle.  " +
	   "Be careful!  Answering incorrectly could prove to be very " +
           "dangerous.")
       
 );
}

int get_next()
{
     int x;
     
     do { x = random(5); } while(sol_done[x] == 1);
     return x;
}

int solve_func(string str)
{
     write(BSN("The oracle bellows: You have awakened the oracle!  Now you " +
         "must solve the puzzle or else incur my wrath!  You must use the " +
	 "'answer' command to enter your answers.  For example: 'answer " +
	 "aye aye nay aye nay'."));

     current = get_next();
     solved = 0;
     return ask_next();
}

int ask_next()
{
     write(BSN("How did " + voters[current] + " vote?"));
     return 1;
}
      
int answer_func(string str)
{
     string *ans;
     int i;
     
     notify_fail("bad syntax.\n");
     
     ans = explode(str, " ");
     if (sizeof(ans) != 5) {
	  write("There were 5 proposals, not " + sizeof(ans) + "\n");
	  return 0;
     }

     for (i = 0; i < 5; i++) {
	  if ((ans[i] != "aye") && (ans[i] != "nay")) {
	       write("You typed something other than 'aye' or 'nay'\n");
	       return 0;
	  }
	  
	  if (ans[i] != sol[current*5 + i]) {
	       write("Your solution is wrong!\n");
	       reset_room();	       
	       TP->move_living("X", PORDIR + "nimroom");
	       return 1;
	       break;
	  }
     }
     write("Your solution for how " + voters[current] +" voted is correct!\n");
     if (++solved == 5) {
	  reset_room();
	  write("You solved the entire puzzle!\n");
	  return 1;
     }
     sol_done[current] = 1;
     current = get_next();
     ask_next();
     return 1;
}
     
read_func(string str)
{
     notify_fail("Read what?\n");
     if (str == "sign") {
	  write(desc_sign());
	  tell_room("Reads the sign.\n");
	  return 1;
     }
     return 0;
}
