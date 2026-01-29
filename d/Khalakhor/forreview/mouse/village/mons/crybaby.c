/* humanoid npc coded by Elizabeth Cook/Mouse, January 1997 */

inherit "/std/monster";
#include <stdproperties.h>
#include <ss_types.h>
#include <const.h>
#include <alignment.h>
inherit "/std/act/chat";
inherit "/std/act/action";
#include "../../mouse.h" 

void create_monster()  {
     set_name("boy");
     set_living_name("mouse:crybaby");
     set_race_name("human");
     add_adj(({"crying","little"}));
     set_short("crying little boy");
     set_long("A sobbing child with a tear-stained face and swollen eyes. "+
          "He has been crying so hard, he is breathing in deep, ragged, "+
          "wracking breaths. He clutches a stuffed bear in his arms.\n");
     set_stats(({10,10,15,15,10,10}));
     set_skill(SS_WEP_CLUB,10);
     set_skill(SS_AWARENESS,10);
     set_skill(SS_DEFENCE, 10);
     set_skill(SS_PARRY, 10);
     set_gender(G_MALE);
     set_alignment(ALIGN_NEUTRAL);
     add_prop(NPC_I_NO_LOOKS,1);
     add_prop(NPC_I_NO_RUN_AWAY,1);
     add_prop(LIVE_I_NEVERKNOWN, 1);
     add_prop(CONT_I_WEIGHT, 35000);
     add_prop(CONT_I_HEIGHT, 100);

     set_act_time(5);
     add_act("emote lets out a long, howling wail.\n");
     add_act("emote sobs inconsolably.\n");
     add_act("emote sniffs pitifully and wipes his nose on his sleeve.\n");

     set_chat_time(5);
     add_chat("My puppy is lost! She's gone forever!\n");
     add_chat("My pretty brown doggy is missing, have you seen her?\n");
     add_chat("I miss my pretty puppy! There will never be another doggy "+
          "in the world like her.\n");
     
     add_weapon(ROOT+"village/items/stuffed.c"); 
}    
