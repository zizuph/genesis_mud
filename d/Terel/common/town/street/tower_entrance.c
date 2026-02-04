// Modified by Lilith, Mar 2022: slight re-map of area, added
//   items and fleshed out descriptions.

inherit "std/room";

#include <macros.h>
#include <tasks.h>
#define PATH "/d/Terel/common/town/street/"
void
create_room()
{
   set_short("Tower Entrance");
   set_long("A white stone tower stands here, rising up high over " +
      "the pines that surround it. Thick hedges have grown from " +
      "the forest to enclose the base of the tower.  "+
      "The only direction to go is east, where a small "+
	  "paved walkway leads into the deep shade of the pine trees.\n"+
      "A small firepit with smoldering ashes.\n");

   add_item(({"pit", "fire pit", "ashes", "firepit", "small firepit"}),
      "There is a small fire pit here, filled with ashes that give "+
      "off a hint of smoke.\n");
   
   add_item(({"shade", "deep shade", "east", "trail", "walkway"}), 
      "The pine trees cast a deep shade over the walkway.\n");	  

   add_item(({ "tower", "stone tower", "white stone tower" }),
       "From the outside, the tower gives no indication of its purpose. " +
       "Its construction is unremarkable: its white, stone walls rising " +
       "about ten meters up to the roof. Judging by the locked door, " +
       "and the hints of minor disrepair, it doesn't seem to be occupied.\n");

   add_item(({ "wall", "walls", "stone wall", "stone walls",
	       "white stone wall", "white stone walls",
               "stones", "blocks" }),
       "The walls of the tower are formed from blocks of light-coloured " +
       "stone about one meter by one-half meter in size.  Toward the top " +
       "of the tower, the stones show signs of deterioration, leaving " +
       "the ground below littered with small bits of rock which have " +
       "fallen away from the crumbling blocks.\n");

   add_item(({ "top", "roof", "top of tower", "top of the tower" }),
       "The roof of the tower is not visible from the ground. Toward the " + 
       "top of the tower, the stones show signs of deterioration.\n");

   add_item(({ "hedge", "hedges", "bushes" }),
       "A thick row of bushes makes it difficult to get to the west side " +
       "of the tower from here.\n");

   add_exit("street2", "east");
              
   room_add_object(PATH + "t_door1");
}

void
go_through_bushes()
{
    string msg;

    if (this_player()->resolve_task(TASK_DIFFICULT, ({ TS_STR, TS_DEX })) <= 0)
    {
        write("You can't manage to push yourself through the hedge.\n");
        return;
    }

    write("You push your way through the hedge to the western side of the " +
        "tower.\n");

    msg = " pushes " + this_player()->query_possessive() + 
         " way through the hedge.\n";
    say(({ METNAME + msg, ART_NONMETNAME + msg, "" }));

    this_player()->move_living("M",
        "/d/Terel/common/town/street/west_tower", 1);


    say(({ METNAME + msg, ART_NONMETNAME + msg, "" }));
}

int
climb(string str)
{
    if (!strlen(str))
    {
        return 0;
    }

    if ((str != "up") && !parse_command(str, ({}),
        "[the] [white] [stone] 'tower' / 'wall' / 'walls'"))
    {
        string *prep = ({ "over", "through" });
        if (parse_command(str, ({}),
            "%p [the] [thick] 'bushes' / 'hedges' / 'hedge'"), prep)
	{
            if (prep[0] == "over")
	    {
                write("The hedge bushes are too difficult to climb over.\n");
                return 1;
	    }

            go_through_bushes();
            return 1;
	}

        notify_fail("Climb what?\n");
        return 0;
    }

    write("You can't seem to get a good enough hold to climb all the " +
       "way up.\n");
    return 1;
}

int
pass_bushes(string str)
{
    if (!strlen(str))
    {
        return 0;
    }

    if (!parse_command(str, ({}), 
        "'past' / 'through' [the] [thick] 'bushes' / 'hedge' / 'hedges'"))
    {
        notify_fail(capitalize(query_verb()) + " where?\n");
        return 0;
    }

    go_through_bushes();
    return 1;
}

int
enter_bushes(string str)
{
    if (!strlen(str))
    {
        return 0;
    }

    if (!parse_command(str, ({}),
        "[the] [thick] 'bushes' / 'hedge' / 'hedges'"))
    {
        notify_fail("Enter what?\n");
        return 0;
    }

    go_through_bushes();
    return 1;
}

int
jump_bushes(string str)
{
    if (strlen(str) && parse_command(str, ({}),
        "[over] 'bushes' / 'hedge' / 'hedges'"))
    {
        write("The bushes are too tall.\n");
        return 1;
    }

    return 0;
}

void
init()
{
    ::init();
    add_action(climb, "climb");
    add_action(pass_bushes, "push");
    add_action(pass_bushes, "go");
    add_action(pass_bushes, "walk");
    add_action(pass_bushes, "crawl");
    add_action(jump_bushes, "jump");
    add_action(enter_bushes, "enter");
}
