/*
 * The village Solace
 *
 * By Rastlin
 */
#include "local.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include QUESTH

#define QQNAME "small1"

inherit SOLOUTROOM;

/*prototype*/
static void reward_player(object ob);
void owner_arrives(object ob);
 
object gCitizen;

reset_solace_room()
{
    if (!gCitizen)
        (gCitizen = clone_object(NPC + "citizen"))->move(TO);
}

create_solace_room()
{
    set_place(PARK);

    set_long_desc("This is the western part of the Solace Park. Small " +
		  "gazebos and picnic tables and benches line the edges " +
            "of the road. There is one tree here that doesn't look " +
		  "like a Vallenwood tree at all. Looking up, you see the " +
		  "dense canopy of " +
		  "vallenwood branches and a bridge-walk. The road goes " +
		  "back east to the eastern part the park.");

    add_item(({"tree", "trees"}),
             "Among the grand trees you recognize a smaller apple tree.\n");
    add_item("apple tree",
             "There are some very nice looking apples hanging there.\n");
    add_item(({"apple", "apples"}),
             "The apples are red and look just ready to be picked.\n");

    add_exit(TDIR + "park1", "east");

    reset_solace_room();
}

void
init()
{
    ADA("pick");
    ADA("shake");
    ADA("throw");
    ::init();
}

int
allow_pick(object ob)
{
    string nm = QUEST_DIR + QQNAME;
    nm->load_me();
    return (QUEST_MASTER->query_quest_number(SMALLADV, ob) < 1 &&
            REALAGE(ob) > nm->age());
}

int
pick(string str)
{
   object ob, ob2, player = TP;
   
   NF("Pick what?\n");
   if (str != "apple")
     return 0;
   
   if (!(ob2 = present("ladder", TO)))
     {
         player->catch_msg("You can't reach the apples, nor climb the trees.\n")
;
         return 1;
     }
   
   set_alarm(3.0, 0.0, &owner_arrives(ob2));
   
   if (!allow_pick(player))
     {
         player->catch_msg("The apples move away from you as if by magic.\n");
         return 1;
     }
   
   player->catch_msg("You climb the ladder and pick an apple.\n");
   tell_room(TO,QCTNAME(player) + " picks an apple.\n", ({ player }));
   seteuid(getuid(TO));
   ob = clone_object(OBJ + "apple");
   if (ob->move(player))
     {
         player->catch_msg("You drop the apple on the ground though.\n");
         tell_room(TO, QCTNAME(player) + " drops the apple on the ground.\n",({ 
player }));
         ob->move(E(player));
     }
   
   reward_player(player);
   
   return 1;
}

void
owner_arrives(object ob) 
{ 
    ob->owner_arrives(); 
}

static void
reward_player(object ob)
{
   ob->add_exp(900, 0);
   QUEST_MASTER->inc_quest_number(SMALLADV, ob);
   ob->catch_msg("You feel you have gained some experience.\n");
   ob->save_me();
   seteuid(getuid(TO));

   K_QUEST_LOG("quest", "Small 1", ob, 900);
}

int
shake(string str)
{
   NF("Shake what?\n");
   if ((str != "tree") && (str != "apple tree"))
      return 0;
   
   write("You shake the apple tree but the apples stay where they are.\n");
   say(QCTNAME(TP) + " shakes the apple tree but no apples fall.\n");
   
   return 1;
}

int
throw(string str)
{
   object ob;
   string *str2;
   
   NF("Throw what?\n");
   if (!str)
     return 0;
   
   str2 = explode(str, " ");
   str = str2[0];
   
   NF("You don't have no " + str + ".\n");
   if (!(ob = present(str, TP)))
     return 0;
   
   NF("The " + str + " seams to be stuck with you.\n");
   if (ob->move(environment(TP)))
     return 0;
   
   write("You throw your " + str + " at the apples but you miss.\n");
   write("The " + str + " falls to the ground with a thud.\n");
   say(QCTNAME(TP) + " throws " + TP->query_possessive() + " " + str + 
       " trough the air. No hit.\n");
   
   return 1;
}





