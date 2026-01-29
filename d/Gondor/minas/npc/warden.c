inherit "/std/monster";
#include "/sys/ss_types.h"
#include "/sys/macros.h"
int not_intro;

void
create_monster()
{
    if (!IS_CLONE)	return;
    set_name("Earnil");
    add_name("warden");
    add_name("man");
    set_title("Warden of the Houses of Healing");
    set_race_name("human"); 
    set_adj(({"calm","patient"}));
    set_appearance(30);
    set_short("Warden of Gondor");
    set_pshort("wardens of Gondor");
    set_long(break_string(
      "A solid-looking man, who runs the Houses of Healing. He " +
      "is responsible for all the patients here, as well as the " +
      "healers, herbmasters, and messange boys, and their " +
      "servants. \n", 75));
    set_stats(({30+random(20),30+random(20),30+random(20), 
                30+random(10), 20+random(20), 10+random(25)}));
    set_hp(2000);
    set_alignment(250);
    set_skill(SS_WEP_KNIFE,30 + random(20));
    set_skill(SS_DEFENCE,30 + random(20));
    set_skill(SS_PARRY,30 + random(20));
    set_skill(SS_AWARENESS,30 + random(20));

    set_chat_time(20);
    add_chat("Welcome to the Houses of Healing.");
    add_chat("Are you here to visit a patient?");
    add_chat("The healers are quite busy right now.");
    add_chat("We serve the greviously ill and injured here.");
    add_chat("I have many charges in my care.");
    add_chat("Some folks are tougher in fiber than others.");

    set_act_time(13);
    add_act("nod");
    add_act("emote looks over his charges with care.");
    add_act("emote looks stern, yet you feel he is gentle.");
    add_act("emote checks his patient log.");
    add_act("smile quietly");

    set_cchat_time(7);
    add_cchat("What's this? Get out!");
    add_cchat("Begone, you devil!");
    add_cchat("Leave the sick in peace!");
    
    set_cact_time(9);
    add_cact("shout Guards! Guards!");
    add_cact("emote tries to defend himself.");
    add_cact("shout Help me! Quickly!");

    seq_new("do_things");
    seq_addfirst("do_things",({"@@arm_me"}));

    trig_new("%w 'introduces' %s", "react_introduce");
  }

void
arm_me()
{
    object wep, arm;

    seteuid(getuid(this_object()));
    wep = clone_object("/d/Gondor/common/wep/woodknife");
    wep->move(this_object());
    command("wield knife");

    arm = clone_object("/d/Gondor/minas/obj/ltunic");
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

