#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Genesis/start/human/town/tower.h"
#include "/d/Cirath/common/defs.h"
inherit TOWER_OFFICE;

void add_office_sign()
{
/* This does nothing on purpose. */
}
static void
create_board()
{
    object board;
    if((board = clone_object("/std/board")))
    {
     board->set_board_name("/d/Cirath/open/projects/board");
           board->set_num_notes(50);
        board->set_silent(0);
    board->set_err_log("/d/Cirath/common/board/errors");
        board->set_show_lvl(0);
        board->move(TO);
    }
    return 0;
}

public void
reset_room()
{
    if(!present("board", TO))
            create_board();
}


create_tower_office()
{
    ::create_tower_office();
    set_short("the border");

    set_long("You stand at a crossroads near the Sea of Silt, close to "
            +"a tiny sunbleached tower: In each direction loom testaments "
            +"to man's weakness. A magic induced wasteland stretches out "
            +"around you, with only the hardiest and toughest of plants "
            +"and animals surviving.  In this realm good and evil matter "
            +"little, survival is what matters most.  To the north, jagged "
            +"mountain peaks rend the air like fangs.  Far to the east, "
            +"what appears to be trees stand boldly upright from the dry, "
            +"nutrient poor soil, struggling to survive in this tortuous "
            +"environment.  Immediately to your west, the Silt Sea opens "
            +"up like a vast plain, when in reality, it is the final "
            +"remnant of a massive ocean, which is now nothing but dust.  "
            +"The hypnotic whisper of the Silt Sea urges you to look "
            +"closer at it.\n"); 

    add_item("silt", "As you stare into the silt a voice calls to your "
            +"mind.\n 'I am the servant of the Dragon: He who knows all that "
            +"happens within Cirath. He wishes to share his information "
            +"with you. You have but to 'request' it. And keep in mind that "
            +"he needs more slav...errr...servants.\n");

    set_project_path("/d/Cirath/open/projects/");
    set_project_dir("/d/Cirath/open/projects/");

    add_tower_link("tower");
     set_alarm(1.0,0.0,"reset_room");
}

int
do_list_projects(string str)
{
    object tp = this_player();
    string *w, fp;

    if (!stringp(str))
        str = query_domain();
    else
        str = capitalize(lower_case(str));
    fp = (projdir + str + PROJ_EXT);
    if (file_size(fp) == -1)
    {
        notify_fail("The silt whirls around, knowing nothing of what "
                   +"you desire.\n");
        say("The silt whirls around, almost as if confused.\n");
        return 0;
    }

    tp->more("The silt gurgles forth all it knows about " + capitalize(str) +
             ":\n" + read_file(fp));
    return 1;
}

void
init()
{
    ::init();
    add_action("do_list_projects", "request");
}

