inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object statue1;

/* by korat */

create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Inside a temple");
   set_long("You seem to have arrived inside a huge chamber in a temple "+
      "that has avoided the destiny of destruction and pillaging. "+
      "Back to the west, you will leave this place that makes your blood "+
      "freeze, or you could try to continue to the east. "+
      "Your lightsource doesn't reach far enough to lighten it up, "+
      "but somehow you know that salvation lingers inside that "+
      "eastern darkness.\n");
   add_item(({"temple","temples","temple ruin","temple ruins"}),
      "This temple has avoided the destruction, not through pure "+
      "luck but by a poweful curse of protection.\n");
   add_item(({"exits","exit"}),"You see one that "+
      "goes back west and one east into "+
      "pure darkness and salvation.\n");
   add_item("salvation","It is just a feeling you have, but one "+
      "you know is for real. It is like this place hides its own "+
      "purpose inside that dark chamber.\n");
   add_exit(CPASS(dwarf/temple/t15),"west");
   add_exit(CPASS(dwarf/temple/t17),"east","@@temple");
   
   set_noshow_obvious(1);
   set_alarm(0.0,0.0,"reset_room");
}

temple()
{
   object *ob;
   int i;
   int ok;
   ob = all_inventory(TP);
   ok = 0;
   for (i=0;i<sizeof(ob);i++)
   {
      if (ob[i]->query_prop("korat_quest_gem")==1)
         {
         ok = 1;
        }
   }
   if (ok)
      {
      TP->catch_msg("The glow from the gem pushes away the darkness "+
         "and all the fright you know lingers in the chamber. You boldly step "+
         "further onwards.\n");
      say(QCTNAME(TP)+" seems to be unscratched by the fright that lingers "+
         "in the chamber and walks onwards.\n");
      return 0;
   }
   if(present("statue"))
      {
      write("The dwarven statue suddenly becomes alive "+
         "and blocks you from continuing to the east!\n");
      statue1->command("kill "+TP->query_real_name());
      return 1;
   }
   
   write("An utterly chilling feeling decends upon you as you start to walk "+
      "eastwards.\n");
   say(QCTNAME(TP)+" looks extremely panicked as "+TP->query_pronoun()+
      "tries to walk eastwards.\n");
   if(random(TP->query_base_stat(SS_DIS))<140)
      {
      write("You try to control yourself, but a feeling of utter fright "+
         "flows through your body! You cannot move at all!!\n");
      say(QCTNAME(TP)+" goes visibly pale in fright and freezes up!\n");
      if(TP->query_wiz_level()>0)
         {
         write("As a wizard you don't get stunned. Lucky you.\n");
         return 0;
      }
      set_alarm(0.0,0.0,"make_para",TP);
   }
   if(TP->query_wiz_level()>0)
      {
      write("As a wizard you don't get more paniced.\n");
      return 1;
   }
   TP->add_panic(160);
   return 1;
}
make_para(object player)
{
   object stun;
   stun = clone_object(CPASS(dwarf/obj/stun_object));
   stun->move(player);
}
reset_room()
{
   if(!objectp(statue1))
      {
      statue1=clone_object(CPASS(dwarf/npc/statue_dwarf));
      statue1->arm_me();
      statue1 -> move_living("M",TO);
   }
}
