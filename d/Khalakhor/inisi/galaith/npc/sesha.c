/*********************************************************************
 * - sesha.c                                                       - *
 * - Created by Damaris 3/2003                                     - *
 *********************************************************************/
#pragma strict_types
#include "/d/Khalakhor/sys/defs.h"

#include <language.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <const.h>   // for G_FEMALE
#include <macros.h>  // for OB_NAME
#include <files.h>
#include <std.h>
#include "defs.h"

inherit "/d/Khalakhor/std/npc/elf";
inherit "/d/Khalakhor/lib/gks/knowledge_base";
inherit "/d/Khalakhor/se_speir/port/npc/help_me";

static mapping remembered = ([]), failed = ([]);
#define TIQRN        this_interactive()->query_real_name()
void
create_khalakhor_elf()
{
    set_name("sesha");
    set_title("Alinau, Elven wood nymph of the Aiur, the pub owner");
    add_name(({"pubowner","keeper", "woman", "nymph", "wood nymph"}));
    set_race_name("elven wood nymph");
    set_gender(G_FEMALE);
    add_adj(({"youthful", "delicate"}));
    set_long("She is serving food and drink.\n" +
      "Her hair is hip length, soft brown and windswept.\n" +
      "She has soft brown skin.\n" +
      "She has lustrous deep brown eyes.\n" +
      "She has the pointed ears and the aura of an elven wood nymph.\n");

    set_all_hitloc_unarmed(50);
    set_stats(({70,70,70,70,70}));
    add_prop(CONT_I_WEIGHT,48000);
    add_prop(CONT_I_HEIGHT,190);
    clone_object(ARM + "dress")->move(TO);
    clone_object(ARM + "cloak")->move(TO);
    clone_object(ARM + "slippers2")->move(TO);
    command("wear all");

  
    set_appearance_offset(-150);
    set_alignment(1200);
    set_mm_in("arrives brushing pine needles from her hair.");
    MONEY_MAKE_SC(random(40))->move(this_object());
    set_act_time(15);
    add_act("ponder");
    add_act("smile secret");
    add_act("smile thought");
    add_act("whistle");
    add_act("yawn");
    add_act("emote delicately runs her fingers along her neck.");
    add_act("emote hums an ancient elven tune.");
   
    add_ask(({"undead"}),
      "say A word of warning the undead are closer than you realize.", 1);
    add_ask(({"elves", "elf"}),
      "say Elves? Yes I have seen some elves in my day.", 1);
    add_ask(({"human", "humans"}),
      "say I know quite a few.", 1);
    add_ask(({"goblin", "goblins"}),
      "say Goblins! Heh.. they are always lurking somewhere.", 1);
    add_ask(({"galaith"}),
      "say Galaith is still under such duress, but we don't "+
      "speak about it.", 1);
    add_ask(({"help"}),
      "say I could always use a bit of help, but not today.",1);
    add_ask(({"task"}),
      "say I have no tasks for you to do.", 1);
    add_ask(({"quest"}), 
      "say Ahh now there is something me wish me could do, and that "+
      "be a quest. If only me could go off and discover something "+
      "but me Pub keeps me very busy.", 1);
    add_ask(({"dwarf", "dwarves"}),
      "say I do not see as many dwarves as I used to. They prefer "+
      "to stay away.", 1);
    add_ask(({"hobbit", "hobbits"}),
      "say Hobbits! Yes yes, I've seen one or two.", 1);
    add_ask(({"minotaur", "minotaurs"}),
      "say Heh, Minotaur? You mean those creatures that look "+
      "like cows?", 1);
    add_ask(({"gnome", "gnomes"}),
      "emote laughs heartily as she replies: You must keep all eyes on "+
      "them. Always with a new fool invention. If "+
      "you don't watch out they will blow you up!", 1); 
}
/*********************************************************************
 * - Function name: hook_return_intro                              - *
 * - Description  : Called when someone introduces themselves.     - *
 * - Arguments    : str - Name of the player introducing.          - *
 * - Returns      : 1                                              - *
 *********************************************************************/
public int
hook_return_intro(string str)
{
   if (SECURITY->query_wiz_rank(TIQRN) >= WIZ_ARCH)
    {
        command("asay devoted Blessed be my soul!");
        present(str, environment(TO))->add_introduced("sesha");
        command("kneel " + str);
        command("asay devoted Greetings to thee most honoured, "+
          "" + capitalize(str) + ". I am " + query_name() + " "+
          "" + query_title() + ", and thy humble servant always.");
        command("asay devoted Ask anything of me and I shall do "+
            "my best to complete it and all I ask in "+
            "return is allow my devotion to you.");

        remembered[str] = "nice";

    }  
   else if (SECURITY->query_wiz_rank(TIQRN, "Khalakhor"))
    {
        command("asay devoted Greetings! Ohh great, " + capitalize(str) +
          ". I am " + query_name() + " " + query_title() + 
          ". I'm so happy that you have graced me with your pressence. "+
          "How might me serve you? A nice mug of hot buttered rum or "+
          "perhaps you are hungry for some a flakey cream scone?");
        command("asay worriedly I only ask that you not put me on the "+
          "racks again.");
        present(str, environment(TO))->add_introduced("sesha");
        command("kneel " + str);
        remembered[str] = "nice";

    }  
 
    else if (!remembered[str])
    {
        command("say Heya, " + capitalize(str) +
            ", I am " + query_name() + " " + query_title() + 
            ". A pleasure to meet you.");
        present(str, environment(TO))->add_introduced("sesha");
        command("bow " + str);
        remembered[str] = "nice";

    }
    else if (remembered[str] == "bad")
    {
        command("growl sof");
        command("say I remember you perfectly, so best be on your way!");
    }
    else
    {
        command("emote beams with pleasure.");
        command("say Hey I remember you, " + capitalize(str) + ". How "+
          "could I ever forget you. Will you be wanting to try some "+
          "hot buttered rum today?");
        command("bow " +str);
        command("say I do hope you have been well, and enjoying our "+
          "lovely isle?");
    }
    return 1;
}
public void
add_introduced(string who)
{
    kb_add_introduced(who);
}

public void
init_living()
{
    ::init_living();
    kb_init_living();
}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    kb_enter_env(to, from);
}
