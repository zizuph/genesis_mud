/*
 * Nax Zeb, mysteriously green skinned human,
 *   keeper of the tavern at Reefcutters Jetty 
 *   "/d/Krynn/turbidus_ocean/living/reefcutter_tavernkeeper.c"
 *  (based on Tika Waylan of the Inn of the Last Home)
 *
 * Nax is a tavernkeeper and wrecker... he is cursed with
 *   eternal life by Zeboim each time he is killed, a
 *    curse is unleashed on sailors in his location ...
 *    causing them bad luck on the high seas
 *    (manifest as a shadow on sailing abilities)
 *
 * Between death and respawning, the alternate form of Nax Zeb
 *   is on the shoreline luring ships onto the rocks to wreck.
 *    (deadwrecker.c)
 *
 * When Zeboim curses him back to life, he comes back to the
 *   tavern bearing timbers and other items from the wrecked
 *    vessels and adds it to the wall and ceiling
 *
 * Players can search the walls and ceilings of the tavern
 *  when Nax is absent, but are prevented in his presence.
 *
 *  If attacked, old seadogs spring to his defence, even though
 *    they dislike him.  This is because they want to avoid
 *     his death curse.
 *
 * by Vitwitch 2021
 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>

#define DRINKGIFT "/d/Ansalon/estwilde/obj/brewcraft_beermug"

// object added to player to provide benefit
#define INVOCATION "/d/Krynn/turbidus_ocean/obj/tavernkeeper_invocation"

//shadow added to player to provide cursed actions when at sea 
#define CURSESHADOW0 "/d/Krynn/turbidus_ocean/obj/tavernkeeper_sailorcurse"

//seadogs who spring to tavernkeepers defence if attacked
#define SEADOG_PATH "/d/Krynn/turbidus_ocean/living/tavern_seadog"

#define TAVERN_ENEMY "_reefcutter_tavernkeeper_enemy"

inherit M_FILE

static int gSeadogsJoinedFight = 0;
static string gItemString = ""; 

void
create_krynn_monster()
{
    int i;

    set_name("nax");
    set_living_name("nax");
    set_race_name("human");
    set_title("Zeb, tavern keeper");
    set_adj("damp");
    add_adj("greenish");
    set_long("This tavern keeper is kind of odd-looking; human-ish, but "+
             "not quite like any other folk you can remember running across "+
             "in your voyages. He looks like he was washed ashore long ago "+
             "and never entirely dried out. His skin is vaguely greenish, "+
             "visibly damp in patches and crusted with salt elsewhere. "+
             "A plain canvas shift covers his hard lean form. "+
             "His hair, although sparse and wispy, is pulled tightly back "+
             "across his scalp and braided into a grey sailor's queue. " +
             "Despite never straying far from the heat of the brazier at "+
             "the bar, the tavern-keeper is shivering constantly. "+
             "His lips twitch about chattering teeth, as he endlessly "+
             "whispers a mantra in the common tongue.\n");

    add_item(({"mantra","whispers"}), "The tavern keeper seems to be constantly "+
             "whispering an invocation against the cold breathless terror "+
             "of the deeps in the common tongue.\n");

    set_gender(G_MALE);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(CONT_I_HEIGHT, 215);
    add_prop(CONT_I_WEIGHT, 150000);

    add_prop(NPC_M_NO_ACCEPT_GIVE," doesn't take from the hands of strangers, "+
                "he bids you <put> what you would have him examine.\n");

    set_introduce(1);

    set_act_time(20);
    add_act("The timbers and canvas of the tavern ripple ever "+
       "so slightly in the wake of the tavern keeper's passage.\n");
    add_act("emote stares across the tavern checking the dark "+
              "nooks of the place.");
    add_act("A drop of water falls on the tavern keeper "+
             "from the damp timbers overhead. He shudders visibly.\n");
    add_act("emote straightens his twisted back with a sigh, his cordlike " +
            "muscles bunch and contract then resume shivering.");
    add_act("say So cold, so cold...");
    add_act("emote huddles close to a red-hot brazier -- risking a burn. "+
             "Steam rises from his flesh.");
    add_act("Pirates and cutthroats eye the tavern keeper warily from "+
              "corners of the tavern.\n");
    add_act("emote snaps a timber spar over his bony knee. "+
              "Patrons jump at the sharp report.");
    add_act("emote pokes a timber fragment into a brazier and blows hard "+
              "so that it promptly bursts into flame.");
    add_act("emote breaks an empty barrel into pieces with gusto.");
    add_act("emote slams a mug down in front " +
            "of a patron; the larger seafaring man makes no "+
            "complaint at the splash of brew over him.");
    add_act(({"grin","say Maybe it'll come on to blow later... we'll see."}));

    set_cact_time(7);
    add_cact("shout To Wrack and Ruin!");
    add_cact("say Meet the Storm...");

    set_knight_prestige(-3);
    set_alignment(-330);

    for (i = 0; i < 6; i++)
        set_base_stat(i, 75+random(5));

    set_all_attack_unarmed(10, 8);
    set_all_hitloc_unarmed(2);

}


public void
react_freshness()
{
    TP->catch_msg(one_of_list( ({
    "The cold and salty clamminess of " + QNAME(TO) + " repels you.\n",
    "You feel the energy of a great storm about " + QNAME(TO) + ".\n",
    QCNAME(TO) + "'s eyelids flicker closed and convulsions wrack his frame.\n",
   "A shockwave of inhuman cold which sweeps over you from " + QNAME(TO) + ".\n"
        }) ));
}


public void
react_offensive()
{
    command(one_of_list( ({
        "say A fresh storm is brewing",
        "say O Mother of Storms... release me",
        "say Waves and winds care not for mortal fate..."
        }) ));
}


public void
emote_hook(string emote, object actor, string adverb, object *oblist,
        int cmd_attr, int target)
{
    if (ACTION_OFFENSIVE & cmd_attr)
    {
        react_offensive();
    }

    if (ACTION_INTIMATE & cmd_attr)
    {
        react_freshness();
    }
}


int
cannot_see_speaker()
{
    if ( !CAN_SEE(TO, TP) )
    {
        command("say Is someone there?... show yer face ere the Deeps take ye...");
        return 1;
    }
    return 0;
}



int
is_invocation( object ob )
{
    return ( wildmatch(sprintf("%s*",INVOCATION),file_name(ob)) );
}


void
remove_invocation(object killer)
{
    // remove any invocation given to the killer and team

    object *gangers = killer->query_team_others() + ({killer});
    foreach ( object ganger : gangers )
    {
        foreach ( object invoc : filter( all_inventory(ganger), is_invocation ) )
            invoc->remove_it(invoc,ganger);
    }
}


void
sailor_curse(object killer)
{
    // Add curse shadow to the killer and team
    // ... when one of these folk board a ship
    // the ship becomes cursed (different shdw obj)

    object shdw;

    setuid();
    seteuid(getuid());
    object *gangers = killer->query_team_others() + ({killer});
    foreach ( object ganger : gangers )
    {
        shdw = clone_object(CURSESHADOW0);
        if (!shdw->is_sailor_curse_shadow())
            shdw->remove_object();
        shdw->shadow_me(ganger);
        ganger->catch_msg("A cold salt wind blows over "+
          "your soul... you feel strangely burdened.\n");
    }
}


int
testcurse(string str)
{

    if ( !str || !strlen(str) ) return 0;
    if ( str != "me" ) return 0;
    sailor_curse(this_player());
    return 1;
}

void
notify_death(object killer)
{
    ::notify_death(killer);

    string str = "O Zeboim release me now! Take this other in my place!";

    killer->catch_msg("You hear " + QNAME(this_object()) 
              + " exclaim with his dying breath: " + str);
    tell_room(environment(this_object()), QCNAME(this_object()) 
        + " exclaims with his dying breath: " + str, killer);

//    sailor_curse(killer);
    remove_invocation(killer);
}


int
value_item(object ob)
{
    int val = 0;
    string *kwords = ({"wood","timber","twig","log",
                       "tinder","branch","oak","beech"});
    string *xwords = ({"burnt","scorched","burned"});

    tell_room(environment(TO), QCNAME(TO) +
          " picks up a " + ob->short() + 
          " from the bar and examines it closely.\n");

    foreach ( string word : kwords )
        if ( wildmatch(sprintf("*%s*",word),ob->long()) ) val++;
    if (!val) 
    {
        command("frown");
        command("say There aint 'nuff wood to burn here...");
        tell_room(environment(TO), QCNAME(TO) +
          " tosses the " + ob->short() + 
          " back on the bar.\n");
        command("shiver");
        return 0;
    }

    val = 0;
    foreach ( string word : xwords )
        if ( wildmatch(sprintf("*%s*",word),ob->long()) ) val-- ;
    if (val < 0 )
    {
        command("sigh");
        command("say It's a bit used up... but the fire aint picky");
        command("shiver");
        return 1;
    }

    command("ponder");
    command("say Dry wood... dry wood...");
    command("grin faint");
    command("shiver");

    switch (ob->query_prop(OBJ_I_VALUE))
    {
        case 0..12:
            return 1;            
        case 13..1600:
            return 2;            
        default:
            return 3;            
    }
}


int
is_likely_item( object item )
{
    if ( !gItemString ) return 0;
    return wildmatch(sprintf("*%s",gItemString),item->short());
}
    

int
donate_it(string str)
{
    int nitems;
    string itemlist;
    object *items;

    if ( cannot_see_speaker() ) return 0;

    if(!strlen(str) || !str)
    {
        write("Donate what?\n");
        return 1;
    }

    gItemString = str;
    items = filter(all_inventory(environment(TO)),is_likely_item);

    if ( sizeof(items) == 0 ) 
    {
        TP->catch_msg(QCNAME(TO) + 
       " looks upon the bar for the item you would donate... "+
           "but cannot see it there.\n");
        return 1;
    }

    if ( sizeof(items) > 1 ) 
    {
        itemlist = "";
        foreach ( object item : items )
            itemlist = itemlist + sprintf("... %s",item->short());
        tell_room(environment(TO), QCNAME(TO) +
          " indicates objects before him on the bar.\n", TP);
        TP->catch_msg("With a careless gesture, " + QNAME(TO) + 
        " indicates the items before him :\n" + itemlist + "\n");
        command("say to " + OB_NAME(TP)
        + " Which of these burny things are you givin' me?");
        command("emote raises a damp eyebrow.\n");
        return 1;
    }
    else
    {
        switch ( value_item(items[0]) )
        {
            case 3:
                command("say" 
                 + " Good dry wood burns bright to ward"
                 + " off the chill of the deep...");
                command("say to " + OB_NAME(this_player())
                 + " Accept this blessing by way of thanks...");
                TP->catch_msg(QCNAME(TO) + 
                 " makes an elaborate invocation over you...\n");
                tell_room(environment(TO), QCNAME(TO) +
                   " makes an elaborate intonation before " + QNAME(TP) 
                      + " .\n", TP);
                setuid();
                seteuid(getuid());
                clone_object(INVOCATION)->move(TP);
                break;
            case 2:
                command("say" 
                 + " Dry wood burns to wards off the chill of the deep...");
                command("say to " + OB_NAME(this_player())
                 + " Accept this brew in thanks");
                TP->catch_msg(QCNAME(TO) + 
                 " passes you a drink across the bar.\n");
                tell_room(environment(TO), QCNAME(TO) +
                   " gives a drink to " + QNAME(TP) + ".\n", TP);
                setuid();
                seteuid(getuid());
                clone_object(DRINKGIFT)->move(TP);
                break;
            case 1:
                command("say to " + OB_NAME(this_player())
                 + "this will keep us warm a while longer... I thank you");
                break;
            default:
                return 1;
        } 

        // toss object on the fire
        tell_room(environment(TO), QCNAME(TO) +
          " carefully places a " + items[0]->short() + " in " +
          "the brazier upon the bar, where it catches light, "+
          "giving off warmth.\n");

        items[0]->remove_object();

    }
    
    return 1;
}


void
attacked_by(object attacker)
{
    object *rg;

    attacker->add_prop(TAVERN_ENEMY, 1);
    if(!attacker->query_npc())
    {
        attacker->stop_fight(this_object());
        if(!gSeadogsJoinedFight)
        {
            tell_room(environment(TO),"A bunch of sea dogs join the fray!\n");

            rg = allocate(3);
            rg[0] = clone_object(SEADOG_PATH);
            rg[1] = clone_object(SEADOG_PATH);
            rg[2] = clone_object(SEADOG_PATH);

            foreach ( object rgi : rg )
            {
               rgi->move(E(TO),1);
               rgi->command("kill " +attacker->query_real_name());
               rgi->command(one_of_list( ({
                   "say to " + OB_NAME(attacker) + " Leave off ol'Nax!",
                   "say Leave him be or we're all doomed!",
                   "say The storm'ill come!",
                   "say Beware! Zeboim sees all!"
                  }) ));
            }
            rg[0]->initial_attack(attacker);
            gSeadogsJoinedFight = 1;
        }
    }
    ::attacked_by(attacker);
}


void
init_living()
{
    if (TP->query_prop(TAVERN_ENEMY)) {
        set_alarm(0.5, 0.0, "attack_func", TP);
    }
    ::init_living();
//    add_action("donate_it","donate");
//VW
//    add_action("testcurse","testcurse");
}


