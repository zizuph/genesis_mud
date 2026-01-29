inherit "/std/room.c";

#include <macros.h>
#include <stdproperties.h>

#include "defs.h"
#include "ritual.h"

void create_room()
{
 set_short("A dirty hole in the ground");
 set_long(BS(
   "This dirty hole in the ground is a known hangout for Tricksters. "+
   "A sign is the lone decoration on the west wall, "+
   "while the east wall is a solid wall of dirt.  Water drips from the "+
   "ceiling into a puddle on the floor. South leads deeper into the "+
   "hole and up is the way out. In the middle of the room you see "+
   "bloody altar. A notice hangs from the east wall.\n"));

 add_prop(ROOM_M_NO_ATTACK,"The unholy presence in the air stops you.\n");

 add_item("hole","The hole in the ground that is this room is the "+
   "headquarters for the Trickster guild.\n");
 add_item("sign","Read the sign, if you are able.  Otherwise, get "+
   "someone to read it for you.\n");
 add_item(({"wall","walls"}),"The east wall is made of dirt as are all "+
   "the other walls, but it also has a sign affixed to it.\n");
 add_item("notice","It is quite readable.\n");
 add_item("altar","Dark and bloody altar , it is surely used for "+
   "dark and bloody rituals! You see an ancient dusty book chained "+
   "to altar.\n");

 add_exit(TRICKSTERS+"train","south","@@block");
 add_exit("/d/Earthsea/karg/island/rooms/forest/dend","up");

 clone_object(TRICKSTERS+"obj/book")->move(TO);
}

void init()
{
 ::init();
 add_action("do_read","read");
 add_action("fill","fill");
 add_action("discard","discard");
 add_action("view","view");
 add_action("contact","contact");
 add_action("initiate","initiate");
 add_action("abandon","abandon");
 add_action("appeal","appeal");

 init_ritual();
}

int do_read(string what)
{
 if(!what) return 0;
 if(what!="sign" && what!="notice") return 0;

 if(what=="sign")
  {
   write("<fill application> - apply for membership\n"+
         "<discard application/appeal> - \n"+
         "    remove your application/appeal\n"+
         "<view application/appeal> - \n"+
         "    review your application/appeal and Council\n"+
         "    responds to it\n"+
         "<contact council> - reply the Council responds on\n"+
         "                      application or appeal\n"+
         "<appeal banishment> - Appeal your banishment\n"+
         "<initiate ritual> - Start the dark joining ritual\n"+
         "<abandon faith> - Abandon your faith to Kina and leave\n");
   say(QCTNAME(TP)+" reads the sign.\n");
   return 1;
  }

 if(what=="notice")
  {
   if((SERVER)->query_apply_block())
     write("Turn back!\nTricksters are currently closed for new "+
       "members!\n");
   else
     write("Welcome to Tricksters!\nRead sign for instructions.\n");
   say(QCTNAME(TP)+" studies the notice.\n");
   return 1;
  }
}

int fill(string what)
{
 NF("Fill what? An application maybe?\n");
 if(!what) return 0;
 if(what!="application" && what!="apply") return 0;

 (SERVER)->fill_apply();
 return 1;
}

int discard(string what)
{
 NF("Discard what? Your application or appeal?\n");
 if(!what) return 0;
 if(what!="application" && what!="apply" && what!="appeal") return 0;

 if(what=="application" || what=="apply")
   (SERVER)->discard_apply(TP->query_name());
 if(what=="appeal")
   (SERVER)->discard_appeal(TP->query_name());
 return 1;
}

int view(string what)
{
 NF("View what? Your application or appeal?\n");
 if(!what) return 0;
 if(what!="application" && what!="apply" && what!="appeal") return 0;

 if(what=="application" || what=="apply")
   MORE((SERVER)->view_apply(TP->query_name()),0,0);
 if(what=="appeal")
   MORE((SERVER)->view_appeal(TP->query_name()),0,0);

 return 1;
}

int contact(string what)
{
 NF("Contact what?? Council maybe?\n");
 if(!what) return 0;
 if(what!="council") return 0;

 (SERVER)->reply_council(TP->query_name());
 return 1;
}

void accept_trickster()
{
 object sh;

 sh = clone_object(TRICKSTERS_SHADOW);
 if(sh->add_trick_shadow(TP) != 1)
  {
   sh->remove_shadow();
   write("UHM! Can't join because of a bug! Mail Ged!!!\n");
   return;
  }

 (SERVER)->add_member(TP->query_name());
 (SERVER)->remove_apply(TP->query_name());
}

int initiate(string what)
{
 NF("Initiate what? Maybe rutial??\n");
 if(!what) return 0;
 if(what!="ritual") return 0;

 NF("But you are already member!!\n");
 if((SERVER)->query_member(TP->query_name())) return 0;
 
 NF("Fill an applciation form first!\n");
 if(!(SERVER)->query_applicant(TP->query_name())) return 0;

 NF("Your application still havn't been approved by Council.\n");
 if(!(SERVER)->query_approved(TP->query_name())) return 0;

 NF("You already member of another layman guild!\n");
 if(TP->query_guild_name_lay()) return 0;

 NF("There is ritual going on. You will have to wait.\n");
 if(ritual) return 0;

 start_ritual(TP);

 return 1;
}

int block()
{
 if((SERVER)->query_member(TP->query_name())) return 0;

 write("Some kind of force field you cannot penetrate stops you.\n");
 return 1;
}

int abandon(string what)
{
 NF("Abandon what? Your faith in Kina?\n");
 if(!what) return 0;
 if(what!="faith") return 0;

 TP->kick_out_trickster();
 leave_guild(TP);
 return 1;
}

int appeal(string what)
{
 NF("Appeal what? your banishment?\n");
 if(!what) return 0;
 if(what!="banishment" && what!="ban") return 0;

 (SERVER)->appeal_banish(TP->query_name());
 return 1;
}
