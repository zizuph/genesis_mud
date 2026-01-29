/* Name      : /d/Gondor/harondor/room/camp/wind_check_open.c
 * Purpose   : Keeping track of the secret trails options
 *             of being open or not.
 *             A timer of 2hrs +/- 5min keeps track on 
 *             updates on the exits.
 * Created by: Sir Toby, Gondor Domain, 2005-11-18
 *
 *   Modified: 2005-11-21, Sir Toby
 *                         Moved all code to handle the random
 *                         exits to this file.
 */

#include <stdproperties.h>


int wb_west = -1, wb_east = -1;
int my_time = time();

#define DEBUG(x) find_player("toby")->catch_msg("[DEBUG - wind_check_open]: "  + x + "\n")


/* Function name: wind_block_set
 * Description  : Set the exits to open or closed
 *                for the backdoor into the camp.
 *                The exits can have these four states:
 *                   1: west - open   :: east - closed
 *                   2: west - closed :: east - open
 *                   3  west - open   :: east - open
 *                   4: west - closed :: east - closed
 *                Global variables int wb_west, wb_east (1/0)
 *                where 1 is open and 0 is closed.
 * Arguments    : -
 * Returns      : -
 */
void wind_block_set()
{
   my_time = time();

   switch(random(4))
   {
      case 0:
         wb_west = 1;
         wb_east = 0;
 DEBUG("wb_west = 1 :: wb_east = 0");
         break;
      case 1:
         wb_west = 0;
         wb_east = 1;
 DEBUG("wb_west = 0 :: wb_east = 1");
         break;
      case 2:
         wb_west = 1;
         wb_east = 1;
 DEBUG("wb_west = 1 :: wb_east = 1");
         break;
      default:
         wb_west = 0;
         wb_east = 0;
 DEBUG("wb_west = 0 :: wb_east = 0");
         break;
   }

}

/* Function name: query_wind_open
 * Description  : Returns wether an exit is open, dir
 *                is mandatory.
 * Arguments    : string dir - The direction to examine
 * Returns      : int 1/0 - open/closed
 */
int query_wind_open(string dir)
{
   /* Updates every 2 hours: 2*60*60=7200s */

   if( (6900+random(600)) < (time() - my_time) || wb_east == -1 || wb_west == -1)
      wind_block_set();

   if(dir == "west")
      return wb_west;

   return wb_east;
}

/* Function name: wind_block
 * Description  : Gets called from room, argument is mandatory.
 * Arguments    : string dir - The west or east part of the 
 *                camp calling the function.
 * Returns      : int 1/0 - closed/open
 */
int wind_block(string dir)
{
   if(query_wind_open(dir))
      return 0;

   write("The mounds have grown too big to pass in that direction.\n");
   return 1;
}

