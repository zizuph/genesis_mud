#include "../default.h"
inherit PORT_ROOM;

void reset_room();
void do_search();
int recently_searched;

void
create_port_room()
{
    set_short("A clothes room");
    set_long("This is another small room within the Seahawk's lower "+
      "level. The entire room is bare of furnishment, in fact, the only "+
      "thing within the room, besides dust and cobwebs, is a pile of "+
      "dirty clothes in the corner.\n");
    add_item(({"dust"}),"It blankets the entire room, coloring everything "+
      "a light gray.\n");
    add_item(({"cobwebs","cobweb"}),"The thin flimsy strands cover "+
      "many parts of the room, mixing with the ever present dust.\n");
    add_item(({"pile of dirty clothes","pile","dirty clothes","clothes"}),
      "Shirts, pantaloons, and other articles of clothing. However, due "+
      "to age and lack of care, they are little more than rags.\n");

    add_prop(ROOM_I_INSIDE,1);

    add_exit(PORT + "seahawk/fl6", "south");
    reset_room();
}

void
reset_room()
{
    recently_searched = 0;
}

void
init()
{
    ::init();
    add_action("search","search");
}

int
search(string s)
{
    if(!s || s != "pile")
	return 0;
    if(recently_searched)
    {
	write("You find nothing but a few rat hairs.\n");
	return 1;
    }

    write("You start to search the pile.\n");
    say(QCTNAME(TP) + " starts to search the pile.\n");
    set_alarm(4.0,0.0,"do_search");
    return 1;
}

void
do_search()
{
    recently_searched = 1;
    write("You've disturbed a nest of rats!\n");
    say(QCTNAME(TP) + " disturbed a nest of rats!\n");
    clone_object(PORT + "npc/grat")->move(TO);
    clone_object(PORT + "npc/grat")->move(TO);
    clone_object(PORT + "npc/grat")->move(TO);
    clone_object(PORT + "npc/grat")->move(TO);
    clone_object(PORT + "npc/grat")->move(TO);
    clone_object(PORT + "npc/grat")->move(TO);
    tell_room(TO,"Half a dozen rats burst forth from the pile!\n");
    return;
}

