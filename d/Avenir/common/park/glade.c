
// file name: glade.c
// creator(s): Ilyian (April, 1995(
// last update: Lilith Dec 2004: update for quest reset.
// purpose: Faerie glade where the faerie quest can be done.
// note:
// bug(s):
// to-do: add the actual quest

inherit "/std/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "park.h"

#ifndef SCROLLING_LOG
#define SCROLLING_LOG(file, entry)   ((file_size(file) > 10000) ? \
    (rm(file) && write_file(file, ctime(time()) + ": "+ \
    entry + "\n")) : (write_file(file, ctime(time()) + ": " + entry + "\n")))
#endif

static object andromahi;
static object *faeries = allocate(8);

init()
{
        ::init();
        add_action("thruwall","push");
}

create_room()
{
set_short("Glade");
set_long("You have entered into a wide glade of grass and flowers "
        +"surrounded by high walls "
        +"of vegetation that seem quite strong, except that it is "
        +"a bit thinned in a small section on the west side. "
        +"A large ring of white stones lies in the "
        +"center, from which a mysterious aura emanates. The canopy "
        +"of trees overhead hides the cavern above from view, creating "
        +"the illusion that you are out in the open world. A small stream "
        +"flows noisily over some rocks on the east side of the "
        +"glade.\n");

AI(({"glade","ground","grass"}),"The ground is of grass that seems "
        +"to be immaculately tended. Small flowers grow at random "
        +"intervals along the ground, and in the center of the glade "
        +"is  ring of small white stones.\n");

AI(({"flower","flowers"}),"A wide variety of strange flowers grow here, "
        +"rising up from the grass in seemingly random intervals, although "
        +"you suspect there is some sort of pattern underlying their "
        +"distribution.\n");

AI(({"wall","vegetation","plants"}),"The entire glade is surrounded by "
        +"a think wall of vegetation and plant life. It was obviously "
        +"constructed thorugh painstakingly tending the manipulating the "
        +"growth in the area. It makes a formidable wall, although a "
        +"section in the west side of the glade seems a bit thinner than "
        +"the rest of it, so that you might be able to push your way "
        +"through.\n");

AI(({"stream","brook","water"}),"This is a little narrow brook that "
        +"winds its way noisily from a gap in the northeast hedges to "
        +"a small hole in the ground in the southeast corner of the "
        +"glade. The water looks fresh and pure, although very cold.\n");

AI(("hole"),"The water from the stream flows into a dark hole in the "
        +"ground, where it proceeds to flow underground.\n");

AI(("gap"),"The gap in the northeast hedges is very small. It seems as "
        +"though the force of the stream has opened it up.\n");

AI(({"ring","stone","stones","circle"}),"In the center of the glade is a ring "
        +"of dazzling white stones, each arranged about a handspan apart "
        +"in a perfect circle. A mysterious feeling of power emanates "
        +"from it, one which you would not feel right in disturbing. A "
        +"gentle mist seems to hang over the ring, nearly invisible.\n");

AI(({"mist","fog"}),"The mist that lies over the ring of stones is shallow "
        +"and white. You can see through it, yet you feel as though there "
        +"is some benevolant force eminating from it.\n");

AI(({"tree","trees","canopy","ceiling"}),"Powerful "
        +"trees rise up from the other "
        +"side of the wall of vegetation, and their branches extend "
        +"and mesh over the glade, hiding the view of the cavern "
        +"ceiling.\n");


add_prop(ROOM_I_LIGHT,1);
IN

   add_prop(OBJ_I_CONTAIN_WATER, 1);
  add_prop(OBJ_I_SEARCH_TIME,2);
  add_prop(OBJ_S_SEARCH_FUN,"herb_search");
  add_herb_file(HERB+"fordinfa.c");

reset_room();

}

thruwall(string str)
{
        if ((str=="wall")||(str=="through wall")||(str=="vegetation")||

          (str=="thru wall"))
                {
                write("You press yourself against the "
                     +"vegetation, and finally it gives way before "
                     +"you.\n");
                say(QCTNAME(this_player())+ " pushes on"
                        +" the wall of vegetation, and then "
                        +"passes through it.\n");
                this_player()->move_living("through the wall",PK+"enterlab");
                SCROLLING_LOG("/d/Avenir/log/quest/rescue_faerie", 
                     capitalize(QCTNAME(TP)) +" found faerie glade.");
                return 1;
                }
}


reset_room()
{
    object obj;
    int     i = sizeof(faeries); 

    while(i--)
    {
        if (!objectp(faeries[i]))
        {
            faeries[i] = clone_object(PK+"mon/std_faerie.c");
            faeries[i]->move(this_object());
        }
    }
  if (!andromahi)
   {
      andromahi = clone_object(PK+"mon/andromahi.c");
      andromahi->move_living("M", this_object());
    }

    obj = present("astarte", this_object());
    if (obj)
    {
         obj->remove_object();
    }


     set_searched(0);
}


