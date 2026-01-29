
// file name: park.h
// creator(s): Ilyian (8 March, 1995)
// last update: 4 April (added all the description definitions)
// purpose: File to include in all /d/Avenir/common/park rooms
// note: IN_IN still dosen't seem to work..
// bug(s):
// to-do:

#include "/d/Avenir/common/common.h"

#define DELAY 18
#define DUST 2
#define DIRT 5
#define SGT seteuid(getuid(this_object()));
#define PK_JUNG "/d/Avenir/common/holm/jungle/"

// I'm putting herbs around here?
#include "/d/Avenir/common/herbs/herbsearch.h"

// Descriptions for the cell rooms.
#define CELLWALL   \
   AI(({"wall","walls"}),"The crumbling stone walls of this small room "\
     +"slant dangerously inwards, threatening to fall at any time. "\
     +"Between the cracks in the stones flood the watery light of the "\
     +"outside, and creeping vines slowly force their way in through "\
     +"the wall.\n");

#define CELLGATE   \
   AI(({"gate","gates"}),"The gate to this room once stood strong, "\
    +"but had since rusted and fallen into decay through neglect. It "\
    +"hangs loosely on one hinge, and is no longer functional in any "\
    +"way.\n");

#define CELLSTONE   \
   AI(({"stone","stones"}),"The stones from which this room was "\
    +"constructed are granite-like, but have decayed so much over "\
    +"time that they are crumbling and ready to collapse.\n");

#define CELLHINGE   \
   AI(({"hinge","hinges"}),"The hinges which once held the gate up "\
    +"are of iron, but have rusted so heavily that they are nothing "\
    +"but twisted metal.\n");

#define CELLCEILING   \
   AI(("ceiling"),"The ceiling of this cell was once as strong as the "\
    +"rest of it, but now it has crumbled almost to the point that "\
    +"it is collapsing. You can see the gloom of the park outside "\
    +"filtering in between the gaps.\n");

#define CELLFLOOR    \
   AI(({"floor","ground"}),"The floor here was once made from "\
    +"closely fitted stones, but over the years they have been slowly "\
    +"seperated and torn apart by the relentless vines that creep "\
    +"their way in.\n");

#define CELLVINE    \
   AI(({"vine","vines","growth","vegeatation"}),"The vines that creep "\
    +"in through the walls, ceiling, and between the stones of the "\
    +"floor are gradually reclaiming this small room.\n");

#define CELLDUST   \
   AI(("dust"),"Some dust has acumulated on the floor. You notice "\
    +"some prints in the dust that look like they were made by hooves.\n");

#define CELLLEAVES   \
   AI(({"leaf","leaves"}),"Some leaves have blown in through the "\
    +"open doorway. They slowly decay along with the rest of the "\
    +"place.\n");

#define STDCELL         CELLVINE CELLFLOOR CELLCEILING CELLHINGE \
                        CELLSTONE CELLGATE CELLWALL CELLDUST \
                        CELLLEAVES



#define COURTWALL  \
   AI(({"wall","walls"}),"The stone walls which enclose the courtyard " \
    +"are high and strong. They seem to be in excellent shape, and " \
    +"preserved extraordinarily well from the effects of erosion.\n");

#define COURTGROUND  \
   AI(({"ground","pavingstones","cobblestones","paving","cobbles","stones"}), \
    "The ground in this courtyard is made up of tiny cobblestones that "\
    +"were once perfectly fitted together, although over the course "\
    +"of time many have become loose, or have been broken apart by "\
    +"the encroaching vines.\n");

#define COURTCEILING \
   AI(({"ceiling","roof"}),"You can barely make out the ceiling of "\
    +"the cavern, high above. No details are visible, only the massive "\
    +"veins of the light-giving rock that light the entire cavern.\n");

#define COURTVINES \
   AI(({"vine","vines","vegetation","plant","plants"}),"The vegetation "\
    +"in the courtyard is quite a bit less dense than in other areas "\
    +"of the park, possibly due to the solid construction of the "\
    +"walls.\n");

#define COURTLIGHT  \
   AI(("light"),"The light from above is watery and dim.\n");

#define COURTHUT  \
   AI(({"hut","building","room"}),"This is just a tiny little hut, "\
    +"constructed on the edge of the courtyard.\n");

#define STDCOURT     COURTLIGHT COURTVINES COURTCEILING COURTGROUND  \
                     COURTWALL


#define EPATH   \
   AI(({"path","ground","dirt"}),"The path is of simple dirt and " \
    +"quite narrow, bordered on both sides by a high wall of " \
    +"crumbling stone.\n");

#define EVINE   \
   AI(({"vine","vines","underbrush","weeds","weed"}),"The weeds and " \
    +"vines here slowly encroach in upon the path, climbing down " \
    +"over the walls and between the stones. All around, strange " \
    +"plants and vegetation grow, choking the area with life.\n");

#define EWALL  \
   AI(({"wall","walls","stone"}),"The walls that border the path are " \
    +"too high to see over, but through cracks in the stones you can " \
    +"see thick and fierce vegetation growing.\n");

#define EPATHG  \
   AI(({"path","ground","dirt"}),"The path here is made up of " \
    +"finely cut stones that are fitted together perfectly. The " \
    +"vines and weeds in the area are slowly reclaiming the path though, "\
    +"and it will probably not last much longer.\n");

#define ECANOPY   \
   AI(("canopy"),"Vegetation that has grown together overhead forms "\
    +"a natural canopy, through which little of the already-dim light "\
    +"filters through.\n");

#define STDEPATH    ECANOPY EWALL EVINE EPATH COURTLIGHT COURTCEILING
#define GEPATH      ECANOPY EWALL EVINE EPATHG COURTLIGHT COURTCEILING


