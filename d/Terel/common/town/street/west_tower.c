inherit "std/room";

#include <macros.h>
#include <tasks.h>
#include <files.h>
#include <stdproperties.h>
#include <ss_types.h>

void
reset_room()
{
    object rocks = present("terel_tower_rocks");
    
    int no = random(4) - 1;

    if (!no)
    {
        return;
    }

    if (!rocks)
    {
        rocks = clone_object(HEAP_OBJECT);
        rocks->set_heap_size(random(3));
        rocks->set_name("rock");
        rocks->add_name("terel_tower_rocks");
        rocks->add_prop(HEAP_S_UNIQUE_ID, "rock");
        rocks->set_long("A small, light-coloured stone.\n");
        rocks->move(this_object(), 1);
    }
    else
    {
        if (rocks->num_heap() > 20)
	{
            return;
	}

        rocks->set_heap_size(rocks->num_heap() + no);
    }
   
    tell_room(this_object(), "A few stones fall from the tower wall.\n");
}
        
void
create_room()
{
   set_short("Western side of the tower");
   set_long("A white stone tower stands here, rising up high over " +
      "the pines that grow all around it. A thick hedge blocks access " +
      "to the eastern side of the tower.\n");

   add_item(({ "tower", "stone tower", "white stone tower" }),
       "From the outside, the tower gives no indication of its purpose. " +
       "Its construction is unremarkable: its white, stone walls rising " +
       "about ten meters up to the roof. Judging by the locked door, " +
       "and the hints of minor disrepair, it doesn't seem to be occupied.\n");

   add_item(({ "wall", "walls", "stone wall", "stone walls",
               "white stone wall", "white stone walls",
               "stones", "blocks" }),
       "The walls of the tower are formed from blocks of light-coloured " +
       "stone about one meter by one-half meter in size.  This side of " +
       "the tower shows pronounced signs of deterioration, leaving " +
       "many large pits in the wall and littering the ground with small " +
       "bits of rock which have fallen away from the crumbling blocks.\n");

   add_item(({ "top", "roof", "top of tower", "top of the tower" }),
       "The roof of the tower is not visible from the ground. Toward the " + 
       "top of the tower, the stones show signs of deterioration, leaving " +
       "the ground below littered with small bits of rock which have " +
       "fallen away from the crumbling blocks.\n");

   add_item(({ "hedge", "hedges", "bushes" }),
       "A thick row of bushes makes it difficult to get to the east side " +
       "of the tower from here.\n");

    reset_room();
}

void
go_through_bushes()
{
    string msg;
    if (this_player()->resolve_task(TASK_DIFFICULT, ({ TS_STR, TS_DEX })) <=0)
    {
        write("You can't manage to push yourself through the hedge.\n");
        return;
    }

    write("You push your way through the hedge to the eastern side of the " +
        "tower.\n");

    msg = " pushes " + this_player()->query_possessive() + 
         " way through the hedge.\n";
    say(({ METNAME + msg, ART_NONMETNAME + msg, "" }));

    this_player()->move_living("M",
        "/d/Terel/common/town/street/tower_entrance", 1);


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
                write("The bushes are too difficult to climb over.\n");
                return 1;
	    }

            go_through_bushes();
            return 1;
	}

        notify_fail("Climb what?\n");
        return 0;
    }

    if (this_player()->resolve_task(TASK_DIFFICULT, ({ TS_STR, TS_DEX })) <= 50)
    {
        write("You can't make that vertical climb... No way...\n");
        return 1;
    }

    write("With an incredible disply of strength and dexterity, you "+
        "quickly scale the tower wall up to the roof.\n");
    say(({ METNAME + " scales the tower wall up to the roof.\n",
           ART_NONMETNAME + " scales the tower wall up to the roof.\n",
           "" }));

    this_player()->move_living("M",
        "/d/Terel/common/town/street/tower_roof", 1);

    say(({ METNAME + " climbs onto the roof.\n",
           ART_NONMETNAME + " climbs onto the roof.\n",
           "" }));

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
