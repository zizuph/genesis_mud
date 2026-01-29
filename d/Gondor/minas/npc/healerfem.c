inherit "/std/monster";
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "names.h"
int not_intro;
   int ranname;

void
create_monster()
{
    if (!IS_CLONE)	return;

   ranname = random(47);

   set_name(FEMALENAME[ranname]);
    add_name("healer");
    add_name("woman");
    set_title("Healer of the Houses of Healing");
    set_race_name("human"); 
    set_adj(({"young","serene"}));
    set_gender(1);
    set_appearance(30);
    set_pshort("healers of Gondor");
    set_long(break_string(
      "A sweet young healer, who must have excellent herbcraft " +
      "to be a healer so young. She appears to be absorbed in " +
      "her arts. \n", 75));
    set_stats(({20+random(20),20+random(20),20+random(20), 
                25+random(10), 25+random(20), 15+random(25)}));
    set_hp(2000);
    set_alignment(150);
    set_skill(SS_WEP_KNIFE,30 + random(20));
    set_skill(SS_DEFENCE,20 + random(20));
    set_skill(SS_PARRY,25 + random(20));
    set_skill(SS_AWARENESS,20 + random(20));

    set_chat_time(20);
    add_chat("We're near filled up with charges.");
    add_chat("Ioreth is the eldest of us. She knows a good craft.");
    add_chat("There is much to be done, and so few of us here.");
    add_chat("I fear that there will be greater war soon!");
    add_chat("I pray for the return of kings to Gondor.");
    add_chat("What shall become of our fair city?");
    add_chat("We have already been under the Enemy's attack.");

    set_act_time(13);
    add_act("emote tends her patients.");
    add_act("emote hums under her breath.");
    add_act("emote straightens some spare bottles and tools.");
    add_act("emote busies herself with linens.");
    add_act("smile calmly");
    add_act("emote sings a little tune about the Springtime.");

    set_cchat_time(7);
    add_cchat("Why do you do this?");
    add_cchat("You murdering devil! ");
    add_cchat("How can you disturb the sick?");
    
    set_cact_time(9);
    add_cact("scream");
    add_cact("shout Help me! Please help!");
    add_cact("emote breaks some bottles as she flails about!");

    seq_new("do_things");
    seq_addfirst("do_things",({"@@arm_me"}));

    trig_new("%w 'introduces' %s", "react_introduce");
  }

void
arm_me()
{
    object wep, arm;

    seteuid(getuid(this_object()));
    wep = clone_object("/d/Gondor/common/wep/ivknife");
    wep->move(this_object());
    command("wield knife");

    arm = clone_object("/d/Gondor/minas/obj/mtunic");
    arm->move(this_object());
    command("wear all");

    arm = clone_object("/d/Gondor/minas/obj/legging");
    arm->move(this_object());
    command("wear all");
}

void
react_introduce(string person, string who)
{
           if (find_call_out("introduce_me") == -1)
    call_out("my_intro", 4);
}

void 
my_intro()
{
          if(not_intro)
     return;
       command("introduce myself");
     not_intro = 1;
         if (find_call_out("re_intro") == -1)
   call_out("re_intro", 15);
}

void
re_intro()
{
       not_intro = 0;
}

/* solemnian prestige */
query_knight_prestige() {return (-5);}

