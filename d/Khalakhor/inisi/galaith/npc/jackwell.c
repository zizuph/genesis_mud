/*********************************************************************
 * - jackwell.c                                                    - *
 * - Shopkeeper                                                    - *
 * - Created by Damaris 1/2002                                     - *
 *********************************************************************/
#pragma strict_types
#include "/d/Khalakhor/sys/defs.h"

#include <language.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <const.h>   // for G_MALE
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
    set_name("jackwell");
    set_title("Sillaith from the House of Sillaith, the weapons dealer");
    add_name(({"shopkeeper","keeper", "man"}));
    set_race_name("elf");
    set_gender(G_MALE);
    add_adj(({"broad-shouldered", "muscular"}));
    set_long("He is a weapons dealer and shopkeeper.\n"+
      "He has gentle eyes.\n"+
      "He has smooth dark skin.\n"+
      "His hair is shoulder length, soft black and tied back.\n"+
      "He has the distinguished mark of the mystic vine of the Eil-Galaith.\n"+
      "He wears the silver and sable colours from the elven House of "+
      "Sillaith.\n"+
      "He has small beads of persperation along his soft brow.\n");
    set_all_hitloc_unarmed(50);
    set_stats(({70,70,70,70,70}));
    clone_object(ARM + "shirt1")->move(TO);
    clone_object(ARM + "pants2")->move(TO);
    clone_object(ARM + "boots")->move(TO);
    command("wear all");

    add_prop(CONT_I_WEIGHT,48000);
    add_prop(CONT_I_HEIGHT,190);
    add_prop(NPC_I_NO_RUN_AWAY,1);
    set_alignment(100);
    set_mm_in("arrives from the storeroom grumbling.");
    MONEY_MAKE_SC(random(40))->move(this_object());
    set_act_time(15);
    set_act_time(15);
    add_act("ponder");
    add_act("smile elvish");
    add_act("whistle elvish");
    add_act("emote hums an elvish tune.");
    add_act("emote refastens his hair tie more firmly.");
    add_act("emote pulls out a sword from a storage bin and begins "+
      "to polish it.");
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
        present(str, environment(TO))->add_introduced("jackwell");
        command("kneel " + str);
        command("asay devoted Greetings to thee, " + capitalize(str) +
            ". I am " + query_name() + " " + query_title() + 
            ", thy humble servant.");
        command("asay devoted Ask anything of me and I shall do "+
            "my best to please thee.");

        remembered[str] = "nice";

    }  
   else if (SECURITY->query_wiz_rank(TIQRN, "Khalakhor"))
    {
        command("asay devoted Greetings to thee, " + capitalize(str) +
            ". I am " + query_name() + " " + query_title() + 
            ". I am most pleased that thee hath graced me with thy pressence. "+
            "How may I serve thee? A new dagger or perhaps thee would "+
            "prefer something else?");
        present(str, environment(TO))->add_introduced("jackwell");
        command("kneel " + str);
        remembered[str] = "nice";

    }  
 
    else if (!remembered[str])
    {
        command("say Greetings to thee, " + capitalize(str) +
            ", I am " + query_name() + " " + query_title() + 
            ". A pleasure to make thy acquaintance.");
        present(str, environment(TO))->add_introduced("jackwell");
        command("bow quiet " + str);
        remembered[str] = "nice";

    }
    else if (remembered[str] == "bad")
    {
        command("growl sof");
        command("say I remember thou very well. So be on thy way!");
    }
    else
    {
        command("emote beams with pleasure.");
        command("say I remember thee very well from thy " +
          "last visit, " + capitalize(str) + ". How could I "+
          "ever forget thee.");
        command("curtsey " +str);
        command("say I hope thou art faring well, and enjoying our "+
          "fine city?");
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
