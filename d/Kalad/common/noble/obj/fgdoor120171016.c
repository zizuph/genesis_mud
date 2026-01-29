/* by Antharanos with header from Aldarion */
/* 2017-09-18 Malus: Header contents were removed, so removing directive */ 
inherit "/std/door";
create_door()
{
   set_door_id("fgdoor");
   set_pass_command(({"e","east"}));
   set_door_name(({"pair of massive steel doors","massive steel doors","steel doors","doors","massive doors"}));
   set_other_room("/d/Kalad/common/noble/farmer-end");
   set_fail_pass("The Farmer's Gate is closed!\n");
   set_open(0);
   set_str(300);
   set_door_desc("These huge double doors are the only way through the "+
      "huge encircling walls of Kabal. Built out of solid steel and "+
      "standing thirty feet in height, as well as several feet in "+
      "thickness, the Farmer's Gate is virtually impassable when closed. "+
      "A large winch lies beside the doors.\n");
}
