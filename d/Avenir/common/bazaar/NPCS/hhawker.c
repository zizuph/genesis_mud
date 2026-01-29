// file name:	hhawker.c
// creator(s):  Grace
// last update: Denis, May'97: Regular updates.
// purpose:     To shout about what is sold in the tent
//		Hatshop shop hawker
// note:
// bug(s):
// to-do:

# pragma strict_types

# include "/d/Avenir/common/bazaar/bazaar.h"
# include <money.h>
# include <ss_types.h>
# include <stdproperties.h>

inherit NPC + "call_for_help";
inherit "/d/Avenir/inherit/intro";

int alarm_id;

void
create_monster()
{
    set_name("blittor");
    set_title("Tipsi");
    add_name(({"hawker","peddler"}));
    set_race_name("human");
    set_gender(0);

    add_adj(({"grinning", "dark-eyed"}));
    set_long("This young human seems to like yelling at the "+
	     "top of his voice. He's hawking the wares of the tent"+
	     "shop nearby.\n");
    set_all_hitloc_unarmed(50);

    set_stats(({60,60,60,40,40}));

    set_skill(SS_UNARM_COMBAT,50);
    set_skill(SS_BLIND_COMBAT,100);
    set_skill(SS_PARRY,50);
    set_skill(SS_DEFENCE,65);
    set_skill(SS_AWARENESS,50);
    set_skill(SS_WEP_KNIFE,50);
   
    add_prop(NPC_I_NO_RUN_AWAY,1);
    set_mm_in("arrives.");
   
    set_act_time(5);
    add_act("shout We've got hats here!");
    add_act("shout Step inside this tent to enter the world "+
        "of high-fashion head-wear!");
    add_act("shout High-hats, berets, bonnets!");
    add_act("point tent");
    add_act("shout Get a hat like the ones the Shadow Elves wear!");
    add_act("shout Sybarite high-fashion hats made by Heboba. Right inside");

    add_ask(({"hat", "hats", "beret", "bonnet"}),
      "say Why yes, There are some in that tent over there.",1);
    add_ask("hatshop", "say Just enter the tent here,", 1);
    add_ask(({"bath", "melchior's bath"}),
      "say It is in Sybarus City, a heavenly place to wash and rest.",1);
    add_ask("sybarus",
      "say All in this cavern is Sybarus, and every island within it, though "+
      "some be called City, or Park, or Bazaar.",1);
    add_ask("city", "say It is Sybarus, the Shadow-elf City. A "+
      "wonderous place.",1);
    add_ask("massage", "say You can get one at Melchior's Bath, if you can " +
      "win passage into the City.",1);
    add_ask("park",
        ({"say Beautiful, but dangerous, that is all I'll say."}),1);
    add_ask("bazaar",
      "say You're standing in it! The commercial center of Sybarus.",1);
    add_ask(({"task", "job", "quest", "help"}),
      "say Try the Baker, or ask the gate-wardens, they might have "+
      "something for you to do.",1);
    add_ask("passage","say Ah, that must be earned. One way or another we all "+
      "strive to enter there.",1);

}

public void
arm_me()
{
   seteuid(getuid());
   MONEY_MAKE_SC(random(40))->move(this_object());

   clone_object(BAZAAR + "Obj/worn/pshirt")->move(TO, 1);
   clone_object(BAZAAR + "Obj/worn/pshoes")->move(TO, 1);
}

void
react_meet(object tp)
{
	int i;
	i= random(4);

	 alarm_id = 0;
	 if (!present(tp, environment(TO)))
		  return;
	 if(tp->query_prop("_is_cat_"))
	 {
		if(i==0)
		{
			command("emote shouts: Skat, cat!");
			return;
		}
		return;
	 }

    if ((!tp->query_met(query_real_name())))
        command("say Enter this tent for a look at some novelty junk.");
}

void
init_living()
{
    ::init_living();

    if (alarm_id)
        return;
    else
        if (interactive(this_player()))
	    alarm_id = set_alarm(3.0, 0.0, &react_meet(this_player()));
}
