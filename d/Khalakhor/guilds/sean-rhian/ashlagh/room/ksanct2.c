// in the village kirk
#include "defs.h"
inherit  ROOM+"ksanct";
#include  "/d/Khalakhor/guilds/sean-rhian/defs.h"
 
void create_khalakhor_room()
{
   extra="You are standing at the entrance of the sanctuary.";
   create_ksanct();
   add_exit("ksanct1","west");
   add_exit("ksanct4","north");
   add_exit("ksanct3","east");
   add_exit("courtk","south");
   reset_room();
   num_manachs=3;
   reset_room();
   (clone_object(OBJ+"altar"))->move(this_object());
}
 
void do_bow(object ob)
{
      ob->command("emote places his hands together prayerfully and bows "+
                  "deeply toward the altar.");
}
 
void enter_inv(object ob, object from)
{
   if (ob->id(SR_NPC_ID)) set_alarm(3.0,0.0,&do_bow(ob));
   ::enter_inv(ob,from);
}
