// Kirk of Port City - Abbey Library - upper level (private)
//
// History:
// Date        Coder       Action
//----------   ----------- ----------------------------------
// 7/20/98     Zima        Created
//
//
#include "defs.h"
#include <macros.h>
inherit  ROOM+"ulib";
 
object monk;
string* BFname = ({
                 "_empty",
                 "rh_accept"
                 });
string* Tlist  = ({
                 "_empty",
                 "the rhian of acceptance"
                 });
 
//
// reset_room
//
void reset_room()
{
   if (!objectp(monk))
      {
      monk = clone_object(SR_NPC+"alebard");
      monk->equip_me();
      monk->move(TO);
      tell_room(TO,QCTNAME(monk)+" enters the library.\n");
      }
}
 
//
// create_khalakhor_room
//
void create_khalakhor_room()
{
   create_library("north"," flanked by two large cabinets filled with "+
                  "books, scrolls and other documents",0);
 
   add_item(({"cabinet","cabinets","books","scrolls","documents"}),
      "There are two large oak cabinets standing along the northern "+
      "wall, one on each side of the window. Each is filled with "+
      "books, scrolls and other documents of import to the abbey, "+
      "and is protected by a lead crystal door over its front. "+
      "You notice a small plaque pertaining to the cabinets on the "+
      "wall below the window.\n");
 
   add_item("plaque",
      "The plaque says: Ask the librarian for help with writings reserved "+
      "in the cabinets.\n");
   add_cmd_item("plaque","read",
      "The plaque says: Ask the librarian for help with writings reserved "+
      "in the cabinets.\n");
 
   add_exit("ucorr3",   "south");
   add_exit("ulib2",    "east");
   add_exit("ulibpost", "west");
   reset_room();
}
 
//
// monk_here
//
int monk_here() { return (objectp(monk)&&present(monk,TO)); }
 
//
// list_titles
//
int list_titles()
{
   if (!monk_here())
      write("There is no one here to help you.\n");
   else if (!(TP->is_saggart()))
      monk->command("say You may not read any of the writings here.");
   else if ((TP->query_sr_level())<SRLVL_SEARM1)
      monk->command("say Novishaghs are not allowed to read the "+
                    "writings here.");
   else
      write("The titles you can borrow are:    \n"+
            "   The Rhian of Acceptance        \n"+
            "");
  return 1;
}
 
//
// do_return
//
int do_return(string cmd)
{
  object ob;
  string obs;
 
  if (!monk_here())
     write("There is no one here to help you.\n");
  else if (!stringp(cmd))
     monk->command("say What is it you wish to return?");
  else if (!(parse_command(cmd,all_inventory(TP),"%o",ob)))
     monk->command("say What is it you wish to return?");
  else if (!(ob->query_prop(SR_RES_BOOK)))
     monk->command("say The "+(ob->short())+" does not belong here.");
  else
     {
     obs = (ob->short());
     ob->remove_object();
      write("You return the "+obs+" to the librarian.\n");
     tell_room(TO,QCTNAME(TP)+" returns a "+obs+".\n",TP);
     monk->command("emote places the "+obs+" in the secured cabinet.");
     }
  return 1;
}
 
//
// valid_title - return ndx into parallel arrays
//
int valid_title(string t)
{
   int ndx = member_array(lower_case(t),Tlist);
   if (ndx>0) return ndx;
   return 0;
}
 
//
// do_borrow
//
int do_borrow(string cmd)
{
   int    tnum;
   object book;
 
   if (!monk_here())
      write("There is no one here to help you.\n");
   else if (!(TP->is_saggart()))
      monk->command("say You may not read any of the writings here.");
   else if ((TP->query_sr_level())<SRLVL_SEARM1)
      monk->command("say Novishaghs are not allowed to borrow the "+
                    "writings here.");
   else if (!stringp(cmd))
      monk->command("say Which writing do you wish to borrow?");
   else if (!(tnum = valid_title(cmd)))
      monk->command("say I have nothing entitled "+cmd+" to lend you.");
   else
      {
      book=clone_object(SR_BOOK+BFname[tnum]);
      book->move(monk);
      monk->command("emote takes a book from the secured cabinet.");
      monk->command("give book to "+lower_case(TP->query_name()));
      monk->command("drop book");
      }
   return 1;
}
 
//
// init
//
void init()
{
   ::init();
   add_action(&list_titles(),"list");
   add_action(&do_borrow(),  "borrow");
   add_action(&do_return(),  "return");
}
