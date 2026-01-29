inherit "/std/room";

#include <stdproperties.h>

#define MAILREADER      "/secure/mail_reader"
#define MAILCHECKER	"/secure/mail_checker"

void
create_room()
{
   set_short("Private Post Office of the Keepers");
   set_long("   This small, wood-walled room has a small counter behind "+
	    "which you can see various sacks of scrolls and letters "+
	    "which are being carried to and from the other cities in an "+
	    "attempt to stay in contact with one another. There are even "+
	    "some sacks here from other continents.\n"+
	    "Commands Are:\n"+
            "    read           Read your mail.\n" +
            "    mail <name>    Mail to player 'name'.\n" +
            "    from           List all mail headers.\n\n");

   add_prop(ROOM_I_INSIDE, 1);
   add_exit("shop","west");
}

init()
{
   object reader;
   
   ::init();
   reader=clone_object(MAILREADER);
   if (!reader) {
      write("No mailreader is available at this time.\n");
      return;
   }
   reader->move(this_player());
}

leave_inv(object ob,mixed to)
{
   object reader;
   
   ::leave_inv(ob,to);
   reader=present("mailread",ob);
   if (reader)
      reader->remove_object();
}

query_mail(int silent)
{
   string new, sp;
    int mail;

    mail = MAILCHECKER->query_mail();
    if (!mail)
	return 0;
   if (silent)
      return 1;
   new="read";
   sp="    ";
   if (mail>1) {
      new=" NEW";
      sp="";
   }
   write("\n");
   write(".---------------------------------------------------------.\n");
   write("| There is "+new+" mail for you in the Keepers' Post Office. |\n");
   write("`---------------------------------------------------------'\n");
   return 1;
}
