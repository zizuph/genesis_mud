
inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "/d/Shire/greenfields/camp/tent.h"
#include <macros.h>
#include <language.h>


add_stuff() 
{
  object mage;
  if(!find_living("mauhur"))
  {
    mage = clone_object(GREEN_DIR + "npc/mage");
    mage->arm_me();
    mage->move(TO);
    tell_room(TO,QCTNAME(mage)+" steps out of "+
      "the shadows.\n");
  }
}


reset_room()
{
  add_stuff();
}

void
create_room()
{
   set_short("Inside a black tent");
  set_long("This black tent is empty of almost all decoration.  A "+
    "bed dominates the north wall of the tent, with a strange tapestry "+
    "hanging above it.  A small table stands along the eastern wall "+
    "of the tent, and a lamp floats above it.  Near the table is a "+
    "small, black stool pushed off to the side.  The rest of the tent is "+
    "bare of furnishings or adornment.\n");

  add_item(({"tapestry","strange tapestry"}),"@@exa_tapestry");
  remove_item("ground");
  add_item(({"ground","floor","dirt","sand"}),
    "The floor of this tent is liberally covered with a fine, "+
    "black sand.\n");
  add_item(({"table","small table","stool","small stool"}),
    "The table is bare, constructed of some unknown wood with a "+
    "lustreless black appearance.  The stool is similiar crafted and "+
    "unadorned.\n");
  add_item(({"lamp","floating lamp"}),
    "This lamp gives off a steady, but dim amount of light "+ 
    "while floating, with no apparent supports, over the table.\n");
   MBED;
   TENT;
 add_item(({"camp","outside"}), "The camp is outside, but you cannot "+
   "see it from in here.\n");
     add_prop(ROOM_I_INSIDE,1);
     add_prop(ROOM_I_LIGHT,5);
   
     add_exit(GREEN_DIR + "camp/camp15","out",0,1);

  enable_reset();
  set_alarm(1.5,0.0,"add_stuff");
}


string exa_tapestry()
{
  say(QCTNAME(TP)+" stares intently at the tapestry for a moment, "+
    "then looks away with a slightly blank look.\n");
  TP->set_stat_extra(SS_INT,TP->query_stat_extra(SS_INT)-10);
  return "The evil red eye of the Dark Lord stares back at you from "+
    "the tapestry.  You feel an intense pain as it seems to bore "+
    "right through your mind.  You tear your eyes away, feeling "+
    "somewhat weaker than before.\n";
}
