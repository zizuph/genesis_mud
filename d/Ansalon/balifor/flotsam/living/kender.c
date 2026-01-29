/* created by Aridor 05/19/94 */

inherit "/d/Krynn/common/monster/kender_base";

#include "/ss_types.h"
#include "/d/Krynn/solamn/splains/local.h"
#include <macros.h>
inherit "/std/act/action";

void
create_kender()
{
    int i;

    switch(random(4))
    {
    case 0: set_adj("sneaky");
	break;
    case 1: set_adj("bouncy");
	break;
    case 2: set_adj("playful");
	break;
    case 3: set_adj("small");
	break;
    }

    for(i = 0; i < 6; i++)
	set_base_stat(i,random(20)+20);
    set_hp(2000);
    set_skill(SS_DEFENCE, 20 + random(10));
    set_skill(SS_PARRY, 20 + random(10));
    set_skill(SS_WEP_KNIFE, 40 + random(5));
    set_skill(SS_WEP_POLEARM, 40 + random(10));

    set_long("This kender has travelled here from the merry forests of " +
      "Kendermore, and is enjoying himself thoroughly.\n");

    set_act_time(0);
    add_act("wield hoopak");
    add_act("shoot elf with hoopak");
    add_act("emote rambles on about something his Uncle " +
      "Trapspringer has told him.");
    add_act("shoot dwarf with hoopak");
    add_act("smile");
    add_act("swing hoopak");
    add_act("shoot human with hoopak");
    add_act("shoot draconian with hoopak");
    add_act("spin hoopak");
    add_act("bounce");
    add_act("jump");
    add_act("swing hoopak");
    add_act("swing hoopak");
    add_act("shoot goblin with hoopak");
    add_act("laugh");
    add_act("giggle");
    add_act("say As soon as I have mapped this area, I'll open a "
      +  "cartographer's shop!");

    set_cact_time(10);
    add_cact("smile");
    add_cact("wield all");

    add_ask("'centaur' / 'centaurs'",VBFC_ME("centaur_hint"),1);
    add_ask("[kender] [trail] 'song'",VBFC_ME("song_hint"),1);

    if (IS_CLONE)
	set_alarm(1.0,0.0,"fill_pockets");

}

void
fill_pockets()
{
    seteuid(getuid(TO));
    my_stuff = ({});
    my_stuff += ({ clone_object(OBJ + "map")->move(TO) });
    my_stuff += ({ clone_object(OBJ + "feather")->move(TO) });
    my_stuff += ({ clone_object(OBJ + "stone")->move(TO) });
    my_stuff += ({ clone_object(OBJ + "kknife")->move(TO) });
    my_stuff += ({clone_object("/d/Ansalon/balifor/flotsam/obj/weapon/hoopak")->move(TO)});
    /* some more objects in here! and some randomness, please! */

}

string
centaur_hint()
{
    command("smile excit");
    command("say Centaurs? Sure! I know of centaurs!");
    command("say My uncle used to travel the woods around " +
      "kendermore... my uncle was an explorer you see, and " +
      "he made maps of everywhere he travelled. In fact, " +
      "he made this map of the Dairy Plains, that was stolen by " +
      "this faery dragon that had the wings of a butterfly!");
    command("say What was I saying? Oh yes, centaurs. If you " +
      "go to the forest to the west of kendermore, you " +
      "might find a few centaurs. That reminds me! I know a " +
      "great kender trail song, and it has a nifty bit about " +
      "centaurs in it! Want to hear it?");

    command("grin eager");
    return "";
}

string
song_hint()
{
    command("smile");
    command("emote starts singing a well-known kender " +
      "trail song :\n\n" +
      "     Your one true loves a sailing ship\n" +
      "     That anchors at our pier.\n" +
      "     We lift her sails, we man her decks,\n" +
      "     We scrub the portholes clear;\n\n" +
      "     And yes, our lighthouse shines for her,\n" +
      "     And yes, our shores are warm;\n" +
      "     We steer her into harbour -\n" +
      "     Any port in a storm.\n\n" +
      "     The sailors stand upon the docks,\n" +
      "     The sailors stand in line,\n" +
      "     As thirsty as a dwarf for gold\n" +
      "     Or centaurs for cheap wine.\n\n" +
      "     For all the sailors love her,\n" +
      "     And flock to where she's moored,\n" +
      "     Each man hoping that he might\n" +
      "     Go down, all hands on board.\n");
    command("giggle");
    return "";
}
