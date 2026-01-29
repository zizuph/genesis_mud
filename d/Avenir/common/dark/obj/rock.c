// file name:		~Avenir/common/dark/obj/rock.c
// creator(s):		Denis
// revsion history:
//			Denis, Jan 96: Added notification of altar room when
//				       the hammer is cloned (for impquest
//				       reset-ability)
// purpose:		Under this rock is the hammer - imps quest item.
// note:		Can be opened only using three small pieces of Source.
//			Is located in ~avenir/dark/l4/n16.c
// bug(s):
// to-do:

inherit "/std/object";

# include "/d/Avenir/common/dark/dark.h"
# include "../l3/l3_defs.h"
# include "/d/Avenir/smis/sys/statserv.h"

int sources_number;
object hammer;

void create_object()
{
    set_name("rock");
    add_name("_Unterdark_rock");
    set_no_show();

    sources_number=0;
}

void enter_env(object dest, object old)
{
    ::enter_env(dest,old);
    dest->add_my_desc("A rock lies in the middle of the cavern.\n");
    dest->add_cmd_item("rock",({"raise","lift","get"}),
                 "You try to raise the rock, but it won't "+
                 "budge. It is somehow stuck to the ground!\n");

    dest->add_item("rock",
               "There is a large, black rock in the center of the "+
               "cavern. By its color and shape, you discern that it "+
               "is not indiginous to this cave, and has been placed "+
               "here. You can make out some very faint, faded runes "+
               "along the top. There are three small holes on the "+
               "top of the rock, forming a perfect triangle.\n");

    dest->add_item("runes",
                 "The runes are in some forgotten language: their "+
                 "lore is beyond you.\n");

    dest->add_item(({"hole","holes"}),
                 "The holes are small and oddly-shaped, as if something "+
                 "was meant to be inserted in them.\n");
}

add_shining_piece()
{
    sources_number++;
    write("You place a piece of shining crystal in one of the holes of "+
          "the rock.\n");
    tell_room(environment(TP),
              QCTNAME(TP)+" places a shining crystal in one of "+
              "the holes of the rock.\n",TP);
    switch(sources_number)
    {
    case 1:
        tell_room(environment(TP),
                  "The runes on the rock flash briefly.\n\n");
        break;
    case 2:
        tell_room(environment(TP),
             "Two shining pieces connect with burst of blue energy.\n\n");
        break;
    case 3:
        tell_room(environment(TP),
                  "The small crystals in the rock form flashing triangle, "+
                  "the runes start to glow with blue and the "+
                  "rock raises above the floor.\n\n");
        seteuid(getuid());
        hammer=clone_object(IMPS_QUEST_HAMMER);
        hammer->move(TP);
	ALTAR->set_hammer_object(hammer);
        write("You quickly grab the hammer, which lies under the rock.\n");
        tell_room(environment(TP),
                      QCTNAME(TP)+" grabs the hammer from under the rock.\n",
                      TP);
        tell_room(environment(TP),
                  "The rock returns back.\n");
        sources_number=0;
	STATSERV_LOG_EVENT("impquest", "Hammers retrieved");
    }
}

