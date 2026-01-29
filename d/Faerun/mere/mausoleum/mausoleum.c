/*  /d/??/??/mausoleum.c
 *
 *  Main dungeon entranceobject.
 *
 *  Nerull 2017.
 */

inherit "/std/object";

// Inherit this for room tell support!
inherit "/d/Sparkle/lib/room_tell";
#include <stdproperties.h>
#include <macros.h>
#include "dungeon_defs.h";



object instances_main;

object mainentrance;


int open = 0;



int create_dungeon()
{
	object instanceroom0; 
	object instanceroom1;
	object instanceroom2;
	
	int size = random(10) +2;
	
	int first_room = 1;
	
	int primary_direction = random(4);
	
	mainentrance = clone_object(DUNGEON_DIR +"instances_main");
	instanceroom1 = clone_object(DUNGEON_DIR +"instances_room");
		
	mainentrance->add_exit(instanceroom1, "east");
	instanceroom1->add_exit(mainentrance, "west");

	for (int i = 0;i < size;i++)
	{
		instanceroom2 = clone_object(DUNGEON_DIR +"instances_room");
		
		instanceroom1->add_exit(instanceroom2, "east");
        instanceroom2->add_exit(instanceroom1, "west");

        instanceroom1 = instanceroom2;

        instanceroom2 = 0;		
	}
	
	return 1;
}


/*
 * Function name: create_object()
 * Description  : Creates the object we wish to clone.
 */
void
create_object()
{
    setuid();
    seteuid(getuid());

    set_short("sinking broken mausoleum");
    set_name("mausoleum");
    set_adj("sinking");
    add_adj("broken");

    set_long("You stand before a sinking mausoleum. "
    +"Its' stone walls are stained abnormally black. What "
    +"isnt black is covered in thick ivy. A fence once "
    +"kept the perimeter safe, but it has long since "
    +"fallen. It is currently closed.\n");

    add_item(({ "mausoleum" }), "This mausoleum has sunken "
    +"into the ground at least a foot and tilts slightly, "
    +"sloping down towards the back.\n");

    add_item(({ "door", "doors", "entrance", "slabs" }), "The entrance "
    +"into the mausoleum has two massive slabs of "
    +"stone as doors.\n");

    add_item(({ "wall", "walls" }), "Thick stone walls "
    +"which are black and are to be covered by many hand "
    +"prints. Perhaps the very dark aspect isnt just rain "
    +"but oils from the hands of the prints?\n");

    add_item(({ "wall", "walls" }), "Thick stone walls "
    + "which are black and are to be covered by many hand "
    + "prints. Perhaps the very dark aspect isnt just rain "
    + "but oils from the hands of the prints?\n");

    add_item(({ "ivy" }), "A thick green blanket of ivy "
    +"grows over the mausoleum. Eventually, only an ivy "
    +"mound will exist.\n");

    add_prop(OBJ_M_NO_GET, "The "+short()+" is too heavy to "
    +"move.\n");

    add_prop(OBJ_M_NO_STEAL, "The "+short()+" is too heavy to "
    +"steal.\n");
    
    //Room tells.
    set_tell_time(60); 
    start_room_tells();
    add_tell("roo_tell1.\n");
    add_tell("roo_tell1.\n");   

    add_prop(CONT_I_VOLUME,  45000);
    add_prop(CONT_I_WEIGHT,  500000);
	
	
	
	//mainentrance->add_exit(file_name(environment(this_object())), "up");
	
	//mainentrance->add_exit(environment(this_object()), "up");
	
	create_dungeon();
}


/*
 * Function name: close_instance
 * Description  : Returns what happens if someone try to close it.
 */
int
close_instance(string str)
{
    if (str == "mausoleum")
    {
        write("The stoneslabs are stuck in open position.\n");

        return 1;
    }

    return 0;
}


/*
 * Function name: open_instance
 * Description  : opens the mausoleum
 */
int
open_instance(string str)
{
    if (str != "mausoleum")
    {
        return 0;
    }

    if (open == 1)
    {
        write("The mausoleum is open already.\n");
        
        return 1;
    }

    tell_room(environment(this_object()), "The mausoleum "
    +short()+" opens!\n");

    open = 1;


    this_object()->set_long("You stand before a sinking mausoleum. "
        + "Its' stone walls are stained abnormally black. What "
        + "isnt black is covered in thick ivy. A fence once "
        + "kept the perimeter safe, but it has long since "
        + "fallen. It is currently open.\n");

    // Opening the entrance to a dungeon.
    instances_main = clone_object(DUNGEON_DIR +"instances_main");

    // Ancient tomb descriptor for main/first instanceroom.
    instances_main->set_short("Inside an ancient mausoleum");
        
    instances_main->set_long("To the back is a stairwell that sticks "
    +"out above the floor due to the tilt of the mausoleum, but "
    +"still manages to allow access down. On the left side is "
    +"a crypt which has a knightly figured carved in stone "
    +"resting on the top of the sarcophagus. On the right "
    +"side is a black chapel.\n");

    instances_main->add_item(({ "stairwell"}), "Even with all the settling "
    +"of the main structure, the stairs provide a safe "
    +"passage down into the darkness.\n");

    instances_main->add_item(({ "sarcophagus" }), "A marble tomb "
    +"with an elaborately carved knight resting on top. There "
    +"is a large hole in the lid between the knights legs.\n");

    instances_main->add_item(({ "hole" }), "You peer into the "
    +"interior of the sarcophagus and see something towards "
    +"the headspace. It looks white.\n");

    instances_main->add_item(({ "headspace" }), "It looks as "
    +"if the skull of the knight remains in rest.\n");

    instances_main->add_item(({ "chapel" }), "This chapel "
    +"consists of a large black granite slab which is "
    +"surrounded by many candle holders. A smaller "
    +"slab of black granite lays at its base.\n");

    instances_main->add_item(({ "holders" }), "The stands "
    +"are black rods of various heights which end in a golden "
    +"bowl.\n");

    instances_main->add_item(({ "slab", "small slab" }), "It "
    +"has several worn indentions on its surface, where many "
    +"knees have fallen to pray.\n");
    
    //environment(this_object())->add_exit(file_name(instances_main),
    //"enter");

    //instances_main->add_exit(file_name(environment(this_object())), "up");

    return 1;
}

int enter_instance(string str)
{
	if (str == "mausoleum")
	{
		write("You enter the mausoleum!\n");
		
		tell_room(mainentrance, QCNAME(this_player())
        +" arrives from above.\n", this_player());

        tell_room(environment(this_object()), QCTNAME(this_player())
        + " enters the mausoleum.\n", this_player());

        this_player()->move_living("M", file_name(mainentrance), 1);
		
		mainentrance->maus_outside(file_name(environment(this_object())));
		
		write(file_name(environment(this_object())));
		
		return 1;
	}
	
	return 0;
}


/*
 * Function name: create_object()
 * Description  : Creates the object we wish to clone.
 */
void init()
{
    ::init();
    
    //add_action(open_instance, "push");
	
	add_action(enter_instance, "enter");
	
    //add_action(open_instance, "open");
    //add_action(close_instance, "close");
}



