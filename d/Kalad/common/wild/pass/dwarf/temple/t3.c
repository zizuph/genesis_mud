inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object gem;
object shred;
int eye_fixed;

/* by korat */

create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Outside a temple");
   set_long("You seem to be at something that once was a small "+
      "plaza situated inbetween several temples that now has "+
      "suffered the destiny of destruction and pillaging. To "+
      "the northwest you can see the outline of such a ruin "+
      "and you still remember another one even further westwards. "+
      "Your lightsource doesn't reach far enough eastwards, "+
      "but you have a creeping feeling that another one is to be "+
      "found in that direction. "+
      "From here you can walk both to the northwest and southwest, "+
      "making a turn around "+
      "some ruins in the center of this old plaza.\n");
   add_item(({"temple","temples","temple ruin","temple ruins"}),
      "Just a few whole stones can be seen of the northwestern one, making "+
      "fairly unaccessable. A gut feeling tells you that you will "+
      "find another one further east.\n");
   add_item("plaza","The plaza seems to be surrounded by old temple-ruins, "+
      "and is fairly deserted for life. In the center you see yet more "+
      "cracked stone-blocks that once might have been a statue or monument.\n");
   add_item(({"path","street","streets"}),"Among all the rubble you can "+
      "walk along a small trodden path that the dwarven boots has "+
      "managed to clear.\n");
   add_item(({"monument","statue"}),
      "Among all the cracked stone-blocks you can see something resembling "+
      "a head wearing an armour carved stone and a long majestic beard.\n");
   add_item(({"armour in stone","armour carved into stone"}),
      "It is all cracked up and partly covered in greyish moss. "+
      "The armour has been masoned to resemble a helmet with several "+
      "ornated decorations.\n");
   add_item(({"decorations","decoration","platemail","ornated platemail","ornated decorations"}),
      "It has been smoothed out during time."+
      " You do "+
      "understand that when this statue once was new, it was "+
      "a work of art. But that must be decades ago.\n");
   add_item("head","The head has survived the ordeals of time, showing how "+
      "excellent this piece of work was when it was new. The face "+
      "is like an image from reality, but contains an aura of immortality "+
      ", power and wisdom; The flowing majestic beard seems to emphasize the "+
      "knowledge while the eyes shows the extreme power this statue once "+
      "symbolized. Something puzzles you though; The eye seems to be "+
      "undone.\n");
   add_item("beard","It is a majestic beard that flows down from the dwarven "+
      "face, giving it an aura of omnipotent knowledge.\n");
   add_item(({"eye","shred","flaw"}),"@@check_eye@@");
   
   add_exit(CPASS(dwarf/temple/t4),"northwest");
   add_exit(CPASS(dwarf/temple/t2),"southwest");
   add_exit(CPASS(dwarf/temple/t5),"east","@@temple");
   
   set_noshow_obvious(1);
   set_alarm(0.0,0.0,"reset_room");
}
reset_room()
{
   eye_fixed = 0;
}
init()
{
   ::init();
   add_action("insert","insert");
   add_action("insert","place");
   add_action("insert","put");
}
insert(string str)
{
   object *ob;
   int ok;
   int i;
   notify_fail("Insert what into what?\n");
   if(!str) return 0;
   if(!parse_command(str, E(TP),"'shred' [in] / [into] [stone] 'eye'"))
      return 0;
   ob = all_inventory(TP);
   ok = 0;
   for (i=0;i<sizeof(ob);i++)
   {
      if (ob[i]->query_prop("korat_quest_shred")==1)
         {
         ok = 1;
         shred = ob[i];
        }
   }
   notify_fail("But you don't have any shred on you.\n");
   if (!ok) return 0;
   notify_fail("But the shred doesn't fit anywhere on the eye.\n");
   if(eye_fixed) return;
   shred->remove_object();
   write("You insert the shred into the small flaw of the "+
      "stone-eye. It fits perfectly!\n");
   say(QCTNAME(TP)+" does something with the stone-eye.\n");
   eye_fixed = 1;
   set_alarm(3.0,0.0,"eye_effect",TP);
   return 1;
}
eye_effect(object person)
{
   if (!present(person)) return;
   tell_room(TO,"The stone-eye suddenly changes! Where there "+
      "once was a perfectly shaped eye-ball, it now glints of "+
      "riches beyond any dreams ... a red sparkling gem shines "+
      "as the sun in a hot desert, draping you in a veil of "+
      "protection against any fright and horror.\n");
   person->catch_msg("You feel yourself blessed with a gift "+
      "of gratitude and automatically pick the gem out of the "+
      "eyesocket.\n");
   tell_room(TO,QCTNAME(person)+" bends down and picks the gem out "+
      "of the eyesocket.\n",person);
   gem = clone_object(CPASS(dwarf/obj/quest_gem));
   gem -> move(person);
}
check_eye()
{
   if(eye_fixed)
      return "The eye is perfectly shaped, except instead of a "+
   "eyeball, you see a small hole in the stone.\n";
   
   return "The small flaw of this once marvellous monument of some deity, is "+
   "a small cut in the right eye, where a shred must have been "+
   "accidentally chipped out when it was masoned some decades ago.\n";
}
temple()
{
   object *ob;
   int ok;
   int i;
   ob = all_inventory(TP);
   ok = 0;
   for (i=0;i<sizeof(ob);i++)
   {
      if (ob[i]->query_prop("korat_quest_thing")==1)
         {
         ok = 1;
        }
   }
   if (ok)
      {
      TP->catch_msg("The glow from the gem pushes away the darkness "+
         "and all the fright you know lingers in the chamber. You boldly step "+
         "further onwards.");
      say(QCTNAME(TP)+" seems to be unscratched by the fright that lingers "+
         "in the chamber and walks onwards.\n");
      return 0;
   }
   if(TP->query_base_stat(SS_DIS)>30)
      {
      write("You feel uneasy about walking eastwards, but continue "+
         "slowly.\n");
      say(QCTNAME(TP)+" looks uneasy about going further east, but continus "+
         "slowly.\n");
      if(TP->query_wiz_level()>0)
         {
         write("As a wizard you don't get more paniced.\n");
         return 0;
      }
      TP->add_panic(40);
      return 0;
   }
   write("A chilling feeling decends upon you as you start to walk "+
      "eastwards.\n");
   say(QCTNAME(TP)+" looks very unseasy as "+TP->query_pronoun()+
      "tries to walk eastwards.\n");
   if(random(TP->query_base_stat(SS_DIS))<15)
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
      write("As a wizard oyu don't get more paniced.\n");
      return 1;
   }
   TP->add_panic(40);
   return 1;
}
make_para(object player)
{
   object stun;
   stun = clone_object(CPASS(dwarf/obj/stun_object));
   stun->move(player);
}
