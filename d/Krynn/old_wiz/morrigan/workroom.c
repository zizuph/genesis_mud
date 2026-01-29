inherit "/std/room.c";

#include "/d/Shire/common/defs.h"

string          Owner = creator(this_object());
object          me = find_living(Owner);

void
create_room()
{
   set_short("Entryway to Tower");
   set_long("You are in a dim room. A sense of unease permeates your " +
      "soul, and the shadows and eerie sounds that echo in the tower " +
      "do not serve to calm you at all. A staircase spirals up into the " +
      "upper levels of the tower, but it is too dark to make out any " +
      "details. A portal shimmers colourfully on one wall.\n");
   
   add_item("portal", "This portal leads to the room on Krynn where " +
      "wizards sometimes come together to discuss the world.\n");
   add_item(({"eye", "eyes", "disembodied eyes", "disembodied eye"}),
      "Two white eyes adorn the wall, and watch you motionlessly.");
   
   add_exit("/d/Krynn/morrigan/tower/room/path", "out");
   add_exit("/d/Krynn/workroom", "portal", "@@check_if_wiz@@");
   add_exit("/d/Krynn/morrigan/tower/room/stair1", "up");
}

void
init()
{
   ::init();
   
   if (TP->query_real_name() == Owner && !present("_reader_", TP)) {
      setuid();
      seteuid(getuid());
      clone_object("/secure/mail_reader")->move(TP, 1);
   }
}

int
check_if_wiz()
   {
   if (TP->query_wiz_level()) {
      return 0;
   }
   write("Two disembodied eyes detach themselves from the wall, and " +
      "float towards you in warning as you approach the exit.\n" +
      "The Guardian thunders: The Master of the Tower has decreed that "+
      "you may not pass.\n");
   return 1;
}

void
enter_inv(object ob, object from)
{
   
   ::enter_inv(ob, from);
   if (!living(ob))
      return;
   if (ob->query_real_name() == Owner) {
      write("The Tower itself welcomes you, recognizing you as the Master.\n");
      return;
   }
   say("Two disembodied eyes emerge from the darkness only centimeters from " +
      QTNAME(ob) + "'s face, who pales visably. Slowly, almost reluctantly, " +
      "the eyes float back, and become motionless on the wall again.\n");
   write("You catch your breath in horror as a pair of disembodied eyes appear "+
      "from the darkness in front of your face. They regard you eerily for " +
      "what seems like an eternity before slowly floating away.\n");
   
   if (!present(Owner, TO) && me)
      me->catch_msg("\nThe Guardians alert you to an intruder in the Tower.\n\n");
}

query_prevent_snoop()
{
   return 1;
   
}
