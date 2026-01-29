/*
 *  /d/Gondor/morgul/city/mm_stables/obj/steed.c
 *
 *  The steed for the stables of Minas Morgul.
 *
 *  Deagol, August 2002
 */

inherit "/d/Genesis/steed/new/steed";
inherit "/std/act/action";
inherit "/std/act/chat";
inherit "/lib/commands";

#include <adverbs.h>
#include <const.h>
#include <macros.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "../mm_stables.h"
#include "/d/Genesis/steed/new/steed.h"
//#include "/d/Terel/calathin/npc/terel_horse_saddlebag.c"

string	text;
int	Hgallop;
string	emote;

void	add_acts();
string	long_desc();
string	rider_description();
void	pet_horse(object who, string emote);
int	hgallop(string str);
int	check_attack();

void
create_steed()
{
    setuid();
    seteuid(getuid());

    set_name(({"horse", "steed"}));
    set_pname(({"horses", "steeds"}));
    add_name("_steed_");
    set_adj(({"large", "black"}));
    set_gender(G_NEUTER);
    
    set_stats(({180, 150, 250, 40, 40, 150}));
    set_skill(SS_CLIMB, 30);
    set_skill(SS_UNARM_COMBAT, 75);
    set_skill(SS_DEFENCE, 70);
    set_skill(SS_SWIM, 40);
    set_skill(SS_AWARENESS, 40);

    set_short("large black horse");
    set_long(&long_desc());

    set_m_in("comes galloping in");
    set_m_out("gallops");
    
    add_prop(OBJ_M_NO_ATTACK, check_attack);
    add_prop(CONT_I_WEIGHT, 560000);
    
    set_alignment(-300);
    
    set_rider_object_file(MM_STABLES_OBJ_DIR + "mm_rider_object");
    set_leader_object_file(MM_STABLES_OBJ_DIR + "mm_leader_object");
    set_rider_shadow_file(MM_STABLES_OBJ_DIR + "rider_shadow");

    set_allowed_food(({"oats", "apple", "hay"}));
    
    allow_mounted_combat(1);
    set_no_trans(1);
    set_max_riders(2);
    set_stuffed(TO->query_prop(LIVE_I_MAX_EAT));

    add_item(({"rider", "black rider"}), rider_description);

    add_acts();
}

string
long_desc()
{   
    string text = "This is a large black horse, with a strong neck " +
                  "standing straight up to the crest. Its wide chest " +
                  "and broad haunches are covered by a black " +
                  "caparison. The heavy cloth ends just above the " +
                  "horse's thick hooves, which seem to have been shod " +
                  "with sharp, protruding nail heads.";
                  
    if ((TO->query_leader() == TP) ||
        (TO->query_driver() == TP))
    {
        return text + " Do 'hhelp' to see emotes and commands.\n";
//                      "Do 'hhelp saddlebag' to see how you can use " +
//                      "a saddlebag.\n";
    }
    return text + "\n";
}

string
rider_description()
{
    object rider = TO->query_driver();
    
    if (!rider)
    {
        return "You find no rider.\n";
    }
    return rider->long();
}

int
check_attack()
{
    if (TP->query_npc())
    {
        return 1;
    }
    return 0;
}

/*
 * Function name: query_gallop
 * Description  : Returns whether we are galloping or not.
 * Returns      : int 1/0 - if true, we gallop, otherwise not.
 */
int
query_gallop()
{
    return Hgallop;
}

int
hgallop(string str)
{   
    if ((TO->query_driver())->query_name() != TP->query_name())
    {   
        return 0;
    }
    if (str != "on" && str != "off")
    {   
        notify_fail("hgallop on/off?\n");
        return 0;
    }
    if (str == "on")
    {
        Hgallop = 1;
        write("Your horse will gallop from now.\n");
        query_driver()->steed_is_updated();
        return 1;
    }
    if (str == "off")
    {
        Hgallop = 0;
        write("Your horse will not gallop from now.\n");
        query_driver()->steed_is_updated();
        return 1;
    }
}

/*
 * Function name: query_rider_m_in
 * Description  : Routine to modify the m_in of the rider. Since the person
 *                is mounted, we need to give him the mounted messages. The
 *                horse itself is described in the name or nonmet description
 *                of the player in the rider_shadow.c so we don't have to do
 *                that here anymore. We do take into account whether the horse
 *                is galloping or not.
 * Arguments    : object rider - the player for whom to give the message.
 * Returns      : string - the m_in text.
 */
public string
query_rider_m_in(object rider)
{
    return (Hgallop ? "charges" : "rides") + " in";
//     if (!Hgallop)
//     {
//        return "arrives on " + LANG_ADDART(steed_short());
//     }
//     return "charges in on " + LANG_ADDART(steed_short());
}

/*
 * Function name: query_rider_m_out
 * Description  : Routine to modify the m_out of the rider. Since the person
 *                is mounted, we need to give him the mounted messages. The
 *                horse itself is described in the name or nonmet description
 *                of the player in the rider_shadow.c so we don't have to do
 *                that here anymore. We do take into account whether the horse
 *                is galloping or not.
 * Arguments    : object rider - the player for whom to give the message.
 * Returns      : string - the m_out text.
 */
public string
query_rider_m_out(object rider)
{   
    return (Hgallop ? "charges" : "rides");
//    if (!Hgallop)
//    {
//        return "rides " + rider->query_possessive() + " " + steed_short();
//    }
//    return "charges " + rider->query_possessive() + " " + steed_short();
//    write(Hgallop + "in set_m_in 2\n");
}

void
add_acts()
{
    set_act_time(5);
    add_act("emote suddenly snorts, and tosses " + POSSESSIVE(TO) + " mane.");
    add_act("emote swings " + POSSESSIVE(TO) + " tail to the side, " +
            "slapping " + POSSESSIVE(TO) + " flank.");
    add_act("emote stomps " + POSSESSIVE(TO) + " hoof on the ground, " +
            "neighing softly.");
    add_act("emote lowers " + POSSESSIVE(TO) + " head, tossing " +
            POSSESSIVE(TO) + " mane from one side to the other.");
    add_act("emote throws back " + POSSESSIVE(TO) + 
            " head and whinnies loudly.");
    add_act("emote shifts " + POSSESSIVE(TO) + " great weight slightly, " +
            "the powerful muscles rippling beneath "+POSSESSIVE(TO)+" hair.");
    add_act("emote tosses " + POSSESSIVE(TO) + " head around and snorts " +
            "violently.");
}

public void
emote_hook(string emote, object actor, string adverb, object *oblist,
    int cmd_attr = 0, int target = 0)
{
    /* Don't react if we aren't the target of the emote. */
    if (!target)
    {
        return;
    }
    if (!interactive(actor))
    {
        return;
    }

    switch(emote)
    {
    case "pet":
    case "touch":
    case "snuggle":
    case "scratch":
    case "fondle":
    case "pat":
        set_alarm(1.5, 0.0, &pet_horse(TP, emote));
    default:
        break;
    }
}

void
pet_horse(object who, string emote)
{
    if (IS_MORGUL_MAGE(who))
    {
        return;
    }
    write("The " + short() + " swiftly moves its head as you carelessly " +
          "reach out with the intent to " + emote + " it, and bites you!\n");
    say("The " + short() + " swiftly moves its head as " + QTNAME(who) +
        " carelessly reaches out with the intent to " + emote + " it, and " +
        "bites " + OBJECTIVE(who) + "!\n");
    return;
}

public varargs string 
short_old(object for_obj)
{
    return steed_short(for_obj);
}

public varargs string
short(object for_obj)
{
    /* If no riders return the original short desc of the horse. */
    if (!has_riders)
    {
        return steed_short(for_obj);
    }
    if (!objectp(for_obj))
    {
        for_obj = this_player();
    }
    /* If the person hasn't met us yet, he sees a black rider. */
    if (!for_obj->query_met(query_driver()))
    {
        return "black rider";
    }
    /* If the person knows the rider, see the name and description of the
     * horse. */
    return steed_short(for_obj) + " with " + composite_riders(for_obj) +
        " riding on " + query_objective();
}

public int
can_mount(object rider)
{
    if (rider->query_skill(SS_ANI_HANDL) < 20)
    {
        return STEED_STS_SKILL_TOO_LOW;
    }
    return STEED_STS_OK;
}

void
init_living()
{
//    add_action("do_fill", "fill");
//    add_action("do_empty","empty");
//    add_action("do_drape", "drape");
//    add_action("do_remove","remove");
//    add_action("do_close", "close");
//    add_action("do_open", "open");

    ::init_living();
}
