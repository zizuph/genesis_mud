inherit "/std/room";
#include "/d/Cirath/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#define HESHE (this_player()->query_pronoun())
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
   bring_room_mob("guard", TZ_MINTHOR+"npc/guard",1,1);
}

create_room()
 {
  set_short("Library");
  set_long("This appears to be the famed library of the Minthor's. "
	+"It is unusual to see such a thing considering that literacy "
	+"has been mostly banned by Kalak, but it is well known that "
	+"loyalty and wealth will get you almost anything.  The tomes "
	+"in this library are extremely old and look to be mostly "
	+"used as a status symbol as opposed to for learning or actual "
	+"use.\n");
  add_item("wall","The wall is off to your side.\n");
  add_item("hallway","It leads south and east directions.\n");
  add_item("ceiling","It is above you.\n");
  add_item(({"house","mansion"}),"You are inside of it.\n");
  add_item(({"book","books","tome","tomes"}),"The books here look to "
	+"be extremely old and are well worn and covered in dust.  "
	+"Unfortunately, though, all of the books look to be in a "
	+"strange language that you are unable to read.\n");
  add_cmd_item("book","read","@@read");
  ADD_SUN_ITEM
  ADD_ZIG_ITEM
  INSIDE

  add_exit(TZ_MINTHOR + "mh24","north",0);
  add_exit(TZ_MINTHOR + "mh26","east",0);
  set_alarm(1.1,0.0,"reset_room");
}

read()
{
        write("You pluck one of the books from the shelf and attempt "
	+"to read it, but the language is unfamiliar to you.\n");
        say(QCTNAME(TP) + " gets a book from the shelf and opens it,  "
        +"apparently trying to read it.  After only a few moments, "
   + HESHE +" shrugs and puts it back.\n");
        return 1;
        return 0;
}

