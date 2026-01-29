// file name:        captain.c
// creator(s):       Ilyian
// revision history: Denis, May'97: Obsolete code update.
//           Lilith, Feb 2022: added ogre reaction.
// purpose:          Captain for the Dead barge...
// note:             
// bug(s):           
// to-do:            

#include <ss_types.h>
#include "../deadship.h"

inherit "/d/Genesis/ship/captain";

int alarm_id = 0;

/* Protos   */
void react_climb();
void climb_me();

void
create_captain()
{
    if (!IS_CLONE)
        return;
    set_name("omi");
    add_name("captain");
    set_title("Divider of the Waters");
    set_living_name("omi");
    set_race_name("human");
    set_adj(({"withered", "ashen-faced"}));
    set_stats(({ 80, 60, 90, 80, 60, 70 }));
    set_skill(SS_SWIM, 100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENCE,75);
    set_skill(SS_PARRY,75);
    set_skill(SS_AWARENESS,50);

    add_prop(DEAD_ENABLE,1);

    set_long("Draped in a swadling grey robe, this "
            +"bent man glares searchingly for "
            +"something just beyond perception.\n"
            +"There is the taint of death in his eyes.\n");

    set_alignment(-100);
    set_appearance(1);

    set_act_time(5);
    add_act("moan gently");
    add_act("scowl horowitz");
    add_act("pat horowitz");
    add_act("point coffin");
    add_act("emote sighs very softly.");
    add_act("growl .");
    add_act("emote looks up at the Source.");


   add_ask(({"where","where to","from"}),
             "say We go to meet the Dead.",1);
   add_ask(({"dead","isle","Dead"}),
             "say You will see. Soon.",1);

   trig_new("%s 'climbs' %s", "climb_me");
}

void
climb_me()
{
    set_alarm(itof(random(3)), 0.0, react_climb);
}

static void
react_climb()
{
    command("gasp");
    command("emote rasps: The dead are rising before their time.");
}

static void
react_intro()
{
    command("say Leave me be.");
}

public void
add_introduced(string str)
{
    set_alarm(itof(random(5) + 1), 0.0, &react_intro());
}

public void
arm_me()
{
    seteuid(getuid());
    clone_object(DEAD_DIR + "obj/robes")->move(this_object(),1);
    command("wear all");
    return;
}

int
special_attack(object victim)
{
    if (random(2))
	return 0; /* normal attack */

    switch (random(2))
    {
    case 0:
        tell_room(ENV(TO), QCTNAME(TO) + " narrows his eyes slightly.\n");
        victim->add_panic(5000);
        break;
    case 1:
        tell_room(ENV(TO), QCTNAME(TO) + " brings something up to his lips.\n");
        heal_hp(200 + random(70));
    }
    return 1;
}

void
do_ogre(object player)
{
    command("emote blinks in astonishment.");
    command("shout An ogre? An ogre! How did an ogre make it to "+
	    "the islands!!??");	
    command("say Oh! Oh I see. You're one of those surface ogres. Whew!");
    command("say You'll get an interesting reception from Mascarvin, "+
        "that's for certain.");	
}


void
init_living()
{
    ::init_living();

    if (alarm_id)
        return;
    if (this_player()->query_race_name() == "ogre") 
       alarm_id = set_alarm(itof(random(4) + 1), 0.0, 
           &do_ogre(this_player()));
}  
