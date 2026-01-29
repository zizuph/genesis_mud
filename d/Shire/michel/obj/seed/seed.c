inherit "/std/object";
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/d/Shire/common/defs.h"

#define RANADJ   ({"tiny","round","square","long","big"})
#define RANADJ2 ({"green","yellow","brown","grey","black"})
#define HERBNAME pawnrose
#define HERBPATH "/d/Shire/common/herbs/pawnrose"

int do_grow();
void test_growth();

   int mess;

void
create_object()
{
   set_name("seed");
   add_name("germ");

   set_adj("ordinary");
   add_adj("looking");
   set_short("ordinary looking seed");

   set_long("This "+short()+" seems to grow, even in your hand. "+
                  "You think it would grow even faster if you planted it.\n");

   add_prop(OBJ_I_VALUE, 15);
   add_prop(OBJ_I_VOLUME, 37);
   add_prop(OBJ_I_WEIGHT, 25);

   FIXEUID;

   mess = 0;

}

void
init()
{
    ::init();
    add_action("do_plant","plant");

}

int
do_plant(string str)
{
   int likely;

     if (str != "seed")
     {
      write("Plant what?");
      return 1;
     }

   if(environment(environment(TO))->query_prop(ROOM_I_INSIDE))
    {
      write("You cannot expect to grow anything indoors!\n");
       return 1;
    }


   say(QCTNAME(TP)+ " kneels down and does something to the dirt.\n");
   likely = (TP->query_skill(SS_HERBALISM));

   set_alarm(itof(15+random(20)), itof(30 + random(60)),"do_count");
//  set_alarm(itof(600+random(60)),0.0,&remove_growth());

   TO->remove_name("seed");
   TO->set_long("This small germ is growing in the ground.\n");
   TO->add_prop(OBJ_M_NO_GET, "The germ is firmly rooted in the ground.\n");
   TO->add_prop("_likely_to_grow",likely);
   TO->move(environment(environment(TO)));

   return 1;
}

void
do_count()
{
   mess = mess + 1;
   set_alarm(1.0,0.0,"do_grow");

}
int
do_grow()
{

   switch(mess)
   {
     
     case 0:
     tell_room(environment(TO), "The seed buries itself into the ground.\n");
     break;

     case 1:
     tell_room(environment(TO), "The seed germinates and begins to grow.\n");
     break;

     case 2:
     tell_room(environment(TO), "A shoot grows up from the ground.\n");
     break;

     case 3:
     tell_room(environment(TO), "The shoot thickens and begins to branch out.\n");
     break;

     case 4:
     tell_room(environment(TO), "The shoot grows into a full-fledged plant.\n");
     break;

     case 5:
       set_alarm(1.0,0.0,"test_growth");
     break;

   }

}

int
test_growth()
{
   object herb, plant, plant2;

   if(!TO->query_prop("_likely_to_grow") > 20 + random(60))
   {
     tell_room(environment(TO), "The plant withers and dies, leaving only sad remains.\n");
     plant2 = clone_object(MICH_DIR + "obj/seed/dead_plant");
     plant2->move(environment(TO));
     return 1;
     TO->remove_object();
    }

   plant = clone_object(MICH_DIR + "obj/seed/live_plant");
   plant->set_short("A plant");
   plant->set_long("This plant looks like it is fertile.\n");
   plant->add_prop(OBJ_M_NO_GET, 1);
   plant->move(environment(TO));

   herb = clone_object(HERBPATH);
   herb->move(plant);
   return 1;
   TO->remove_object();

}
