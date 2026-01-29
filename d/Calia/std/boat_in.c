
/*
   Standard inside of a boat.

   Copyright Miguel Leith 1996 

   Coded by Maniac, April 96
   Updated, Maniac, 30/7/96
*/

inherit "/std/room";
inherit "/d/Calia/std/contents_desc";
inherit "/d/Calia/std/ahoy";
inherit "/d/Calia/std/owner"; 

#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include "/d/Calia/sys/water.h"

object boat_loc;
string boat_loc_str;
object boat_out;
string boat_out_str;
int num_passengers = 0; 


/*
   Here create_room has some basics.  config_boat_inside() should be
   defined in the (outside) boat object to set up whatever special
   details one wants.
*/
void
create_room()
{
    set_short("Inside a rowing boat");
    set_long("You are sitting inside a rowing boat.\n");
    add_item("oars", "A pair of rowing oars are attached to the boat.\n");
    add_item("boat", "It is a rowing boat.\n");
}


int
query_inside_of_boat()
{
    return 1;
}


void
outer_room_check()
{
    if (!objectp(boat_loc))
        if (stringp(boat_loc_str))  {
            boat_loc_str->load_me();
            boat_loc = find_object(boat_loc_str);
        }
}


void
move_out(object player)
{
    outer_room_check(); 

    player->move_living("outside", boat_loc, 1); 
}


void
m_p_o()
{
    map(FILTER_PLAYERS(all_inventory(this_object())), move_out); 

    remove_object(); 
}


/* 
   This is called from the (outside object of the) boat when 
   it is removed, to move players outside the boat. 
   The inside of the boat is then removed.  
 */  
void
move_players_out()
{
    if (sizeof(FILTER_PLAYERS(all_inventory(this_object())))) 
        set_alarm(1.0, 0.0, m_p_o);
    else
        remove_object(); 
}


string
row_exit_desc()
{
    string red;

    outer_room_check();

    if (!stringp(red = boat_loc->row_exit_desc()))
        return "";
    else
        return red;
}

string
query_boat_vista()
{
    string bv;

    outer_room_check();

    if (!stringp(bv = boat_loc->query_boat_vista()))
        if (!stringp(bv = boat_loc->short()+ ".")) 
            return "";
    else
        return bv;
}


string
query_contents_desc()
{
     string d;

     outer_room_check();

     if (!stringp(d = this_object()->contents_desc(boat_loc)))
         return "";
     else
         return d;
}


string
view_long()
{
    string ot, b, r, q; 

    b = query_boat_vista();
    if (!strlen(b)) 
        b = "It doesn't look like very interesting scenery actually."; 
    r = row_exit_desc(); 
    if (!strlen(r)) 
        r = "It seems you can't row anywhere from here.\n"; 
    q = query_contents_desc();

    ot = (break_string(b, 65, "  } ") + "\n" + 
          break_string(q, 65, "  } ") + "\n");  
    return ("\n" + "  } Outside you see the following view:\n" + ot + r); 
}


varargs public mixed
long(string str)
{
    mixed lg;

    lg = ::long(str);

    if (str)
       return lg;

    return (lg + view_long()); 
}


/* Sets the associated object for the outside of the boat */
void
set_boat_out(object bo)
{
    if (objectp(bo)) {
        boat_out = bo;
        boat_out_str = MASTER_OB(bo);
    }
}



void
set_boat_loc(object bl)
{
     if (objectp(bl) && bl->query_prop(ROOM_I_IS)) {
         boat_loc = bl;
         boat_loc_str = file_name(bl);
     }
}



object
query_boat_loc()
{
    return boat_loc; 
}


int
do_row(string str)
{
     int r;
     object o;

     outer_room_check();

     if (!objectp(boat_loc)) {
         notify_fail("Ack! No boat environment! This should not " +
                     "happen, please commune a wizard.\n");
         log_file("water", "Boat without any external boat location! " +
                          ctime(time()) + ", player was " +
                          this_player()->query_real_name() + ".\n");
         return 0;
     }

     r = boat_loc->try_row(str); 

     if (r)
          owned_object_action(this_player(), "row " + str);  

     return r;
}


/* Move the boat to a new location, this is called from the water room one
   rowed _from_ when one tries to row in a legitimate direction */
void
carry_out_row(string direc, string to_path)
{
    object tp = this_player(); 

    if (!stringp(to_path))
        return;

    say(QCTNAME(tp) + " rows " + LANG_THESHORT(boat_out) + " " + 
                             direc + ".\n"); 
    write("You row " + LANG_THESHORT(boat_out) + " " + direc + ".\n"); 

    boat_out->set_direc(direc); 
    boat_out->move(to_path);  
    set_boat_loc(find_object(to_path));

    remove_exit("out");
    add_exit(to_path, "out");

    tell_room(this_object(), view_long()); 
}



int
query_num_passengers()
{
    return num_passengers; 
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from); 

    if (living(ob)) 
        num_passengers++; 
    enter_owned_room(ob, from);  
}


void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to); 

    if (living(ob)) 
        num_passengers--; 
    leave_owned_room(ob, to); 
}


void
init()
{
    ::init();
    add_action(do_row, "row");
    add_action(ahoy, "ahoy"); 
}

