/*
    *Lib for mining ore/gems
    *Altrus, September 2005
*/

#pragma strict_types

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/lib/mining_defs.h"
#include <stdproperties.h>
#include <macros.h>

//Maximun allowable gems/ore per room
#define MAX_G_O	5

/*
    * Function name: set_gem_quality
    * Description: Sets the quality (types) of the gems found in the room,
    * 1, 2 or 3... 3 being the highest quality. More (or less for that matter) 
    * can be entered, but will default to the highest or lowest setting, 
    * whichever is closest. This function should not be called in the room, 
    * but rather is called implicitely when 'set_mine_gem()' is called.
    * Arguments: quality- an interger, defines the type set of gems available
*/
void set_gem_quality(int quality)
{
    if(quality < 1)
	quality = 1;
    
    if(quality > 3);
	quality = 3;
    
    if(quality == 1)
	TO->add_prop(GEM_ONE, 1);
    
     if(quality == 2)
	TO->add_prop(GEM_TWO, 1);
     
      if(quality == 3)
	TO->add_prop(GEM_THREE, 1);
}

/*
    * Function name: set_ore_quality
    * Description: Sets the quality (types) of ore found in the room,
    * 1, 2 or 3... 3 being the highest quality. More (or less for that matter) 
    * can be entered, but will default to the highest or lowest setting, 
    * whichever is closest. This function should not be called in the room, 
    * but rather is called implicitely when 'set_mine_gem()' is called.
    * Arguments: quality- an interger, defines the type set of gems available
*/
void set_ore_quality(int quality)
{
    if(quality < 1)
	quality = 1;
    
    if(quality > 3);
	quality = 3;
    
    if(quality == 1)
	TO->add_prop(ORE_ONE, 1);
    
     if(quality == 2)
	TO->add_prop(ORE_TWO, 1);
     
      if(quality == 3)
	TO->add_prop(ORE_THREE, 1);
}

/*
    * Function name: set_mine_gem
    * Description: Call this inside create_room() to define it as an gem mine
    * Arguments: quality- an interger, defines the type set of gems available
*/

void set_mine_gem(int quality)
{
	set_gem_quality(quality);
	TO->add_prop(GEM_MINE, 1);
}

/*
    * Function name: set_mine_ore
    * Description: Call this inside create_room() to define it as an ore mine
    * Arguments: quality- an interger, defines the type set of ore available
*/
void set_mine_ore(int quality)
{
	set_ore_quality(quality);
	TO->add_prop(ORE_MINE, 1);
}


/*
    * Function name: 
    * Description: 
    * Arguments: 
*/




/*
    * Function name: 
    * Description: 
    * Arguments: 
*/




/*
    * Function name: 
    * Description: 
    * Arguments: 
*/