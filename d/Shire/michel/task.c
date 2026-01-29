inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include <macros.h>
#include <stdproperties.h>
object ob;
create_room() {

   set_short("A hobbit's entrance hall");
   set_long("You are standing inside a hobbit's entryway "+
    "and it is sparsely decorated, even for a hobbit. A hatrack "+
    "stands near the door, and a picture hangs on the wall to your left. "+
   "There does not seem to be any way to go further into "+
   "this kindly hobbit's house, you can go back out to "+
   "the town or try to see the hobbit's pony in the stables.\n");

   add_item(({"door","doorway","wall","picture"}),
   "The door is almost always open, leaving the doorway wide "+
    "open and the picture free to steal from the wall, if you could just "+
    "do it without the hobbit seeing you.\n");

   add_item(({"pony","stables","stable","house"}),
    "You cannot see the pony from inside this house, perhaps you "+
     "should try going to the stables?\n");
   add_prop(ROOM_I_INSIDE,1);
   add_prop(ROOM_I_NO_ATTACK, 1);
   add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
 
   add_exit("/d/Shire/common/greyhaven/md2","out",0);
   add_exit(MICH_DIR + "task_st","stables", "@@wiz_check");
   reset_room();
 }
 
void
init()
{
    ::init();
    add_action("do_pull","pull");

}
/*
 * Function name:   wiz_check
 * Description:     Check if a player is a wizard
 * Returns:         0 if the player is a wizard
 *                  1 otherwise
 * Modified function from  Shires herbshop
 */
wiz_check()
{
   seteuid(geteuid(this_object()));
   if (this_player()->query_wiz_level()
       || this_player()->query_npc())
      return 0;
   write("The old hobbit doesn't think you have any business here.\n");
   say("The hobbit is stopping " + QCTNAME(this_player()) + ".\n");
   return 1;
}
 
reset_room() {
   if(!ob) {
   ob = clone_object(MICH_DIR + "npc/task_master");
   ob->move(this_object());
} }
