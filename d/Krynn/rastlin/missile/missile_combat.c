/*
 * This module is designed to support missile fire between 2 or more rooms.
 * Note:  This is a non-standard room module.  It must be inherited separately.
 *
 * To use this module the following calls need to be made.
 * In create_room():
 *   add_other_missile_rooms(string rm, string str1, string str2, int visible) 
 *      - 'rm' is the path to the linked, 'str1' is a string to show others 
 *      in the firer's environment where he is shooting (ex: "out the window"),
 *      'str2' is the string indicating the direction from  which the missile 
 *      came (ex: "from the bushes"), and 'visible' is a flag indicating 
 *      whether the firer will be visible to targets in 'rm' when s/he shoots.
 *   set_cover(int amt) - sets the amount of cover in the room.  This affects
 *      the chance of hitting a target in the room.
 *
 * Under normal conditions no other calls need to be made.  However if the
 * room does some complex or non-standard things the following functions can
 * be redefined to support changes to local conditions.
 * In the firer's room:
 *   query_target_rooms(firer) - this function returns a list of rooms to check
 *      for possible targets.  If the position of the firer affects the rooms
 *      that he can 'see' targets in, this function should be redefined.
 *   query_room_firer_mods(target_room, firer) - this fuction returns the 
 *      'terrain' modifications to the missile attack for the room the firer
 *      is in, 0 by default.  Redefine this functions if the position of the
 *      firer in this room affects his ability to hit a target in the 
 *      target's room.
 * In the target's room:
 *   query_target_list(firer_env) - this function returns the list of targets
 *      visible to the environent of the caster.  By default that's everthing
 *      in the room.  Should the position of a target affect its visibility
 *      to certain rooms this function should be redefined.
 *   query_room_target_mods(firer_room, target) - this function returns the
 *      'terrain' modifications to the missile attack for the room the target
 *      is in, the value of 'cover' by default.  Redefine this function if the
 *      position of the target in this room affects his ability to be hit by
 *      someone in the firer's room.
 *
 */

mixed  other_rooms = ({});     /* array of connected rooms and their params */
string *other_room_list = ({}); /* backup list of rooms */
int    cover;                  /* default amount of cover in the room */
int    first_call = 1;         /* test for first call of load_other_rooms */

/* prototypes */
void load_other_rooms();

/*
 * Function Name: add_other_missile_room
 * Description:   add a room to the list of rooms that can be reached via
 *                missile combat.  The 2nd argument is optional.
 * Arguments:     rm - the room path to add to the list.
 *                str1 - a string indicating to where the firer is shooting.
 *                str2 - a string indicating where the missile is coming from.
 *                visible - a flag for whether the firer is visible to his
 *                   targets or not.  By default the firer is visible.
 */
varargs void
add_other_missile_room(string rm, string str1="into the distance", 
   string str2="from afar", int visible=1)
{
   mixed temp;

   if(!strlen(str2))
      str2 = "from_afar";
   temp = ({rm, str1, str2, visible});
   other_rooms += ({temp});
   other_room_list += ({rm});
}

/*
 * Function Name: query_other_missile_rooms
 * Description:   returns the list of rooms from which target in this room can
 *                be reached.
 * Returns:       the list of rooms, either as strings or objects.
 */
mixed
query_other_missile_rooms()
{
   return other_rooms;
}

/*
 * Function Name: query_other_room_list
 * Description:   returns the backup list of linked rooms.
 * Returns:       the list of linked rooms, as strings.
 */
string *
query_other_room_list()
{
   return other_room_list;
}

/*
 * Function Name: set_cover
 * Description:   sets the amount of cover (as a percentage) available in the
 *                room.
 * Arguments:     amt - amount of cover
 */
void
set_cover(int amt)
{
   cover = amt;
}

/*
 * Function Name: query_cover
 * Description:   returns the amount of cover in the room.
 */
int
query_cover()
{
   return cover;
}

/*
 * Function Name: query_room_firer_mods
 * Description:   returns the modifications to missile combat caused by the 
 *                firer's location w/in this room.  By default this is 0.
 * Arguments:     target_room - the object containing the target.
 *                firer - the object doing the shooting.
 * Returns:       the local modifications to missile combat.
 */
int
query_room_firer_mods(object target_room, object firer)
{
   return 0;
}

/*
 * Function Name: query_room_target_mods
 * Description:   returns the modifications to missile combat caused by the 
 *                target's location w/in this room.  By default this is the
 *                cover value for this room.
 * Arguments:     firer_room - the object containing the target.
 *                target - the object doing the shooting.
 * Returns:       the local modifications to missile combat.
 */
int
query_room_target_mods(object firer_room, object target)
{
   return cover;
}

/*
 * Function Name: query_target_rooms
 * Description:   returns a list of rooms which can be checked for valid 
 *                targets.  This function returns the full list of rooms
 *                by default and should be redefined if the list should be
 *                limited by some local condition (ex. a closed window).
 * Arguments:     firer - object firing the missile.
 * Returns:       the list of room-objects which might contain targets.
 */
object *
query_target_rooms(object firer)
{
   int i;
   object *list = ({});

   for(i=0; i<sizeof(other_rooms); i++)
      list += ({other_rooms[i][0]});

   return list;
}

/*
 * Function Name: query_target_list
 * Description:   returns a list of potential targets in this room.  By default
 *                it returns the entire inventory of the room.  If local
 *                conditions limit acceptable targets this function should be
 *                redefined.
 * Arguments:     firer_env - the environment of the firer, ie the linked room
 *                            in which the firer is standing.
 * Returns:       the list of potential target objects.
 */
object *
query_target_list(object firere_env)
{
   return all_inventory(this_object());
}


/*
 * Function Name: query_valid_targets
 * Description:   returns the list of targets that can be shot at from this 
 *                room by a given individual.
 * Arguments:     firer - object doing the shooting.
 * Returns:       the list of targets.
 */
object *
query_valid_targets(object firer)
{
   int i;
   object *rooms, *targets = ({});

   /* lets do this very time to make sure we have room objects */
   load_other_rooms();

   rooms = this_object()->query_target_rooms(firer);
   rooms -= ({0});
   for(i=0; i<sizeof(rooms); i++)
      targets += rooms[i]->query_target_list(this_object());

   return targets;
}

/*
 * Function Name: load_other_rooms
 * Description:   attempts to load any other rooms not loaded and store a list
                  of the objects.
 */
void
load_other_rooms()
{
   int i;
   object temp;

   for(i=0;i<sizeof(other_rooms);i++)
   {
      if(objectp(other_rooms[i][0]))
         continue;

      if(!other_rooms[i][0])
         other_rooms[i][0] = other_room_list[i];

      if(temp = find_object(other_rooms[i][0]))
         other_rooms[i][0] = temp;
      else
      {
         other_rooms[i][0]->teleledningsanka();
         other_rooms[i][0] = find_object(other_rooms[i][0]);
         if(other_rooms[i][0] == 0)
            other_rooms[i] = 0;
      }
   }
   other_rooms -= ({0});
   first_call = 0;
}

