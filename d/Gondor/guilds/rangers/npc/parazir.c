/*
 * Herbalist in Gairent
 * Varian - August 2015
 * Code borrowed from Daisy in the Shire
 * /d/Shire/eastroad/npc/herbalist.c
 */

#pragma save_binary

#include "/d/Gondor/defs.h"
#include "../rangers.h"
#include <stdproperties.h>
#include <macros.h>
#include "/sys/ss_types.h"

inherit RANGERS_NPC + "random_npc_ranger.c";
inherit "/std/monster.c";

void

introduce_me();
arm_me();

int intro_id;

void
create_monster()
{
   
    set_name("parazir");
    add_adj(({"aged","grim-faced"}));
    set_title("the Librarian of the North Company");
    set_long("This ranger is well aged, having retired from many years " +
        "of patrolling the northern lands.\n");
    set_race_name("human");
    set_gender(0);
   
    add_act("smile all");
    add_act("emote carefully turns a page in the book he is studying.");
    add_act("emote squints as he examines the bookshelves.");
    add_act("emote appears to be momentarily lost in thought.");
    add_act("say Shh! This is a library!");
    add_act("rhail");
    add_act("emote stretches his back.");

    add_ask(({"book","books"}), VBFC_ME("ask_book"));
    add_ask(({"library"}), VBFC_ME("ask_library"));

    set_act_time(30);
   
    set_skill(SS_UNARM_COMBAT,100);
    set_skill(SS_DEFENCE, 100);

    set_stats(({ 120, 140, 120, 110, 110, 130}), 10);
   
    set_alignment(950);
   
   
    intro_id = 0;
    set_alarm(0.5,0.0,"arm_me");

}

arm_me()
{
   object cloak;
   object pin;

   FIXEUID;

   cloak = clone_object(RANGERS_OBJ + "grey_cloak");
   pin = clone_object(RANGERS_OBJ + "ron_brooch");

   cloak->move(TO); 
   pin->move(TO);  

   command("wear all");
}

void
add_introduced(string person)
{
   if (intro_id == 0) {
      intro_id = set_alarm(4.0,0.0, introduce_me);
   }
}

void
allow_introductions() 
{
   intro_id = 0;
}

void
introduce_me()
{
   command("introduce me");

   set_alarm(15.0, 0.0, allow_introductions);
}

string
ask_book()
{
    command("say These books are how we are able to share and communicate " +
        "our ideas and collective wisdom. I encourage you to share yours!");
    return "";
}
string
ask_library()
{
    command("say This library gives me a great feeling of peace and " +
        "contentment. I hope all rangers will learn to share their " +
        "wisdom here.");
    return "";
}

default_answer()
{
    command("say I don't know much about that!");
    return "";
}