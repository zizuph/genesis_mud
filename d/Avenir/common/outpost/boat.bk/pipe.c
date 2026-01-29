// -*-C++-*-
// $Id: pipe.c,v 1.2 1995/09/13 01:12:01 bob Exp $
// file name: d/Avenir/common/outpost/boat/pipe.c
// creator(s):  Kazz    May 1995
// last update: 
// purpose:     inherit file for boat 'pipe' functions.
// note:	currently used in outpost/boat/boat_path2_copy &
//	 	  bazaar/pier/float
// bug(s):
// to-do:

#pragma save_binary

#include "/d/Avenir/common/common.h"

#define DEBUG

#ifdef DEBUG
#define D(x) find_player("lilith")->catch_msg("PIPE DEBUG: " + (x))
#else
#define D(x) ;
#endif

object query_ship();

private object boat_start_room;

void
init_boat_room()
{
  add_action( "do_call_boat", "beat" );
  add_action( "do_call_boat", "hit" );
  add_action( "do_call_boat", "pound" );

  add_action( "dont_move", "move" );
  add_action( "dont_move", "pull" );
  add_action( "dont_move", "push" );
  add_action( "dont_move", "get" );
  add_action( "dont_move", "take" );
} // init_boat_room()


/* Function name: pipe_description
 * Returns:       the default string for a pipe used to call a Sea boat.
 *                for the delivery office. This can be called eg with:
 *                add_item(({"pipe", "metal pipe"}), "@@pipe_description@@");
 */
public string
pipe_description()
{
  return( "The hard metal pipe sticks out about two feet from the sea "+
	 "surface. It leans over the beach slightly, and you can "+
	 "see it disappear underwater at the same angle. Despite the "+
	 "hard quality of the metal, the pipe has scratches.\n" );
} // pipe_description()


/* Function name: pipe_scratch_description
 * Returns:       the default string for a pipe used to call a Sea boat.
 *                for the delivery office. This can be called eg with:
 *                add_item(({"scratches", "pipe scratches"}), "@@pipe_scratch_description@@");
 */
public string
pipe_scratch_description()
{
  return( "The scratches are scattered along the length of the pipe.\n" );
} // pipe_scratch_description()


// beating on metal pipe to summon the Sea boat.
//
//  old: function_exists("create_weapon",weapon) == "/std/weapon"
int
do_call_boat(string str) {
  object obj;
  string foo;
  object *inv;
  
  // these defines are from Gondor.h
  NFN( CAP(QVB) + " what?");
  if (!str || !strlen(str)) 
    return 0;
  
  inv = all_inventory(TP);
  if (!parse_command( str, inv, "[metal] 'pipe' %s", foo))
    return 0;
  
  notify_fail( CAP(QVB) +" the pipe with what? Your hands would be hurt.\n");
  
  if (!parse_command(str, inv, "[metal] 'pipe' 'with' %o", obj)) 
    return 0;
  
  // make sure this object is a weapon, and heavy enuf to make a noise.
  if (!obj->query_wielded()) {
    TP->catch_msg( "You aren't wielding the " + obj->short() +"!\n");
    return 1;
  }
  
  TP->catch_msg( "You beat on the metal pipe with the " +
		obj->short() +"!\n");
  say( QCTNAME(TP) + " hits the metal pipe with "+
       TP->query_possessive() + " "+ obj->short() +".\n" );
  
  // coming depends on the creature's current state.
  if (!query_ship()->call_boat(file_name(this_object())))
    // call_boat always returns 1.
    // If we're here query_ship() returned bad value.
    TP->catch_msg("The pipe is broken. Please leave bug report.\n");
  
  return 1;
}

int
dont_move(string str)
{
  NFN( CAP(QVB) + " what?");
  if (!str || !strlen(str)) 
    return 0;
  
  if ((str != "pipe") && (str != "metal pipe")) 
    return 0;
  
  TP->catch_msg( "The pipe won't budge.\n" );
  return 1;
} // dont_move()

object
query_ship() { return boat_start_room->query_ship(); }

void
set_boat_start_room(object ob) {boat_start_room = ob; }



