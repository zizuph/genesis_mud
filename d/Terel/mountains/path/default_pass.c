/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * default_pass.c
 *
 * Default file for use with the lower level of the mountains
 * Tomas   -- Dec. 1999
 */

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/include/herb_arrs.h"

inherit "/d/Terel/std/herbsearch.c";
inherit "/d/Terel/std/room_tell.c";
inherit STDROOM;

#define  ONE_OF_LIST(array) ((array)[random(sizeof(array))])

public int cold_fatigue();




/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Mountain pass");
    set_long("The snow-bound pass was carved from solid rock " +
         "by the dwarven miners long ago. It traverses the dragon " +
         "tooth mountains from southwest to northeast, creating a " +
         "junction from the lower levels of Terel to the higher elevations " +
         "of the mountains. It keeps as much as possible to the high" +
         "peaks, which although beautiful and rugged, present numerous " +
         "problems for less experienced travellers who often find themselves " +
         "ill-equipped to handle the harsh climate. The weather here is cold " +
         "and brutal but perhaps the worst of which is the wind. " +
        "The wind through the pass blows constantly removing heat from " +
        "any exposed areas on your body. ");



   add_item(({"peaks","mountains","high peaks"}),"peaks.\n");

   add_item(({"pass"}),"This is a deep cleft between the " +
        "soaring magesty of the dragon tooth mountain peaks. Steep " +
        "embankments rise to either side of you blocking " +
        "out most of the light creating shadows and darkness " +
        "everywhere.\n");

   add_item(("path"),"The narrow path is littered with loose rock " +
      "and slate making the footing treacherous. Several small hearty " +
      "snow covered bushes and shrubs can be seen scattered about the " +
      "area.\n");

   add_item(("bushes"),"bushes.\n");

   add_item(("shrubs"),"shrubs.\n");

   set_tell_time(100 + random(200));
   add_tell("You shiver as a gust of wind blows through the pass.\n");



/*
 *
 * Thanks for the herb code Goldberry!
 *
 */
    
    set_up_herbs( ({ ONE_OF_LIST(FROST_HERBS),
                     ONE_OF_LIST(FROST_HERBS),
                     ONE_OF_LIST(FROST_HERBS),
                  }),
                  ({"bushes","shrubs"}) , 3 );

    

   
}


/*
 *
 * Thank you Shiva for writing the fatigue code below
 *
 */

public int 
cold_fatigue() 
{
   return (TP->query_prop("wearing_fur") ? 0 : 5 + random(10)); 
}


init()
{
    ::init();
    start_room_tells();
}

