/*  Created by Mecien & Mortricia 
 *
 *   Moved to /d/Terel/common/moor/   ~1999
 *
 *   Revisions:
 *     Lilith Dec 2021: copied cloned items to moor/obj/ dir.
 *                      code cleanup.
 */

inherit "/std/monster";
inherit "/std/act/seqaction";

#include "/d/Terel/include/Terel.h"
#include "../local.h"

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <comb_mag.h>
#include <wa_types.h>


public void
create_monster()
{
   
    set_name("vercus");
    set_race_name("human");
    set_living_name("vercus");
    set_adj("black-haired");
    add_adj("wizened");
    add_name("warlock");
    add_name("evoker");
   
    set_scar(2);
    show_scar(({"right shoulder", "forehead"}));
   
    set_title("the High Evoker of the Icy Abyss");
    set_stats(({ 101, 111, 180, 190, 150, 150 }));
    set_skill(SS_SPELLCRAFT, 100);

    set_skill(SS_ELEMENT_FIRE, 100);
    set_skill(SS_ELEMENT_AIR, 100);
    set_skill(SS_ELEMENT_LIFE, 100);
    set_skill(SS_ELEMENT_DEATH, 100);
    set_skill(SS_ELEMENT_WATER, 100);
    set_skill(SS_ELEMENT_EARTH, 100);
	
    set_skill(SS_FORM_ABJURATION, 100);
	set_skill(SS_FORM_CONJURATION, 100);
    set_skill(SS_FORM_ENCHANTMENT, 100);
    set_skill(SS_FORM_DIVINATION, 100);
    set_skill(SS_FORM_ILLUSION, 100);
    set_skill(SS_FORM_TRANSMUTATION, 100);

    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 50);
	set_skill(SS_BLIND_COMBAT, 50);
    set_skill(SS_WEP_SWORD, 75);
    set_skill(SS_UNARM_COMBAT, 55);
   
    set_all_hitloc_unarmed(60);  
    set_appearance_offset(-30);
    set_alignment(-980);
   
    set_long("A charismatic man, standing medium height, his eyes "+
      "and hair now gray, fingers tipped with sharp black claws.\nAn " +
       "aura of darkness seems to gather about him.\n");
   
    /* Obsolete for decades but leaving for nostalgia */ 
    add_ask("for absolution", "@@absolve", 1);
    add_ask(({"about curse", "about mystic curse", "mystic curse", "curse"}),
      "say That foul power is long broken, faded from the world!"+
	  "I could still absolve people of the curse, if the Shrine "+
	  "and the Valley were still accessible. "+
	  "All they would have to do is bring me the robe of the "+
      "holy cantor and ask for absolution.", 1);
    add_ask(({"prophet", "about prophet", "mecien", "prophet mecien"}), 
	  "say The Prophet Mecien was a great and visionary leader. He raised "+
      "up a band of mystics, built them a shrine, and then did what many "+
	  "leaders do... He disappeared, leaving his Mystics to struggle "+
      "and die in their powerlessness.", 1);
    add_ask(({"mystics", "mystic", "shrine", "order", "holy men", "valley"}),
      "say There once was an order of holy men living up in the mountains. "+
	  "They were eventually driven out of their Shrine when their Prophet "+
      "disappeared.", 1);
    add_ask(({"god", "dark god", "beast", "lord of darkness"}),
      "say He has many faces, many names, but always rules in darkness. "+
      "By this shall you know Him.", 1);

    set_chat_time(5);
    add_chat("We took the Mystic Shrine and desecrated its altars! "+
        "Praised be the Lord of Darkness!");
    add_chat("Mystics were a breed of vile swine...");
    add_chat("They thought they were such goody-goodies, yet they "+
        "served a dark cause all the same.");
    add_chat("I killed many mystics in my time.");
    add_chat("I had hoped their Prophet would one day die at my hands, "+
        "but he disappeared long ago.");
    add_chat("I shall make all prostrate before my Lord's idols.");
    add_chat("We must worship the Beast in all His forms.");
	add_chat("I have absolved many of the mystic curse.");

    set_act_time(10);
    add_act("smile satan");
    add_act("emote chews on his claw-like finger.");
    add_act("emote exhales a cloud of vapor.");
	add_act("shiver");
    add_act("seems to be rehearsing a spell.");	
	
    set_cchat_time(3);
    add_cchat("You pitiful fool!");
    add_cchat("I am beyond your power!");
    add_cchat("Hear my name and tremble! I am Vercus the "+
        "High Evoker of the Icy Abyss!");
    add_cchat("O Dark One, reveal your strength!");
   
    set_cact_time(2);

    setuid();
    seteuid(getuid(this_object()));
	
	add_armour(OBJDIR +"warlock_robe");
	add_weapon(OBJDIR +"bsword");
    equip("/d/Terel/spells/vercus_spells"); 	
}


void
gone(object who, string place)
{
    tell_room(ENV(who), QCTNAME(who) + " fades into darkness!\n", who);
    who->catch_msg("You are covered by darkness!\n");
    who->move_living("M", place);
}

void
wisk(object victim)
{
    string place;
    int loc;
    command("cackle satan");
    tell_room(ENV(TO), QCTNAME(TO) + " intones strange words and "+
      "points a finger at " +QCTNAME(victim) + ".\n", victim);
    victim->catch_msg(QCTNAME(TO) + " intones strange words and "+
      "points at you.\n");
    loc = random(3);
    if(loc = 0) place = "/d/Terel/mountains/top";
    if(loc = 1) place = "/d/Terel/silver/road/road58";
    if(loc = 2) place = "/d/Terel/common/road/road2";
    set_alarmv(3.0, -1.0, "gone", ({ victim, place }));
	return;
}

void
summon()
{
   
    object mon;
   
    setuid();
    seteuid(getuid(this_object()));

    tell_room(ENV(TO), QCTNAME(TO) + 
      " raises his hands and a black flame arises!\n");

    if (!present("hound", ENV(TO)))
    {
        say("Come, hound! Come to me in my moment of need!\n");
		mon=clone_object(MOBDIR +"hound");
        mon->move_living("M", ENV(TO));
        tell_room(ENV(TO), "A black hound takes shape from the flames.\n");
    }
    mon->command("growl menac");   
    mon->attack_object(TO->query_attack());
    mon->set_follow("vercus");
    return;
}


int
special_attack(object victim)
{
    if (ENV(victim) != ENV(TO) || victim->query_ghost())
    {
        TO->stop_fight(victim);
        return 1;
    }
    command("emote intones a prayer to his Dark God.");
    switch(random(5))
    {		
      case 0:
      {
        if(!TO->query_prop(LIVE_I_SEE_DARK))
            command("cast darkvision");
      } break;
      case 1:
        command("cast heal me");
        break;
      case 2:
        command("cast firebolt " +OB_NAME(victim));
        break;
      case 3:
        wisk(victim); 
        break;
      case 4:
        summon();
        break;		
      default: return 0;
    }
    return 0;
}



