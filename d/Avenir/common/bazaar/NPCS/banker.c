// Banker
// creator(s):	Lilith, Aug 1999
// last update:	
// purpose:
// note:
// bug(s):
// to-do:

# pragma strict_types
# include <language.h>
# include <money.h>
# include <ss_types.h>
# include <stdproperties.h>
# include <macros.h>
# include "/d/Avenir/include/guilds.h"
# include "/d/Avenir/include/paths.h" 
# include "/d/Avenir/include/defs.h"
# include "/d/Avenir/include/relation.h"

inherit "/d/Avenir/inherit/spy_npc";

string
my_long()
{
    string  str;

    str = "A successful gnome by any measurement, this fellow "+
    "makes a fine living exchanging coins for travellers who "+
    "wish to lighten their loads or safely deposit their funds "+
    "for later use.\n";

    if (IS_SYBARITE(TP))
    {
	str += "He might be inclined to tell you what he has seen "+
	"today.\n";
    }
    return str;
}


void
create_monster()
{
    ::create_monster();

    set_name("borutas");
    set_title("icu Abun'ana, First Teller of the Bank of Sybarus");
    add_name(({"shopkeeper","keeper", "banker", "teller"}));
    set_race_name("gnome");
    set_gender(0);

    add_adj(({"pleasant"}));
    set_long(my_long);
    set_act_time(10);
    add_act("bow slight");
    add_act("emote smoothes the lines of his clothing.");
    add_act("emote stares meditatively at the dome.");
    add_act("emote moves with deliberate grace behind the counter.");
    add_act("smile helpful");


    set_default_answer(VBFC_ME("what_me"));
    add_ask(({"what has occurred", "what has occured", 
	"what have you seen"}), VBFC_ME("ask_about_encountered"), 1);
    add_spy_ask();
    spy_auto_intro();

    set_all_hitloc_unarmed(50);

    set_stats(({70,70,70,70,70}));

    set_skill(SS_UNARM_COMBAT,50);
    set_skill(SS_BLIND_COMBAT,50);
    set_skill(SS_PARRY,50);
    set_skill(SS_DEFENCE,65);
    set_skill(SS_AWARENESS,50);
    add_prop(NPC_I_NO_RUN_AWAY,1);

    set_alignment(0);
    set_knight_prestige(-1);

    set_mm_in("strolls in");
}

public void
arm_me()
{
    object cloak, shirt, pants;

    seteuid(geteuid(this_object()));
    MONEY_MAKE_SC(random(20))->move(this_object());

    cloak = clone_object(BAZAAR + "Obj/worn/mencloaks");
    cloak->create_tailored();
    cloak->move(this_object(), 1);

    shirt = clone_object(BAZAAR + "Obj/worn/menshirts");
    shirt->create_tailored();
    shirt->move(this_object(), 1);

    pants = clone_object(BAZAAR + "Obj/worn/menpants");
    pants->create_tailored();
    pants->move(this_object(), 1);

    command("wear all");
}

/*
 * check_meet enables the npc to greet players it
 * comes into contact with, according to guild.
 */
void
check_meet(object tp)
{
    string  occ;
    int     i;
    i = random(6);

    alarm_id = 0;
    if (!present(tp, environment(TO)))
	return;

    if(tp->query_prop("_is_cat_"))
    {
	if(i<4)
	{
	    command("say This is no place for a smell cat!");
	    command("emote waves a scroll around in a threatening manner.");
	    return;
	}
	return;
    }

    occ = tp->query_guild_name_occ();
    if (occ == OUNION)
    {
	if (i == 0)           
	    command("smile joy "+ tp->query_real_name());
	else 
	if (i == 2)
	    command("bow deep "+ tp->query_real_name());
	else
	if (i == 4)
	    command("say to "+ tp->query_real_name() +" I am "+
	      "honoured by your patronage!");
	else
	if (i == 5)
	    command("say to "+ tp->query_real_name() +" A "+
	      "splendid day for a Hunt, is it not?");
	return;
    }
    if (tp->query_prop("_live_i_am_dancer_of_veils"))
    {
	if (i == 0)
	    command("smile respect "+ tp->query_real_name());
	else
	if (i == 4)
	    command("smile admir "+ tp->query_real_name());
	return;
    }       
    else
    {
	if (i == 3)
	    command("say May I help you?");
	return;
    }
}


string
what_me()
{
    switch(random(5))
    {
    case 0:
	command("say I am not permitted to answer that question.");
	break;
    case 1:
	command("emote struggles to answer, but does not seem able "+
	  "to get the words out.");
	break;
    case 2:
	command("say Would that I could, but I cannot say.");
	break;

    case 3:
	command("say I am not worthy of your attention.");
	break;
    case 4:
	command("emote shrugs.");
	break;
    }
    return "";    
}
