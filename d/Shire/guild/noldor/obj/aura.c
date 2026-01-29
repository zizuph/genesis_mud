/*
 * A configurable aura by Finwe
 * Prototype for Noldor racial guild
 * June 1999
 */

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#define SUBLOC "_aura_subloc_"

/* Some prototypes and Globals, sorry :( */
private string gAura;
void set_aura ( string str );
string get_aura ();
void setaura_fun ( string str );

void
create_object()
{
    set_name ("aura");
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    set_no_show();
    set_aura ( "surrounded by a mystical aura.");

}

void
init()
{
    ::init();
    add_action ("setaura_fun","setaura");
}

void
setaura_fun ( string str )
{
    if ( !str )
    {
        set_aura ("surrounded by a mystical aura.");
        write ("Your aura has been set to 'surrounded by a mystical " +
            "aura.\n");
    }
    else
    {
        set_aura ( str );
        write ("Your aura has been set to " + get_aura() + "\n");
    }
}
string
query_auto_load()
{
    return MASTER_OB(this_object()) + ":" + get_aura();
}

/* Called when the aura enters another object */
/*
void
enter_env(object to, object from)
{
    if (living(to))
    {
        write ("Please configure your aura with 'setaura <text>'\n");
        to->add_subloc(SUBLOC,this_object());
    }
    ::enter_inv(to, from);
}
*/

 /* Called when the aura leaves another object */
void
leave_env(object from, object to)
{
    if (living(from))
        from->remove_subloc(SUBLOC);
    ::leave_env(from, to);
}

/* Called when listning of subloc should be done. */
string
show_subloc(string subloc, object carrier, object for_obj)
{
    string str;

    if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return ""; /* Don't show this sublocation as inventory. */

    if (for_obj == carrier)
    return "You are " + get_aura() + "\n";
    else
    return capitalize(carrier->query_pronoun()) + "is " + get_aura() +
            "\n";
}

void
set_aura ( string str )
{
    gAura = str;
}

string
get_aura ()
{
    return gAura;
}

public void
init_arg ( string arg )
{
    string aura;

    if (sscanf(arg, "%s", aura) == 1)
        set_aura ( aura );
}
