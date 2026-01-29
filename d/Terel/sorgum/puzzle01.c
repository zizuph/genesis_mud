inherit "/std/room";
     
#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"
#include "tomb/tomb.h" /* fix this later */

#define PORDIR TOWNDIR + "mansion/porcia/"

string *Guilds = ({"Calian", "Mystic", "Monk", "Vampyr", "Ranger",
		   "Gladiator", "Hin"});

string *Players = ({"Chilliwack", "Dosewallips", "Geoduck", "Moray",
		    "Entiat", "Hobbes", "Skate"});

string *Titles = ({"The Great", "The Unbeatable", "The Hero", "The Brave",
		   "The Menace", "The Strong", "The White"});

string *levels = ({"Beginner", "Apprentice", "Adventurer", "Veteran",
		   "Champion"});

string *guilds = ({"", "", "", "", ""});
string *players = ({"", "", "", "", ""});
string *titles = ({"", "", "", "", ""});

int *taken = ({0, 0, 0, 0, 0, 0, 0});
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

#define CLEAR(xx) for (i = 0; i < sizeof(xx); i++) xx[i] = 0;

void pick(string *choices, string *picks)
{
     int i;
     int x;

     CLEAR(taken);
     
     for (i = 0; i < 5; i++) {
	  do {
	       x = random(sizeof(choices));
	  } while (taken[x] == 1);
	  taken[x] = 1;
	  picks[i] = choices[x];
     }
}

void reset_room()
{
     int i, x;

     CLEAR(sol_done);
     current = 0;
     pick(Guilds, guilds);
     pick(Titles, titles);     
     pick(Players, players);

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
        "This is a puzzle room.  There is a sign on " +
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
      "Each of the five players-- " +
      implode(players[0..3],", ") +
      " and " + players[4] + "-- are in " +
      "guilds, have different titles and are at different levels of " +
      "experience. " +
      "You must deduce the title, guild and experience level of each " +
      "player, given the following clues:") +

       "\n1. " + players[3] + " is a member of the " + guilds[1] + "s.  He " +
            "is not the most experienced of the five, but he is more " +
	    "experienced than the player with the title\n'" + titles[0] +
            "' of the " + guilds[3] + " guild, " +
	    "who is not " + players[4] + ".\n" +

      "\n2. " + players[1] + " is known as '" + titles[1] + "' and " +
       "is not a member of the " + guilds[0] + "s.\n" + 
	   
      "\n3. " + players[2] + " is the " + levels[2] + ".\n" +

	   
      "\n4. '" + titles[0] + "' is not as experienced as the " + guilds[0] +  
	   ".\n" +  
	   
      "\n5.  The " + levels[3] + "does not call himself '" + titles[1] +
             "'.\n" +

      "\n6. " + players[4] + " in spite of his name, is not the most\n" +
	    " experienced of the five.\n\n" +

       "When you think you have solved the puzzle you can use 'solve'\n" +
       "to give you answer to the oracle.\n" +
       "Be careful!  Answering incorrectly could prove to be very\n" +
       "dangerous.\n");
       

       
       
       
       
       
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
	 players[random(5)] + " " + titles[random(5)] + " " +
	 guilds[random(5)] + " " + levels[random(5)] + "'."));

     current = get_next();
     solved = 0;
     return ask_next();
}

int ask_next()
{
     write(BSN("How about " + players[current] + "?"));
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
     write("Your solution for how " + players[current] + " is correct!\n");
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
