/* 
 * /d/Kalad/common/central/arena/entrance_arena.c
 * Purpose    : The entrance to the arena
 * Located    : /d/Kalad/common/central/arena/
 * Created By : Korat 1995
 * Modified By: 
 */ 

/* The entrance to the arena */
/* Made by Korat 0701-95 */


inherit "/d/Kalad/room_std";  
#include "/d/Kalad/defs.h"  

void reset_room();

object ob1;
object ob2;
object ob3;
object ob4;
object ob5;
object ob6;
void
create_room()
{
   
   ::create_room(); 
   hear_bell = 3; 
   set_short ("The entrance to the arena"); 
   set_long (
      "You are standing outside the huge gladiatoral arena of Kabal. "+
      "An arena famous for its excellent games that are held each day "+
      "to the pleasure of the audience. With its reputation of giving "+
      "a challenge to anyone who think they are skilled in the art of "+
      "combat, the arena keeps on attracting new fighters from every "+
      "part of the world. Inside it new heroes are made and old heroes "+
      "find their final but worthy death.\n");
   
   add_exit (CENTRAL(arena/outer_circle1),"north",0,1);
   add_exit (CENTRAL(arena/outer_circle16),"northeast",0,1);
   add_exit (CENTRAL(arena/outer_circle15),"east",0,1);
   add_exit (CENTRAL(gladiator/s5),"southwest",0,1);
   
   add_item (({"arena","coliseum"}),
      "The arena is a hugh circular structure, divided up in two levels. "+
      "At the top you can see several banners flap in the weak wind.\n"); 

   
   add_item (({"banner","banners"}),
      "On the top of this structure, you can see several banners line up "+
      "along the outer walls. The only detail you can see from this "+
      "distance is that they have a deep colour that reminds "+
      "you of dried blood.\n");
   
   reset_room();
   
}

reset_room()
{
   if(!objectp(ob1))
      {
      ob1 = clone_object("/d/Kalad/common/central/npc/slave");
      ob1 ->arm_me();
      ob1 -> move_living("xxx",TO);
   }
   if(!objectp(ob2))
      {
      ob2 = clone_object("/d/Kalad/common/central/npc/slave");
      ob2 ->arm_me();
      ob2 -> move_living("xxx",TO);
   }
   if(!objectp(ob3))
      {
      ob3 = clone_object("/d/Kalad/common/central/npc/slave");
      ob3 ->arm_me();
      ob3 -> move_living("xxx",TO);
   }
   if(!objectp(ob4))
      {
      ob4 = clone_object("/d/Kalad/common/central/npc/slave");
      ob4 ->arm_me();
      ob4 -> move_living("xxx",TO);
   }
   if(!objectp(ob5))
      {
      ob5 = clone_object("/d/Kalad/common/central/npc/slave");
      ob5 ->arm_me();
      ob5 -> move_living("xxx",TO);
   }
   if(!objectp(ob6))
      {
      ob6 = clone_object("/d/Kalad/common/central/npc/slave_man");
      ob6 ->arm_me();
      ob6 -> move_living("xxx",TO);
   }
   ob6 -> team_join(ob1);
   ob6 -> team_join(ob2);
   ob6 -> team_join(ob3);
   ob6 -> team_join(ob4);
   ob6 -> team_join(ob5);
}
