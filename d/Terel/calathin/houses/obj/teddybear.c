#include "/d/Terel/include/Terel.h"
inherit "/std/object";
#define FOUND_THE_BEAR "_i_found_bear"
#define ASKED_FARM2_CROW "_i_asked_crow"

object chest_key;

int hug_bear(string str);
int rip_bear(string str);
int feel_bear(string str);

void create_object()
{
   seteuid(getuid(TO));
   set_name("teddy bear");
   add_name("bear");
   add_name("stuffed bear");
   add_name("teddy bear");
   add_name("teddybear");
   set_long("A cute, stuffed teddy bear with soft, fluffy " +
   "fur and dark button eyes.\n");

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 200);

}


void init()
{
   ::init();
   add_action(hug_bear, "hug");
   add_action(rip_bear, "rip");
   add_action(feel_bear, "feel");
}


int
feel_bear(string str)
{
   if(str=="bear" || str == "teddybear" || str == "teddy")
   {
   write("You feel something hard and lumpy inside the bear. " +
      "Perhaps, if you were mean enough, you could rip the bear " +
      "apart to find out what it is.\n");
   return 1;
   }
else
  {
   notify_fail("What do you wish to feel?\n");
   return 0;
  }

}


int 
hug_bear(string str)
{
   if(str=="bear" || str == "teddybear" || str == "teddy")
   {
   write("Thinking back to your younger days you fondly hug the " +
   "stuffed bear. You feel something lumpy in the bear.\n");
    say(QCTNAME(TP) +" hugs the bear, smiling fondly.\n");
   return 1;
   }
else
  {
   notify_fail("What do you wish to hug?\n");
   return 0;
  }
}

int
rip_bear(string str)
{
    if(str=="bear" || str == "teddybear" || str == "teddy")
   {
      chest_key=clone_object(CALATHIN_DIR + "houses/obj/chest_key");
         chest_key->move(TP);
   
   write("You viciously rip the tiny stuffed bear apart revealing a key.\n");
    say(QCTNAME(TP) +" rips apart the stuffed bear, grinning devilishly.\n");
   remove_object();
   
       if(TP->query_prop(ASKED_FARM2_CROW))
       {
          TP->add_prop(FOUND_THE_BEAR,1);
          return 1;
       }
   
   return 1;
  }
 else
  {
   notify_fail("You dont mean the cute little bear do you?\n");
   return 0;
  }
}
