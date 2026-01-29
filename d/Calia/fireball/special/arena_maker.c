
/* 
    ~Calia/fireball/special/arena_maker.c 

    This is the area maker for the fireball arena. 
    It can be used to generate the rooms of the arena. 

    Coded by Maniac@Genesis, 1997/1998

    Copyright (C) Miguel Leith 1997/1998
*/ 

#pragma strict_types
#pragma no_clone
#pragma no_inherit

#include "defs.h"
#include FIREBALL_HEADER
#include <std.h>

inherit "/std/object"; 

void init_arena(); 

mixed arena; 
int room_alarm, x_count, y_count; 

void
create_object()
{
    seteuid(getuid()); 
    set_name("maker"); 
    set_adj(({ "fireball", "arena" })); 
    init_arena(); 
    room_alarm = 0; 
}


/* Sets up the arena in case there is no save file. */ 
void
init_arena()
{
    arena = ({ ({ 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1 }), 
               ({ 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1 }), 
               ({ 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1 }), 
               ({ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }), 
               ({ 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 }), 
               ({ 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0 }), 
               ({ 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 }), 
               ({ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }), 
               ({ 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1 }), 
               ({ 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1 }), 
               ({ 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1 }) }); 
}


int
room_x(int x)
{
    return x + 1; 
}


int
room_y(int y)
{
   return (11 - y); 
}

string 
arena_room_file_name(int x, int y) 
{
    return ("ar_" + room_x(x) + "_" + room_y(y)); 
}


string 
arena_room_exit(string direction)
{
    int add_x, add_y, new_x, new_y; 

    switch (direction) { 
        case "north" : add_x = 0;  add_y = -1; break; 
        case "south" : add_x = 0;  add_y = 1; break; 
        case "east" : add_x = 1;  add_y = 0; break; 
        case "west" : add_x = -1;  add_y = 0; break; 
        case "northeast" : add_x = 1;  add_y = -1; break; 
        case "northwest" : add_x = -1;  add_y = -1; break; 
        case "southeast" : add_x = 1;  add_y = 1; break; 
        case "southwest" : add_x = -1;  add_y = 1; break; 
        default : return ""; break;
    } 
    new_x = x_count + add_x; 
    new_y = y_count + add_y; 

    if ((new_x < 0) || 
        (new_y < 0) || 
        (new_y >= sizeof(arena)) || 
        (new_x >= sizeof(arena[new_y]))) 
        return ""; 

    if (arena[new_y][new_x]) 
         return ""; 

    return ("    add_exit(FIREBALL_ARENA+\""+
               arena_room_file_name(new_x, new_y))+
               "\",\""+ direction + "\");\n";  
}


string
arena_room_exits()
{
     return (arena_room_exit("north") + 
             arena_room_exit("south") + 
             arena_room_exit("east") + 
             arena_room_exit("west") + 
             arena_room_exit("northeast") + 
             arena_room_exit("northwest") + 
             arena_room_exit("southeast") + 
             arena_room_exit("southwest")); 
}


string
intro_lines()
{
    return ("/*\n" + 
            " * A room in the Firedrome's arena.\n" + 
            " *\n" + 
            " * Coded by Maniac@Genesis, December 1998\n" +  
            " *\n" + 
            " * Copyright (C) Miguel Leith 1998\n" + 
            " */\n\n"); 
}


string
top_lines()
{
    return ("#include \"defs.h\"\n\n" + 
            "#include FIREBALL_HEADER\n\n" +     
            "inherit FIREBALL_ARENA_ROOM;\n\n");  
}


string 
main_lines()
{
    return ("void\n"+       
            "create_room()\n" + 
            "{\n"+  
            "    make_arena_room(" + room_x(x_count)+", " + 
                                     room_y(y_count)+", " +
                                     x_count + ", " + 
                                     y_count + ");\n" + 
            arena_room_exits() + "}\n");  
}


private void
generate_rooms()
{
    string fn; 

    if (room_alarm && get_alarm(room_alarm)) 
        return;

    fn = (FIREBALL_ARENA+arena_room_file_name(x_count, y_count)+".c");  
    if (!arena[y_count][x_count] && (file_size(fn) == -1))  
        write_file(fn, intro_lines() + top_lines() + main_lines());  

    y_count++; 
    if (sizeof(arena) <= y_count) {  
        y_count = 0; 
        x_count++; 
    } 

    if (sizeof(arena[y_count]) <= x_count)  {
        room_alarm = 0; 
        return;
    } 

    room_alarm = set_alarm(3.0, 0.0, generate_rooms);  
}

int
make_rooms()
{
    if (!SECURITY->valid_write(file_name(this_object()), 
                               this_interactive(),  
                               write_file))
        return 0;

   generate_rooms(); 
   return 1;
}

