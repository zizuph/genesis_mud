/*
 * greenelf.c
 * Green elf who belongs in Thranduil's Caverns
 *
 */

inherit "/std/monster";

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include "/secure/std.h"
#include "/d/Rhovanion/defs.h"

#define COINS     "/std/coins"
#define WEP_PATH  "/d/Rhovanion/common/weapons/"
#define ARM_PATH  "/d/Rhovanion/common/armours/"
#define OBJ_PATH  "/d/Rhovanion/common/objects/"

void add_speech(string str);  /* A handy little function. */

void
create_monster()
{
  if ( !IS_CLONE )
    {
      return;
    }
  seteuid(getuid());
  set_name("elf" );
  set_pname( "elves" );
  set_short("green elf");
  set_pshort("green elves");
  set_long("@@query_long");
  set_race_name("elf");
  set_gender(0); /* Male */    /* str, dex, con, int, wis, dis */
  set_stats( ({ 40+random(5), 40+random(8), 50+random(5), 
                  40+random(5),  40+random(5), 110+random(5) }) );
  set_hp(query_max_hp());
  set_mana(query_max_mana());
  set_alignment(500);
  set_all_hitloc_unarmed(40); /* AC of 40 without armor */
  set_living_name("elf");
  set_aggressive(0);
  set_attack_chance(0);
  set_chat_time(1);  /* He just doesn't talk enough. */
  set_cchat_time(1); /* All those monks with their plexus hits.. */
  add_speech("How are you?");
  add_speech("Where are you going?");
  set_skill(SS_WEP_SWORD,30);
  set_skill(SS_WEP_KNIFE,30);
  set_skill(SS_2H_COMBAT,50);
  set_skill(SS_UNARM_COMBAT,50);
  set_skill(SS_PARRY,40);
  set_skill(SS_DEFENCE,40);
  set_skill(SS_AWARENESS,80); /* smart elf */
  add_prop(CONT_I_HEIGHT,193);
  add_prop(CONT_I_WEIGHT,70000);
  add_prop(LIVE_I_SEE_DARK,50);
  add_prop(LIVE_I_SEE_INVIS,10);
  add_prop(LIVE_I_NEVERKNOWN,1);
  set_random_move(4,0);
  set_restrain_path("/d/Rhovanion/common/mirkwood/thranduil/");
}

string query_long()
{
  return (BS("This is one of the elves who are living in these caverns. \n"));
}

void add_speech(string str)
{
  add_chat(str);
  add_cchat(str);
}

arm_me()
{
  object weapon,cash,armour;
  int i,x;
  
  i = random(2);
  if (i==1)
    {
      weapon = clone_object(WEP_PATH + "esword");
    }
  else
    {
      weapon = clone_object(WEP_PATH + "edagger");
    }
  weapon -> move(TO);
  
  i = random(3);
  switch(i)
    {
    case 0: 
      armour = clone_object(ARM_PATH + "eplate");
      armour -> move(TO);
      break;
    case 1:
      armour = clone_object(ARM_PATH + "eboots");
      armour -> move(TO);
      break;
    case 2:
      armour = clone_object(ARM_PATH + "eshield");
      armour -> move(TO);
      break;
    }
  
  cash = clone_object(COINS);
  cash -> set_coin_type("copper");
  cash -> set_heap_size(random(50));
  cash -> move(TO);

  command("wield all");
  command("wear all");
  command("smile");
}

/* Solamnian Knights are honored by this kill. */

query_knight_prestige()
{
  return -3;
}

/* EOF */
