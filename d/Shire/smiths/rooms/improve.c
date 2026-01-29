/*
     The improvement room for the smiths guild
     smiths improve and meditate here
*/

#pragma save_binary;

inherit "/d/Shire/room";
inherit "/lib/guild_support";
inherit "/lib/skill_raise";
inherit "/d/Shire/lib/training";

#include "smiths.h"
#include "/d/Shire/common/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

set_up_skills();

void
create_room() {
   seteuid(getuid());

   set_short("improvement room in the Smiths Guild");
   set_long("This small room, placed in a remote corner of the guild"+
      " building, is where members of the guild come to study their progress"+
      " and learn strange skills. The room has some nice furniture in the"+
      " style of hobbit-holes though the carpet on the floor is surely not"+
      " of hobbit-make.\n");

   add_item("carpet","It is a handwoven carpet made by humans.\n");

   if (!objectp("round blue crystal")) room_add_object
      (SMITHSDIR_OBJ+"crystal", 1);
/*
   if (!objectp("book")) room_add_object
      (SMITHSDIR_OBJ+"sm_book", 1);
*/
   create_guild_support();
   create_skill_raise();
   set_up_skills();

   add_prop(ROOM_I_INSIDE,1);
// safe rooms
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(OBJ_M_NO_ATTACK,1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1); 

   add_exit(SMITHSDIR_ROOMS + "rest_r", "northeast",0);
   add_exit(SMITHSDIR_ROOMS + "master_r","east",0);
   add_exit(SMITHSDIR_ROOMS + "library_entr", "west",0);
   add_exit(SMITHSDIR_ROOMS + "drop", "south", "@@check_player@@", 1);
   
   clone_object("/d/Shire/smiths/obj/sm_box")->move(this_object(), 1);
   clone_object("/d/Shire/smiths/obj/sm_rec_barrel")->move(this_object(), 1);

   /*
   if (!objectp("board")) room_add_object
      ("/d/Shire/smiths/obj/noteboard", 1);
   */
}

leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
   gs_leave_inv();
}

init() {
   ::init();
   init_guild_support();
    init_skill_raise();
   add_action("stare","stare");
   add_action("stare","study");
}

int
stare(string str) {
   if ((str=="into crystal") || (str=="at crystal")) {
      gs_meditate("test");
      return 1;
   }
   return 0;
}

int
gs_hook_start_meditate() {
   string race;

   write("You stare into the blue round crystal.\n");
   say(QCTNAME(TP)+" stares into the blue round crystal.\n");
   write("It seems that there are small images of ");

   race=TP->query_race_name();
   if (race=="hobbit")
      write ("hobbits making parties and celebrating");
   if (race=="dwarf")
      write ("wonderful and precious gems in deep mines");
   if (race=="elf")
      write ("wonderful forests and ancient trees with fresh green leaves");
   if (race=="human")
      write ("magnificent buildings and tall proud towers");
   if (race=="gnome")
      write ("complicated and fascinitating machines");
   write(" swirling inside the crystal.\n");
   write("You find yourself able to <estimate> your different\n" +
      "preferences and <set> them at your own desire.\n" +
      "Just <rise> when you are done meditating.\n");
   say(QCTNAME(TP)+" smiles happily.\n");

   return 1;
}

void
gs_hook_rise() {
   write("With some effort you stop staring into the crystal.\n");
   say(QCTNAME(TP)+" looks away from the crystal.\n");
}

set_up_skills() {

  /* Add skill that can be trained. Do not add all skills, and vary a bit */

  sk_add_train(SS_FORGING,train_text(SS_FORGING),"forging",80,60,
     SS_LAYMAN, 100);
  sk_add_train(SS_MENDING_ARMOURS,train_text(SS_MENDING_ARMOURS),
    "mending armours",50,60,SS_LAYMAN,100);
  sk_add_train(SS_MENDING_WEAPONS,train_text(SS_MENDING_WEAPONS),
    "mending weapons",50,60,SS_LAYMAN,100);

  sk_add_train(SS_APPR_OBJ,train_text(SS_APPR_OBJ),0,0,60);
  sk_add_train(SS_APPR_VAL,train_text(SS_APPR_VAL),0,0,60);

  sk_add_train(SS_TRADING,train_text(SS_TRADING),0,0,60);

  sk_add_train(SS_WEP_SWORD,train_text(SS_WEP_SWORD),"sword",0,50);
  sk_add_train(SS_WEP_AXE,train_text(SS_WEP_AXE),"axe",0,50);
  sk_add_train(SS_WEP_CLUB,train_text(SS_WEP_CLUB),"club",0,50);
  sk_add_train(SS_WEP_KNIFE,train_text(SS_WEP_KNIFE),"knife",0,60);
}

/*
 * Function name: sk_hook_unknown_skill
 * Description:   Player tries to improve or learn an unknown skill
 * Arguments:	  skill - The skill he sought for
 *		  verb  - 'learn' or 'improve'
 * Returns:	  0
 */
int
sk_hook_unknown_skill(string skill, string verb)
{
    NF("I'm afraid there is no skill named '" + skill + "' to " +
	verb + ".\n");
    return 0;
}

/*
 * Function name: sk_hook_improve_unknown
 * Description:	  Player wants to improve a skill he has never learned
 * Arguments:	  skill - The skill
 * Returns:	  0
 */
int
sk_hook_improve_unknown(string skill)
{
    NF("You must learn a skill before you can improve it.\n");
    return 0;
}

/*
 * Function name: sk_hook_learn_known
 * Description:	  Player wants to learn an already known skill
 * Arguments:	  skill - The skill
 * Returns:	  0
 */
int
sk_hook_learn_known(string skill)
{
    NF("You already know that skill, try improve it.\n");
    return 0;
}

/*
 * Function name: sk_hook_cant_train
 * Description:   Player can't train that skill that high for some reason
 * Arguments:	  skill  - The skill
 *		  to_lev - The level to wich the player wanted training
 * Returns:	  0
 */
int
sk_hook_cant_train(string skill, int to_lev)
{
    NF("You fail to adopt what the guildmaster teaches you.\n");
    return 0;
}

/*
 * Function name: sk_hook_cant_pay
 * Description:   Player can't pay for session (kill him?)
 * Arguments:	  skill  - The skill
 *		  to_lev - The level to wich the player wanted training
 *		  cost   - The price
 * Returns:	  0
 */
int
sk_hook_cant_pay(string skill, int to_lev, int cost)
{
    NF("You don't have enough money with you.\n");
    return 0;
}

string
train_text(int skill) {
   string what;

    switch(skill) {
        case SS_FORGING:
            what="forge items";
            break;
        case SS_APPR_OBJ:
            what="appraise objects";
            break;
        case SS_APPR_VAL:
            what="appraise the value of an item";
            break;
        case SS_WEP_KNIFE:
            what="use a knife";
            break;
        case SS_WEP_SWORD:
            what="use a sword";
            break;
        case SS_WEP_CLUB:
            what="use a club";
            break;
        case SS_WEP_AXE:
            what="use an axe";
            break;
        case SS_TRADING:
            what="trade with profit";
            break;
        case SS_MENDING_WEAPONS:
            what="repair broken weapons";
            break;
        case SS_MENDING_ARMOURS:
            what="repair broken armours";
            break;
    }
    return what;
}

/*
// checks players to see if they are advanced smiths
check_player()
{
    if (TP->query_stat(SS_LAYMAN)>=50 || this_player()->query_wiz_level())

        return 0;
    else
        TP->catch_tell("An apprentice steps in front of you and " +
            "declares: You have not proven yourself worthy to go there.\n");
        return 1;
}
*/


public void
pick_up(object ob)
{
    object cleaner;
    FIXEUID;   
    if(!present(ob, this_object())) return;

    cleaner = clone_object("/std/monster");
    cleaner->set_name("guild_cleaner");
    cleaner->set_base_stat(SS_STR, 350);
    cleaner->set_base_stat(SS_DEX, 10);
    cleaner->set_base_stat(SS_CON, 150);
    cleaner->set_base_stat(SS_WIS, 10);
    cleaner->set_base_stat(SS_INT, 10);
    cleaner->set_base_stat(SS_DIS, 30);
    cleaner->set_pname("smiths");
    cleaner->set_race_name("smith");
    cleaner->set_adj(({"charming", "neat"}));
    cleaner->set_short("charming neat smith");
    cleaner->add_prop(LIVE_I_NEVERKNOWN, 1);
    cleaner->move(TO, 1);
    tell_room(TO, QCNAME(cleaner)+" arrives.\n");
    cleaner->command("get all");
    cleaner->command("sigh");
    cleaner->command("drop items in box"); 
    cleaner->command("say Allow me to lend you a hand and put " +
        "this in the box for you.");
    cleaner->command("smile");
    tell_room(TO, QCNAME(cleaner)+" leaves.\n");
    cleaner->remove_object();
}


int
armageddon_it()
{
    return ARMAGEDDON->shutdown_active();  
}

public void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);


   if (armageddon_it()) return; 

   if(living(ob)) return;

   set_alarm(3.0, 0.0, &pick_up(ob));
}

