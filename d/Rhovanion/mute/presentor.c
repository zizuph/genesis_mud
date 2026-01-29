inherit "/std/monster";
#include <macros.h>
#include <language.h>
#include "/d/Rhovanion/lib/binbit.h"
#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
void
create_monster()
{
int i;
set_name("mute's simulacrum");
add_name("simulacrum");
set_short("mute's simulacrum");
set_long("Before you stands a drab grey-robed, hooded figure."+
"His face lies hidden beneath the soft, grey hood "+
" of his robe. \n");
set_race_name("human");
set_adj("mute's");
set_gender(0);
default_config_mobile(10);
set_alignment(0);
set_aggressive(0);
set_stats(({ 20, 20, 20, 100, 100, 20 }));
set_hp(1000);
set_skill(SS_DEFENCE, 20);
set_skill(SS_WEP_CLUB, 20);
set_skill(SS_PARRY, 20);
add_ask(({"report"}), VBFC_ME("do_report"));
add_ask(({"silence"}), VBFC_ME("do_silence"));
add_ask(({"perform"}), VBFC_ME("do_perform"));
add_ask(({"the stars"}), "emote gets mango from his backpack and says:  No, that's not it.  Ask me about potatoes!", 1);
add_ask(({"potatoes"}), "say Very good.  You are wise wizards, but you must prove to me your persistence.  Ask again!", 1);
add_ask(({"the masking street murders"}), "emote gasp and says: No! No! No!  That was the bollocks, you yobbers... uh... they skinned themselves... lightning lit that C-4, the police planted those instruments of dental torture on me, Aye yai yai, Zordon, summon the power rangers!", 1);
add_prop(CONT_I_WEIGHT, 56000);
add_prop(CONT_I_HEIGHT, 1500);
add_prop(CONT_I_VOLUME, 56000);
set_act_time(1);
add_act("say I have been sent here in m'Lord Mute's place to present to you his progress.");
add_act("emote acknowledges you all with a slow, short bow.");
add_act(({"say When you are ready to listen and hear of my Master's progress, ask me to report.  Should you tire of my voice, ask me to silence.  And if you bore, then ask me to perform.", "say I seek only to serve my Master."}));
set_alarm(1.0, 0.0, "get_club");
}
get_club()
{
seteuid(getuid());
clone_object("/d/Rhovanion/mute/simstaff.c")->move(this_object());
command("wield all");
}
string
do_report()
{
command("say Here is what I have to report!  Listen well so that ye may learn something...");
set_alarm(2.0,0.0,"part_two");
return "";
}
string
part_two()
{
command("emote mutters some arcane phrases and a blast of white light radiates forth from his visage!");
set_alarm(2.0,0.0,"part_three");
return "";
}
part_three()
{
command("say M'Lord Mute has been far busier than your nominal minds might possibly comprehend!  M'Lord Mute has NOT read any of your simple files, has NOT endeavored to read all about your lovely little code, and has REFUSED to kowtow to your puny standards!");
command("say However he has managed to keep his room tidy now for two whole days and counting!");
set_alarm(2.0,0.0, "part_next");
return "";
}
string
part_next()
{
command("say M'Lord Mute though has instructed me to inform you that he has managed to ingest enough example files to give him a working understanding of how to accomplish his coding means.  I am living proof of that!!!");
set_alarm(2.0,0.0, "part_next2");
return "";
}
string
part_next2()
{
command("emote turns around in a circle showing you the beauteous object of Mute's creation");
command("say M'Lord and Master also wishes to inform you that he is working on a quest series idea that will stupify you and make your ordinary code seem trivial in comparison!!!");
set_alarm(2.0,0.0, "part_next3");
return "";
}
string
part_next3()
{
command("say My Master is also considering coding a wizard tower in a forest.  He has been trying to find his old Middle-Earth Role-playing books for some idea-aid, but can't find all of them.  He suspects his trusted RP companion of `obtaining' them, but he's off to Russia...");
command("say Ahh, but I digress.  My Master truly wishes he could enlighten you more, but a raging kegger calls!!!  If you are curious as to his designs, you may make an appointment with him at his leisure.");
set_alarm(5.0,0.0, "part_next4");
return "";
}
string
part_next4()
{
command("say That is all I choose to divulge now!");
command("emote mutters more arcane phrases and the radiant light which once shown from him disappears.");
return "";
}
string
do_silence()
{
command("emote begins to laugh in a manner most evil and hideous!  Your heart sinks into your boots...");
set_alarm(2.0,0.0,"part_2");
return "";
}
string
part_2()
{
command("shout Impudent fool!  Did you really think the all-powerful Thessalonian wizard Mute would allow YOU to silence her sole representative to these gatherings???  Your actions have been noted!");
set_alarm(2.0,0.0, "part_3");
return "";
}
string
part_3()
{
command("emote smiles twistedly and you can feel Mute's powerful aura within him.");
return "";
}
string
do_perform()
{
command("emote twirls his twisted staff over his hands and proceeds to dance the enchanted dance of the magic, forest fairies!");
set_alarm(2.0,0.0, "part_ten");
return "";
}
string
part_ten()
{
command("emote stops and a magic, fairy light begins to emanate from his eyes!  Mute's simulacrum cries:  Would you like to see my special trick?  Ask me about the stars!!!");
return "";
}
