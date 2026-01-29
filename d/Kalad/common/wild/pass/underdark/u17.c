/*
 * /d/Kalad/common/wild/pass/underdark/u17.c
 * Purpose    : If you have to ask...
 * Located    : Under Hespyre Mts.
 * Created By : Antharanos
 * Modified By: Nikklaus, Oct'97: adapted to dark_dom
 */

# pragma strict_types
# include "dark_dom.h"

inherit DARK_DOM;
object ob1;
object ob2;
object ob3;
object ob4;

void
create_dark_dom()
{
    set_short("Giant Cave");
    set_short("Giant Cave");
    set_long("This gigantic cave is so large that its outer reaches are beyond "+
      "your range of sight. What you can see is a rough stone floor covered "+
      "with an abundant amount of droppings and pointy stalagmites. The ceiling "+
      "above is littered with many long stalactites, the perfect perch for "+
      "bats and their ilk. The cavern entrance lies to the northwest.\n");
    add_item(({"rough stone floor","rough floor","stone floor","floor"}),
      "The rocky ground is covered with some animals' droppings.\n");
    add_item(({"rocky ground","ground"}),"Made of the strangely dark stone "+
      "of the underdark, it seems to radiate darkness.\n");
    add_item(({"droppings","dropping"}),"It would appear to be the waste matter "+
      "of an extremely large number of bats, perhaps a colony of them.\n");
    add_item(({"stalagmites","stalagmite"}),"Jutting up from the ground "+
      "beneath you, they seem to remind you of the jagged teeth of a "+
      "waiting predator.\n");
    add_item(({"ceiling"}),"It lies far above you, barely within your sight.\n");
    add_item(({"stalactites","stalactite"}),"Jutting down from the "+
      "ceiling above, they look like the perfect home for a colony of bats.\n");
    add_item(({"cavern entrance","entrance"}),"The way out of the cave lies "+
      "to the northwest.\n");
    add_item(({"walls","wall"}),"Dark stone that is pockmarked with "+
      "cracks, holes and other depressions.\n");
    add_exit(DARK(u15), "northwest");
    set_alarm(1.0, 0.0, "reset_room");
}

void
reset_room()
{
    if(!ob1)
	(ob1 = clone_object(DEEP_BAT))->move_living("xxx", this_object());
    if(!ob2)
	(ob2 = clone_object(DEEP_BAT))->move_living("xxx", this_object());
    if(!ob3)
	(ob3 = clone_object(DEEP_BAT))->move_living("xxx", this_object());
    if(!ob4)
	(ob4 = clone_object(DEEP_BAT))->move_living("xxx", this_object());
}
