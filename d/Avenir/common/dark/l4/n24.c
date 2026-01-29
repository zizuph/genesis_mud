// Iron pole which is required to gain entrance to the worm lair
// is cloned here.
// By Boriska

inherit "/std/room";

#include "/d/Avenir/common/dark/dark.h"

static int pole_is_here = 0;

void
reset_room()
{
  pole_is_here = 1;
}
  
void
create_room()
{
  set_short("small dirty tunnel");
  
  set_long(
    "You are in a tiny passage, strewn with cobwebs and choked with dust,\n" +
    "which leads off to the northwest and to the southeast. The ceiling is\n"+
    "in better shape here than in the rest of the passage but still\n" +
    "requiring some support shafts.\n");

  AI(({"walls", "wall", "floor", "tunnel", "passage", 
	 "passageway"}), "Very uninteresting stone.\n");
  
  AI("dust", "It is thick on the floor. Your footsteps stir " +
     "it up and cloud the air.\n");
  
  AI(({"cobweb","cobwebs"}),"The cobwebs hang down in your " +
     "face, tickling your skin.\n");
  
  AI("shafts", 
     "They keep the ceiling from crashing." + "@@check_pole@@");
  

  AI("shaft", "@@shaft_desc@@");
  AI("pole", "@@pole_desc@@");
  
  AE(L4+"n23","southeast",0,DIRT);
  AE(L4+"n25","northwest",0,DIRT);
  
  add_prop(ROOM_I_LIGHT,0);
  IN;
  reset_room();
}

string
check_pole()
{
  return pole_is_here ?
   " One of the shafts, appearing to be made from iron seems to be loose.\n" :
  "\n";
}

string
shaft_desc()
{
  return pole_is_here ?
    "It is an iron pole inserted between two large rocks.\n" :
  "You find no shaft.\n";
}

string
pole_desc()
{
  return pole_is_here ?
    "It is an iron pole inserted between two large rocks.\n" :
  "You find no pole.\n";
}

void
init()
{
  ::init();
  add_action("do_pick", "pick");
  add_action("do_pick", "get");
}

int
do_pick(string str)
{
  object tp = this_player();
  object pole;
  
  if (!str || str != "pole" || !pole_is_here)
    return 0;

  tp->catch_msg(
	  "As you remove the pole the ceiling trembles dangerously...\n");
  say ("As " + QCTNAME(tp) +
       " removes the iron pole supporting the ceiling\n" +
       "the loose rocks start trembling dangerously...\n");
  
  set_alarm(5.0, 0.0, "drop_rock", tp);
  
  pole = clone_object(OBJ + "i_pole");
  if (pole->move(tp))
    pole->move(this_object());
  pole_is_here = 0;
  return 1;
}

void
drop_rock(object tp)
{
  tp->catch_msg ("One of the rocks falls down hurting your head!\n");
  say ("One of the rocks falls down, hurting " + QCTNAME(tp) + "'s head!\n");
}
