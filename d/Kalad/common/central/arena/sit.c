/* The inner circle of the arena */ 
/* Made by Korat 0701-95 */ 

inherit "/d/Kalad/room_std";  
#include "/d/Kalad/defs.h" 

void 
create_room()
{
   ::create_room();
   hear_bell = 2; 
   set_short("seats");
   
   set_long("You find yourself sitting, watching the fights.\n");
   
   set_time_desc (" The seats around you are crowded with spectators "+
      "watching the fights.\n"," At this late our there are few people "+
      "watching the fights. You can sit down almost anywhere.\n"); 
   
   add_exit(CENTRAL(arena/inner_circle1),"rise","@@rise",-1,-1);
   
   add_item (({"arena","coliseum"}),
      "The arena is a hugh circular structure, divided up in two "+
      "levels. On this level the common people usually sits down and "+
      "enjoy the sight of death and heroism, while the richer people tend "+
      "to pay abit more to get better seatings and a better view on the "+
      "second level. At the top you can see several banners flap in "+
      "weak wind.\n");
   
   add_item (({"banner","banners"}),
      "On the top of this structure, you can see several banners line "+
      "up along the outer walls. The only detail you can see from this "+
      "distance is that they have a deep red colour that reminds you "+
      "of dried blood.\n"); 
   
}

rise()
{
   TP->catch_msg("You stand up.\n");
   return 0;
}

