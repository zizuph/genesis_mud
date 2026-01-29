/*
 * /d/Gondor/morgul/cellar/shadow/messy_shadow.c
 * Just for the Tuvale
 *
 * Technical code provided and fixed by Petros
 *
 * Varian, May 2016
 */

inherit "/std/shadow";

#define SML ({"A foul, noxious odour invades your nose.","There is a nasty stink coming from somewhere, or someone, nearby.","The fetid smell of rotting garbage drifts through the air.","A horirble stench assaults the senses of every living creature nearby.","There is a truly nasty smell hanging in the air here.","The rotting scent of decay fills the air."})

// Prototypes
public void smell();
public void remove_messy_shadow();

varargs public mixed
query_adj(int arg) 
{
    if (!arg)
    {
        // If arg == 0, we should only return one adjective.
        return "putrid";
    }
    return ({ "disgustingly", "putrid" });
}

/*
 * Function name: shadow_me
 * Description  : Called from object to make us shadow it.
 * Arguments    : mixed to_shadow - either a string or object. If it is
 *                a string, use find_player to find the player to shadow.
 * Returns      : int - True if shadowed.
 */
public varargs int
shadow_me(mixed to_shadow)
{
    ::shadow_me(to_shadow);

    // Set an alarm to tell the room that it smells
    set_alarm(2.0, 0.0, smell);
    set_alarm(1000.0, 0.0, remove_messy_shadow);
}

public void
smell()
{
    string sml = one_of_list(SML);
    tell_room(environment(this_player()),""+sml+"\n");
    // Set up the next alarm to give this message again.
    set_alarm(100.0 + 20.0 * rnd(), 0.0, smell);
}

public int
query_messy_shadow()
{
    return 666;
}

public void
remove_messy_shadow()
{
    tell_room(environment(this_player()),"The air smells just a little " +
        "bit cleaner now.\n");
    remove_shadow();
}
