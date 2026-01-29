/*
 * A gibberer.
 */

#include "../stddefs.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"

#pragma save_binary

inherit "/std/monster";
inherit STRINGLIB;

#define ADJECTIVES \
  ({ "loudmouthed", "smartmouthed", "widemouthed", "loud", "shrill",  \
     "talkative", "loquacious", "conversational", "chattering", "glib", \
     "flippant", "longwinded", "multiloquous", "garrulous", "loosetongued", \
     "babbling", "jabbering", "quibbling", "simple", "dense", "nasal", \
     "guttural", "mumbling", "drawling", "incoherent", "deranged", \
     "unhinged", "scatterbrained", "raving", "rambling", "confounded"})

#define LONG \
  "It's a stunted, humanoid creature. The head is low and wide, with a\n"+\
  "broad, lipless mouth filled with sharp teeth. Its nose is small and\n"+\
  "snub between two slanted eyes. Its brow is slanting, and the top of\n"+\
  "its head is crowned by a pair of long, pointed ears on the sides of\n"+\
  "a dirty tuft of pale hair. Its short body is hairy and inadequately\n"+\
  "covered by tied-on pieces of rags. It is @@query_gender_string@@.\n"

#define GIBBER_STRINGS \
({ \
  "Knife is sharp. Sharp is knife. Sharp knife is. Is sharp knife. Knife is.",\
  "Protect the Purity of Essence! Save precious bodily fluids!",\
  "Life! Don't talk to me about life!", \
  "There is the silent death. It is green. It has horrible eyes.", \
  "I have seen no light.", \
  "Listen. Hear the blue moose. Go where down is up.", \
  "The Uniform inhibits the bastard turtledove in humans.", \
  "A tent mogul flew bisected and enchained over the bridge.", \
  "Gossamer syllables caress my tongue.", \
  "Advice me. The future is dead. Merge with the fracas.", \
  "Burrow deep. Burrow in blackness. The dark is.", \
  "See the darkness shine.", \
  "I want a shrubbery.", \
  "I said 'nih' to an old lady.", \
  "What is the average airspeed velocity of an unladen swallow?", \
  "Light and darkness. Darkness and light. Turn the wheel.", \
  "Use a tenon to crop the sienna halibut.", \
  "Many interesting bowls are taken for emissaries when regurgitated.", \
  "Before the adversary there was forage retained for the hazel discord.",\
  "Pick isomorph fleshwounds when the false belfry is covered.", \
  "Are you here for an argument?", \
  "Albatross! Albatross!", \
  "Abounding is the broth when the rapacious fortune comes.", \
  "Prosper, you gloss and confounded ocular monochord.", \
  "If you bore into a heap of picaroons, real nails will culminate.", \
  "Gauge the grandfather before the child becomes pragmatic.", \
  "Increase eccentrically along the sweet collaborating justice.", \
  "The galley is conoid. The sigil is wasted. Disapprove.", \
  "Goldfish shoals are nibbling at my toes.", \
  "Freckles have a smack of the lower blue framework of order.", \
  "Illuminate your party! Mistreat the galvanic blockage!", \
  "Anew I ask: Is thy entertainment bearable?", \
  "Deafen the defenestrated defenders!", \
  "The deed is done.", \
  "We're going nowhere fast!", \
  "The force is strong in you!", \
  "I can feel this is the beginning of a wonderful friendship!", \
  "Go ahead; Make my day!", \
  "Aha! Green gloss globules!", \
})


#define KNIFE OBJDIR + "gibber_knife"

string *gibber_array;

equip();

create_monster() {
  if (IS_CLONE) {
    set_name("gibberer");
    set_race_name("gibberer");
    set_adj(ADJECTIVES[random(sizeof(ADJECTIVES))]);
    set_long(LONG);

    set_gender(random(2));

    set_base_stat(SS_STR, 3);
    set_base_stat(SS_DEX, 5);
    set_base_stat(SS_CON, 4);
    set_base_stat(SS_INT, 3);
    set_base_stat(SS_WIS, 3);
    set_base_stat(SS_DIS, 25);
    set_hp(16);    

    set_alignment(-70);
    set_appearance(65);
    set_aggressive(1);
    set_attack_chance(100);

    add_prop( NPC_I_NO_LOOKS,   1);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_alarm(0.5, 0.0, equip);

    refresh_mobile();
  }
}

init_living()
{
  if (interactive(this_player()))
    set_heart_beat(1);

  ::init_living();
}


string master_gibber()
{
  int i;
  string str;

  if (!gibber_array ||
      sizeof(gibber_array) < 1)
    gibber_array = GIBBER_STRINGS;

  i = random(sizeof(gibber_array));
  str = gibber_array[i];

  gibber_array = exclude_array(gibber_array, i, i);
  return str;
}

void check_gibber_shutdown()
{
  object *inv;
  int i;
  
  if (environment() && (inv = all_inventory(environment())) != 0)
    for (i = 0; i < sizeof(inv); i++)
      if (interactive(inv[i]))
	return;

  set_heart_beat(0);
}


void gibber()
{
  say(WRAP("The " + query_nonmet_name() + 
	   " says: " + MASTER->master_gibber() + "\n"));
}



void heart_beat()
{
  gibber();
  check_gibber_shutdown();

  ::heart_beat();
}


equip()
{
  object knife;

  knife = clone_object(KNIFE);
  knife->move(this_object());
  command("wield knife");
}
  



