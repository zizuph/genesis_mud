inherit "/std/door";

/* Sarr */

void
create_door()
{
   set_door_id("vault");
   set_pass_command(({"n","north"}));
   set_door_name(({"pair of large wooden doors","wooden doors","doors"}));
   set_other_room("/d/Kalad/common/noble/castle/g3");
   set_door_desc("These are a pair of large wooden oak doors. On "+
   "it, you see the golden symbol of the High-Lord.\n");
   set_fail_pass("You bang your nose on the closed doors.\n");
   set_open(0);
}
