/* 
 * /d/Kalad/common/wild/pass/w10.c
 * Purpose    : Road
 * Located    : Caravan Route out of Kabal
 * Created By : Antharanos  
 * Modified By: 
 */ 

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
void reset_room();
void create_brigands();
int shadows_disturbed;
/* by Antharanos */
void
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("The Caravan Route");
   set_long("You are travelling along the Caravan Route.\n"+
      "The way west eventually leads towards the famed city of Kabal. "+
      "All about you are the immense mountains of the Hespyre range. Almost lost "+
      "among the towering heights of the mountains are the no less "+
      "impressive redwoods, which blanket the lower slopes of the range. "+
      "The Caravan Route, which winds its way past the sheer walls of the mountains, "+
      "continues eastward, deeper into the Hespyre mountains.\n");
   add_item(({"caravan route","route","way"}),"A cobblestoned roadway that "+
      "appears worn due to heavy usage and the harsh effects of time and "+
      "weather.\n");
   add_item(({"immense mountains","hespyre range","hespyre mountains","mountain","range","immense mountains","hespyre mountain"}),
      "Craning your neck to take in the full sight of the mountains, their "+
      "sheer size and cold beauty make you feel as insignificant as a bug "+
      "compared with a human being. The mountains of the range cast a dark "+
      "shadow over the land.\n");
   add_item(({"impressive redwoods","impressive redwood","redwoods","redwood","lower slopes","lower slope","slopes","slope"}),
      "Giant redwood trees, as large as twenty feet across at the base "+
      "cover the lower slopes of the mountains. On the higher slopes, thin "+
      "blankets of snow are visible. The canopy of the trees, in combination "+
      "with the looming mountains results in deep shadows on the forest floor.\n");
   add_item("shadows", "@@exa_shadows");
   add_item(({"sheer walls","sheer wall","walls","wall"}),"The "+
      "unclimbable sides of the mountains.\n");
   add_exit("/d/Kalad/common/wild/pass/w9", "west",0,2);
   add_exit("/d/Kalad/common/wild/pass/w11", "east",0,2);
   reset_room();
}
void
reset_room()
{
   shadows_disturbed = 0;
   return;
}
string
exa_shadows()
{
   if(shadows_disturbed)
      return("You peer intently at the shadowy depths of the forest, eyes "+
      "searching intently for the slightest hint of movement...and then..."+
      "\n"+
      "\n"+
      "\n"+
      "A squirrel dashes in front of you!\n");
   set_alarm(6.0,0.0,"create_brigands");
   return("You peer intently at the shadowy depths of the forest, eyes "+
      "searching intently for the slightest hint of movement...and then...\n");
}
void
create_brigands()
{
   int i;
   shadows_disturbed = 1;
   for(i = 0; i < 6; i++)
   {
      clone_object("/d/Kalad/common/wild/pass/npc/brigand")
      ->move(TO);
      tell_room(TO, "A brigand jumps out from behind a tree!\n");
   }
}
