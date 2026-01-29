/* The donkey working at the elevator.
 * Latest update 20.03.95 by Dajala
 */

#include "/d/Krynn/common/defs.h"
#include <macros.h> /* This is needed to be able to use the macros, IS_CLONE */
inherit M_FILE

string namer();

void
create_krynn_monster()
{
    int i;
    string name, *word;

    set_name("donkey");
    set_living_name("donkey");
    name = namer();
    set_short(name);
    word = explode(name, " ");
    set_adj(word[0]);
    set_long("This little animal has obviously not seen pastures and green " +
	     "grass in a long time, but the gnomes take good care of it " +
	     "when the automatic feeder is broken down.\n");
    set_race_name("donkey");

    if (!IS_CLONE) /* Added by Nick, to get rid of some possible errors. */
	return;

    set_gender(2);
    add_act("emote looks about nervously.");
    add_act("emote balks as the gnomes try to get it back to the wheel.");
    set_act_time(10);
    for (i = 0; i < 6; i++)
      set_base_stat(i, 10 + random(5));
    set_alignment(100);
    set_hp(10000);

    set_tell_active(1);
    trig_new("%s 'kicks' 'you' %s", "kick_back");
    trig_new("%s 'tickles' 'you' %s", "kick_back");
    trig_new("%s 'pokes' 'you' %s", "kick_back");
}

void
kick_back(string str1, string str2)
{
   set_alarm(3.0, -1.0, "kick_back_2", str1);
}

void
kick_back_2(string str1)
{
   
   command("kick " + lower_case(str1));
   command("emote barks joyfully.");
}

string
namer()
{
    string *desc1, *desc2;
    string name;
    int a, b;
    
    desc1 = ({ "small", "restless", "fat", "tired", "scruffy" });
    desc2 = ({"grey", "white-nosed", "friendly", "braying" });
    a = random(4);
    b = random(4);
    name = desc1[a] + " " + desc2[b] + " donkey";
    return name;
}
public void
attacked_by(object ob)
{
    string exit;
    
    tell_room(E(TO), "The donkey brays loudly in fear!\n");
    exit = E(TO)->wayout();
    command(exit);
}

