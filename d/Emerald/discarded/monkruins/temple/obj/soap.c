/* temple/obj/shovel.c is cloned by temple/bathroom.c */
inherit "/std/object";
 
#include "/d/Emerald/defs.h"
 
void
create_object()
{
  seteuid(getuid(this_object()));
  set_name("soap");
  add_name("_ring_quest_soap_");
  set_short("wet soap");
  set_adj("wet");
  set_long("It's wet soap. Even a person with a lack of intelligence " +
           "can understand that it's good for soaping.\n");
 
  add_prop(OBJ_I_WEIGHT,500);
  add_prop(OBJ_I_VOLUME,300);
  add_prop(OBJ_I_VALUE,100+random(20));
}
 
init()
{
 ::init();
 if (environment()==this_player())
   add_action("do_soap","soap");
}
 
int
do_soap(string str)
{
 object key;
 
 if ((str=="me") || (str=="myself"))
  {
  if (function_exists("create_room", ENV(ENV(TO)))==
          TEMPLE_DIR + "bathroom")
   {
    if ((TP->query_prop("_ring_quest_")==1) &&
          (TP->query_prop("_got_key_")!=1))
      {
       write("When you try to soap yourself, the soap jumps out from " +
             "your palm.\n");
       write("You charge for it, and you see the soap fly into " +
             "the furthest corner of room...\n");
       write("When you squeeze through tubs in hope to get your soap " +
             "back, you find the gold key !\n");
       say(QCTNAME(TP) + " drops his soap and then runs in the " +
           "furthest corner of room, trying to get it back.\n");
       key=clone_object(TEMPLE_DIR + "obj/gold_key");
       key->move(ENV(ENV(TO)));
       TP->add_prop("_got_key_",1);
       return 1;
      }
     notify_fail("You soap yourself. Now, where is the water?\n");
     return 0;
    }
   notify_fail("You soap yourself. Now, where is the water?\n");
   return 0;
  }
  notify_fail("Soap what?\n");
  return 0;
}
