// file name:        /d/Avenir/common/dead/mascarvin/spots.c
// creator(s):       Lilith, May 2021
// revision history: Lilith, Aug 2021: Added checks for quest stages
//                       so mortals can do it in stages if they can't
//                       do it all at once.
// purpose:          Quest Room 2 of the Meet Mascarvin Quest.
//                   Connect the dots to the panels, move along
//                   to next stage.
// note:            
// bug(s):           
// to-do:
inherit "/std/room";
inherit "/d/Avenir/inherit/quest";
#include "/d/Avenir/smis/sys/statserv.h"
#include "/sys/terrain.h"
#include "defs.h"
#include <tasks.h>

string *num;
int    *solution = ({ 0, 0, 0, 0, 0, 0, 0, 0 });
int     tried, door;

object  torchier;

void close_door()
{
      door = 0;
      tell_room(TO, "A panel slowly slides back into place.\n");
	  // Room to the east.
      tell_room(PASSAGE, "You hear a deep rumble, and the "
         +"stone slab to the west rolls back into place.\n");
	  remove_exit("east");
 
}

int go_east()
{
	if (TP->query_skill(SS_MASQ_STAGE) > 1)
		return 0;
    else
	{
	   write("The mist congeals to form a wall that prevents you "
           +"from going east. "
	       +"White dots dance before your eyes.\n");
	   return 1;
    }  
}

void open_door()
{
    tell_room(TO, "You hear a deep rumble far below you, and "
      +"a large slab of stone in the east wall raises to "
      +"reveal an opening into the darkness.\n");
    door = 1;
    add_exit(PASSAGE, "east", go_east);
    tell_room(PASSAGE, "With a low rumble, the large stone "
      +"slab to the west rises, opening into a large, circular "
      +"room.\n");
}


int go_west()
{
    object   hole = find_object(HOLE);

    if(hole && sizeof(filter(all_inventory(hole), interactive)))
    {
        write("There is someone already in the tunnel, and "
             +"you cannot both fit in there together.\n");
        tell_room(HOLE, "Someone seems to be trying to enter "
             +"from the east, but there is not enough room "
             +"for two people in this space.\n");
        return 1;
    }

  write("You climb into the hole.\n");
  say(QCTNAME(TP) + " climbs into the hole.\n");
  return 0;
}

void reset_room()
{

     /* Don't reset while there are players here */
    if(sizeof(filter(all_inventory(TO), interactive)))
      return;

    /* All this hackneyed bit does is pick a random symbol for a certain number,
     * so that, say, 5 can be either ::. or ..... or :.:, etc. */
    num  = ({ ".",
       ONEOF(({"..",":"})),
       ONEOF(({"...",":.",".:"})),
       ONEOF(({"....","::",":..",".:.","..:"})),
       ONEOF(({"::.",":.:",".::","...:",".:.."})),
       ONEOF(({":::","......","...:.",":..:","::..",":.:."})),
       ONEOF(({":.:..",":::.",":.::",":...:"})),
       ONEOF(({"::::",":....:","..::..",":.:.:","::...."})),
       ONEOF(({"::::.",".::::",":.:.:.","::..:.",".:.:.:"})),
       ONEOF(({"::..::",".::::.",".:.:.:.","...::..."})),
       ONEOF(({":..:..:.",".::.::.","::...::",":.:.:.:"})),
       ONEOF(({"::....:: ",":.:.:.:.","::..::..","...:::..."}))
 });

    solution = ({ random(12), random(12), random(12), random(12), 
                  random(12), random(12), random(12), random(12) });
    tried = 0;
    tell_room(TO, "The floor swirls with a rush of colour for "
      +"a moment, and something seems different.\n");

    if(door)
    {
        close_door();
		remove_exit("east");
    }
}  

void 
leave_inv(object to, object from)
{
    ::leave_inv(to, from);
      set_alarm(10.0, 0.0, reset_room);
}

string 
query_solution()
{
    string   str = "";
    int      i;

    for(i=0;i<sizeof(solution);i++)
      str += num[solution[i]] + "  ";

    return str;
}

int 
solution_sum()
{
    int i, sum;

    for(i=0;i<sizeof(solution);i++)
      sum += solution[i] + 1;

      return sum;
}

/* Is the door to the next room open? If so, show in room desc. */
string 
see_door()
{
    if(!door)
        return ""; 

    return " There is an opening along the east side "
        +"of the chamber, leading into a gloomy passage.";
}


/* If there is a torch in the sconce, show it in the room desc */
string 
torchier_inv(void)
{
	if (!torchier)
		return "";
    
	object *inv = filter(all_inventory(torchier), &->query_prop(OBJ_I_HAS_FIRE));

    if (!sizeof(inv)) 
		return "";
	else return "Flickering in the stone block is a "+
	       inv[0]->query_name() + ".";
}

/* Lets give the players their puzzle to solve. Connect the dots. */
public string 
see_dots()
{
    say(QCTNAME(TP) + " stares hard at the pattern on the floor.\n");
    // Is there a ligthed torch in the torch stand? 
    if(!strlen(torchier_inv()))
      return "There seems to be some sort of pattern etched "
         +"into the floor around the torch stand, but the light "
         +"around it is too dim to make them out.\n";
		 
    // Am I too mentally tired to do this?
    if(TP->query_mana() < 40)
      return "You stare at the pattern on the floor, but "
       +"your mind is so tired you cannot make any sense out "
       +"of it.\n";
    
	// Do I have the basic skills to understand what I'm seeing?
    if(TP->resolve_task(TASK_ROUTINE, ({ SKILL_AVG,
        SS_AWARENESS, TS_INT, SKILL_END })) <= 0 && 
        TP->query_prop(SAW_PATTERN) != solution_sum())
    {
      TP->add_mana(-40);
      return "You stare hard at the pattern on the floor, "
       +"but the flickering shadows hurt your eyes and "
       +"you cannot make out the pattern.\n";
    }

    // Player can see the pattern. Now can they connect the dots?
    TP->add_prop(SAW_PATTERN, solution_sum());
    return "Around the base of the torch stand are flat, circular "
	   +"bits of polished bones set into the surface of "
	   +"the floor. Illuminated clearly by the light "
	   +"from the torch stand is the following pattern:\n"
	   +"    "+ query_solution() +"\n";
}

/* You dare cast magic in a god's home? */
public int
anti_magic(object who)
{
    /* Don't bother with uncast spells. */
    if (!who->query_prop(LIVE_I_CONCENTRATE))
	    return 0;

    who->catch_tell("An oppressive force presses upon you like "+
	    "a giant hand closing around you.\n");
 
    /* hurt him some (but don't kill him) */
    who->heal_hp(-50 - random(100));
    who->add_mana(-50 - random(100));
	who->add_fatigue(-50 - random(100));

    /* break his spell */
    who->cmdhooks_break_spell("Your brain flutters wildly in "
	    +"time with your heart.\nA wave of exhaustion rolls "
	    +"over you and you can feel yourself falling forward.\n");
	who->command("$kneel");
	return 1;
	
}


void 
create_room()
{
    set_short("circular room with a stone block in the middle");
	
    set_long("Dead center in this perfectly round "
      +"room is a stone block, and inlaid into the floor "
	  +"around it are pale dots."
      +" @@torchier_inv@@ The wall is high and very "
      +"smooth, and evenly spaced all along it are "
      +"twelve rectangular panels made of reddish stones. "
      +"The panels are spread evenly around the wall, except for "
      +"a space in the west side, where there is a round hole "
      +"leading into a small, dim tunnel. @@see_door@@ "
	  +"Mist flows around you, swirling almost restlessly, "
      +"and whenever it touches you, it imparts a disquieting "
      +"feeling, as though it is hungry. This is not a place "
	  +"you want to linger in.\n");

    add_item(({"mist", "swirls"}), 
	    "A thin white mist moves along the ground, making the "
	   +"walls and floor wet and slippery. Something about it "
	   +"makes you paranoid. You feel as though you are being "
	   +"watched.\n");
    add_item(({"floor","ground"}),"The floor is of smooth-"
      +"packed clay, unadorned except for the area around the "
      +"stone block, which seems to be decorated with patterns "
      +"of some sort.\n");
    add_item(({"dots","pattern","patterns","dot","circle","circles","bones" }),
	   see_dots);
	add_item(({"wall", "walls"}), "The room is circular, all one wall, "
	   +"with rectangular panels spread evenly along it.\n");
    add_item(({"panel","panels","tile","tiles", "rectangles"}),
	    "There are twelve "
      +"reddish rectangular panels spread along the wall at even intervals, "
      +"all appearing to be identical.\n");
    add_item(({"first panel","second panel","third panel","fourth panel",
	    "fifth panel","sixth panel","seventh panel", "eighth panel",
        "ninth panel", "tenth panel", "eleventh panel", "twelveth panel",
        "twelfth panel" }),
		"It looks just like all the rest, shiny reddish stone.\n"
		+"It appears to be somewhat loose.\n");
    add_item(({"tunnel","hole"}),"The hole in the west wall leads "
	  +"into a small tunnel, just large enough for one person "
	  +"to fit into.\n");

    ACI(({"panel","tile","first panel","second panel","third panel",
	    "fourth panel","fifth panel","sixth panel","seventh panel",
		"eighth panel","ninth panel","tenth panel","eleventh panel", 
		"twelveth panel", "twelfth panel"}),
       ({"rattle","shake","pull","lift","wiggle","jiggle"}),
       "It moves slightly. You might be able to push it into the wall.\n");
	add_prop(OBJ_S_WIZINFO, 
	   "This room is part of the Mascarvin Quest. To get "
       +"past this room the player must put a lighted "
	   +"torch in the stone block, examine the dots "
       +"around the stone block, and push the panels "
	   +"that correspond to the dots. Example, if player sees:\n"
       +" ...  :::  :.:.: 	   \n"
	   +"the commands are 'push panel 3', 'push panel 6', and "
	   +"'push panel 8'.\n"
	   +"If player leaves the room the dots reset.\n");
    set_noshow_obvious(1);
    add_exit(HOLE, "west", go_west);
    torchier = clone_object(OBJ +"torch_stand");
    torchier->move(TO);
	
	add_prop(ROOM_M_NO_TELEPORT, 
	    "An angry goddess-figure wreathed in red-gold flames "
       +"appears to prevent you from doing that.\n");
	add_prop(ROOM_M_NO_MAGIC, anti_magic(TP));

	IN;  
    IN_IN;
    set_terrain(({ TERRAIN_SHADOWS, TERRAIN_HASDEAD, TERRAIN_UNDERGROUND,
    	TERRAIN_ROCK }));
	
    reset_room();

}

int 
push(string str)
{
    string   wnum;
    int      num;

    NF(CAP(QVB) + " what?\n");
    if(!strlen(str))
        return 0;

    NF(CAP(QVB) + " which panel?\n");
    if(parse_command(str, ({}), "[the] 'panel' / 'panels'"))
        return 0;

    if(CHECK_QUEST_MASQ(TP))
	{
	   /* TP has done the quest already */
	    write("A feeling of menace and hostility floods your "
	       +"being.\nThe voice of Mascarvin whispers in your ear:"
		   +" It is not wise to attempt this again. Go!\n");
		return 0;
	}
    /* Allow for 'push the second panel' or 'push panel 2' */
    if(!parse_command(str, ({}),
       "[the] 'panel' / 'tile' [number] %d", num) && !parse_command(str, ({}),
       "[the] %w 'panel' / 'tile'", wnum))
        return 0;

    if(strlen(wnum))
        num = LANG_ORDW(wnum);  // translate 'third' -> 3

    NF("There are only twelve panels.\n");
    if(num > 12)
        return 0;

    NF("You do not see that panel.\n");
    if(num < 1)
        return 0;

    NF("It does not budge.\n");
    if(door)
        return 0;

    write("You "+QVB+" the "+LANG_WORD(num)+" panel inwards slightly.\n");
    say(QCTNAME(TP)+" pushes the "+LANG_WORD(num)+" panel "
        +"inwards.\n");

    /* Pushed the wrong panel in the sequence. Start over. */
    if(--num != solution[tried++])
    {
        DEBUG("Wrong panel: pushed " + (num+1) + ", should have been " + solution[tried-1]);

        /* If the (wrong) panel we pushed happens the be the first panel
         * in the correct sequence, allow that to happen 
		 */
        if(num == solution[0])
            tried = 1;
        else
            tried = 0;
    }

    if(tried >= sizeof(solution) && TP->query_prop(SAW_PATTERN) == solution_sum())
    {
        TP->set_skill(SS_MASQ_STAGE, STAGE_2_DOTS);
        open_door();
        tried = 0;
    }

    return 1;
}

int 
query_tried()
{
    return tried;
}

int 
query_door()
{
    return door;
}


void 
init()
{
    ::init();

    add_action("push", "push");
    add_action("push", "press");
    add_action("push", "move");	
}


/* The Meet Mascarvin Quest is done in stages.
 * Move player to the last stage completed  
 * so they don't have to re-do each one.
 */ 
void 
enter_inv(object ob, object from)
{
    int stage;
	
    ::enter_inv(ob, from);
      
    // If not a player, ignore.
    if(!interactive(ob)) return;
	
    //If a wizard, let them stay--they might be helping a mortal.
    //commented out for testing purposes.
 	if(ob->query_wiz_level())  return;

	// If they are trying to leave the quest area, let them out.
	if (file_name(from) == PASSAGE)
	{
		ob->move_living("X", HOLE);
		return;
	}

    // Player already did the quest.
    if(CHECK_QUEST_MASQ(ob))
    {
        write("\n\nYour time in this place has already passed. Begone!\n\n");
		ob->move_living("X", (CRYPT +"crypt"+ random(15)), 1, 0);
		return;
	}

    STATSERV_LOG_EVENT("crypt", "Entered Mascarvin area");
	
    // They are in-progress on this quest...move to where they left off.	
    stage = ob->query_skill(SS_MASQ_STAGE);
    switch(stage)
    {
        case 0:
            set_alarm(1.5, 0.0, &write("\n\nYour mind reverberates with "
			    +"a god's angry voice saying: You should not be here, mortal!\n\n"));
			set_alarm(2.0, 0.0, &ob->move_living("X", HOLE, 1,0));
            break;
        case STAGE_1_HEG:
            set_alarm(1.0, 0.0, &write("\n\nAs you take this first step "
			    +"on the path to meeting Mascarvin, you feel apprehensive.\n\n"));
            break;
        case STAGE_2_DOTS:
            set_alarm(1.0, 0.0, &write("\n\nYou passed this room in your "
			    +"previous attempt to meet Mascarvin, and are ready for "
				+"the next one.\n\n")); 
            set_alarm(2.0, 0.0, &ob->move_living("X", CHALICE, 1, 0)); 	
            break;
        case STAGE_3_MAZE:
            set_alarm(1.0, 0.0, &write("\n\nYou solved the maze when last "
			    +"you came through, but be aware: you may need to do "
				+"so again...\n\n"));
		    set_alarm(2.0, 0.0, &ob->move_living("X", MAZE+"maze13", 1, 0));
            break;
        case STAGE_4_SKULLS:
		    write("\n\nSo you want a meeting with Mascarvin...\n\n");
			set_alarm(1.0, 0.0, &ob->move_living("X", RESTING, 1, 0));
            break;
		case STAGE_5_MEET:
			set_alarm(1.0, 0.0, &ob->move_living("X", RESTING, 1, 0));
            set_alarm(1.5, 0.0, &write("\n\nA voice slams into your "
			    +"mind: We have unfinished business, you and I...\n\n"));
			break;
		case STAGE_6_THIEF:
			set_alarm(2.0, 0.0, &ob->move_living("X", RAGING, 1, 0));
            write("\n\nA voice slams into your mind: Little thief, you "
			    +"cannot escape my notice...\n\n");
            break;
	}
    return;	
}
