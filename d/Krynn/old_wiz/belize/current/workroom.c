inherit "/std/workroom";


inherit "/std/workroom";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

void
create_workroom()
{
INSIDE;
    set_short("Belize's workroom. ");
    set_long("The room is large and overfilled, yet seems somehow neat and " +
             "organized. Near the wall stands a trestle table. A big armchair " +
             "appears to be the only item of comfort. On the table you " +
             "can see some books and papers. Shelves line the walls and stand " +
             "freely throughout the room. They are filled with books and " +
             "scrolls cases and loose or bundled papers. Around and between " +
             "these are a bewildering array of magical and mundane items. " +
             "Leaning against the massive, square-cut stones is a mirror " +
             "nearly as tall as you. It is framed in stiffened leather dyed " +
             "a very dark hue. \n");
    add_item(({"shelves"}),"These old shelves contain a lot of mysteries. " +
                           "There are books and magical scrolls. \n");
    add_item(({"books","papers","scrolls"}),"Wow! What a collection of magical " +
                                            "knowledge! You think, that there " +
                                             "is not enough money on Krynn " +
                                            "if you want to buy them! \n");
    add_item(({"items","magical items","mundane items"}),"You can see boxes, " +
                                                         "stones, herbs... " +
                     "You don't know all these items. \n");
    add_item("armchair","This is very large and comfortable armchair. Why don't you sit in it? \n");
    add_item(({"mirror"}),"You can see an indistinct image of a library. \n");
    add_exit("/d/Krynn/common/domain_entr.c","krynn",0,1);
    add_exit("/d/Krynn/solamn/moor/room/road3.c","palanthas",0,1);
    add_cmd_item(({"armchair","in armchair"}),"sit","@@gorr");
   add_cmd_item(({"mirror","large mirror"}),"enter","@@tower");

}

void witamy(object player)
{
    player->catch_msg("Suddenly you see the image of Belize! He says: Welcome to my laboratory! \n");
}
void
enter_inv(object ob,object from)
{
    ::enter_inv(ob, from);
    if(ob->query_prop(LIVE_I_IS))
    set_alarm(2.0,0.0,&witamy(ob));
}
string
tower()
{   
    write("You feel,that your body sneaks easily into the mirror. You find yourself in a different place... \n");
    say(QCTNAME(this_player()) + " suddenly disappears in the mirror. When you look in it, you see only your image... \n");
    this_player()->move_living(0,"/d/Krynn/wayreth/tower/mage_library",1,0);
    return"";
}
string
gorr()
{
    write("You sit in the comfortable armchair. Suddenly you feel very sleepy... When you wake up, you are in a different place... \n");
    say(QCTNAME(this_player()) + " sits in comfortable armchair and disappears...Strange... \n");
    this_player()->move_living(0,"/d/Ansalon/gorr/workroom.c",1,0);
    set_alarm(3.0,0.0,"niespodzianka");
    set_alarm(6.0,0.0,"niespodzianka1");
    return"";
}
void niespodzianka()
{
    write(" \n\n\nYou hear the voice:\n\nCOME HERE, MORTAL ONE! \n"); 
}
void niespodzianka1()
{
    write("\n\n\n\n\n\n\nDeath whispers: I'm just kidding... HA, HA, HA!!!\n");
}

