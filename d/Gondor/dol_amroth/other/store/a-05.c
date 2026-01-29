/* -*- Mode: C -*-
 *
 * other/store/a-05.c
 *
 * Skippern 20(c)01
 *
 * A store room. ///// CLOTHES
 */
#include "../../defs.h"

inherit DOL_STD + "inside";

/* Global variables */
object        o;
object        *tg;
void
create_inside()
{
    set_short("store room for a-05");
    set_long("this is the store room of the shop in a-05\n\n");

    add_exit(DOL_CRAFT + "houses/a-05", "down", 0, 1);

    tg = allocate(30);

    reset_room();
}

void leave_inv(object ob, object to)
{
    reset_room();
    ::leave_inv(ob, to);
}

void
reset_room()
{
    int i;
    string *a;

    if (!present("pants"))
    {
	o = clone_object(DOL_TG + "pants");
	o->move(this_object());
    } if (!present("coat"))
    {
	o = clone_object(DOL_TG + "coat");
	o->move(this_object());
    } for (i = 0; i < 4; i++)
    {
	if (!present(tg[i]))
	{
	    a = ({ "blue", "brown", "white", "red" });
	    tg[i] = clone_object(DOL_TG + "slippers");
	    tg[i]->set_color(a[i]);
	    tg[i]->move(this_object());
	}
    } if (!present("underwear"))
    {
	o = clone_object(DOL_TG + "underware");
	o->move(this_object());
    } if (!present("pumps"))
    {
	o = clone_object(DOL_TG + "pumps");
	o->move(this_object());
    } if (!present("shirt"))
    {
	o = clone_object(DOL_TG + "shirt");
	o->move(this_object());
    } if (!present("vest"))
    {
	o = clone_object(DOL_TG + "vest");
	o->move(this_object());
    } if (!present("jacket"))
    {
	o = clone_object(DOL_TG + "jacket");
	o->move(this_object());
    } if (!present("jacket"))
    {
	o = clone_object(DOL_TG + "s_jacket");
	o->move(this_object());
    } if (!present("boots"))
    {
	o = clone_object(DOL_TG + "lboots");
	o->move(this_object());
    } if (!present("bowler"))
    {   
	o = clone_object(DOL_TG + "bowler");
	o->move(this_object());
    } if (!present("dress"))
    {
    o = clone_object(DOL_TG + "dress");
    o->set_color(one_of_list( ({ "red", "blue", "white", "black", 
				     "pink", "yellow" }) ) );
    o->move(this_object());
    } if (!present("belt"))
    {
	o = clone_object(DOL_TG + "belt");
	o->move(this_object());
    }
}

