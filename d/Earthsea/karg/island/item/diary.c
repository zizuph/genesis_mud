inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

#include "defs.h"

#define PAGES 19
#define PATH_HINT_PAGE 13
#define TREE_HINT_PAGE 19

int open=0;
int page=1;

void create_object()
{
 set_name("diary");
 set_adj("old");
 add_adj("dusty");
 set_long("@@book_long");
}

string book_long()
{
 string res;

 res="This is old and dusty diary. Karg officer used it to report "+
   "all events into it. If you want to read it "+
   "you may open it and turn page backward or forward or to certain "+
   "page.\n";
 if(open) res+="The diary is open at page "+NUM_TO_STR(page)+".\n";
 else res+="The diary is closed.\n";

 return res;
}

void init()
{
 ::init();
 add_action("open","open");
 add_action("close","close");
 add_action("turn","turn");
 add_action("read","read");
}

int open(string what)
{
 if(!what) return 0;
 if(what!="diary") return 0;

 if(open)
  {
   write("The diary is already open!\n");
   say(QCTNAME(TP)+" looks kinda silly as "+PRO(TP)+" tries to open "+
     "an already opened diary.\n");
   return 1;
  }

 write("You open "+short()+".\n");
 say(QCTNAME(TP)+" opens "+short()+".\n");
 open=1;

 return 1;
}

int close(string what)
{
 if(!what) return 0;
 if(what!="diary") return 0;

 if(!open)
  {
   write("The diary is already closed!\n");
   say(QCTNAME(TP)+" looks kinda silly as "+PRO(TP)+" tries to close "+
     "an already closed diary.\n");
   return 1;
  }

 write("You close "+short()+".\n");
 say(QCTNAME(TP)+" closes "+short()+".\n");
 page=1;
 open=0;
 
 return 1;
}

void do_turn_forward()
{
 if(page==PAGES)
  {
   write("You are at the last page.\n");
   say(QCTNAME(TP)+" looks kinda silly as "+PRO(TP)+" tries to turn "+
     "the last page forward.\n");
   return;
  }

 page++;
 write("You turn "+short()+" to page "+NUM_TO_STR(page)+".\n");
 say(QCTNAME(TP)+" turns "+short()+" to page "+NUM_TO_STR(page)+".\n");
}

void do_turn_backward()
{
 if(page==1)
  {
   write("You are at the first page.\n");
   say(QCTNAME(TP)+" looks kinda silly as "+PRO(TP)+" tries to turn "+
     "the first page backward.\n");
   return;
  }

 page--;
 write("You turn "+short()+" to page "+NUM_TO_STR(page)+".\n");
 say(QCTNAME(TP)+" turns "+short()+" to page "+NUM_TO_STR(page)+".\n");
}

void do_turn_to_page(int num)
{
 if(num<1 || num>PAGES)
  {
   write("That is invalid page number.\n");
   say(QCTNAME(TP)+" looks kinda silly as "+PRO(TP)+" tries to "+
     "turn "+short()+" to unexisting page.\n");
   return;
  }

 page=num;
 write("You turn "+short()+" to page "+NUM_TO_STR(page)+".\n");
 say(QCTNAME(TP)+" turns "+short()+" to page "+NUM_TO_STR(page)+".\n");
}

int turn(string what)
{
 int res,num;
 string dir;

 NF("Try turning page forward , backward or to specific page , i.e "+
   "turn page forward or turn page 2.\n");
 if(!what) return 0;

 if(what=="page")
  {
   do_turn_forward();
   return 1;
  }
 
 res=sscanf(what,"page %s",dir);
 if(!res) return 0;

 if(dir=="forward")
  {
   do_turn_forward();
   return 1;
  }

 if(dir=="backward" || dir=="back")
  {
   do_turn_backward();
   return 1;
  }

 res=sscanf(what,"page %d",num);
 if(!res) return 0;
 do_turn_to_page(num);

 return 1;
}

int read(string what)
{
 if(!what) return 0;
 if(what!="diary") return 0;

 if(!open)
  {
   write("You try to read a closed diary.\n");
   say(QCTNAME(TP)+" looks kinda silly as "+PRO(TP)+" tries to read "+
     "a closed diary.\n");
   return 1;
  }

 setuid();
 seteuid(getuid());

 write("\n"+read_file(DIARY+sprintf("page%d.txt",page))+"\n");
 say(QCTNAME(TP)+" reads "+short()+".\n");

 if(page==PATH_HINT_PAGE) TP->add_prop(HAS_PATH_HINT,1);
 if(page==TREE_HINT_PAGE) TP->add_prop(HAS_TREE_HINT,1);

 return 1;
}

