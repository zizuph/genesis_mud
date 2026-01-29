/* Deldin- Shopkeeper
 * Shopkeeper
 * Created by Damaris 11/2001
 */
# pragma strict_types
#include "/d/Raumdor/defs.h"
#include "../guild.h"
# include <language.h>
# include <money.h>
# include <ss_types.h>
# include <stdproperties.h>
#include <const.h>   // for G_FEMALE
#include <macros.h>  // for OB_NAME
#include <files.h>
#include <std.h>

#include "/d/Raumdor/common/drakmere/npc/npc.h"
inherit "/std/monster";
inherit HELP_ME;
inherit RANDOM;
static mapping remembered = ([]), failed = ([]);
#define TIQRN        this_interactive()->query_real_name()
void
create_monster()
{
    set_name("deldin");
    set_title("the shopkeeper and servant of Kuhl de Van");
    add_name(({"shopkeeper","keeper", "man"}));
    set_race_name("human");
    set_gender(G_MALE);
    add_adj(({"grinning", "well-dressed"}));
    set_long("He is a master weaver of fine cloths and shopkeeper.\n"+
      "He has sparkling grey eyes.\n"+
      "He has smooth pale skin.\n"+
      "His hair is very short, mousy brown and layered.\n"+
      "He has fabrics draped over his arms.\n");
    set_all_hitloc_unarmed(50);
    set_stats(({70,70,70,70,70}));
    add_prop(CONT_I_WEIGHT,48000);
    add_prop(CONT_I_HEIGHT,190);
  
    set_alignment(100);
    set_mm_in("arrives.");
    MONEY_MAKE_SC(random(40))->move(this_object());
    set_act_time(15);
    add_act("ponder");
    add_act("smile secret");
    add_act("whistle");
    add_act("emote hums a tune.");
    add_act("say Oh I do hope the Lords of drakmere will be "+
      "pleased with my new line of clothing.");
    add_act("say All my clothing is elaborately made.");
    add_act("emote moans saying: Oh how my fingers are sore this day.");
    add_act("say Have you been to the keep? I hear many changes are underway.");
    add_act("say I used to live near the graveyard until the "+
      "undead began to come. I'm so glad I moved into Drakmere "+
      "where it is safer.");
    add_ask(({"undead"}),
      "say You had better just watch thy step they might hear and seek you out.", 1);
    add_ask(({"elves", "elf"}),
      "say Ahh yes, elves. I've not known too many personally, but "+
      "I've fitted a few.", 1);
    add_ask(({"human", "humans"}),
      "say I know quite a few. Drakmere's population is of humans. I "+
      "used to be head tailor for the Nobles of Raumdor.", 1);
    add_ask(({"goblin", "goblins"}),
      "say Goblins! May Drakin help us all if any show up here.", 1);
    add_ask(({"drakmere"}),
      "say Drakmere is still under such duress. A fine city it is "+
      "though, but not as it was.", 1);
    add_ask(({"help"}),
      "say I could always use a bit of help, but not today.",1);
    add_ask(({"task"}),
      "say I have no tasks for you to do.", 1);
    add_ask(({"quest"}),      "say Ahh now there is something I wish I could do, and that is a quest. If only I could go off and discover something.", 1);
    add_ask(({"dwarf", "dwarves"}),
      "say I've had to fit dwarves before. Not an easy fit at times. "+
      "Their shoulders are quite differently proportioned.", 1);
    add_ask(({"hobbit", "hobbits"}),
      "say Hobbits! Yes yes. A wonderful lot they are, I've enjoyed "+
      "fitting them in so many dashing clothes.", 1);
    add_ask(({"minotaur", "minotaurs"}),
      "say You mean the cows? I'd not fit one if I was paid "+
      "handsomely either.", 1);
    add_ask(({"clothes", "clothing"}),
      "say I have many clothes for you to choose try to 'list' them.", 1);
    add_ask(({"cloth", "cloths", "fabric", "fabrics"}),
      "say I use only the finest fabrics in my clothing.", 1);
    add_ask(({"cloak room", "cloakroom", "shop"}),
      "say I pride myself in having an orderly shop.", 1); 
    add_ask(({"gnome", "gnomes"}),
      "emote laughs heartily as he says: I have fitted a few "+
      "after their experiments go KABOOM!", 1); 
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
        present(str, environment(TO))->add_introduced("deldin");
        command("kneel " + str);
        command("asay devoted Greetings to thee, " + capitalize(str) +
            ". I am " + query_name() + " " + query_title() + 
            ", thy humble servant.");
        command("asay devoted Ask anything of me and I shall do "+
            "my best to please thee.");

        remembered[str] = "nice";

    }  
   else if (SECURITY->query_wiz_rank(TIQRN, "Raumdor"))
    {
        command("asay devoted Greetings to thee, " + capitalize(str) +
            ". I am " + query_name() + " " + query_title() + 
            ". I am most pleased that thee has graced me with thy pressence. "+
            "How may I serve thee, a new cloak or perhaps you would "+
            "prefer a cape?");
        present(str, environment(TO))->add_introduced("deldin");
        command("kneel " + str);
        remembered[str] = "nice";

    }  
 
    else if (!remembered[str])
    {
        command("say Greetings to thee, " + capitalize(str) +
            ", I am " + query_name() + " " + query_title() + 
            ". A pleasure to make thy acquaintance.");
        present(str, environment(TO))->add_introduced("deldin");
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
        command("curtsey " +str);
        command("say I hope thou art faring well, and enjoying our "+
          "fine city?");
    }
    return 1;
}
