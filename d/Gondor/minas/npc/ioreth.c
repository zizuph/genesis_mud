inherit "/std/monster";
#include "/sys/ss_types.h"
#include "/sys/macros.h"
int not_intro;

void
create_monster()
{
    if (!IS_CLONE)	return;
    set_name("ioreth");
    add_name("healer");
    add_name("woman");
    set_title("Herbwife of the Houses of Healing");
    set_race_name("human"); 
    set_adj(({"withered","talkative"}));
    set_gender(1);
    set_appearance(10);
    set_pshort("healers of Gondor");
    set_long(break_string(
      "A wrinkled prune of a woman, bent about her tasks " +
      "as a woman of healing. Her deep-lined face tells of " +
      "long years of hardship and battle-worn life. \n", 75));
    set_stats(({15+random(20),15+random(20),15+random(20), 
                20+random(10), 20+random(20), 5+random(25)}));
    set_hp(1100);
    set_alignment(150);
    set_skill(SS_WEP_KNIFE,20 + random(20));
    set_skill(SS_DEFENCE,20 + random(20));
    set_skill(SS_PARRY,20 + random(20));
    set_skill(SS_AWARENESS,20 + random(20));

    set_chat_time(10);
    add_chat("My sister and I found some kingsfoil. I wonder why 'tis called so. If I were king, I'd have plants more bright in my garden.");
    add_chat("I hope those murdering devils do not come to this House and trouble the sick.");
    add_chat("It is said in the old lore, 'The hands of the king are the hands of a healer.' Thus the king could ever be known.");
    add_chat("I fear that there will be greater war soon!");
    add_chat("Would that there were kings in Gondor, as there were once upon a time, they say!");
    add_chat("I can't say as to what will be happening, I am sure, but it should hurry up and happen, and be done!");

    set_act_time(13);
    add_act("emote shuffles about, tending her patients.");
    add_act("emote sniffs and mumbles under her breath.");
    add_act("emote straightens some spare bottles and tools.");
    add_act("emote busies herself with linens.");
    add_act("smile warmly");

    set_cchat_time(7);
    add_cchat("Ay! Let me be!");
    add_cchat("You murdering devil! Leave the sick to rest!");
    add_cchat("Leave a body to peace!");
    
    set_cact_time(9);
    add_cact("scream");
    add_cact("shout Won't no soul aid me?");
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
    wep = clone_object("/d/Gondor/common/wep/woodknife");
    wep->move(this_object());
    command("wield knife");

    arm = clone_object("/d/Gondor/minas/obj/frock");
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

