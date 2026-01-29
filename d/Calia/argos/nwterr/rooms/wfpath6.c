/* Trail to Eldoral, above falls
**
** History
** Date        Coder       Action
** --------  ------------  ----------------------
** 2/22/97   Zima          Created
** 8/10/03   Jaacar        Added Zombies
*/
/* inherits/includes */
inherit "/std/room";
#include <macros.h>
#include "defs.h"
 
#define NUM 3
#define THIS this_object()


object this, *zombie = allocate(NUM);

void
make_monster(int i)
{
    zombie[i] = clone_object("/d/Calia/argos/nwterr/monsters/marsh_zombie");
    zombie[i]->move(this);
    tell_room(this, QCTNAME(zombie[i]) + " arrives.\n");
}

void
reset_room()
{
    int i;

    for (i=0; i < NUM; i++)
        if (!zombie[i])
            set_alarm(0.5, 0.0, &make_monster(i));
}

/* room definition */
void create_room() {
   set_short("A narrow trail through a mountain forest");
   set_long(
        "You are walking along a narrow trail through a heavy forest of "+
       "pines and firs atop a mountain. You hear the roar of the falls to "+
       "the south, while the trail winds its way northeast deeper into the "+
       "forest. The trees grow thickly around you, their upper branches "+
       "interlaced into a tunnel over the trail. Typical sounds of "+
       "small forest creatures sprinkle the soothing roar of the nearby "+
       "falls.\n");
 
   add_item("trail",
       "The trail is nothing more than an animal path along the forest "+
       "floor here, leading northeast deeper into the woods and south toward "+
       "the roar of the falls.\n");
   add_item(({"forest","woods","trees","pines","firs"}),
       "A forest of towering trees, mostly pines and firs, grows all "+
       "around you on the mountain top.\n");
   add_item("mountain",
       "You are near the peaks of the mountain, though the heavy forest "+
        "limits your view. There is a small crack in the mountain.\n");
    add_item(({"crack","small crack"}),"The small crack runs about four "+
        "feet upwards in the mountain and appears to be large enough "+
        "for someone to crawl into.\n");
   add_item(({"waterfall","falls"}),
       "You can't see them from here, but you hear the roar of the falls "+
       "to the south.\n");
 
   /* exits */
   add_exit(ELDORAL_CONN,"northeast",0);
   add_exit("wfall3","south",0);
   this = THIS;
   set_alarm(1.0, 0.0, reset_room);
}

int
do_crawl(string str)
{
    if (!str)
        return 0;
    if (str != "into crack")
    {
        notify_fail("Crawl where? Into the crack? <crawl into crack>\n");
        return 0;
    }

    say(QCTNAME(TP)+" crawls into the crack.\n");
    TP->move_living("M","/d/Calia/eldoral/tunnel/rooms/crack_entrance");
    tell_room(environment(TP),QCTNAME(TP)+" arrives through the crack.\n",({TP}));
    return 1;
}

void
init()
{
    ::init();
    add_action(do_crawl,"crawl");
}
