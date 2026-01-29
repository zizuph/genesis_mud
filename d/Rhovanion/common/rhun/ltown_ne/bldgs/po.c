#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

void create_room()
{
  add_exit(RHUN_DIR+"ltown_ne/streets/st3","south",0);
  add_exit(RHUN_DIR+"ltown_ne/bldgs/rats","east",0);

  set_short("Rhun public post office");
  set_long("You are in the public post office of Rhun.  Commands:\n"+
	"   read            Read from the mailbox.\n" +
	"   mail <name>     Mail to player 'name'.\n" +
	"   from            List all headers.\n" +
	"East of here, the pigeons are sold.\n");

  add_prop(ROOM_I_INSIDE,1);
}

void init()
{
  ::init();
  clone_object("/secure/mail_reader")->move(TP,1);
}

void leave_inv(object ob, object to)
{
  object reader;
  ::leave_inv(ob, to);

  reader = present("mailread", ob);
  if (reader) reader->remove_object();
}