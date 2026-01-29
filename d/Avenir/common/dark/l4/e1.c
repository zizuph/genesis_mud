// File name:    /d/Avenir/common/dark/l4/e1.c
// creator(s):   Farlong
// last update:  Cirion, May 1996 - added Ogres, cleaned up the area.
// purpose:      Tunnels in Level 5 of the Utterdark, containing Ogres and
//               other nasties.
// note:         
// bug(s):       
// to-do:        
// revision:     
/*
center.c is W
e2.c is E
*/
//updated by Lilith 2 Nov 1996, for use with the dark_treas_pmodule.c 
// file in the /dark/obj/* dir. It places crates here.

inherit "/d/Avenir/inherit/room";

# include "/d/Avenir/common/dark/dark.h"
# include "/d/Avenir/smis/sys/statserv.h"
#define IS_MEMBER(x)  ((x)->query_guild_name_occ() == "Union of the Warriors of Shadow")

/* Prototypes.
 */
int check_down();

create_domain_room()
{
  set_short("collapsed tunnel");
 set_long("Much of this tunnel's ceiling and walls have collapsed"
+" inward, creating a pile of debris in the center of the passage."
+" The debris has recently been cleared enough to reveal a stairway leading"
+" down into the shadows. Back west is a large chamber.\n");


add_exit("/d/Avenir/common/dark/l4/center","west",0);
add_exit(L5+"s20","down", check_down);

BLACK
IN

add_item(({"rubble","debris","pile"}), break_string("Part of the walls"
+" and ceiling have collapsed, leaving a pile of dirt and stones in"
+" the center of the tunnel.\n",75));
AI(({"stair","stairs","stairway"}),"The stairs leading down are very old, and "
+"a terrible smell is eminating from the opening created by them.\n");
AI(({"ceiling", "walls", "wall", "floor"}),
   "Very uninteresting stone.\n");  

}

int
block()
{
  if (!this_player()->query_wiz_level())
    {
      write (
      "The pile of stones is too high for you to pass.\n");
      return 1;
    }
return 0;
}


int check_down()
{
   if(!interactive(TP) || TP->id("merchant"))
     return 2; // make the merchant take another exit...
  if(TP->query_stat(SS_DIS) < 50)
  {
   write("The smell from below brings about an awful sense of "
      +"dread.\nYou cannot bring yourself to climb down the "
     +"steps.\n");
   TP->add_panic(80);
    return 1;
  }

  STATSERV_LOG_EVENT("Utterdark", "Entered the ogre lair");
 return 0;
}

/*
 * Function name: find_union
 * Description:   Check to see if a specific player is here.
 * Arguments:     ob - the player to check
 * Returns:       1 - in tell zone,
 *		  0 - not.
 */
static int
find_union(object ob)
{
    if (IS_MEMBER(ob))
    {
        ob->catch_msg("\nYou have a sudden premonition of "+
            "ogres on the move!\n");
        return 1;
    }

    /* The player ins't who we're looking for */
    return 0;
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (ob->id("ave::ogre_raider"))
        (filter(users(), find_union));
 
}
