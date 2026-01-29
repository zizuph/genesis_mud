/*
 *   tells.c
 * 
 *  adds a set of tells to the room.
 *
 * Baldacin@Genesis, Aug 2003
 */
 
inherit "/d/Calia/std/room_tell_room";

void
add_tells(string set, int time = 90)
{
    this_object()->set_tell_time(time);
    switch(set)
    {
        case "forest":
            this_object()->add_tell("A bird sings from a tree high above you.\n");
            this_object()->add_tell("A small animal scurries quickly from "+
                "one bush to another.\n");
            this_object()->add_tell("You hear a loud, shrieking sound coming "+
                "from one of the trees.\n");
            this_object()->add_tell("One of the old trees goes 'Creak, creeek' "+
                "as the wind forces it to sway slowly.\n");
            this_object()->add_tell("Suddenly everything is very quiet.\n");
        break;
        case "tunnel":
            this_object()->add_tell("A dull scraping sound echoes through the "+
                "tunnels.\n");
            this_object()->add_tell("You hear a loud, shrieking sound.\n");
            this_object()->add_tell("It feels as if something is nibbling at your "+
                "feet, but as you look down you see nothing.\n");
            this_object()->add_tell("You think you spot something moving in the "+
                "corner of your eye, but as you turn your head to look, you see "+
                "nothing.\n");
            this_object()->add_tell("Suddenly everything is very quiet.\n");
            this_object()->add_tell("This malodorous smell is really awful!\n");
        break;
    }
}