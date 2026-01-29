/* A can of paint
* With big help from
* Napture and Gresolle
* Joshua 19950114
*
* Updated: Jakob 950301
*/

#pragma save_binary

inherit "std/object";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <language.h>
#include "/d/Roke/common/defs.h"
#include "/d/Roke/common/qbits.h"



int n;


create_object()
{
   n=1;
   set_name("can");
   set_short("can of paint");
   set_long("This is a can of paint. There is some "+
      "black paint left in the can. \n");
   set_adj(({"painted","black"}));
   
   add_prop(OBJ_I_VALUE, 293);
   add_prop(OBJ_I_VOLUME, 200);
   add_prop(OBJ_I_WEIGHT, 750);
   
}

init()
{
   ::init();
   add_action("paint_me", "paint");
}

paint_me(string what)
{
   object dragobj;
   object *arr;
   string possesiv;
   
   seteuid(getuid());
   notify_fail("Paint what? \n");
   if (!what)  return 0;
   
   if (environment(TO) != TP)  {
      notify_fail("But you have nothing to paint with!\n");
      return 0;
   }
   
   what = lower_case(what);
   sscanf(what, "%s black", what);  /* Remove `paint dragon black` */
   arr = FIND_STR_IN_OBJECT(what, environment(TP));
   if (!sizeof(arr))   return 0;
   if (sizeof(arr) > 1)  {
      notify_fail("You can only paint one thing at a time!\n");
      return 0;
   }
   
   dragobj = arr[0];
   
   if (n>3)
      {
      notify_fail("Damn, There is no paint left...\n");
      TO->set_long("This is can of paint. "+
         "There is no paint left in it. \n");
      return 0;
   }
   if (present("_the_paint_subloc",dragobj))
      {
      if(TP != dragobj)
         TP->catch_msg(QCTNAME(dragobj) + " is already painted black!\n");
      else 
         TP->catch_msg("You are already painted black!\n");
      return 1;
   }
   
   clone_object(MOUNT + "obj/paint_subloc")->move(dragobj);
   if (dragobj->id("kaheda_dragon_quest"))
      {
      n++;
      TP->catch_msg("You paint the lovely dragon black! \n");
      say(QCTNAME(TP) + " paints " +LANG_ADDART(dragobj->short())+ "!!\n");
      if (!QDONE(GROUP1,PAINTQUEST) && (TP->query_alignment() <0))
         {
         TP->catch_msg("You feel more experienced!\n");
         TP->add_exp(50,0);
         ADDEXP(TP,50,0);
         QSET(GROUP1,PAINTQUEST);
         QLOG("paint quest");
         seteuid(getuid());
         log_file("log_file", ctime(time()) + " " +
            " Paint quest (Q): " + this_player()->query_real_name() +"\n");
         return 1;
       }
   }
   else
      {
      n++;
      
      possesiv = TP->query_objective()+"self";
      
      if (TP != dragobj)
         {
         if (TP->query_met(dragobj))
            write("He he you paint "+dragobj->short()+" black. Great fun! \n");
         else
            write("He he you paint the "+dragobj->query_race_name() +
            " black. Great fun! \n");
      }
      else
         write("He he you paint yourself black. Great fun! \n");
      
      if (TP != dragobj)
         {
         say(QCTNAME(TP)+" paints "+QNAME(dragobj)+" black! \n",
            ({dragobj, TP}));
         dragobj->catch_msg(QCTNAME(TP)+" paints you black!\n");
      }
      else
         {
         say(QCTNAME(TP)+" paints "+ possesiv +" black! \n");
      }
      return 1;
   }
   return 1;
}

