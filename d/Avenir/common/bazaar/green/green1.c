// Green1 (/d/Avenir/common/bazaar/green/green1.c)
// creator(s):   Tepisch Sept 1994
// last update:  Lilith, 6:24 PM 4/21/97
// purpose:     A place for herbs, flowers, and veggies to be found
//
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/common/bazaar/green/std_green.c";
#include "/d/Avenir/common/bazaar/bazaar.h"
#include "/d/Avenir/common/herbs/herbsearch.h"

#define  WOLF_PROP "_wolf_i_riding"

string *herbs = HERB_MASTER->query_herbs( ({"garden"}) );
object  wolf, steed;

void
create_room()
{
   AE(GREEN + "green4", "south", 0);
   AE(GREEN + "green2", "west", 0);

   AI("brush", "It is composed of dense, low-growing shrubs.\n");
   AI("shrubs", "They appear to be evergreen.\n");

   SHORT("Western center of garden");
   make_the_room(" Herbs and other plants grow in profusion here. You "
      +"can hear the noise of a crowd to the north.\n");

   clone_object(OBJ + "door/g_gate1b")->move(TO);

    /*
     * This array provides the herbs to be found, the places to be 
     * searched, and the search delay.
     */
    set_up_herbs(({ ONEOF(herbs), ONEOF(herbs), ONEOF(herbs) }), 
        ({ "garden","beds","soil", "brush", "shrubs" }), 5);
    add_herb_file(HERB + "carlith");
    add_herb_file(GONDOR + "tuo");

}

void
reset_room()
{
    set_searched(0);
}


/*
 * This is the check for players who are riding steeds. 
 */
int 
steed_check(object tp)
{
    steed = tp->query_prop(LIVE_O_STEED);

    write("Your "+ steed->short() +" cannot fit through the gate.\n");
    tell_room(ENV(TO), QCTNAME(tp) +"'s "+ steed->short() +
        " cannot fit through the gate!\n", tp);
    return 1;
}

/*
 * Kalad doesn't use the LIVE_O_STEED prop,
 * so the Riders of the Red Fang get their own check.
 */
int riding_wolf(object ob) {    return (ob->id("wolf"));    }

int 
wolf_check(object tp)
{
    object *wolves;
    if (sizeof(wolves = filter(all_inventory(tp), "riding_wolf", TO)))    
    {
        wolf = wolves[0];      
        write("Your "+ wolf->short() +" cannot fit through the  "+
            "gate.\n");
        tell_room(ENV(TO), QCTNAME(tp) +"'s "+ wolf->short() +
            " cannot fit through the gate!\n", tp);
        return 1;
    }
}
     
/*
 * Function name: prevent_enter
 * Description:   Called when an object is trying to enter this container to
 *                see if we will allow it in.
 * Arguments:     object ob - the object that is trying to enter.
 * Returns:       1 - The object is not allowed to enter
 *                0 - The object is allowed to enter
 */
public int 
prevent_enter(object ob)
{

    if (ob->query_prop(LIVE_O_STEED))
    {    
        steed_check(ob);
        return 1;
    }

    if (ob->query_prop(WOLF_PROP))
    {
        wolf_check(ob);
        return 1;
    }     
   
    return 0;
}
