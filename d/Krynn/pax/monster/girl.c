/*
   girl.c
   ------

   Coded ........: 95/02/03
   By ...........: Jeremiah

   Latest update : 95/07/10
   By ...........: Jeremiah

   This girl is the second prisoner the player has to free. She will 
   only follow the player if s/he has given her the rag doll from the 
   gully dwarf(if its blood stained she won't follow), AND if her 
   mother, Maritta, is with the player.

*/

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
inherit M_FILE
inherit "/d/Krynn/std/act/gift";

 
string i_got_doll_from;     /* player who gave me doll. */
string i_attempt_to_follow; /* player I try to follow 
                             * if mommy says ok       */

int got_doll(object doll, object who);

void
create_krynn_monster()
{
    int i;
 
    set_name("girl");
    set_race_name("human");
    set_long("She is a young girl about the age of nine. Her " +
        "face is pale and her hair is tousled. Over her ragged " +
        "clothings she is wearing a small cloak.\n");
    set_adj("young");
    add_adj("tousle-haired");

    for (i = 0; i < 6; i++)
        set_base_stat(i,5 + random(5));

    set_all_attack_unarmed(5, 5);
    set_all_hitloc_unarmed(5);
    set_knight_prestige(-5);
    set_alignment(250);
    set_gender(G_FEMALE);

    add_ask(({ "follo", "follow me" }), VBFC_ME("follow"));

    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(NPC_M_NO_ACCEPT_GIVE,0);
    seteuid(geteuid(TO));

    add_gift("pax_quest_doll", got_doll);
}

int
got_doll(object doll, object who)
{
    if (doll->query_blood_stains())
    {
        command("sob");
        command("say You hurt somebody, I don't like you. Go away !");
        command("drop doll");
    }
    else
    {
        command("smile");
        command("hug " + OB_NUM(who));
        command("say Thank you so much!");
        command("say I lost my doll right after those dragon men " +
            "took us here.");
        command("emote looks happily at the small rag doll.");
        i_got_doll_from = who->query_real_name();
    }
    
    return 1;
}

public void                                                                 
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    recieve_gift(ob, from);
}


void
begin_follow(object who)
{
    command("say Ok, mom. But please don't hurt the old dragon!");
    set_follow(who);
}

string
follow()
{
    string who;
    object mom;
    string *player_gender;
	
    if (environment() != environment(TP))
        return "";
   
    if (!present("maritta", E(TO)))
    {
        command("say My mom told me not to go with strangers.");
        return "";
    }
   
    if (!i_got_doll_from)
    {
        command("say I won't leave without my doll!");
        return "";
    }
   
    who = TP->query_real_name();
    if (who != i_got_doll_from)
    {
        command("sob");
        command("say I don't like you, I won't go with you.");
        command("ignore " + who);
        return "";
    }
   
    mom = present("maritta", E(TO));
   
    command("say Mommy are we going with " + 
        TP->query_objective() + " ?");
    command("point " + OB_NAME(TP));
    if (mom->ask_permission(TP))
    {
        set_alarm(3.0 * rnd(), 0.0, &begin_follow(TP));
    }
    return "";
}


void
set_i_follow()
{
    command("say ok mommy, but please don't hurt the old dragon.");
}


public int
compare_i_follow(string name)
{
    if (name == query_follow()->query_real_name())
        return 1;
    
    return 0;
}


public void
do_die(object killer)
{
    object mom;

    ::do_die(killer);

    mom = P("maritta", E(TO));

    if (mom)
        mom->the_end();
}
   
void
the_end()
{
    command("emote leaves.");
    remove_object();
}

