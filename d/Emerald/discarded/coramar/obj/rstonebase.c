/*
 * RSTONEBASE.c
 * Base inherit object for the Rune Stones in Coramar forest
 * Alaron - Feb 1998
 */

#include "/d/Emerald/defs.h"
#include "../coramar.h"
#include "../dirheader.h"
#include <stdproperties.h>

inherit "/std/object";

private string rune_description;

public void create_runestone();
public nomask void hide_me();
public nomask void set_rune_desc(string str);
public nomask string query_rune_desc();


/*
 * Mask this function in the actual object code.
 */
public void
create_runestone()
{
}


void
create_object()
{
    set_name("stone");
    set_adj("small"); add_adj("yellow");

    set_short("small yellow stone");

    set_long("It is a small, extremely smooth stone. It has a very light yellow "+
	"color. It seems to sparkle slightly as there are tiny specks of crystal "+
	"grown naturally inside the stone.  The stone has one side that is "+
	"flat, and another that is curved outward. From looking at it, you guess "+
	"that this "+
	"stone must have come from somewhere deep undergroup or deep within "+
	"a mountain. The almost unnatural smoothness of it leads you to believe "+
	"that it was carved and smoothed by an expert craftsman. No matter how hard "+
	"you try, you can't even guess at how old the item might be. Rolling it over "+
	"in your hand, you notice that on the flat side of the stone there is a "+
	"drawing, etched deep into the stone. The grooves seem to go almost to the "+
	"other side.\n");

    add_item( ({"rune", "drawing", "etch", "etching", "grooves", "flat side", "picture"}),
	"The picture etched into the flat side of the stone looks to be a rune "+
	"of some kind.\n"+
        VBFC("query_rune_desc")+"\n");

    add_item( ({"specks", "speckles", "crystal", "crystals"}),
	"The tiny specks of crystal glint as you roll the stone around in your "+
	"hand, examining it. You've seen rocks with this property before, but "+
	"none were as smooth and perfectly shaped as this.\n");

    add_item( ({"curves", "curved side", "outward curve", "curve"}),
	"The curve of the stone is perfect. You have seen hand-smoothed stones "+
	"before, as well as stones smoothed by the currents of an ocean, but never "+
	"have you encountered a stone as perfectly shaped as this one. In fact, the "+
	"shape is so perfect, so mathematically precise in its angle, that it "+
	"gives you an uneasy feeling.\n");


    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_WEIGHT, 300);

    /*
     * Just in case a player can detect magical resistances, they should see
     * that this object is quite enchanted. 
     */

    add_prop(MAGIC_I_RES_ACID, 100);
    add_prop(MAGIC_I_RES_AIR, 100);
    add_prop(MAGIC_I_RES_COLD, 100);
    add_prop(MAGIC_I_RES_EARTH, 100);
    add_prop(MAGIC_I_RES_ELECTRICITY, 100);
    add_prop(MAGIC_I_RES_FIRE, 100);
    add_prop(MAGIC_I_RES_MAGIC, 100);
    add_prop(MAGIC_I_RES_WATER, 100);

    add_prop(MAGIC_AM_MAGIC, ({ 70, "elemental rune" }) );

    add_prop(MAGIC_AM_ID_INFO,
	     ({ 10, "You get a very strong feeling that the source of the magic of "+
		    "this object is related closely to the rune carving on its "+
	            "flat side.\n",
                30, "You get a strong sense of duality from the magical rune etched "+
	            "into the flat side of the stone. It is almost as if there is "+
	            "another component of the rune that is required to complete "+
                    "its purpose.\n",
                70, "After long and careful consideration of all of the images you "+
	            "receive regarding the magical rune on the flat side of the "+
	            "stone, you get a strong feeling that another, opposite rune "+
                    "is required to join with this one in order to complete the "+
                    "spell as it was intended.\n" }) );

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_SELL, "It may not be worth any money, but you feel that this "+
	"stone is somehow important to you.\n");

    add_prop(OBJ_M_NO_GIVE, "It might make a nice gift, but something about the "+
	"stone makes you want to keep it.\n");
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_NO_TELEPORT, 1);

    create_runestone();


}

public nomask void
hide_me()
{
    add_prop(OBJ_I_HIDE, 15);
}

public nomask void
set_rune_desc(string str)
{
    rune_description = str;
}

public nomask string
query_rune_desc()
{
    return rune_description;
}

