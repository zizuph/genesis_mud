/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 *
 * Dwarven Stronghold
 * Tomas  -- Jan. 2000
 */

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <stdproperties.h>
#include <filter_funs.h>

inherit STDROOM;

#define DEFAULT  "/d/Terel/mountains/stronghld/"
#define AREA        ({ DEFAULT + "roada", \
                           DEFAULT + "roadb",  \
                           DEFAULT + "roadc", \
                           DEFAULT + "roadd", \
                       DEFAULT + "roade", \
                       DEFAULT + "fielda", \
                       DEFAULT + "fieldb", \
                       DEFAULT + "fieldc", \
                       DEFAULT + "fieldb", \
                       DEFAULT + "fieldd", \
                       DEFAULT + "fielde", \
                       DEFAULT + "fieldf", \
                       DEFAULT + "fieldg", \
                       DEFAULT + "fieldh", \
                       DEFAULT + "fieldi", \
                       DEFAULT + "fieldj", \
                       DEFAULT + "walk1", \
                       DEFAULT + "walk2", \
                       DEFAULT + "walk3", \
                       DEFAULT + "walk4", \
                       DEFAULT + "walk5", \
                       DEFAULT + "walk6", \
                       DEFAULT + "walk7", \
                       DEFAULT + "walk8", \
                       DEFAULT + "walk9", \
                       DEFAULT + "walk10", \
                       DEFAULT + "walk11", \
                       DEFAULT + "walk12", \
                       DEFAULT + "walk13", \
                       DEFAULT + "walk14", \
                       DEFAULT + "walk15", \
                       DEFAULT + "walk16", \
                       DEFAULT + "walk17", \
                       DEFAULT + "walk18", \
                       DEFAULT + "walk19", \
                       DEFAULT + "walk20", \
                       DEFAULT + "walk21", \
                       DEFAULT + "walk22"})



public void
create_room()
{
    ::create_room();
    INSIDE;

    add_item(({"warhorn","horn"}),
       "A large warhorn suspended from the ceiling by chains " +
       "From the size of the horn you figure all of Stonehold " +
       "could hear it.\n");

    add_cmd_item(({"horn","warhorn"}),"blow","@@blowhorn");
    reset_room();

}

void
blowhorn()
{
    tell_room(TO,"You inhale deeply and blow as hard as you can " +
       "onto the warhorn. The MIGHTY BLAST of the horn deafens you slightly.\n");
    tell_room(AREA,"You hear the BLAST of a warhorn coming from the " +
       "catwalk.\n",TO);
    return;
}




