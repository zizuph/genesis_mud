/* Vladimir 8-09-94 */

#pragma strict_types

inherit "/std/monster";

#include <macros.h>
#include <ss_types.h>

#include "defs.h"

void arm_me();

void
create_monster()
{
    int x;
    string *adj, *size;
    adj = ({"loudmouthed", "smartmouthed", "widemouthed", "loud", "shrill", 
        "talkative", "loquacious", "conversational", "chattering", "glib",
        "flippant", "longwinded", "multiloquous", "garrulous", "loosetongued",
        "babbling", "jabbering", "quibbling", "simple", "dense", "nasal",
        "guttural", "mumbling", "drawling", "incoherent", "deranged",
        "unhinged", "scatterbrained", "raving", "rambling", "confounded"});
    x = random(sizeof(adj));

    set_race_name("gibberer");
    add_adj(adj[x]);
    set_long("It's a stunted, humanoid creature. The head is low and " +
        "wide, with a broad, lipless mouth filled with sharp teeth. " +
        "Its nose is small and snub between two slanted eyes. Its brow " +
        "is slanting, and the top of its head is crowned by a pair of " +
        "long, pointed ears on the sides of a dirty tuft of pale hair. " +
        "Its short body is hairy and inadequately covered by tied-on " +
        "pieces of rags. It is a @@query_gender_string@@.\n");

    set_gender(random(2));

    set_alignment(0);
    default_config_npc(25);
    set_skill(SS_DEFENCE, 10);
    set_skill(SS_WEP_KNIFE, 15);

    add_chat("Knife is sharp. Sharp is knife. Sharp knife is. Is sharp knife. Knife is.");
    add_chat("Protect the Purity of Essence! Save precious bodily fluids!");
    add_chat("Life! Don't talk to me about life!");
    add_chat("There is the silent death. It is green. It has horrible eyes.");
    add_chat("I have seen no light.");
    add_chat("Listen. Hear the blue moose. Go where down is up.");
    add_chat("The Uniform inhibits the bastard turtledove in humans.");
    add_chat("A tent mogul flew bisected and enchained over the bridge.");
    add_chat("Gossamer syllables caress my tongue.");
    add_chat("Advice me. The future is dead. Merge with the fracas.");
    add_chat("Burrow deep. Burrow in blackness. The dark is.");
    add_chat("See the darkness shine.");
    add_chat("I want a shrubbery!");
    add_chat("A witch she is. Burn her!");
    add_chat("I said 'nih' to an old lady.");
    add_chat("What is the average airspeed velocity of an unladen swallow?");
    add_chat("Light and darkness. Darkness and light. Turn the wheel.");
    add_chat("Use a tenon to crop the sienna halibut.");
    add_chat("Many interesting bowls are taken for emissaries when regurgitated.");
    add_chat("Before the adversary there was forage retained for the hazel discord.");
    add_chat("Pick isomorph fleshwounds when the false belfry is covered.");
    add_chat("Are you here for an argument?");
    add_chat("Albatross! Albatross!");
    add_chat("Abounding is the broth when the rapacious fortune comes.");
    add_chat("Prosper, you gloss and confounded ocular monochord.");
    add_chat("If you bore into a heap of picaroons, real nails will culminate.");
    add_chat("Gauge the grandfather before the child becomes pragmatic.");
    add_chat("Increase eccentrically along the sweet collaborating justice.");
    add_chat("The galley is conoid. The sigil is wasted. Disapprove.");
    add_chat("Goldfish shoals are nibbling at my toes.");
    add_chat("Freckles have a smack of the lower blue framework of order.");
    add_chat("Illuminate your party! Mistreat the galvanic blockage!");
    add_chat("Anew I ask: Is thy entertainment bearable?");
    add_chat("Deafen the defenestrated defenders!");
    add_chat("The deed is done.");
    add_chat("We're going nowhere fast!");
    add_chat("The force is strong in you!");
    add_chat("I can feel this is the beginning of a wonderful friendship!");
    add_chat("Go ahead; Make my day!");
    add_chat("Aha! Green gloss globules!");
    add_chat("Besieged shoes dipped in soup smell like flying birds.");
    add_chat("No theories say green donuts spread easily.");
    add_chat("Purple feathers expound the meaning of a small paradise.");

    arm_me();

}

void
arm_me()
{
   clone_object(WEP_DIR + "dagger")->move(TO);

   command("wear all");
   command("wield all");
}

