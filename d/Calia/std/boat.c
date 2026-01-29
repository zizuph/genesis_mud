
/* 
   This is the inheritable file for the outside of a boat, that 
   supports the configuration of the boat inside (a room).  

   Copyright Miguel Leith 1996 

   Coded by Maniac April 96 
*/ 

#include <cmdparse.h>
#include <language.h>
#include "/d/Calia/sys/water.h"
#include <stdproperties.h>

inherit "/std/object"; 
inherit "/d/Calia/std/contents_desc";
inherit "/d/Calia/std/ahoy"; 


string next_direc; 
object boat_in; 
int max_passengers = 3; 


nomask void
create_object()
{
    seteuid(getuid()); 
    this_object()->create_boat();  
    add_name("boat"); 
    add_adj("rowing"); 
    add_prop(OBJ_I_FLOAT, 1); 
    add_prop(OBJ_I_WEIGHT, 50000); 
    add_prop(OBJ_I_VOLUME, 200000); 
    add_prop(OBJ_M_NO_GET, "It's too big and awkward to carry.\n"); 
}


void
set_max_passengers(int n)
{
    max_passengers = n; 
}


int
query_max_passengers()
{
    return max_passengers; 
}


/* Stop players on the inside of the boat seeing the outside of it 
   in the outside view :) */ 
int
check_seen(object for_obj)
{
    if (objectp(for_obj) && objectp(boat_in) && 
        objectp(present(for_obj, boat_in)))  
        return 0; 
    else 
        return ::check_seen(for_obj); 
}



varargs public mixed
long(string str)
{
    mixed lg;
    string c;

    lg = ::long(str);

    if (str)
        return lg;

    if (!objectp(boat_in)) 
        return lg;

    c = contents_desc(boat_in); 
    if (!strlen(c)) 
         c = "Nothing.\n"; 
    c = ("Inside " + LANG_THESHORT(this_object()) + " you see the " +
         "following:\n" + c); 

    return (lg + "The command <ahoy> will work with this type " +
           "of boat.\n" + c);
}


/* Mask this to configure the long, short, items, objects etc. in the 
   boat, but remember to ::config_boat_inside() as this contains important 
   stuff. Should only be called once, after creation, of any boat. */ 
void
config_boat_inside()
{
    if (!objectp(boat_in))
         boat_in = clone_object("/d/Calia/std/boat_in"); 

    boat_in->set_boat_out(this_object()); 
    boat_in->set_boat_loc(environment(this_object())); 
    boat_in->add_exit(file_name(environment(this_object())), "out"); 
}


/* Set the next direction for the boat to row in */
void
set_direc(string d)
{
    next_direc = d; 
}


void
enter_env(object dest, object old)
{
    string s, sh; 

    ::enter_env(dest, old); 
  
    if (!stringp(next_direc)) 
        s = ""; 
    else
        s = (" " + next_direc); 

    sh = capitalize(LANG_ADDART(short())); 
    tell_room(old, sh + " is rowed away" + s + ".\n"); 
    tell_room(dest, sh + " is rowed in.\n"); 
    old->boat_exit(this_object()); 
    dest->boat_enter(this_object()); 
}


/* Mask this to set up things as one wants on the reset of the inside of
   the boat. */ 
void
reset_boat_inside()
{

}


/* If this boat is recreated after the outside was destructed, 
   boat_in can be set from the boat inside. */ 
void
set_boat_in(object bi)
{
    boat_in = bi; 
}


object
query_boat_in()
{
    return boat_in; 
}


/* Perhaps someone is trying to climb into this boat */ 
int
do_climb(string str)
{
     object tp; 
     object *ob;

     if (!stringp(str)) {
          notify_fail("Climb where? Boat?\n"); 
          return 0;
     }

     tp = this_player(); 
     ob = FIND_STR_IN_ARR(str, all_inventory(environment(this_object())));  

     if (sizeof(ob) == 0) {
          notify_fail("Climb where? Boat?\n"); 
          return 0; 
     }

     if (sizeof(ob) > 1) {  
          notify_fail("How can you climb into more than one thing " +
                      "at once?\n");
          return 0;
     }

     if (ob[0] != this_object()) 
         return 0;

     if (!objectp(boat_in))  
         config_boat_inside(); 

     if (boat_in->query_num_passengers() >= max_passengers)  { 
          notify_fail("The " + short() + " already appears to be full.\n"); 
          return 0;
     } 

     tp->move_living("climbing into the " + 
                     this_object()->short(), boat_in, 1);   
     return 1;
}


/* Inform the inside of the boat that this object has been removed, 
   so that this outside of the boat can be re-cloned in a second. */ 
void
remove_object()
{
    if (objectp(boat_in))
         boat_in->move_players_out(); 
    ::remove_object(); 
}


int 
is_boat(object ob)
{
    return ob->id("boat"); 
}


void
init()
{
    ::init();
    add_action(do_climb, "climb"); 
    add_action(do_climb, "board"); 
    add_action(do_climb, "enter");  
    add_action(ahoy, "ahoy"); 
}

