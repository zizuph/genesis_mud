inherit "/d/Emerald/ctower/room/ctower_base";

void
create_ctower_room()
{
    set_short("Crystal cavern");
   
    set_long("   The walls of a large, crystal cavern rise up " +
       "around you.  Near the center of the cavern, a small " +
       "platform rises high up into the air.  An elevated walkway " +
       "connects the platform to a ledge on the cavern wall to " +
       "the south..\n");

    add_item(({ "ledge", "narrow ledge" }),
        "The narrow ledge extends out a short distance from the " +
        "cavern wall to the south.\n");

    add_item(({ "floor", "crystaline floor" }),
        "Millions of crystal formations make up the floor of the " +
        "cavern.\n");

    add_item(({ "cavern", "large cavern", "wall", "walls", "ceiling" }),
        "A truly huge cavern opens up before you.  Composed entirely " +
        "of crystal, the walls, ceiling, and floor reflect the light " +
        "in a brilliant array of colours.\n");

    add_item(({ "platform", "small platform", "crystal platform",
        "small crystal platform" }),
        "Near the center of the cavern, a small crystal platform extends " +
        "high up from the floor.  From here, it looks large enough for" +
        " perhaps a single person to move about on.  There " +
        "doesn't seem to be any way to climb to it, though.\n");
}

int
climb(string str)
{
    if (!strlen(str) ||
        ((str != "up") &&
	 !parse_command(str, ({}), 
         "[up] [on] [the] 'wall' / 'walls' / 'platform'") &&
         !parse_command(str, ({}),
         "[up] 'to' [the] 'platform' / 'ledge' / 'passage'")))
    {
        notify_fail(capitalize(query_verb()) + " where?\n");
        return 0;
    }

    write("You try to get a hold and climb up, but fail miserably.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(climb, "climb");
}
