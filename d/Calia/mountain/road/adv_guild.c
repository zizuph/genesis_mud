
/* 
   Adventurers guild, 

   Coded by Maniac, based on Malcontent's

   History: 
           27/3/02  updated total skills trained for new rule     Maniac
           18/11/99 updated skills to new max levels              Maniac
           22/4/96  swim added                                    Maniac 
           3/12/95  non-taxed skills moved in from Calian guild   Maniac
           24/5/95          Created                               Maniac
*/


#pragma save_binary

inherit "/lib/guild_support"; 
inherit "/lib/skill_raise";
inherit "/std/room";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <money.h>
#include "road.h"

void set_up_skills();

void
create_room()
{
    set_short("Adventurer's Guild of Calia");
    set_long("You have entered a large training hall. " +
         "Welcome to the Adventurer's Guild of Calia. " +
         "Brave adventurers come from many lands to train " +
         "various skills here. " +
         "You may <meditate> here to find your strengths and " +
         "weaknesses, and you may <learn> or <improve> your skills " +
         "here.\n");

   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_TYPE, ROOM_NORMAL);
   
   create_guild_support();
   create_skill_raise();
   set_up_skills();

   add_exit(ROAD + "road19", "southeast");
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

    me = "fight unarmed"; ot = me;
    sk_add_train(SS_UNARM_COMBAT, ({ me, ot }), 0, 0, 30);
    me = "use a knife"; ot = me;
    sk_add_train(SS_WEP_KNIFE, ({ me, ot }), 0, 0, 20);
    me = "defend yourself"; ot = "use defence skill";
    sk_add_train(SS_DEFENCE, ({ me, ot }), 0, 0, 20); 
/*
    me = "swing a sword"; ot = me;
    sk_add_train(SS_WEP_SWORD, ({ me, ot }), 0, 0, 30);
    me = "use a polearm"; ot = me;
    sk_add_train(SS_WEP_POLEARM, ({ me, ot }), 0, 0, 30);
    me = "become more aware of the surroundings"; ot = me;
    sk_add_train(SS_AWARENESS, ({ me, ot }), 0, 0, 30);
    me = "perform magic and spells"; ot = me;
    sk_add_train(SS_SPELLCRAFT, ({ me, ot }), 0, 0, 20);
 */ 
    me = "make better trades and deals"; ot = me;
    sk_add_train(SS_TRADING, ({ me, ot }), 0, 0, 30);
    me = "handle animals"; ot = me;
    sk_add_train(SS_ANI_HANDL, ({ me, ot }), 0, 0, 30);
    me = "understand various languages"; ot = me;
    sk_add_train(SS_LANGUAGE, ({ me, ot }), 0, 0, 30);
    me = "climbing"; ot = me;
    sk_add_train(SS_CLIMB, ({ me, ot }), 0, 0, 30);
    me = "appraise different objects"; ot = me;
    sk_add_train(SS_APPR_OBJ, ({ me, ot }), 0, 0, 30);
    me = "swim"; ot = me;
    sk_add_train(SS_SWIM, ({me, ot}), 0, 0, 30); 
}
