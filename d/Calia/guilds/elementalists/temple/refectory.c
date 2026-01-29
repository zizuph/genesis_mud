/*
 * Refectory of the Elemental Temple of Calia
 * 
 * Created by Petros, April 2010
 * Mirandus - November 24, 2020
 *    - Fixed the Task Six answering issue.
 */

#pragma strict_types

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <mail.h>

inherit TEMPLE_ROOM_BASE;
inherit "/d/Sparkle/area/city/library/room/library_lib";
inherit "/lib/pub";

// Defines

// Prototypes
object tiashe;
string task, summary;
int question;

/*
 * Function:    my_time
 * Description: Returns the time format used for logs.
 */
public string
my_time()
{
    return (ctime(time())[4..9] + ": ");
}

void
reset_room()
{
     if (!objectp(tiashe)) { 
         tiashe = clone_object(ELEMENTALIST_NPCS +"tiashe");
         tiashe->set_width_desc("lean");
         tiashe->set_height_desc("tall"); 
         tiashe->move_living("steps out from behind a counter", TO); 
     } 
}

public void
create_temple_room()
{
    set_short("Refectory");
    set_long("This chamber is the refectory of this temple. It is here so that "
		+ "members of the Elemental Circle and their guests can nourish "
		+ "themselves. Rows of long tables fill the chamber, aside each are "
		+ "long benches. On one wall you notice a menu. A small row "
		+ "of slender windows on the northern wall "
		+ "allows the light and fragrances of the garden to enter the room. "
		+ "It is possible to go south to the outer circle or out through a "
		+ "door leading to the east.\n\n"); 
			
	try_item( ({"rows", "tables", "benches"}),
		"There are rows of long tables in the chamber and beside each of them "
		+ "are long benches, one on each side. They are made of wood and look "
		+ "comfortable.\n");
		
    try_item(({"door","small door","wooden door","small wooden door"}),
        "It is a small wooden door set into the eastern wall.\n");
	
	try_item( ({"window", "windows", "fragrances"}), 
		"Slender windows in the marble north wall sit just below the ceiling "
		+ "and the daylight and flowery fragrances of the garden outside "
		+ "flow through the room, giving the refectory a brisk yet calming "
		+ "feel.\n");
             
    try_item(({"pricelist","menu"}),"It appears to have the prices of "+
        "all of the things you can order here. Perhaps you should "+
        "read it.\n");
    add_cmd_item("pricelist","read","@@read");
    add_cmd_item("menu","read","@@do_read");
    
    add_drink(({"bottle","water bottle","water bottles","bottles","water"}),
        ({"bottle","water bottle","water bottles","bottles","water"}),
        "bottle",100,0,12,"bottle of water","bottles of water",
        "It's a refreshing bottle of clear water.\n",0);

    add_drink(({"milk","milk glass","glass","glass of milk","milks",
        "glasses","glasses of milk","milk glasses"}),
        ({"milk","milk glass","glass","glass of milk","milks",
        "glasses","glasses of milk","milk glasses","glass of milk"}),"glass",
        135,0,15,"glass of milk","glasses of milk",
        "It is an ice cold glass of milk.\n",0);
    
    add_drink(({"jug","water jug","water jugs","jugs","water"}),
        ({"jug","water jug","water jugs","jugs","water"}),
        "jug",600,0,50,"jug of water","jugs of water",
        "It is a refreshing jug of clear water.\n",0);

    add_drink(({"pot","pot of tea","pots of tea","teas","pots","tea"}),
        ({"pot","pot of tea","pots of tea","teas","pots","tea"}),
        "pot",600,0,50,"pot of tea","pots of tea",
        "It is a perfectly steeped pot of tea.\n",0);

    add_food(({"muffin","small muffin","small muffins","small muffin"}),
        ({"muffin","small muffin","small muffins","small muffin"}),
        "small", 30, 25, "small muffin",
        "small muffins",
        "It is a small muffin.  It looks very delicious.\n",0);

    add_food(({"cookie","chocolate chip cookie","chocolate chip cookies",
        "chocolate cookie","chocolate cookies","cookies"}),
        ({"cookie","chocolate chip cookie","chocolate chip cookies",
        "chocolate cookie","chocolate cookies","cookies"}),"chocolate chip",
        30, 25, "chocolate chip cookie",
        "chocolate chip cookies",
        "It is a chocolate chip cookie.  It looks very delicious.\n",0);

    add_food(({"stick","sticks","bread stick","bread sticks",
        "bread","breads"}),({"stick","sticks","bread stick","bread sticks",
        "bread","breads"}),"bread",  65, 80, "bread stick",
        "bread sticks","It is a fresh baked bread stick.\n",0);

    add_food(({"broth","broths","herb broth","herb broths"}),
        ({"broth","broths","herb broth","herb broths"}),"herb",
        100,100,"bowl of herb broth","bowls of herb broth",
        "It is a fairly large bowl of herb broth. It looks and smells "+
        "quite delicious.\n",0);

    add_food(({"sandwich","cheese sandwich","sandwiches","cheese sandwiches"}),
        ({"sandwich","cheese sandwich","sandwiches","cheese sandwiches"}),"cheese",
        150,150,"cheese sandwich","cheese sandwiches",
        "It is a cheese sandwich.\n",0);
    add_exit(ELEMENTALIST_TEMPLE + "herb_garden", "east", "@@cannot_enter_middle_circle", 1, "@@cannot_see_middle_circle");
    add_exit(ELEMENTALIST_TEMPLE + "outer4", "south");
    reset_room(); 
}

public int
library_write_access()
{
	if (!GUILD_MANAGER->query_can_do_wor_task_two(TP))
	{
	    if(!GUILD_MANAGER->query_can_do_ec_task_six(TP))
    	{
    		notify_fail("What?\n");	
    		return 0;
    	}
    }
	if (GUILD_MANAGER->query_can_do_wor_task_two(TP) > 8)
	{
		notify_fail("You have already completed this task.\n");
		return 0;
	}
	if (GUILD_MANAGER->query_can_do_ec_task_six(TP) > 6)
	{
		notify_fail("You have already completed this task.\n");
		return 0;
	}
	return 1;
}

public int
library_write(string str)
{
	string input, task_question;
    if (!library_write_access())
    {
        return 0;
    }
    if (GUILD_MANAGER->query_can_do_wor_task_two(TP) < 9)
    {
    	if (!GUILD_MANAGER->query_can_do_ec_task_six(TP))
    	{
	        task = "Task two";
	        question = (GUILD_MANAGER->query_can_do_wor_task_two(TP));    
	        setuid();
	        seteuid(getuid());
	        switch(question)
	        {
	        	case 1:
	        		task_question="What does the Lord of the Flames and his Element "+
	        		    "of Fire define for you?";
	        		break;
	        	case 2:
	        		task_question="What does the Lady of the Winds and her Element "+
	        		    "of Air define for you?";
	        		break;
	        	case 3:
	        		task_question="What does the Lord of the Seas and his Element "+
	        		    "of Water define for you?";
	        		break;
	        	case 4:
	        		task_question="What does the Lady of the Earth and her Element "+
	        		    "of Earth define for you?";
	        		break;
	        	case 5:
	        		task_question="What does Psuchae and the Element "+
	        		    "of Spirit define for you?";
	        		break;
	        	case 6:
	        		task_question="Name me the places in the Realms where you personally, "+
	        		    "clearly perceive the Five, and why this is significant for you.";
	        		break;
	        	case 7:
	        		task_question="Explain which of the Five you would dedicate yourself "+
	        			"to, should you be accepted into the Circle, and why that is so.";
	        		break;
	        	case 8:
	        		task_question="What do you feel the Five want from us?";
	        		break;
	        	default:
	        		task_question="There is a problem. Please inform the council.";
	        		break;
	        }
	        write(task_question+"\n");
	        clone_object(EDITOR_OBJECT)->edit(&done_writing(task,input));
	        return 1;
    	}
    }

    task = "Task six";
    question = (GUILD_MANAGER->query_can_do_ec_task_six(TP));    
    setuid();
    seteuid(getuid());
    switch(question)
    {
    	case 1:
    		task_question="Given that we are both Elemental Servants and "+
    		    "Kyrullians, explain to me who the Clerics of this Temple "+
    		    "are.";
    		break;
    	case 2:
    		task_question="What behaviour would you expect from such a Cleric?";
    		break;
    	case 3:
    		task_question="How do the Clerics handle conflicts internally and "+
    		    "externally?";
    		break;
    	case 4:
    		task_question="How do the Clerics approach outsiders?";
    		break;
    	case 5:
    		task_question="How do the Clerics stand in regards to the moral "+
    		    "strifes of good and evil?";
    		break;
    	case 6:
    		task_question="How do the Clerics view wars of dominion?";
    		break;
    	default:
    		task_question="There is a problem. Please inform the council.";
    		break;
    }
    write(task_question+"\n");
    clone_object(EDITOR_OBJECT)->edit(&done_writing(task,input));
    return 1;

}

public int
done_writing(string task, string summary, string input)
{
    if (!strlen(input))
    {
        library_write_abort_hook();
        return 0;
    }
    
    if (task == "Task two")
    {
        switch(question)
        {
        	case 1:
        		write("You finish your submission and hand it to Tiashe.\n"+
        		    "When you are ready, you can <ask Tiashe faith task> for "+
        		    "the next question.\n");
        		GUILD_MANAGER->set_can_do_wor_task_two(TP,2);
        		GUILD_MANAGER->set_task_two_answer_one(TP, input);
        		return 1;
        		break;
        	case 2:
        		write("You finish your submission and hand it to Tiashe.\n"+
        		    "When you are ready, you can <ask Tiashe faith task> for "+
        		    "the next question.\n");
        		GUILD_MANAGER->set_can_do_wor_task_two(TP,3);
        		GUILD_MANAGER->set_task_two_answer_two(TP, input);
        		return 1;
        		break;
        	case 3:
        		write("You finish your submission and hand it to Tiashe.\n"+
        		    "When you are ready, you can <ask Tiashe faith task> for "+
        		    "the next question.\n");
        		GUILD_MANAGER->set_can_do_wor_task_two(TP,4);
        		GUILD_MANAGER->set_task_two_answer_three(TP, input);
        		return 1;
        		break;
        	case 4:
        		write("You finish your submission and hand it to Tiashe.\n"+
        		    "When you are ready, you can <ask Tiashe faith task> for "+
        		    "the next question.\n");
        		GUILD_MANAGER->set_can_do_wor_task_two(TP,5);
        		GUILD_MANAGER->set_task_two_answer_four(TP, input);
        		return 1;
        		break;
        	case 5:
        		write("You finish your submission and hand it to Tiashe.\n"+
        		    "When you are ready, you can <ask Tiashe faith task> for "+
        		    "the next question.\n");
        		GUILD_MANAGER->set_can_do_wor_task_two(TP,6);
        		GUILD_MANAGER->set_task_two_answer_five(TP, input);
        		return 1;
        		break;
        	case 6:
        		write("You finish your submission and hand it to Tiashe.\n"+
        		    "When you are ready, you can <ask Tiashe faith task> for "+
        		    "the next question.\n");
        		GUILD_MANAGER->set_can_do_wor_task_two(TP,7);
        		GUILD_MANAGER->set_task_two_answer_six(TP, input);
        		return 1;
        		break;
            case 7:
        		write("You finish your submission and hand it to Tiashe.\n"+
        		    "When you are ready, you can <ask Tiashe faith task> for "+
        		    "the next question.\n");
        		GUILD_MANAGER->set_can_do_wor_task_two(TP,8);
        		GUILD_MANAGER->set_task_two_answer_seven(TP, input);
        		return 1;
        		break;
        	case 8:
        		write("You finish your submission and hand it to Tiashe.\n"+
        		    "Tiashe nods at you.\nTiashe telepathically says to you: "+
        		    "You have answered all of my questions and completed my "+
        		    "task. Please inform the council that you have done so.\n");
        		string log_message = capitalize(TP->query_real_name()) + " has completed task 2.\n";
        		COUNCIL_LOG_BOOK->update_log_book(my_time() + log_message);    
        		GUILD_MANAGER->set_can_do_wor_task_two(TP,9);
        		GUILD_MANAGER->set_task_two_answer_eight(TP, input);
        		return 1;
        		break;
        	default:
        		write("You finish your submission but there is a problem. "+
        		    "please notify the council.\n");
        		return 1;
        		break;
        }
    }
    if (task == "Task six")
    {
        switch(question)
        {
        	case 1:
        		write("You finish your submission and hand it to Tiashe.\n"+
        		    "When you are ready, you can <ask Tiashe servitude task> for "+
        		    "the next question.\n");
        		GUILD_MANAGER->set_can_do_ec_task_six(TP,2);
        		GUILD_MANAGER->set_task_six_answer_one(TP, input);
        		return 1;
        		break;
        	case 2:
        		write("You finish your submission and hand it to Tiashe.\n"+
        		    "When you are ready, you can <ask Tiashe servitude task> for "+
        		    "the next question.\n");
        		GUILD_MANAGER->set_can_do_ec_task_six(TP,3);
        		GUILD_MANAGER->set_task_six_answer_two(TP, input);
        		return 1;
        		break;
        	case 3:
        		write("You finish your submission and hand it to Tiashe.\n"+
        		    "When you are ready, you can <ask Tiashe servitude task> for "+
        		    "the next question.\n");
        		GUILD_MANAGER->set_can_do_ec_task_six(TP,4);
        		GUILD_MANAGER->set_task_six_answer_three(TP, input);
        		return 1;
        		break;
        	case 4:
        		write("You finish your submission and hand it to Tiashe.\n"+
        		    "When you are ready, you can <ask Tiashe servitude task> for "+
        		    "the next question.\n");
        		GUILD_MANAGER->set_can_do_ec_task_six(TP,5);
        		GUILD_MANAGER->set_task_six_answer_four(TP, input);
        		return 1;
        		break;
        	case 5:
        		write("You finish your submission and hand it to Tiashe.\n"+
        		    "When you are ready, you can <ask Tiashe servitude task> for "+
        		    "the next question.\n");
        		GUILD_MANAGER->set_can_do_ec_task_six(TP,6);
        		GUILD_MANAGER->set_task_six_answer_five(TP, input);
        		return 1;
        		break;
        	case 6:
        		write("You finish your submission and hand it to Tiashe.\n"+
        		    "Tiashe nods at you.\nTiashe telepathically says to you: "+
        		    "You have answered all of my questions and completed my "+
        		    "task. Please inform the council that you have done so.\n");
        		string log_message = capitalize(TP->query_real_name()) + " has completed task 6.\n";
        		COUNCIL_LOG_BOOK->update_log_book(my_time() + log_message);    
        		GUILD_MANAGER->set_can_do_ec_task_six(TP,7);
        		GUILD_MANAGER->set_task_six_answer_six(TP, input);
        		return 1;
        		break;
        	default:
        		write("You finish your submission but there is a problem. "+
        		    "please notify the council.\n");
        		return 1;
        		break;
        }
    }
}

int
order(string str)
{
    return ::order(str); 
}

int
do_read(string str)
{
    write("\n"+
        "    Water Bottle                  12 cc\n"+
        "    Glass of Milk                 15 cc\n"+
        "    Water Jug                     50 cc\n"+
        "    Pot of Tea                    50 cc\n"+
        "\n"+
        "    Small Muffin                  25 cc\n"+
        "    Chocolate Chip Cookie         25 cc\n"+
        "    Bread Stick                   80 cc\n"+
        "    Bowl Of Herb Broth           100 cc\n"+
        "    Cheese Sandwich              150 cc\n"+
        "\n"+
        "Try 'buy water with gold' if you want to specify what\n"+
        "coin type to pay with, or 'buy 10 water' would get\n"+
        "you ten water from the refectory.\n\n");
    return 1;
}

public int
do_sprinkle(string str)
{
	object invismandala;
	int task_status;
	
	invismandala=present("invismandala",TP);
    task_status = invismandala->query_task_status();
    
	// They are on the child mandala task and should rub powder on the gem
    if (invismandala && task_status == 12)
    {
    	present("Sporos powder",TP)->remove_object();
    	present("Sporos seed shaped gem",TP)->remove_object();
    	write("You sprinkle the powder on the seed shaped gem. The powder is quickly "+
    	    "absorbed by it. The hard surface of the gem becomes softer, "+
    	    "almost skin-like in nature. The surface begins to crack and parts "+
    	    "of it break off into your hands. The surface continues to break "+
    	    "and decay into nothingness, leaving only a fist-sized dark seed.\n"+
    	    "Tiashe telepathically says to you: You should take that dark seed "+
	    	"to Sehis and ask her about it to continue.\n");
    	say(QCTNAME(TP)+" sprinkles some kind of powder onto a gem in "+HIS+
    	    "hands. The hard surface of the gem changes and begins to crack, "+
    	    "parts of it breaking off into "+QTPNAME(TP)+" hands. It continues "+
    	    "to break and decay until all that is left in "+QTPNAME(TP)+" hands "+
    	    "is a fist-sized dark seed.\n");
    	clone_object(ELEMENTALIST_OBJS+"raw_sporos")->move(TP,1);
    	invismandala->set_task_status(13);    		
    	return 1;
    }
    
    NF("What?\n");
    return 0;
}

public void
init()
{
    ::init();
    init_genesis_library();
    init_pub();
    add_action(library_write, "answer");
    add_action(do_sprinkle,"sprinkle");
}
