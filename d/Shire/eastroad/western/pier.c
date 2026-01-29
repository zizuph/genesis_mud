/*
 * Brandybuck Ferry pier, West side
 * -- Finwe, March 2005
 */

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "local.h"


inherit BASE_COMMON;
inherit EAST_ROAD;
#define IS_ELF_GR_TRAVELLER "/d/Shire/std/elf_gr_patrol.c"
inherit IS_ELF_GR_TRAVELLER;


#define GR_PATROL_LOG    "/d/Shire/log/elf_gr_patrol"
#define WRITE_NAME(o)  sprintf("%-11s", capitalize((o)->query_real_name()))

#include "/d/Gondor/common/mordor/sys/clock.h"

int lamp_status = 0; // 0 lamp off, 1 lamp on
int lamp_id;

void lamp_off();
string lamp_check();

/*
object _clock;
int lamp_check = 0; // 0 lamp off, 1 lamp on

string lamp_check();


void my_dusk_function()
{
    say("A hobbit wanders by and lights the lantern.\n");
    lamp_check = 1;

    set_alarm (
      itof (
        (_clock->dusk (_clock->game_time () + 1) - 
	 _clock->game_time ()) / 10),
      0.0, &my_dusk_function ());
}

void my_dawn_function()
{
    say("A hobbit comes by and extinguishes the lantern.\n");
    lamp_check = 0;
    set_alarm (
      itof (
        (_clock->dawn (_clock->game_time () + 1) - 
	 _clock->game_time ())),
      0.0, &my_dawn_function ());

}
*/

void
create_er_room()
{
    areadesc = "wooden pier";
    area = "over";
    areaname = "the Brandywine river";
    land = "Eriador";
    areatype = 0;

    grass = "green";
    
    extraline = "The Brandywine flows under the pier, which streches " +
    "east over it. The pier is wide and looks well used. Trees grow on " +
    "either side of it, partially obscuring the pier. A lantern hangs " +
    "from a pole on one side of the pier. It is " + lamp_check() + ".";

    set_add_plains();
    set_add_brandywine();
    set_add_road();
    set_add_plants();

    add_item(({"pier", "platform", "wooden platform"}),
        "It's a wooden platform that extends from the road out to " +
        "the river. The lantern hangs from a sturdy " +
        "pole on the the pier.\n");
    add_item(({"wood"}),
        "The wood is dark and sturdy. Wide planks were used to make " +
        "the pier, and large trunks for pilings to support it.\n");
    add_item(({"planks", "wood planks", "wide planks", "plank", "wood plank", 
            "wide plank"}),
        "The wood planks are made from smooth lengths of wood. They " +
        "are thick and strong. The planks are laid horizontally across " +
        "the top of the pier.\n");
    add_item(({"wood pilings", "pilings", "wood piling", "piling"}),
        "They are thick and set into the river. They support the pier " +
        "above the river and look sturdy.\n");

// lamp descriptions
    add_item(({"lantern"}),
        "It has a flat bottom, six sides, and the top tapers to a point. " +
        "It hangs from a sturdy pole set into the pier. It is " + 
        lamp_check()+ ".\n");
    add_item(({"sides", "six sides", "sides of lantern", "six sides of lantern"}),
        "They are flat and square shaped. The top of each side bends " +
        "inward to a point.\n");
    add_item(({"bottom of lantern", "lantern bottom"}),
        "It is flat and six sided.\n");
    add_item(({"top of lantern", "point of lantern"}),
        "It is six-sided and forms a small point on top of the lantern.\n");
    add_item(({"pole", "sturdy pole"}),
        "The sturdy pole is long and thick. The top is 'L' shaped, " +
        "and runs parallel with the pier. From that end hangs a lantern.\n");
  
    add_exit(EAST_R_DIR + "er21s4", "west",0,2);



  //_clock = find_object (CLOCK);

// turns on lantern in the PM    
/*
    set_alarm (
      itof (
        (_clock->dusk (_clock->game_time () + 1) - 
	 _clock->game_time ()) / 10),
      0.0, &my_dusk_function ());

// turns off lantern in the AM
    set_alarm (
      itof (
        (_clock->dawn (_clock->game_time () + 1) - 
	 _clock->game_time ())),
      0.0, &my_dawn_function ());
*/
} // end of room create_er_room




public void
enter_inv(object ob, object from)
{   
    string *names;
    ::enter_inv(ob, from);
    
    names = ob->query_names();
    
    if (file_size(GR_PATROL_LOG) > 1000)
	{
	    rename(GR_PATROL_LOG, (GR_PATROL_LOG + ".old"));
	}

    
    if(ob->id(npc_name))
    {    
         // Remove any NPC travellers
         set_alarm(1.0, 0.0, ob->remove_object());
         write_file(GR_PATROL_LOG, (ctime(time()) + " "+  WRITE_NAME(npc_name) + " Completed.\n"));

    }
}

void
init()
{
    ::init();

//    add_action("light_lamp", "light");
//    add_action("extinguish_lamp", "extinguish");

}


string lamp_check()
{
    if(lamp_status == 0)
        return "unlit";
    else if(lamp_status == 1)
        return "lit";
}


 string light_lamp(string str)
{
    if(!str)
        return "Light what, the lantern?\n";

    if(!lamp_status)
    {
        say(QCTNAME(TP) + " lights the lantern hanging on the pier.\n");
        write("You light the lantern hanging on the pier.\n");
        lamp_id = set_alarm(1800.0,0.0, &lamp_off(TP, 1));
        lamp_status = 1;
        return "";
    }
write(lamp_status + "\n");
    write("The lamp is already lit.\n");
    return "";
}

string extinguish_lamp(string str)
{
        if(!str)
        return "Extinguish what, the lantern?\n";

    if(!lamp_status)
    {
        say(QCTNAME(TP) + " extinguishes the lantern hanging on the pier.\n");
        write("You extinguish the lantern hanging on the pier.\n");
        remove_alarm(lamp_id);
        lamp_status = 1;
        return "";
    }
}

string lamp_off()
{
    lamp_status = 0;
    say("A hobbit walks up the pier and extinguishes the lamp. He then walks away.\n");
    return "";
}