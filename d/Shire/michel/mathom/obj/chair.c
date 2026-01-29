// 1996/03/17 Last update
// 2011/07/18 Lavellan - Added west blocking, as it is cloned in adventuresome
//      hobbits guild too. Improved command parsing.
//      Made it so only one person can sit at once. *sigh*

inherit "/std/object";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>

int do_rock(string str);
int do_sit(string str);
object sitter;

void
create_object()
{

     set_short("wooden rocking chair");
     set_name("chair");
     add_adj(({"wooden","rocking"}));
     set_long("This wooden rocking chair is in good condition and looks "+
     "as if it is used quite frequently.\n");
     add_prop(OBJ_I_WEIGHT, 10000); /* Not too heavy to carry */
     add_prop(OBJ_I_VOLUME, 10000); /* Big chair */
     add_prop(OBJ_M_NO_GET, 1); /* Can't take it with ya */
}

void
init()
{
    ::init();
    add_action("do_rock","rock");
    add_action("do_sit","sit");
    add_action("do_nothing","east");
    add_action("do_nothing","e");
    add_action("do_nothing","south");
    add_action("do_nothing","s");
    add_action("do_nothing","west");
    add_action("do_nothing","w");
    add_action("do_nothing","sneak");
    add_action("do_stand","stand");
    add_action("do_nothing","bow");
}

int
do_nothing(string str)
{
   if(TP->query_prop("i_am_sat"))
   {
    write("You're sitting down, you can't do that! Stand up first.\n");
    return 1;
   }
}

int
do_stand(string str)
{
   if(!str) { write("Stand where? Up?\n"); return 1; }
   if(str != "up")
   {
     write("Stand "+str+"? How do you plan to do that?\n");
     return 1;
   }

   if(!TP->query_prop("i_am_sat"))
   {
    write("But you aren't sitting down!\n");
    return 1;
   }

   TP->remove_prop("i_am_sat");
   write("You stand up again, feeling relaxed.\n");
   say(QCTNAME(TP)+ " stands up again, a bit more relaxed than before.\n");
   sitter = 0;
   return 1;
}

int
do_sit(string str)
{
   if(!str) { return 0; }
   //if((str != "chair")  && (str !="in chair") && (str !="on the chair"))
   if (!parse_command(str, TO,
    " 'in' / 'on' [the] [wooden] [rocking] 'chair' "))
   {
    write("Sit in what?\n");
    return 1;
   }

  if((TP->query_prop("i_am_sat")))
  {
   write("You are already seated!\n");
   return 1;
  }

   if (objectp(sitter)) {
    if (environment(sitter) == environment(TO))
    {
     write(sitter->query_The_name(TP) + " is already sitting in the chair.\n");
     return 1;
    }
   }
   TP->add_prop("i_am_sat",1);
   write("You take your seat in the rocking chair.\nAhh, that feels good!\n");
   say(QCTNAME(TP)+ " has a seat in the wooden rocking chair.\n");
   sitter = TP;
   return 1;

}


int
do_rock(string str)
{
   if(!str) { return 0; }
   if((str != "chair")  && (str !="in chair") && (str !="the chair"))
   {
    write("Rock what?\n");
    return 1;
   }

  if(!(TP->query_prop("i_am_sat")))
  {
   write("You rock the chair gently, back and forth.\n");
   say(QCTNAME(TP)+ " rocks the chair back and forth.\n");
   return 1;
  }

   write("You rock back and forth in the chair.\nWhee!\n");
   say(QCTNAME(TP)+ " has a good time rocking back and forth in the chair.\n");
   return 1;

}

