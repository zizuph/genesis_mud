// file name:		~Avenir/common/dark/obj/smash_tool.c
// creator(s):		Denis
// revision history:
// 			Ilyian, May 13 1995: I added some props to the hammer
//			to make it a magical item.
//
//			Jan 96: Made some changes to allow
//				impquest reset-ability.
//					-=Denis
// purpose:		Kill imps for ghost quest item.
// note:		Quest starts in l3/altar.c
//       		This file is cloned by obj/rock.c
//			For more info see QUESTS/impquest.doc.
// bug(s):
// to-do:

# include "../l3/l3_defs.h"
# include "/d/Avenir/common/common.h"
inherit "/std/object";

create_object()
{
    set_name("hammer");
    add_adj("sacrificial");
    add_adj("white");
    set_long(
"The solid hammer has a long, oak haft and a square head made of a "+
"strange stone. The artifact is unwieldly, and seem like it "+
"would have little use as a weapon, but nonetheless is quite "+
"heavy and would be good at smashing things.\n");

  add_prop(MAGIC_AM_MAGIC,({6,"enchantment"}));
  add_prop(OBJ_M_NO_BUY, "It is sacred and cannot be sold.\n");

  add_prop(MAGIC_AM_ID_INFO,({
     "The " + short() + " seems to be enchanted.\n",1,
     "It is used in a ceremony.\n",10,
     "The " + short() + " was hidden ages ago for safety.\n",30,
     "It is used to destroy statues.\n",50}));

  add_prop(OBJ_S_WIZINFO,"This is the hammer that is used to "+
     "smash the statues in the impquest.\n");

    add_prop(OBJ_I_VOLUME,2000);
    add_prop(OBJ_I_WEIGHT,20000);
    add_prop(IS_STATUE_SMASHER, 1);
}

void self_destruct()
{
    environment(TO)->catch_msg(
"\nThe sacrificial hammer suddenly turns to black and crumbles to dust.\n");
    remove_object();
}

