//
// Rhian Book of Sean-Rhian - allows member to easily perform rhians
//
// Zima July 19, 1998
//
#include "defs.h"
#include <ss_types.h>
inherit  SR_BOOK_BASE;
 
string *cmd   = (({}));
int    numcmd = 0;
 
//
// set_cmdlist
//
void set_cmdlist(string* clist)
{
   cmd = clist;
   numcmd = sizeof(cmd);
}
 
//
// create_book
//
void create_book()
{
   set_name("Unknown Rhian");
   set_long("It is a book of an unknown rhian.\n");
}
 
//
// do_cmd - interpret arg as a line number; have player perform that line
//
int do_cmd(string s)
{
   int i;
   if (book_is_closed)
      write("The "+short()+" is closed.\n");
   else if (!allowed(TP))
      write("The book is enchanted. Your vision blurs when you try to "+
            "look at the lettering.\n");
   else if (!stringp(s))
      write("Rh which line number?\n");
   else
      {
      i = atoi(s);
      if ((i<1)||(i>=numcmd))
         write("There is no number "+i+" in the rhian.\n");
      else
         TP->command(cmd[i]);
      }
   return 1;
}
 
 
//
// init - add "rh" command
//
void init()
{
   ::init();
   add_action(&do_cmd(),"rh");
}
