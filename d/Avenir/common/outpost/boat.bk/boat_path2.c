// file name:   /d/Avenir/common/outpost/boat_path2.c
// creator(s):  Kazz    April 1995
// last update: May (added do_call_boat)
//              Boriska, Sep 95 Changes in bazaar ship project
//		May 1996, Denis: Removed this_object();
// purpose:     The first lake-level view of the Lake.
//		Beach 'dock' for the boat to the Park.
// bug(s):
// to-do:       

# include "/d/Avenir/common/common.h"
# include "/d/Avenir/include/relation.h"
# include "/d/Avenir/common/outpost/outpost.h"
# include "/d/Avenir/common/outpost/boat/ship.h"
# include "/sys/ss_types.h"

# pragma save_binary

inherit "/std/room";
inherit "/d/Avenir/common/outpost/boat/pipe.c";

private object ship;

void init()
{
    ::init();
    init_boat_room();
}

void create_room()
{
    set_short("sandy beach");
    set_long("You stand on a thin sandy beach within an immense underground "+
             "cavern. A great, underground sea begins at your feet, and "+
             "stretches further to the north than you can see. The entire "+
             "great cavern is lit by strange phosphorescent veins running "+
             "through the ceiling far overhead. A short metal pipe leans "+
             "out of the calm sea.\n");
  
    add_exit(OUTPOST + "boat/boat_path1","southwest");
  
    add_item(({"sea", "great sea"}),
	   "The light from above does not penetrate the sea, making "+
	   "it a heavy shade of black.\n" );
    add_item(({"light", "white light", "glowing light"}),
	   "The light gives an unearthly glow to everything.\n" );
    add_item(({"veins", "strange veins"}),
	   "The veins criss-cross the entire cavern ceiling. They "+
	   "are more concentrated to the far east.\n" );
    add_item(({"island", "islands"}),
	   "Trees and vegetation grow on the nearest islands. You can "+
	   "barely discern a boat travelling between distant "+
	   "islands.\n" );
    add_item(({"cavern", "underground cavern"}),
	   "The cavern stretches farther than you can see. Strangely "+
	   "glowing veins cast light down onto the great sea and "+
	   "islands.\n" );

    add_item(({"beach", "sandy beach"}),
	   "The beach marks the beginning of the great sea. From the "+
	   "here, you can return to the tunnel and fort.\n" );

    add_item(({"pipe", "metal pipe"}),
	   "@@pipe_description@@" );
    add_item(({"scratches", "pipe scratches"}),
	   "@@pipe_scratch_description@@" );
  
    add_cmd_item(({"sea", "in water", "water", "great sea", "in sea"}),
	       ({"swim"}),
	       ("The islands are too far away to swim to.\n" ));

    LIGHT;
    IN;

    ship = clone_object(OUTPOST + "boat/ship");
    ship->move(this_object(),1);
    ship->start_ship();
    set_boat_start_room(this_object());
    BAZAAR_DOCK->set_boat_start_room(this_object());

}

object query_ship() { return ship; }

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (IS_INFIDEL(ob) &&
       (file_name(from) == "/d/Avenir/common/outpost/boat/deck"))
    {
        write_file("/d/Avenir/log/misc/infidel", 
        ob->query_real_name() +" had infidel status removed at "+
        ctime(time())+".\n");
        ob->set_skill(SS_INFIDEL, 0);
    }
}


