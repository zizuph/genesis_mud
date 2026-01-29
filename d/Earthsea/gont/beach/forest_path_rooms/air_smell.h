#include <macros.h>

public int
air(string s)
{
    if(!strlen(s) || !parse_command(s, this_object(), "[the] [sea] 'air'"))
        return notify_fail("Smell what? The air?\n");

    write("You breathe the fresh, salty sea air deep in your lungs, " +
        "tasting it on your lips.\nMmmm.....\n" +
        "There is no place like the sweet lands of the Archipelago.\n");
    say(QCTNAME(this_player()) + " takes a deep breath, smiling happily.\n");

    return 1;
}

public void
init()
{
    ::init();
    add_action(air, "smell");
}
