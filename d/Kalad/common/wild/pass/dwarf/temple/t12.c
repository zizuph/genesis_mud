inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object statue1;
object statue2;
object statue3;

/* by korat */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Inside a temple");
   set_long("You seem to be at a larger chamber inside this temple "+
      "of doom that has "+
      "avoided the destiny of destruction and pillaging. "+
      "Back west you will leave this place that makes your blood "+
      "freeze, or you could try to continue further eastwards "+
      "where three exits forks out. Your lightsource doesn't reach "+
      "far enough to lighten it up, "+
      "but you know that peril lingers inside the"+
      " darkness.\n");
   add_item(({"temple","temples","temple ruin","temple ruins"}),
      "This temple has avoided the destruction, not through pure "+
      "luck but by some other means of protection.\n");
   add_item(({"path","street","streets"}),"Among all the rubble you can "+
      "walk along a small trodden path that the dwarven boots has "+
      "managed to clear.\n");
   add_item(({"exits","exit"}),"You see three of them that "+
      "continues further northeast, east and southeast into "+
      "pure darkness.\n");
   add_exit(CPASS(dwarf/temple/t10),"west");
   add_exit(CPASS(dwarf/temple/t13),"northeast","@@temple");
   add_exit(CPASS(dwarf/temple/t14),"southeast","@@temple");
   add_exit(CPASS(dwarf/temple/t15),"east","@@temple");
   
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
      write("The statues suddenly becomes alive "+
         "and blocks you from continuing to the east!\n");
      return 1;
   }
   
    if(TP->query_base_stat(SS_DIS)>70)
      {
      write("You feel very frightened about walking eastwards, but continue "+
         "slowly.\n");
      say(QCTNAME(TP)+" looks very frightened about going further eastwards, "+
         "but continues slowly.\n");
      if(TP->query_wiz_level()>0)
         {
         write("As a wizard you don't get more paniced.\n");
         return 0;
      }
      TP->add_panic(120);
      return 0;
   }
   write("A very chilling feeling decends upon you as you start to walk "+
      "eastwards.\n");
   say(QCTNAME(TP)+" looks very frightened as "+TP->query_pronoun()+
      "tries to walk eastwards.\n");
   if(random(TP->query_base_stat(SS_DIS))<50)
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
   TP->add_panic(120);
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
      statue1=clone_object(CPASS(dwarf/npc/statue));
      statue1->set_stats(({100,110,120,50,50,140}));
      statue1->move_living("M",TO);
      statue1->heal_hp(statue1->query_max_hp());
   }
   if(!objectp(statue2))
      {
      statue2=clone_object(CPASS(dwarf/npc/statue));
      statue2->set_stats(({100,110,120,50,50,140}));
      statue2->move_living("M",TO);
      statue2->heal_hp(statue1->query_max_hp());
   }
   if(!objectp(statue3))
      {
      statue3=clone_object(CPASS(dwarf/npc/statue));
      statue3->set_stats(({100,110,120,50,50,140}));
      statue3->move_living("M",TO);
      statue3->heal_hp(statue1->query_max_hp());
   }
   statue1->team_join(statue3);
   statue1->team_join(statue2);
}
