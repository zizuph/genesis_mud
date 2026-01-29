// file name:	gatekeeper.c
// creator(s):	Ilyian, April 1995
// purpose:	Gatekeeper for green17
/*
 * Revisions:
 * 	Denis, May 1997:  Regular updates: triggers and such.
 * 	Denis, May 2000:  Removed triggers and replaced them with sequences.
 * 	Lilith, Dec 2000: Added check for key to the actions.
 * 	Lilith, Feb 2001: Added moods, if he's in a bad mood
 * 			  he won't open the gate.
 *	Lilith, Mar 2001: Added sybarun token functionality
 *	Lilith, Nov 2004: Re-opened holm, made modifications
 *	Lucius, Jul 2016: Sped up, he was too slow.
 *	Lucius, Mar 2018: Allow Union seekers past the age check.
 *  Lilith, Sep 2021: Modifications relating to allowing players to open
 *                    the gate from the Holm-side to reduce awkwardness
 *                    with timing of gatekeeper actions and to reduce the
 *                    wait time.
 */
#pragma strict_types

#include "/d/Avenir/include/paths.h"
#include "/d/Avenir/include/relation.h"
#include "/d/Avenir/include/macros.h"
#include <ss_types.h>
#include <money.h>
#include <macros.h>

// If true, giving coins won't budge the old fart.
#define NO_SYB_COIN 0

inherit "/d/Avenir/inherit/monster";
inherit "/d/Avenir/common/bazaar/NPCS/call_for_help";

object button;
int opening, mood, al1, al2, al3;
int query_mood() { return mood; }
void do_sequence(string *seq);

void
my_mood()
{
    int i = random(80);

    mood = i;
    if (!present(button, this_object()))
    {
        button = clone_object(BAZAAR +"Obj/misc/medallion");
    }
    button->set_button(mood);
    button->move(this_object(),1);
    command("wear button");
}

void
create_monster()
{
    set_name(({"freud","gatekeeper","keeper","guard" }));
    set_race_name("dwarf");
    set_adj("crochety");
    add_adj("old");
    set_living_name("freud");
    set_long("This old dwarf seems to be in a lousy mood, intermittently "
       +"mumbling things to himself and growling. He looks like a guard "
       +"of sorts.\n");

    set_stats(({175, 135, 150, 127, 127, 157}));
    set_alignment(0);
    set_knight_prestige(-1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    MAKE_SYBARITE;
    KILL_THIEF;
    set_skill(SS_DEFENSE, 30 );
    set_skill(SS_WEP_POLEARM, 35 );
    set_skill(SS_AWARENESS, 40);

    set_act_time(3);
      add_act("grumble");
      add_act("emote swings his feet back and forth.");
      add_act("yawn");
      add_act("emote mutters to himself.");
      add_act("emote stares up at the Source.");
      add_act("close gate");
      add_act("touch medallion");
    set_chat_time(4);
      add_chat("Some strange plants grow on the Holm, ones you'll "+
          "never see in this garden.");
      add_chat("Bicorn horns can be quite valuable.");
      add_chat("The Holm may look like an idyllic park, but its not, "+
          "so be careful.");
      add_chat("Me knees are achin' now, all this up n' down pushin' "+
          "people through the gate.");
	  add_chat("Hegemon done changed things up on us. I doan hafta open ta "+
	      "gate fer people coming back from the Holm. They can let them"+
		  "selves out now.");
      add_chat("No one likes me, an' I know it. Its envy, pure an' simple.");
      add_chat("I've got the most important job there is, an' I "+
          "doan forgit it, or the Hegemon, he'd see me workin' on "+
          "his kahve farm with kesoit sap rubbed on my privates.");
      add_chat("Ye'd best know what'cher doin' wanting onta the Holm. ");
      add_chat("Demmed Outlanders got me inta trouble for lettin' em "+
          "through without makin' sure they read the rules.");
      add_chat("My list is reconsiled by the librarian and the Commissioner's "+
          "office...gotta make sure people don't have no excuse ta be bigger "+
          "idjits than they already are.");
      add_chat("The Hegemon was in a fit of rage when he got word tha Outlanders "+
          "were usin' tha Holm and then complainin' aboot what happened there. "+
          "He done closed the place down for quite a few wei. No tellin' when he "+
          "might do it again, so I gotta be vigilant.");
      add_chat("Hartsig said he'd gut me if I let the wrong sort on the Holm.");
      add_chat("Kill, or be killed. Its a place for testing yer "+
          "mettle, the Holm is. If yer afraid ta die, don't go.");
    set_cact_time(10);
      add_cact("spit enemy");
      add_cact("growl");
      add_cact("shout Die for this! Die!");
      add_cact("snarl enemy");
      add_cact("scream");
      add_cact("shout You worthless little s'nay!");
      add_cact("spit");


    trig_new("'Shouts' %s", "react_shout");

    add_ask(({"market", "bazaar", "marketplace"}),
        "say Yeah, the marketplace is to the north. Wretched, "
        +"worthless junk they all sell to, may they all be damned.", 1);
    add_ask(({"park","island", "holm", "Holm", "beyond", "through"}),
         "say Through the gate is the way to the Holm of the Icondite, "
        +"where the shadow-elves Hunt. It is a lawless place, where "
        +"the line between hunter and hunted does not exist, and "
        +"where the only rule is that there are no rules.",1);
    add_ask(({"rules", "rules", "rule of the holm" }),
        "say Are ye daft? Do ye think yer goin' ta some getaway? "
       +"They ain't no rules there, plain an' simple. Ya kill "
       +"or ya be killed.", 1);
    add_ask(({"list", "lists" }),
        "say The list shows me who I can let through tha gate. "
       +"If'n ya want ta be on it, ya better read the book on "
       +"tha Holm in the lib'ry.", 1);
    add_ask(({"blessing", "proof", "proof of blessing" }),
       "say I expect ya to give me evidence that ya have the Hegemon's "
        +"blessing.", 1);
    add_ask(({"gate","key"}),"say Yeah, I got the key. If you want me to "
        +"open the gate, just ask. When you want to come back just open "
		+"it yerself from the other side.",1);
    add_ask(({"open the gate","to open the gate","open gate","open "
        +"the gate","to open gate"}),VBFC_ME("do_open"));
    add_ask(({"give me the key","give key"}),"shout No!",1);
}

public void
equip_me()
{
    seteuid(getuid());

    MONEY_MAKE_SC(random(25))->move(this_object());
    MONEY_MAKE_CC(random(40))->move(this_object());

    my_mood();
    clone_object(BAZAAR + "Obj/wield/pclub")->move(this_object());
    command("wield all");

    clone_object(BAZAAR + "Obj/worn/pshirt")->move(this_object(), 1);
    clone_object(BAZAAR + "Obj/worn/ppants")->move(this_object(), 1);
    clone_object(BAZAAR + "Obj/worn/pshoes")->move(this_object(), 1);
    clone_object(BAZAAR + "Obj/worn/pbelt")->move(this_object(), 1);
    clone_object(BAZAAR + "Obj/worn/pbelt")->move(this_object(), 1);
    command("wear all");
}

public void
emote_hook(string emote, object who, string adverb)
{
    if (emote == "smile")
    {
	set_alarm(2.0, 0.0 ,&command("say What the hell are you smilin' at?"));
	set_alarm(4.0, 0.0 ,&command("grumble"));
    }
}

public void
attacked_by(object ob)
{
    ::attacked_by(ob);
    set_alarm(2.0, 0.0 , &command("shout Hey, you worthless little spawn " +
				  "of a toothless demon!"));
}

void
reset_opening()
{
    opening = 0;
}


public void
react_shout(object who, string str)
{
    set_alarm(0.1, 0.0,
        &command("shout The Hegemon says I don't have to let you "
		    +"back in! Open it fer yer own self."));
    return;
}

string
do_open()
{
    my_mood();
    if (opening)
    {
        command("say You in a hurry ta die or sumpin?");
        return "";
    }

    if (IS_INFIDEL(this_player()))
    {
        command("say You have sinned against the Gods!");
        command("say Do you think would I put my own re-birth "+
            "at risk to help you?!");
        command("spit "+ this_player()->query_real_name());
        return "";
    }

    if (IS_SYBARITE(this_player()))
    {
        command("say Ya know I canna open the gate without proof "+
            "of the Hegemon's blessing, Arus.");
        command("say He says the Holm is being over-hunted by "+
           "the Outlanders, and the Shadow-elves are a mite "+
           "sore about it.");
        return "";
    }

    /* Sub expert check */
    if (this_player()->query_average_stat() < 87)
    {
        command("say The Hegemon would have me skinned alive if "+
            "I let an Outlander yer size on the Holm.\n");
        command("say Ya whine too much, the lot of ya.\n");
        return "";
    }

    command("say Ya want on the Holm, do ya?");
    command("say Weel, ya better make sure ye've read the rules "+
       "of the Holm in the libray.");
    command("say An' then ya have ta give me proof of the Hegemon's "+
       "blessing bafore I'll let ya pass.");
    return "";
}

public void
add_introduced(string str)
{
    set_alarm(itof(random(2)), 0.0, &command("eyebrow ."));
    set_alarm(itof(random(2)), 0.0, &command("say So?"));
}

void
do_sit()
{
    command("sit on bench");
}

void
do_sequence(string *seq)
{
    if (sizeof(seq) > 1)
        set_alarm(1.5, 0.0, &do_sequence(seq[1..]));

    command(seq[0]);
}

/*
 * Function name:   query_not_attack_me
 * Description:     The intended victim may force a fail when attacked.
 *                  If fail, the cause must produce explanatory text himself.
 * Arguments:       who: The attacker
 *                  aid: The attack id
 * Returns:         True if the attacker fails hitting us, false otherwise.
 */
int
query_not_attack_me(object who, int aid)
{
     /* This will block any and all attacks */
     who->catch_msg(QCTNAME(this_object()) +" is immune to your attack.\n");
     command("emote seems to be quite pleased with himself.");
     return 1;
}

static void
destruct_coin(void)
{
    if (objectp(present("_sybarun_token", this_object())))
        present("_sybarun_token", this_object())->remove_object();
}

void
open_sez_me(object player)
{
    remove_alarm(al3);
    if (objectp(present(player, environment(this_object()))))
    {
        say("The crotchety old dwarf pushes "+ QTNAME(player) +
            " through the opening and closes the gate behind "+
            player->query_objective() +".\n");
        write("The crotchety old dwarf pushes you through the "+
           "gate and swings it closed behind you.\n");
        player->move_living("south", BAZAAR +"green/s_shore", 1, 0);
    }
}

void
enter_inv(object to, object from)
{
    object syb;
    int wei, holm;

    if (!to->id("_sybarun_token") && interactive(from))
    {
        set_alarm(1.0, 0.0, &command("eyebrow"));
        set_alarm(2.0, 0.0, &command("drop "+to->query_adj() +" " + to->query_name()));
	  ::enter_inv(to, from);
	  return;
    }

    ::enter_inv(to, from);

    if (!interactive(from))
	return;

    if (NO_SYB_COIN)
    {
        command("say The Holm is closed.\n");
        set_alarm(2.0, 0.0, &command("give token to "+ from->query_real_name()));
        return;
    }

    if (opening)
    {
        command("frown at "+ from->query_real_name());
        command("say Cantcha see I'm helpin' someone else? Waitcher turn!\n");
        set_alarm(2.0, 0.0, &command("give token to "+ from->query_real_name()));
        return;
    }

    if (IS_INFIDEL(from))
    {
        command("say You have sinned against the Gods!");
        command("say Do you think would I put my own re-birth "+
            "at risk to help you?!");
        command("spit "+ from->query_real_name());
        return;
    }

    /* Sub expert check */
    if (from->query_average_stat() < 87)
    {
	command("say The Hegemon would have me skinned alive if "+
	    "I let an Outlander yer size on the Holm.");

	if (from->query_prop("heard_the_union_quest"))
	{
	    command("But I've a feelin' the Idrys 'emselves would "+
		"be even mighter displeased if I turned ya away.");
	    /* Continue on for Union seekers. */
	}
	else
	{
	    command("say Ya whine too much, the lot of ya.");
	    command("say Come back when ya got more expertise.");
	    set_alarm(2.0, 0.0, &command("give token to "+ from->query_real_name()));
	    return;
	}
    }

    /* check that player has read the book */
    holm = (this_player()->query_skill(139001));
    if (!holm)
    {
        command("emote checks a list in his gnarled old hand.\n");
        command("say Ya need to read the book on the Holm before "+
            "I ken let ya through.");
        command("say Off to the library with ya.");
        set_alarm(2.0, 0.0, &command("give token to "+ from->query_real_name()));
        return;
    }
    wei = ("/d/Avenir/inherit/avenir_time.c")->get_avenir_week();
    if (wei > 9)
        wei = 1;
    if (wei > holm)
    {
        command("emote looks you over and checks a list.\n");
        command("say Its been too long since ya read the book.");
        command("say Ya know where it is.");
        set_alarm(2.0, 0.0, &command("drop "+to->query_adj() +" " + to->query_name()));
        return;
    }

    opening = 1;
    al1 = set_alarm(1.0, 0.0, &do_sequence(({
        "emote sniffs the sybarun coin.",
        "emote checks a list in his gnarled old hand.",
        "say Mind ya follow the rule of the Holm, or I'll not "+
        "let ya in again.",
        "emote unlocks the silver garden gate.",
        "emote opens the silver garden gate.",
        "emote leans a gnarled hand against the silver garden gate.",
        "emote locks the silver garden gate.",
        })));
    al2 = set_alarm(15.0, 0.0, reset_opening);
    al3 = set_alarm(8.0, 0.0, &open_sez_me(from));
    set_alarm(5.0, 0.0, &destruct_coin(to));
}
