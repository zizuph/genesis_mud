/*********************************************************************
 * - milith.c                                                      - *
 * - Shopkeeper                                                    - *
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
    set_name("milith");
    set_title("Silith from the House of Silith, shopkeeper");
    add_name(({"shopkeeper","keeper", "woman"}));
    set_race_name("half-elf");
    set_gender(G_FEMALE);
    add_adj(({"tall", "slender"}));
    set_long("She is a shopkeeper.\n"+
      "She has soft grey eyes.\n"+
      "She has smooth light skin.\n"+
      "Her hair is shoulder length, black with grey streaks along the "+
      "temples and pulled up into a nicely shaped bun atop her head.\n"+
      "She has soft pointed ears.\n"+
      "She has the distinguished mark of the mystic vine of the Eil-Galaith.\n"+
      "She wears the pearl and hyacinth colours from the elven House of "+
      "Silith.\n");
    set_all_hitloc_unarmed(50);
    set_stats(({70,70,70,70,70}));
    clone_object(ARM + "dress")->move(TO);
    clone_object(ARM + "cloak2")->move(TO);
    clone_object(ARM + "slippers")->move(TO);
    command("wear all");    
    add_prop(CONT_I_WEIGHT,48000);
    add_prop(CONT_I_HEIGHT,190);
    add_prop(NPC_I_NO_RUN_AWAY,1);
    set_alignment(100);
    set_mm_in("arrives from the storeroom.");
    MONEY_MAKE_SC(random(40))->move(this_object());
    set_act_time(15);
    set_act_time(15);
    add_act("ponder");
    add_act("smile elvish");
    add_act("whistle elvish");
    add_act("emote hums an elven tune.");
    add_act("emote dusts a crystal oil lamp.");
    add_act("emote inspects a leather pack then returns it to a shelf.");
    add_act("emote presses a few stray hairs back into her nicely shaped "+
      "bun.\n");
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
        present(str, environment(TO))->add_introduced("milith");
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
            ". I am most pleased that thee has graced me with thy pressence. "+
            "How may I serve thee, a new cloak or perhaps you would "+
            "prefer a cape?");
        present(str, environment(TO))->add_introduced("milith");
        command("kneel " + str);
        remembered[str] = "nice";

    }  
 
    else if (!remembered[str])
    {
        command("say Greetings to thee, " + capitalize(str) +
            ", I am " + query_name() + " " + query_title() + 
            ". A pleasure to make thy acquaintance.");
        present(str, environment(TO))->add_introduced("milith");
        command("curtsey " + str);
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
        command("bow " +str);
        command("say I hope thou art faring well, and enjoying our "+
          "fine isle?");
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
