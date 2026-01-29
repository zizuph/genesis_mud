
/* 
    ~Calia/fireball/inherit/arena_room.c

    The inheritable room for rooms in the Firedrome arena. 

    Coded by Maniac@Genesis, 1998

    Last revised April 1999 by Maniac

    Copyright(C) Miguel Leith 1998
*/ 

#include <stdproperties.h>
#include <language.h>
#include <composite.h>
#include <language.h> 
#include <macros.h>
#include "defs.h"
#include FIREBALL_HEADER

inherit "/std/room";


string fireball_field_sector(int x, int y); 
string query_arena_wall_room(int x, int y); 
string query_fire_room(int x, int y); 

int x_val;
int y_val; 
int x_real_val; 
int y_real_val; 
string field_sector; 

void
make_arena_room(int x, int y, int xr, int yr)
{
    string s, l, l2, txt;  

    x_val = x; 
    y_val = y; 
    x_real_val = xr; 
    y_real_val = yr; 

    set_short((field_sector = fireball_field_sector(x, y)) + 
              " (" + x + ", " + y +")"); 
    l = ""; 

    txt = ("It's a rectangular goal about three yards wide. " +
          "Behind it is a net."); 

    if (x == 6 && y == 11) { 
        l += "The north goal gapes immediately in front of you. "; 
        add_item(({ "goal", "north goal" }), 
                 "The north goal is immediately in front of you. " +
                 txt + "\n"); 
        add_item(({"net" }), "It's made of strong looking cords.\n"); 
        add_item(({"goals"}), VBFC_ME("both_goals")); 
        add_item("south goal", VBFC_ME("south_goal"));  
    } 
    else if (x == 6 && y == 1) { 
        l += "The south goal gapes immediately in front of you. "; 
        add_item(({ "goal", "south goal" }), 
                 "The south goal is immediately in front of you. " +
                 txt + "\n"); 
        add_item(({"net" }), "It's made of strong looking cords.\n"); 
        add_item(({"goals"}), VBFC_ME("both_goals")); 
        add_item("north goal", VBFC_ME("north_goal"));  
    } 
    else { 
        l += ("You're at " + field_sector + ". "); 
        /* put vbfc goal desc here */ 
        add_item(({"goal", "goals"}), VBFC_ME("both_goals")); 
        add_item("north goal", VBFC_ME("north_goal"));  
        add_item("south goal", VBFC_ME("south_goal"));  
    } 

    if (stringp(s = query_arena_wall_room(x, y))) 
    {  
        l += ("The arena wall looms over you here. "); 
        add_item(({"wall", "arena wall" }), 
           "The arena wall looms over you here, " +
           "its nearest point to your " + s + ".\n"); 
    } 
    else { 
        add_item(({"wall", "arena wall", "firedrome wall" }), 
         "A wall of towering stone skirts the edge of the " +
         "arena casting long shadows across the playing surface.\n");
    } 

    if (stringp(s = query_fire_room(x, y))) {
        l += ("The fire burns just to your " + s + ". "); 
        add_item(({"fire" }), 
                 "The fire at the centre of the arena " +
                 "burns just to your " + s + ". Its flames " +
                 "leap and dance dangerously above " +
                 "the enclosing wall.\n");  
    }
    else {
        add_item(({"fire" }), 
                 "At the centre of the arena a great fire " +
                 "surrounded by a wall burns, blocking passage " +
                 "across the centre point.\n"); 
    }

    add_item(({"firedrome", "stadium"}), 
               "The Firedrome is a circular stadium built with a " +
               "large area of seating overlooking an arena in which " +
               "fireball games are played.\n"); 

    add_item(({"arena", "area"}), 
              "You are in the arena of the Firedrome. From here " +
              "you may examine a game or the current score.\n"); 

    add_item(({"ground", "floor", "dust", "rock", "stone" }), 
              "The ground is dusty faded red stone, with a rough " +
              "but level surface.\n"); 

    add_item(({"crowd", "huge crowd" }), 
              "The crowd is situated in the stand above the arena wall, " +
              "all around the stadium.\n"); 

    l += ("Before you is the Firedrome arena, a " +
     "circular expanse of faded red stone topped by a thin layer of dust. " +  
     "A towering wall skirts the edge casting " +
     "long shadows across the playing surface. At the centre of the arena " +
     "a great fire burns. A huge crowd amassed above " +
     "the walls projects a tide of noise that carries across " +
     "the pitch and echoes off the walls."); 

    set_long(l + "\n"); 

    add_prop(ROOM_M_NO_ATTACK, "The guards will not allow that in the " +
                               "arena.\n"); 
    add_prop(ROOM_M_NO_MAGIC_ATTACK, "The guards will not allow that in " +
                                     "the arena.\n"); 
    add_prop(ROOM_M_NO_MAGIC, "The guards will not allow that in the arena.\n"); 
}


string
north_goal()
{
    int hor, vert;  
    string h;

    hor = x_val - 6; 
    vert = 11 - y_val; 

    if (hor < 0) {  
        h = "west"; 
        hor = -hor; 
    } 
    else 
        h = "east"; 

    return ("You are " + LANG_WNUM(hor*10) + " yards " + h + " of the north "
          + "goal and " + LANG_WNUM(vert*10+5) + " yards south of it.\n");  
}


string
south_goal()
{
    int hor, vert;  
    string h;

    hor = x_val - 6; 
    vert = y_val - 1; 

    if (hor < 0) {  
        h = "west"; 
        hor = -hor; 
    } 
    else 
        h = "east"; 

    return ("You are " + LANG_WNUM(hor*10) + " yards " + h + " of the south "
          + "goal and " + LANG_WNUM(vert*10+5) + " yards north of it.\n");  
}


string
both_goals()
{
    return (north_goal() + south_goal()); 
}


nomask int
check_fireball_arena_room() 
{
    return 1;
}


string
fireball_field_sector(int x, int y)
{
    if (x == 1) {
        return FIREBALL_WEST_POINT;
    }
    else if (x < 5) {
        if (y < 5)
            return FIREBALL_SOUTHWEST_FIELD;
        else if (y < 8)
            return FIREBALL_WEST_FIELD;
        else if (y < 11)
            return FIREBALL_NORTHWEST_FIELD;
    }
    else if (x < 8) {
        if (y == 1)
            return FIREBALL_SOUTH_GOAL;
        else if (y < 5)
            return FIREBALL_SOUTH_FIELD;
        else if (y < 8)
            return FIREBALL_MID_FIELD;
        else if (y < 11)
            return FIREBALL_NORTH_FIELD;
        else if (y == 11)
            return FIREBALL_NORTH_GOAL;
    }
    else if (x < 11) {
        if (y < 5)
            return FIREBALL_SOUTHEAST_FIELD;
        else if (y < 8)
            return FIREBALL_EAST_FIELD;
        else if (y < 11)
            return FIREBALL_NORTHEAST_FIELD;
    }
    else if (x == 11) {
        return FIREBALL_EAST_POINT;
    }
}


string
query_arena_wall_room(int x, int y)
{
    switch (x) {
        case 1 : 
                 return "west";
                 break;
        case 2 :
                 switch (y) {
                      case 4 : return "southwest"; break;
                      case 8 : return "northwest"; break;
                      default : return 0; break;
                 }
                 break;
        case 3 :
                 switch (y) {
                      case 3 : return "southwest"; break;
                      case 9 : return "northwest"; break;
                      default : return 0; break;
                 }
                 break;
        case 4 :
                 switch (y) {
                      case 2 : return "southwest"; break;
                      case 10 : return "northwest"; break;
                      default : return 0; break;
                 }
                 break;
        case 5 .. 7 :
                 switch (y) {
                      case 1 : return "south"; break;
                      case 11 : return "north"; break;
                      default : return 0; break;
                 }
                 break;
        case 8 :
                 switch (y) {
                      case 2 : return "southeast"; break;
                      case 10 : return "northeast"; break;
                      default : return 0; break;
                 }
                 break;
        case 9 :
                 switch (y) {
                      case 3 : return "southeast"; break;
                      case 9 : return "northeast"; break;
                      default : return 0; break;
                 }
                 break;
        case 10 :
                 switch (y) {
                      case 4 : return "southeast"; break;
                      case 8 : return "northeast"; break;
                      default : return 0; break;
                 }
                 break;
        case 11 : 
                 return "east";
                 break;
        default : return 0; break;
    }
}


string
query_fire_room(int x, int y)
{
    switch (x) {
        case 4 : if (y == 5) 
                     return "northeast"; 
                 else if (y == 6) 
                     return "east"; 
                 else if (y == 7) 
                     return "southeast"; 
                 else
                     return 0; 
                 break; 
        case 5 : if (y == 5 || y == 4) 
                     return "northeast"; 
                 else if (y == 7 || y == 8) 
                     return "southeast"; 
                 else
                     return 0; 
                 break; 
        case 6 : if (y == 4) 
                     return "north"; 
                 else if (y == 8) 
                     return "south"; 
                 else
                     return 0;
                 break; 
        case 7 : if (y == 5 || y == 4)
                     return "northwest"; 
                 else if (y == 7 || y == 8)
                     return "southwest"; 
                 else
                     return 0;
                 break; 
        case 8 : if (y == 5) 
                     return "northwest"; 
                 else if (y == 6) 
                     return "west"; 
                 else if (y == 7) 
                     return "southwest"; 
                 else
                     return 0; 
                 break; 
        default : return 0; 
                  break;  
    } 
}


int
query_x()
{
    return x_val; 
}

int
query_y() 
{
    return y_val; 
}

int
query_real_x()
{
    return x_real_val; 
}

int
query_real_y() 
{
    return y_real_val; 
}

string
query_field_sector()
{
    return field_sector; 
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from); 
    if (living(ob)) {
        if (!IS_FIREBALL_ARENA_ROOM(from)) 
            FIREBALL_GAME_HANDLER->enter_arena(ob, from, this_object());

        FIREBALL_GAME_HANDLER->enter_arena_location(ob, this_object()); 
    } 
}


void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest); 
    if (living(ob)) { 
        if (!IS_FIREBALL_ARENA_ROOM(dest))
            FIREBALL_GAME_HANDLER->leave_arena(ob, this_object(), dest);
        FIREBALL_GAME_HANDLER->leave_arena_location(ob, this_object()); 
    } 
}


/* I don't use the ordinary exit system for arena rooms.
   Running and dribbling is handled by the player object */ 
void
init()
{
}
