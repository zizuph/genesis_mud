/**********************************************************************
 * - sanctuary.c                                                    - *
 * -                                                                - *
 * - Created by Damaris@Genesis 3/2004                              - *
 * - New Standrad file for new area for guild. Typos fixed.         - *
 * - by Mirandus@Genesis 01/2018                                    - *
 **********************************************************************/
#pragma strict_types

#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>
#include <files.h>

#include "../guild.h"

inherit THANAR_STD_ROOM; 
#include "kneel.c"
#include "altar.c"

/*
 * Function name: members_only()
 * Description  : Allows only members
 */
public int
members_only()
{
    if (IS_MEMBER(this_player()) || this_player()->query_wiz_level())

    {
    /* Is a member, pass through as normal */

    return 0;
    }

    write("A magical force prevents you from entering.\nYou are not a "+
      "Thanarian!\n");
    return 1;
}

/*
 * Function name: create_std_thanar()
 * Description  : Creates the room from standard room file
 */
public void
create_std_thanar()
{
   set_short("A sanctuary");
   set_long("The sanctuary lies before you. The largeness "+
    "of the area could make one feel quite small basking in such "+
    "splendour. There are five long candelabras hanging down from "+
    "the vaulted ceiling, with candles burning to light the area. "+
    "The light infiltrates the stained glass windows that are placed "+
    "on the west and east sides of the sanctuary. There is a wide "+
    "single isle that leads directly to the altar between the "+
    "two sections of pews.\n");
    
    add_item(({"kneeler", "kneelers"}), kneel_desc);
    add_my_desc(kneel_desc, this_object());  

    add_item(({"altar", "obsidian altar", "large altar", "grand altar"}),
    "The altar is quite grand in size and made of obsidian. You can "+
    "kneel before it and even make offerings or sacrifices to the "+
    "great Lord Thanar.\n");
    
    add_item(({"stained glass", "stained glass windows", "stained glass window"}),
    "There are eight stained glass windows in the sanctuary, four in the "+
    "west wall and four in the east wall. Each one is very tall and shaped "+
    "into an arch at the top. The dominant colours in each window are "+
    "vibrant purple and scarlet red. They are stunning and beautifully let "+
    "the light penetrate through, which produces a most wonderful glow "+
    "of mystery. You should be able to look at each one a little bit more "+
    "closely.\n");
    
    add_item(({"first stained glass"}),
    "This stained glass window is a depiction of Saint Elizabeth in a garden "+
    "filled with scarlet roses. Her beauty is reflected in the glass "+
    "in a most lovely way.\n");
  
    add_item(({"second stained glass"}),
    "This stained glass window is a depiction of Saint Margaret in a "+
    "garden filled with purple roses. Her beauty is reflected in the glass "+
    "in a most lovely way.\n");
    
    add_item(({"third stained glass"}),
    "This stained glass window is a depiction of Saint Providence in a "+
    "garden filled with scarlet and purple roses. His face is etched with "+
    "concern as if in deep prayer.\n");
    
    add_item(({"fourth stained glass"}),
     "This stained glass window is a depiction of Saint Elizabeth holding "+
     "a weary Saint Providence in a garden filled with scarlet roses. Her "+
     "beauty is radiates from her as she comforts him.\n");
     
    add_item(({"fifth stained glass"}),
    "This stained glass window is a depiction of Saint Margaret listening "+
    "intently to Saint Providence as he talks with his arms stretched "+
    "upward to the heavens. They are in a garden filled with purple roses.\n");
    
    add_item(({"sixth stained glass"}),
    "This stained glass window is a depiction of Saint Elizabeth crying in "+
    "a garden filled with scarlet roses. Her beauty is reflected in the glass "+
    "even through her tears.\n");
    
    add_item(({"seventh stained glass"}),
    "This stained glass window is a depiction of Saint Margaret sleeping "+
    "in a garden filled with purple roses. Her sleeping body continues to "+
    "reflect her beauty in a most lovely way.\n");

    add_item(({"eighth stained glass"}),
    "This stained glass window is a depiction of Saint Elizabeth and Saint "+
    "Margaret crying as they hold the lifeless body of Saint Providence in "+
    "a garden filled with scarlet and purple roses.\n");
             
    add_item(({"window", "windows"}),
    "Look at the stained glass perhaps?\n");
  
    add_item(({"candle", "candles", "light"}),
    "There are many candles burning brightly in here.\n");  
  
    add_item(({"vaulted ceiling"}),
    "The vaulted ceiling is quite large and has golden candelabras hanging "+
    "from it. It is also one huge painting. You can clearly see that an "+
    "artist of greatness painted it.\n");
  
    add_item(({"painting", "canvas"}),
    "The painting, which has been bestowed on the ceiling, is beautiful. "+
    "You can make out many different scenes that have been merged "+
    "together on this huge canvas. There are angels depicted along with "+
    "saints.\n");
    
    add_item(({"sanctuary", "room","area"}), query_long);
  
    add_item(({"candelabras", "candelabra" ,"candelabrum"}),
    "There are five candelabras here in the sanctuary, which one would you "+
    "like to look at?\n");
  
    add_item(({"first candelabra", "first candelabrum"}),
    "The first candelabrum is golden and hangs down from the vaulted "+
    "ceiling just over the first half of the west side of the pews. "+
    "It holds a total of twenty-five cream coloured candles, which are "+
    "burning brightly.\n");
    
    add_item(({"second candelabra", "second candelabrum"}),
    "The second candelabrum is golden and hangs down from the "+
    "vaulted ceiling just over the first half of the east side of the pews. "+
    "It holds a total of twenty-four cream coloured candles, which are "+
    "burning brightly.\n");
    
    add_item(({"third candelabra", "third candelabrum"}),
    "The third candelabrum is golden and hangs down from the vaulted "+
    "ceiling just over the last half of the west side of the pews. It holds a "+
    "total of twenty-four cream coloured candles, which are burning"+
    "brightly.\n");
    
    add_item(({"fourth candelabra", "fourth candelabrum"}),
    "The fourth candelabrum is golden and hangs down from the vaulted "+
    "ceiling just over the last half of the east side of the pews. It "+
    "holds a total of twenty-five cream coloured candles, which are "+
    "burning brightly.\n");
    
    add_item(({"fifth candelabra"}),
    "The fifth candelabrum is golden and hangs down from the vaulted "+
    "ceiling directly over the altar. It holds a total of twenty-four cream "+
    "coloured candles, twelve scarlet coloured candles and four purple "+
    "coloured candles, all of which are burning brightly.\n");
    
    add_exit("join", "south");
}

/*
 * Function name: init()
 * Description  : Initializes the commands.
 */
void
init()
{
    ::init();
    init_kneel();
    init_altar();

}
