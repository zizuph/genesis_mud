inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_monster()
{
    ::create_monster();
    set_name("orgadar");
    add_name("sailmaker");
    set_race_name("human");
    set_adj("weathered");
    add_adj("melancholy");
    set_long("This old man has an ancient look to him, eyes seeming to "+
      "see more than just the immediate surroundings. A certain sadness "+
      "is evident in those knowledgeable eyes, a deep-rooted sorrow that "+
      "must emerge from his very soul.\n");
    set_stats(({45,50,40,60,60,50}));
    set_alignment(125);
    set_skill(SS_TRADING,90);
    set_skill(SS_AWARENESS,60);
    set_act_time(3);
    add_act("sigh");
    add_act("emote gazes wistfully out to sea.");
    add_act("ponder");
    add_act("say Are you here to buy some sails?");
    add_act("say I was once a captain of the Seahawk, aye, she was a grand "+
      "ship, the likes of which the sea shall never know again.");
    add_act("say How I wish she could sail once more.");
    add_act("say A storm seems to be brewing in the south.");
    add_act("say Ah, how I long for the good old days.");
    set_knight_prestige(-100);
    set_title("the Sailmaker");
    add_speak("All I sell are sails for sea-going vessels.\n");
    set_default_answer("The sailmaker sighs deeply.\n");
    add_ask(({"sails","sail"}),"The sailmaker says: That's what I sell "+
      "here in this shop.\n");
    add_ask(({"ship","seahawk"}),"The sailmaker says: Ahh...she was a "+
      "fine old gal...until they mothballed her...\n"+
      "The sailmaker wipes away a tear.\n");
    add_ask(({"sea","storm","south"}),"The sailmaker says: Trouble is "+
      "stirring in the south, far out at sea. Don't ask me how I know...I just "+
      "have this feeling in my gut.\n");
    add_prop(OBJ_M_NO_ATTACK,"Considering the fact that many ships depend "+
      "on this man's sails, you don't think it'd be wise to anger all those "+
      "ship captains by killing him.\n");
    set_alarm(1.0,0.0,"my_stuff");
    trig_new("%w 'bought' %s", "react_buy");
}
void
my_stuff()
{
    object item;
    seteuid(getuid(TO));
    item = clone_object("/d/Kalad/common/port/obj/tar");
    item -> move(TO);
    item = clone_object("/d/Kalad/common/port/obj/tar");
    item -> move(TO);
    item = clone_object("/d/Kalad/common/port/obj/tar");
    item -> move(TO);
    item = clone_object("/d/Kalad/common/port/obj/tar");
    item -> move(TO);
    item = clone_object("/d/Kalad/common/port/obj/tar");
    item -> move(TO);
    item = clone_object("/d/Kalad/common/port/obj/tar");
    item -> move(TO);
    item = clone_object("/d/Kalad/common/port/obj/tar");
    item -> move(TO);
    item = clone_object("/d/Kalad/common/port/obj/tar");
    item -> move(TO);
    item = clone_object("/d/Kalad/common/port/obj/tar");
    item -> move(TO);
    item = clone_object("/d/Kalad/common/port/obj/tar");
    item -> move(TO);
}
int
react_buy(string who, string dummy){
    if(who){
	who = lower_case(who);
	set_alarm(2.0,0.0,"return_buy",who);
	return 1;
    }
}
void
return_buy(string who){
    object obj;
    int ran;
    if(obj = present(who, environment())){
	command("give tar to " + (obj->query_real_name()));
	command("smile");
	command("whisper " + (obj->query_real_name()) + " You might want to go and see Bassil the Shipwright over in the docks.");
    }
}
