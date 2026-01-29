/*
 * arroch.c
 *
 * Fishmonger for the village fish market in Port MacDunn.
 * 
 * Khail - April 21/97
 * Refactored slightly
 * Tapakah, 07/2021
 */

#pragma strict_types

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"
#include "npc.h"

inherit BASE_NPC;

object shop;

string
act_1 ()
{
  object *arr;
  string str;

  arr = filter(all_inventory(environment()), living);
  arr -= ({TO});
  str = LANG_WNUM(sizeof(arr));

  return "say Well? What do you " +
    (str == "one" ? "" : str + " ") + "want?";
}

/*
 * Function name: arm_me
 * Description  : Clones in the shopkeeper's equipment
 *                and has him wear/wield it.
 * Arguments    : n/a
 * Returns      : n/a
 */
void
arm_me ()
{
  armours = ({ "/d/Khalakhor/common/arm/shirt_cloth",
               "/d/Khalakhor/common/kilts/kilt_garrow",
               "/d/Khalakhor/common/arm/belt" });
  weapons = ({ "/d/Khalakhor/common/wep/dirk" });
  ::arm_me();
}

/*
 * Function name: create_khalakhor_human
 * Description  : Turns this object into a shopkeeper.
 * Arguments    : n/a
 * Returns      : n/a
 */
void
create_khalakhor_human ()
{
  ::create_khalakhor_human();
  add_name("monger");
  add_name("man");
  set_adj("thinly bearded");
  add_adj("dark-eyed");
  set_long("This muscular, dark-eyed man is a bit on the " +
           "intimidating side, but that could be the smell of fish. " +
           "His eyes gleam brightly, and the defiant set of his " +
           "chin seems odd for one of his occupation.\n");

  set_size_descs("of normal length", "of normal width");

  default_config_npc(40);
  set_skill(SS_AWARENESS, 50);
  set_skill(SS_UNARM_COMBAT, 30);
  set_skill(SS_DEFENCE, 20);
  set_skill(SS_WEP_KNIFE, 35);

  set_alignment(-400);
  set_exp_factor(50);
  set_act_time(15);

  add_act("ponder");
  add_act("emote scratches absentmindedly at his beard.");
  add_act("emote gets a look of concentration on his face " +
          "and begins quickly counting something on fingers.");
  add_act("cough");
  add_act("emote sorts through one of the trays of fish, " +
          "muttering to himself as he pulls out a few that " +
          "have gone bad and discards them.");
  add_act(act_1);

  add_ask(({"whale","blubber","whale blubber","whales"}),
          "say I almost never have anything from the whales, unless "+
          "someone finds one washed up on the shore.",1);
  add_ask(({"shore","about shore","where shore","where is shore"}),
          "say You walked over the shore on the "+
          "piers when you arrived.",1);
  add_ask(({"eil-galaith"}),
          "say Hmm. Well I'm not sure. Sounds like something that might "+
          "be on the isle of Galaith.", 1);
  add_ask(({"galaith", "isle of galaith", "galaith isle"}),
          "say Oh yes, the isle of Galaith is near the southwestern speir. "+
          "I've heard there is a tower that suddenly appeared there. I do "+
          "not travel much myself to know for sure. You might try around "+
          "the docks.", 1);
}

void
hook_return_intro_new (string str)
{
  command("say Good day to you, " + capitalize(str) +
          ", I'm " + query_name() + " " + query_title() + 
          ". What can I do for you?");
  command("bow " + str);
}

void
hook_return_intro_bad (string str)
{
  command("smirk");
  command("say I remember you, bugger off!");
}

void
hook_return_intro_good (string str)
{
  command("chuckle");
  command("say Ahh, yes, of course, I remember you from " +
          "your last visit, " + capitalize(str) + ", what " +
          "can I do for you this time?");
}

/*
 * Function name: attacked_by (MASK)
 * Description  : Allows the npc to call for help when attacked.
 * Arguments    : who - Object pointer to the attacker.
 * Returns      : n/a
 */
void
attacked_by (object who)
{
  ::attacked_by(who);

  respond_to_attack(who);
}    

/*
 * Function name: can_block_me
 * Description  : Allows the monger to attempt to block a player
 *                trying to get into the secret passage into the
 *                tunnels. He can block only if he's not stunned,
 *                can see the player.
 * Arguments    : who - Object pointer to player to stop.
 * Returns      : 0 - Couldn't stop the player.
 *                1 - Stopped the player.
 */
int
can_block_me (object who)
{
  /* Can't block if the npc isn't even in the shop. */
  if (environment() != shop)
    return 0;

  /* If the room is too dark, we can't see the player to stop */
  /* them. */
  if (!CAN_SEE_IN_ROOM(TO)) {
    tell_object(who, TO->query_The_name(who) + " can't see " +
                "in the dark, so you slip right past him.\n");
    return 0;
  }

  /* If the npc can't see the player, it can't stop him. */
  if (!CAN_SEE(TO, who)) {
    tell_object(who, TO->query_The_name(who) + " can't see you " +
                "for some reason, and is oblivious to you entering " +
                "the opening!\n");
    return 0;
  }

  /* Can't block if we're stunned. */
  if (query_prop(LIVE_I_STUNNED)) {
    tell_object(who, TO->query_The_name(who) + " is too busy " +
                "trying to regain his senses to even notice you approaching " +
                "the barrels.\n");
    return 0;
  }

  tell_object(who, TO->query_The_name(who) + " won't let you " +
              "anywhere near the opening.\n");
  tell_room(environment(), QCTNAME(who) + " tries getting a bit " +
            "closer to the back barrels, but is stopped by " +
            QTNAME(TO) + ".\n", ({TO, who}));
  return 1;
}
    
