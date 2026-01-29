
#pragma save_binary

inherit "/d/Shire/room";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Shire/common/defs.h"
#include "/d/Shire/herald/herald.h"
#define JOINROOM "/d/Shire/guild/heralds/room/join"

void add_stuff();
void reset_room() { add_stuff(); }



void
create_room()
{
    set_short("Inside the large maple tree");
    set_long("Standing inside the large maple tree, you realize the " +
        "vastness of the trunk, here at ground level. For nearly twenty " +
        "feet in any direction, there is open space, amazing, considering " +
        "that this is indeed a living tree. Sap dripping down the " +
        "barky walls can attest to the life of this tree, and an aura " +
        "of goodness pervades this chamber. Around all the walls are " +
        "drying racks and hanging from them are rather large leather " +
        "pouches. A rope ladder leads up, out onto the tree, and you " +
        "can slide back the bark door that allowed entrance in order " +
        "to exit.\n");

    add_item(({"ladder","rope ladder"}),
      "It is used to climb up and down on.\n");
    add_item(({"trunk","tree","maple tree","large maple tree"}),
      "This is the inside of a vast, living maple tree. The magic "+
      "that keeps this tree alive also makes it thrive, as evidenced "+
      "by the sheer size of the inside and outside of the tree.\n");

    add_item(({"sap","barky walls","wall","bark"}),
      "The sap is fresh and flowing down the bark on the inside.\n"+
      "The tree seems to be in excellent health.\n");

    add_item(({"drying racks","racks","rack","drying rack"}),
      "The drying racks are where herbs are stored to dry for "+
      "further use.\n");

    add_item(({"large leather pouches","leather pouch","leather pouches"}),
      "The large leather pouches are used for keeping herbs fresh, for "+
      "use in spells or ingredients in a potion.\n");

    add_item(({"rope","rope ladder"}),
      "It leads through a small hole onto the top of the tree.\n");

    add_item(({"door","bark door"}),
      "It is made of bark and melts in with the rest of the tree. "+
      "Sliding it will always lead you out.\n");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);

    add_exit(HERALD_DIR + "board","up");
    


    reset_room();
}

void
init()
{
    ::init();
    add_action("do_slide","slide");

}

int
do_slide(string str)
{

    if ((str == "door") || (str == "bark door"))
    {
        write("The door slides open easily and you go out.\n");
        say(QCTNAME(TP)+ " slides the bark door open and leaves through it.\n");
        TP->move_living("M","/d/Shire/guild/heralds/room/join",1);
        tell_room(JOINROOM,QCTNAME(TP)+" comes crawling out of the tree.\n",TP);
        return 1;
    }

    write("Slide what?\n");
    return 1;
}


void
add_stuff()
{
    object herbalist;

    if(!present("herbalist"))
    {
        herbalist = clone_object(HERALD_DIR + "herbalist");
        herbalist->move(TO);
    }

}
