/*
 * PIRATE's SCHOOL
 * This was originally by Charon
 * Re-touched slightly by Alaron
 */

inherit "/lib/guild_support"; 
inherit "/lib/skill_raise";
inherit "/std/room";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <money.h>
#include "defs.h"

#define NUM             sizeof(query_money_types(-1))
#define CLOSED          0       /* 1 = closed,   0 = open.  */

int closed;
object meditate;

void set_up_skills();

void
create_room()
{ 
   
   set_short("Pirates' School\n");
   set_long(
      "   Torches line the wall of this void in the rock. "+
      "On one wall there are crude drawings of pirates "+
      "raiding ships and stealing treasures. On another "+
      "wall is a half-backwards, half-attempt at the "+
      "alphabet. Through the center of the room are "+
      "numerous chairs in disarray.\n\n");
   add_item(({"wall","walls"}),
	    "The walls are solid rock and somewhat smooth. "+
	    "One wall has many crude drawings portraying pirate life. "+
	    "Another wall has a poor depiction of most of the "+
	    "alphabet.\n");
   add_item(({"drawing","drawings"}),
	    "They depict pirate life.\n");
   add_item("alphabet",
	    "You are pretty certain that it is the alphabet that you know, "+
	    "although you could be mistaken.\n");
   add_item(({"chairs","chair"}),
	    "The chairs are scattered randomly around "+
	    "the room; however, their focal point may have "+
	    "once been the wall with the drawings.\n");

   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_TYPE, ROOM_NORMAL);
   
   add_exit(THIS_DIR+"storage","up",0);
   
   create_skill_raise();
   set_up_skills();
   
}

void
leave_inv(object ob, mixed to)
{
   ::leave_inv(ob, to);
   gs_leave_inv(ob, to);
   
}


void
init()
{
   ::init();
   init_skill_raise();
   init_guild_support();
   
}

void
set_up_skills()
{
   string me, ot;
   
   me = "hide"; me = ot;
   sk_add_train(SS_HIDE, ({ me, ot }),     0, 0, 30);
   me = "sneak around"; ot = me;
   sk_add_train(SS_SNEAK, ({ me, ot }),     0, 0, 30);
   me = "swim"; ot = me;
   sk_add_train(SS_SWIM, ({ me, ot }),     0, 0, 50);
   me = "trade with merchants for a profit"; ot = me;
   sk_add_train(SS_TRADING, ({ me, ot }),     0, 0, 30);
   me = "pick pockets"; ot = me;
   sk_add_train(SS_APPR_VAL, ({ me, ot }),     0, 0, 50);
   me = "find your way around"; ot = me;
   sk_add_train(SS_LOC_SENSE, ({ me, ot }),     0, 0, 50);
   me = "open locks without a key"; ot = me;
   sk_add_train(SS_OPEN_LOCK, ({ me, ot }),    0, 0, 20);
   me = "speak the languages of the realm"; ot = me;
   sk_add_train(SS_LANGUAGE, ({ me, ot }),     0, 0, 50);
}

void
gs_hook_start_meditate()
{
  write("You plop down in one of the rickety chairs "+
	"and begin to meditate.\n");
  tell_room(ENV(TP),QCTNAME(TP)+" plops down "+
	    "in a chair and begins to meditate.\n", TP);
}

void
gs_hook_rise()
{
  write("You stand up from the old chair "+
	"feeling refreshed.\n");
  tell_room(ENV(TP),QCTNAME(TP)+" stands up "+
	    "from a chair seeming very refreshed.\n", TP);
}

