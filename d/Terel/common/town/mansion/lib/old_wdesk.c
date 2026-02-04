inherit "/std/container.c";
#include "lib_defs.h"

object	ob;

void
init()
{
   ::init();
   add_action("do_lock","lock");
   add_action("do_unlock","unlock");
   add_action("do_open","open");
   add_action("do_close","close");
   seteuid(getuid(this_object()));
}

create_container()
{
  object sc;
   set_name("desk");
	add_name("writing_desk");
   set_adj("writing");
   set_adj("antique");
   set_long(BS("The fine, hard wood of the desk has remained "
         + "sound through the years. The desk itself is massive and looks quite "
         + "sturdy, carefully constructed and beautifully decorated "
         + "with elaborate carvings. It would probably be worth a fortune to "
         + "an antique collector; too bad it's too heavy to move!\n"));
   
   seteuid(getuid(this_object()));
   add_prop(CONT_I_WEIGHT, 200000);	/* weighs 200 kg */
   add_prop(CONT_I_MAX_WEIGHT, 100000);	/* holds a lot of weight */
   add_prop(CONT_I_VOLUME, 250000);	/* damn big desk! */
   add_prop(CONT_I_MAX_VOLUME, 250000);	/* holds plenty o' stuff */
   add_prop(OBJ_I_VALUE, 5000);		/* pretty valuable */
   add_prop(CONT_I_CLOSED, 1);           /* it is closed */
   add_prop(CONT_I_LOCK, 1);           /* it is locked */
   add_prop(CONT_I_RIGID,1);		/* it's rigid */

   ob=present("index");   
   sc=clone_object("/d/Terel/mecien/valley/guild/quest/scroll");
   sc->move(this_object());
}

int 
do_lock(string str)
{
  ob=present("index",environment(TO()));
  if (member_array(str,({"desk","writing desk","antique writing desk"}))!=-1)
   {
 
   if (this_object()->query_prop(CONT_I_LOCK))
      write("But it's already locked!\n");
   else
      if (present("writing_desk_key",this_player()))
      {
      if (this_object()->query_prop(CONT_I_CLOSED))
         {
         write("You lock the desk up again.\n");
         say(BS(QCTNAME(this_player()) + " locks up the antique writing desk.\n"));
         this_object()->add_prop(CONT_I_LOCK,1);
         }
      else
         {
	 ob->add_prop(OBJ_I_INVIS, 1);	    /* make the book invis when desk is closed */
         write("You close and lock the desk.\n");
         say(BS(QCTNAME(this_player()) + " locks up the antique writing desk.\n"));
         this_object()->add_prop(CONT_I_LOCK,1);
         this_object()->add_prop(CONT_I_CLOSED,1);
         }
      }
   else
      write("You do not have a key that fits!\n");
   return 1;
   }
   else return 0;
}

int 
do_unlock(string str)
{
  ob=present("index",environment(TO()));
 if (member_array(str,({"desk","writing desk","antique writing desk"}))!=-1)
   {
 
   if (this_object()->query_prop(CONT_I_LOCK)==0)
      write("But it's already unlocked!\n");
   else
      if (present("writing_desk_key",this_player()))
      {
          ob->add_prop(OBJ_I_INVIS, 0);	    /* make the book visible when desk is open */
	  write(BS("You unlock and open the desk to reveal a very ancient book, laying "
            + "open on the desktop.\n"));
          say(BS(QCTNAME(this_player())+" unlocks and opens the desk, "
            + "revealing an ancient book laying open on the desktop.\n"));
          this_object()->add_prop(CONT_I_CLOSED,0);
          this_object()->add_prop(CONT_I_LOCK,0);
      }
   else
      write("You do not have a key that fits!\n");
   return 1;
   }
   else return 0;
}

int
do_open(string str)
{
 ob=present("index",environment(TO()));
 if (member_array(str,({"desk","writing desk","antique writing desk"}))!=-1)
   {
   if (TO()->query_prop(CONT_I_CLOSED))
   {
      if (TO()->query_prop(CONT_I_LOCK))
         write("The desk is locked!\n");
      else
         {
	    ob->add_prop(OBJ_I_INVIS, 0);	    /* make the book visible when desk is open */
	    write(BS("You open the antique writing desk to reveal a very ancient book, laying "
               + "open on the desktop.\n"));
	    say(BS(QCTNAME(this_player())+" opens the desk, "
               + "revealing an ancient book laying open on the desktop.\n"));
	    TO()->add_prop(CONT_I_CLOSED,0);
	 }
   }
   else
      write("But it's already open!\n");
   return 1;
   }
   else return 0;
}

int
do_close(string str)
{
   ob=present("index",environment(TO()));
   if (member_array(str,({"desk","writing desk","antique writing desk"}))!=-1)
   {
    if (TO()->query_prop(CONT_I_CLOSED))
	  write("But it's already closed!\n");
       else
       {
	  ob->add_prop(OBJ_I_INVIS, 1);	    /* make the book invis when desk is closed */
	  write("You gently lower the cover of the antique writing desk.\n");
	  say(BS(QCTNAME(TP())+" closes the antique writing desk.\n"));
	  TO()->add_prop(CONT_I_CLOSED,1);
       }
       return 1;
   }
   else return 0;
}

string
stat_object()
{
   string str;
   
   str = ::stat_object();
   
   str += "CONT_I_LOCK: " + (mixed) TO()->query_prop(CONT_I_LOCK) + "\n";
   str += "CONT_I_CLOSED: " + (mixed) TO()->query_prop(CONT_I_CLOSED) + "\n";
   
   return str;
}
