// Store room for wandering merchant.
// Modified from Boriska's Utterdark merchant.
// Lilith
// Boriska@Genesis August 1994

inherit "/std/room";
inherit "/lib/store_support.c";
#include "../holm.h"

static object merchant_is_alive = 0;

void set_merchant (object mer) {    merchant_is_alive = mer; }
object merchant_alive()        {    return merchant_is_alive;    }
void reset_room();

void create_room ()
{
    set_short ("store room for wandering merchant");
    set_long ("This is store room for wandering merchant.\n" +
	"<mwhere> shows where the merchant is now.\n");
    reset_room();
}

void enter_inv(object ob, object from)
{
	::enter_inv(ob, from);
	store_update(ob);
}

void init ()
{
    ::init();
    add_action ("do_where", "mwhere");
}

int do_where (string str)
{
    object tp = this_player();
  
    if (!tp->query_wiz_level())
    {
        tp->catch_msg("Only wizards are allowed to do that!\n");
        return 1;
    }
    if (merchant_is_alive)
        tp->catch_msg("The merchant is currently at " +
	    file_name(environment(merchant_is_alive)) + ".\n");
    else
        tp->catch_msg ("The merchant is dead.\n");
    return 1;
}

void reset_room()
{
    if (!present("knife",TO))
    {
        clone_object("/d/Avenir/common/obj/knife.c")->move(this_object());
    }
    if (!present("feather",TO))
    {
        clone_object("/d/Avenir/common/obj/feather.c")->move(this_object());
    }
    if (!present("sausage",TO))
    {
        clone_object(DARK + "obj/sausage.c")->move(this_object());
        clone_object(DARK + "obj/sausage.c")->move(this_object());
        clone_object(DARK + "obj/sausage.c")->move(this_object());
    }
}

