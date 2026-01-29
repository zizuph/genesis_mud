
/* 
   Area maker.

   Copyright (C) Miguel Leith 1996

 */ 

#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include "area_maker.h"

inherit "/std/object"; 

mapping rt_headers; 
mapping rt_pragmas; 
mapping rt_inherits; 
mapping rt_includes;
mapping rt_props; 
mapping rt_miscs; 
mapping rt_room_dir; 
mapping rt_fatigue; 
mapping rt_filename_stem; 


/* holds the exit value for each room. */ 
mixed overall_map_directions; 
/* holds the room type array for each room. */ 
mixed overall_map_roomtypes; 

string area_name;


void
create_area_maker()
{
}


nomask void
create_object()
{
    set_name("maker"); 
    set_adj("area"); 
    add_prop(OBJ_M_NO_DROP, 1); 
    add_prop(OBJ_M_NO_GIVE, 1); 
    seteuid(0); 
    create_area_maker(); 
}


varargs string 
short(object for_obj)
{
    if (!stringp(area_name)) 
        return "area maker for an un-named area"; 
    else
        return ("area maker for " + area_name);  
}




string *
segment_line(string str)
{
     int i, s;
     string *sg; 

     sg = ({ }); 
     s = strlen(str) - 4; 

     for (i = 0; i < s; i += 4)  
         sg += ({ str[i..i+4] }); 
 
     return sg;
}


mixed
get_north_line_dirs(string *sg)
{
     int i;
     int *lc; 

     lc = allocate(GRIDX); 

     /* interpret the segments as direction chars */ 
     for (i = 0; i < sizeof(sg); i++) { 
         if ((sg[i][0] == KRIS_KROS) || (sg[i][0] == NW_SE_CHAR))  
               lc[i] += NORTHWEST; 
         if (sg[i][2] == N_S_CHAR) 
               lc[i] += NORTH;  
         if ((sg[i][4] == KRIS_KROS) || (sg[i][4] == NE_SW_CHAR))   
               lc[i] += NORTHEAST; 
     } 

     return lc; 
}


mixed
get_south_line_dirs(string *sg)
{
     int i;
     int *lc; 

     lc = allocate(GRIDX); 

     /* interpret the segments as direction chars */ 
     for (i = 0; i < sizeof(sg); i++) { 
         if ((sg[i][0] == KRIS_KROS) || (sg[i][0] == NE_SW_CHAR))  
               lc[i] += SOUTHWEST; 
         if (sg[i][2] == N_S_CHAR) 
               lc[i] += SOUTH;  
         if ((sg[i][4] == KRIS_KROS) || (sg[i][4] == NW_SE_CHAR))   
               lc[i] += SOUTHEAST; 
     } 

     return lc; 
}



mixed
get_central_line_dirs(string *sg)
{
     int i;
     int *lc; 

     lc = allocate(GRIDX); 

     /* interpret the segments as direction chars */ 
     for (i = 0; i < sizeof(sg); i++) { 
         if ((sg[i][0] == E_W_CHAR))  
               lc[i] += WEST; 

         if (sg[i][2] == U_CHAR)  
               lc[i] += UP; 
         else if (sg[i][2] == D_CHAR) 
               lc[i] += DOWN; 
         else if (sg[i][2] == U_D_CHAR)
               lc[i] += (UP + DOWN); 

         if (sg[i][4] == E_W_CHAR) 
               lc[i] += EAST;  
     } 

     return lc; 
}



int * 
make_map_section_dirs(int *l1, int *l2, int *l3)
{
   int i, *r;

   r = allocate(GRIDX); 

   for (i = 0; i < GRIDX; i++)
       r[i] = (l1[i] | l2[i] | l3[i]); 

   return r; 
}




int
check_char(int c, int direc)
{
  if  ((c == N_S_CHAR) || 
       (c == E_W_CHAR) || 
       (c == NE_SW_CHAR) || 
       (c == NW_SE_CHAR) || 
       (c == KRIS_KROS) || 
       (c == F_CHAR) || 
       (c == U_CHAR) || 
       (c == D_CHAR) || 
       (c == U_D_CHAR))
      return 1;
 
   return (!direc && (c == BLANK_CHAR)); 
}


mixed
get_room_types(string *sg)
{
    int i, j;
    mixed rt;
    string s;

    rt = ({ }); 

    for (i = 0; i < sizeof(sg); i++) { 
        if (check_char(sg[i][2], 1) || 
            check_char(sg[i][1], 0) || 
            check_char(sg[i][3], 0)) 
            return i;
         
        rt += ({ ({ sg[i][1..1], sg[i][3..3] }) }); 
    } 

    return rt;
}


/* 
 * Returns the map array for a map section read in from a file,
 * or an error message (string).  
 */ 
mixed
read_map_section(string path, int sect_num)
{
    string str1, str2, str3, *sg;
    int line_num; 
    int *l1, *l2, *l3; 
    mixed directions, room_types; 

    line_num = (sect_num*2); 

    /* Read in and interpret north line of section */ 
    line_num++; 
    str1 = read_file(path, line_num, 1); 
    if (str1 == 0) 
        return ("Could not read in a north line at " +
                "line " + line_num + " for the file " + 
                 path + ".\n"); 

    sg = segment_line(str1); 
    l1 = get_north_line_dirs(sg); 


    /* Read in and interpret central line of section */ 
    line_num++; 
    str2 = read_file(path, line_num, 1); 
    if (str2 == 0)
        return ("Could not read in a central line at " +
                "line " + line_num + " for the file " + 
                 path + ".\n"); 

    sg = segment_line(str2); 
    l2 = get_central_line_dirs(sg); 
    room_types = get_room_types(sg); 

    if (intp(room_types)) 
        return ("Misuse of reserved character at location " + room_types + 
                " of the line " + line_num + " for the file " + 
                path + ".\n"); 

    /* Read in and interpret south line of section */ 
    line_num++; 
    str3 = read_file(path, line_num, 1); 

    if (str3 == 0)
        return ("Could not read in a south line at " +
                "line " + line_num + " for the file " + 
                 path + ".\n"); 

    sg = segment_line(str3); 
    l3 = get_south_line_dirs(sg);  

    /* Make the map section */ 
    directions = make_map_section_dirs(l1, l2, l3);  

    return ({ directions, room_types });
}


/* 
 * Returns the map array for a map read in from a file,
 * or an error message (string).  
 */ 
mixed
read_map(string path)
{
    mixed section, map; 
    int i;

    map = ({ }); 

    i = 0; 
    while (i < GRIDY) { 
        section = read_map_section(path, i); 
        if (stringp(section)) 
            return section; 
        map += ({ section }); 
        i++;
    } 

    return map; 
}


int
join_map_n(mixed main_map, mixed new_map)
{

}

int
join_map_s(mixed main_map, mixed new_map)
{

}

int
join_map_e(mixed main_map, mixed new_map)
{

}

int
join_map_w(mixed main_map, mixed new_map)
{

}

void
set_area_name(string an)
{
    if (stringp(an) && strlen(an)) 
        area_name = an;
}


/* 
 * Add an element to the value array for an index ix of 
 * a mapping. Returns 1 if successful.  
 */ 
int
add_mapping_value_el(mapping m, string ix, mixed ve)
{
    mixed e1;

    e1 = m[ix]; 
    if (e1 == 0)  { 
         m += ([ ix : ({ ve })]);  
         return 1;
    } 

    if (!pointerp(e1)) 
        return 0;

    m = m_delete(m, ix); 

    m += ([ ix :  (e1 + ({ ve }))]);  
    return 1;
}


int
set_mapping_value(mapping m, string ix, mixed e)
{
    mixed e1;

    e1 = m[ix]; 
    if (e1 == 0)  { 
         m += ([ ix : e ]);  
         return 1;
    } 

    m = m_delete(m, ix); 

    m += ([ ix : e ]);  
    return 1;
}


int
add_rt_header(string room_type, string header)
{
    if (!stringp(room_type) || !stringp(header)) 
        return 0;

    return add_mapping_value_el(rt_headers, room_type, header);  
}


int
add_rt_pragma(string room_type, string prag)
{
    if (!stringp(room_type) || !stringp(prag)) 
        return 0;

    return add_mapping_value_el(rt_pragmas, room_type, prag);  
}


int
add_rt_include(string room_type, string inc)
{
    if (!stringp(room_type) || !stringp(inc)) 
        return 0;

    return add_mapping_value_el(rt_includes, room_type, inc);  
    
}


int
add_rt_inherit(string room_type, string inh)
{
    if (!stringp(room_type) || !stringp(inh)) 
        return 0;

    return add_mapping_value_el(rt_inherits, room_type, inh);  
}


int
add_rt_prop(string room_type, string prop)
{
    if (!stringp(room_type) || !stringp(prop)) 
        return 0;

    return add_mapping_value_el(rt_props, room_type, prop);  
}


int
add_rt_misc(string room_type, string misc)
{
    if (!stringp(room_type) || !stringp(misc)) 
        return 0;

    return add_mapping_value_el(rt_miscs, room_type, misc);  
}


int
set_rt_fatigue(string room_type, int fat)
{
    if (!stringp(room_type) || !intp(fat))
        return 0;

    return set_mapping_value(rt_fatigue, room_type, fat); 
}


int
set_rt_dir(string room_type, string dr) 
{
    if (!stringp(room_type) || !stringp(dr)) 
        return 0;

    return set_mapping_value(rt_room_dir, room_type, dr);
}


int
set_rt_filename_stem(string room_type, string fnst) 
{
    if (!stringp(room_type) || !stringp(fnst)) 
        return 0;

    return set_mapping_value(rt_filename_stem, room_type, fnst);
}

