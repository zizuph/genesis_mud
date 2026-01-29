/*
 *  A copper stake created for use in events. 
 *
 *                          Toby, 2008-05-02
 *
 *  Modification log:
 *
 */

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

// Prototypes
int thrust_stake(string str);
int pull_stake(string str);
void set_smith_made_stake();
int query_smith_made_stake();

int smith_made_stake = 0;

string
set_stake_short()
{
    string str = "crude copper stake";

    if(query_smith_made_stake())
        str = "lean copper stake";

    return str;
}

string
set_stake_long()
{
    string str = "This is a crude copper stake which has a rather sharp tip. " +
            "It is about an inch in diameter if diameter it could be called. " +
            "The hands that worked this stake did a rough job and the stake " +
            "rather dented as if given a very serious beating with a hammer. " +
            "It bears the mark of the Shire smiths guild.";

    if(query_smith_made_stake())
        str = "This is a lean copper stake which has a very sharp tip. " +
            "It is about an inch in diameter. The hands that worked this " +
            "stake did a smooth job as the stakes surface is quite smooth. " +
            "It bears the mark of the Shire smiths guild.";

    return (str + "\n");
}

void
create_object() 
{

   set_name("stake");
   add_name( ({"copper_smith_stake", "smiths_copper_stake"}) );
   set_adj("copper");
   set_short("@@set_stake_short@@");

   set_long("@@set_stake_long@@");

   add_prop(OBJ_I_WEIGHT,3200);
   add_prop(OBJ_I_VOLUME,2200);
   add_prop(OBJ_I_VALUE, 50);
}


void
init()
{
    ::init();

    add_action(thrust_stake,"thrust"); // Thrust the stake into the ground
    add_action(pull_stake,"pull");   // Pull a stake out of the ground

}

int
thrust_stake(string str)
{
    object stake;

    if ((str=="stake" || str=="copper stake" || str=="crude copper stake"))
    {
        if (objectp(stake = present("smiths_copper_stake", this_player())))
        {
            stake->move(environment(this_player()), 1);
            write("You thrust the stake with all your might into the ground.\n");
            tell_room(environment(this_player()), QCTNAME(this_player())+
                " thrusts a copper stake hard into the ground!\n",this_player());
            return 1;
        }

        write("You don't seem to have the stake in your possession any longer!\n");
        return 1;
    }

    write("Thrust what? The crude copper stake?\n");

    return 1;
}

int
pull_stake(string str)
{
    write("Not implemented yet! How odd.\n");
    return 1;
}


void 
set_smith_made_stake()
{
    smith_made_stake = 1;

}

int
query_smith_made_stake()
{
    return smith_made_stake;
}
