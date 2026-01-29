inherit "/std/object.c";
#include "/d/Genesis/city/defs.h"
#include <stdproperties.h>

static object holder;
static string Pad_string = ("                              "+
   "                                 ");

void
create_object()
{
   ::create_object();
   set_name("charter");
   set_short("The Arcoron City Charter");
   set_long("This is the City Charter of Arcoron.  It will identify you as one of the \n"+
      "founders of Arcoron and will provide you with powers worthy of that\n"+
      "possition.  Please 'read charter' to find these powers.\n");
   add_prop(OBJ_M_NO_DROP,1);
}

void
init()
{
   ::init();
   add_action("spot","spot");
   add_action("info","read");
   add_action("cwho","cwho");
}


public int
info(string str)
{
   if(str=="charter")
      {
      write("Arcoran City Charter commands:\n"+
         "cwho -	\t\t\t\tA compact 'who' list.\n"+
         "spot <player> -	\t\t\tSee a player's environment.\n"+
         "\n");
      return 1;
   }
   else
      return_fail("No information availiable on "+str+".\n");
}

public int
spot(string seepl)
{
   string rm1,rm2;
   int i;
   object *allwho,*inv;
   object plr,rm;
   allwho = users();
   plr = find_player(seepl);
   if(member_array(plr,allwho) != -1)
      {
      rm = environment(plr);
      write(rm->query_short()+"   "+file_name(rm)+"\n"+
         rm->query_long()+
         plr->query_name()+" "+plr->query_title()+"\n\n");
      inv = all_inventory(rm);
      for(i=0;i<sizeof(inv);i++)
      {
         rm1 = inv[i]->query_name();
         rm2 = file_name(inv[i]);
         write(rm1+"\t\t\t\t"+rm2+"\n");
      }
      return 1;
   }
   else
      return_fail(capitalize(seepl)+" isn't in the game.\n");
}

public int
cwho()
{
   /* Credits to Cynicus on KoBra Mud for assistance with the formatting,
   which almost works!
   */
   int i,length,diff;
   int mornum,wiznum,plnum;
   string plname;
   object *allwho;
   allwho = users();
   plnum = sizeof(allwho);
   write("\nMortals currently present:\n");
   for(i=0;i<sizeof(allwho);i++)
   {
      if(allwho[i]->query_wiz_level()==0)
         {
         mornum++;
         plname = allwho[i]->query_name();
         length = strlen(plname);
         if(!(diff=(20 - length)))
            write(plname);
         if(diff>0)
            write(plname+Pad_string[1..(diff-1)]);
       }
   }
   write("\n");
   write("\nWizards currently present:\n");
   for(i=0;i<sizeof(allwho);i++)
   {
      if(allwho[i]->query_wiz_level() > 0)
         {
         wiznum++;
         plname=allwho[i]->query_name()+" "+allwho[i]->query_wiz_level();
         length = strlen(plname);
         if(!(diff=(20 - length)))
            write(plname);
         if(diff>0)
            write(plname+Pad_string[1..(diff-1)]);
       }
   }
   write("\n");
   write("Total mortals: "+mornum+".  Total Wizards: "+wiznum+".  Total Players: "+plnum+".\n");
   return 1;
}

