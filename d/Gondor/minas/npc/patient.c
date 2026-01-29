inherit "/std/monster";
#include "/sys/ss_types.h"
#include "/sys/macros.h"
int not_intro;

void
create_monster()
{
    if (!IS_CLONE)	return;
    set_name("Belrond");
    add_name("patient");
    add_name("man");
    set_race_name("human"); 
    set_adj(({"injured","weakened"}));
    set_appearance(10);
    set_short("charge of the Houses of Healing");
    set_pshort("charges of the Houses of Healing");
    set_long(break_string(
      "An injured warrior, beiong treated for battle wounds. " +
      "He doesn't appear to be very coherant. \n", 75));
    set_stats(({20+random(20),25+random(20),15+random(20), 
                20+random(10), 20+random(20), 10+random(25)}));
    set_hp(500);
    set_alignment(150);
    set_skill(SS_WEP_KNIFE,30 + random(20));
    set_skill(SS_DEFENCE,30 + random(20));
    set_skill(SS_PARRY,30 + random(20));
    set_skill(SS_AWARENESS,30 + random(20));

    set_chat_time(20);
    add_chat("What? No. I. . . what?");
    add_chat("Mirabel! No. . . of course it isn't.");
    
    set_act_time(10);
    add_act("emote groans and winces.");
    add_act("emote turns restlessly, but cries out in pain.");
    add_act("emote murmurs incoherently.");
    add_act("emote grimaces, breaking out into a sweat on his brow.");
    add_act("emote sighs with the pain.");

    set_cchat_time(7);
    add_cchat("What's this? Oh! No, no, no!");
    
    set_cact_time(9);
    add_cact("shout No! Oh! Warden!");
    add_cact("emote tries to defend himself.");
    add_cact("shout Help me! Someone!");

    seq_new("do_things");
    seq_addfirst("do_things",({"@@arm_me"}));

    trig_new("%w 'introduces' %s", "react_introduce");
  }

void
arm_me()
{
    object wep, arm;

    seteuid(getuid(this_object()));
    wep = clone_object("/d/Gondor/common/wep/knife");
    wep->move(this_object());
    command("wield knife");

    arm = clone_object("/d/Gondor/minas/obj/ltunic");
    arm->move(this_object());
    command("wear all");

    arm = clone_object("/d/Gondor/minas/obj/ctrousers");
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
       command("say What. . . no. . . I. . .");
       command("emote rolls over, winces, and passes out.");
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

