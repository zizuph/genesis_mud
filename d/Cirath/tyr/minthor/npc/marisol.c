inherit "/std/monster";
#include "/d/Cirath/common/defs.h"
#include "/d/Cirath/common/introfnc.h"
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>

create_monster()
{
   set_name("marisol");
   set_title("Minthor, Eldest Daughter of the Minthor Clan");
   set_race_name("human");
   set_adj("rich");
   add_adj("spoiled");
   set_gender(1);
   set_short("rich spoiled female human");
   set_long("This young human looks to be one of the daughters of "
	+"Lord Minthor.  She is very nice to look at, but seems very "
	+"spoiled and dominating.  Sometimes the wealthy are the most "
	+"corrupt, you should probably watch your step around her.\n");

   set_alignment(-100);
   set_stats(({40,50,50,55,55,50}));
   set_skill(SS_UNARM_COMBAT,30);
   set_skill(SS_DEFENCE,40);
   set_skill(SS_AWARENESS,20);
   set_act_time(3);
   add_act("say What the hell are you doing in my room?");
   add_act("say My father will cut your eyes out for being here.");
   add_act("say How dare you come in here!!");
   add_act("emote grins devilishly");
   set_cact_time(6);
   add_cact("say You have just signed your own death warrant");
   add_cact("say Get your filthy hands off me!");
   add_cact("emote shrieks in terror.");
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_ask("mother","Its so sad she was murdered.  I don't know "
	+"what I'll do!\n");
   add_ask("bracelet","Yes, mother had a very nice bracelet, she "
	+"never took it off.  It is a priceless family heirloom "
	+"and now its gone!\n");
  add_ask(({"murder","assassination","assassin"}),
   "@@ask_murder");
  add_ask("mother","@@ask_minthor");
   add_ask(({"initials","mm","MM"}),"@@ask_initials");

   set_default_answer("I don't know anything about that.\n");

 
}

void
arm_me()
{
   MONEY_MAKE_SC(random(100))->move(TO, 1);
}


ask_murder()
{
    command("say Its been so hard since Mother was killed. "
   	+"Who would want to kill her?  It makes no sense! Some "
	+"dirty assassin snuck into our house somehow and killed "
	+"her.\n");
   command("emote gets a resigned look on her face.");
   command("say I guess I will have to be the acting lady of the "
	+"house.  Father is getting old amd can't handle things as "
	+"well anymore.\n");
   return ">";

}

ask_mother()
{
   command("say She was a good woman, this is a tragedy!  Her "
	+"death will be avenged!  I will use all of the resources "
	+"of our noble house to find the assassin and have him "
	+"punished.\n");
   command("emote stares off into the distance.");
   command("say Have you found any clues yet?  I will pay you for "
	+"information!  I just want this handled quickly and "
	+"quietly.\n");
   return ">";
}

ask_initials()
{
   command("say My initials?\n");
   command("hmm");
   command("say My initials are MM.  Have you found the person "
	+"responsible's initials or name somewhere?\n");
   command("emote begins to sniffle.");
   command("cry");
   command("say I'm so sorry.  I didn't think it would be this way! "
	+"It all just moved so fast!  I did it!  I paid him to kill "
	+"her.  Her bracelet is hidden in my room.  I'm so sorry.\n");
   command("sob");
   command("say Don't tell father, he doesn't need to know.  Please?\n");
   command("emote turns and runs.\n");
   command("northwest");
    return ">";
}


