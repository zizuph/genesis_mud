/*
 * The scribe of the Wizards of High Sorcery
 *
 * Originally a student at the Library of Palanthas.
 * He now aides the wizards by keeping track of their records.
 */
inherit "/d/Krynn/std/monster";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <language.h>

#include "/d/Krynn/common/defs.h";
#include "../guild.h";

int last_talk;
#define TALK_INTERVAL 160

void
create_krynn_monster()
{
    set_name("alfran");
    set_title("Gelt of Palanthas");

    set_race_name("human");
    set_adj(({ "old", "wrinkled" }));

    set_stats(({ 80, 80, 80, 130, 120, 70 }));
    set_alignment(350);
    set_gender(G_MALE);

    set_skill(SS_LANGUAGE, 70);
    set_skill(SS_AWARENESS, 30);

    set_introduce(1);

    add_ask(({ "palanthas" }),
        "say Aye, I'm from Palanthas. I was once working in the " + 
        "Great Library there.", 1);
    add_ask(({ "magic", "spells", }), 
        "say I may work here, but that does not a wizard me make.", 1);
    
    add_ask(({ "members", "wizards" }), "@@member_ask@@", 1);
    add_ask(({ "renegades", }), "@@renegades_ask@@", 1);
    add_ask(({ "initiates", "students" }), "@@initiates_ask@@", 1);
    add_ask(({ "conclave", "council" }), "@@conclave_ask@@", 1);
}

int
empty_talk()
{
    if ((time() - last_talk) >= TALK_INTERVAL)
        return 1;
    return 0;
}

string
conclave_ask()
{
    string *who, head;
    int size;

    who = ADMIN->query_conclave_members();
    size = sizeof(who);

    if (!size) 
    {
        command("say Well, right now there is no conclave.");
        return "";
    }

    if (empty_talk())
    {
        command("say I fear not much would happen without someone in " + 
            "charge..");
    }

    head = ADMIN->query_conclave_head();

    command("say The master of the conclave is " + capitalize(head) + 
        ". Who is of the " + ADMIN->query_member_type(head) + " Robes.");

    who -= ({ head });
    size = sizeof(who);
    
    while (size--)
    {
        command("say " + capitalize(who[size]) + " is master of the " + 
            ADMIN->query_member_type(who[size]) + " robes.");
    }
    
    return "";
}

string
member_ask()
{
    string *who;
    int size;

    who = ADMIN->query_members() - ADMIN->query_members(INITIATE);
    size = sizeof(who);

    if (!size)
    {
        command("say This is awful odd, I have no members in my " + 
            "records.");
        return "";
    }

    if (size == 1)
    {
        command("say There is just one lone wizard in the Tower.");
        command("say It is " + capitalize(who[0]) + ".");
        return "";
    }

    command("say There are " + LANG_WNUM(size) + " wizards in the Tower.");
    command("say " + COMPOSITE_WORDS(map(who, capitalize)) + ".");
    
    return "";
}

string
renegades_ask()
{
    string *who;
    int size;

    who = ADMIN->query_renegades();

    if (empty_talk())
    {
        command("shudder");
    }

    size = sizeof(who);
    
    if (!size)
    {
        command("say I have no information about any Renegades and " + 
            "thank Paladin for that.");
        return "";
    }

    if (size == 1)
    {
        command("say I have heard of only one wizard who turned his back " + 
            "on the Tower. It is the " + ADMIN->query_member_type(who[0]) +
            " " + capitalize(who[0]) + ".\n");
        return "";
    }

    command("say There are a few cursed ones now, " + 
        COMPOSITE_WORDS(map(who, capitalize)) + ".");
    return "";
}

string 
initiates_ask()
{
    string *who;
    int size;
    
    who = ADMIN->query_members(INITIATE);
   
    if (empty_talk())
    {
        command("say Ah, the hard working students!");
        command("say The proud future of the tower.");
    }


    command("think");
    size = sizeof(who);

    if (!size)
    {
        command("say Alas, there are no initiates studying for the " + 
            "test.");
        command("sigh");
        return "";
    }

    if (size == 1)
    {
        command("nod");
        command("say We have one student, " + capitalize(who[0]) + 
            " who study under " + capitalize(ADMIN->query_mentor(who[0])) +
            ".");
        return "";
    }
    
    command("say There are " + LANG_WNUM(size) + " initiates now.");
    command("say They are " + COMPOSITE_WORDS(map(who, capitalize)) + 
        ".");
    
    return "";
}
