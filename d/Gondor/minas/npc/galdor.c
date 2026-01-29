/*
 * /d/Gondor/minas/npc/galdor.c
 *
 * Olorin, August 1994
 */
#pragma strict_types

inherit "/d/Gondor/minas/npc/gondor_officer";

#include <language.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "/d/Gondor/morgul/quest/bsw/bsw_defs.h"

void    react_quest(object pl);
void    react_quest_twice(object pl);

/*
 * Global variables
 */
int     rq_c = 0,
        rq_alarm = 0;

void
create_monster()
{
    ::create_monster();
    set_name("galdor");
    add_name("captain");
    set_short(0);
    set_title("the Captain of the Guard");

    set_long("@@long_desc");

    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"task", "quest", "details", }), VBFC_ME("answer_quest"));
    add_ask(({"standard", "battle standard", }), VBFC_ME("answer_quest"));
    add_ask(({"baranor", "father", }), VBFC_ME("answer_baranor"));

    remove_prop(LIVE_I_NEVERKNOWN);
}

string
long_desc()
{
    string  desc = CAP(LANG_ADDART(implode(query_adjs()," ")))
      + " officer of the Gondorian Army. He is probably from Anorien or "
      + "Lossarnach, the provinces closest to Minas Tirith. His proud stance "
      + "makes him look like he is the veteran of many battles. Experienced "
      + "and skilled as he is, he is a terrifying opponent in combat.";

    if (TP->query_prop(BSW_I_SENT_TO_GALDOR))
        desc += " This is the Captain of the Guard that the Master of Advice "
              + "told you to ask for details on the task your are to solve.";
    return BSN(desc);
}

string
default_answer()
{
    command("think");
    command("say I'm afraid I do not know what you are talking of.");
    return "";
}

string
answer_quest()
{
    if (!TP->query_prop(BSW_I_SENT_TO_GALDOR))
        default_answer();
    else if (TP->query_prop(BSW_I_SENT_TO_BARANOR))
        set_alarm(2.0, 0.0, &react_quest_twice(TP));
    else if (rq_alarm && sizeof(get_alarm(rq_alarm)))
        command("say Yes, yes, I'm talking about it right now!");
    else
    {
        command("peer "+TP->query_real_name());
        command("say Hunthor sent you?");
        rq_c = 0;
        rq_alarm = set_alarm(2.0, 2.0, &react_quest(TP));
    }
    return "";
}

void
react_quest_twice(object pl)
{
    command("glare "+pl->query_real_name());
    command("say I told you already everything I know!");
    command("say Now get out of here and talk to Baranor!");
}

void
react_quest(object pl)
{
    if ( (objectp(query_attack())) ||
         (!objectp(pl)) || (!present(pl, ENV(TO))) )
    {
        rq_c = 0;
        remove_alarm(rq_alarm);
        rq_alarm = 0;
        return;
    }

    switch(rq_c++)
    {
        case 0:
            command("say So you want to try to solve this task?");
            command("say Well, you probably have no idea what it's all about!");
            break;
        case 2:
            command("sigh");
            command("say Ok, here is the whole story.");
            break;
        case 4:
            command("say The Stewards of Gondor are of the House of Hurin.");
            break;
        case 5:
            command("say Most of the heirlooms of the House of Hurin were left "
              + "behind when Ithilien had to be evacuated.");
            break;
        case 6:
            command("say Most important of all the lost heirlooms is the battle "
              + "standard of the Witchking which Earnur conquered in the battle "
              + "of Fornost in the year 1975 of the Third Age.");
            break;
        case 8:
            command("say We know that Angmar is trying to recover the battle "
              + "standard. His minions are searching for it in Ithilien.");
            break;
        case 10:
            command("say It is of utmost importance to prevent him from "
              + "reaching that aim.");
            break;
        case 12:
            command("say After what happened to Earnur later, the battle "
              + "standard is the only token we have of the victory in the "
              + "Battle of Fornost, the last battle that we have won when "
              + "fighting Angmar himself.");
            break;
        case 14:
            command("say That is why the Steward has ordered to recover the "
              + "battle standard from its hiding place in Ithilien.");
            break;
        case 15:
            command("say The problem is that Angmar has the place guarded. "
              + "The last men we sent there did never return.");
            break;
        case 17:
            command("say Then Bergil, son of Baranor, had the command.");
            break;
        case 19:
            command("say Some rangers later found parts of his equipment. "
              + "It was brought to Baranor, his father.");
            pl->add_prop(BSW_I_SENT_TO_BARANOR, 1);
            break;
        case 20:
            command("say If you go to him, you might be able to learn more.");
            break;
        case 21:
            rq_c = 0;
            remove_alarm(rq_alarm);
            rq_alarm = 0;
            break;
        default:
            break;
    }
}

void
return_introduce(object pl)
{
    if ((!objectp(pl)) || (objectp(query_attack())))
        return;

    command("introduce me to "+pl->query_real_name());
    return;
}

void
add_introduced(string who)
{
    object  pl = find_player(LOW(who));

    if ((!objectp(pl)) || (objectp(query_attack())))
        return;

    set_alarm(3.0, 0.0, &return_introduce(pl));
    return;
}


string
answer_baranor()
{
    if (objectp(query_attack()))
        return "";

    if (TP->query_prop(BSW_I_SENT_TO_BARANOR))
        command("say Baranor? He is living in the fifth circle.");
    else
        default_answer();
    
    return "";
}

