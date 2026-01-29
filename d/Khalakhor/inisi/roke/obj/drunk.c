/*
 * drunk.c
 *
 * Used in obj/cadubeer.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>

mixed
query_schludderlist()
{
    return ([
        "s":"sch",
        "t":"th",
        "g":"gh",
        "'":"..'",
        "c":"ch",
        "f":"phf",
        "z":"sz",
        "n":"ng",
        "y":"i",
        "I":"Ah",
        "1":"3",
        "2":"1",
        "3":"8",
        "4":"5",
        "5":"9",
        "6":"2",
        "7":"6",
        "8":"4",
        "9":"0",
        "0":"7",
        ]);
}

void
create_object()
{
    // Some dummy names
    set_name("fylla"); //drunkedness
    add_name("drunk");
    set_adj("billig"); //cheap
    set_long("Detta ar en billig fylla.\n");

    set_no_show();
    add_prop(OBJ_M_NO_DROP, 1);
}

void
init()
{
    ::init();

    add_action("say", "say");
    add_action("say", "'", 2);
}

void
enter_env(object a, object b)
{
    ::enter_env(a, b);

    if (!living(a))
        return;

    a->catch_msg("You feel a little drunk.\n");
    a->add_subloc("totallydrunk", this_object());
}

public void
leave_env(object from, object to)
{
    if (!living(from))
        return;
    from->remove_subloc("totallydrunk");
    from->catch_msg("You feel less drunk.\n");
}

public string 
show_subloc(string subloc, object on, object for_obj)
{
    string data;

    if (for_obj == on)
        data = "You look ";
    else
        data = capitalize(environment(this_object())->query_pronoun()) +
            " looks ";

    data += "a little drunk.\n";

    return data;
}

int
say(string s)
{       
    string *str, ss;
    mapping mapp;
    int i, a, b;

    if (!s)     
        return 0;

    if ((a = this_player()->query_intoxicated()) > 
        (this_player()->query_stat(2)/3))
    {
        mapp = query_schludderlist();
        b  = this_player()->query_stat(2);
        
        str = explode(s, "");

        for (i = 0; i < sizeof(str); i++)
        {
            if (random(a) > random(b))
            {
                ss = mapp[str[i]];
                if (ss)
                    str[i] = ss;
            }
        }
            
        this_player()->communicate(implode(str, ""));
            
        return 1;
    }
    else
    {
        set_alarm(1.0, 0.0, &remove_object());
        return 0;
    }
}
