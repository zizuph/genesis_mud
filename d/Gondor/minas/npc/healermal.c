inherit "/std/monster";
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "names.h"
int not_intro;

void
create_monster()
{
   int ranname;
    if (!IS_CLONE)	return;
   ranname = random(61);
   set_name(MALENAME[ranname]);
    add_name("healer");
    add_name("man");
    set_title("Healer of the Houses of Healing");
    set_race_name("human"); 
    set_adj(({"gentle","bearded"}));
    set_appearance(10);
    set_pshort("healers of Gondor");
    set_long(break_string(
      "A careworn man, setting about his work. His face is " +
      "lined with years, but his eyes still sparkle. \n", 75));
    set_stats(({30+random(20),30+random(20),30+random(20), 
                45+random(10), 45+random(20), 15+random(25)}));
    set_hp(3000);
    set_alignment(150);
    set_skill(SS_WEP_KNIFE,20 + random(20));
    set_skill(SS_DEFENCE,20 + random(20));
    set_skill(SS_PARRY,20 + random(20));
    set_skill(SS_AWARENESS,20 + random(20));

    set_chat_time(30);
    add_chat("I can't say I have overmuch lore, but it will do.");
    add_chat("Perhaps I should ask the herbmaster about this.");
    add_chat("Are you here to see a charge?");
    add_chat("I fear that there will be greater war soon!");
    add_chat("Would that there were kings in Gondor, as there were once upon a time, they say!");
    add_chat("What can be done?");

    set_act_time(25);
    add_act("emote shuffles about, tending his patients.");
    add_act("emote brushes the dust from the curtains.");
    add_act("emote straightens some spare bottles and tools.");
    add_act("emote busies himself with a leafy herb.");
    add_act("twinkle");

    set_cchat_time(7);
    add_cchat("Ay! Let me be!");
    add_cchat("You murdering devil!");
    add_cchat("Leave a body to peace!");
    
    set_cact_time(9);
    add_cact("scream");
    add_cact("shout Oh, no! Is there no one near?");
    add_cact("emote scuttles about the room, trying to escape.");

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

