inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
string sign_text();
 
void
create_room()
{
    set_short("The township Blacksmith");
    set_long("You have entered the local blacksmith's shop. " +
        "A large forge occupies the south side of the room.  Next to " +
        "it is a trough for quenching the hot metal. The walls are " +
        "covered with a variety of tools, hammers and huge tongs. " +
        "There is also a small sign hanging here.\n");
 
    add_item(({"hammer","hammers"}),"A selection of heavy hammers, "+
        "used to shape hot metal.\n");
    add_item("tongs","Several large pairs of tongs, used to remove hot "+
        "metal from the forge, are hanging from hooks on the wall.\n");
    add_item("forge","A large coal forge takes up most of the northern "+
        "wall. As you walk closer to it, you can feel the heat, and "+
        "wonder how someone can work in such a place.\n");
    add_item("trough","A small wooden trough full of a murky brown " +
        "water.\n");
 
    add_item("sign","A small sign fixed to the wall that reads \n\n" +
        sign_text());
 
    add_prop(ROOM_I_INSIDE,1);
 
    clone_object( TOWNSHIP_DIR + "obj/wrack")->move(TO);
    clone_object( TOWNSHIP_DIR + "obj/anvil")->move(TO);
 
    add_exit( TOWNSHIP_DIR + "street_e3_3","north",0,1);
 
    set_alarm( 1.0,0.0,"reset_room");
}
 
 
void
reset_room()
{
    object blacksmith;
 
    blacksmith = present("blacksmith");
    if (blacksmith && blacksmith->query_name() != "corpse")
        return;
    blacksmith=clone_object( TOWNSHIP_DIR + "npc/blacksmith");
    blacksmith->arm_me();
    blacksmith->move(TO);
    tell_room(TO,QCNAME(blacksmith) + " arri\n");
}
 
 
void
init()
{
    ::init();
    add_action("do_read","read");
}
 
 
int
do_read(string str)
{
    notify_fail("Read what?\n");
 
    if (!str || str != "sign")
        return 0;
 
    write("The sign reads\n\n" + sign_text());
    return 1;
}
 
 
string
sign_text()
{
  /*
    return "Services offered are mending or sharpening of damaged " +
        "weapons.  Use 'cost <weapon>' to get an estimate of the " +
        "repair cost and 'repair <weapon>' to get it fixed.\n\n";
	*/
    return "The blacksmith currently is not doing any repairs. He "+
	"has decided to change his offering to repairing armours "+
	"and is waiting for the necessary equipment that he has on "+
	"order. Please try again at a later date.\n\n";
}
