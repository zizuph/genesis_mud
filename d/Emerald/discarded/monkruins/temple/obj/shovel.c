/* temple/obj/shovel.c cloned by temple/npc/abbed.c */
inherit "/std/object";
 
#include "/d/Emerald/defs.h"
 
int cracked;
 
void
create_object()
{
  seteuid(getuid(this_object()));
  set_name("shovel");
  set_short("small shovel");
  set_adj("small");
  set_long("@@shovel_desc");
 
  add_prop(OBJ_I_WEIGHT,1500);
  add_prop(OBJ_I_VOLUME,2300);
  add_prop(OBJ_I_VALUE,50+random(20));
 
  cracked=0;
}
 
string
shovel_desc()
{
 string txt;
 
 txt = "This is a small shovel. It is very old and going to " +
        "break soon.";
 if (cracked==0)
   txt = txt + "\n";
 if (cracked==1)
   txt = txt + " There are some cracks on it already.\n";
 if (cracked==2)
   txt = txt + " It is covered with many cracks.\n";
 return txt;
}
 
init()
{
 ::init();
 if (environment()==this_player())
   add_action("do_dig","dig");
}
 
int
do_dig(string str)
{
 string qro;
 int broken=0;
 object ring;
 
 if (str=="here" || str=="ground")
  {
   write("You dig here with the small shovel.\n");
   if (cracked==0)
     write("Some cracks appear on it.\n");
   if (cracked==1)
     write("More cracks appear on it.\n");
   if (cracked==2)
     {
      write("The shovel breaks from your efforts!\n");
      broken = 1;
     }
   cracked=cracked + 1;
   qro=function_exists("create_room",ENV(ENV(TO)));
   if  ((qro==TEMPLE_DIR + "tunnel1" &&
            TP->query_prop("_ring_is_")==4) ||
       (qro==TEMPLE_DIR + "tunnel4" &&
            TP->query_prop("_ring_is_")==3) ||
       (qro==TEMPLE_DIR + "tunnel5" &&
            TP->query_prop("_ring_is_")==2)  ||
       (qro==TEMPLE_DIR + "tunnel7" &&
            TP->query_prop("_ring_is_")==1) &&
       (TP->query_prop("_me_found_ring_")!=1))
              {
               write("You found a ring!\n");
               ring=clone_object(TEMPLE_DIR + "obj/q_ring");
               ring->move(ENV(ENV(TO)));
               TP->add_prop("_me_found_ring_",1);
              }
        else write("You found nothing.\n");
   say (QCTNAME(TP) + " digs ground with " + HIS_HER(TP) +
                 " small shovel.\n");
   if (broken) remove_object();
   return 1;
  }
 notify_fail("Dig where?\n");
 return 0;
}
