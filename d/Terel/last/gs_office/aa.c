/*
 * Genesis ShipLines - Sparkle office.
 * Toilet keeper
 * TAPAKAH, 10/2008
 * To be transferred later into /d/Sparkle
 */

#include <macros.h>

inherit "/std/monster";

void
create_monster () {

  if(! IS_CLONE)
    return;

  set_living_name("Wipper");
  set_name("Wipper");
  add_name(({"Wipper", "wipper", "toilet_keeper", "cleaner"}));
  set_race_name("goblin");
  set_adj(({"old", "scraggy"}));
  set_gender(G_MALE);
  set_long("This goblin is a toilet keeper and cleaner working for Genesis " +
           "ShipLines Company. He is sitting behind a simple desk, seeming " +
           "extremely bored.\n");
  //  set_default_answer("say just go an fix de damn toilits willya?\n");
  add_prop(OBJ_M_NO_ATTACK,
           "You cannot attack Genesis ShipLines employees.\n");
  add_prop(OBJ_M_NO_MAGIC_ATTACK,
           "You cannot attack Genesis ShipLines employees.\n");
  add_prop(OBJ_M_NO_GIVE, 1);
  add_act("The goblin darts a quick look inside the western door, then " +
          "sighs.\n");
}

void
catch_question (string question)
{
  command("say just go an fix de damn toilits willya?");
}

void
equip_me () {

}
