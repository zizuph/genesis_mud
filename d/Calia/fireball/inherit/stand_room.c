
/* 
    ~Calia/fireball/inherit/stand_room.c

    The inheritable room for the stands of the Firedrome arena. 

    Coded by Maniac@Genesis, July 1997

    Revised by Maniac January 1999. 

    Copyright(C) Miguel Leith 1997. 
*/ 

#include <stdproperties.h>
#include <language.h>
#include <composite.h>
#include <language.h> 
#include <macros.h>
#include "defs.h"
#include FIREBALL_HEADER

inherit "/std/room";
inherit FIREBALL_VIEW_SUPPORT; 
inherit FIREBALL_HELP_SUPPORT; 

void
make_stand_room()
{
    set_short("The stand of the Firedrome"); 
    set_long("You are in a stand overlooking the arena, " +
         "a great place to get a panoramic view of a fireball game. It " +
         "is built above the wall that encircles the playing area. " +
         "Rows of wooden benches provide the seating here, rising in " +
         "tiers and divided by aisles. Most of the crowd " +
         "is standing, though, and making a lot of noise.\n");   

    add_item("crowd", "As usual there is a large crowd here to watch " +
                      "the busy schedule of events. It is a mixture " +
                      "of all ages and races.\n"); 

    add_item(({"firedrome", "stadium", "stand"}), 
              "The firedrome is a circular stadium " + 
              "built with a large area of seating overlooking " +
              "an arena in which fireball games are played.\n");  

    add_item(({"fire", "great fire", "fire wall"}), 
              "A great fire burns at the centre of the arena. " +
              "It is surrounded by a wall to protect fireball players " +
              "but its flames leap and dance high and dangerously.\n"); 

    add_item(({"bench", "benches", "wooden benches", "seats", "seating"}), 
         "Long heavy wooden benches provide the seating here. " + 
         "They are polished and fairly comfortable.\n");  

    add_item(({"wall", "arena wall", "walls" }), 
         "A wall of towering stone skirts the edge of the arena, " + 
         "casting long shadows across the playing surface.\n");

    add_item(({ "playing area", "arena", "firedrome arena"}), 
       "The arena is a wide circular expanse of dusty faded "+  
       "red stone, some hundred and ten yards in diameter. "+  
       "A wall of towering stone skirts the edge of the arena " +
       "casting long shadows across the playing surface. At the centre " +
       "a great fire burns surrounded by a protective wall. From here you " +
       "may examine a game or the scoreboard.\n"); 
}


nomask int
check_fireball_stand_room()
{
    return 1;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from); 
    if (!IS_FIREBALL_STAND_ROOM(from) && living(ob))      
        FIREBALL_GAME_HANDLER->enter_stand(ob, from); 
}


void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest); 
    if (!IS_FIREBALL_STAND_ROOM(dest) && living(ob))      
        FIREBALL_GAME_HANDLER->leave_stand(ob, dest); 
}

void
init()
{
    ::init(); 
    init_view_support(); 
    init_help_support(); 
}
