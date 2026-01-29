/*
 * small elven nymph dragons
 * for Galaith isle
 * Created by Damaris 12/Y2K
 */

#pragma save_binary
#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <language.h>
#include <filter_funs.h>
#include <stdproperties.h>


#define A_RCLAW  1
#define A_LCLAW  2

#define H_HEAD 0
#define H_BODY 1
#define H_RARM 2
#define H_LARM 3

private string query_creature_one();

string _ADJ = query_creature_one();

public void
create_creature()
{
    set_name("dragon");
    set_race_name("elven nymph dragon");
    set_short("tiny elven nymph dragon");
    set_adj("tiny");
    set_gender(G_FEMALE);
    set_long("This is a " + short() + ".\n"+
      "She has "+ _ADJ + " coloured scales.\n"+
      "She has piercing " + _ADJ + " eyes.\n"+
      "She has a sinuous agile body.\n"+
      "She has a long swishy tail.\n"+
      "She has long sharp claws.\n");
  
    set_stats(({100 + random(20),
                100 + random(5),
                100 + random(10),
                100 + random(5),
                100 + random(5),
                100 + random(10)}));
                
    set_act_time(15);
    refresh_living();
    set_stuffed(1200);
    set_appearance_offset(-150);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_UNARM_COMBAT, 100);

                     
    set_attack_unarmed(A_RCLAW, 25, 20, W_BLUDGEON, 30, "right claw");
    set_attack_unarmed(A_LCLAW, 25, 20, W_BLUDGEON, 30, "left claw");

    set_hitloc_unarmed(H_HEAD,     /* Hitloc id */
                      35,          /* Ac of hitloc (25 to all dt's) */
                      10,          /* % of attacks to hit this hitloc */
                      "head");     /* Hitloc description. */
    set_hitloc_unarmed(H_BODY, 30, 50, "body");
    set_hitloc_unarmed(H_RARM, 15, 10, "right wing");
    set_hitloc_unarmed(H_LARM, 15, 10, "left wing");

    set_m_in("mysteriously appears");
    set_m_out("mysteriously disappears");

    add_prop(CONT_I_WEIGHT, 350);
    add_prop(CONT_I_VOLUME, 350);
    add_prop(LIVE_I_NON_REMEMBER, 1);

    add_prop(NPC_M_NO_ACCEPT_GIVE, " does not seem to be able to carry " +
             "anything else but small letters.\n");
    add_act("emote puts a claw into the water.");
    add_act("emote flaps her wings quickly.");
    add_act("emote curls her long tail up around her body.");
    add_act("emote yawns and a bit of smoke escapes from her mouth.");
    add_act("emote jumps into the pool then flies up and around before "+
      "resting again.");
}

private string
query_creature_one()
{
  string *adjectives = ({
        "rainbow",
        "saffron and cerulean",
        "emerald and silver",
        "pearl and hyacinth",
        "silver and sable",
        "ruby and ebony",
        "gold and jade",
        "crimson and gold"
                        });

  return adjectives[random(sizeof(adjectives))];
}


