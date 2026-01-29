/* Created By Stevenson */
#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include "/d/Krynn/icewall/local.h"
inherit "/std/act/domove";
inherit "/std/act/action";

inherit C_FILE

void
create_creature()
{
   set_race_name("puppy");
   set_name("puppy");
   set_long(
      "You see an adorable Husky puppy. It looks very sad though. "
      + "It seems to be looking for something.\n");
   set_base_stat(SS_STR, 20);
   set_base_stat(SS_DEX, 50);
   set_base_stat(SS_CON, 20);
   set_base_stat(SS_WIS, 3);
   set_base_stat(SS_INT, 3);
   set_base_stat(SS_DIS, 30);
   set_act_time(5);
   add_act("emote looks up at you expectantly.");
   add_act("emote whimpers very sadly.");
   add_act("emote searches hopelessly for something.");
   set_random_move(5);
   set_restrain_path(ICE_CAST1_R);
   set_monster_home(ICE_CAST1_R + "oakroom");
   remove_prop(NPC_M_NO_ACCEPT_GIVE);
   LEFTOVER("tail");
   LEFTOVER("tongue");
   CUTLEFTOVER("tummy");
   set_hitloc_unarmed( 0, 10, 100, "little body" );
}

void
init_living()
{
   ::init_living();
   add_action("pet_func", "pet");
}

int
pet_func(string arg)
{
   if ((arg == "puppy")) 
     {
	 write("You pet the puppy, and he jumps up and licks your face.\n");
	 say(QCTNAME(TP)+" pets the puppy, who jumps up and licks "
	     + TP->query_possessive()+" face.\n");
	 return 1;
     }
   NF("Pet what?\n");
   return 0;
}

void
enter_inv(object ob, object from)
{
    if (from) 
      {
	  set_alarm(2.0,0.0,"check_ball",ob,from);
	  ::enter_inv(ob, from);
      }
}

void
check_ball(object ob, object from) 
{
    if (ob->adjectiv_id("red") && ob->id("ball")) 
      {
	  ob->remove_object();
	  command("emote wags his tail happily.");
	  seteuid(getuid(this_object()));
	  clone_object(ICE_CAST_O+"closetkey")->move(TO);
	  command("drop bone");
	  command("emote runs off to play with his ball.");
	  TO->remove_object();
      }
    else 
      {
	  command("emote looks grateful but is still sad.");
	  command("drop all");
      }
}

int 
special_attack(object ob)
{
    if (TO->query_stat(SS_DEX) < random(ob->query_stat(SS_DEX)))
      {
	  ob->hit_me(random(60), W_IMPALE, TO, -1 );
	  ob->catch_msg( QCTNAME(TO) + " bites you.\n" );
	  tell_watcher( QCTNAME(TO) + " bites " + QCTNAME(ob) + ".\n", ob );
      }
    return 1;
}

