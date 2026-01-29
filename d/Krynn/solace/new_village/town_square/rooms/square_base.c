/*
* Solace Town Square Base
* Written by Leia
* May 30, 2005
*/

/*
** Last Updated By:
** Leia
** July 1, 2005
*/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/common/clock/clock.h"
#include "../local.h"

inherit OR_FILE
inherit CONQUER_BASE

#define CREATE "create_solace_room"
#define RESET  "reset_solace_room"

nomask public int
query_reset()
{
	if (function_exists(RESET, TO))
		return 1;
	return 0;
}

string
tod_descr1()
{
   string str;
   switch (GET_TIMEOFDAY)
   {
      case TOD_NIGHT:
      str = "It is night in the town of Solace. ";
      break;
      case TOD_DAWN:
      str = "It is the break of day in the town of Solace. ";
      break;
      case TOD_DAY:
      str = "It is the middle of the day in the town of Solace. ";
      break;
      case TOD_TWILIGHT:
      str = "It is the early evening in the town of Solace. ";
      break;
   }
   return str;
}

string
tod_descr2()
{
   string str;
   switch (GET_TIME_STRING)
   {
      case MIDNIGHT:
      case NIGHT:
      str = "It is dark outside, save for the light of the moon and stars. All around you are the sounds of the creatures of the night. ";
      break;
      case EARLY_MORNING:
      case MORNING:
      str = "The darkness has given way to sunshine and the world about you is bright. The sun warms your face as you look around. ";
      break;
      case EVENING:
      str = "Night has begun to fall and the daylight is quickly fading from view. The temperature is falling, and the crickets are beginning to chirp. ";
      break;
      case NOON:
      case AFTERNOON:
      str = "The sun shines bright around you, and clouds drift slowly through the sky, casting familiar shapes above you. ";
      break;
      
   }
   return str;
}


string
season_descr()
{
   string str;
   switch (GET_SEASON)
   {
      case SPRING:
      str = "A light breeze blows through the air, bringing with it the smell of flowers. ";
      break;
      case SUMMER:
      str = "The humidity of the air stifles your breathing, and the smell of rain is in the air. ";
      break;
      case AUTUMN:
      str = "Wind blows through the area, and the smell of leaves intoxicates your senses. ";
      break;
      case WINTER:
      str = "The air is chilly and the wind here cuts to the bones. ";
      break;
   }
   return str;
}

nomask public void
create_krynn_room()
{
	set_area_name(WAR_AREA_SOLACE);
	call_other(TO, CREATE);
	set_short("Solace Town Square");
	set_long("@@determine_long@@");
	add_item(({"cage","cages"}), "@@determine_cages@@");
	add_item(({"prisoner", "prisoners", "slave", "slaves"}), "@@determine_prisoners@@");
}

int
area_owned_by_armies()
{
    string owner = ARMYMASTER->army_in_area(WAR_AREA_SOLACE);
    if (owner == RED_ARMY || owner == BLUE_ARMY)
    {
         return 1;
    }
    else
    {
        return 0;
    }
}

string
determine_long()
{
    if(area_owned_by_armies())
    {
         return tod_descr1() + tod_descr2() + "You are standing in Solace's Town Square, which is now in shambles. Leading through this area is a train of slave cages that are filled to the brim with prisoners. There are several trees and buildings in the area as well. " + season_descr() + "\n";
    }
    else
    {
         return tod_descr1() + tod_descr2() + "You are standing in Solace's Town Square, which is now in shambles. In front of you stand what appears to be a broken train of cages. There are several trees and buildings in the area as well. " + season_descr() + "\n";
    }
}

string
determine_cages()
{
    if(area_owned_by_armies())
    {    
         return "The cages are filled with hungry looking prisoners of the armies. A look of worry is upon their faces and their eyes plead with you to rescue them.\n";
    }
    
    else
    {
         return "These cages are broken and empty. They are hooked together as if they were ready to be transported somewhere. It is obvious that someone has freed whatever was inside.\n";
    }
}

string
determine_prisoners()
{
    if(area_owned_by_armies())
    {
        return "The prisoners are skinny and malnourished. Each and every one of them has a look of fear upon his or her face. It is the fear of not knowing if one will live or die.\n";
    }
    
    else
    {
        return "What do you wish to look at?\n";
    }
}

nomask public void
reset_krynn_room()
{
	call_other(TO, RESET);
	reset_conquer_room();
}

void
init()
{
    init_conquer();
		::init();
}

void
set_add_trees()
{
    add_item(({"tree", "trees"}), "There are several tall vallenwood trees here. As your eyes gaze up their tall trunks, you notice wooden walkways in their branches.\n");
    add_item(({"walkway", "walkways"}), "The walkways support the upper section of the town of Solace. You hear the sounds of feet pattering on them above you.\n");
    add_item(({"branch", "branches"}), "The branches are thick and strong; more than capable of supporting the walkways built into them.\n");

}

void
set_add_buildings()
{
    add_item(({"building", "buildings"}), "The buildings here are quite run down. Many of the roofs are caving in, and the walls barely stand beneath them.\n");
    add_item(({"roof", "roofs"}), "The roofs have a shape that hints they were beautifully peaked at one time. There are scorch marks on many of them as though fire played a role in their demise.\n");
    add_item(({"wall", "walls"}), "The walls are burned a dark black and are in a state of near-collapse. On certain buildings you can see what look like signs to stores that no longer exist.\n");
    add_item(({"sign", "signs"}), "The signs are charred badly and hardly readable. They're current state is a testament to the damage the war has caused this town.\n");
    add_item(({"mark", "marks"}), "The scorch marks are long and blacker than any you have ever seen.\n");
}