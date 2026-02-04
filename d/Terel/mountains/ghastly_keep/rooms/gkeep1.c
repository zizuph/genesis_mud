/* /d/Terel/mountains/ghastly_keep/rooms/gkeep1.c
 *
 * One of the rooms in the Ghastly Keep.
 * This is the entrance room for the ghastly keep.
 * Znagsnuf
 *
 * - Language tweak complete (Gorboth)
 *
 */

/*

         _,.-------.,_
     ,;~'             '~;,
   ,;                     ;,
  ;                         ;
 ,'      Ghastly Keep       ',
,;                           ;,
; ;      .           .      ; ;
| ;   ______       ______   ; |
|  `/~"     ~" . "~     "~\'  |
|  ~  ,-~~~^~, | ,~^~~~-,  ~  |
 |   |        }:{        |   |
 |   l  0    / | \'  0   !   |
 .~  (__,.--" .^. "--.,__)  ~.
 |     ---;' / | \ `;---     |
  \__.       \/^\/       .__/
   V| \                 / |V
    | |T~\___!___!___/~T| |
    | |`IIII_I_I_I_IIII'| |
    |  \'III I I I III,/  |
     \''  `~~~~~~~~~~'    /
       \'  .       .    / 
         \'    ^    . /
           ^~~~^~~~^

*  Date:                      What is done:                            By whom:            
*  ----------------------------------------------------------------------------
*  28/04-17                   The Ghastly Keep is opened!              Znagsnuf
*  28/04-17                   Fixed a typo with an extra space         Znagsnuf   
*
*/

#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include "defs.h";

inherit GKEEP_STD_ROOM;

int do_slide(string str);
int arrival;

/*
 * Function name: create_gkeep_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_gkeep_room()
{
    update_longdesc();

    set_short("Immense castle ruins");
    set_long("Standing here in front of the castle ruins, you are amazed"
            + " with the size and scope of the castle complex. The cathedral "
            + "inside the complex was at one time in history lavishly "
            + "adorned, but now only heaps of stone are left. Tall "
            + "grey buildings once stood in the middle of the empty, "
            + "abandoned street. You can sense an evil presence within "
            + "it as its shadows darken the road - silent guttural sounds "
            + "heard as the spirits roam and wander the soulless, haunted "
            + "castle ruins. The darkness cast from the shadows of the "
            + "stones seems unlike what you are used to, a kind of "
            + "darkness that robs you of your best senses, replacing them "
            + "with a paralyzing fear.\n");

    add_item( ({"snowflakes", "snowflake", "flake", "flakes"}), "Gravity "
               + "has finally won the long battle, and carries "
               + "the snowflakes to the ground.\n");

    add_item( ({"stone", "stones", "sharp stones", "opening"}), "You see a "
               + "small opening between the sharp stones. The small opening "
               + "seems large enough to slide through.\n");

    add_item( ({"cathedral", "cathedrals"}), "Once upon a time it was"
               + " lavishly adorned, perhaps, but rubble alone remains.\n");

    add_item( ({"rubble", "pile", "piles"}), "Small piles of rubble made out "
               + "of rough fragments of broken stone covers the area.\n");

    add_item( ({"castle", "ruins","complex"}), "At one point in "
               + "history this complex was immense, but only rubble is left "
               + "behind.\n");

    add_item( ({"heap", "heaps"}), "The castle crumbles in slow motion, "
               + "slower than the eye can detect even over a lifetime. Only "
               + "the sun and the moon themselves witness the steady "
               + "deterioration of these abandoned turrets and ramparts. "
               + "You notice something strange about the stones.\n");

    add_item( ({"turrets", "ramparts", "rampart"}), "They are slowly "
               + "withering under the sun and moon.\n");

    add_item( ({"buildings", "street", "building"}), "Tall grey buildings "
               + "once stood in the middle of the empty abandoned street.\n");

    add_item( ({"spirits", "evil", "presence"}), "They roam and wander the "
               + "soulless, haunted caste ruins.\n");

    add_item( ({"dark", "darkness", "shadow", "shadows"}), "Darkness has "
               + "taken a stranglehold, squeezing light out of this area.\n");

    add_item( ({"street", "streets"}), "The streets are scattered with "
               + "personal items strewn about haphazardly. The streets "
               + "seem to have been cleared in a hurry.\n");

    add_item( ({"track", "tracks"}), "All of the tracks in this area are "
               + "leading towards the east.\n");

    add_item( ({"road", "roads"}), "The road is blocked with heaps of rocks, "
               + "making it impossible to go any further.\n");

    add_exit(GKEEP + "gkeep_ent",  "east");
    
    set_no_exit_msg( ({ "northeast", "northwest", "north", "southeast",
                        "south", "southwest", "west" }),
                        "There is no path leading in that direction.\n");

    // Need to follow tracks.
    set_noshow_obvious(1);

    // Outside.
    add_prop(ROOM_I_INSIDE, 0);

   //Room tell.
   set_tell_time(60); 
   start_room_tells();
   add_tell("Silvery flakes drifts down.\n"); 
   add_tell("Wintry air swirls around you.\n"); 

    // Cloning the Quest npc.
    add_npc(GKEEP_NPC + "g_steel", 1);

    reset_room();
}

/*
 * Function name: reset_room()
 * Description  : Resets the room
 */
void
reset_room()
{
    update_longdesc();
}

/*
 * Function name: init
 * Description  : Add commands to the player on the deck
 */
void
init() 
{
    ::init();
    add_action(do_slide, "enter");
    add_action(do_slide, "slide");
    add_action(do_slide, "pass");
}

/*
 * Function name: do_slide()
 * Description  : Transport the player to the next room.
 */
int do_slide(string str)
{
  
    if (!strlen(str))
    {
        notify_fail("Slide into the opening?\n");
        return 0;
    }
    notify_fail("Are you trying to slide into the opening?\n");
    if (!parse_command(str, ({ }),
        "[myself] [up] [in] / [into] [through] [the] " +
        "'hole' / 'opening' / 'stones'"))
        return 0;    

    notify_fail("This opening is not large enough to allow the passage "
               + "for you, and your steed.\n");
      if (TP->query_prop("_live_o_steed"))
         return 0;    

    write("\nYou slide down in the opening between the sharp stones, "
         + "into the darkness.\n\n");
    say(QCTNAME(TP) + " slides down in the opening between the sharp stones,"
                    + " and disappears into the darkness.\n");

    // Send a notification to the next room.
    tell_room(GKEEP + "gkeep2", QCTNAME(TP) + " arrives from an opening "
             + "in the ceiling.\n");

    TP->move_living("M", GKEEP + "gkeep2",1,0);
    
    return 1;
}

/* 
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 */
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    object steel = present("_ghastly_keep_npc_steel", TO);

    if (!ob || !present(ob, TO))
    return;

    if (living(ob) && (steel) && CAN_SEE(steel, ob))
    {
      set_alarm(1.0,0.0,  "greet_arrivals",  ob);
      set_alarm(10.0,0.0, "remove_arrivals", ob);
    }
}

/*
 * Function name: greet_arrivals()
 * Description  : Just a friendly greetings to the travelers
 */
void
greet_arrivals(object ob)
{

    object steel = present("_ghastly_keep_npc_steel", TO);
    object *team;

    if (!ob || !present(ob, TO))
      return;

    if(ob->query_real_name() == "steel")
      return;

    if (ob->query_npc())
      return;
    
    if(arrival)
      return;    

    if (living(ob) && (steel) && CAN_SEE(steel, ob))
    {    
       if(T_WIZ(ob))
       {
          steel->command("say to " + ob->query_real_name() + " Greetings, "
                      + "Creator of Old!"); 
          return;
       }

      // Check if other members in the team.  
      team = ob->query_team_others();

      if (sizeof(team))
      {
        steel->command("say Greetings travelers!");
        arrival = 1;
        return;
      }
      else
      {
        steel->command("say Greetings traveler!");
        arrival = 1;
        return;
      }
      tell_room(ob, "Bug. Please report it.\n");
    }
}

/*
 * Function name: remove_arrivals()
 * Description  : Just a friendly greetings to the travelers
 */
void
remove_arrivals(object ob)
{
    arrival = 0;
}    