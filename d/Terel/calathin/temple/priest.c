// Modified by Lilith, Mar 2022: fixed the path for cloning the censer
//   and removed the mystic-related code. 
//inherit "/d/Terel/std/mystic";
//#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

inherit "/d/Terel/std/monster";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

#define TO       this_object()
#define TP       this_player()
#define ETO      environment(TO)
#define ETP      environment(TP)

#define MO_PROP  "_blessed_by_talhurn"
#define CENSER   "/d/Terel/calathin/temple/censer"

public string ask_menablix();

public void
create_monster()
{
    object censer;

    ::create_monster();

    set_name("talhurn");
    add_name("priest");
    add_name("keeper");
    add_name("elder");
    set_adj(({"old", "formidable"}));
    set_race_name("human");
    set_gender(0);
    set_long("A formidable man, he is priest of the temple and its " +
             "guardian. He wears a long gold robe. He has long blonde " +
             "hair and a beard, both are set into braids. His eyes " +
             "are pale blue, luminous and searching.\n");

    set_alignment(834);
    set_stats(({ 70, 70, 70, 150, 150, 100}));

    set_skill(SS_DEFENCE, 70);
    set_skill(SS_SPELLCRAFT, 70);
    set_skill(SS_LANGUAGE, 70);
    set_skill(SS_FORM_CONJURATION, 70);
    set_skill(SS_ELEMENT_LIFE, 70);
    enable_intro();

    set_all_hitloc_unarmed(40);

    seteuid(getuid());
    censer = clone_object(CENSER);
    censer->move(TO);

    set_act_time(15);
    add_act("pray");
    add_act("light censer");
    add_act("emote swings his censer back and forth.");
	add_act("reverence");
    add_act("sigh");
    add_act("emote inclines his head with reverence toward the statue.");
    set_chat_time(5);
    add_chat("Seek Truth from Holy Ones.");
    add_chat("Reverence the powers here.");
    add_chat("I am priest and guardian of this holy place.");
    add_chat("I will bless the result of defoliation.");

    add_ask(({"about high place", "high place"}), "@@high_place", 1);
    add_ask(({"to bless leaf", "bless leaf", "to bless my leaf",
        "bless my leaf"}), "@@bless_leaf", 1);
	
    add_ask(({"[about] [the] 'mystics' / 'ancients' / 'holy' 'ones'"}),
        "say They exhausted their powers fighting immense evil. I do not "+
        "know when or if they will return.", 1);
    add_ask(({"[about] 'benton' / 'vercus' / 'necromancers'"}), 
	    "say There were three practitioners of evil and perverted "+
        "magic: Benton, Menablix, and Vercus. I have little more to say "+
        "on the subject.", 1);	
    add_ask(({"[about] 'perverted' 'magic'"}),
        "say There is magic in the world that feeds life, and then there is "+
        "magic in the world that feeds on life. Some call it necromancy.", 1);			
    add_ask(({"[about] [the] 'necromantic' 'arts'"}), 
        "say There is magic in the world that feeds life, and then there is "+
        "magic in the world that feeds on life. Some call it necromancy.", 1);		
    add_ask(({"[about] / [who] [is] / [was] [the] [evil] [called] 'menablix'"}), 
        &ask_menablix());	
    set_default_answer("say Only The Ancients know.", 1);

}

public string
high_place()
{
    command("whisper " + TP->query_real_name() + " " +
            "In the icy mountains shall ye find it.");
    return "smile";
}



/*
 * Function name: ask_menablix
 * Description  : respond to questions about Menablix the Necromancer
 * Returns      : "" (answer is written before return)
 */
public string
ask_menablix()
{
    set_alarm(2.0, 0.0, &command("say An evil man with evil aims."));
    set_alarm(4.0, 0.0, &command("say Menablix had two brothers: Benton "+
        "and Vercus."));	
    set_alarm(6.0, 0.0, &command("say They all had a fascination with "+
        "the necromantic arts, and it took a gathering of all who could "+
        "use magic to stop Menablix from unleashing his evil upon the world."));
    set_alarm(8.0, 0.0, &command("say The Ancients were exhausted fighting "+
        "his evil. I do not know when we will see them again."));	
		return "";
}






public int
do_bless(string what)
{
    int i;
    object *obs, leaf;

    notify_fail("Bless what?\n");
    if (!what || !parse_command(what, TP, "%i", obs))
        return 0;

    if (sizeof(obs) <= 1) 
	{
        command("say I cannot bless something you do not possess.");
        return 1;
    }

    for (i=1; i<sizeof(obs) ; i++) {
        if (obs[i]->id("leaf") >= 1) 
		{
            leaf = obs[i];
           // if (leaf->query_prop(MO_PROP) == 1)
                break;
        }
    }

    if (!leaf) {
        command("say I will not bless that.");
        return 1;
    }
    if (leaf->query_prop(MO_PROP) == 2) {
        command("say The " + leaf->short() + " is already blessed.");
        command("smile");
        return 1;
    }

    write("The priest puts his hands on your leaf and blesses it.\n");
    command("say It's now prepared to soften the Keeper " +
            "of the Key.");
    //leaf->add_prop(MO_PROP, 2);
    return 1;
}

public string
bless_leaf()
{
    if (do_bless("leaf"))
		return "emote raises a hand over the leaf and chants a few words.";
    return "ponder";
}

public void
init_living()
{
    ::init_living();
    add_action(do_bless, "bless");
}
