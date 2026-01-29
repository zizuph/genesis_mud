inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#define AMULET_TALE"amulet_tale"

string amulet_tale();

void
create_monster()
{
    ::create_monster();
    set_name("derek");
    set_race_name("human");
    set_adj("skinny");
    add_adj("jovial");
    set_short("jovial skinny human");
    set_long("This man looks very happy. He is standing in the "+
    "corner of the room with a lute in one hand and a glass of "+
    "wine in the other. He is dressed in very bright colors and "+
    "seems to be a bit drunk.\n");
    set_stats(({70,80,70,70,70,70}));
    set_alignment(700);
    set_skill(SS_WEP_KNIFE,75);
    set_skill(SS_DEFENCE,60);
    set_skill(SS_PARRY,35);
    set_skill(SS_AWARENESS,70);
    add_prop(NPC_M_NO_ACCEPT_GIVE,0);
    add_prop(CONT_I_WEIGHT, 60000);
    add_prop(CONT_I_HEIGHT, 170);
    set_title("The Travelling Bard");
    add_ask(({"tale", "story"}),VBFC_ME("amulet_tale"));
    set_knight_prestige(-200);
    add_speak("Greetings! How are you today? would you like to hear a "+
    "tale? if so, tell me!\n");
    set_act_time(8);
    add_act("emote sips his wine, and giggles like a girl.");
    add_act("say Nice day huh?.");
    add_act("say Want to hear a story? If so, tell me!.");
    add_act("snicker");
    set_cact_time(1);
    add_cact("say Hey!.");
    add_cact("say Help! Guards!");
    add_cact("say I'm going to stab you!");
    
    set_default_answer("Derek says: Eh??\n");
    add_prop(NPC_M_NO_ACCEPT_GIVE,0);
}

string
amulet_tale()
{ 
    write("Ahh, You wish to hear a tale, well hmm....Alright. I'll tell "+
    "you about the Amulet of Light... Long ago When King Raumdor "+
    "came to this land, the Undead here where running wild, Our "+
    "faithfull king led many brave warriors into battle, only to "+
    "be forced back into his stonghold. King Raumdor, asked his most "+
    "trusted Priest Illmareth to create something that would aid "+
    "our King and his warriors in battle. After many months of "+
    "work the Amulet of Light was created by Illmareth and his sect "+
    "of priests. With this amulet King Raumdor was successfull in "+
    "defeating the many undead and reducing them in number. Strangly "+
    "Illmareth and the Amulet disappeared some years after it's creation "+
    "no one knows where it is or what happended to it... But, I hear "+
    "that Lord Drakmere still seeks the lost Amulet, and hopes for it's "+
    "safe return, for in these dark times, it would be a very usefull "+
    "tool...\n\n");
   return "";
}
