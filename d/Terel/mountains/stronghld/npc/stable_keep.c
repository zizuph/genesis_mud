/*  
 *  Blacksmith
 *
 *
 */
#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;
inherit "/std/act/action";

#include "/sys/macros.h"
#include <ss_types.h>


public string
reply_stable()
{
  command("say This here stable is for the Lancers of " +
     "Stonehold only. But, if yer are needing supplies, " +
     "we could spare some oats. And the waters free.");
  return "";
}


public string
reply_water()
{
  command("say Waters free. Over there in that trough..");
  command("point trough");
  return "";
}

public string
reply_oats()
{
  command("say I reckon we could spare some. Just " +
     "buy em from me.");
  return "";
}


void
create_monster()
{
    if (!IS_CLONE) return;

    set_name("dola");
    add_name("Dola");
    add_name("stable keep");
    set_race_name("dwarf");
    set_title("Stronghold Stable Keep");
    set_adj(({"blue-eyed","gentle"}));
    set_long("The stable keep looks busy keeping the stables "+
       "clean and its charges comfortable.\n");

    default_config_npc(88);


    set_skill(SS_DEFENCE, 70);
    set_skill(SS_PARRY, 70);
    set_skill(SS_UNARM_COMBAT, 80);
    SET_MAX_HP;

    set_all_hitloc_unarmed(40);
    set_all_attack_unarmed(50, 40);
    
    enable_intro();
    add_act("cleans out a stall.");
    add_act("pitches fresh hay into a stall.");
    add_act("fills a food bin with oats.");
    add_act("drink water from trickle");
    set_chat_time(20);
    add_chat("How about a bag of fresh oats for yer mount?");
    add_chat("Used to work fer Jonas down in Calathin. " +
       "If yer ever down that way look him up. He's got " +
       "fine horses fer sale..");
    add_chat("If'n yah thirsty, make sure you drink from the " +
       "trickle and not the trough. I wouldn't want to " +
       "mistake you for an animal.. Just a bit of friendly " +
       "advice dont cha know..\n");

   add_ask(({"stable"}), reply_stable, 1);
   add_ask(({"water"}), reply_water, 1);
   add_ask(({"feed","oats"}), reply_oats, 1);
}
