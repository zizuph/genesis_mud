#pragma save_binary

inherit "/d/Rhovanion/lib/room";
inherit "/lib/guild_support";
inherit "/lib/skill_raise";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

static int *skill_arr;
static string *form;
static int *vals;

void set_up_skills();

void create_room()
{
  set_short("Training hall");
  set_long("This is the training hall of this large town"
	+" in Rhun, where the local people once came for"
	+" instruction in various arts.  Now, only a few are"
	+" left for you to advance your skill in, for a fee.  You"
	+" might also kneel down to meditate here.\n");

  add_prop(ROOM_I_INSIDE, 1);
  add_exit(RHUN_DIR+"ltown_ne/streets/st4","north",0);

  skill_arr=({SS_APPR_MON,SS_WEP_SWORD,SS_HUNTING});
  form=({"appraise monsters","use a sword","hunt for food"});
  vals=({35,30,35});

  set_up_skills();
}

void init()
{
  ::init();
  init_guild_support();
  init_skill_raise();
}

void set_up_skills()
{
  int i;
  for(i=0; i< sizeof(skill_arr); i ++)
    sk_add_train(skill_arr[i],form[i],0,0,vals[i]);
}

void leave_inv(object ob, object to)
{
  ::leave_inv(ob, to);
  gs_leave_inv(ob, to);
}