inherit "/std/monster";

#include <ss_types.h>
#include <macros.h>

void restart();
int  greet(string s1, object ob, string s2);
int  follow(string s1, string s2);

void
create_monster()
{
    set_name("thief");
    set_name("grimulf");
    set_race_name("human"); 
    set_adj(({"slick","suspicious"}));

    set_long("He looks slick and suspicious, watch your pockets now!\n");

    default_config_npc(20);
    set_base_stat(SS_CON, 50);
    set_alignment(-300 - random(100));
    seq_new("do_things");
    seq_addfirst("do_things",({"say Ok...back in business."}));
    
    set_chat_time(7);
    add_chat("I need money.");
    add_chat("Hmmf.");
    add_chat("G'morning, mate.");
    add_chat("Do you have anything interesting to do?");
    add_chat("You look rich today, fellow.");
    add_chat("It's poor times these days!");
    add_chat("Walking is good for your legs.");

    add_cchat("Why do you hit me?");
    add_cchat("Please, I mean you no harm.");
    add_cchat("You stupid sod!");
    set_living_name("grimulf");
    set_alarm(200.0, 0.0, restart);
    trig_new("%s 'follow' %s","follow");
    trig_new("%s %l %s","greet");
    set_random_move(3);
}

void
restart()
{
    set_alarm(400.0, 0.0, restart);
    move_living("X", "/d/Gondor/rohan/edoras/stairs3");
}

int
find_someone(string name)
{
    object ob;

    ob = find_player(name);

    if (!ob)
        return 0;

    move_living("X", environment(ob));
    return 0;
}

int
greet(string s1, object ob, string s2)
{
    int il;

    if (objectp(ob))
        ob = ({ ob });

    seq_addfirst("do_things","twiddle");
    seq_addfirst("do_things", "grin");
    return 1;
}

int
follow(string s1, string s2)
{
    string *bepa;
    
    if (!s2)
        return 0;

    bepa = explode(s2+" "," ");
    if (find_living(bepa[0]))
    {
        seq_addfirst("do_things", ({ "say Hmmm...I think I'll follow.." }));
        set_follow(bepa[0]);
    }
    return 1;
}

/* Solemnian prestige */
query_knight_prestige() {return 700;}
