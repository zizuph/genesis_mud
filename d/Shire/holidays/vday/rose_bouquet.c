/*
 * rose_bouquet.c  -> Goes with the florist.c :)
 * -- Finwe, February 2001
 *
 *
 */

inherit "/std/object";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <macros.h>

//int do_egg(string str);
//int do_roll(string str);

string thiscolor;

void
create_object()
{
    thiscolor = ONE_OF_LIST(({"yellow","red","pink","varigated","white",
	"orange","red","white","red"}));

    set_name("roses");
    add_name("dozen roses");
    plural_short("roses");
    set_adj(thiscolor);
    set_short("dozen " + thiscolor + " roses");
    set_long("The " + thiscolor + " roses are lovely and perfect. They " +
        "are very fragrant and arranged in a woven brown basket. " +
        "The buds are just beginning to open and are surround by " +
        "a swath of fern and baby's breath. Miraculously the " +
        "roses are fresh as the day they were picked.\n");

    add_item("basket",
        "The basket is made of brown woven fibers. It is " +
        "watertight and looks sturdy. A handle on the basket " +
        "enables you to carry the basket.\n");
    add_item("baby's breath",
        "They are small white flowers on delicate stems. They " +
        "are arranged, enhancing the bouquet of roses.\n");
    add_item(({"fern", "ferns", "swath of ferns"}),
        "It is deep green and finely tooths. It is arranged in " +
        "the bouquet to accent the flowers.\n");


    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 74);
    add_prop(OBJ_I_VALUE, 0);

}

void
init()
{
    ::init();
    add_action("do_smell","smell");
//    add_action("do_egg","egg");
//    add_action("do_roll","roll");
}

int
do_smell(string str)
{

    if((str != "roses") && (str != "basket of roses") && (str !="basket of " + thiscolor + " roses"))
    {
	write("Smell what? Smell your roses?\n");
	return 1;
    }

    write("You close your eyes and lean down and smell your basket of "+
        thiscolor+" roses. A smile comes to your face as you " +
        "enjoy the fragrance.\n");
    say(QCTNAME(TP)+ " closes "+HIS_HER(TP)+" eyes and smells a basket of "+
        thiscolor+" roses. A contented smile fills " +HIS_HER(TP)+" face.\n");
    return 1;

}
/*
int
do_egg(string str)
{
    object target;

    if(!str)
    {
	write("Egg whom?\n");
	return 1;
    }
    if(!present(str, environment(TP)))
    {
	write("There is no "+str+" here.\n");
	return 1;
    }

    target = present(str, environment(TP));
    if(!living(target))
    {
	write("That target is not worthy of your attention.  Try something that "+
	  "moves.\n");
	return 1;
    }

    write("You throw your "+thiscolor+" egg at "+ target->query_the_name(this_player()) +
      "!\nThe egg crumbles with the force of the impact and egg yolk begins to "+
      "drip down "+target->query_possessive()+" leg.\nWhat a mess!\n");

    say(QCTNAME(TP)+ " throws "+HIS_HER(TP)+ " "+thiscolor+ " egg at "+
      target->query_name() +"!\nIt leaves an oozing slime that drips down "+
      target->query_possessive()+ " leg.\nWhat a mess!\n",({TP,target}));

    target->catch_msg(QCTNAME(TP)+" throws "+HIS_HER(TP)+ " " +thiscolor+
      " egg at you.  It hits you hard and leaves an oozing slime that drips down your "+
      "leg.\n");

    remove_object();
    return 1;

}
*/