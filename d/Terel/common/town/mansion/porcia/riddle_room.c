/* 921016: Dust: Riddle room for porcia quest */
/*
    Modified: 30 Apr 2003, by Bleys
        - Fixed a typo in an add_item()
*/

inherit "/std/room";
// #include "/d/Terel/common/terel_defs.h"
#include "/d/Terel/include/Terel.h"

#include <stdproperties.h>
#include <macros.h>
#define PORDIR TOWNDIR + "mansion/porcia/"
#define DBASE PORDIR + "riddles"

#include "/d/Terel/include/zodiac.h"

string	riddle_text,*door_text = ({ "","","" }),
	*attribs = ({"gold","silver","lead"});
int *damage = ({ 0,0,0 }); 
object gold,silver,lead;

/*
 * It contains a hint for the secret door
 * There are several hints spread, this is
 * hint number HINT_INDEX
 */
#define HINT_INDEX 2


/* query_final_hint delivers the final hint string for the picture in
 * the right solution room
 */
string
query_final_hint()
{
    return(break_string("After you clean the painting, you can make out the " +
	       "painting of the maid Porcia, wearing " + HINT[HINT_INDEX] +
		"clothes.\n",70) +
		"Next to her there's the picture of " + SIGPR[calc_hint(2)] +
	       SIGEQ[calc_hint(2)] + ".\n");
}


int
get_damage(int i)
{
    return(damage[i]);
}

void
reset_room() { 
    int line_number,riddle_number,i,j,k,riddles,*order,*orders;
    string line,whole_line; 
    string *lin; 
    object gold_room,silver_room,lead_room;

    line_number = 0; riddles = 0; 
    /* Read number of riddles out of file */ 
    while (!riddles) {
	line_number++; line = read_file(DBASE,line_number,1);
	lin = explode(line,"");
	if (lin[0] == "#") continue;
	sscanf(line,"%d",riddles);
    }
    riddle_number = random(riddles) + 1; /* Choose a riddle */
    /* offset to selected riddle */
    while (riddle_number) {
	line_number++; line = read_file(DBASE,line_number,1);
	lin = explode(line,"");
	if (lin[0] == "@") riddle_number--;
    }
    /* Read general description */
    riddle_text = "";
    while (1) {
	line_number++; line = read_file(DBASE,line_number,1);
	lin = explode(line,"");
	if (lin[0] == "#") continue;
	if (lin[0] == "*") break;
	riddle_text = riddle_text + line;
    }
    /* Choose one of 6 possible orders gold-silver-lead */
    orders = ({0,1,2,0,2,1,1,0,2,1,2,0,2,0,1,2,1,0});
    i = random(6);
    order = slice_array(orders,i*3,i*3+2);
    /* Read in the 3 damage values */
    for (i=0; 1; i++) {
	while(1){
	    line_number++; line = read_file(DBASE,line_number,1);
	    lin = explode(line,"");
	    if (lin[0] == "#") continue;
	    break;
	}
	if (lin[0] == "*") break;
	sscanf(line,"%d",k);
	damage[order[i]] = k;
    }
    /* Read in the 3 riddle texts */
    for (i=0; i<3; i++) {
	whole_line = "";
	while(1){
	    line_number++; line = read_file(DBASE,line_number,1);
	    lin = explode(line,"");
	    if (lin[0] == "#") continue;
	    if (lin[0] == "*" || lin[0] == "@") break;
	    for (j=0; j<sizeof(lin); j++) {
		if (lin[j] == "&") {
		    j++;
		    sscanf(lin[j],"%d",k);
		    whole_line = whole_line + attribs[order[k]];
		} else whole_line = whole_line + lin[j];
	    }
	}
	door_text[order[i]] = whole_line;
    }
    gold->reset_door();
    silver->reset_door();
    lead->reset_door();
    gold->set_desc(door_text[0]);
    silver->set_desc(door_text[1]);
    lead->set_desc(door_text[2]);
    tell_room(this_object(),break_string("Suddenly, the sign and all the " +
	"inscriptions on the doors flicker and disappear. A second later, " +
	"new inscriptions appear at the same places.\n",70));
}

create_room()
{
    set_short("porcia's room");
    set_long(break_string("This is a very unusual room. It is very dusty " +
	"and dirty, it seems nobody entered this room for centuries. " +
	"The most unusual feature of the room are three doors, a golden " +
	"door leading to the north, a silver door to the west, and a lead " +
	"door to the south. There's a painting above the entrance to the " +
	"east and a sign just next to it. Each of the three doors has some " +
	"text embossed in them. You wonder what awaits you behind " +
	"them...\n",70));
    add_item("painting",break_string("This very ancient looking painting " +
	"shows the painting of a young maid. In the background you see " +
	"the landscape of Venice. At the bottom of the painting you can " +
	"make out the name 'Porcia'.\n",70));
    add_item("sign","It looks like a normal sign. Maybe you should read it?\n");
    add_cmd_item("sign",({"read"}),({"@@riddle_desc"}));
    add_prop(ROOM_I_INSIDE,1);
    add_exit(PORDIR + "entrance","east",0);
    gold = clone_object(PORDIR + "door_gold");
    gold->move(this_object());
    silver = clone_object(PORDIR + "door_silver");
    silver->move(this_object());
    lead = clone_object(PORDIR + "door_lead");
    lead->move(this_object());
    reset_room();
}

string
riddle_desc()
{
    say(QCTNAME(this_player()) + " carefully reads the sign.\n");
    return(break_string("Behind one of those three doors you'll find " +
	"wisdom and the picture of Porcia. But be warned - if you enter " +
	"the wrong room, you'll probably be killed, so find a wise " +
	"decision. The doors themselves bear inscriptions that help " +
	"you to make up your decision.\n",70) + riddle_text);
}

