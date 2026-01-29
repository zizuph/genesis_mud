/* 
 * /d/Kalad/common/central/arena/inner_circle5.c
 * Purpose    : The inner circle of the arena
 * Located    : /d/Kalad/common/central/arena/
 * Created By : Korat 1995
 * Modified By: 
 */ 

/* The inner circle of the arena */ 
/* Made by Korat 0701-95 */ 

inherit "/d/Kalad/room_std";  
#include "/d/Kalad/defs.h" 

void 
create_room()
{
    ::create_room();
    hear_bell = 2; 
    set_short ("The inner circle of the arena"); 

    set_long ("You have arrived at the "+
      "northeastern "+
      "side of the arena, with a good view of the combat scenes "+
      "in the center of the coliseum. Far above you on the other side "+
      "of the circular arena some banners flaps slightly in the mild "+
      "wind, and below them you see the richer part of the audience "+
      "enjoying the excellent view they have of the battles going on down "+
      "in the arena. You can see @@number_of_fights@@.");

    set_time_desc (" The seats around you are crowded with spectators "+
      "watching the fights.\n", " At this late hour there are few people "+
      "watching the fights. You can sit down almost anywhere.\n"); 

    add_exit(CENTRAL(arena/inner_circle4),"northwest",0,-1,-1);
    add_exit(CENTRAL(arena/inner_circle6),"southeast",0,-1,-1);

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

    add_item (({"combat","fight","fights"}),
      "The gladiators seems to be some excellent warriors, all ready to "+
      "fight until death comes as a savior from their unbearable "+
      "pains. If you want to look at a specific fight, then sit down and "+
      "choose one.\n"); 
}

number_of_fights()
{
    return "no fights being fought down there now. The arena is still not ready "+
    "for the sounds of metal hitting metal being "+
    "drowned by the cheering of the spectators when the weapons draw "+
    "blood.";
}
