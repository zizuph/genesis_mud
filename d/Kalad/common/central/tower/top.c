/*
 * 2021-08-03 - Cotillion
 * - Fixed an issue where the quest could only be solved once per armageddon 
 */
inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define QBMAN "/d/Kalad/common/central/npc/q_tman"
#define BELL "/d/Kalad/common/central/obj/q_bell"

/* Modified by Antharanos for Taskmaster quest 1 */

void
create_room()
{
   ::create_room();
   INSIDE;
   
   set_short("landing");
   set_long("This is a small room at the top of the "+
      "bell tower. The bottom of the tower " +
      "is not visible as the center of the tower is filled by a " +
      " circular wall. " +
      "The walls are made of thick, interlaying blocks of granite. " +
      "A staircase spirals down around the walls and a doorway to the " +
      "northeast heads out on to the roof. " +
      "\n");
   
   hear_bell = 4; /*deafening: inside bell tower*/
   
   add_exit(CENTRAL(tower/roof),"northeast",0,-1,-1); /* inside: no fatigue */
   add_exit(CENTRAL(tower/stair7),"down",0,1); /*stairs:some effort*/
   
   add_item(({"stair","stairs","staircase","spiral staircase"}),
      BS("They are made of hard stone and curve down, out of sight, " +
         "around the walls of the tower.\n"));
   add_item(({"circular wall","wall","walls"}), BS(
         "The walls are made of thick, interlaying blocks of granite. " +
         "There is an outer wall and inner wall. " +
         "\n"));
   add_item("outer wall",BS(
         "This is the outside wall of the tower. It is made of " +
         "thick, interlaying blocks of granite.\n"));
   add_item("inner wall",BS(
         "The inner wall is circular and fills the center of the tower. " +
         "It is  made of thick, interlaying blocks of granite.\n"));

   add_object(BELL);
   add_npc(QBMAN);
} 

/* Moved functions from the bell to the room so it can detect if 
   the Quest NPC is here, and hint to players that he should be here.
   26/6-2021 Meton.*/

void
init()
{
   ::init();
   AA(polish,polish);
}

int
polish(string str)
{
    if (!str || !parse_command(str, this_player(), "[the] [great] [bronze] 'bell'"))
        return 0;

   write("You polish the great bronze bell.\n");
   say(QCTNAME(TP) + " polishes the great bronze bell.\n");

   set_alarm(2.0, 0.0, "polished");
   return 1;
}

void
polished()
{
   TP->catch_msg("The great bronze bell looks slightly cleaner.\n");

   if (!present("hyuk"))
   {
      write("If only someone here appreciated your work.\n");
   }

}
