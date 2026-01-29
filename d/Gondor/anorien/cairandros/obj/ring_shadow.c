/*
 * Borrowed from /d/Gondor/morgul/cellar/shadow/messy_shadow.c
 *
 * Varian, September 2016
 */

inherit "/std/shadow";

#define SML ({"You feel a strange itch inside.","There air feels heavier here, making you itch inside.","There is something strange here."})

// Prototypes
public void itch();
public void remove_ring_shadow();

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
    set_alarm(2.0, 0.0, itch);
    set_alarm(1000.0, 0.0, remove_ring_shadow);
}

public void
itch()
{
    string itch = one_of_list(ITCH);
    tell_room(environment(this_player()),""+itch+"\n");
    // Set up the next alarm to give this message again.
    set_alarm(100.0 + 20.0 * rnd(), 0.0, itch);
}

public int
query_ring_shadow()
{
    return 666;
}
