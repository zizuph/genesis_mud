#include "defs.h"

inherit TELBERIN_CANTORS_WAY;

/* Prototypes */
public void        create_cantors_way();
public int         check_exit();


public void
create_cantors_way()
{
    set_em_long("Cantors Way runs southeasterly here, where its gradual"
      + " arc turns to head towards Cantors Plaza. Just to the south,"
      + " a long pool of crystal blue water extends the length of the"
      + " boulevard, rimmed by a green lawn on either side. Song and"
      + " bells can be heard over the din of the normal traffic here,"
      + " as street musicians have taken up voice and instrument to"
      + " fill the Arts Quarter with their skillful craft. Just to the"
      + " north, the Silver Swan, the main Inn of Telberin, rises above"
      + " the rooftops to dominate the street corner.\n");

    add_item( ({ "rooftops", "rooftop" }),
        "The building to the north is clearly the tallest building in"
      + " this portion of the Arts Quarter.\n");

    add_item( ({ "song", "bells", "music" }),
        "Music drifts through the quarter, adding a sense of gaiety"
      + " to the otherwise standard events of the street.\n");
    add_item( ({ "musician", "musicians", "street musician",
                 "street musicians" }),
        "A few musicians have decided to add to the abiance of"
      + " the Arts Quarter with their song. It is clear that these"
      + " individuals are well-trained in what they do. Their sound"
      + " is clear and pleasing.\n");
    add_item( ({ "inn", "silver swan", "swan", "silver swan inn",
                 "inn of telberin", "building", "white building",
                 "large building", "large white building" }),
        "The large white building to the north appears somewhat derelict."
      + " A sign on the door reads: We have moved to Sparkle due to lack of"
      + " business here in Telberin.\n");


    add_cmd_item( ({ "at sign", "sign" }), ({ "read", "exa", "examine",
                     "look" }),
        "A sign on the door of the building to the north reads: We have"
      + " moved to Sparkle due to lack of business here in Telberin.\n");
    add_item( ({ "street corner", "corner" }), long);

    add_exit("cantors_way06", "west");
    add_exit("arts/cantors_plaza", "southeast");
    add_exit("arts/inn", "north", check_exit, 1, 1);

//  add_building("/d/Emerald/telberin/arts/inn");
}


/*
 * Function name:        check_exit
 * Description  :        We're closing down the inn here and moving it to
 *                       Sparkle, so we'll let players know this.
 * Returns      :        int 1 - the way is closed
 */
public int
check_exit()
{
    write("The Silver Swan Inn appears to have been closed. On the door you"
      + " see a sign that reads: We have moved to Sparkle due to lack of"
      + " business here in Telberin.\n");

    return 1;
} /* check_exit */
