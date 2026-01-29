inherit "/std/monster";
#include "/sys/ss_types.h"
#include "/sys/macros.h"
int not_intro;

void
create_monster()
{
    if (!IS_CLONE)	return;
    set_name("Hador");
    add_name("herbmaster");
    add_name("man");
    set_title("Herbmaster of the Houses of Healing");
    set_race_name("human"); 
    set_adj(({"demure","learned"}));
    set_appearance(30);
    set_short("Herbmaster of Gondor");
    set_pshort("herbmasters of Gondor");
    set_long(break_string(
      "A gaunt man, with long, thin fingers and a sharp nose. He " +
      "has an air of a scholar about him. \n", 75));
    set_stats(({20+random(20),25+random(20),15+random(20), 
                30+random(10), 20+random(20), 10+random(25)}));
    set_hp(2000);
    set_alignment(250);
    set_skill(SS_WEP_KNIFE,30 + random(20));
    set_skill(SS_DEFENCE,30 + random(20));
    set_skill(SS_PARRY,30 + random(20));
    set_skill(SS_AWARENESS,30 + random(20));

    set_chat_time(20);
    add_chat("I cannot think of any use for kingsfoil, as the rustics call athelas. It only seems to freshen foul air.");
    add_chat("Are you here to visit a patient?");
    add_chat("The old wives, like Ioreth, repeat the old rhymes without understanding.");
    add_chat("I doubt that galenas, or westmansweed as the rustics call it, has any virtue at all. We have none in the Houses of Healing.");
    add_chat("Herblore is my craft. I am in charge of all the herbs here at the Houses of Healing.");
    add_chat("Old wives often garble old herblore.");

    set_act_time(13);
    add_act("nod");
    add_act("emote examines an herb with care.");
    add_act("emote straightens his glasses.");
    add_act("emote checks herblore tome.");
    add_act("sigh");

    set_cchat_time(7);
    add_cchat("What's this? Get out!");
    add_cchat("Begone, you devil!");
    add_cchat("Leave this old man in peace!");
    
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

