/* A small globe of Khalakor
 * To be found in the SW_speir
 * By Damaris 01/Y2K1
 */
#pragma strict_types

inherit "/std/object";
inherit "/lib/holdable_item";
#include <stdproperties.h>
#include <macros.h>

#define TP        this_player()
#define TO        this_object()
#define CAP(x)    capitalize(x)
#define ENV(x)    environment(x)
#define HIS(x)    x->query_possessive()
#define HE(x)     x->query_pronoun()
#define HIMM(x)    x->query_objective()

void
create_object()
{
    setuid(); seteuid(getuid());

    set_short("small crystal globe");
    set_name("globe");
    add_name("_eil-galaith_globe_");
    set_adj( ({"small", "crystal"}) );
    set_long("This is a small crystal globe that can fit in the palm "+
      "of a hand. The sphere itself is clear and is laden with five "+
      "ornate points of gold, which would rest perfectly within an "+
      "elven hand. Within the sphere you can see sections of land that "+
      "appear to be shaped like a 3-bladed pinwheel. The 'blades' "+
      "of land point approximately north, southeast, and southwest. "+
      "Spread in a circular chain between the tips of the blades are "+
      "small islands. When the light flickers on the globe the forests "+
      "in the southwest speir sparkle mysteriously. Underneath the "+
      "globe you see a small engraving that reads 'Khalakhor'.\n");
    
    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME, 1200);
    add_prop(OBJ_I_VALUE,  100);
    add_prop(OBJ_M_NO_BUY,  1);
}
int
shake_globe(string str)
{
    if(!strlen(str))
	return notify_fail("Shake what?\n");

    if((str == "globe") || (str == "crystal globe") || (str == "small crystal globe"))
    {

        if (TP->query_race_name() != "elf")
        {
             write("You shake the globe vigorously, but nothing happens.\n");
	     say(QCTNAME(TP)+" shakes the " + short() + " vigorously.\n");
	return 1;
        }

	write("You shake the " + short() + " vigorously.\n"+
	  "The globe begins to glow and becomes warm in your hand "+
	  "and you hear a distant voice calling to you.\n"+
	  "Calling you home.\n");
	/* This what others in room see. */
	say(QCTNAME(TP)+" shakes the " + short() + " vigorously "+
	  "then gets a distant look in "+HIS(TP)+" eyes.\n");
	return 1;
    }
}
int
lift_globe(string str)
{
    if(!strlen(str))
	return notify_fail("Lift what?\n");

    if((str == "globe") || (str == "crystal globe") || (str == "small crystal globe"))
    {

        if (TP->query_race_name() != "elf")
        {
             write("You lift the " + short() + " up to inspect it.\n"+
               "It is quite beautiful.\n");
	     say(QCTNAME(TP)+" lifts the " + short() + " upwards "+
	       "and examines it.\n");
	return 1;
        }

	write("You lift the " + short() + " upwards and you marvel "+
	  "at the beauty that is held within the fine crystal.\n");
	/* This what others in room see. */
	say(QCTNAME(TP)+" proudly lifts the " + short() + " upwards, "+
	  "inspecting it carefully.\n");
	return 1;
    }
}
int
focus_globe(string str)
{
    if(!strlen(str))
	return notify_fail("Focus on what?\n");

    if((str == "globe") || (str == "on globe") ||(str == "crystal globe") || (str == "small crystal globe"))
    {

        if (TP->query_race_name() != "elf")
        {
             write("You focus your mind on the " + short() + ", but "+
               "nothing happens.\n");
             say(QCTNAME(TP)+" stares intensely at the " + short() + ".\n");
	return 1;
        }

	write("As you focus on the " + short() + "  you sense yourself "+
	  "floating across the vast forests, endless highlands and "+
	  "proud chasms of great Khalakhor .. to the far south you "+
	  "see a small island and a mysterious tower reaching to the sky.\n");
	/* This what others in room see. */
	say(QCTNAME(TP)+" stares intensely at the " + short() + " and"+
	  "a faint glow briefly appears around "+HIMM(TP)+".\n");
	return 1;
    }
}
void
init()
{
    ::init();
    add_action(shake_globe, "shake");
    add_action(lift_globe, "lift");
    add_action(focus_globe, "focus");
}


    
    
