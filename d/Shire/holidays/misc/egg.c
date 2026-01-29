/*
 * egg.c  -> Goes with the eggmaker.c :)
 * Dunstable
 *
 *
 */

inherit "/std/food";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <macros.h>

int do_egg(string str);
int do_roll(string str);

string thiscolor;

void
create_food()
{
    thiscolor = ONE_OF_LIST(({"red","yellow","green","brown","scarlet","black","ocher","peach","ruby","olive","violet","fawn","lilac","gold","chocolate","mauve","cream","crimson","silver","rose","azure","lemon","russet","grey","purple","white","pink","orange","blue"}));

    set_name("egg");
    add_name("easter egg");
    set_adj(thiscolor);
    set_short(thiscolor + " colored egg");
    set_long("This "+thiscolor+ " egg is very beautiful and precious. "+
      "It is also fragile so be careful with it or it might break. Definitely don't "+
      "egg anyone. Rolling it around on the ground might be ok, though.\n");

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 74);
    add_prop(OBJ_I_VALUE, 0);
    set_amount(25); 


}

void
init()
{
    ::init();
    add_action("do_egg","ooze");
    add_action("do_egg","egg");
    add_action("do_roll","roll");
}

int
do_roll(string str)
{

    if((str != "egg") && (str != "easter egg") && (str !="egg on the ground"))
    {
	write("Roll what, a "+str+"?  Why not roll the egg?\n");
	return 1;
    }

    write("You roll the "+thiscolor+" egg carefully on the ground, taking care not to "+
      "damage it.\n");
    say(QCTNAME(TP)+ " rolls the "+thiscolor+" egg on the ground, taking "+
      "care not to damage it, isn't that cute?\n");
    return 1;

}

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
	write("That target is not worthy of your attention. Try something that "+
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
      " egg at you. It hits you hard and leaves an oozing slime that drips down your "+
      "leg.\n");

    remove_object();
    return 1;

}
