/*
 * /d/Sparkle/area/spiderlair/rooms/room_std.c
 *
 * The standardroom for the dungeon : Spiderlair.
 *
 * Created February 2009, by Nerull.
 */

inherit "/std/room"; 

#include <stdproperties.h>
#include <macros.h>
#include "../defs.h"
#include "../roomitems.h"


int a = 0;
int dice_roll;


void
create_dungeon_room()
{ 
		
}


int set_dungeon_level(int t)
{	 
  	a = t;
  	return a;
}

int query_dungeon_level()
{
	  return a;
}
	

void
create_room()
{
    create_dungeon_room();
   
    add_prop(ROOM_I_INSIDE, 1);   
    add_prop(ROOM_I_LIGHT, 1);

    seteuid(getuid(this_object()));
}


void
room_itemization()
{		
		object room_item;
  	
  	if (random(7) == 1)
  	{  	 	                
    		room_item = clone_object(P_ROOM + 
    		roomitems[random(sizeof(roomitems))]);        
    		room_item->move(this_object(), 1);
    		return;
    }    
    return;
}


void
room_setup(int i)
{
		
	  dice_roll = random(10);
	  
	  
	  // Spesific/unique room locations.
	  if (i == 1)
	  {
	  		set_name(DUNGEON_NAME);
    		add_name( ({ "room", "hall", "corridor", "tunnel" }) );

    		set_short("Inside a smooth cobwebfilled tunnel");
    		set_long("Desc inc soon.\n");
    
    		add_item(({"wall", "walls"}),
    		"soon to come.\n");
    		
    		add_item(({"wall", "walls"}),
    		"soon to come.\n");
    		
    		add_item(({"wall", "walls"}),
    		"soon to come.\n");
    		
    		room_itemization();
    		
    		return;
    }
	
	  // Dungeon descriptions 0
	  if (dice_roll == 0)
	  {
	  		set_name(DUNGEON_NAME);
    		add_name( ({ "room", "hall", "corridor", "tunnel" }) );

    		set_short("Inside a smooth cobwebfilled tunnel");
    		set_long("Desc inc soon.\n");
    
    		add_item(({"wall", "walls"}),
    		"soon to come.\n");
    		
    		add_item(({"wall", "walls"}),
    		"soon to come.\n");
    		
    		add_item(({"wall", "walls"}),
    		"soon to come.\n");
    		
    		room_itemization();
    		
    		return;
    }
    
    // Dungeon descriptions 1
    if (dice_roll == 1)
	  {
	  		set_name(DUNGEON_NAME);
    		add_name( ({ "room", "hall", "corridor", "tunnel" }) );

    		set_short("Inside an irregular-shaped cobwebfilled tunnel");
    		set_long("Desc inc soon.\n");
    
    		add_item(({"wall", "walls"}),
    		"soon to come.\n");
    		
    		add_item(({"wall", "walls"}),
    		"soon to come.\n");
    		
    		add_item(({"wall", "walls"}),
    		"soon to come.\n");
    		
    		room_itemization();
    		
    		return;
    }
    
    
    // Dungeon descriptions 2
    if (dice_roll == 2)
	  {
	  		set_name(DUNGEON_NAME);
    		add_name( ({ "room", "hall", "corridor", "tunnel" }) );

    		set_short("Inside a broad cobwebfilled tunnel");
    		set_long("Desc inc soon.\n");
    
    		add_item(({"wall", "walls"}),
    		"soon to come.\n");
    		
    		add_item(({"wall", "walls"}),
    		"soon to come.\n");
    		
    		add_item(({"wall", "walls"}),
    		"soon to come.\n");
    		
    		room_itemization();
    		
    		return;
    }
    
    
    // Dungeon descriptions 3
    if (dice_roll == 3)
	  {
	  		set_name(DUNGEON_NAME);
    		add_name( ({ "room", "hall", "corridor", "tunnel" }) );

    		set_short("Inside a narrow cobwebfilled tunnel");
    		set_long("Desc inc soon.\n");
    
    		add_item(({"wall", "walls"}),
    		"soon to come.\n");
    		
    		add_item(({"wall", "walls"}),
    		"soon to come.\n");
    		
    		add_item(({"wall", "walls"}),
    		"soon to come.\n");
    		
    		room_itemization();
    		
    		return;
    }
    
    
    // Dungeon descriptions 4
    if (dice_roll == 4)
	  {
	  		set_name(DUNGEON_NAME);
    		add_name( ({ "room", "hall", "corridor", "tunnel" }) );

    		set_short("Inside a rocky cobwebfilled tunnel");
    		set_long("Desc inc soon.\n");
    
    		add_item(({"wall", "walls"}),
    		"soon to come.\n");
    		
    		add_item(({"wall", "walls"}),
    		"soon to come.\n");
    		
    		add_item(({"wall", "walls"}),
    		"soon to come.\n");
    		
    		room_itemization();
    		
    		return;
    }
    
    
    // Dungeon descriptions 5
    if (dice_roll == 5)
	  {
	  		set_name(DUNGEON_NAME);
    		add_name( ({ "room", "hall", "corridor", "tunnel" }) );

    		set_short("At a small stream of water");
    		set_long("Desc inc soon.\n");
    
    		add_item(({"wall", "walls"}),
    		"soon to come.\n");
    		
    		add_item(({"wall", "walls"}),
    		"soon to come.\n");
    		
    		add_item(({"wall", "walls"}),
    		"soon to come.\n");
    		
    		room_itemization();
    		
    		return;
    }
    
    
    // Dungeon descriptions 6
    if (dice_roll == 6)
	  {
	  		set_name(DUNGEON_NAME);
    		add_name( ({ "room", "hall", "corridor", "tunnel" }) );

    		set_short("Inside a cobwebfilled tunnel filled with bones");
    		set_long("Desc inc soon.\n");
    
    		add_item(({"wall", "walls"}),
    		"soon to come.\n");
    		
    		add_item(({"wall", "walls"}),
    		"soon to come.\n");
    		
    		add_item(({"wall", "walls"}),
    		"soon to come.\n");
    		
    		room_itemization();
    		
    		return;
    }
    
    
    // Dungeon descriptions 7
    if (dice_roll == 7)
	  {
	  		set_name(DUNGEON_NAME);
    		add_name( ({ "room", "hall", "corridor", "tunnel" }) );

    		set_short("In a broad tunnel covered with cobweb.");
    		set_long("Desc inc soon.\n");
    
    		add_item(({"wall", "walls"}),
    		"soon to come.\n");
    		
    		add_item(({"wall", "walls"}),
    		"soon to come.\n");
    		
    		add_item(({"wall", "walls"}),
    		"soon to come.\n");
    		
    		room_itemization();
    		
    		return;
    }
    
    
    // Dungeon descriptions 8
    if (dice_roll == 8)
	  {
	  		set_name(DUNGEON_NAME);
    		add_name( ({ "room", "hall", "corridor", "tunnel" }) );

    		set_short("At a dark still pond");
    		set_long("Desc inc soon.\n");
    
    		add_item(({"pond", "walls"}),
    		"soon to come.\n");
    		
    		add_item(({"wall", "walls"}),
    		"soon to come.\n");
    		
    		add_item(({"wall", "walls"}),
    		"soon to come.\n");
    		
    		room_itemization();
    		
    		return;
    }
    
    
    // Dungeon descriptions 9
    if (dice_roll == 9)
	  {
	  		set_name(DUNGEON_NAME);
    		add_name( ({ "room", "hall", "corridor", "tunnel" }) );

    		set_short("In a large tunnel filled with stalacites");
    		set_long("Desc inc soon.\n");
    
    		add_item(({"stalagmites", "walls"}),
    		"soon to come.\n");
    		
    		add_item(({"wall", "walls"}),
    		"soon to come.\n");
    		
    		add_item(({"wall", "walls"}),
    		"soon to come.\n");
    		
    		room_itemization();
    		
    		return;
    }
    
}


