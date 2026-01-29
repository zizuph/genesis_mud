/* 
 *
 * Main instanceobject. This is the first room in an instance.
 *
 * Nerull 2021
 *
 */

#include "/d/Gondor/rhovanion/defs.h"
#include <stdproperties.h>
#include <macros.h>
 
inherit RHOVANION_DIR + "dolguldur/std/base";

#define INSTANCEKEY       "_instancekey_access"
#define MM_GURUQUEST      "_on_mm_quest"
#define FOUND_MM_BOOK     "_found_mm_book"

object instances_room = 0;
int direction = 0;
int instancekey = 0;


/*
 * Function name: set_direction
 * Description  : Sets the next direction of the dungeon.
 */
void
set_direction(int i)
{
    direction = i;
}


/*
 * Function name: block_player
 * Description  : If a monster is present, it will block the desired exit.
 */
public int
block_player()
{
    if (this_player()->query_prop(MM_GURUQUEST) 
        && this_player()->query_prop(FOUND_MM_BOOK)) 
    {
        return 0;
    }
	
	write("The underbrush is too thick for you!\n");
	
    return 1;
}


/*
 * Function name: set_instancekey
 * Description  : Set key to enter the instance.
 */
void
set_instancekey(int i)
{
    instancekey = i;
}


int
query_instancekey(int i)
{
    return instancekey;
}



/*
 * Function name: query_instancetype_long
 * Description  : The longdescriptors of the intermediate rooms.
 */
void
query_instancetype_descr()
{
	int z = random(10);

	if (z == 0)
	{
		instances_room->set_short("A large black granite room.");

		instances_room->set_long("This room is a huge circle, at "
		+"least "
		+"twenty meters across and a ceiling which is almost five "
		+"meters up. The room has a massive "
		+"black granite square slab in its center, surrounded by "
		+"four smaller slabs at its base. The floor, walls and "
		+"ceiling are all made with smooth black granite and the "
		+"only blemish are the doors which break the circle.\n");

		instances_room->add_item(({ "massive slab" }), "This slab "
		+"is a square of black granite which has sides that are "
		+"three meters in length and stands chest high to a "
		+"normal man. It surface is covered in a dried substance "
		+"and marred only by four carved divots.\n");

		instances_room->add_item(({ "smaller slabs" }), "These "
		+"slabs "
		+"have several worn indentions on their surfaces, where "
		+"many knees"
		+"have fallen to pray.\n");

		instances_room->add_item(({ "slab surface", "surface" }),
		"The four "
		+"divots are half spheres which have been carved into each "
		+"corner of the surface, each with its own iron ring "
		+"inset. The "
		+"dried substance smells of death.\n");

		instances_room->add_item(({ "floor" }), "Two rings have "
		+"been worn "
		+"into the floor. One near the walls and one closer to "
		+"the slab.\n");

		instances_room->add_item(({ "rings" }), "These rings are "
		+"very "
		+"noticable and impressed fairly deep into the floor. "
		+"Many many miles of walking must have "
		+"created them.\n");

		instances_room->add_item(({ "walls", "wall" }), "So "
		+"smooth and "
		+"black is the outer wall it feels as if it is "
		+"closing in on you.\n");
	}

	if (z == 1)
	{
		instances_room->set_short("A large white rhodizite room.");

		instances_room->set_long("This room is a huge square, at "
		+"least twenty meters across and a ceiling which is almost "
		+"five meters up. The room has a massive white "
		+"rhodizite circular slab in its center, surrounded by "
		+"four quarter circle slabs at its base. The floor, walls "
		+"and ceiling are all made with millions of rhodizite "
		+"crystals which cause a shimmering effect to infect ever "
		+"inch of the room and cause distant objects to look blurry.\n");

		instances_room->add_item(({ "slab" }), "Easily three meters "
		+"in diameter, this circular slab is covered in tens "
		+"of thousands of white rhodizite crystals. There are "
		+"three equally spaced half spheres carved near the "
		+"edge of the slabs surface, each with its own iron "
		+"ring inset.\n");

		instances_room->add_item(({ "smaller slabs" }), "Covered in "
		+"white rhodizite crystals, which are very sharp, has "
		+"left a dark dried residue to coat the surface of "
		+"these slabs.\n");

		instances_room->add_item(({ "residue" }),
		"It smells of death, as does the surface of the "
		+"main slab, though it seems to have no residue.\n");

		instances_room->add_item(({ "floor" }), "Two dark "
		+"rings surround the slab. One close and one "
		+"near the outer walls.\n");

		instances_room->add_item(({ "rings" }), "These rings "
		+"smell of death. But the crystals below them "
		+"seem unworn, still very sharp.\n");

		instances_room->add_item(({ "walls", "wall" }),
		"Shimmering white walls with two rings of dark "
		+"residue coating them. One ring near a normal "
		+"mans knees and the other near the chest.\n");
	}

	if (z == 2)
	{
		instances_room->set_short("A dark eerie corridor.");

		instances_room->set_long("This is a dark eerie "
		+"corridor. Dust and cobwebs are everywhere, only "
		+"interrupted by your footsteps hitting the floor "
		+"which consists of large dusty stoneslabs. You "
		+"feel definitely threatened by the dark and "
		+"creepy environment, as if the murky shadows  "
		+"could grow and envelop you at any time.\n");

		instances_room->add_item(({ "shadow", "shadows" }), "While "
		+"the corridor is relatively straight, you still feel "
		+"some unnatural presence of eerie and perpaps "
		+"animated shadows lingering about.\n");

		instances_room->add_item(({ "floor", "slab", "slabs" }),
		"This part of the corridor uses some sort of large "
		+"slabs made of stone to cover the ground. The slabs "
		+"are definitely dusty.\n");
	}

	if (z == 3)
	{
		instances_room->set_short("A stone-filled corridor.");

		instances_room->set_long("The corridor is filled with stones "
			+ "and fallen rocks. The roof is partially cracked and you can "
			+ "see roots from trees. Obviously the area suffers from "
			+ "long decay and the nature above has taken its toll.\n");

		instances_room->add_item(({ "root", "roots", "tree", "trees", "roof" }),
			"Through time, the roots of the trees above have grown and made "
			+ "intrusions through the solid roof.\n");
	}

	if (z == 4)
	{
		instances_room->set_short("A murky burial chamber.");

		instances_room->set_long("Many loculuses line up each side "
			+ "of the room, filled with dusty remains of the ancient "
			+ "dead. Some of the remains litter the floor as if they "
			+ "fell out of their alcoves or were subject of "
			+ "graverobbery long ago. Cobwebs cover many of the "
			+ "loculuses.\n");

		instances_room->add_item(({ "loculus", "loculuses" }),
			"Niches embedded into the walls to keep the bodies "
			+ "of the dead.\n");

		instances_room->add_item(({ "remain", "remains" }),
			"Decayed corpses of the long dead. Most of them are entirely "
			+ "decomposed and some mummified. Cobwebs and dust covers most "
			+ "of them, including the scattered bones of the remains on "
			+ "the floor.\n");
	}

	if (z == 5)
	{
		instances_room->set_short("A partially collapsed corridor.");

		instances_room->set_long("This curved and partially "
		+"collapsed corridor withess of long decay and "
		+"the intrusion of the outside environment. Streams "
		+"of water continuously fills the murky "
		+"ground. Through cracks in the wall you can see "
		+"black wet mold.\n");

		instances_room->add_item(({ "stream", "streams", "water", "ground", "floor" }),
		"The water streams continuously from cracks in the walls "
		+"and pools up at the ground which seems to consist of "
		+"slabs made of stone.\n");

		instances_room->add_item(({ "mold", "black mold" }), "Through "
		+"the cracks in the walls, you see some black mold. It is "
		+"soaked in water.\n");

		instances_room->add_item(({ "crack", "cracks", "wall", "walls" }),
		"The walls are made of some sort of stone, but is in this place "
		+"very deformed and cracked. Small streams of water comes from "
		+"the cracks, and forms at the bottom of the corridor.\n");
	}

	if (z == 6)
	{
		instances_room->set_short("A stone-filled corridor.");

		instances_room->set_long("The corridor is filled with stones "
		+"and fallen rocks. The roof is partially cracked and you can "
		+"see roots from trees. Obviously the area suffers from "
		+"long decay and the nature above has taken its toll.\n");

		instances_room->add_item(({ "root", "roots", "tree", "trees", "roof" }),
		"Through time, the roots of the trees above have grown and made "
		+"intrusions through the solid roof.\n");
	}

	if (z == 7)
	{
		instances_room->set_short("A large burial chamber.");

		instances_room->set_long("Rows of large stone sarcophaguses lines "
		+"the walls in an upward position. All of the lids are removed, and "
		+"the remains within "
		+"lies in heaps at the bottom. Cobwebs and dust covers the remains "
		+"like fine sheets. The stench of death and decay lingers here "
		+"though, filling your nostrils like unavoidable intrusive "
		+"insects.\n");

		instances_room->add_item(({ "sarcophagus", "sarcophaguses"}),
		"Ancient and eroded with time, these sarcophaguses are all "
		+"opened and plundered by graverobbers long ago. Pathetic "
		+"remains of the skeletons it once occupied lies at "
		+"the bottom in a pile.\n");

		instances_room->add_item(({ "heap", "heaps", "remains" }),
		"The remains are piled in various heaps at the bottom of "
		+"each sarcophagus. Obviously plundered long ago by "
		+"graverobbers.\n");
	}

	if (z == 8)
	{
		instances_room->set_short("A dark flooded corridor.");

		instances_room->set_long("Murky water reaches you to the waist "
		+"this flooded corridor. The reek of rot and decay emanates from "
		+"all around you, and you sense with your feet that you "
		+"step on various bones and remains from corpses. It is "
		+"claustrophobic and a terrible sense of imminent fear "
		+"coming from below almost blinds your judgement.\n");

		instances_room->add_item(({ "water", "murky water" }), "You "
		+ "sense that it's very cold, and it stinks of rot and "
		+ "decay. You prefer to move out of this environment as "
		+ "fast as possible.\n");

		instances_room->add_item(({ "bones", "remains", "corpses" }), "While "
		+"you can't see them, you certainly feel them with your feet. You "
		+"want to move on as fast as possible!\n");
	}

	if (z == 9)
	{
		instances_room->set_short("An empty burrial chamber.");

		instances_room->set_long("Many loculuses line up each side "
		+ "of the room, but they are all empty. You find "
		+"it strange that not even dust or cobwebs occupy them "
		+"to any degree, as if someone was here recently and "
		+"swept them clean.\n");

		instances_room->add_item(({ "loculus", "loculuses" }),
		"They are empty and clean. You contemplate why.\n");
	}
}


/*
 * Function name: add_instance_room
 * Description  : Selects random size and direction of the instance.
 */
void
add_instance_room()
{
    // Random size of instance
    int rooms = 8 + random(4);

    if (instances_room == 0)
    {
       instances_room = clone_object(RHOVANION_DIR
       +"dolguldur/instances/instances_room");

       query_instancetype_descr();
    }
	
	if (direction == 1)
    {
        this_object()->add_exit(file_name(instances_room),
        "west", block_player);

        instances_room->add_exit(file_name(this_object()), "east");
		
		int i = random(5) + 1;

        instances_room->set_direction(i);
        instances_room->set_rooms_left(rooms);

        return;
    }

    if (direction == 2)
    {
        this_object()->add_exit(file_name(instances_room),
        "east", block_player);

        instances_room->add_exit(file_name(this_object()), "west");
		
		int i = random(5) + 1;

        instances_room->set_direction(i);
        instances_room->set_rooms_left(rooms);

        return;
    }

    if (direction == 3)
    {
        this_object()->add_exit(file_name(instances_room),
        "northeast", block_player);

        instances_room->add_exit(file_name(this_object()), "southwest");
		
		int i = random(5) + 1;

        instances_room->set_direction(i);
        instances_room->set_rooms_left(rooms);

        return;
    }

    if (direction == 4)
    {
        this_object()->add_exit(file_name(instances_room),
        "northwest", block_player);

        instances_room->add_exit(file_name(this_object()), "southeast");
		
		int i = random(5) + 1;

        instances_room->set_direction(i);
        instances_room->set_rooms_left(rooms);

        return;
    }

    if (direction == 5)
    {
        this_object()->add_exit(file_name(instances_room),
        "north", block_player);

        instances_room->add_exit(file_name(this_object()), "south");


        int i = random(5) + 1;

        instances_room->set_direction(i);
        instances_room->set_rooms_left(rooms);

        return;
    }

    return;
}


void
remove_instance()
{
    remove_object();
}


/*
 * Function name: create_rav_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_dg_room()
{
    setuid();
    seteuid(getuid());

    add_prop(ROOM_I_INSIDE, 0);
	
	set_direction(4);
    
    // Clean the instance from memory.
    set_alarm(7200.0, 0.0, &remove_instance());

    reset_room();
}


/*
 * Function name: init
 * Description  : When a player arrives, the dungeon keeps building
 * more rooms until the limit is met.
 */
void
init()
{
    if(interactive(this_player()))
    {
        if (instances_room == 0)
        {
            add_instance_room();
        }
    }

     ::init();
}


/*
 * Function name: reset_room
 * Description  : Resets the room/states/npc spawns.
 */
void
reset_room()
{

}

