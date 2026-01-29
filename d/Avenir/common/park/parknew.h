// file name: park.h
// creator(s): Farlong
// last update: Ilyian (8 March, 1995)
// purpose:
// note:
// bug(s):
// to-do:

#include "/d/Avenir/common/common.h"

#define DELAY 18
#define DUST 2
#define DIRT 5
#define SGT seteuid(getuid(this_object()));

#define MALEB clone_object(PK+"mon/bicorna")->move(this_object(),1);
#define FEMALEB clone_object(PK+"mon/bicornb")->move(this_object(),1);
#define BABYB clone_object(PK+"mon/bicornv")->move(this_object(),1);
#define YMALEB clone_object(PK+"mon/bicornblk")->move(this_object(),1);
#define YFEMALEB clone_object(PK+"mon/bicornbrn")->move(this_object(),1);

/*
Eg:
#define WATER  \
        AI(({"water","waters","lake"}),"The churning water of this "\
         +"underground lake is a shade "\
         +"of blue so deep it is almost black. Its surface is distorted "\
         +"by the waves, and it all moves slowly from the great rift on "\
         +"the west end of the cavern to the waterfall at the east ledge.\n");
*/


bldg.c:
   nothing for now
cell1.c
   wall, walls, gate, stone, hinge, hinges, ceiling

#define CELLWALL   \
   AI(({"wall","walls"}),"The crumbling stone walls of this small room "\
     +"slant dangerously inwards, threatening to fall at any time. "\
     +"Between the cracks in the stones flood the watery light of the "\
     +"outside, and creeping vines slowly force their way in through "\
     +"the wall.\n");

#define CELLGATE   \
   AI(({"gate","gates"}),"The gate to this room once stood strong, "\
    +"but had since rusted and fallen into decay through neglect. It "\
    +"hangs loosly on one hinge, and is no longer functional in any "\
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
    +"closely fitted stones, but over the years they have been slowly"\
    +"seperated and torn apart by the relentless vines that creep"\
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


