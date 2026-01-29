inherit "/d/Shire/std/room";

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/bree/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>


/* Prototype */
void reset_shire_room();

void make_npcs();

object hob1, hob2, ranger, man, dwarf, spoon;

void
create_shire_room()
{
   set_short("The common room of the Prancing Pony");
   set_long(
      "This is the fabled common room of Bree's Prancing Pony, "+
      "the most famous inn in the known world, according to Bree-"+
      "folk, that is. A great fire burns in the fireplace, surrounded by many scattered "+
      "tables, and even a few dark corners, nooks and crannies, for "+
      "more private conversation. The small windows on the wall are "+
      "always closed at night, for even in the summer the Shire gets "+
      "a bit drafty for a hobbit's taste. Usually there are several "+
      "people, elves, men, dwarves or hobbits discussing recent happenings "+
      "from diverse areas like Staddle, Michel Delving, Hobbiton, and sometimes "+
      "even Edoras is discussed. But this is a curious bunch, so "+
      "don't expect your conversation to be private!\n");
   
   
   add_item(({"nook","nooks","cranny","crannies","corner","corners"}),"T"+
      "here are several dark places in this room, and by the flickering light "+
      "of the fire, you cannot tell if any or all are occupied. They would "+
      "be excellent places for semi-private conversation, though "+
      "since there are even more ears listening here than "+
      "tongues wagging.\n");
   
   add_item(({"fire","fireplace","great fire","light"}),"The only source of "+
      "light in this room is a great fire on the northern wall. It is piled "+
      "high, and is burning continously, day or night. Its warmth makes you "+
      "want to sit down and lean back in a chair and relax, for surely you have "+
      "had a long journey. The fireplace is black and looks as if it has "+
      "always been so.\n");
   
   add_item(({"tables","table","chairs","chair"}), "Throughout "+
      "the room, tables and chairs are scattered without rhyme or reason. "+
      "It is likely Barliman is kept so busy by orders for more drink that he "+
      "cannot spare the time to order the room. In any case, the tables "+
      "are covered with a white cloth, and you do not detect any stains "+
      "in this dim light. The chairs are made of solid spruce-wood, and are well "+
      "worn, but in good condition.\n");
   
   add_item(({"shutter","shutters","window","windows","wall","northern wall"}),
      "The windows on the wall are covered with shutters in the day-time "+
      "to maintain a dim ambient light, which is most agreeable for the "+
      "gossip that all who spend any time in this room engage in. The "+
      "walls around here are illuminated briefly by the flickering firelight, "+
      "and the northern wall, where the fire is, is clearly lit.\n");
   
   add_prop(ROOM_I_INSIDE,1);
   
   add_exit(OLD_BREE_DIR + "inn","east",0);
   enable_reset();
   reset_shire_room();
   
}

void reset_shire_room()
{
   make_npcs();
}

void
make_npcs()
{
   if(!hob1)
      {
      hob1 = clone_object(NPC_DIR + "ponyhobbit");
      hob1->move(TO);
      tell_room(TO,capitalize(LANG_ADDART(hob1->query_nonmet_name()))+
         " comes strolling into the room.\n");
      hob1->command("sit in chair");
   }
   if(!hob2)
      {
      hob2 = clone_object(NPC_DIR + "ponyhobbit2");
      hob2->move(TO);
      tell_room(TO,capitalize(LANG_ADDART(hob1->query_nonmet_name()))+
         " prances into the room.\n");
      hob2->command("sit in chair");
   }
   
   if(!ranger)
      {
      ranger = clone_object("/d/Gondor/common/guild/north/npc/wolfeater");
      ranger->arm_me(0);
      ranger->move(TO);
      tell_room(TO,capitalize(LANG_ADDART(ranger->query_nonmet_name()))+
         " strides in warily..\n");
      ranger->command("sit in shadows");
   }
   
   if(!man)
      {
      man = clone_object(NPC_DIR + "ferny");
      man->move(TO);
      tell_room(TO,capitalize(LANG_ADDART(man->query_nonmet_name()))+
         " paces in nervously, glancing about.\n");
      man->command("lean against wall");
   }
   
   if(!dwarf)
      {
      dwarf = clone_object(NPC_DIR + "dwarf");
      dwarf->move(TO);
      tell_room(TO,capitalize(LANG_ADDART(dwarf->query_nonmet_name()))+
         " strolls in confidently, tugging his beard thoughtfully.\n");
      dwarf->command("sit by fire");
   }


}


init()
{
   add_action("do_sit","sit");
   add_action("do_stoke","stoke");
   add_action("do_stand","stand");
   add_action("do_stand","rise");
   add_action("do_lean","lean");
   add_action("do_climb","climb");
   ::init();
}


int do_climb(string str)
{
  if(!str)
  {
    NF("Climb where?");
  }
  switch(str)
  {
    if(!TP->query_prop("_standing"))
    {
      write("You are already standing on the ground.\n");
      return 1;
    }
    case "down": case "off table": case "down off table":
    case "down off the table":
      write("You climb down off the table.\n");
      SAY(" climbs down from the table.");
      TP->remove_prop("_standing");
      TP->remove_prop(LIVE_S_EXTRA_SHORT);
      break;
    case "up": case "walls": case "wall": case "up the wall":
      write("You try to climb, but find no purchase to do so.\n");
      SAY(" paws uselessly at the air trying to climb impossible "+
         "things.");
      break;
    case "table": case "on table": case "up table": case "up on table":
    case "the table": case "up on the table":
      write("Perhaps you wish to stand on the table?\n");
      break;
    default:
      write("Perhaps you wish to stand on the table or climb down "+
        "from it?\n");
      break;
  }
  return 1;
}


int do_stoke(string str)
{
  if(!str) { NF("What do you want to stoke?"); }
/*
  if(TP->query_prop(LIVE_S_EXTRA_SHORT) != "%w 'by the fire'")
  {
    write("And how do you expect to do that from here?\n");
    return 1;
  }
*/
  write("You stoke the fire, sending embers flying as the fire burns "+
     "brighter.\n");
  SAY(" stokes the fire sending sparks flying as the fire erupts "+
     "briefly.");
  return 1;
}


int do_sit(string str)
{
   if (!str) { NF("Sit where?\n"); return 0; }
   if(TP->query_prop("_sitting"))
   {
      write("But you are already sitting somewhere!\n");
      return 1;
   }
  if(TP->query_prop("_leaning") || TP->query_prop("_standing"))
  {
    write("Perhaps you should stand up first?\n");
    return 1;
  }
   switch(str) 
   {
    case "down": case "in chair": case "chair": case "in the chair":
    case "in a chair": case "on chair": case "on a chair":
      write("You sit down in one of the chairs by the table.\n");
      SAY(" pulls up a chair and sits by the table.");
      TP->add_prop("_sitting",1);
      TP->add_prop(LIVE_S_EXTRA_SHORT," is sitting in a chair");
      break;
    case "by fire": case "by the fire": case "the fire":
      write("You pull up a chair and sit by the fire.\n");
      SAY(" pulls up a chair and sits by the fire.");
      TP->add_prop("_sitting",1);
      TP->add_prop(LIVE_S_EXTRA_SHORT," is sitting by the fire");
      break;
    case "in shadow": case "in the shadow": case "in shadows":
    case "in the shadows":
      write("You hunker down into a chair obscured by the shadows.\n");
      SAY(" silently sinks into a chair hidden in the shadows.");
      TP->add_prop("_sitting",1);
      TP->add_prop(LIVE_S_EXTRA_SHORT," is sitting in the shadows");
      break;
    default: 
      write("Perhaps you'd like to sit in the shadows, in a chair, "+
        "or by the fire?\n");
      break;
   }
   return 1;
}


int do_lean(string str)
{
   if (!str) { NF("Lean where?\n"); return 0; }
  if(TP->query_prop("_leaning"))
  {
     write("You are already leaning against a wall!\n");
     return 1;
   }
  if(TP->query_prop("_sitting") || TP->query_prop("_standing"))
  {
    write("Perhaps you should stand up first?\n");
    return 1;
  }
   switch(str) 
   {
    case "wall": case "the wall": case "against the wall":
    case "against wall": case "a wall": case "against a wall":
      write("You lean against a wall near the table.\n");
      SAY(" saunters over to the table and leans against a wall.");
      TP->add_prop("_leaning",1);
      TP->add_prop(LIVE_S_EXTRA_SHORT," is leaning against a wall");
      break;
    case "by fire": case "by the fire": case "the fire":
      write("You lean against a wall by the fire.\n");
      SAY(" strolls over to the fire and leans against the wall.");
      TP->add_prop("_leaning",1);
      TP->add_prop(LIVE_S_EXTRA_SHORT," is leaning against the wall "+
        "by the fire");
      break;
    case "in shadow": case "in the shadow": case "in shadows":
    case "in the shadows":
      write("You lean against a wall in the shadows.\n");
      SAY(" leans against a wall obscured by the shadows.");
      TP->add_prop("_leaning",1);
      TP->add_prop(LIVE_S_EXTRA_SHORT," is leaning against a wall "+
        "in the shadows");
      break;
    default:
      write("Perhaps you'd like to lean by the fire, against the "+
        "wall, or in the shadows?\n");
      break;
   }
   return 1;
}


int do_stand(string str)
{
  if(!str)
  {
    NF("Stand where?");
  }
  if(str == "on table" || str == "table" || str == "on the table")
  {
    if(TP->query_prop("_standing"))
    {
      write("You are already standing on the table.\n");
      return 1;
    }
    if(TP->query_prop("_sitting") || TP->query_prop("_leaning"))
    {
      write("Perhaps you should stand up first?\n");
      return 1;
    }
    write("You clamber up onto the table and stand on it.\n");
    SAY(" climbs up onto the table and looks around the room.");
    TP->add_prop("_standing",1);
    TP->add_prop(LIVE_S_EXTRA_SHORT," is standing on the table");
    return 1;
  }
   
   if (str != "up") {
      NF(CAP(query_verb())+" what? Up?\n");
      return 0;
   }
  if(TP->query_prop("_sitting"))
  {
    write("You stand up and leave your chair behind.\n");
    say(QCTNAME(TP)+" suddenly stands up.\n",TP);
    TP->remove_prop("_sitting");
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
    return 1;
  }
  if(TP->query_prop("_leaning"))
  {
    write("You stand away from the wall.\n");
    SAY(" leaves "+HIS_HER(TP)+" place by the wall.");
    TP->remove_prop("_leaning");
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
    return 1;
  } 
  if(!TP->query_prop("_sitting") && !TP->query_prop("_leaning") &&
    !TP->query_prop("_standing"))
  {
    write("You are already standing! Perhaps you'd like to sit down "+
      "or lean against a wall to rest for a bit?\n");
    return 1;
  }
}

void leave_inv(object ob, object to)
{
   ::leave_inv(ob, to);
   
   if(!objectp(to) || !objectp(ob))
      return;
  if(TP->query_prop("_sitting"))
  {
    write("You rise from your chair before leaving.\n");
    say(QCTNAME(TP) + " moves from "+HIS_HER(TP)+" position.\n");
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
    TP->remove_prop("_sitting");
  }
  if(TP->query_prop("_standing"))
  {
    write("You climb down from the table before leaving.\n");
    say(QCTNAME(TP) + " climbs down from "+HIS_HER(TP)+" position.\n");
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
    TP->remove_prop("_standing");
  }
  if(TP->query_prop("_leaning"))
  {
    write("You push away from the wall before leaving.\n");
    say(QCTNAME(TP) + " pushes away from "+HIS_HER(TP)+" position.\n");
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
    TP->remove_prop("_leaning");
  }
}
