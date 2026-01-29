#include "default.h"
inherit PORT_ROOM;

#define PG PORT + "npc/pgmember"
object ob1;
object ob2;

void
create_port_room()
{
    set_short("Street by the Bay");
    set_long("This street runs aside the bay, travelling in an east-west "+
      "direction. The breaking of the surf just to the south sends up a "+
      "light shower of moisture that makes anything above a run rather "+
      "dangerous here, because of the increased chance of slipping and "+
      "falling. The cobblestones beneath you are covered with grime. A "+
      "large building lies to the north, while an enormous ship is docked "+
      "in the south.\n");
    set_time_desc("A large group of people pass in and out of the building "+
      "in the north.\n","Only a few people are passing in and out of the building "+
      "in the north.\n");
    add_item(({"street"}),"A narrow road that hugs the coastline.\n");
    add_item(({"cobblestones","cobblestone"}),"The pavement is kept "+
      "continually slick from the breaking of the surf. A layer of grime "+
      "blankets its surface.\n");
    add_item(({"layer","grime"}),"A number of rootless plants such as "+
      "moss and lichen have taken to growing on the cobblestones.\n");
    add_item(({"bay"}),"Colored a deep azure, its beauty is mirrored "+
      "only by the skies above.\n");
    add_item(({"skies","sky"}),"It is a mirror image of the bay beneath "+
      "it.\n");
    add_item(({"large building","building"}),"A large structure built "+
      "from hardwood planks. It looks like a warehouse. The section of it "+
      "immediately to your north has a sign hanging upon it.\n");
    add_item(({"sign"}),"Faded writing is visible on it. Perhaps you "+
      "should read it.\n");
    add_item(({"enormous ship","ship"}),"An ancient looking galleon whose "+
      "massive masts tower above the docks.\n");
    add_item(({"people"}),"They come from all walks of life.\n");
    add_exit(PORT + "s72", "west");
    add_exit(PORT + "s60", "north");
    add_exit(PORT + "s74", "east");
    reset_room();
    set_alarm(10.0,60.0,"pub");
}

init()
{
    ::init();
    AA(read_sign,read);
}

string
sign()
{
    return "\n"+
    " (!)(!)(!)(!)(!)(!)(!)(!)(!)(!)\n"+
    " (!)^^^^^^^^^^^^^^^^^^^^^^^^(!)\n"+
    " (!)   The  Liquid  Booty   (!)\n"+
    " (!) ~~~~~~~~~~~~~~~~~~~~~~ (!)\n"+
    " (!)  All paying customers  (!)\n"+
    " (!)        WELCOME!        (!)\n"+
    " (!) ^^^^^^^^^^^^^^^^^^^^^^ (!)\n"+
    " (!)  Open from dawn until  (!)\n"+
    " (!)   the next sunrise.    (!)\n"+
    " (!)(!)(!)(!)(!)(!)(!)(!)(!)(!)\n"+
    " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}

reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(PG);
	ob1 -> move_living("xxx",TO);
    }

    if(!ob2)
    {
	ob2 = clone_object(PG);
	ob2 -> move_living("xxx",TO);
	ob1 -> team_join(ob2);
    }

}

pub()
{
    tell_room(TO,"Hearty laughter sounds from the north.\n");
    return 1;
}

